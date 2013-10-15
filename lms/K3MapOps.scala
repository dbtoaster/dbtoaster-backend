package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext
import toasterbooster.lifters._
import ddbt.Utils.ind

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in k3apply)
 *
 * @author Mohammad Dashti
 */

object K3MapCommons {
  /**
   * The default initial capacity - MUST be a power of two.
   */
  final val DEFAULT_INITIAL_CAPACITY: Int = 1024
  final val DEFAULT_INITIAL_CAPACITY_INDEX: Int = 512
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

  def entryClassName(value:Type, key:List[Type], indexList: List[List[Int]] = List[List[Int]]()): String = "EntryK"+key.map(x => shortName(x)).mkString+"_V"+shortName(value)+"_X"+indexList.map(x => x.mkString("_")).mkString("N")
  def indexEntryClassName(value:Type, key:List[Type], indexList: List[List[Int]], indexLoc: List[Int]): String = indexEntryClassName(entryClassName(value,key,indexList),indexLoc)
  def indexEntryClassName(entryClsName: String, indexLoc: List[Int]): String = "Idx"+entryClsName+indexNamePostfix(indexLoc)
  def indexMapName(map: String, indexLoc: List[Int]): String = map+indexNamePostfix(indexLoc)
  def indexNamePostfix(indexLoc: List[Int]): String = "_I"+indexLoc.map(_+1).mkString("_")

  def generateAllEntryClasses = generateEntryClasses + "\n" + generateIndexEntryClasses
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

  def shortName(tp: Type) = tp match {
    case TypeLong => "L"
    case TypeDouble => "D"
    case TypeString => "S"
    case TypeDate => "A"
  }

  def zeroValue(v: Type) = v match {
    case TypeLong => "0L"
    case TypeDouble => "0.0"
    case TypeString => "\"\""
    case TypeDate => "new Date()"
  }

  def actualZeroValue(v: Type) = v match {
    case TypeLong => 0
    case TypeDouble => 0.0
    case TypeString => ""
    case TypeDate => new java.util.Date()
  }

  def createK3VarDefinition(name: String, value:Type) = "var "+name+" = "+zeroValue(value)

