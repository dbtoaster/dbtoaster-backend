CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
CSV ();

SELECT R1.* FROM R r1 NATURAL JOIN R r2;
