CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;

SELECT * FROM R WHERE A IN LIST (1, 2, 3);
SELECT * FROM R WHERE NOT A IN LIST (1, 2, 3);