  def createK3MapDefinition(name: String, value:Type, key:List[Type], indexList: List[List[Int]]) = {
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

  def createK3TempDefinition(name: String, value:Type, key:List[Type]) = {
    val entryCls = entryClassName(value, key,List[List[Int]]())
    entryClasses += (entryCls -> (value,key,List[List[Int]]()))

    "var "+name+": Array["+entryCls+"] = new Array["+entryCls+"]("+DEFAULT_INITIAL_CAPACITY+");\n" +
    "var "+name+"__sz: Int = 0;\n" +
    "var "+name+"__ts: Int = "+INITIAL_THRESHOLD+";"
  }

  def clear = {
    entryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[List[Int]])]()
    indexEntryClasses = scala.collection.mutable.HashMap[String,(Type,List[Type],List[List[Int]],List[Int])]()
  }

  def genGenericAddNamedMap(isConstant: Boolean, isZero: Boolean, prefixValue: String, prefixKey: String, nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], keyNames:List[String], valueName:String, indexList: List[List[Int]]) = {
    if(isZero) {
      "//K3ADDNAMED_CANCELLED"
    } else {
      "//K3ADDNAMED\n" +
      prefixValue +
      (if(isConstant) {
        genGenericSetTempMap("",prefixKey,nodeName,map,K3MapCommons.entryClassName(value, key, indexList),keyIndicesInEntery,keyNames,valueName,false,"+=",indexList,indexList.map(K3MapCommons.indexEntryClassName(value,key,indexList,_)),true,zeroValue(value))
      } else {
        "if("+valueName+" != "+K3MapCommons.zeroValue(value)+") {\n" +
        ind(genGenericSetTempMap("",prefixKey,nodeName,map,K3MapCommons.entryClassName(value, key, indexList),keyIndicesInEntery,keyNames,valueName,false,"+=",indexList,indexList.map(K3MapCommons.indexEntryClassName(value,key,indexList,_)),true,zeroValue(value)))+"\n" +
        "}"
      })
    }
  }

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
      genSetIndexMap(K3MapCommons.indexMapName(nodeName,idx), K3MapCommons.indexMapName(map,idx), indexEntryClsName(i), idx, filterExprAtElementLoc(keyNames, idx) , e, false, indexList) + "\n"
    }.mkString) +
    "\n}"

    if(insideBlock) "; {\n"+ind(content)+"\n}" else content
  }

  def genAddEntryMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[String], inputValueSymbol:String, e:String, hash: String, bucketIndex:String) = {
    val newCapacity = nodeName+"_nc"
    val tmp = e+"_atmp"

    "  val " + tmp + ":" + entryClsName + " = " + map + "(" + bucketIndex + ")\n" +
    "  " + e + " = new " + entryClsName + "("+hash+","+inputKeySymbols.mkString(",")+","+inputValueSymbol+","+tmp+")\n" +
    "  " + map + "(" + bucketIndex + ") = "+e+"\n"+
    "  " + map + "__sz += 1\n" +
    "  if(" + map + "__sz-1 >= " + map + "__ts) {\n" +
    "    val "+newCapacity+" = 2 * "+map+".length\n" +
    "    "+map+" = __transferHashMap["+entryClsName+"]("+map+",new Array["+entryClsName+"]("+newCapacity+"))\n" +
    "    "+map+"__ts = (" + newCapacity + "*" + K3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
    "  }"
  }

  def genSetIndexMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], keyNames:List[String], inputValueSymbol:String,insideBlock: Boolean=true, indexList: List[List[Int]] = List[List[Int]](), indexEntryClsName: List[String]=List[String]()) : String = {
    //st = set index
    val hash = nodeName+"_sithash"
    val e = nodeName+"_site"
    val found = nodeName+"_sitfound"
    val result = nodeName+"_sitresult"
    val i = nodeName+"_siti"
    val valueName = inputValueSymbol
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
    genAddEntryIndexMap(nodeName,map,entryClsName,keyIndicesInEntery,keyNames,valueName,e,hash,i)+"\n"+
    "  "+valueName+"."+currentIndexPointerName+" = "+e+"\n"+
    "  "+valueName+"."+currentIndexPointerName+"_idx = "+e+".v.length\n"+
    "  "+e+".v += "+valueName+"\n" +
    "\n}"

    if(insideBlock) "{\n"+ind(content)+"\n}" else content
  }

  def genAddEntryIndexMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[String], inputValueSymbol:String, e:String, hash: String, bucketIndex:String) = {
    val newCapacity = nodeName+"_nic"
    val tmp = e+"_aitmp"

    "  val " + tmp + ":"+entryClsName+" = " + map + "(" + bucketIndex + ")\n" +
    "  " + e + " = new " + entryClsName + "("+hash+","+inputKeySymbols.mkString(",")+","+tmp+")\n" +
    "  " + map + "(" + bucketIndex + ") = "+e+"\n"+
    "  " + map + "__sz += 1\n" +
    "  if(" + map + "__sz-1 >= " + map + "__ts) {\n" +
    "    val "+newCapacity+" = 2 * "+map+".length\n" +
    "    "+map+" = __transferHashMap["+entryClsName+"]("+map+",new Array["+entryClsName+"]("+newCapacity+"))\n" +
    "    "+map+"__ts = (" + newCapacity + "*" + K3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
    "  }"
  }

  def genGenericSetNamedMap(prefixValue: String, prefixKey: String, nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], keyNames:List[String], valueName:String, indexList: List[List[Int]], operation: String="") = {
    //sn = set named map
    "//K3SETNAMED\n" +
    prefixValue +
    "if("+valueName+" == "+K3MapCommons.zeroValue(value)+") {\n" +
    genGenericDelNamedMap(prefixKey,nodeName,map,key,value,keyIndicesInEntery,keyNames,valueName,indexList,operation)+ "\n" +
    "} else {\n" +
    ind(genGenericSetTempMap("",prefixKey,nodeName,map,K3MapCommons.entryClassName(value, key, indexList),keyIndicesInEntery,keyNames,valueName,false,"=",indexList,indexList.map(K3MapCommons.indexEntryClassName(value,key,indexList,_))))+"\n" +
    "}"
  }

  def genGenericDelNamedMap(prefixKey: String, nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], keyNames:List[String], valueName:String, indexList: List[List[Int]], operation: String="") = {
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
    }.mkString +
    "      "+ map + "__sz -= 1\n" +
    "      if("+prev+" == "+e+") "+map+"("+i+") = "+next+"\n" +
    "      else "+prev+".next = "+next+"\n"+
    "    }\n" +
    "    "+prev+" = "+e+"\n" +
    "    "+e+" = "+next+"\n" +
    "  }\n"
  }

  def filterExprAtElementLoc(inputKeySymbols: List[String], indexLoc: List[Int]): List[String] = inputKeySymbols.zipWithIndex.filter{ case (_, ki) => indexLoc contains ki }.map(_._1)
}

