package ddbt.codegen

/**
 * Transform a typed AST into vanilla C++ code (String).
 *
 * @author Mohammad Dashti, Milos Nikolic
 */

object CppGen {
  val VALUE_NAME = "__av"
}

class CppGen(val cgOpts: CodeGenOptions) extends ICppGen 

trait ICppGen extends CodeGen {

  import scala.collection.mutable.{ HashMap, HashSet, ArrayBuffer }
  import ddbt.lib.Utils._
  import ddbt.lib.TypeHelper.Cpp._
  import ddbt.ast._
  import ddbt.ast.M3._ 
  import CppGen._

  private var deltaRelationNames = Set[String]()

  /**
   * By default, each user-provided (top-level) query is materialized as a single map.
   * If this flag is turned on, the compiler will materialize top-level queries as multiple maps (if it is more efficient to do so),
   * and only combine them on request. For more complex queries (in particular nested aggregate, and AVG aggregate queries),
   * this results in faster processing rates, and if fresh results are required less than once per update, a lower overall computational cost as well.
   * However, because the final evaluation of the top-level query is not performed until a result is requested, access latencies are higher.
   * This optimization is not activated by default at any optimization level.
   */
  private var isExpressiveTLQSEnabled = false

  private var isBatchModeActive = false
  
  private def getIndexId(m: String, is: List[Int]): String = 
    (if (is.isEmpty) mapDefs(m).keys.indices.toList else is).mkString

  protected def mapTypeToString(m: MapDef) = 
    if (m.keys.isEmpty) typeToString(m.tp) else m.name + "_map"

  protected def queryTypeToString(q: Query) = 
    if (q.expr.ovars.isEmpty) typeToString(q.expr.tp) else q.name + "_map"

  protected def queryRefTypeToString(q: Query) = 
    if (q.expr.ovars.isEmpty) refTypeToString(q.expr.tp) else q.name + "_map&"

  protected def queryReturnTypeToString(q: Query) = 
    if (q.expr.ovars.isEmpty) refTypeToString(q.expr.tp) else "const " + q.name + "_map&"

  protected def cmpToString(op: OpCmp) = op match {
    case OpEq => "=="
    case OpNe => "!="
    case OpGt => ">"
    case OpGe => ">="
  }

  protected val rIfBranch = """(?s)if\s+\((.*?)\)\s+\{\n(.*)\}\s*""".r

  //---------- Slicing (secondary) indices for a map
  protected val secondaryIndices = 
    HashMap[String, List[List[Int]]]().withDefaultValue(List[List[Int]]())
  
  private def registerSecondaryIndex(mapName: String, columns: List[Int]): Int = {
    val indices = secondaryIndices(mapName)
    val pos = indices.indexOf(columns)
    if (pos != -1) pos 
    else {
      secondaryIndices += (mapName -> (indices ::: List(columns)))
      indices.size
    }
  }
  
  // ---------- Methods manipulating with temporary maps

  // tmp mapName => (List of key types and value type)
  private val tempMapDefinitions = HashMap[String, (List[Type], Type)]()

  protected def emitTempMapDefinitions = {
    val s = tempMapDefinitions.map { case (n, (ksTp, vTp)) =>
      "MultiHashMap<" + tempEntryTypeName(ksTp, vTp) + ", " + typeToString(vTp) + 
        ", PrimaryHashIndex<" + tempEntryTypeName(ksTp, vTp) + "> > " + n + ";"
    }.mkString("\n")

    stringIf(s.nonEmpty, "/* Data structures used as temporary materialized views */\n" + s)
  }

  // Initialize and (if needed) register a temp variable
  private def emitInitTempVar(name: String, tp: Type, keys: List[(String, Type)]): String =
    if (keys.isEmpty) {
      typeToString(tp) + " " + name + " = " + zeroOfType(tp) + ";\n"
    }
    else {
      tempMapDefinitions += (name -> (keys.map(_._2), tp))
      name + ".clear();\n"
    }

  private val tempEntryTypes = HashSet[(List[Type], Type)]()

  protected def emitTempEntryTypes = {
    val s = tempEntryTypes.map { case (ksTp, vTp) =>
      val name = tempEntryTypeName(ksTp, vTp)
      val ksTpIdx = ksTp.zipWithIndex
      val sKeyDefs = ksTpIdx.map { case (t, i) => typeToString(t) + " _" + (i + 1) + ";" }.mkString(" ")
      val sValueDef = typeToString(vTp) + " " + VALUE_NAME + ";"
      val sModFnParams = ksTpIdx.map { case (t, i) => "const " + refTypeToString(t) + " c" + (i + 1) }.mkString(", ")
      val sModFnBody = ksTpIdx.map { case (_, i) => "_" + (i + 1) + " = c" + (i + 1) + ";"}.mkString(" ")
      val sEqualFnBody = ksTpIdx.map { case (_, i) => "(x._" + (i + 1) + " == y._" + (i + 1) + ")" }.mkString(" && ")
      val sHashFnBody = 
        // if (ksTp.forall(isPrimitiveType))
        //   s"h = MurmurHash64A(&e, sizeof(${name}) - sizeof(e.${VALUE_NAME}) - sizeof(e.nxt) - sizeof(e.prv), 0);"
        // else
          ksTpIdx.map { case (_, i) => "hash_combine(h, e._" + (i + 1) + ");" }.mkString("\n")

      s"""|struct ${name} {
          |  ${sKeyDefs} ${sValueDef} ${name}* nxt; ${name}* prv;
          |  explicit ${name}() : nxt(nullptr), prv(nullptr) { }
          |  ${name}& modify(${sModFnParams}) { ${sModFnBody} return *this; }
          |  static bool equals(const ${name} &x, const ${name} &y) {
          |    return (${sEqualFnBody});
          |  }
          |  static long hash(const ${name} &e) {
          |    size_t h = 0;
          |${ind(sHashFnBody, 2)}
          |    return h;
          |  }
          |};
          |""".stripMargin
    }.mkString("\n")

    stringIf(s.nonEmpty, "/* Temporary entry type definitions */\n" + s)
  }

  private def tempEntryTypeName(ksTp: List[Type], vTp: Type): String = 
    "tuple" + (ksTp.size + 1) + "_" + ksTp.map(typeToChar).mkString + "_" + typeToChar(vTp)


  // ---------- Local entry definitions (name and type) are accumulated in this variable
  
  private val localEntries = ArrayBuffer[(String, String)]()

  protected def emitLocalEntryDefinitions = {
    val s = localEntries.map { case (n, t) => t + " " + n + ";" }.mkString("\n")
    stringIf(s.nonEmpty, "/* Preallocated map entries (to avoid recreation of temporary objects) */\n" + s)
  }

  // ---------- Regular expression methods

  private def emitRegexInit = {
    val s = regexpCacheMap.map { case (regex, rvar) =>
        s"""|if (regcomp(&${rvar}, "${regex}", REG_EXTENDED | REG_NOSUB)) {
            |  cerr << "Error compiling regular expression: /${regex}/" << endl;
            |  exit(-1);
            |}
            |""".stripMargin
      }.mkString("\n")

    stringIf(s.nonEmpty, "/* Regular expression initialization */\n" + s)
  }

  private def emitRegexDestroy = {
    val s = regexpCacheMap.map { "regfree(&" + _._2 + ");" }.mkString("\n")
    stringIf(s.nonEmpty,  s"""|~data_t() {
                              |${ind(s)}
                              |}
                              |""".stripMargin)
  }

  private def emitRegexDefinitions = {
    val s = regexpCacheMap.map { "regex_t " + _._2 + ";" }.mkString("\n")
    stringIf(s.nonEmpty, "/* Regular expression objects */\n" + s)
  }

  // ---------- Methods manipulating with constants

  // Constant member definition
  // private def isConstexprDefinition(a: Apply) = a match {
  //   case Apply("StringType", TypeString, Const(TypeString, v) :: Nil) => false
  //   case _ => true
  // }

