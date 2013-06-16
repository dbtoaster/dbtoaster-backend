CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
csv ();

SELECT * FROM R r2 WHERE r2.B IN (SELECT r1.A FROM R r1);