trait K3MapOps extends Base {
  // Nodes creation
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  def namedK3Var[T](name: String,tp:Type)(implicit mT:Manifest[T]): Rep[K3Var[T]]
  def namedK3Map[K,V](name: String,key:List[Type],value:Type,indexList: List[List[Int]])(implicit mK:Manifest[K], mV:Manifest[V]): Rep[K3Temp[K,V]]
  def k3var(value:Type) : Rep[K3Var[_]]
  def k3temp(key_tp:List[Type],value_tp:Type):Rep[K3Temp[_,_]]
  // Operations on K3Map, K3Var and K3Temp
  def k3get(map:Rep[_], key:List[Rep[_]]=Nil,value_tp:Type):Rep[_]
  def k3set(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3add(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3foreach(map:Rep[_], key: Rep[_], value: Rep[_], body: => Rep[Unit]) : Rep[Unit]
  def k3slice(map:Rep[_],part:Int,partKey:List[Rep[_]]):Rep[_]
  def k3clear(map:Rep[_]):Rep[Unit]
}

trait K3MapOpsExp extends BaseExp with EffectExp with K3MapOps{
  import ManifestHelper.man
  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }
  def namedK3Var[T](name: String,tp:Type)(implicit mT:Manifest[T]) = reflectMutable(NamedK3Var(name,tp)(mT))
  def namedK3Map[K, V](name: String,key:List[Type],value:Type,indexList: List[List[Int]])(implicit mK:Manifest[K], mV:Manifest[V]) = reflectMutable(NamedK3Map(name,key,value,indexList,mK,mV))
  def k3var(value:Type) = reflectMutable(NewK3Var(value,man(value)))
  def k3temp(key:List[Type],value:Type) = reflectMutable(NewK3Temp(key,value,man(key),man(value)))

  def k3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = K3Get(map,key,man(value_tp))
  def k3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Set(map,key,value))
  def k3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Add(map,key,value))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body: => Exp[Unit]) = k3foreach(map,key,value,reifyEffects(body))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Block[Unit]) = reflectEffect(K3Foreach(map,key,value,body),summarizeEffects(body).star)
  def k3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = K3Slice(map,part,partKey)
  def k3clear(map:Exp[_]) = reflectWrite(map)(K3Clear(map))

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  case class NamedK3Var[T](n:String,tp:Type)(implicit mT:Manifest[T]) extends Def[K3Var[T]]
  case class NamedK3Map[K,V](n:String,key:List[Type],value:Type,indexList: List[List[Int]],mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[K,V]]
  case class NewK3Var[K,V](value:Type,mV:Manifest[V]) extends Def[K3Var[_]]
  case class NewK3Temp[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[_,_]]
  case class K3Get[T](map:Exp[_], key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  case class K3Set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Foreach(map:Exp[_], key:Exp[_], value:Exp[_], body:Block[Unit]) extends Def[Unit]
  case class K3Slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) extends Def[Exp[_]]
  case class K3Clear(map:Exp[_]) extends Def[Unit]

  override def syms(e: Any): List[Sym[Any]] = e match {
    case K3Foreach(m,k,v,b) => syms(k):::syms(v):::syms(b)
    case _ => super.syms(e)
  }
  override def boundSyms(e: Any): List[Sym[Any]] = e match {
    case K3Foreach(m,k,v,b) => effectSyms(k):::effectSyms(v):::effectSyms(b)
    case _ => super.boundSyms(e)
  }
  override def symsFreq(e: Any): List[(Sym[Any], Double)] = e match {
    case K3Foreach(m,k,v,b) => freqHot(k):::freqHot(v):::freqHot(b)
    case _ => super.symsFreq(e)
  }
  override def aliasSyms(e: Any): List[Sym[Any]] = e match {
    case K3Set(m,k,v) => Nil
    case K3Add(m,k,v) => Nil
    case _ => super.aliasSyms(e)
  }
}

