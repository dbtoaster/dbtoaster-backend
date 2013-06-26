package org.dbtoaster.dbtoasterlib {
  /** This object defines dbtoaster-related exceptions
    */
  object DBToasterExceptions {
    final case class DBTScalaCodegenError(msg: String) extends Error(msg)
    final case class DBTFatalError(msg: String) extends Error(msg)
    final case class DBTNotImplementedException(msg: String) 
      extends RuntimeException(msg)
  }
} 
