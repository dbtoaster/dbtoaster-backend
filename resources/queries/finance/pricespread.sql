CREATE STREAM bids(t FLOAT, id INT, broker_id INT, volume FLOAT, price FLOAT)
  FROM FILE '@@DATA@@.csv'
  LINE DELIMITED orderbook (book := 'bids', brokers := '10', 
                            deterministic := 'yes');

CREATE STREAM asks(t FLOAT, id INT, broker_id INT, volume FLOAT, price FLOAT)
  FROM FILE '@@DATA@@.csv'
  LINE DELIMITED orderbook (book := 'asks', brokers := '10', 
                            deterministic := 'yes');

SELECT SUM(a.price + (-1 * b.price)) AS psp 
FROM bids b, asks a
WHERE ( b.volume > 0.0001 * (SELECT SUM(b1.volume) FROM bids b1) )
  AND ( a.volume > 0.0001 * (SELECT SUM(a1.volume) FROM asks a1) );
