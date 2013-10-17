package ddbt.codegen
import ddbt.ast._
import ddbt.lib.{K3Temp,K3Var}

import scala.reflect.SourceContext
import toasterbooster.lifters._
import ddbt.Utils.ind

/**
 * This class has the responsibility for code generation
 * of different k3 operations, for inlining targets.
 *
 * The operations implemented here will be used by both LMS and LMSGen.
 */
object K3MapCommons {
  final val InliningLevelMax = 10
  final val InliningLevelNone = 0

  var InliningLevel = InliningLevelNone

  /**
   * The default initial capacity - MUST be a power of two.
   */
  final val DEFAULT_INITIAL_CAPACITY: Int = 16
  final val DEFAULT_INITIAL_CAPACITY_INDEX: Int = 16
  final val DEFAULT_INITIAL_CAPACITY_INDEX_INNER: Int = 16
  /**
   * The maximum capacity, used if a higher value is implicitly specified
   * by either of the constructors with arguments.
   * MUST be a power of two <= 1<<30.
   */
  final val MAXIMUM_CAPACITY: Int = 1 << 30
  /**
   * The load factor used when none specified in constructor.
   */
  final val DEFAULT_LOAD_FACTOR: Float = 0.75f
  /**
   * The load factor used when none specified in constructor.
   */
  final val INITIAL_THRESHOLD: Int = (DEFAULT_INITIAL_CAPACITY * DEFAULT_LOAD_FACTOR).asInstanceOf[Int]
  final val INITIAL_THRESHOLD_INDEX: Int = (DEFAULT_INITIAL_CAPACITY_INDEX * DEFAULT_LOAD_FACTOR).asInstanceOf[Int]
  final val INITIAL_THRESHOLD_INDEX_INNER: Int = (DEFAULT_INITIAL_CAPACITY_INDEX_INNER * DEFAULT_LOAD_FACTOR).asInstanceOf[Int]

