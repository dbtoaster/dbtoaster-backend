CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
  CSV ();

SELECT SUM((SELECT SUM(1) FROM R r2 WHERE r1.A = r2.A)) FROM R r1;
