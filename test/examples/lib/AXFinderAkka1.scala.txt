package examples
import ddbt.lib._

class AXFinderAkka extends AXFinderBase {
  val N = 16
  val idx = List((x:(Long,Double))=>x._1)
  val AXFINDER = KAMap.make[Long,Double](context,N);
  val mASKS1 = KAMap.make[(Long,Double),Double](context,N,idx);
  val mASKS2 = KAMap.make[(Long,Double),Long](context,N,idx);
  val mBIDS1 = KAMap.make[(Long,Double),Long](context,N,idx);
  val mBIDS3 = KAMap.make[(Long,Double),Double](context,N,idx);
  def result = AXFINDER.toMap
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg1 = mBIDS1.aggr((0,BIDS_BROKER_ID)) { case (k2,v3) =>
      val A_PRICE = k2._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v3 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)))
    }
    val agg4 = mBIDS3.aggr((0,BIDS_BROKER_ID)) { case (k5,v6) =>
      val A_PRICE = k5._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v6 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg1 * -BIDS_VOLUME) + agg4));
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),1L);
  }
  
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val agg7 = mBIDS1.aggr((0,BIDS_BROKER_ID)) { case (k8,v9) =>
      val A_PRICE = k8._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v9 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    val agg10 = mBIDS3.aggr((0,BIDS_BROKER_ID)) { case (k11,v12) =>
      val A_PRICE = k11._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v12 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg7 * BIDS_VOLUME) + (agg10 * -1L)));
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),-1L);
  }
  
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val agg13 = mASKS1.aggr((0,ASKS_BROKER_ID)) { case (k14,v15) =>
      val B_PRICE = k14._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      (v15 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    val agg16 = mASKS2.aggr((0,ASKS_BROKER_ID)) { case (k17,v18) =>
      val B_PRICE = k17._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      (v18 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(ASKS_BROKER_ID,((agg13 * -1L) + (agg16 * ASKS_VOLUME)));
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
  }
  
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val agg19 = mASKS1.aggr((0,ASKS_BROKER_ID)) { case (k20,v21) =>
      val B_PRICE = k20._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      (v21 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    val agg22 = mASKS2.aggr((0,ASKS_BROKER_ID)) { case (k23,v24) =>
      val B_PRICE = k23._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      (v24 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(ASKS_BROKER_ID,(agg19 + (agg22 * -ASKS_VOLUME)));
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),-1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
  }
}
