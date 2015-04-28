using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Input;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace CodeGenTesting.Query6Vertex
{
    public static class ExtensionMethods
    {
        public static Stream<double, Epoch> StreamingRevenue(this Stream<LINEITEM, Epoch> stream)
        {
            return stream.NewUnaryStage(
                (i, s) => new Query6Vertex(i, s), 
                x => x.GetHashCode(), 
                null, "Revenue");
        }

        internal class Query6Vertex: UnaryVertex<LINEITEM, double, Epoch>
        {
            double REVENUE = 0;
            DateTime c1 = new DateTime(1994, 1, 1);
            DateTime c2 = new DateTime(1995, 1, 1);

            public override void OnReceive(Message<LINEITEM, Epoch> message)
            {
                double agg1 = 0;
                for (int i = 0; i < message.length; i++)
                {
                    LINEITEM lineitem = message.payload[i];
                    
                        if (lineitem.shipdate >= c1 &&
                            c2 > lineitem.shipdate &&
                            lineitem.discount >= 0.05 &&
                            0.07 >= lineitem.discount &&
                            24L > lineitem.quantity)
                            agg1 += (lineitem.function * (lineitem.extendedprice * lineitem.discount));

                }
                REVENUE = agg1;
                var output = this.Output.GetBufferForTime(message.time);
                output.Send(REVENUE);
            }

            public override void OnNotify(Epoch time)
            {
                var output = this.Output.GetBufferForTime(time);
                output.Send(REVENUE);
            }

            public Query6Vertex(int index, Stage<Epoch> stage) : base(index, stage) { }
        }
    }
}
