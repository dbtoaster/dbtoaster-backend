using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting.Query19Reducer
{

    public static class ExtensionMethods
    {
        public static Stream<double, Epoch> Query19RevenueReduce(this Stream<double, Epoch> stream)
        {
            return stream.NewUnaryStage(
                (i, s) => new Query6ReducerVertex(i, s),
                x => 1,
                null, "Revenue");
        }

        internal class Query6ReducerVertex : UnaryVertex<double, double, Epoch>
        {
            double REVENUE = 0;

            public override void OnReceive(Message<double, Epoch> message)
            {
                this.NotifyAt(message.time);
                for (int i = 0; i < message.length; i++)
                {
                    double partial_results = message.payload[i];
                    REVENUE += partial_results;
                }
            }

            public override void OnNotify(Epoch time)
            {
                var output = this.Output.GetBufferForTime(time);
                output.Send(REVENUE);
            }

            public Query6ReducerVertex(int index, Stage<Epoch> stage) : base(index, stage) { }
        }
    }
}
