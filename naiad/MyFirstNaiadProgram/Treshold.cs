using System.Collections.Generic;
using Microsoft.Research.Naiad;
using Microsoft.Research.Naiad.Dataflow;
using Microsoft.Research.Naiad.Dataflow.StandardVertices;

namespace Threshold
{
    public static class ExtensionMethods
    {
        class ThresholdVertex<TRecord, TTime> : UnaryVertex<TRecord, TRecord, TTime> where TTime : Time<TTime>
        {
            private readonly int threshold;

            // Per-time counts for each record.
            private readonly Dictionary<TTime, Dictionary<TRecord, int>> counts;

            public override void OnReceive(Message<TRecord, TTime> message)
            {
                var time = message.time;

                // Get the state for this time.
                Dictionary<TRecord, int> countsForTime;
                if (!this.counts.TryGetValue(time, out countsForTime))
                {
                    countsForTime = new Dictionary<TRecord, int>();
                    this.counts[time] = countsForTime;

                    // Request a notification when we are finished with this time.
                    this.NotifyAt(time);
                }

                // We use a time-specific buffer to send records.
                var outputByTime = this.Output.GetBufferForTime(time);

                // For each record in the message.
                for (int i = 0; i < message.length; ++i)
                {
                    var record = message.payload[i];

                    // Read-modify-update the current count for record.
                    int currentCount = 0;
                    countsForTime.TryGetValue(record, out currentCount);
                    currentCount = currentCount + 1;
                    countsForTime[record] = currentCount;

                    // Send record only when it crosses the threshold.
                    if (currentCount == threshold)
                    {
                        outputByTime.Send(record);
                    }
                }
            }

            public override void OnNotify(TTime time)
            {
                // Release the state associated with the given time.
                this.counts.Remove(time);
            }

            public ThresholdVertex(int index, Stage<TTime> stage, int threshold)
                : base(index, stage)
            {
                this.threshold = threshold;
                this.counts = new Dictionary<TTime, Dictionary<TRecord, int>>();
            }
        }

        public static Stream<TRecord, TTime> Threshold<TRecord, TTime>(this Stream<TRecord, TTime> input, int threshold)
            where TTime : Time<TTime>
        {
            return input.NewUnaryStage((i, s) => new ThresholdVertex<TRecord, TTime>(i, s, threshold),
                x => x.GetHashCode(), x => x.GetHashCode(), "Threshold");
        }

    }
}
