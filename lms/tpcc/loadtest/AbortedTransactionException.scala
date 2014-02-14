package ddbt.tpcc.loadtest

class AbortedTransactionException(val message: String) extends Exception {
	def this() = this("")
}