  private def emitConstDefinitions =
    if (!cgOpts.useOldRuntimeLibrary) {
      val s = hoistedConsts.map {
        case (Apply("StringType", tp, Const(TypeString, v) :: Nil), n) =>
          "static const " + typeToString(tp) + " " + n + ";"

        case (Apply(fn, tp, args), n) =>
          val sArgs = args.map {
            case Const(TypeString, v) => "\"" + v + "\""
            case a => cpsExpr(a)
          }.mkString(", ")
          "static constexpr " + typeToString(tp) + " " +
            n + " = U" + fn + "(" + sArgs + ");"
      }.mkString("\n")
      stringIf(s.nonEmpty, "/* Constant definitions */\n" + s)
    }
    else {
      val s = hoistedConsts.map { case (a, n) =>
        "/* const static */ " + typeToString(a.tp) + " " + n + ";"
      }.mkString("\n")

      stringIf(s.nonEmpty, "/* Constant definitions */\n" + s)      
    }

  private def emitPostConstDefinitions = 
    stringIf(!cgOpts.useOldRuntimeLibrary, {
      val s = hoistedConsts.map {
        case (Apply("StringType", tp, Const(TypeString, v) :: Nil), n) =>
          "const " + typeToString(tp) + " data_t::" + 
            n + " = StringType(\"" + v + "\");"
        case (a, n) => 
          "constexpr " + typeToString(a.tp) + " data_t::" + n + ";"
      }.mkString("\n")
      stringIf(s.nonEmpty, "/* Constant definitions */\n" + s)
    })

  // Constant member initialization
  private def emitConstInits = stringIf(cgOpts.useOldRuntimeLibrary,
    hoistedConsts.map { case (Apply(fn, _, args), n) => 
      if (fn == "StringType") {      // string initialization
        assert(args.size == 1)        // sanity check
        n + " = " + fn + "(\"" + args.head.asInstanceOf[Const].v + "\");"
      }
      else {
        val sArgs = args.map {
          case Const(TypeString, v) => "\"" + v + "\""
          case a => cpsExpr(a)
        }.mkString(", ")
        n + " = U" + fn + "(" + sArgs + ");"
      }
    }.mkString("\n")
  )



  // ----------

  protected def emitMapDefinitions(maps: List[MapDef], queries: List[Query]) = {
    val s = maps.filter { m => !queries.exists(_.name == m.name) }   // exclude TLQ maps
                 .map { m => mapTypeToString(m) + " " + m.name + ";" }
                 .mkString("\n")
    stringIf(s.nonEmpty, "/* Data structures used for storing materialized views */\n" + s)
  }

  private def emitDataDefinitions(maps: List[MapDef], queries: List[Query]) = {    
    s"""|
        |${ind(emitLocalEntryDefinitions)}
        |
        |${ind(emitRegexDefinitions)}
        |
        |${ind(emitMapDefinitions(maps, queries))}
        |
        |${ind(emitTempMapDefinitions)}
        |
        |${ind(emitConstDefinitions)}
        |""".stripMargin
  } 

  // ------- Trigger generation (Start)
  private def emitStmt(s0: Statement): String = s0 match {
    case s: TriggerStmt =>
      val localVar = fresh("se")
      if (s.target.keys.nonEmpty) {
        localEntries += ((localVar, s.target.name + "_entry"))
      }

      val sResetTargetMap = s.op match {
        case OpSet if s.target.keys.isEmpty => 
          s"${s.target.name} = ${zeroOfType(s.target.tp)};\n"
        case OpSet if s.target.keys.nonEmpty => 
          s"${s.target.name}.clear();\n"
        case _ => ""
      }

      val sInitExpr = s.initExpr.map { iexpr =>
        ctx.load()
        cpsExpr(iexpr, (v: String) =>
          if (s.target.keys.isEmpty) 
            s"if (${s.target.name} == ${zeroOfType(iexpr.tp)}) ${s.target.name} = ${v};\n"
          else {
            val sArgs = localVar + ".modify(" + s.target.keys.map(x => rn(x._1)).mkString(", ") + ")"
            s"if (${s.target.name}.getValueOrDefault(${sArgs}) == ${zeroOfType(iexpr.tp)}) ${s.target.name}.setOrDelOnZero(${localVar}, ${v});\n"
          }
        ) 
      }.getOrElse("")

      ctx.load()
      val sStatement = cpsExpr(s.expr, (v: String) =>
        if (v == zeroOfType(s.expr.tp)) "" 
        else if (s.target.keys.isEmpty) {
          extractBooleanExp(v) match {
            case Some((c, t)) =>
              s"""|if (${c}) {
                  |${ind(s"${s.target.name} += ${t};")}
                  |}
                  |""".stripMargin
            case _ =>
              s"${s.target.name} += ${v};\n"
          }
        }
        else {
          val argList = s.target.keys.map(x => rn(x._1)).mkString(", ")
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              s"""|if (${c}) {
                  |${ind(s"${s.target.name}.addOrDelOnZero(${localVar}.modify(${argList}), ${t});")}
                  |}
                  |""".stripMargin
            case _ =>
              s"${s.target.name}.addOrDelOnZero(${localVar}.modify(${argList}), ${v});\n"
          }
        },
        Some(s.target.keys)
      )

      sResetTargetMap + sInitExpr + sStatement

