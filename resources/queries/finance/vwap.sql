CREATE STREAM bids(t FLOAT, id INT, broker_id INT, volume FLOAT, price FLOAT)
  FROM FILE '@@DATA@@.csv'
  LINE DELIMITED orderbook (book := 'bids', brokers := '10', 
                            deterministic := 'yes');

SELECT SUM(b1.price * b1.volume) AS vwap
FROM   bids b1
WHERE  0.25 * 
       (SELECT SUM(b3.volume) FROM bids b3)
            >
       (SELECT SUM(b2.volume) FROM bids b2 WHERE b2.price > b1.price);
