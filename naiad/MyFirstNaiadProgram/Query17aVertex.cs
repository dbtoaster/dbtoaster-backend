using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting.Query17a
{

    public static class ExtensionMethods
    {
        public static Stream<double, Epoch> query17a(this Stream<LINEITEM17a, Epoch> lineitems, Stream<PART17a, Epoch> parts)
        {
            return Foundry.NewBinaryStage(lineitems, parts, (i, s) => new Query17aVertex(i, s), x => x.GetHashCode(), y => y.GetHashCode(), null, "Query17a");
        }

        public class Query17aVertex : BinaryVertex<LINEITEM17a, PART17a, double, Epoch>
        {
            double QUERY17 = 0.0;
            M3MapBase<long, long> QUERY17PART1_DELTA = new M3MapBase<long,long>();
            M3MapBase<TLD17a, double> QUERY17LINEITEM1_DELTA = new M3MapBase<TLD17a,double>();
            M3MapBase<long, long> QUERY17LINEITEM1 = new M3MapBase<long,long>();
            M3MapBase<long, double> QUERY17LINEITEM1_L1_1 = new M3MapBase<long,double>();
            M3MapBase<long, long> QUERY17LINEITEM2_DOMAIN1_1_DELTA = new M3MapBase<long,long>();
            M3MapBase<TLD17a, double> QUERY17LINEITEM2_P_1 = new M3MapBase<TLD17a, double>(0, false, 
                new Function1<TLD17a, object>[]{ new MySliceFunction()});
            M3MapBase<long, double> QUERY17LINEITEM2_L1_3_DELTA = new M3MapBase<long,double>();
            public Query17aVertex(int index, Stage<Epoch> vertex) : base(index, vertex) {}

            public override void OnReceive1(Message<LINEITEM17a, Epoch> message)
            {
               QUERY17LINEITEM2_L1_3_DELTA.clear();
               M3MapBase<long, double> agg1 = new M3MapBase<long, double>();
               M3MapBase<long, long> agg2 = new M3MapBase<long, long>();
               M3MapBase<TLD17a, double> agg3 = new M3MapBase<TLD17a,double>(); 
               for (int i = 0; i < message.length; i++)
               {
                   LINEITEM17a lineitem = message.payload[i];
                   agg1.add(lineitem.partkey, (lineitem.function * lineitem.quantity));
                   agg2.add(lineitem.partkey, lineitem.function);
                   agg3.add(new TLD17a(lineitem.partkey, lineitem.quantity), (lineitem.function * lineitem.extendedprice));
               }
                
                foreach (var entry in agg1.tempforeach()) QUERY17LINEITEM2_L1_3_DELTA.add(entry.key, entry.value);
                QUERY17LINEITEM2_DOMAIN1_1_DELTA.clear();
                
                foreach (var entry in agg2.tempforeach()) QUERY17LINEITEM2_DOMAIN1_1_DELTA.add(entry.key, entry.value);

                QUERY17LINEITEM1_DELTA.clear();
                foreach (var entry in agg3.tempforeach()) 
                {
                    var l_partkey = entry.key._1;
                    var l_quantity = entry.key._2;

                    QUERY17LINEITEM1_DELTA.add(new TLD17a(l_partkey, l_quantity), entry.value);
                }


                double agg4 = 0.0;
                foreach (var entry in QUERY17LINEITEM2_DOMAIN1_1_DELTA.tempforeach()) 
                {
                    double l1 = ((QUERY17LINEITEM1_L1_1.get(entry.key) + QUERY17LINEITEM2_L1_3_DELTA.get(entry.key)) * 0.005);
                    var l_partkey = entry.key;
                    var v7 = entry.value;
                    foreach (var entry2 in QUERY17LINEITEM2_P_1.slice(0, entry.key).tempforeach()) 
                    {
                        var l_quantity =  entry2.key._2;
                        var v8 = entry.value;
                        if (v7 != 0 && l1 > l_quantity) 
                            agg4 += (v8 * QUERY17LINEITEM1.get(l_partkey));

                    }

                }

                double agg5 = 0.0;
                foreach (var entry in QUERY17LINEITEM1_DELTA.tempforeach())
                {
                    var l_partkey = entry.key._1;
                    var l_quantity = entry.key._2;
                    var v9 = entry.value;
                    var l2 = ((QUERY17LINEITEM1_L1_1.get(l_partkey) + QUERY17LINEITEM2_L1_3_DELTA.get(l_partkey)) * 0.005);
                    if (l2 > l_quantity) agg5 += (v9 * QUERY17LINEITEM1.get(l_partkey));

                }

                double agg6 = 0.0;
                foreach (var entry in QUERY17LINEITEM2_DOMAIN1_1_DELTA.tempforeach())
                {
                    var l_partkey = entry.key;
                    var v10 = entry.value;
                    var l3 = (QUERY17LINEITEM1_L1_1.get(l_partkey) * 0.005);

                    foreach (var entry1 in  QUERY17LINEITEM2_P_1.slice(0,l_partkey).tempforeach())
                    {
                        var k11 = entry1.key;
                        var v11 = entry1.value;
                        var l_quantity = k11._2;

                        if (v10 != 0 && l3 > l_quantity) agg6 += (v11 * QUERY17LINEITEM1.get(l_partkey));

                    }
                }

                QUERY17 += (agg4 + (agg5 + (agg6 * -1L)));
   
                foreach (var entry in QUERY17LINEITEM2_L1_3_DELTA.tempforeach()) 
                    QUERY17LINEITEM1_L1_1.add(entry.key, entry.value);
              

                foreach (var entry in QUERY17LINEITEM1_DELTA.tempforeach()) 
                {
                    var k13 = entry.key;
                    var v13 = entry.value;
                    var l_partkey = k13._1;
                    var l_quantity = k13._2;
                    QUERY17LINEITEM2_P_1.add(new TLD17a(l_partkey,l_quantity),v13);
                }

                var output = this.Output.GetBufferForTime(message.time);
                output.Send(QUERY17);
            }

            public override void OnReceive2(Message<PART17a, Epoch> message)
            {
                QUERY17PART1_DELTA.clear();
                M3MapBase<long, long> agg7 = new M3MapBase<long, long>();

                for (int i = 0; i < message.length; i++)
                {
                    PART17a part = message.payload[i];
                    agg7.add(part.partkey, part.function);
                    QUERY17PART1_DELTA.add(part.partkey, part.function);
                }

                var agg8 = 0.0;

                foreach (var entry in QUERY17PART1_DELTA.tempforeach())
                {
                    var l_partkey = entry.key;
                    var v16 = entry.value;
                    var l4 = (QUERY17LINEITEM1_L1_1.get(l_partkey) * 0.005);

                    foreach (var entry2 in QUERY17LINEITEM2_P_1.slice(0,l_partkey).tempforeach())
                    {
                        var k17 = entry2.key;
                        var v17 = entry2.value;
                        var l_quantity = k17._2;
                        if (l4 > l_quantity) 
                            agg8 += (v16 * v17);
                    }
                }
  
                QUERY17 += agg8;
                foreach (var entry in QUERY17PART1_DELTA.tempforeach())
                {
                    QUERY17LINEITEM1.add(entry.key, entry.value);
                }

                var output = this.Output.GetBufferForTime(message.time);
                output.Send(QUERY17);

            }
        }

        public class MySliceFunction : Function1<TLD17a, object>
        {
            public override object apply(TLD17a t)
            {
                return t._1;
            }
        }
    }
}
