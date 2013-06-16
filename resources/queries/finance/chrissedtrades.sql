CREATE STREAM bids(t FLOAT, id INT, broker_id INT, volume FLOAT, price FLOAT)
  FROM FILE '@@DATA@@.csv'
  LINE DELIMITED orderbook (book := 'bids', brokers := '10', 
                            deterministic := 'yes');

CREATE STREAM asks(t FLOAT, id INT, broker_id INT, volume FLOAT, price FLOAT)
  FROM FILE '@@DATA@@.csv'
  LINE DELIMITED orderbook (book := 'asks', brokers := '10', 
                            deterministic := 'yes');

SELECT b.broker_id, SUM(a.foo + b.foo) AS mst
FROM (SELECT b0.broker_id, SUM(-1 * b0.price * b0.volume * ba.cnt) AS foo
      FROM bids b0,
           (SELECT COUNT(*) AS cnt FROM asks) ba
      WHERE 0.25 * (SELECT SUM(b1.volume) FROM bids b1) >
                   (SELECT SUM(b2.volume) FROM bids b2
                    WHERE b2.price > b0.price)
      GROUP BY b0.broker_id
     ) b,
     (SELECT ab.broker_id, SUM(aa.foo) AS foo
      FROM (SELECT SUM(a0.price * a0.volume) AS foo
            FROM asks a0
            WHERE 0.25 * (SELECT SUM(a1.volume) FROM asks a1) >
                         (SELECT SUM(a2.volume) FROM asks a2
                          WHERE a2.price > a0.price)
           ) aa,
           bids ab
      GROUP BY ab.broker_id
     ) a
WHERE a.broker_id = b.broker_id
GROUP BY b.broker_id;
