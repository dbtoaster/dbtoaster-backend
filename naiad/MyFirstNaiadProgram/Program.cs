using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Input;
using Threshold;
using CodeGenTesting.FindMax;
using System.Diagnostics;
using CodeGenTesting.Query19Reducer;
using CodeGenTesting.Query19Vertex;
using CodeGenTesting.Query6Vertex;
using CodeGenTesting.Query6ReducerVertex;
using CodeGenTesting.Query1Vertex;
using CodeGenTesting.Query17a;
using CodeGenTesting.Query4;

namespace CodeGenTesting
{
    class Program
    {
        static void Main(string[] args)
        {
            //testMap();
            testQuery4(args);
            //double L = 201.0 * 0.005 - 0.005 * 1;
            //Console.WriteLine(L);
            Console.ReadLine();
            //findMaxTest(args);
        }

        static void testMap()
        {
            Function1<test, object>[] proj = new Function1<test, object>[1];
            proj[0] = new MyFunction();
            M3MapBase<test, string> map = new M3MapBase<test, string>("", false, proj);
            test t1 = new test(1, "a", 1.2);
            test t2 = new test(2, "b", 2.3);
            test t3 = new test(2, "c", 2.1);
            map.put(t1, "t1");
            map.put(t2, "t2");
            map.put(t3, "t3");

            M3Map<test, string> sl = map.slice(0, (2));
            sl.add(t2, "modify t2");

            Console.WriteLine(sl.size());
            foreach (Entry<test, string> tmp in sl.tempforeach())
                Console.WriteLine(tmp.key + " " + tmp.value);

            Console.WriteLine("*****");

            foreach (Entry<test, string> tmp in map.tempforeach())
                Console.WriteLine(tmp.key + " " + tmp.value);
        }

        static void testQuery1(string[] args) {
            using (var computation = NewComputation.FromArgs(ref args))
            {

                var source = new BatchedDataSource<LINEITEM1>();
                var query6 = computation.NewInput(source).query1SUM_QTY();
                Dictionary<Query1TSS, double> SUM_QTY = new Dictionary<Query1TSS, double>();
                query6.Subscribe(list =>
                {

                    //Console.WriteLine("New Result : ");
                    foreach (M3MapBase<Query1TSS, double> element in list)
                    {
                        foreach (var pair in element.tempforeach())
                        {
                            if (SUM_QTY.ContainsKey(pair.key))
                            {
                                SUM_QTY[pair.key] = pair.value;
                            }
                            else
                            {
                                SUM_QTY.Add(pair.key, pair.value);
                            }
                        }
                    }
                });


                int batchSize = 10;
                LINEITEM1[] data = getLineItems1();
                for (int i = 0; i < data.Length; )
                {
                    int nextSize = Math.Min(data.Length - i, batchSize);
                    LINEITEM1[] nextBatch = new LINEITEM1[nextSize];
                    // Console.WriteLine(i + " " + nextSize);
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = data[i++];

                    source.OnNext(nextBatch);
                }
                computation.Activate();       // activate the execution of this graph (no new stages allowed).
                source.OnCompleted();   // signal the end of the input.
                computation.Join();           // waits until the graph has finished executing.

                // print resutl here;
                foreach (var pair in SUM_QTY)
                {
                    Console.WriteLine(pair.Key + " " + pair.Value);
                }
            }
        }
 
