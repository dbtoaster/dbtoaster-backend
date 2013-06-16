CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
csv ();

SELECT r2.C FROM (
  SELECT r1.A, COUNT(*) AS C FROM R r1 GROUP BY r1.A
) r2;
