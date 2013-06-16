CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;

SELECT SUM(1) FROM (SELECT SUM(1) FROM R) r;