        static void testQuery4(string[] args)
        {
            using (var computation = NewComputation.FromArgs(ref args))
            {
                var lineitemSource = new BatchedDataSource<LINEITEM4>();
                var orderSource = new BatchedDataSource<ORDERS4>();

               // computation.NewInput(lineitemSource).
                //    query17a(computation.NewInput(partSource)).
                //    Subscribe(list => { foreach (var element in list) Console.WriteLine("QUERY17a : " + element); });
                
                Dictionary<string, long> COUNT_ORDER = new Dictionary<string, long>();
                computation.NewInput(lineitemSource).
                query4(computation.NewInput(orderSource)).Subscribe(list =>
                {

                    //Console.WriteLine("New Result : ");
                    foreach (M3MapBase<string, long> element in list)
                    {
                        foreach (var pair in element.tempforeach())
                        {
                            if (COUNT_ORDER.ContainsKey(pair.key))
                            {
                                COUNT_ORDER[pair.key] = pair.value;
                            }
                            else
                            {
                                COUNT_ORDER.Add(pair.key, pair.value);
                            }
                        }
                    }
                });


                int batchSize = 100;

                // send Lineitems
                LINEITEM4[] data = getLineItems4();
                for (int i = 0; i < data.Length; )
                {
                    int nextSize = Math.Min(data.Length - i, batchSize);
                    LINEITEM4[] nextBatch = new LINEITEM4[nextSize];
                    // Console.WriteLine(i + " " + nextSize);
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = data[i++];

                    lineitemSource.OnNext(nextBatch);
                    orderSource.OnNext();
                }

                // send ORDERS
                ORDERS4[] orders = getOrders4();
                for (int i = 0; i < orders.Length; )
                {
                    int nextSize = Math.Min(orders.Length - i, batchSize);
                    ORDERS4[] nextBatch = new ORDERS4[nextSize];
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = orders[i++];

                    lineitemSource.OnNext();
                    orderSource.OnNext(nextBatch);
                }


                computation.Activate();       // activate the execution of this graph (no new stages allowed).
                lineitemSource.OnCompleted();   // signal the end of the input.
                orderSource.OnCompleted();
                computation.Join();           // waits until the graph has finished executing.

                foreach (var pair in COUNT_ORDER)
                {
                    Console.WriteLine(pair.Key + " " + pair.Value);
                }
                Console.WriteLine("Finished");
            }
        }

