using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting.Query1Vertex
{
    public static class ExtensionMethods
    {
        public static Stream<M3MapBase<Query1TSS, double>, Epoch> query1SUM_QTY(this Stream<LINEITEM1, Epoch> stream)
        {
            return stream.NewUnaryStage(
                (i, s) => new Query1Vertex(i, s), 
                x => x.GetHashCode(),
                null, "SUM_QTY");
        }

        internal class Query1Vertex: UnaryVertex<LINEITEM1, M3MapBase<Query1TSS, double>, Epoch>
        {

            M3MapBase<Query1TSS, double> SUM_QTY = new M3MapBase<Query1TSS, double>();
            M3MapBase<Query1TSS, double> SUM_QTYLINEITEM1_DELTA = new M3MapBase<Query1TSS, double>();

            DateTime c1 = new DateTime(1997, 9, 1);
            
            public override void OnReceive(Message<LINEITEM1, Epoch> message)
            {
                SUM_QTYLINEITEM1_DELTA.clear();
                M3MapBase<Query1TSS, double> agg1 = new M3MapBase<Query1TSS,double>();
                for (int i = 0; i < message.length; i++)
                {
                    LINEITEM1 lineitem = message.payload[i];

                    if (c1 >= lineitem.shipdate)
                    {
                        Query1TSS key = new Query1TSS(lineitem.returnflag, lineitem.linestatus);
                        double value = lineitem.function * lineitem.quantity;
                        agg1.add(key, value);
                        /*if (agg1.ContainsKey(key))
                        {
                            agg1[key] = agg1[key] + value;
                        }
                        else
                        {
                            agg1.Add(key, value);
                        }*/
                    }
                }


                foreach (var p in agg1.tempforeach())
                {
                    var k2 = p.key;
                    var v2 = p.value;
                    var lineitem_returnflag = k2._1;
                    var lineitem_linestatus = k2._2;
                    Query1TSS key = new Query1TSS(lineitem_returnflag, lineitem_linestatus);
                    SUM_QTYLINEITEM1_DELTA.add(key, v2);
                    /*if (SUM_QTYLINEITEM1_DELTA.ContainsKey(key))
                    {
                        SUM_QTYLINEITEM1_DELTA[key] = SUM_QTYLINEITEM1_DELTA[key] + v2;
                    }
                    else
                    {
                        SUM_QTYLINEITEM1_DELTA.Add(key, v2);
                    }*/
                }

                foreach (var p in SUM_QTYLINEITEM1_DELTA.tempforeach())
                {
                    var k3 = p.key;
                    var v3 = p.value;

                    var lineitem_returnflag = k3._1;
                    var lineitem_linestatus = k3._2;

                    Query1TSS key = new Query1TSS(lineitem_returnflag, lineitem_linestatus);
                    SUM_QTY.add(key, v3);
                    /*if (SUM_QTY.ContainsKey(key))
                    {
                        SUM_QTY[key] = SUM_QTY[key] + v3;
                    }
                    else
                    {
                        SUM_QTY.Add(key, v3);
                    }*/
                }

                var output = this.Output.GetBufferForTime(message.time);
                output.Send(SUM_QTY);

            }

            public override void OnNotify(Epoch time)
            {
                
            }

            public Query1Vertex(int index, Stage<Epoch> stage) : base(index, stage) { }
        }
    }
}
