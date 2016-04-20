package ddbt.codegen.prettyprinter

import java.io.PrintWriter

import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.types.{NothingType, Lambda1Type, AnyType, PardisType}
import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ch.epfl.data.sc.pardis.utils.document._
import ch.epfl.data.sc.pardis.ir._
import ddbt.lib.store._
import ddbt.lib.store.deep.StoreIRs._
import ddbt.lib.store.deep.StoreDSL
import pardis.deep.scalalib.ScalaPredefOps
import transformer._

import scala.reflect.io.File


class StoreScalaCodeGenerator(val IR: StoreDSL) extends ScalaCodeGenerator with ASTCodeGenerator[StoreDSL] {

  import IR._


  case class EntryIndex(val entry: SEntry, val idx: Index) {

    //      override def equals(obj: scala.Any): Boolean = obj match {
    //        case EntryIndex(e, i) => contains(e, i)
    //        case _ => false
    //      }
    //
    //      def contains(e: Entry, i: Index) = entry.name == e.name && idx.cols == i.cols && idx.f == null && i.f == null
    //
    //      val name = if (entry.name == "GenericEntry") {
    //        if (idx.f == null)
    //          "GenericOps"
    //        else
    //          "GenericCmp"
    //      }
    //      else
    //        s"${entry.name}_Idx$i"
    //
    def hashFn(c: Seq[Int]) = {
      implicit val tp = entry.tp
    }

    val instance = if (entry.name == "GenericEntry") {
      if (idx.f == null)
        doc"GenericOps(List(${idx.cols.mkString(", ")}))"
      else
        doc"GenericCmp(${nodeToDocument(idx.f)})"
    }
    else {
      val cmpfn = if (idx.f == null) {
        if (idx.cols == Nil) {
          val cols = (1 until entry.sch.size)
          doc"(e1: ${entry.name}, e2: ${entry.name}) => if(${cols.map(c => doc"(e1._$c == ${nullValue(entry.sch(c - 1))} || e2._$c == ${nullValue(entry.sch(c - 1))} || e1._$c == e2._$c)").mkString(" && ")}) 0 else 1"
        }
        else
          doc"(e1: ${entry.name}, e2: ${entry.name}) => if(${idx.cols.map(c => s"e1._$c == e2._$c").mkString(" && ")}) 0 else 1"
      } else {
        implicit val tp = entry.tp
        val e1 = fresh[SEntry]
        val e2 = fresh[SEntry]

        val compareBlock = reifyBlock {
          implicit val tpR = idx.f.typeS.asInstanceOf[TypeRep[Any]]
          val r1 = idx.f.asInstanceOf[PardisLambda[SEntry, Any]].f(e1)
          val r2 = idx.f.asInstanceOf[PardisLambda[SEntry, Any]].f(e2)
          __ifThenElse(Equal(r1, r2), unit(0), __ifThenElse(ordering_gt(r1, r2), unit(1), unit(-1)))
        }

        doc"($e1:${entry.name}, $e2: ${entry.name}) => ${blockToDocument(compareBlock)}"
      }
      val hashfn =
        doc"(e: ${entry.name}) => {" :\\:
          doc"var hash:Int = 0xcafebabe" :\\:
          doc"var mix:Int = 0" :\\:
          doc"${
            idx.cols.map(c =>
              doc"mix = e._$c.hashCode * 0xcc9e2d51" :\\:
                doc"mix = (mix << 15) | (mix >>> -15)" :\\:
                doc"mix *= 0x1b873593" :\\:
                doc"mix ^= hash" :\\:
                doc"mix = (mix << 13) | (mix >>> -13)" :\\:
                doc"hash = mix * 5 + 0xe6546b64").mkDocument("\n")
          }" :\\:
          doc"hash ^= 2" :\\:
          doc"hash ^= hash >>> 16" :\\:
          doc"hash *= 0x85ebca6b" :\\:
          doc"hash ^= hash >>> 13" :\\:
          doc"hash *= 0xc2b2ae35" :\\:
          doc"hash ^= hash >>> 16" :\\:
          doc"hash" :\\:
          doc"}"

      doc"SplEntryOps($hashfn, $cmpfn)"
    }

