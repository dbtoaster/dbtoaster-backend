CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
  csv ();

SELECT * FROM (SELECT COUNT(*) FROM R) n;