        static void testQuery17a(string[] args)
        {
            using (var computation = NewComputation.FromArgs(ref args))
            {
                var lineitemSource = new BatchedDataSource<LINEITEM17a>();
                var partSource = new BatchedDataSource<PART17a>();

                computation.NewInput(lineitemSource).
                    query17a(computation.NewInput(partSource)).
                    Subscribe(list => { foreach (var element in list) Console.WriteLine("QUERY17a : " + element); });


                int batchSize = 100;

                // send Lineitems
                LINEITEM17a[] data = getLineItems17a();
                for (int i = 0; i < data.Length; )
                {
                    int nextSize = Math.Min(data.Length - i, batchSize);
                    LINEITEM17a[] nextBatch = new LINEITEM17a[nextSize];
                    // Console.WriteLine(i + " " + nextSize);
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = data[i++];

                    lineitemSource.OnNext(nextBatch);
                    partSource.OnNext();
                }

                // send PARTS
                PART17a[] parts = getParts17a();
                for (int i = 0; i < parts.Length; )
                {
                    int nextSize = Math.Min(parts.Length - i, batchSize);
                    PART17a[] nextBatch = new PART17a[nextSize];
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = parts[i++];

                    lineitemSource.OnNext();
                    partSource.OnNext(nextBatch);
                }


                computation.Activate();       // activate the execution of this graph (no new stages allowed).
                lineitemSource.OnCompleted();   // signal the end of the input.
                partSource.OnCompleted();
                computation.Join();           // waits until the graph has finished executing.
            }
        }
        static void testQuery19(string[] args) {
            using (var computation = NewComputation.FromArgs(ref args))
            {
                var lineitemSource = new BatchedDataSource<LINEITEM19>();
                var partSource = new BatchedDataSource<PART19>();

                computation.NewInput(lineitemSource).
                    query19Revenue(computation.NewInput(partSource)).
                    Query19RevenueReduce().
                    Subscribe(list => { foreach (var element in list) Console.WriteLine("Revenue : " + element); });


                int batchSize = 100;

                // send Lineitems
                LINEITEM19[] data = getLineItems19();
                for (int i = 0; i < data.Length; )
                {
                    int nextSize = Math.Min(data.Length - i, batchSize);
                    LINEITEM19[] nextBatch = new LINEITEM19[nextSize];
                    // Console.WriteLine(i + " " + nextSize);
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = data[i++];

                    lineitemSource.OnNext(nextBatch);
                    partSource.OnNext();
                }

                // send PARTS
                PART19[] parts = getParts19();
                for (int i = 0; i < parts.Length; )
                {
                    int nextSize = Math.Min(parts.Length - i, batchSize);
                    PART19[] nextBatch = new PART19[nextSize];
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = parts[i++];

                    lineitemSource.OnNext();
                    partSource.OnNext(nextBatch);
                }


                    computation.Activate();       // activate the execution of this graph (no new stages allowed).
                lineitemSource.OnCompleted();   // signal the end of the input.
                partSource.OnCompleted();
                computation.Join();           // waits until the graph has finished executing.
            }
        }
        static void testQuery6(string[] args)
        {
            using (var computation = NewComputation.FromArgs(ref args))
            {

                var source = new BatchedDataSource<LINEITEM>();
                var query6 = computation.NewInput(source).StreamingRevenue().StreamingRevenueReduce();
                query6.Subscribe(list => { foreach (var element in list) Console.WriteLine("Revenue : " + element); });


                int batchSize = 10;
                LINEITEM[] data = getLineItems();
                for (int i = 0; i < data.Length; )
                {
                    int nextSize = Math.Min(data.Length - i, batchSize);
                    LINEITEM[] nextBatch = new LINEITEM[nextSize];
                   // Console.WriteLine(i + " " + nextSize);
                    for (int j = 0; j < nextSize; j++)
                        nextBatch[j] = data[i++];

                    source.OnNext(nextBatch);
                }
                computation.Activate();       // activate the execution of this graph (no new stages allowed).
                source.OnCompleted();   // signal the end of the input.
                computation.Join();           // waits until the graph has finished executing.
            }
        }
        public static LINEITEM[] getLineItems()
        {

            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\lineitem.csv");
            LINEITEM[] items = new LINEITEM[lines.Length];
            int i = 0;
            foreach (string s in lines) {
                string[] cols = s.Split(new char[]{'|'});
                items[i] = new LINEITEM();
                items[i].function = 1;
                items[i].orderkey = Int64.Parse(cols[0]);
                items[i].partkey = Int64.Parse(cols[1]);
                items[i].suppkey = Int64.Parse(cols[2]);
                items[i].linenumber = Int64.Parse(cols[3]);
                items[i].quantity = Int64.Parse(cols[4]);
                items[i].extendedprice = Double.Parse(cols[5]);
                items[i].discount = Double.Parse(cols[6]);
                items[i].tax = Double.Parse(cols[7]);
                items[i].returnflag = cols[8][0];
                items[i].linestatus = cols[9][0];
                string[] tmp = cols[10].Split(new char[] { '-' });
                items[i].shipdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                
                tmp = cols[11].Split(new char[] { '-' });
                items[i].commitdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[12].Split(new char[] { '-' });
                items[i].receiptdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                items[i].shipinstruct = cols[13];
                items[i].shipmode = cols[14];
                items[i].comment = cols[15];


                i++;
            }
            return items;
        }
        public static LINEITEM1[] getLineItems1()
        {

            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\lineitem.csv");
            LINEITEM1[] items = new LINEITEM1[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                items[i] = new LINEITEM1();
                items[i].function = 1;
                items[i].orderkey = Int64.Parse(cols[0]);
                items[i].partkey = Int64.Parse(cols[1]);
                items[i].suppkey = Int64.Parse(cols[2]);
                items[i].linenumber = Int64.Parse(cols[3]);
                items[i].quantity = Int64.Parse(cols[4]);
                items[i].extendedprice = Double.Parse(cols[5]);
                items[i].discount = Double.Parse(cols[6]);
                items[i].tax = Double.Parse(cols[7]);
                items[i].returnflag = cols[8][0];
                items[i].linestatus = cols[9][0];
                string[] tmp = cols[10].Split(new char[] { '-' });
                items[i].shipdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[11].Split(new char[] { '-' });
                items[i].commitdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[12].Split(new char[] { '-' });
                items[i].receiptdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                items[i].shipinstruct = cols[13];
                items[i].shipmode = cols[14];
                items[i].comment = cols[15];


                i++;
            }
            return items;
        }
        public static LINEITEM19[] getLineItems19()
        {

            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\lineitem.csv");
            LINEITEM19[] items = new LINEITEM19[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                items[i] = new LINEITEM19();
                items[i].function = 1;
                items[i].orderkey = Int64.Parse(cols[0]);
                items[i].partkey = Int64.Parse(cols[1]);
                items[i].suppkey = Int64.Parse(cols[2]);
                items[i].linenumber = Int64.Parse(cols[3]);
                items[i].quantity = Int64.Parse(cols[4]);
                items[i].extendedprice = Double.Parse(cols[5]);
                items[i].discount = Double.Parse(cols[6]);
                items[i].tax = Double.Parse(cols[7]);
                items[i].returnflag = cols[8][0];
                items[i].linestatus = cols[9][0];
                string[] tmp = cols[10].Split(new char[] { '-' });
                items[i].shipdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[11].Split(new char[] { '-' });
                items[i].commitdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[12].Split(new char[] { '-' });
                items[i].receiptdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                items[i].shipinstruct = cols[13];
                items[i].shipmode = cols[14];
                items[i].comment = cols[15];


                i++;
            }
            return items;
        }
        public static PART19[] getParts19()
        {
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\part.csv");
            PART19[] parts = new PART19[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                parts[i] = new PART19();
                parts[i].function = 1;
                parts[i].partkey = Int32.Parse(cols[0]);
                parts[i].name = cols[1];
                parts[i].mfgr = cols[2];
                parts[i].brand = cols[3];
                parts[i].type = cols[4];
                parts[i].size = Int32.Parse(cols[5]);
                parts[i].container = cols[6];
                parts[i].retailprice = Double.Parse(cols[7]);
                parts[i].comment = cols[8];
        
                i++;
            }
            return parts;
        }

