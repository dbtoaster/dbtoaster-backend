using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;


namespace CodeGenTesting.Query19Vertex
{
    public static class ExtensionMethods
    {
        public static Stream<double, Epoch> query19Revenue(this Stream<LINEITEM19, Epoch> lineitems, Stream<PART19, Epoch> parts)
        {
            return Foundry.NewBinaryStage(lineitems, parts, (i, s) => new Query19Vertex(i, s), x => x.GetHashCode(), y => y.GetHashCode(), null, "Query19 Revenue");
        }

        public class Query19Vertex : BinaryVertex<LINEITEM19, PART19, double, Epoch>
        {
            
            //Dictionary<Query19TLLLLDDDDSSAAASSS, long> DELTA_LINEITEM = new Dictionary<Query19TLLLLDDDDSSAAASSS,long>();
            //Dictionary<Query19TLSSSSLSDS, long> DELTA_PART = new Dictionary<Query19TLSSSSLSDS,long>();
            M3MapBase<Query19TLSLS, long> REVENUEPART1_DELTA = new M3MapBase<Query19TLSLS,long>();
            M3MapBase<Query19TLDSS, double> REVENUEPART1 = new M3MapBase<Query19TLDSS,double>();
            M3MapBase<Query19TLDSS, double> REVENUELINEITEM1_DELTA = new M3MapBase<Query19TLDSS,double>();
            M3MapBase<Query19TLSLS, long> REVENUELINEITEM1 = new M3MapBase<Query19TLSLS,long>();
  
            string c17 = "LG PACK";
            string c14 = "Brand#34";
              string c2 = "AIR";
              string c13 = "MED PACK";
              string c18 = "LG PKG";
              string c12 = "MED PKG";
              string c5 = "SM CASE";
              string c3 = "AIR REG";
              string c7 = "SM PACK";
              string c11 = "MED BOX";
              string c15 = "LG CASE";
              string c1 = "DELIVER IN PERSON";
              string c6 = "SM BOX";
              string c9 = "Brand#23";
              string c4 = "Brand#12";
              string c16 = "LG BOX";
              string c8 = "SM PKG";
              string c10 = "MED BAG";    
            
            public override void OnReceive1(Message<LINEITEM19, Epoch> message)
            {
                double REVENUE = 0.0;

                REVENUELINEITEM1_DELTA.clear();
                M3MapBase<Query19TLDSS, double> agg1 = new M3MapBase<Query19TLDSS, double>();
    
                for (int i = 0; i < message.length; i++)
                {
                    LINEITEM19 lineitem = message.payload[i];
                    agg1.add(new Query19TLDSS(lineitem.partkey,
                        lineitem.quantity,
                        lineitem.shipinstruct,
                        lineitem.shipmode), (lineitem.function * (lineitem.extendedprice * (1L + (-1L * lineitem.discount)))));
                }

                foreach (var pair in agg1.tempforeach()) {
                    Query19TLDSS k2 = pair.key;
                    double v2 = pair.value;
                    var l_partkey = k2._1;
                    var l_quantity = k2._2;
                    var l_shipinstruct = k2._3;
                    var l_shipmode = k2._4;

                    REVENUELINEITEM1_DELTA.add(new Query19TLDSS(l_partkey, l_quantity, l_shipinstruct, l_shipmode), v2);
                }

                double agg2 = 0.0;
                foreach(var pair in REVENUELINEITEM1_DELTA.tempforeach()) {
                    Query19TLDSS k3 = pair.key;
                    double v3 = pair.value;
                    var l_partkey = k3._1;
                    var l_quantity = k3._2;
                    var l_shipinstruct = k3._3;
                    var l_shipmode = k3._4;

                    foreach(var pair2 in REVENUELINEITEM1.tempforeach()) {
                        Query19TLSLS k4 = pair2.key;
                        long v4 = pair2.value;
                        var p_partkey = k4._1;
                        var p_brand = k4._2;
                        var p_size = k4._3;
                        var p_container = k4._4;
                        long l1 = (/*if */(p_partkey == l_partkey && l_shipinstruct == c1 && p_size >= 1L) ? (((/*if */(l_shipmode == c2) ? 1L : 0L) + (/*if */(l_shipmode == c3) ? 1L : 0L)) * ((/*if */(p_brand == c4 && l_quantity >= 1L && 11L >= l_quantity && 5L >= p_size) ? ((/*if */(p_container == c5) ? 1L : 0L) + ((/*if */(p_container == c6) ? 1L : 0L) + ((/*if */(p_container == c7) ? 1L : 0L) + (/*if */(p_container == c8) ? 1L : 0L)))) : 0L) + ((/*if */(p_brand == c9 && l_quantity >= 10L && 20L >= l_quantity && 10L >= p_size) ? ((/*if */(p_container == c10) ? 1L : 0L) + ((/*if */(p_container == c11) ? 1L : 0L) + ((/*if */(p_container == c12) ? 1L : 0L) + (/*if */(p_container == c13) ? 1L : 0L)))) : 0L) + (/*if */(p_brand == c14 && l_quantity >= 20L && 30L >= l_quantity && 15L >= p_size) ? ((/*if */(p_container == c15) ? 1L : 0L) + ((/*if */(p_container == c16) ? 1L : 0L) + ((/*if */(p_container == c17) ? 1L : 0L) + (/*if */(p_container == c18) ? 1L : 0L)))) : 0L)))) : 0L);
                        if (l1 > 0L)
                            agg2 += (v3 * v4);   
                    }
                }
                
                REVENUE += agg2;
                foreach(var pair in REVENUELINEITEM1_DELTA.tempforeach()) {
                    Query19TLDSS k5 = pair.key;
                    double v5 = pair.value;
                    var l_partkey = k5._1;
                    var l_quantity = k5._2;
                    var l_shipinstruct = k5._3;
                    var l_shipmode = k5._4;
                    Query19TLDSS tlds = new Query19TLDSS(l_partkey, l_quantity, l_shipinstruct, l_shipmode);
                    /*if (REVENUEPART1.(tlds))
                    {
                        //Console.WriteLine("Copy key : " + tlds.GetHashCode());
                        //Console.WriteLine(tlds);
                        //Console.WriteLine(REVENUEPART1[tlds]);
                        continue;
                    }*/
                    REVENUEPART1.add(tlds, v5);
                }

                var output = this.Output.GetBufferForTime(message.time);
                output.Send(REVENUE);
            }