  var entryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[List[Int]])]()
  var indexEntryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[List[Int]],List[Int])]()

  /**
   * Generates the class name for HashMap entries, given
   * value type, key type, and list of indices used for 
   * indexing data inside the map
   */
  def entryClassName(value:Type, key:List[Type], indexList: List[List[Int]] = List[List[Int]]()): String = "EntryK"+key.map(x => shortName(x)).mkString+"_V"+shortName(value)+"_X"+indexList.map(x => x.mkString("_")).mkString("N")

  /**
   * Generates the class name for Index HashMap entries, given
   * value type, key type, and list of indices used for 
   * indexing data inside the index target, and current index
   * information
   */
  def indexEntryClassName(value:Type, key:List[Type], indexList: List[List[Int]], indexLoc: List[Int]): String = indexEntryClassName(entryClassName(value,key,indexList),indexLoc)

  /**
   * Generates the class name for Index HashMap entries, given
   * target HashMap entry class name and current index
   * information
   */
  def indexEntryClassName(entryClsName: String, indexLoc: List[Int]): String = "Idx"+entryClsName+indexNamePostfix(indexLoc)

  /**
   * Generates the index map name, given the index target map
   * name and the index information
   */
  def indexMapName(map: String, indexLoc: List[Int]): String = map+indexNamePostfix(indexLoc)

  /**
   * Generates the postfix of an index map name, given index
   * information
   */
  def indexNamePostfix(indexLoc: List[Int]): String = "_I"+indexLoc.map(_+1).mkString("_")

  /**
   * A given M3 program contains several maps and index maps.
   * This function generates specialized entry classes for all
   * these maps.
   */
  def generateAllEntryClasses = generateEntryClasses + "\n" + generateIndexEntryClasses

  /**
   * Generates specialized HashMap entry classes for maps
   * used in DBToaster program.
   */
  def generateEntryClasses = entryClasses.map { case (name, (value, key, idxList)) =>
    "  class " + name + "(val hs:Int, " +
      key.zipWithIndex.map{case (ktp, i) => "val _"+(i+1)+":"+ktp.toScala+", "}.mkString +
      "var v:" + value.toScala + ", var next:" + name + "=null) extends IEntry {\n" +
      idxList.map{ x =>
        val idxMapName = indexEntryClassName(name, x) 
        "    var ptr"+idxMapName+":"+idxMapName+" = null\n" +
        "    var ptr"+idxMapName+"_idx:Int = -1\n"
      }.mkString +
      "    def hashVal: Int = hs\n" +
      "    def nextEntry: IEntry = next\n" +
      "    def setNextEntry(n:IEntry): Unit = next = n.asInstanceOf["+name+"]\n" +
    //"    val hs: Int = " + hashFunction(key.zipWithIndex.map{case (k,i) => "_"+(i+1)}, "    ") + "\n" +
    //"    var next:" + name + " = null\n" +
    "  }\n"
  }.mkString

  /**
   * Generates specialized Index HashMap entry classes for index maps
   * used in DBToaster program.
   */
  def generateIndexEntryClasses = indexEntryClasses.map { case (name, (value, key, indexList, indexLoc)) =>
    val entryCls = entryClassName(value, key, indexList)
    "  class " + name + " (val hs:Int, " +
      indexLoc.map(i => "val _"+(i+1)+":"+key(i).toScala).mkString(", ") + ", var next:" + name + "=null) extends IEntry {\n" +
    "    var v: scala.collection.mutable.ArrayBuffer["+entryCls+"] = new scala.collection.mutable.ArrayBuffer["+entryCls+"]("+DEFAULT_INITIAL_CAPACITY_INDEX_INNER+");\n" +
    "    def hashVal: Int = hs\n" +
    "    def nextEntry: IEntry = next\n" +
    "    def setNextEntry(n:IEntry): Unit = next = n.asInstanceOf["+name+"]\n" +
    //"    var v__sz: Int = 0;\n" +
    //"    var v__ts: Int = "+INITIAL_THRESHOLD_INDEX_INNER+";\n" +
    //"    val hs: Int = " + hashFunction(indexLoc.map(i => "_"+(i+1)), "    ") + "\n" +
    //"    var next:" + name + " = null\n" +
    "  }\n"
  }.mkString

  /*
   * Implementation of MurmurHash3
   * based on scala.util.hashing.MurmurHash3
   * for Products
   * 
   * https://github.com/scala/scala/blob/v2.10.2/src/library/scala/util/hashing/MurmurHash3.scala
   */
  def hashFunction(keyNames: List[String], prefix: String = "") = {
    //TODO: Is it better to do MurmurHash3 for single values?
    if(keyNames.size == 1) {
      val i = keyNames(0)
      "{\n"+
      prefix + "  var hash:Int = "+i+".##\n" +
      javaHashMapHashFunc("hash", prefix) +
      prefix + "}"
    } else {
      val tupleHashSeed = "0xcafebabe"
      def rotl(i: String, distance: String) = "("+i+" << "+distance+") | ("+i+" >>> -"+distance+")"
      var counter:Int = 0
      "{\n"+
      prefix + "  var hash:Int = "+tupleHashSeed+"\n" +
      keyNames.map { i =>
        counter+=1
        //TODO: Check whether hashCode works better compared to ##
        //      as we know that everything is type-checked
        prefix + (if(counter == 1) "  var mix:Int" else "  mix") + " = "+i+".## * 0xcc9e2d51\n" +
        prefix + "  mix = " + rotl("mix", "15")+"\n" +
        prefix + "  mix *= 0x1b873593\n" +
        prefix + "  mix ^= hash\n" +
        prefix + "  mix = " + rotl("mix", "13")+"\n" +
        prefix + "  hash = mix * 5 + 0xe6546b64\n"
      }.mkString +
      prefix + "  hash ^= " + keyNames.size + "\n" +
      prefix + "  hash ^= hash >>> 16\n" +
      prefix + "  hash *= 0x85ebca6b\n" +
      prefix + "  hash ^= hash >>> 13\n" +
      prefix + "  hash *= 0xc2b2ae35\n" +
      prefix + "  hash ^= hash >>> 16\n" +
      javaHashMapHashFunc("hash", prefix) +
      prefix + "}"
    }
  }

  /**
   * Applies a supplemental hash function to a given hashCode, which
   * defends against poor quality hash functions.  This is critical
   * because HashMap uses power-of-two length hash tables, that
   * otherwise encounter collisions for hashCodes that do not differ
   * in lower bits. Note: Null keys always map to hash 0, thus index 0.
   */
  def javaHashMapHashFunc(hash: String, prefix: String) = {
    prefix + "  "+hash+" ^= ("+hash+" >>> 20) ^ ("+hash+" >>> 12)\n" +
    prefix + "  "+hash+" ^ ("+hash+" >>> 7) ^ ("+hash+" >>> 4)\n"
  }

  /**
   * Returns index for hash code h.
   */
  def indexForFunction(h: String, len: String) = h+" & ("+len+"-1)"

  /**
   * Returns short name for a given Type.
   *
   * The result of this function is currently used in generating
   * HashMap entry class names.
   */
  def shortName(tp: Type) = tp match {
    case TypeLong => "L"
    case TypeDouble => "D"
    case TypeString => "S"
    case TypeDate => "A"
  }

  /**
   * Returns the String zero value for a given Type
   */
  def zeroValue(v: Type) = v match {
    case TypeLong => "0L"
    case TypeDouble => "0.0"
    case TypeString => "\"\""
    case TypeDate => "new Date()"
  }

  /**
   * Returns the zero value for a given Type
   */
  def actualZeroValue(v: Type) = v match {
    case TypeLong => 0
    case TypeDouble => 0.0
    case TypeString => ""
    case TypeDate => new java.util.Date()
  }

  /**
   * Generates K3Var definition statement.
   *
   * @param name is the name of variable
   * @param value is the type of variable
   */
  def createK3VarDefinition(name: String, value:Type) = "var "+name+" = "+zeroValue(value)

  /**
   * Generates K3Map definition statements.
   * These maps will be created once for a DBToaster
   * program and will store the final results and 
   * intermediate results required between separate
   * trigger definitions.
   *
   * @param name is the name of map
   * @param value is the type of map element value
   * @param key is the types of map element key parts
   * @param indexList if the list of indices on the map
   */
  def createK3NamedMapDefinition(name: String, value:Type, key:List[Type], indexList: List[List[Int]]) = {
    val entryCls = entryClassName(value, key,indexList)
    entryClasses += (entryCls -> (value,key,indexList))

    "var "+name+": Array["+entryCls+"] = new Array["+entryCls+"]("+DEFAULT_INITIAL_CAPACITY+");\n" +
    "var "+name+"__sz: Int = 0;\n" +
    "var "+name+"__ts: Int = "+INITIAL_THRESHOLD+";\n" +
    (if (indexList.size>0) {
      indexList.map{ is => 
        val idxEntryCls = indexEntryClassName(value, key, indexList, is)
        indexEntryClasses += (idxEntryCls -> (value,key,indexList,is))

        "var "+indexMapName(name, is)+": Array["+idxEntryCls+"] = new Array["+idxEntryCls+"]("+DEFAULT_INITIAL_CAPACITY_INDEX+");\n" +
        "var "+indexMapName(name, is)+"__sz: Int = 0;\n" +
        "var "+indexMapName(name, is)+"__ts: Int = "+INITIAL_THRESHOLD_INDEX+";"
      }.mkString("\n")+"\n"
    } else "")
  }

  /**
   * Generates temporary K3Map definition statements.
   * These maps will be created inside triggers for
   * storing intermediate results.
   *
   * @param name is the name of map
   * @param value is the type of map element value
   * @param key is the types of map element key parts
   * @param indexList if the list of indices on the map
   */
  def createK3TempDefinition(name: String, value:Type, key:List[Type]) = {
    val entryCls = entryClassName(value, key,List[List[Int]]())
    entryClasses += (entryCls -> (value,key,List[List[Int]]()))

    "var "+name+": Array["+entryCls+"] = new Array["+entryCls+"]("+DEFAULT_INITIAL_CAPACITY+");\n" +
    "var "+name+"__sz: Int = 0;\n" +
    "var "+name+"__ts: Int = "+INITIAL_THRESHOLD+";"
  }

  /**
   * This method clears the accumulated static data
   * inside this object and should be called after
   * generating one DBToaster program.
   */
  def clear = {
    entryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[List[Int]])]()
    indexEntryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[List[Int]],List[Int])]()
  }

  /**
   * Generates HashMap ADD function
   *
   * @param isConstant is a flag which indicates whether
   *        the value to be added is a constant
   * @param isZero is a flag which indicates whether
   *        the value to be added is zero
   * @param prefixValue is a String containing val-def
   *        required to be available, before the value
   *        is used, in the same or a higher scope
   * @param prefixKey is a String containing val-def
   *        required to be available, before the key
   *        is used, in the same or a higher scope
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param key is the list of key parts types
   * @param value is the value type
   * @param keyIndicesInEntery which parts of key are
   *        are used 
   * @param indexList is the list of indices for this map
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   * @param valueName is the input value arg to be added
   */
  def genGenericAddNamedMap(isConstant: Boolean, isZero: Boolean, prefixValue: String, prefixKey: String, nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], keyNames:List[String], valueName:String) = {
    if(isZero) {
      "//K3ADDNAMED_CANCELLED"
    } else {
      "//K3ADDNAMED\n" +
      prefixValue +
      (if(isConstant) {
        genGenericSetTempMap("",prefixKey,nodeName,map,K3MapCommons.entryClassName(value, key, indexList),(0 until keyNames.size).toList,keyNames,valueName,false,"+=",indexList,indexList.map(K3MapCommons.indexEntryClassName(value,key,indexList,_)),true,zeroValue(value))
      } else {
        "if("+valueName+" != "+K3MapCommons.zeroValue(value)+") {\n" +
        ind(genGenericSetTempMap("",prefixKey,nodeName,map,K3MapCommons.entryClassName(value, key, indexList),(0 until keyNames.size).toList,keyNames,valueName,false,"+=",indexList,indexList.map(K3MapCommons.indexEntryClassName(value,key,indexList,_)),true,zeroValue(value)))+"\n" +
        "}"
      })
    }
  }

  /**
   * Generates HashMap SET function
   *
   * @param prefixValue is a String containing val-def
   *        required to be available, before the value
   *        is used, in the same or a higher scope
   * @param prefixKey is a String containing val-def
   *        required to be available, before the key
   *        is used, in the same or a higher scope
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param key is the list of key parts types
   * @param value is the value type
   * @param keyIndicesInEntery which parts of key are
   *        are used 
   * @param indexList is the list of indices for this map
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   * @param valueName is the input value arg to be added
   */
  def genGenericSetNamedMap(prefixValue: String, prefixKey: String, nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], keyNames:List[String], valueName:String, operation: String="") = {
    //sn = set named map
    "//K3SETNAMED\n" +
    prefixValue +
    "if("+valueName+" == "+K3MapCommons.zeroValue(value)+") {\n" +
    genGenericDelNamedMap(prefixKey,nodeName,map,key,value,indexList,(0 until keyNames.size).toList,keyNames)+ "\n" +
    "} else {\n" +
    ind(genGenericSetTempMap("",prefixKey,nodeName,map,K3MapCommons.entryClassName(value, key, indexList),(0 until keyNames.size).toList,keyNames,valueName,false,"=",indexList,indexList.map(K3MapCommons.indexEntryClassName(value,key,indexList,_))))+"\n" +
    "}"
  }

  /**
   * Generates Temporary HashMap SET function
   *
   * @param prefixValue is a String containing val-def
   *        required to be available, before the value
   *        is used, in the same or a higher scope
   * @param prefixKey is a String containing val-def
   *        required to be available, before the key
   *        is used, in the same or a higher scope
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param entryClsName is the name of HashMap entry class
   * @param keyIndicesInEntery which parts of key are
   *        are used as key parts of map entry
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   * @param valueName is the input value arg to be added
   */
  def genGenericSetTempMap(prefixValue: String, prefixKey: String, nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], keyNames:List[String], valueName:String,insideBlock: Boolean=true, operation: String="=", indexList: List[List[Int]] = List[List[Int]](), indexEntryClsName: List[String]=List[String](), fromNamedMap:Boolean = false, zeroValue: String = "") : String = {
    //st = set temp
    val hash = nodeName+"_sthash"
    val e = nodeName+"_ste"
    val found = nodeName+"_stfound"
    val result = nodeName+"_stresult"
    val i = nodeName+"_sti"
    val prev = nodeName+"_dprev"
    val next = nodeName+"_dnext"

    val content = prefixKey +
    prefixValue +
    "//K3SETTEMP\n" +
    "val "+hash+":Int = " + K3MapCommons.hashFunction(keyNames) + "\n" +
    "val "+i+":Int = "+K3MapCommons.indexForFunction(hash, map+".length")+"\n" +
    (if(fromNamedMap) {
      "var "+prev+":" + entryClsName + " = " + map + "(" + i + ")\n" +
      "var "+e+":" + entryClsName + " = " + prev + "\n"
    } else {
      "var "+e+":" + entryClsName + " = " + map + "(" + i + ")\n"
    }) +
    "var "+found+":Boolean = false\n" +
    "while(!"+found+" && "+e+" != null) {\n" +
    (if(fromNamedMap) {
      "  val "+next+":" + entryClsName + " = " + e + ".next\n"
    } else {
      ""
    }) +
    "  if("+e+".hs == "+hash+" && "+keyNames.zip(keyIndicesInEntery).map{case (x, i) => e+"._"+(i+1)+" == "+x}.mkString(" && ")+") {\n"+
    "    "+found+" = true\n"+
    "    "+e+".v "+operation+" "+valueName+"\n" +
    (if(fromNamedMap) {
      "    if("+e+".v == "+zeroValue + ") {\n" +
      indexList.map{ indexLoc =>
        val idxEntryCls = K3MapCommons.indexEntryClassName(entryClsName, indexLoc)
        val field = e+".ptr"+idxEntryCls
        "      "+field+".v.update("+field+"_idx, null)\n"
      }.mkString +
      "      "+ map + "__sz -= 1\n" +
      "      if("+prev+" == "+e+") "+map+"("+i+") = "+next+"\n" +
      "      else "+prev+".next = "+next+"\n" +
      "    }\n"
    } else {
      ""
    }) + 
    "  }\n" +
    (if(fromNamedMap) {
      "  "+prev+" = "+e+"\n" +
      "  "+e+" = "+next+"\n"
    } else {
      "  "+e+" = "+e+".next\n"
    }) +
    "}\n" +
    "if(!"+found+") {\n" +
    genAddEntryMap(nodeName,map,entryClsName,keyIndicesInEntery,keyNames,valueName,e,hash,i)+"\n"+
    ind(indexList.zipWithIndex.map{ case (idx, i) =>
      genSetIndexMap(K3MapCommons.indexMapName(nodeName,idx), K3MapCommons.indexMapName(map,idx), indexEntryClsName(i), idx, filterExprAtElementLoc(keyNames, idx) , e, false) + "\n"
    }.mkString) +
    "\n}"

    if(insideBlock) "; {\n"+ind(content)+"\n}" else content
  }

  /**
   * Generates HashMap ADD ENTRY function
   *
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param entryClsName is the name of HashMap entry class
   * @param keyIndicesInEntery which parts of key are
   *        are used as key parts of map entry
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   * @param valueName is the input value arg to be added
   *
   * Extra params from parent method:
   * @param e is the entry variable name
   * @param hash is the hash value of new element
   * @param bucketIndex is the table index of HashMap that
   *        new element should be inserted in it.
   */
  def genAddEntryMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], keyNames:List[String], valueName:String, e:String, hash: String, bucketIndex:String) = {
    val newCapacity = nodeName+"_nc"
    val tmp = e+"_atmp"

    "  val " + tmp + ":" + entryClsName + " = " + map + "(" + bucketIndex + ")\n" +
    "  " + e + " = new " + entryClsName + "("+hash+","+keyNames.mkString(",")+","+valueName+","+tmp+")\n" +
    "  " + map + "(" + bucketIndex + ") = "+e+"\n"+
    "  " + map + "__sz += 1\n" +
    "  if(" + map + "__sz-1 >= " + map + "__ts) {\n" +
    "    val "+newCapacity+" = 2 * "+map+".length\n" +
    "    "+map+" = __transferHashMap["+entryClsName+"]("+map+",new Array["+entryClsName+"]("+newCapacity+"))\n" +
    "    "+map+"__ts = (" + newCapacity + "*" + K3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
    "  }"
  }

  /**
   * Generates Index HashMap SET function
   *
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param entryClsName is the name of HashMap entry class
   * @param keyIndicesInEntery which parts of key are
   *        are used as key parts of map entry
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   * @param valueName is the input value arg to be added
   *
   * @param insideBlock indicates whether the generated code
   *        should be out inside a block or not
   */
  def genSetIndexMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], keyNames:List[String], valueName:String,insideBlock: Boolean=true) : String = {
    //st = set index
    val hash = nodeName+"_sithash"
    val e = nodeName+"_site"
    val found = nodeName+"_sitfound"
    val result = nodeName+"_sitresult"
    val i = nodeName+"_siti"
    val currentIndexPointerName = "ptr"+entryClsName

    val content = "//K3SETINDEX\n" +
    "val "+hash+":Int = " + K3MapCommons.hashFunction(keyNames) + "\n" +
    "val "+i+":Int = "+K3MapCommons.indexForFunction(hash, map+".length")+"\n" +
    "var "+e+":" + entryClsName + " = " + map + "(" + i + ")\n" +
    "var "+found+":Boolean = false\n" +
    "while(!"+found+" && "+e+" != null) {\n" +
    "  if("+e+".hs == "+hash+" && "+keyNames.zip(keyIndicesInEntery).map{case (x, i) => e+"._"+(i+1)+" == "+x}.mkString(" && ")+") {\n"+
    "    "+found+" = true\n"+
    "    "+valueName+"."+currentIndexPointerName+" = "+e+"\n"+
    "    "+valueName+"."+currentIndexPointerName+"_idx = "+e+".v.length\n"+
    "    "+e+".v += "+valueName+"\n" +
    "  }\n" +
    "  "+e+" = "+e+".next\n" +
    "}\n" +
    "if(!"+found+") {\n" +
    genAddEntryIndexMap(nodeName,map,entryClsName,keyNames,e,hash,i)+"\n"+
    "  "+valueName+"."+currentIndexPointerName+" = "+e+"\n"+
    "  "+valueName+"."+currentIndexPointerName+"_idx = "+e+".v.length\n"+
    "  "+e+".v += "+valueName+"\n" +
    "\n}"

    if(insideBlock) "{\n"+ind(content)+"\n}" else content
  }

  /**
   * Generates Index HashMap ADD ENTRY function
   *
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param entryClsName is the name of HashMap entry class
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   *
   * Extra params from parent method:
   * @param e is the entry variable name
   * @param hash is the hash value of new element
   * @param bucketIndex is the table index of HashMap that
   *        new element should be inserted in it.
   */
  def genAddEntryIndexMap(nodeName:String, map:String, entryClsName:String, keyNames:List[String], e:String, hash: String, bucketIndex:String) = {
    val newCapacity = nodeName+"_nic"
    val tmp = e+"_aitmp"

    "  val " + tmp + ":"+entryClsName+" = " + map + "(" + bucketIndex + ")\n" +
    "  " + e + " = new " + entryClsName + "("+hash+","+keyNames.mkString(",")+","+tmp+")\n" +
    "  " + map + "(" + bucketIndex + ") = "+e+"\n"+
    "  " + map + "__sz += 1\n" +
    "  if(" + map + "__sz-1 >= " + map + "__ts) {\n" +
    "    val "+newCapacity+" = 2 * "+map+".length\n" +
    "    "+map+" = __transferHashMap["+entryClsName+"]("+map+",new Array["+entryClsName+"]("+newCapacity+"))\n" +
    "    "+map+"__ts = (" + newCapacity + "*" + K3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
    "  }"
  }

  /**
   * Generates HashMap DELETE function
   *
   * @param prefixKey is a String containing val-def
   *        required to be available, before the key
   *        is used, in the same or a higher scope
   * @param nodeName is unique name for this statement
   *        (if you view it as one command)
   *
   * Map Information:
   * @param map is the name of target M3 map
   * @param key is the list of key parts types
   * @param value is the value type
   * @param indexList is the list of indices for this map
   * @param keyIndicesInEntery which parts of key are
   *        are used 
   *
   * Input arguments:
   * @param keyNames is a list of input key args
   */
  def genGenericDelNamedMap(prefixKey: String, nodeName:String, map:String, key:List[Type], value:Type, indexList: List[List[Int]], keyIndicesInEntery:List[Int], keyNames:List[String]) = {
    //d = del
    val hash = nodeName+"_dhash"
    val e = nodeName+"_de"
    val i = nodeName+"_di"
    val prev = nodeName+"_dprev"
    val next = nodeName+"_dnext"
    val found = nodeName+"_dfound"
    val entryClsName = K3MapCommons.entryClassName(value, key, indexList)

    "//K3DELNAMED\n" +
    prefixKey +
    "  val "+hash+" = " + K3MapCommons.hashFunction(keyNames) + "\n" +
    "  val "+i+":Int = "+K3MapCommons.indexForFunction(hash, map+".length")+"\n" +
    "  var "+prev+":" + entryClsName + " = " + map + "(" + i + ")\n" +
    "  var "+e+":" + entryClsName + " = " + prev + "\n" +
    "  var "+found+":Boolean = false\n" +
    "  while(!"+found+" && "+e+" != null) {\n" +
    "    val "+next+":" + entryClsName + " = " + e + ".next\n" +
    "    if("+e+".hs == "+hash+" && "+keyNames.zip(keyIndicesInEntery).map{case (x, i) => e+"._"+(i+1)+" == "+x}.mkString(" && ")+") {\n"+
    "      "+found+" = true\n" +
    indexList.map{ indexLoc =>
      val idxEntryCls = K3MapCommons.indexEntryClassName(entryClsName, indexLoc)
      val field = e+".ptr"+idxEntryCls
      "      "+field+".v.update("+field+"_idx, null)\n"

      //TODO we should change this value update to null, into a smarter impl like this:
      // val field = e+".ptr"+idxEntryCls
      // val fieldV = e+"_ptr"+idxEntryCls+"_v"
      // val fieldIdx = field+"_idx"

      // "      val "+fieldV+": Array["+idxEntryCls+"] = "+field+".v\n" +
      // "      val "+fieldV+"_lastElem: Int = "+fieldV+".length-1\n" +
      // "      "+fieldV+".update("+fieldIdx+", "+fieldV+"("+fieldV+"_lastElem))\n" +
      // "      "+fieldV+".remove("+fieldV+"_lastElem)\n"
      // and then we should correct the index info for the moved element

    }.mkString +
    "      "+ map + "__sz -= 1\n" +
    "      if("+prev+" == "+e+") "+map+"("+i+") = "+next+"\n" +
    "      else "+prev+".next = "+next+"\n"+
    "    }\n" +
    "    "+prev+" = "+e+"\n" +
    "    "+e+" = "+next+"\n" +
    "  }\n"
  }

  /**
   * This function is used for extracting key symbols
   * given index information (i.e which parts of key are
   * used as index key?)
   *
   * @param keyNames is a list of input key args
   * @param indexLoc is key part indices
   */
  def filterExprAtElementLoc(keyNames: List[String], indexLoc: List[Int]): List[String] = keyNames.zipWithIndex.filter{ case (_, ki) => indexLoc contains ki }.map(_._1)
}