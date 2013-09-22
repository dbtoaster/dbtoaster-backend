package toasterbooster.lifters

import org.dbtoaster.dbtoasterlib.StreamAdaptor._
import org.dbtoaster.dbtoasterlib.K3Collection._
import org.dbtoaster.dbtoasterlib.Source._
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import org.dbtoaster.dbtoasterlib.ImplicitConversions._
import org.dbtoaster.dbtoasterlib.StdFunctions._
import org.dbtoaster.dbtoasterlib.QueryInterface._
import xml._
import scala.actors.Actor._
import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.language.implicitConversions

trait ImplicitConversionLifters extends CastingOps with IfThenElse with Expressions {
	implicit def boolToLong(b: Rep[Boolean]): Rep[Long] = __ifThenElse[Long](b, unit(1L), unit(0L))
	implicit def boolToDouble(b: Rep[Boolean]): Rep[Double] = __ifThenElse[Double](b, unit(1.0), unit(0.0))
	implicit def longToDouble1(l: Rep[Long]): Rep[Double] = l.asInstanceOf[Rep[Double]]
	//implicit def longToDouble2(l: Const[Long]): Rep[Double] = unit(l.x.toDouble)
	//implicit def doubleToLong1(l: Rep[Double]): Rep[Long] = l.asInstanceOf[Rep[Long]]
	//implicit def doubleToLong2(l: Const[Double]): Rep[Long] = unit(l.x.toLong)
	implicit def intToDouble1(l: Rep[Int]): Rep[Double] = l.asInstanceOf[Rep[Double]]
	//implicit def intToDouble2(l: Const[Int]): Rep[Double] = unit(l.x.toDouble)
	//implicit def doubleToInt1(l: Rep[Double]): Rep[Int] = l.asInstanceOf[Rep[Int]]
	//implicit def doubleToInt2(l: Const[Double]): Rep[Int] = unit(l.x.toInt)
	implicit def intToLong1(l: Rep[Int]): Rep[Long] = l.asInstanceOf[Rep[Long]]
	//implicit def intToLong2(l: Const[Int]): Rep[Long] = unit(l.x.toLong)
}