            public override void OnReceive2(Message<PART19, Epoch> message)
            {
                double REVENUE = 0.0;
                REVENUEPART1_DELTA.clear();
                M3MapBase<Query19TLSLS, long> agg3 = new M3MapBase<Query19TLSLS,long>();
                
                for (int i = 0; i < message.length; i++)
                {
                    PART19 part = message.payload[i];
                    agg3.add(new Query19TLSLS(part.partkey, part.brand, part.size, part.container), part.function);
                }

                foreach (var pair in agg3.tempforeach()) {
                    var k7 = pair.key;
                    var v7 = pair.value;
                    var p_partkey = k7._1;
                    var p_brand = k7._2;
                    var p_size = k7._3;
                    var p_container = k7._4;
                    REVENUEPART1_DELTA.add(new Query19TLSLS(p_partkey,p_brand,p_size,p_container),v7);  
                }

                
                double agg4 = 0.0;
                foreach(var pair in REVENUEPART1_DELTA.tempforeach()) {
                    var k8 = pair.key;
                    var v8 = pair.value;
                    var p_partkey = k8._1;
                    var p_brand = k8._2;
                    var p_size = k8._3;
                    var p_container = k8._4;

                    foreach(var pair2 in REVENUEPART1.tempforeach()) {
                        var k9 = pair2.key;
                        var v9 = pair2.value;
                        var l_partkey = k9._1;
                        var l_quantity = k9._2;
                        var l_shipinstruct = k9._3;
                        var l_shipmode = k9._4;

                        long l2 = (/*if */(p_partkey == l_partkey && l_shipinstruct == c1 && p_size >= 1L) ? (((/*if */(l_shipmode == c2) ? 1L : 0L) + (/*if */(l_shipmode == c3) ? 1L : 0L)) * ((/*if */(p_brand == c4 && l_quantity >= 1L && 11L >= l_quantity && 5L >= p_size) ? ((/*if */(p_container == c5) ? 1L : 0L) + ((/*if */(p_container == c6) ? 1L : 0L) + ((/*if */(p_container == c7) ? 1L : 0L) + (/*if */(p_container == c8) ? 1L : 0L)))) : 0L) + ((/*if */(p_brand == c9 && l_quantity >= 10L && 20L >= l_quantity && 10L >= p_size) ? ((/*if */(p_container == c10) ? 1L : 0L) + ((/*if */(p_container == c11) ? 1L : 0L) + ((/*if */(p_container == c12) ? 1L : 0L) + (/*if */(p_container == c13) ? 1L : 0L)))) : 0L) + (/*if */(p_brand == c14 && l_quantity >= 20L && 30L >= l_quantity && 15L >= p_size) ? ((/*if */(p_container == c15) ? 1L : 0L) + ((/*if */(p_container == c16) ? 1L : 0L) + ((/*if */(p_container == c17) ? 1L : 0L) + (/*if */(p_container == c18) ? 1L : 0L)))) : 0L)))) : 0L);
                        if (l2 > 0L)
                        {
                            agg4 += (v8 * v9);
                            Console.WriteLine(v8 + " " + v9);
                        }
                    }
                }

                REVENUE += agg4;
                foreach(var pair in REVENUEPART1_DELTA.tempforeach()) {
                    var k10 = pair.key;
                    var v10 = pair.value;
                    var p_partkey = k10._1;
                    var p_brand = k10._2;
                    var p_size = k10._3;
                    var p_container = k10._4;
                    REVENUELINEITEM1.add(new Query19TLSLS(p_partkey,p_brand,p_size,p_container),v10);
                }

                var output = this.Output.GetBufferForTime(message.time);
                output.Send(REVENUE);
                //Console.WriteLine("Vertex data " + REVENUELINEITEM1);
                //Console.WriteLine("Vertex data " + REVENUEPART1);
                //Console.WriteLine();
            }

            public Query19Vertex(int index, Stage<Epoch> vertex) : base(index, vertex) { }
        }
    }
}
