package ddbt.tpcc.itx

import java.util.Date
import ddbt.tpcc.tx.TpccTable

/**
 * NewOrder Transaction for TPC-C Benchmark
 *
 * @author Mohammad Dashti
 */
trait IInMemoryTx { self =>
	def setSharedData(db:AnyRef): self.type
}

class InMemoryTxImpl extends IInMemoryTx {
	var SharedData:TpccTable = null

	override def setSharedData(db:AnyRef) = {
		SharedData = db.asInstanceOf[TpccTable]
		this
	}
} 

trait INewOrderInMem extends INewOrder with IInMemoryTx
trait IPaymentInMem extends IPayment with IInMemoryTx
trait IOrderStatusInMem extends IOrderStatus with IInMemoryTx
trait IDeliveryInMem extends IDelivery with IInMemoryTx
trait IStockLevelInMem extends IStockLevel with IInMemoryTx
