package ddbt.codegen.pardis

import ddbt.lib.ManifestHelper._
import ddbt.lib.store.{IHash, Store, Entry}
import ddbt.lib.store.deep.MStoreComponent
import ddbt.ast.Type
import ch.epfl.data.pardis.ir.{IfThenElse, ObjectOps, Base}

trait M3StoreOps extends MStoreComponent with ObjectOps with IfThenElse {
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]

  // M3-specific operations
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]]
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]):Rep[Unit]
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]):Rep[Unit]
}

trait M3StoreOpsExp extends Base with M3StoreOps with IfThenElse{
  val USE_STORE1 = true // whether we specialize temporary maps in Store1
  val USE_UNIQUE_INDEX_WHEN_POSSIBLE = true

  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]] = {
    val sym=newStore[E]; sym.asInstanceOf[Sym[_]].attributes.put("_isTemp",true); sym
  }
  def isTemp(s:Sym[_]) = s.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)

  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last

    val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })

    val entVal = ent.get(n)
    if(tmp) {
      // we don't remove 0-elements
      if (USE_STORE1) {
        //val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
        //addIndicesToEntryClass[E](map, (xx, m) => { val idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })
        __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()),
          reflectWrite(map)(M3Add(map,ent))
        )
      } else {
        __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), {
          ///////
          val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
          __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt += (n, entVal))
          ///////
        })
      }
    } else {
      // we remove 0-elements
      __ifThenElse(infix_==(entVal,unit(zero(lastMan))), unit(()), {
        ///////
        val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
        __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),{
          currentEnt += (n, entVal)
          val currentEntVal = currentEnt.get(n)
          __ifThenElse(infix_==(currentEntVal,unit(zero(lastMan))),map.delete(currentEnt),unit(()))
        })
        ///////
      })
    }
    unit(())
  }
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = {
    val tmp = isTemp(map.asInstanceOf[Sym[_]])
    val n = m.typeArguments.size
    val lastMan = m.typeArguments.last
    val currentEnt = stGet(map,-1,ent) //map.get((1 until n).map(i => (i, ent.get(i))) : _*)
    val entVal = ent.get(n)

    val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
    var idx= -1; addIndicesToEntryClass[E](map, (xx, m) => { idx=m.indexOf(tupVal); if(idx < 0) { m+=tupVal; idx=m.size-1 } })

    if(tmp) { // this never happens in practice
      __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt.update(n, entVal)) // same
    } else {
      __ifThenElse(infix_==(entVal,unit(zero(lastMan))),{
        __ifThenElse(infix_==(currentEnt,unit(null)),unit(()),map.delete(currentEnt))
      },{
        __ifThenElse(infix_==(currentEnt,unit(null)),stUnsafeInsert(map,ent,idx),currentEnt.update(n, entVal)) // same
      })
    }
  }

  override def stGet[E<:Entry:Manifest](x: Rep[Store[E]], idx_in:Int,key:Rep[E]):Rep[E] = {
    var idx = idx_in
    key match {
      case Def(Reflect(SteSampleSEntry(_, args),_,_)) => addIndicesToEntryClass[E](x, (xx, m) => {
        val tupVal = ((IHash,args.map(_._1),USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1)) //if(isTemp) ((IHash,args.map(_._1),false,-1)) else ((IHash,args.map(_._1),true,-1))
        idx = m.indexOf(tupVal)
        if(idx < 0) {
          m += tupVal
          idx = m.size - 1
        }
      })
      case _ =>
        val tupVal = ((IHash,(1 until manifest[E].typeArguments.size).toList,USE_UNIQUE_INDEX_WHEN_POSSIBLE,-1))
        addIndicesToEntryClass[E](x, (xx, m) => {
          idx = m.indexOf(tupVal)
          if(idx < 0) { m+=tupVal; idx=m.size-1 }
        })
      //throw new GenerationFailedException("You should provide a sample entry to this method: Store.get")
    }
    val elem:Rep[E]=StGet[E](x,idx,key)
    steMakeMutable(elem)
  }

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  case class M3Add[E<:Entry:Manifest](s: Rep[Store[E]], e:Rep[E]) extends Def[Unit]

  def stUnsafeInsert[E<:Entry:Manifest](x: Rep[Store[E]], e: Rep[E], idx:Int):Rep[Unit] = reflectWrite(x)(StUnsafeInsert[E](x, e, idx))
  case class StUnsafeInsert[E<:Entry:Manifest](s: Rep[Store[E]], e:Rep[E],idx:Int) extends Def[Unit]
}