    //      override def toString = if (entry.name == "GenericEntry") ""
    //      else {
    //
    //
    //        s"""
    //           |object $name extends EntryIdx[${entry.name}] {
    //           |   $cmpfn
    //           |   override def hash(e: ${entry.name}) = {
    //           |      var hash:Int = 0xcafebabe
    //           |      var mix:Int = 0
    //           |${
    //          idx.cols.map(c =>
    //            s"""|      mix = e._$c.hashCode * 0xcc9e2d51
    //                |      mix = (mix << 15) | (mix >>> -15)
    //                |      mix *= 0x1b873593
    //                |      mix ^= hash
    //                |      mix = (mix << 13) | (mix >>> -13)
    //                |      hash = mix * 5 + 0xe6546b64
    //                       """.stripMargin).mkString("\n")
    //        }
    //           |      hash ^= 2
    //           |      hash ^= hash >>> 16
    //           |      hash *= 0x85ebca6b
    //           |      hash ^= hash >>> 13
    //           |      hash *= 0xc2b2ae35
    //           |      hash ^= hash >>> 16
    //           |      hash
    //           |      }
    //           |}
    //           |
    //                  """.stripMargin
    //      }
    //
    //      override def hashCode(): Int = {
    //        val state = Seq(entry.name, idx.cols)
    //        state.map(_.hashCode()).foldLeft(0)((a, b) => 31 * a + b)
    //      }
  }

  //  object EntryIndex {
  //    val entryindexes = collection.mutable.HashSet[EntryIndex]()
  //
  //    def apply(entry: Entry, idx: Index) = {
  //      val EI = new EntryIndex(entry, idx, entryindexes.size)
  //      if (entryindexes.add(EI)) EI else entryindexes.find(ei => EI.equals(ei)).asInstanceOf[Some[EntryIndex]].get
  //    }
  //
  //    def find(entry: Entry, idx: Index) = entryindexes.find(_.contains(entry, idx))
  //
  //    def unapply(ei: EntryIndex): Option[(Entry, Index)] = Some(ei.entry, ei.idx)
  //  }


  case class BlockWithSymbols(val body: Block[Any], val syms: List[Sym[Any]]) {}


  def emitSource4[T1, T2, T3, T4, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val body = reifyBlock(f(s1, s2, s3, s4))
    (className, List(s1, s2, s3, s4), body)
  }


  def emitSource6[T1, T2, T3, T4, T5, T6, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6))
    (className, List(s1, s2, s3, s4, s5, s6), body)
  }

  def emitSource8[T1, T2, T3, T4, T5, T6, T7, T8, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8))
    (className, List(s1, s2, s3, s4, s5, s6, s7, s8), body)
  }

  def emitSource11[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val s9 = fresh[T9]
    val s10 = fresh[T10]
    val s11 = fresh[T11]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11))
    (className, List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11), body)

  }

  def emitSource16[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11], Rep[T12], Rep[T13], Rep[T14], Rep[T15], Rep[T16]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], e12: TypeRep[T12], e13: TypeRep[T13], e14: TypeRep[T14], e15: TypeRep[T15], e16: TypeRep[T16], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val s9 = fresh[T9]
    val s10 = fresh[T10]
    val s11 = fresh[T11]
    val s12 = fresh[T12]
    val s13 = fresh[T13]
    val s14 = fresh[T14]
    val s15 = fresh[T15]
    val s16 = fresh[T16]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16))
    (className, List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16), body)
  }

  //  def emitSource(global: List[Sym[_]], stream: PrintWriter) = {
  //    allBlocks.foreach {
  //      case (className, BlockWithSymbols(body, args)) =>
  //        val genCode = "class " + className + "(" + global.map(m => m.name + m.id + ":" + tpeToDocument(m.tp)).mkString(", ") + ") extends ((" + args.map(s => tpeToDocument(s.tp)).mkString(", ") + ") => " + tpeToDocument(body.typeT) + ") {\n" +
  //          "def apply(" + args.map(s => s + ": " + tpeToDocument(s.tp)).mkString(", ") + ") = "
  //        val cgDoc = blockToDocument(body)
  //        stream.println(genCode + cgDoc + "\n}")
  //    }
  //  }

  //TODO: SBJ: Bug in ScalaCodeGen
  override def blockToDocument(block: Block[_]): Document = {
    Document.text("{") :: Document.nest(NEST_COUNT,
      mergeDocs(block.stmts.map(s => stmtToDocument(s)), true) :\\: expToDocument(block.res)) :/: "}"
  }

  def blockToDocumentNoBraces(block: Block[_]): Document = {
      mergeDocs(block.stmts.map(s => stmtToDocument(s)), true) :\\: expToDocument(block.res)
  }


  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if (sym.name != "x") {
      Document.text(sym.name)
    } else {
      super.symToDocument(sym)
    }
  }

  val SEntryDefToDocument = new StructDefToDocument {
    override def signature(structDef: PardisStructDef[_]): Document = {
      val name = structDef.tag.typeName
      val count = name.split("_")(1).length

      signatureMod(structDef) :: " class " :: name :: "(" :: fieldsDef(structDef) :: ")" :: " extends " :: s"Entry($count)"
    }

    override def body(structDef: PardisStructDef[_]): Document = doc" {def copy = ${structDef.tag.typeName}(${(1 to structDef.fields.size).map("_"+_).mkString(", ")}) }"
  }

  override def getStruct(structDef: PardisStructDef[_]): Document = SEntryDefToDocument(structDef)

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
//    case Statement(sym, StoreNew2()) => generateNewStore(sym, None)
    case Statement(sym, StringDiff(str1, str2)) => doc"val $sym = $str1.compareToIgnoreCase($str2)"
    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"val $sym = $self.format(${args.map(expToDocument).mkDocument(",")})"
    case Statement(sym, StoreGet(self, idx, key, _)) => doc"val $sym = $self.get($idx, $key)"
    case Statement(sym, StoreIndex(self, idx, tp, uniq, other)) => doc"val $sym = $self.index($idx, ${tp.asInstanceOf[Constant[String]].underlying}, $uniq, $other)"
    case _ => super.stmtToDocument(stmt)
  }

//
  def generateNewStore(c: Sym[_], mname: Option[String]): String = {
    //    val sch = schema getOrElse(c, List[TypeRep[_]]())
    //    val entry = Entry(sch)
    val indexes = c.attributes.get[Indexes](IndexesFlag).get.indexes
    val entry = storeType(c)
    System.err.println(s"Store type for $c is $entry")
    val entryidxes = indexes.map(i => EntryIndex(entry, i))
    def generateNew: String = s"new Store[${entry.name}](" + indexes.size + s", Array[EntryIdx[${entry.name}]](${entryidxes.map(_.instance).mkString(", ")}))"
    val symbolName = c.name + c.id
    val mapAlias = mname match {
      case Some(mapName) =>
        s"val $mapName = $symbolName"
      case None =>
        s""
    }
    s"\nval $symbolName = $generateNew \n" +
      indexes.map(i => symbolName + s".index($i)").mkString("\n") +
      s"\n$mapAlias"
  }
}