        public static LINEITEM17a[] getLineItems17a()
        {
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\lineitem.csv");
            LINEITEM17a[] items = new LINEITEM17a[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                items[i] = new LINEITEM17a();
                items[i].function = 1;
                items[i].orderkey = Int64.Parse(cols[0]);
                items[i].partkey = Int64.Parse(cols[1]);
                items[i].suppkey = Int64.Parse(cols[2]);
                items[i].linenumber = Int64.Parse(cols[3]);
                items[i].quantity = Int64.Parse(cols[4]);
                items[i].extendedprice = Double.Parse(cols[5]);
                items[i].discount = Double.Parse(cols[6]);
                items[i].tax = Double.Parse(cols[7]);
                items[i].returnflag = cols[8][0];
                items[i].linestatus = cols[9][0];
                string[] tmp = cols[10].Split(new char[] { '-' });
                items[i].shipdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[11].Split(new char[] { '-' });
                items[i].commitdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[12].Split(new char[] { '-' });
                items[i].receiptdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                items[i].shipinstruct = cols[13];
                items[i].shipmode = cols[14];
                items[i].comment = cols[15];


                i++;
            }
            return items;
        }

        public static PART17a[] getParts17a()
        {
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\part.csv");
            PART17a[] parts = new PART17a[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                parts[i] = new PART17a();
                parts[i].function = 1;
                parts[i].partkey = Int32.Parse(cols[0]);
                parts[i].name = cols[1];
                parts[i].mfgr = cols[2];
                parts[i].brand = cols[3];
                parts[i].type = cols[4];
                parts[i].size = Int32.Parse(cols[5]);
                parts[i].container = cols[6];
                parts[i].retailprice = Double.Parse(cols[7]);
                parts[i].comment = cols[8];

                i++;
            }
            return parts;
        }

