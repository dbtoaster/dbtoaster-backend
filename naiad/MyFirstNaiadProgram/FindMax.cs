using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting.FindMax
{

    public static class ExtensionMethods
    {

        public static Stream<Pair<TRecord, Int64>, Epoch> MaxCount<TRecord>(this Stream<TRecord, Epoch> stream)
        {
            return stream.NewUnaryStage((i, s) => new MaxVertex<TRecord>(i, s), x => 1, null, "Count");
        }

        internal class MaxVertex<TRecord> : UnaryVertex<TRecord, Pair<TRecord, Int64>, Epoch>
        {
            private TRecord record;
            private int maxCount;
            Boolean changed = false;

            // Each batch of records of type TRecord we receive, we must update counts.
            public override void OnReceive(Message<TRecord, Epoch> message)
            {
                Console.WriteLine("In notify");
                this.NotifyAt(message.time);

                // a message contains length valid records.
                for (int i = 0; i < message.length; i++)
                {
                    var data = message.payload[i];
                    string value = data.ToString();
                    value = value.Substring(1, value.Length - 2);
                    int count = Int32.Parse(value.Split(new char[] { ' ' })[1]);
                    if (count > maxCount)
                    {
                        maxCount = count;
                        record = data;
                        changed = true;
                    }
                }
            }

            // once all records of an epoch are received, we should send the counts along.
            public override void OnNotify(Epoch time)
            {
                var output = this.Output.GetBufferForTime(time);

                if (changed)
                {
                    output.Send(new Pair<TRecord, Int64>(record, maxCount));
                    changed = false;
                }
            }

            // the UnaryVertex base class needs to know the index and stage of the vertex. 
            public MaxVertex(int index, Stage<Epoch> stage) : base(index, stage) { }
        }
    }
}
