CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
CSV ();

SELECT * FROM R r2 WHERE r2.B < ALL (SELECT SUM(r1.A) FROM R r1);
