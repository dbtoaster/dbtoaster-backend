using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting
{
    public static class ExtensionMethods
    {
        public static Random r = new Random();
        /// <summary>
        /// Counts records in the input stream, emitting new counts as they change.
        /// </summary>
        /// <typeparam name="TRecord">record type</typeparam>
        /// <param name="stream">input stream</param>
        /// <returns>stream of counts</returns>
        public static Stream<Pair<TRecord, Int64>, Epoch> StreamingCount<TRecord>(this Stream<TRecord, Epoch> stream)
        {
            return stream.NewUnaryStage((i, s) => new CountVertex<TRecord>(i, s), x => x.GetHashCode(), null, "Count");
        }

        /// <summary>
        /// A Naiad vertex for counting records of type S. Each epoch, changed counts are produced as output.
        /// </summary>
        internal class CountVertex<TRecord> : UnaryVertex<TRecord, Pair<TRecord, Int64>, Epoch>
        {
            // we maintain all the current counts, as well as recently changed keys.
            private readonly Dictionary<TRecord, Int64> Counts = new Dictionary<TRecord, long>();
            private readonly HashSet<TRecord> Changed = new HashSet<TRecord>();

            // Each batch of records of type TRecord we receive, we must update counts.
            public override void OnReceive(Message<TRecord, Epoch> message)
            {
                this.NotifyAt(message.time);

                // a message contains length valid records.
                for (int i = 0; i < message.length; i++)
                {
                    var data = message.payload[i];

                    if (!this.Counts.ContainsKey(data))
                        this.Counts[data] = 0;

                    this.Counts[data] += 1;

                    this.Changed.Add(data);
                }
            }

            // once all records of an epoch are received, we should send the counts along.
            public override void OnNotify(Epoch time)
            {
                //Console.WriteLine("Vertex : " + Counts.Select(x => x.Key + " = " + x.Value).Aggregate((s1, s2) => s1 + ";" + s2));
                var output = this.Output.GetBufferForTime(time);
                foreach (var record in this.Changed)
                    output.Send(new Pair<TRecord, Int64>(record, this.Counts[record]));

                // reset observed records
                this.Changed.Clear();
            }

            // the UnaryVertex base class needs to know the index and stage of the vertex. 
            public CountVertex(int index, Stage<Epoch> stage) : base(index, stage) { }
        }
    }
}
