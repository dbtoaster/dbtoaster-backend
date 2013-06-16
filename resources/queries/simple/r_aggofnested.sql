CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;

SELECT COUNT(*) FROM (SELECT * FROM R) n;