        public static LINEITEM4[] getLineItems4()
        {
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\lineitem.csv");
            LINEITEM4[] items = new LINEITEM4[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                items[i] = new LINEITEM4();
                items[i].function = 1;
                items[i].orderkey = Int64.Parse(cols[0]);
                items[i].partkey = Int64.Parse(cols[1]);
                items[i].suppkey = Int64.Parse(cols[2]);
                items[i].linenumber = Int64.Parse(cols[3]);
                items[i].quantity = Int64.Parse(cols[4]);
                items[i].extendedprice = Double.Parse(cols[5]);
                items[i].discount = Double.Parse(cols[6]);
                items[i].tax = Double.Parse(cols[7]);
                items[i].returnflag = cols[8][0];
                items[i].linestatus = cols[9][0];
                string[] tmp = cols[10].Split(new char[] { '-' });
                items[i].shipdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[11].Split(new char[] { '-' });
                items[i].commitdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));

                tmp = cols[12].Split(new char[] { '-' });
                items[i].receiptdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                items[i].shipinstruct = cols[13];
                items[i].shipmode = cols[14];
                items[i].comment = cols[15];


                i++;
            }
            return items;
        }

        public static ORDERS4[] getOrders4()
        {
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\khgl\Desktop\codebase\MyFirstNaiadProgram\MyFirstNaiadProgram\orders.csv");
            ORDERS4[] orders = new ORDERS4[lines.Length];
            int i = 0;
            foreach (string s in lines)
            {
                string[] cols = s.Split(new char[] { '|' });
                orders[i] = new ORDERS4();
                orders[i].function = 1;
                orders[i].orderkey = Int32.Parse(cols[0]);
                orders[i].custkey = Int32.Parse(cols[1]);
                orders[i].orderstatus = cols[2][0];
                orders[i].totalprice = Double.Parse(cols[3]);                               
                string[] tmp = cols[4].Split(new char[] { '-' });
                orders[i].orderdate = new DateTime(Int16.Parse(tmp[0]), Int16.Parse(tmp[1]), Int16.Parse(tmp[2]));
                orders[i].orderpriority = cols[5];
                orders[i].clerk = cols[6];
                orders[i].shippriority = Int32.Parse(cols[7]);
                orders[i].comment = cols[8];

                i++;
            }
            return orders;
        }
        static void findMaxTest(string[] args) {
         using (var computation = NewComputation.FromArgs(ref args))
            {

                // 1. Make a new data source, to which we will supply strings.
                var source = new BatchedDataSource<string>();

                // 2. Attach source, and apply count extension method.
                var counts = computation.NewInput(source).StreamingCount();
                Stopwatch stopwatch = new Stopwatch();

                // 3. Subscribe to the resulting stream with a callback to print the outputs.
                counts.Subscribe(list => { foreach (var element in list) Console.WriteLine(element + " " + stopwatch.Elapsed); });

                string s = "a";
                for (int i = 0; i < 100; i++) {
                    //source.OnNext("a");
                    //source.OnNext("b");
                    //source.OnNext("c");
                    //source.OnNext("d");
                    //source.OnNext("e");
                    //source.OnNext("g");
                    s += " a";
                    s += " b";
                    s += " c";
                    s += " d";
                    s += " e";
                    s += " g";
                    s += " h";
                }
                source.OnNext(s.Split());
                stopwatch.Start();
                computation.Activate();       // activate the execution of this graph (no new stages allowed).

                //if (computation.Configuration.ProcessID == 0)
                //{
                //    // with our dataflow graph defined, we can start soliciting strings from the user.
                //    Console.WriteLine("Start entering lines of text. An empty line will exit the program.");
                //    Console.WriteLine("Naiad will display counts (and changes in counts) of words you type.");

                //    // read lines of input and hand them to the input, until an empty line appears.
                //    for (var line = Console.ReadLine(); line.Length > 0; line = Console.ReadLine())
                //        source.OnNext(line.Split());
                //}

                source.OnCompleted();   // signal the end of the input.
                computation.Join();           // waits until the graph has finished executing.
                Console.ReadLine();
            }
        }
    }

    public class test
    {
        public test (int a, string b, double c){
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public int a;
        public string b;
        public double c;
    }

    public class MyFunction : Function1<test, object>
    {

        public override object apply(test t)
        {
            return t.a;
        }
    }


}
