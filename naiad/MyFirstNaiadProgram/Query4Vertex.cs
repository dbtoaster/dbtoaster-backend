using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting.Query4
{
    public static class ExtensionMethods
    {
        public static Stream<M3MapBase<string, long>, Epoch> query4(this Stream<LINEITEM4, Epoch> lineitems, Stream<ORDERS4, Epoch> parts)
        {
            return Foundry.NewBinaryStage(lineitems, parts, (i, s) => new Query4Vertex(i, s), x => x.GetHashCode(), y => y.GetHashCode(), null, "Query4");
        }

        public class Query4Vertex : BinaryVertex<LINEITEM4, ORDERS4, M3MapBase<string, long>, Epoch>
        {  
             
            M3MapBase<string, long> ORDER_COUNT = new M3MapBase<string, long>();
            M3MapBase<long, long> ORDER_COUNTLINEITEM1_DOMAIN1_1_DELTA = new M3MapBase<long, long>();
            M3MapBase<TLS4, long> ORDER_COUNTLINEITEM1 = new M3MapBase<TLS4, long>(0, false, 
                new Function1<TLS4, object>[]{ new MySliceFunction()});

            M3MapBase<TLS4, long> ORDER_COUNTORDERS1_DELTA = new M3MapBase<TLS4, long>();
            M3MapBase<long, long> ORDER_COUNTORDERS1_E1_1 = new M3MapBase<long, long>();
            
            DateTime c1 = new DateTime(1993, 7, 1);
            DateTime c2 = new DateTime(1993, 10, 1);

            public override void OnReceive1(Message<LINEITEM4, Epoch> message)
            {
                this.NotifyAt(message.time);


                ORDER_COUNTLINEITEM1_DOMAIN1_1_DELTA.clear();
                for (int i = 0; i < message.length; i++)
                {
                    LINEITEM4 lineitem = message.payload[i];
                    if (lineitem.receiptdate > lineitem.commitdate) 
                        ORDER_COUNTLINEITEM1_DOMAIN1_1_DELTA.add(lineitem.orderkey, lineitem.function);
                }


                foreach (var data in ORDER_COUNTLINEITEM1_DOMAIN1_1_DELTA.tempforeach())
                {
                    var o_orderkey = data.key;
                    var v3 = data.value;
                    foreach (var data1 in  ORDER_COUNTLINEITEM1.slice(0,o_orderkey).tempforeach())
                    {
                        var k4 = data1.key;
                        var v4 = data1.value;
                        var o_orderpriority = k4._2;

                        if (v3 != 0 && 
                            (ORDER_COUNTORDERS1_E1_1.get(o_orderkey) + ORDER_COUNTLINEITEM1_DOMAIN1_1_DELTA.get(o_orderkey)) != 0) 
                            ORDER_COUNT.add(o_orderpriority,v4);

                        if (v3 != 0 && ORDER_COUNTORDERS1_E1_1.get(o_orderkey) != 0)
                            ORDER_COUNT.add(o_orderpriority, (v4 * -1L));
                    }


                }

                foreach (var data in ORDER_COUNTLINEITEM1_DOMAIN1_1_DELTA.tempforeach())
                {
                    var o_orderkey = data.key;
                    var v7 = data.value;
                    ORDER_COUNTORDERS1_E1_1.add(o_orderkey,v7);
                }

            }

            public override void OnReceive2(Message<ORDERS4, Epoch> message)
            {
                this.NotifyAt(message.time);

                ORDER_COUNTORDERS1_DELTA.clear();
                for (int i = 0; i < message.length; i++)
                {
                    ORDERS4 order = message.payload[i];
                    if (order.orderdate >= c1 && c2 > order.orderdate)
                        ORDER_COUNTORDERS1_DELTA.add(new TLS4(order.orderkey, order.orderpriority), order.function);

                }

                foreach (var data in ORDER_COUNTORDERS1_DELTA.tempforeach()) 
                {
                    var k10 = data.key;
                    var v10 = data.value;

                    var o_orderkey = k10._1;
                    var o_orderpriority = k10._2;
                    if (ORDER_COUNTORDERS1_E1_1.get(o_orderkey) != 0) 
                        ORDER_COUNT.add(o_orderpriority,v10);

                    ORDER_COUNTLINEITEM1.add(new TLS4(o_orderkey,o_orderpriority),v10);
                }

            }

            public override void OnNotify(Epoch time)
            {
                var output = this.Output.GetBufferForTime(time);
                output.Send(ORDER_COUNT);
            }

            public Query4Vertex(int index, Stage<Epoch> vertex) : base(index, vertex) { }

        }

    }

     public class MySliceFunction : Function1<TLS4, object>
        {
            public override object apply(TLS4 t)
            {
                return t._1;
            }
        }
}