    case s: IfStmt =>
      ctx.load()
      cpsExpr(s.cond, (v: String) =>
        extractBooleanExp(v) match {
          case Some((c, t)) =>
            "if (" + c + ") {\n" +
              ind(s.thenBlk.map(emitStmt).mkString("\n")) +
            "\n}\n" + 
            stringIf(s.elseBlk.nonEmpty, 
              "else {\n" +
                ind(s.elseBlk.map(emitStmt).mkString("\n")) +
              "\n}\n"
            )
          case None => sys.error("No if condition")
        }        
      )
  }

  private def emitTrigger(t: Trigger): String = {
    // Generate trigger statements    
    val sTriggerBody = {
      ctx = Ctx(t.event.params.map { case (n, tp) => (n, (tp, n)) }.toMap)
      val body = t.stmts.map(emitStmt).mkString("\n")
      ctx = null
      body
    }
  
    def emitBatchTrigger(s: Schema, body: String) = {
      val sTimeout = stringIf(cgOpts.timeoutMilli > 0, 
        s"""|if (tS > 0) { tS += batchSize; return; }
            |gettimeofday(&t, NULL);
            |tT = (t.tv_sec - t0.tv_sec) * 1000L;
            |if (tT > ${cgOpts.timeoutMilli}) { tS = batchSize; return; }
            |""".stripMargin)
      val name = s.name.toLowerCase.capitalize
      if (!cgOpts.useOldRuntimeLibrary) {
        s"""|void on_batch_update_${s.name}(const vector<BatchMessage<${name}Adaptor::MessageType, int>::KVpair>& batch) {
            |${ind(sTimeout)}
            |  tN += batch.size();
            |${ind(body)}
            |}
            |""".stripMargin
      }
      else {
        s"""|void on_batch_update_${s.name}(${delta(s.name)}_map &${delta(s.name)}) {
            |  long batchSize = ${delta(s.name)}.count();
            |${ind(sTimeout)}
            |  tN += batchSize;
            |${ind(body)}
            |}
            |""".stripMargin
      }      
    }

    def emitSingleTupleTrigger(s: Schema, prefix: String, body: String) = {
      val sTimeout = stringIf(cgOpts.timeoutMilli > 0, 
        s"""|if (tS > 0) { ++tS; return; }
            |if ((tN & 127) == 0) {
            |  gettimeofday(&t, NULL);
            |  tT = (t.tv_sec - t0.tv_sec) * 1000L;
            |  if (tT > ${cgOpts.timeoutMilli}) { tS = 1; return; }
            |}
            |""".stripMargin)
      val sName = prefix + s.name
      val sParams = s.fields.map { case (n, t) => s"const ${refTypeToString(t)} ${n}" }.mkString(", ")

      s"""|inline void ${sName}(${sParams}) {
          |${ind(sTimeout)}
          |  ++tN;
          |${ind(body)}
          |}
          |""".stripMargin      
    }

    def emitReadyTrigger(body: String) = {
      s"""|void on_system_ready_event() {
          |${ind(body)}
          |}
          |""".stripMargin      
    }

    t.event match {
      case EventBatchUpdate(s) => emitBatchTrigger(s, sTriggerBody)
      case EventInsert(s) => emitSingleTupleTrigger(s, "on_insert_", sTriggerBody)
      case EventDelete(s) => emitSingleTupleTrigger(s, "on_delete_", sTriggerBody)
      case EventReady => emitReadyTrigger(sTriggerBody)
    }
  } 

  protected def emitFieldNames(fields: List[(String, Type)]) = fields.map(_._1).mkString(", ")

  protected def emitInsertToMapFunc(map: String, entry: String) = 
    map + ".addOrDelOnZero(" + entry + ", 1);"

  protected def emitTableTriggers(sources: List[Source]) = {
    sources.filter(!_.isStream).map { s =>
      val name = s.schema.name
      val fields = s.schema.fields
      val params = fields.map { case (n, t) => "const " + typeToString(t) + " " + n }.mkString(", ")
      val args = emitFieldNames(fields)
      val entry = fresh("entry")

      s"""|void on_insert_${name}(${params}) {
          |  ${name}_entry ${entry}(${args}, 1);
          |  ${emitInsertToMapFunc(name, s"${entry}")}
          |}
          |""".stripMargin +
      stringIf(cgOpts.useOldRuntimeLibrary, {
        val castArgs = fields.zipWithIndex.map { case ((_, tp), i) => 
            "*(reinterpret_cast<" + typeToString(tp) + "*>((*ea)[" + i + "].get()))"
          }.mkString(", ")

        emitUnwrapFunction(EventInsert(s.schema), sources) +
        // 
        stringIf(isBatchModeActive, 
          s"""|void unwrap_batch_update_${name}(const event_args_t& eaList) {
              |  size_t sz = eaList.size();
              |  for (size_t i = 0; i < sz; i++) {
              |    event_args_t* ea = reinterpret_cast<event_args_t*>(eaList[i].get());
              |    ${name}_entry e(${castArgs}, 1);
              |    ${emitInsertToMapFunc(name, "e")}
              |  }
              |}
              |""".stripMargin)
      })
    }.mkString("\n")
  }
  
  protected def emitStreamTriggers(triggers: List[Trigger], sources: List[Source]) = {
    triggers.map { t =>
      emitTrigger(t) + stringIf(t.event != EventReady, "\n" + emitUnwrapFunction(t.event, sources))
    }.mkString("\n")
  }

  private def emitTriggerFunctions(s0: System) = {
    s"""|/* Trigger functions for table relations */
        |${emitTableTriggers(s0.sources)}
        |
        |/* Trigger functions for stream relations */
        |${emitStreamTriggers(s0.triggers, s0.sources)}
        |""".stripMargin
  }

  protected def emitUnwrapFunction(evt: EventTrigger, sources: List[Source]) = stringIf(cgOpts.useOldRuntimeLibrary, {
    val (op, name, fields) = evt match {
      case EventBatchUpdate(Schema(n, cs)) => ("batch_update", n, cs)
      case EventInsert(Schema(n, cs)) => ("insert", n, cs)
      case EventDelete(Schema(n, cs)) => ("delete", n, cs)
      case _ => sys.error("Unsupported trigger event " + evt)
    }
    val constructorArgs = fields.zipWithIndex.map { case ((_, t), i) => 
      "*(reinterpret_cast<" + typeToString(t) + "*>(ea[" + i + "].get()))"
    }.mkString(", ")

    evt match {
      case EventBatchUpdate(_) =>
        var code =    "void unwrap_" + op + "_" + name + "(const event_args_t& eaList) {\n"
        code = code + "  size_t sz = eaList.size();\n"
        for (s <- sources.filter(_.isStream)) {
          code = code + "  " + delta(s.schema.name) + ".clear();\n"
        }       
        code = code +   "  for (size_t i = 0; i < sz; i++) {\n"
        code = code +   "    event_args_t* ea = reinterpret_cast<event_args_t*>(eaList[i].get());\n"
        code = code +   "    relation_id_t relation = *(reinterpret_cast<relation_id_t*>((*ea).back().get()));\n"
        
        for (s <- sources.filter(_.isStream)) {
          val schema = s.schema
          val constructorArgs = s.schema.fields.zipWithIndex.map { case ((_, t), i) =>
              "*(reinterpret_cast<" + typeToString(t) + "*>((*ea)[" + i + "].get()))"
            }.mkString(", ")
          code = code + "    if (relation == program_base->get_relation_id(\"" + s.schema.name + "\"" + ")) { \n"
          code = code + "      event_args_t* ea = reinterpret_cast<event_args_t*>(eaList[i].get());\n"
          code = code + "      " + delta(s.schema.name) + "_entry e(" + constructorArgs + ", *(reinterpret_cast<" + typeToString(TypeLong) + "*>((*ea)[" + s.schema.fields.size + "].get())));\n"
          code = code + "      " + delta(s.schema.name) + ".addOrDelOnZero(e, *(reinterpret_cast<" + typeToString(TypeLong) + "*>((*ea)[" + s.schema.fields.size + "].get())));\n"
          code = code + "    }\n"
        }
        code = code +   "  }\n"
        for (s <- sources.filter(_.isStream)) {
          code = code + "  on_" + op + "_" + s.schema.name + "(" + delta(s.schema.name) + ");\n"
        }            
        code = code +   "}\n\n"

        val deltaRel = delta(name)
        val insertOp = "insert"
        code +
        s"""|void unwrap_insert_${name}(const event_args_t& ea) {
            |  ${deltaRel}.clear(); 
            |  ${deltaRel}_entry e(${constructorArgs}, 1);
            |  ${deltaRel}.${insertOp}(e);
            |  on_batch_update_${name}(${deltaRel});
            |}
            |
            |void unwrap_delete_${name}(const event_args_t& ea) {
            |  ${deltaRel}.clear(); 
            |  ${deltaRel}_entry e(${constructorArgs}, -1);
            |  ${deltaRel}.${insertOp}(e);
            |  on_batch_update_${name}(${deltaRel});
            |}
            |""".stripMargin
      case _ =>
        s"""|void unwrap_${op}_${name}(const event_args_t& ea) {
            |  on_${op}_${name}(${constructorArgs});
            |}
            |""".stripMargin
    }
  })  
  // ------- Trigger generation (End)

  protected def emitMapTypes(s0: System) = {
    "/* Definitions of maps used for storing materialized views. */\n" + 
    { // Maps (declared maps + tables + batch updates)
      s0.maps.filter(_.keys.nonEmpty) ++
      // Queries without a map (with -F EXPRESSIVE-TLQS)
      s0.queries.filter {
        q => q.expr.ovars.nonEmpty && !s0.maps.exists(_.name == q.name)
      }.map {
        q => MapDef(q.name, q.expr.tp, q.expr.ovars, q.expr, LocalExp)
      }
    }.map(emitMapType).mkString("\n")
  }

  private def emitMapType(m: MapDef) = {
    val mapName = m.name
    val mapEntryType = mapName + "_entry"
    val mapType = mapName + "_map"
    val mapValueType = typeToString(m.tp)    
    val fields = m.keys ++ List(VALUE_NAME -> m.tp)
    val indices =     // primary + (multiple) secondary 
      (m.keys.indices.toList -> true /* unique */) ::
      secondaryIndices(m.name).map(p => p -> false /* non_unique */)

    val sEntryType = {
      val sModifyFn = {
        val s = indices.map { case (cols, unique) =>
            val params = cols.map(i => "const " + refTypeToString(fields(i)._2) + " c" + i).mkString(", ")
            val body = cols.map(i => fields(i)._1 + " = c" + i + "; ").mkString
            s"FORCE_INLINE ${mapEntryType}& modify" + stringIf(!unique, getIndexId(mapName, cols)) + 
            "(" + params + ") { " + body + " return *this; }"
          }.mkString("\n")

        stringIf(s.nonEmpty, "\n" + s + "\n")
      }

      emitEntryType(mapEntryType, m.keys, (VALUE_NAME, m.tp))(sModifyFn)
    }

    val sIndexOpsType = indices.map { case (is, unique) =>
      val name = mapType + "key" + getIndexId(mapName, is) + "_idxfn"

      val sCombinators = 
        // if (unique && m.keys.forall(x => isPrimitiveType(x._2)))
        //   s"h = MurmurHash64A(&e, sizeof(${mapEntryType}) - sizeof(e.${VALUE_NAME}) - sizeof(e.nxt) - sizeof(e.prv), 0);"
        // else 
          is.map { idx =>
            "hash_combine(h, e." + fields(idx)._1 + ");"
          }.mkString("\n")

      val sCmpExpr = is.map { idx =>
        val (n, tp) = fields(idx)
        cmpFunc(tp, OpEq, "x." + n, "y." + n, false)
      }.mkString(" && ")

      s"""|struct ${name} {
          |  FORCE_INLINE static size_t hash(const ${mapEntryType}& e) {
          |    size_t h = 0;
          |${ind(sCombinators, 2)}
          |    return h;
          |  }
          |  
          |  FORCE_INLINE static bool equals(const ${mapEntryType}& x, const ${mapEntryType}& y) {
          |    return ${sCmpExpr};
          |  }
          |};
          |""".stripMargin
    }.mkString("\n")

    val sMapTypedefs = {
      val sIndices = indices.map { case (is, unique) =>
          if (unique) "PrimaryHashIndex<" + mapEntryType + ", " + mapType + "key" + getIndexId(mapName, is) + "_idxfn>"
          else "SecondaryHashIndex<" + mapEntryType + ", " + mapType + "key" + getIndexId(mapName, is) + "_idxfn>"
        }.mkString(",\n")
      
      s"""|typedef MultiHashMap<${mapEntryType}, ${mapValueType}, 
          |${ind(sIndices)}
          |> ${mapType};
          |""".stripMargin
    }

    s"""|${sEntryType}
        |${sIndexOpsType}
        |${sMapTypedefs}
        |""".stripMargin
  }

  private def emitEntryType(name: String, keys: List[(String, Type)], value: (String, Type)): String => String = {
    val fields = keys ++ List(value)

    val sFieldDefinitions = fields.map { case (n, t) => 
        typeToString(t) + " " + n + "; " 
      }.mkString + name + "* nxt; " + name + "* prv;"
          
    val sConstructorParams = fields.zipWithIndex.map { case ((_, tp), i) => 
        "const " + refTypeToString(tp) + " c" + i 
      }.mkString(", ")
    
    val sConstructorBody = fields.zipWithIndex.map { case ((n, _), i) => 
        n + " = c" + i + "; " 
      }.mkString

    val sInitializers = fields.map { case (n, tp) => 
        n + "(other." + n + "), "
      }.mkString + "nxt(nullptr), prv(nullptr)"

    val sSerialization = 
      if (!cgOpts.useOldRuntimeLibrary)
        fields.map { case (n, _) =>
          s"""|ar << dbtoaster::serialization::kElemSeparator;
              |dbtoaster::serialization::serialize(ar, ${n}, STRING(${n}));
              |""".stripMargin
        }.mkString
      else 
        fields.map { case (n, _) =>
          s"""|ar << ELEM_SEPARATOR;
              |dbtoaster::serialize_nvp(ar, STRING(${n}), ${n});
              |""".stripMargin
        }.mkString

    s =>
      s"""|struct ${name} {
          |  ${sFieldDefinitions}
          |
          |  explicit ${name}() : nxt(nullptr), prv(nullptr) { }
          |  explicit ${name}(${sConstructorParams}) { ${sConstructorBody} }
          |  ${name}(const ${name}& other) : ${sInitializers} { }
          |
          |${ind(s)}
          |  template<class Archive>
          |  void serialize(Archive& ar) const {
          |${ind(sSerialization, 2)}
          |  }
          |};
          |""".stripMargin
  }

  private def emitTLQStructure(s0: System) = {  
    
    val sSerializeFn = {
      val body = 
        if (!cgOpts.useOldRuntimeLibrary)
          s0.queries.map { q =>
            s"""|ar << "\\n";
                |const ${queryRefTypeToString(q)} _${q.name} = get_${q.name}();
                |dbtoaster::serialization::serialize(ar, _${q.name}, STRING(${q.name}), "\\t");
                |""".stripMargin
          }.mkString("\n")
        else 
          s0.queries.map { q =>
            s"""|ar << "\\n";
                |const ${queryRefTypeToString(q)} _${q.name} = get_${q.name}();
                |dbtoaster::serialize_nvp_tabbed(ar, STRING(${q.name}), _${q.name}, "\\t");
                |""".stripMargin
          }.mkString("\n")


      s"""|/* Serialization code */
          |template<class Archive>
          |void serialize(Archive& ar) const {
          |${ind(body)}
          |}
          |""".stripMargin
    }

    val sTLQGetters = {
      val s = s0.queries.map { q =>
        val body = q.expr match {
          case MapRef(n, _, _, _) if n == q.name =>
            "return " + q.name + ";"
          case _ =>
            ctx = Ctx[(Type, String)]()
            if (q.expr.ovars.isEmpty) {
              cpsExpr(q.expr, (v: String) => "return " + v + ";")
            }
            else {
              val localEntry = fresh("se")
              localEntries += ((localEntry, q.name + "_entry"))
              val localEntryArgs = q.expr.ovars.map(v => rn(v._1)).mkString(", ")            
              val sEvaluateExpr = cpsExpr(q.expr, (v: String) =>
                s"${q.name}.addOrDelOnZero(${localEntry}.modify(${localEntryArgs}), ${v});")

              s"""|${q.name}.clear();
                  |${sEvaluateExpr}
                  |return ${q.name};
                  |""".stripMargin
            }
        }
        s"""|${queryReturnTypeToString(q)} get_${q.name}() const {
            |${ind(body)}
            |}
            |""".stripMargin
      }.mkString("\n")

      stringIf(s.nonEmpty, "/* Functions returning / computing the results of top level queries */\n" + s)
    }

    val sTLQDefinitions = emitTLQDefinitions(s0.queries) 

    val sDataDefinitions = 
      stringIf(isExpressiveTLQSEnabled, emitDataDefinitions(s0.maps, s0.queries))

    val sTLQMapInitializer = emitTLQMapInitializer(s0.maps, s0.queries)

    s"""|/* Defines top-level materialized views */
        |struct tlq_t {
        |  struct timeval t0, t; unsigned long tT, tN, tS;
        |  tlq_t(): tN(0), tS(0) ${sTLQMapInitializer} { 
        |    gettimeofday(&t0, NULL); 
        |  }
        |
        |${ind(sSerializeFn)}
        |
        |${ind(sTLQGetters)}
        |
        |protected:
        |${ind(sTLQDefinitions)}
        |${ind(sDataDefinitions)}
        |};
        |
        |""".stripMargin
  }

  private def emitSourceInitializers(s0: System) = {
    val adaptors = s0.sources.zipWithIndex.map { case (s, i) =>
      val name = s.schema.name.toLowerCase.capitalize
      val types = s.schema.fields.map { case (_, t) => typeToString(t) }.mkString(", ")
      val params = 
          (s.adaptor.options + ("deletions" -> cgOpts.datasetWithDeletions.toString)).map {
            case (k, v) => s"""{ "$k", "$v" }""" 
          }
      val tp = if (s.isStream) "RelationType::kStream" else "RelationType::kTable"
      s"""|struct ${name}Adaptor {
          |  using MessageType = Message<std::tuple<$types>>;
          |
          |  static constexpr Relation relation() {
          |    return Relation(${i + 1}, "${name.toUpperCase}", $tp);
          |  }
          |
          |  static constexpr CStringMap<${params.size}> params() {
          |    return CStringMap<${params.size}>{{ { ${params.mkString(", ")} } }};
          |  }
          |};""".stripMargin
    }.mkString("\n")

    s"""|static constexpr bool kOrderedDataset = ${cgOpts.datasetWithDeletions};
        |static constexpr bool kBatchModeActive = ${isBatchModeActive};
        |
        |${adaptors}
        |""".stripMargin
  }

  private def emitRegisterMapsFn(s0: System) = {
    val body = s0.maps.map { m =>
        val toplevel = s0.queries.exists(_.name == m.name)
        s"""visitor.template addMap<${mapTypeToString(m)}>("${m.name}", ${m.name}, ${toplevel});"""
      }.mkString("\n")
    s"""|template <class Visitor>
        |void registerMaps(Visitor& visitor) {
        |${ind(body)}
        |}
        |""".stripMargin
  }

  private def emitRegisterSourcesFn(s0: System) = {
    val body = s0.sources.groupBy(_.in).map { 
      case (SourceFile(path), sources) =>        
        assert(sources.map(_.adaptor.name).distinct.size == 1)
        val adaptors = sources.map(_.schema.name.toLowerCase.capitalize + "Adaptor{}").mkString(",\n")
        s"""|visitor.template addSource(
            |  "${sources.head.adaptor.name.toUpperCase}",
            |  FileSource("$path"),
            |${ind(adaptors)}
            |);""".stripMargin
      case (s, _) => 
        sys.error("Unsupported source type: " + s)
    }.mkString("\n")
    s"""|template <class Visitor>
        |static void registerSources(Visitor& visitor) {
        |${ind(body)}
        |}
        |""".stripMargin
  }

  private def emitProcessStreamEventFn(s0: System) = {
    val body = s0.sources.flatMap { s =>
      val name = s.schema.name.toLowerCase.capitalize
      val msgType = s"${name}Adaptor::MessageType"
      val args = 
        (0 until s.schema.fields.size).map { i => 
          s"get<${i}>(tpl)" }.mkString(", ")
      s0.triggers.flatMap { _.event match {
        case EventInsert(schema) if schema.name == s.schema.name =>
            List(
              s"""|if (e.id == Event::getId(${name}Adaptor::relation().id, EventType::kInsertTuple)) {
                  |  auto& tpl = static_cast<$msgType*>(e.message.get())->content;
                  |  on_insert_${name.toUpperCase}(
                  |${ind(args, 2)}
                  |  );
                  |}
                  |""".stripMargin)
          case EventDelete(schema) if schema.name == s.schema.name =>
            List(
              s"""|if (e.id == Event::getId(${name}Adaptor::relation().id, EventType::kDeleteTuple)) {
                  |  auto& tpl = static_cast<$msgType*>(e.message.get())->content;
                  |  on_delete_${name.toUpperCase}(
                  |${ind(args, 2)}
                  |  );
                  |}
                  |""".stripMargin)
          case EventBatchUpdate(schema) if schema.name == s.schema.name =>
            List(
              s"""|if (e.id == Event::getId(${name}Adaptor::relation().id, EventType::kBatchUpdate)) {
                  |  auto* msg = static_cast<BatchMessage<$msgType, int>*>(e.message.get());
                  |  on_batch_update_${name.toUpperCase}(msg->content);
                  |}
                  |""".stripMargin)
          case _ => Nil
      }}
    }.mkString("else ")
    s"""|void process_stream_event(const Event& e) {
        |${ind(body)}
        |}
        |""".stripMargin
  }

  private def emitProcessTableEventFn(s0: System) = {
    val body = s0.sources.filterNot(_.isStream).map { s =>
      val name = s.schema.name.toLowerCase.capitalize
      val msgType = s"${name}Adaptor::MessageType"
      val args =
        (0 until s.schema.fields.size).map { i => s"get<${i}>(tpl)" }.mkString(", ")
      s"""|if (e.id == Event::getId(${name}Adaptor::relation().id, EventType::kInsertTuple)) {
          |  auto& tpl = static_cast<$msgType*>(e.message.get())->content;
          |  on_insert_${name.toUpperCase}(
          |${ind(args, 2)}
          |  );
          |}
          |""".stripMargin
    }.mkString("else ")
    s"""|void process_table_event(const Event& e) {
        |${ind(body)}
        |}
        |""".stripMargin
  }

  protected def emitTLQMapInitializer(maps: List[MapDef], queries: List[Query]) = {
    // TLQ map initializer
    maps.filter { m => m.keys.isEmpty && queries.exists(_.name == m.name) }
        .map { m => ", " + m.name + "(" + zeroOfType(m.tp) + ")" }
        .mkString +
    stringIf(isExpressiveTLQSEnabled, {
      // Non-TLQ map initializer
      maps.filter { m => m.keys.isEmpty && !queries.exists(_.name == m.name) }
          .map { m => ", " + m.name + "(" + zeroOfType(m.tp) + ")" }
          .mkString
    })
  }

  protected def emitTLQDefinitions(queries: List[Query]) = {
    val s = queries.map { q => s"${queryTypeToString(q)} ${q.name};" }.mkString("\n")
    stringIf(s.nonEmpty, "/* Data structures used for storing / computing top-level queries */\n" + s)
  }

  private def emitIVMStructure(s0: System) = {

    val sTriggerFunctions = emitTriggerFunctions(s0)

    val sRegisterData = stringIf(cgOpts.useOldRuntimeLibrary, {

      val sRegisterMaps = {
        val s = s0.maps.map { m =>
            s"""pb.add_map<${mapTypeToString(m)}>("${m.name}", ${m.name});"""
          }.mkString("\n")

        stringIf(s.nonEmpty, "// Register maps\n" + s)
      }

      val sRegisterRelations = {
        val s = s0.sources.map { s => 
            s"""pb.add_relation("${s.schema.name}", ${if (s.isStream) "false" else "true"});"""
          }.mkString("\n")

        stringIf(s.nonEmpty, "// Register streams and tables\n" + s)
      }

      val sRegisterStreamTriggers = {
        val s = s0.triggers.filter(_.event != EventReady).map { _.event match {
          case EventBatchUpdate(Schema(n, _)) =>
            s"""|pb.add_trigger("${n}", batch_update, std::bind(&data_t::unwrap_batch_update_${n}, this, std::placeholders::_1));
                |pb.add_trigger("${n}", insert_tuple, std::bind(&data_t::unwrap_insert_${n}, this, std::placeholders::_1));
                |pb.add_trigger("${n}", delete_tuple, std::bind(&data_t::unwrap_delete_${n}, this, std::placeholders::_1));""".stripMargin
          case EventInsert(Schema(n, _)) => 
            s"""pb.add_trigger("${n}", insert_tuple, std::bind(&data_t::unwrap_insert_${n}, this, std::placeholders::_1));"""
          case EventDelete(Schema(n, _)) => 
            s"""pb.add_trigger("${n}", delete_tuple, std::bind(&data_t::unwrap_delete_${n}, this, std::placeholders::_1));"""
          case _ => ""
        }}.mkString("\n")

        stringIf(s.nonEmpty, "// Register stream triggers\n" + s)
      }

      val sRegisterTableTriggers = {          
        val s = s0.sources.filter(!_.isStream).map { s => 
            stringIf(isBatchModeActive,
              s"""pb.add_trigger("${s.schema.name}", batch_update, std::bind(&data_t::unwrap_batch_update_${s.schema.name}, this, std::placeholders::_1));\n"""
            ) + 
            s"""pb.add_trigger("${s.schema.name}", insert_tuple, std::bind(&data_t::unwrap_insert_${s.schema.name}, this, std::placeholders::_1));"""
          }.mkString("\n")

        stringIf(s.nonEmpty, "// Register table triggers\n" + s) 
      }

      s"""|/* Registering relations and trigger functions */
          |ProgramBase* program_base;
          |void register_data(ProgramBase& pb) {
          |  program_base = &pb;
          |
          |${ind(sRegisterMaps)}
          |
          |${ind(sRegisterRelations)}
          |
          |${ind(sRegisterStreamTriggers)}
          |
          |${ind(sRegisterTableTriggers)}
          |
          |}
          |""".stripMargin
    })

    val sDataDefinitions = 
      stringIf(!isExpressiveTLQSEnabled, emitDataDefinitions(s0.maps, s0.queries))

    s"""|/* Contains materialized views and processing (IVM) logic */
        |struct data_t : tlq_t {
        |
        |  data_t(): tlq_t()${emitNonTLQMapInitializer(s0.maps, s0.queries)} {
        |${ind(emitConstInits, 2)}
        |${ind(emitRegexInit, 2)}
        |  }
        |
        |${ind(emitRegexDestroy)}
        |
        |${ind(sRegisterData)}
        |
        |${stringIf(!cgOpts.useOldRuntimeLibrary, ind(emitSourceInitializers(s0)))}
        |
        |${ind(sTriggerFunctions)}
        |
        |${stringIf(!cgOpts.useOldRuntimeLibrary, ind(emitRegisterMapsFn(s0)))}
        |
        |${stringIf(!cgOpts.useOldRuntimeLibrary, ind(emitRegisterSourcesFn(s0)))}
        |
        |${stringIf(!cgOpts.useOldRuntimeLibrary, ind(emitProcessStreamEventFn(s0)))}
        |
        |${stringIf(!cgOpts.useOldRuntimeLibrary, ind(emitProcessTableEventFn(s0)))}
        |
        |private:
        |${ind(sDataDefinitions)}
        |};
        |
        |${emitPostConstDefinitions}
        |""".stripMargin
  }

  protected def emitNonTLQMapInitializer(maps: List[MapDef], queries: List[Query]) =
    stringIf(!isExpressiveTLQSEnabled, {
      // Non-TLQ map initializer
      maps.filter { m => m.keys.isEmpty && !queries.exists(_.name == m.name) }
          .map { m => ", " + m.name + "(" + zeroOfType(m.tp) + ")" }
          .mkString
    })

  private def emitMainClass(s0: System) = stringIf(cgOpts.useOldRuntimeLibrary, {
    s"""|/* Type definition providing a way to execute the sql program */
        |class Program : public ProgramBase {
        |  public:
        |    Program(int argc = 0, char* argv[] = 0) : ProgramBase(argc,argv) {
        |      data.register_data(*this);
        |
        |${ind(emitSourceDefinitions(s0.sources), 3)}
        |    }
        |
        |    /* Imports data for static tables and performs view initialization based on it. */
        |    void init() {
        |        table_multiplexer.init_source(run_opts->batch_size, run_opts->parallel, true);
        |        stream_multiplexer.init_source(run_opts->batch_size, run_opts->parallel, false);
        |
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}struct timeval ts0, ts1, ts2;
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}gettimeofday(&ts0, NULL);
        |        process_tables();
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}gettimeofday(&ts1, NULL);
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}long int et1 = (ts1.tv_sec - ts0.tv_sec) * 1000L + (ts1.tv_usec - ts0.tv_usec) / 1000;
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}std::cout << "Populating static tables time: " << et1 << " (ms)" << std::endl;
        |
        |        data.on_system_ready_event();
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}gettimeofday(&ts2, NULL);
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}long int et2 = (ts2.tv_sec - ts1.tv_sec) * 1000L + (ts2.tv_usec - ts1.tv_usec) / 1000;
        |        ${stringIf(!cgOpts.printTiminingInfo, "// ")}std::cout << "OnSystemReady time: " << et2 << " (ms)" << std::endl;
        |
        |        gettimeofday(&data.t0, NULL);
        |    }
        |
        |    /* Saves a snapshot of the data required to obtain the results of top level queries. */
        |    snapshot_t take_snapshot() {
        |${ind(emitTakeSnapshotBody, 4)}
        |        return snapshot_t( d );
        |    }
        |
        |  protected:
        |    data_t data;
        |};
        |""".stripMargin +
        //
        stringIf(cgOpts.className != "Program",
          s"""|
              |class ${cgOpts.className} : public Program {
              |  public:
              |    ${cgOpts.className}(int argc = 0, char* argv[] = 0) : Program(argc, argv) { }
              |};""".stripMargin
        )
  })

  protected def emitTakeSnapshotBody = 
    s"""|${stringIf(!cgOpts.printTiminingInfo, "// ")}gettimeofday(&data.t, NULL);
        |${stringIf(!cgOpts.printTiminingInfo, "// ")}long int t = (data.t.tv_sec - data.t0.tv_sec) * 1000L + (data.t.tv_usec - data.t0.tv_usec) / 1000;
        |${stringIf(!cgOpts.printTiminingInfo, "// ")}std::cout << "Trigger running time: " << t << " (ms)" << std::endl;
        |
        |tlq_t* d = new tlq_t((tlq_t&) data);
        |${stringIf(cgOpts.isReleaseMode, "// ")}gettimeofday(&(d->t), NULL);
        |${stringIf(cgOpts.isReleaseMode, "// ")}d->tT = ((d->t).tv_sec - (d->t0).tv_sec) * 1000000L + ((d->t).tv_usec - (d->t0).tv_usec);
        |${stringIf(cgOpts.isReleaseMode, "// ")}printf(\"SAMPLE = ${cgOpts.dataset}, %ld, %ld, %ld\\n\", d->tT, d->tN, d->tS);
        |""".stripMargin

  private def emitSourceDefinition(s: Source): String = {
    val sourceId = fresh("source");

    val adaptorVar = sourceId + "_adaptor"    
    val sAdaptor = {
      val paramsVar = adaptorVar + "_params"
      val schemaTypes = s.schema.fields.map { _._2.toString }.mkString(",")

      s.adaptor.name.toUpperCase match {
        case "ORDERBOOK" => {
          val (orderBookTypes, others) = 
            s.adaptor.options.partition { x => x._1 == "bids" || x._1 == "asks"}
          val orderBookType = orderBookTypes.size match {
            case 1 => orderBookTypes.head._1
            case 2 => "both"
          }
          val options = others ++ Map("schema" -> schemaTypes)
          val pairs = 
            "make_pair(\"book\", \"" + orderBookType + "\"), " +
            options.map { x => "make_pair(\"" + x._1 + "\", \"" + x._2 + "\")" }.mkString(", ")

          "pair<string,string> " + paramsVar + "[] = { " + pairs + " };\n" +
          "std::shared_ptr<order_books::order_book_adaptor> " + adaptorVar +
          "(new order_books::order_book_adaptor(" + 
          List("bids", "asks").map { x =>  
            if (s.adaptor.options.contains(x))
              "get_relation_id(\"" + s.adaptor.options(x) + "\"), "
            else "-1, " 
          }.mkString +
          (options.size + 1) + ", " + paramsVar + "));\n"
        }      
        case "CSV" => {
          val options = s.adaptor.options ++ Map("schema" -> schemaTypes, "deletions" -> cgOpts.datasetWithDeletions.toString)
          val pairs = options.map { x => "make_pair(\"" + x._1 + "\", \"" + x._2 + "\")" }.mkString(", ")

          "pair<string,string> " + paramsVar + "[] = { " + pairs + " };\n" +
          "std::shared_ptr<csv_adaptor> " + adaptorVar + 
          "(new csv_adaptor(get_relation_id(\"" + s.schema.name + "\"), " +
          options.size + ", " + paramsVar + "));\n"
        }
      }
    }

    val sourceSplitVar = sourceId + "_fd"
    val sFrameDescriptor = 
      "frame_descriptor " + sourceSplitVar + 
        (s.split match { 
          case SplitLine => "(\"\\n\")" 
          case SplitSep(sep) => "(\"" + sep + "\")" 
          case SplitSize(bytes) => "(" + bytes + ")" 
          case SplitPrefix(p) => "XXXXX(" + p + ")"   //XXXX for SplitPrefix
        }) + ";\n"

    val sourceFileVar = sourceId + "_file"
    val sFileSource = s.in match { case SourceFile(path) => 
      "std::shared_ptr<dbt_file_source> " + sourceFileVar + 
      "(new dbt_file_source(\"" + path + "\"," + sourceSplitVar + "," + adaptorVar + "));\n" 
    }
    
    val registerSource = "add_source(" + sourceFileVar + (if (s.isStream) ", false" else ", true") + ");\n"

    sAdaptor + sFrameDescriptor + sFileSource + registerSource
  }

  private def emitSourceDefinitions(sources: List[Source]) = {
    // one source generates BOTH asks and bids events
    def fixOrderbook(ss: List[Source]): List[Source] = { 
      val (obooks, others) = ss.partition { _.adaptor.name == "ORDERBOOK" }
      
      val grouped = HashMap[(Boolean, SourceIn), (Schema, Split, Map[String, String], LocalityType)]()     
      obooks.foreach { case Source(isStream, schema, in, split, adp, loc) =>
        val k = (isStream, in)
        val v = (adp.options - "book") + ((adp.options.getOrElse("book", "bids"), schema.name))
        grouped.get(k) match {
          case Some(v2) => grouped += (k -> (schema, split, v2._3 ++ v, loc))
          case None => grouped += (k -> (schema, split, v, loc))
        }
      }
      grouped.toList.map { case ((isStream, in), (schema, split, opts, loc)) => 
        Source(isStream, schema, in, split, Adaptor("ORDERBOOK", opts), loc)
      } ::: others        
    }
    val fixed = fixOrderbook(sources)
    val s = fixed.filter{!_.isStream}.map(emitSourceDefinition).mkString("\n") + "\n" +
            fixed.filter{_.isStream}.map(emitSourceDefinition).mkString("\n")

    stringIf(s.nonEmpty, "/* Specifying data sources */\n" + s)
  }

  // --------------  

  private var unionDepth = 0
  
  // extract cond and then branch of "if (c) t else 0"
  private def extractBooleanExp(s: String): Option[(String, String)] =
    if (!s.startsWith("(/*if */(")) None
    else {
      val posInit = "(/*if */(".length
      var pos = posInit
      var nestingLvl = 1
      while (nestingLvl > 0) {
        if (s(pos) == '(') nestingLvl += 1
        else if (s(pos)==')') nestingLvl -= 1
        pos += 1
      }
      Some(s.substring(posInit, pos - 1), s.substring(pos + " ? ".length, s.lastIndexOf(":") - 1))
    }

  private def addToTempVar(name: String, keys: List[(String, Type)], vs: String, vsTp: Type) = 
    if (keys.isEmpty) {
      extractBooleanExp(vs) match {
        case Some((c, t)) =>
          "(/*if */(" + c + ") ? " + name + " += " + t + " : " + zeroOfType(vsTp) + ");\n"
        case _ =>
          name + " += " + vs + ";\n"
      }
    }
    else {
      val localEntry = fresh("st")
      val (ks, ksTp) = keys.unzip
      tempEntryTypes += ((ksTp, vsTp))
      localEntries += ((localEntry, tempEntryTypeName(ksTp, vsTp)))

      extractBooleanExp(vs) match {
        case Some((c, t)) =>
          s"(/*if */(" + c + ") ? " + name + ".add(" + localEntry + ".modify(" + ks.map(rn).mkString(", ") + "), " + t + ") : (void)0);\n"
        case _ =>
          name + ".add(" + localEntry + ".modify(" + ks.map(rn).mkString(", ") + "), " + vs + ");\n"
      }
    }

  private def applyFunc(co: String => String, fn1: String, tp: Type, as1: List[Expr]) = {
    val (as, fn) = fn1 match {
      case "regexp_match" if ENABLE_REGEXP_PARTIAL_EVAL &&
                             as1.head.isInstanceOf[Const] &&
                             !as1.tail.head.isInstanceOf[Const] =>
        val regex = as1.head.asInstanceOf[Const].v
        val preg0 = regexpCacheMap.getOrElseUpdate(regex, fresh("preg"))
        (as1.tail, "preg_match(" + preg0 + ",")
      case "date_part" => as1.head.asInstanceOf[Const].v.toLowerCase match {
          case "year"  => (as1.tail, "date_year" + "(")
          case "month" => (as1.tail, "date_month" + "(")
          case "day"   => (as1.tail, "date_day" + "(")
          case p       => throw new Exception("Invalid date part: " + p)
        }
      case _ => (as1, fn1 + "(")
    }
    // hoist constants resulting from function application
    if (as.forall(_.isInstanceOf[Const])) {
      co(hoistedConsts.getOrElseUpdate(Apply(fn1, tp, as1), fresh("c"))) 
    }
    else {
      var c = co
      as.zipWithIndex.reverse.foreach { case (a, i) => 
        val c0 = c
        c = (p: String) => cpsExpr(a, (v: String) => 
          c0(p + stringIf(i > 0, ", ") + v + stringIf(i == as.size - 1, ")"))) 
      }
      c("U" + fn) 
    }
  }  

  private def cmpFunc(tp: Type, op: OpCmp, arg1: String, arg2: String, withIfThenElse: Boolean = true) = 
    if(withIfThenElse)
      "(/*if */(" + arg1 + " " + cmpToString(op) + " " + arg2 + ")" + " ? 1 : 0)"
    else
      arg1 + " " + cmpToString(op) + " " + arg2


  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  // override 
  private def cpsExpr(ex: Expr, co: String => String = (v: String) => v, am: Option[List[(String, Type)]] = None): String = ex match {
    case Ref(n) => co(rn(n))

    case Const(tp, v) => tp match {
      case TypeLong => co(v + "L")
      case TypeFloat => co(v + "f")
      case TypeChar => co("'" + v + "'")
      case TypeString => cpsExpr(Apply("StringType", TypeString, List(ex)), co)
      case _ => co(v)
    }

    case Exists(e) => 
      cpsExpr(e, (v: String) => co(cmpFunc(TypeLong, OpNe, v, zeroOfType(ex.tp))))

    case Cmp(l, r, op) =>
      co(cpsExpr(l, (ll: String) => cpsExpr(r, (rr: String) => cmpFunc(l.tp, op, ll, rr))))

    case CmpOrList(l, r) =>
      co(cpsExpr(l, (ll: String) =>
        "(/*if */((" +
        r.map(x => cpsExpr(x, (rr: String) => "(" + ll + " == " + rr + ")"))
         .mkString(" || ") +
        ")) ? 1 : 0)"
      ))

    case Apply(fn, tp, as) => applyFunc(co, fn, tp, as)

    case MapRef(mapName, tp, ks, isTemp) =>
      val (ko, ki) = ks.zipWithIndex.partition { case((n, _), _) => ctx.contains(n) }
      val mapType = mapName + "_map"
      val mapEntryType = mapName + "_entry"
      
      if (ks.isEmpty) { // variable
        if (ctx contains mapName) co(rn(mapName)) else co(mapName)
      } 
      else if (ki.isEmpty) {
        if (!cgOpts.useOldRuntimeLibrary && deltaRelationNames.contains(mapName)) {
          sys.error("Delta relation requires primary index. Turn on old runtime library (-xruntime).")
        }
        val localEntry = fresh("se")
        localEntries += ((localEntry, mapEntryType))
        val argList = (ks map (x => rn(x._1))).mkString(", ")
        co(s"${mapName}.getValueOrDefault(${localEntry}.modify(${argList}))") // all keys are bound
      } 
      else {
        val (v0, e0) = (fresh("v"), fresh("e"))

        ctx.add(ks.filter(x => !ctx.contains(x._1)).map(x => (x._1, (x._2, x._1))).toMap)

        if (!isTemp) { // slice or foreach
          val body = 
            if (!cgOpts.useOldRuntimeLibrary && deltaRelationNames.contains(mapName)) {
              ki.map { case ((k, ktp), i) => 
                s"const ${refTypeToString(ktp)} ${rn(k)} = get<${i}>(${e0}.first.content);\n"
              }.mkString + 
              s"const ${refTypeToString(tp)} ${v0} = ${e0}.second;\n" +
              co(v0)              
            }
            else {
              ki.map { case ((k, ktp), i) =>
                s"const ${refTypeToString(ktp)} ${rn(k)} = ${e0}->${mapDefs(mapName).keys(i)._1};\n"
              }.mkString +
              s"const ${refTypeToString(tp)} ${v0} = ${e0}->${VALUE_NAME};\n" +
              co(v0)
            }

          if (ko.nonEmpty) { //slice
            if (!cgOpts.useOldRuntimeLibrary && deltaRelationNames.contains(mapName)) {
              sys.error("Delta relation requires secondary indices. Turn on old runtime library (-xruntime).")
            }

            val is = ko.map(_._2)
            val idxIndex = registerSecondaryIndex(mapName, is) + 1 //+1 because index 0 is the unique index
            val localEntry = fresh("se")
            localEntries += ((localEntry, mapEntryType))
            val sKeys = ko.map(x => rn(x._1._1)).mkString(", ")
            val n0 = fresh("n")

            s"""|{ //slice
                |  const LinkedNode* ${n0} = ${mapName}.slice(${localEntry}.modify${getIndexId(mapName,is)}(${sKeys}), ${idxIndex - 1});
                |  ${mapEntryType}* ${e0};
                |  while (${n0}) {
                |    ${e0} = reinterpret_cast<${mapEntryType}*>(${n0}->obj);
                |${ind(body, 2)}
                |    ${n0} = ${n0}->next;
                |  }
                |}
                |""".stripMargin
          } 
          else { //foreach
            if (!cgOpts.useOldRuntimeLibrary && deltaRelationNames.contains(mapName)) {
              s"""|{ //foreach
                  |  for (auto& ${e0} : batch) {  
                  |${ind(body, 2)}
                  |  }
                  |}
                  |""".stripMargin
            }
            else {
              s"""|{ //foreach
                  |  ${mapEntryType}* ${e0} = ${mapName}.head;
                  |  while (${e0}) {
                  |${ind(body, 2)}
                  |    ${e0} = ${e0}->nxt;
                  |  }
                  |}
                  |""".stripMargin
            }
          }
        } 
        else { // only foreach for Temp map
          val localVars = 
            ki.map { case ((k, tp), i) => 
              s"const ${refTypeToString(tp)} ${rn(k)} = ${e0}->_${i + 1};"
            }.mkString("\n") 

          s"""|{ // temp foreach
              |  ${tempEntryTypeName(ks.map(_._2), tp)}* ${e0} = ${mapName}.head;
              |  while(${e0}) {
              |${ind(localVars, 2)} 
              |    const ${refTypeToString(tp)} ${v0} = ${e0}->${VALUE_NAME}; 
              |
              |${ind(co(v0), 2)}
              |
              |    ${e0} = ${e0}->nxt;
              |  }
              |}
              |""".stripMargin
        }
      }

    // "1" is the neutral element for multiplication, and chaining is done with multiplication
    case Lift(n, e) =>
      // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) {
        cpsExpr(e, (v: String) => co(cmpFunc(TypeLong, OpEq, rn(n), v)))
      }
      else e match {
        case Ref(n2) => 
          ctx.add(n, (e.tp, rn(n2)))
          co("1")    // de-aliasing         
        // This renaming is required
        case _ =>
          ctx.add(n, (e.tp, fresh("l")))
          cpsExpr(e, (v: String) => typeToString(e.tp) + " " + rn(n) + " = " + v + ";\n" + co("1"))
      }

    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1), (er,ctx1) -> (vr,ctx2) ) 
    //    ==>
    //   (v = vl * vr, ctx2)
    case Mul(el, er) =>
      def vx(vl: String, vr: String) = 
        if (vl == "1") vr else if (vr == "1") vl else "(" + vl + " * " + vr + ")"

      // Enforce aggregation if er contains MapRefs in order to reduce
      // the number of (potentially) expensive subsequent er's operations
      val target = {
        def canLeftAggregate = el match {
          case AggSum(_, _) | Add(_, _) => true
          case _ => false
        }
        def isLeftSingleton =
          el.ovars.filter { case (n, t) => !ctx.contains(n) }.isEmpty
        def isRightExpensive =
          er.collect { case m: MapRef => List(m) }.exists(_.keys.nonEmpty)

        if (am.nonEmpty && canLeftAggregate && !isLeftSingleton && isRightExpensive) None else am
      }

      cpsExpr(el, (vl: String) => {
          var ifcond = ""
          val body = cpsExpr(er, (vr: String) => {
            (extractBooleanExp(vl), extractBooleanExp(vr)) match {
              case (Some((cl,tl)), Some((cr,tr))) =>
                if (unionDepth == 0) { ifcond = cl;  co("(/*if */(" + cr + ") ? " + vx(tl, tr) + " : " + zeroOfType(ex.tp) + ")") }
                else co("(/*if */(" + cl + " && " + cr + ") ? " + vx(tl, tr) + " : " + zeroOfType(ex.tp) + ")")

              case (Some((cl,tl)), None) =>
                if (unionDepth == 0) { ifcond = cl; co(vx(tl, vr)) }
                else co("(/*if */(" + cl + ") ? " + vx(tl, vr) + " : " + zeroOfType(ex.tp) + ")")

              case (None, Some((cr,tr))) =>
                co("(/*if */(" + cr + ") ? " + vx(vl, tr) + " : " + zeroOfType(ex.tp) + ")")

              case (None, None) => co(vx(vl, vr))
            }
          }, target)
          
          if (ifcond.isEmpty) body else body match {
            case rIfBranch(c, b) =>
              "if ((" + ifcond + ") && " + c + ") {\n" + b + "\n}\n"
            case _ =>
              "if ((" + ifcond + ")) {\n" + ind(body) + "\n}\n"
          }
        }, target)

    // Add(el,er)
    // ==
    //   Add( (el,ctx0) -> (vl,ctx1) , (er,ctx0) -> (vr,ctx2) ) 
    //         <-------- L -------->    <-------- R -------->
    //    (add - if there's no free variable) ==>
    //   (v = vl + vr , ctx0)
    //    (union - if there are some free variables) ==>
    //   T = Map[....]
    //   foreach vl in L, T += vl
    //   foreach vr in R, T += vr
    //   foreach t in T, co(t) 
    case a @ Add(el, er) =>
      val fks = a.ovars.filter { case (n, t) => !ctx.contains(n) }
      if (fks.isEmpty) {
        val cur = ctx.save
        unionDepth += 1
        cpsExpr(el, (vl: String) => {
          ctx.load(cur)
          cpsExpr(er, (vr: String) => {
            ctx.load(cur)
            unionDepth -= 1
            co(s"(${vl} + ${vr})")
          })
        })
      }
      else am match {
        case Some(t) if t.toSet.subsetOf(fks.toSet) =>
          val cur = ctx.save
          val s1 = cpsExpr(el, co, am)
          ctx.load(cur)
          val s2 = cpsExpr(er, co, am)
          ctx.load(cur)
          s1 + s2
        case _ =>
          val tmp = fresh("sum")
          val cur = ctx.save
          val s1 = cpsExpr(el, (v: String) => addToTempVar(tmp, fks, v, a.tp), Some(fks))
          ctx.load(cur)
          val s2 = cpsExpr(er, (v: String) => addToTempVar(tmp, fks, v, a.tp), Some(fks))
          ctx.load(cur)
          emitInitTempVar(tmp, a.tp, fks) + s1 + s2 + cpsExpr(MapRef(tmp, a.tp, fks, true), co)
      }

    case a @ AggSum(ks, e) =>
      val fks = ks.filter { case(n, t) => !ctx.contains(n) }
      am match {
        case Some(t) if t.toSet.subsetOf(fks.toSet) =>
          cpsExpr(e, co, am)
        case _ =>
          val cur = ctx.save
          val tmp = fresh("agg")
          val s1 = cpsExpr(e, (v: String) => addToTempVar(tmp, fks, v, a.tp), Some(fks))
          ctx.load(cur)
          val s2 = if (fks.isEmpty) co(tmp) 
                   else cpsExpr(MapRef(tmp, e.tp, fks, true), co)
          emitInitTempVar(tmp, a.tp, fks) + s1 + s2
      }

    case Repartition(ks, e) => cpsExpr(e, (v: String) => co(v))
    
    case Gather(e) => cpsExpr(e, (v: String) => co(v))
  
    case _ => sys.error("Don't know how to generate " + ex)
  }

  def apply(s0: System): String = {
    implicit val s0_ = s0

    freshClear()

    mapDefs = s0.maps.map { m => m.name -> m }.toMap

    deltaRelationNames = s0.triggers.flatMap(_.event match {
      case EventBatchUpdate(s) => List(delta(s.name))
      case _ => Nil
    }).toSet

    isBatchModeActive = deltaRelationNames.nonEmpty

    isExpressiveTLQSEnabled = s0.queries.exists { q => 
      q.expr match { 
        case MapRef(n, _, _, _) => n != q.name
        case _ => true
      }
    }

    prepareCodegen(s0)
 
    val sIVMStructure = emitIVMStructure(s0)
    
    val sTLQStructure = emitTLQStructure(s0)

    val sIncludeHeaders = emitIncludeHeaders

    val sRelationTypeDirectives = ""
      // s0.sources.map { s => 
      //   if (s.isStream)
      //     s"#define RELATION_${s.schema.name.toUpperCase}_DYNAMIC" 
      //   else 
      //     s"#define RELATION_${s.schema.name.toUpperCase}_STATIC"
      // }.mkString("\n")

    val sIncludeTypeDefs =
      s0.typeDefs.map(_.file.path).distinct
                 .map(s => "#include \"" + s + "\"").mkString("\n") + "\n"

    val sUsingNamespace =
      if (!cgOpts.useOldRuntimeLibrary) 
        s"""|using namespace standard_functions;
            |using namespace hashing;
            |using namespace serialization;""".stripMargin
      else
        s"""|using namespace standard_functions;""".stripMargin

    // Generating the entire file
    s"""|${sIncludeHeaders}
        |${sIncludeTypeDefs}
        |${sRelationTypeDirectives}
        |
        |using namespace std;
        |
        |namespace dbtoaster {
        |
        |${ind(sUsingNamespace)}
        |
        |${ind(emitMapTypes(s0))}
        |
        |${ind(emitTempEntryTypes)}
        |
        |${ind(sTLQStructure)}
        |
        |${ind(sIVMStructure)}
        |
        |${ind(emitMainClass(s0))}
        |
        |}""".stripMargin    
  }

  protected def prepareCodegen(s0: System): Unit = {}

  protected def emitIncludeHeaders =
    stringIf(!cgOpts.useOldRuntimeLibrary,
      s"""|#include <sys/time.h>
          |#include <cstring>
          |#include <vector>
          |#include <tuple>
          |#include "types.hpp"
          |#include "hash.hpp"
          |#include "multi_map.hpp"
          |#include "standard_functions.hpp"
          |#include "event.hpp"
          |#include "source.hpp"
          |""".stripMargin,
      s"""|#include "program_base.hpp"
          |#include "types.hpp"
          |#include "hash.hpp"
          |#include "mmap/mmap.hpp"
          |""".stripMargin)
}