trait ScalaGenK3MapOps extends ScalaGenBase with ScalaGenEffect {
  val IR: K3MapOpsExp with ExtendedExpressions
  import IR._
  import ddbt.Utils.{ind,tup}

  protected def getBlockContents(blk:Block[_]):String = {
    val save=stream; val wr=new java.io.StringWriter; stream=new java.io.PrintWriter(wr)
    emitBlock(blk); val res=ind(wr.toString); stream=save; res
  }

  def isPossibleToInlineExpr(expr: Exp[_]) = expr match {
    case s@Sym(x) => s.possibleToInline
    case _ => true
  }

  /**
   * If we are using an expression result inside an operation,
   * and this expression is possible to inline, and the result
   * should be used several times in this operation, we should
   * first creat a symbol for it
   */
  def genValDefForNonInlinableExpr(exprList: List[Exp[_]], nodeName: String) = exprList.map{ expr => expr match {
      case s@Sym(x) => if(isPossibleToInlineExpr(expr)) {
        "val x"+x+"_"+nodeName+" = "+quote(expr)+"\n"
      } else {
        ""
      }
      case _ => ""
    }
  }.mkString

  /**
   * Tightly related to genValDefForNonInlinableExpr
   * If we have created val-def for an inlinable expression,
   * we should take care of its symbol
   */
  def genQuoteExpr(exprList: List[Exp[_]], nodeName: String) = exprList.map{ expr => expr match {
      case s@Sym(x) => if(isPossibleToInlineExpr(expr)) {
        "x"+x+"_"+nodeName
      } else {
        quote(expr)
      }
      case _ => quote(expr)
    }
  }

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NamedK3Var(n,_) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NamedK3Map(n,_,_,_,_,_) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NewK3Var(v,_) => stream.println(K3MapCommons.createK3VarDefinition(quote(sym), v))
    case NewK3Temp(ks,v,_,_) => stream.println(K3MapCommons.createK3TempDefinition(quote(sym),v,ks))
    case K3Get(m,ks,_) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => emitValDef(sym, quote(m))
      case Some(Reflect(NewK3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genGetMap(nodeName, map, K3MapCommons.entryClassName(value, key),value.toScala+" = "+K3MapCommons.zeroValue(value), (0 until ks.size).toList, ks)
      })
      case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genGetMap(nodeName, map, K3MapCommons.entryClassName(value, key, indexList),value.toScala+" = "+K3MapCommons.zeroValue(value), (0 until ks.size).toList, ks)
      })
      case _ => emitValDef(sym, quote(m)+".onlyget("+tup(ks map quote)+")")
    }
    case K3Set(m,ks,v) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => stream.println(quote(m)+" = "+quote(v))
      case Some(Reflect(NewK3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genSetTempMap(nodeName, map, K3MapCommons.entryClassName(value, key, List[List[Int]]()), (0 until ks.size).toList, ks, v)
      })
      case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genSetNamedMap(nodeName, map, key, value, (0 until ks.size).toList, ks, v, indexList)
      })
      case _ => stream.println(quote(m)+".onlyset("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    }
    case K3Add(m,ks,v) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) | Some(Reflect(NamedK3Var(_,_),_,_)) => stream.println(quote(m)+" += "+quote(v))
      case Some(Reflect(NewK3Temp(key,value,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genAddTempMap(nodeName, map, value, K3MapCommons.entryClassName(value, key, List[List[Int]]()), (0 until ks.size).toList, ks, v)
      })
      case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genAddNamedMap(nodeName, map, key, value, (0 until ks.size).toList, ks, v, indexList)
      })
      case _ => stream.println(quote(m)+".onlyadd("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    }
    case K3Foreach(m,k,v,body) => {
      val block=getBlockContents(body) // enables both the renaming trick and allow nested block indentation
      Def.unapply(m) match {
        case Some(Reflect(NewK3Temp(key,_,_,_),_,_)) => stream.println({
          val map = quote(m)
          val nodeName = createNodeName(sym)
          
          genForeachMap(nodeName, map, quote(k), quote(v), block, key.size == 1)
        })
        case Some(Reflect(NamedK3Map(_,key,_,_,_,_),_,_)) => stream.println({
          val map = quote(m)
          val nodeName = createNodeName(sym)
          
          genForeachMap(nodeName, map, quote(k), quote(v), block, key.size == 1)
        })
        case Some(Reflect(K3Slice(name,part,partKey),_,_)) => stream.println({
          val nodeName = createNodeName(sym)
          val map = genQuoteExpr(List(m),nodeName).apply(0)

          val elemKeyPostfix = Def.unapply(m) match {
            case Some(Reflect(NamedK3Map(_,_,_,indexList,_,_),_,_)) => stream.println({
              val indexLoc = indexList(part)
              if(indexLoc.size == 1) {
                "._"+indexLoc(0)
              } else ""
            })
            case _ => ""
          }
          
          //f= foreach
          val i = nodeName+"_fi"
          val len = nodeName+"_flen"
          val e = nodeName+"_fe"
          val sliceValDef = ind(genValDefForNonInlinableExpr(List(m),nodeName))
          "; {\n" +
          (if(sliceValDef.length > 2) sliceValDef+"\n" else "") +
          "  //SLICEK3FOREACH\n" +
          "  var "+i+":Int = 0\n" +
          "  val "+len+":Int = "+map+".length\n" +
          "  while("+i+" < "+len+") {\n" +
          "    val "+e+" = "+map+"("+i+")\n" +
          "    if("+e+" != null) {\n"+
          "      val "+quote(k)+" = "+e+elemKeyPostfix+"\n"+
          "      val "+quote(v)+" = "+e+".v\n" +
          ind(block,2)+"\n" +
          "    }\n" +
          "    "+i+" += 1\n" +
          "  }\n" +
          "}"
        })
        case _ => stream.println(quote(m)+".onlyforeach { ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
      }
    }
    case K3Slice(m,p,pks) => Def.unapply(m) match {
      case Some(Reflect(NamedK3Map(_,key,value,indexList,_,_),_,_)) => emitValDef(sym, {
        val map = quote(m)
        val mapClass = K3MapCommons.entryClassName(value,key,indexList)
        val nodeName = createNodeName(sym)
        val indexLoc = indexList(p)
        val targetIndex = K3MapCommons.indexMapName(map,indexLoc)
        val targetIndexClass = K3MapCommons.indexEntryClassName(mapClass,indexLoc)
        //TODOOOO
        //emitValDef(sym, quote(m)+".namedmapslice("+p+","+tup(pks map quote)+")")
        genGetMap(nodeName, targetIndex, targetIndexClass,"scala.collection.mutable.ArrayBuffer["+mapClass+"] = new scala.collection.mutable.ArrayBuffer["+mapClass+"](0)", indexLoc, pks)
      })
      case _ => emitValDef(sym, quote(m)+".onlyslice("+p+","+tup(pks map quote)+")")
    }
    case K3Clear(m) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(tp,_),_,_)) => stream.println(quote(m)+" = "+K3MapCommons.zeroValue(tp))
      case Some(Reflect(NamedK3Var(_,tp),_,_)) => stream.println(quote(m)+" = "+K3MapCommons.zeroValue(tp))
      case Some(Reflect(NewK3Temp(_,_,_,_),_,_)) => stream.println({
        genClearMap(createNodeName(sym), quote(m))+"\n"
      })
      case Some(Reflect(NamedK3Map(_,_,_,indexList,_,_),_,_)) => stream.println({
        val map = quote(m)
        val nodeName = createNodeName(sym)
        genClearMap(nodeName, map)+"\n"+
        indexList.map(is => genClearMap(nodeName+K3MapCommons.indexNamePostfix(is), K3MapCommons.indexMapName(map,is))+"\n").mkString
      })
      case _ => stream.println(quote(m)+".onlyclear")
    }
    case _ => super.emitNode(sym,rhs)
  }

  def createNodeName(s: Sym[_]) = "x"+s.id

  def genForeachMap(nodeName:String, map:String, k:String, v:String, block: String, singleValueKey: Boolean) = {
    //f= foreach
    val i = nodeName+"_fi"
    val len = nodeName+"_flen"
    val e = nodeName+"_fe"
    "; {\n" +
    "  //K3FOREACH\n" +
    "  var "+i+" = 0\n" +
    "  val "+len+" = "+map+".length\n" +
    "  while("+i+" < "+len+") {\n" +
    "    var "+e+" = "+map+"("+i+")\n" +
    "    while("+e+" != null) {\n"+
    "      val "+k+" = "+e+(if(singleValueKey) "._1" else "")+"\n"+
    "      val "+v+" = "+e+".v\n" +
    ind(block,2)+"\n" +
    "      "+e+" = "+e+".next\n" +
    "    }\n" +
    "    "+i+" += 1\n" +
    "  }\n" +
    "}"
  }

  def genAddNamedMap(nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_], indexList: List[List[Int]]) = {
    //an = add named map
    var isConstant:Boolean = false
    var isZero:Boolean = false

    inputValueSymbol match {
      case Const(c) => {
        isConstant = true
        if(c == K3MapCommons.actualZeroValue(value)) {
          isZero = true
        }
      }
      case _ => ()
    }

    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
    val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)
    K3MapCommons.genGenericAddNamedMap(isConstant,isZero,prefixValue,prefixKey,nodeName,map,key,value,keyIndicesInEntery,keyNames,valueName,indexList)
  }

  def genSetNamedMap(nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_], indexList: List[List[Int]], operation: String="") = {
    //sn = set named map
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
    val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)

    K3MapCommons.genGenericSetNamedMap(prefixValue,prefixKey,nodeName,map,key,value,keyIndicesInEntery,keyNames,valueName,indexList,operation)
  }

  def genDelNamedMap(nodeName:String, map:String, key:List[Type], value:Type, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_], indexList: List[List[Int]], operation: String="") = {
    //d = del
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)

    K3MapCommons.genGenericDelNamedMap(prefixKey,nodeName,map,key,value,keyIndicesInEntery,keyNames,valueName,indexList,operation)
  }

  def genAddTempMap(nodeName:String, map:String, value:Type, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_]) : String = {
    //at = add temp map
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)

    "//K3ADDTEMP\n" +
    genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName) +
    "if("+valueName+" != "+K3MapCommons.zeroValue(value)+") {\n" +
    ind(genSetTempMap(nodeName,map,entryClsName,keyIndicesInEntery,inputKeySymbols,inputValueSymbol,false,"+="))+"\n" +
    "}"
  }

  def genSetTempMap(nodeName:String, map:String, entryClsName:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]], inputValueSymbol:Exp[_],insideBlock: Boolean=true, operation: String="=", indexList: List[List[Int]] = List[List[Int]](), indexEntryClsName: List[String]=List[String]()) : String = {
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    val valueName = genQuoteExpr(List(inputValueSymbol),nodeName).apply(0)
    val prefixKey = genValDefForNonInlinableExpr(inputKeySymbols,nodeName)
    val prefixValue = genValDefForNonInlinableExpr(List(inputValueSymbol),nodeName)
    K3MapCommons.genGenericSetTempMap(prefixValue, prefixKey, nodeName, map, entryClsName, keyIndicesInEntery, keyNames, valueName, insideBlock, operation, indexList, indexEntryClsName)
  }

  def genGetMap(nodeName:String, map:String, entryClsName:String, valueTypeAndZeroVal:String, keyIndicesInEntery:List[Int], inputKeySymbols:List[Exp[_]]) = {
    //g = get
    val hash = nodeName+"_ghash"
    val e = nodeName+"_ge"
    val found = nodeName+"_gfound"
    val result = nodeName+"_gresult"
    val keyNames = genQuoteExpr(inputKeySymbols,nodeName)
    "{\n" +
    "  //K3GET\n" +
    genValDefForNonInlinableExpr(inputKeySymbols,nodeName) +
    "  val "+hash+" =" + ind(K3MapCommons.hashFunction(keyNames)) + "\n" +
    "  var "+e+":" + entryClsName + " = " + map + "(" + K3MapCommons.indexForFunction(hash, map+".length") + ")\n" +
    "  var "+found+":Boolean = false\n" +
    "  var "+result+":"+valueTypeAndZeroVal+"\n" +
    "  while(!"+found+" && "+e+" != null) {\n" +
    "    if("+e+".hs == "+hash+" && "+keyNames.zip(keyIndicesInEntery).map{case (x, i) => e+"._"+(i+1)+" == "+x}.mkString(" && ")+") {\n"+
    "      "+found+" = true\n"+
    "      "+result+" = "+e+".v\n" +
    "    }\n" +
    "    "+e+" = "+e+".next\n" +
    "  }\n" +
    "  "+result+"\n" +
    "}"
  }

  def genClearMap(nodeName:String, map:String) = {
    val currentSize = nodeName + "__csz"
    val currentCounter = nodeName + "__ctr"
    "; {\n" +
    "  //K3CLEAR\n" +
    "  val " + currentSize + ":Int = " + map + ".length\n" +
    "  var " + currentCounter + ":Int = 0\n" +
    "  while("+currentCounter+" < "+currentSize+") {\n" +
    "    "+map+"("+currentCounter+")=null\n" +
    "    "+currentCounter+"+=1\n" +
    "  }\n" +
    "  "+map+"__sz = 0\n" +
    "  "+map+"__ts = (" + currentSize + "*" + K3MapCommons.DEFAULT_LOAD_FACTOR + ").toInt\n" +
    "}"
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean) : String = {
    def printSym(s: Sym[Any]): String = {
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case NamedK3Var(n,_) => n
            case NamedK3Map(n,_,_,_,_,_) => n
            case _ =>
              val strWriter: java.io.StringWriter = new java.io.StringWriter;
              val stream = new java.io.PrintWriter(strWriter);
              withStream(stream) { 
                emitNode(s, d)
              }
              strWriter.toString
          }
          case None => if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
        }
      } else {
        if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
      }
    }
    x match {
      case Const(s: String) => "\""+s.replace("\"", "\\\"").replace("\n", "\\n")+"\"" // TODO: more escapes?
      case Const(c: Char) => "'"+c+"'"
      case Const(f: Float) => "%1.10f".format(f) + "f"
      case Const(l: Long) => l.toString + "L"
      case Const(null) => "null"
      case Const(z) => z.toString
      case s@Sym(n) => if (forcePrintSymbol) {
        printSym(s)
      } else { 
        isVoidType(s.tp) match {
          case true => "(" + /*"x" + n +*/ ")"
          case false => printSym(s)
        }
      }
      case _ => throw new RuntimeException("could not quote %s".format(x))
    }
  }

  // 
  // override def quote(x: Exp[Any]) : String = x match {
  //   case sym@Sym(_) if sym.attributes.contains(nameAttr) => sym.attributes(nameAttr).toString
  //   case _ => super.quote(x)
  // }
}
