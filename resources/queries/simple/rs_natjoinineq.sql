CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
CSV ();

CREATE STREAM S(B int, C int)
FROM FILE 'examples/data/simple/s.dat' LINE DELIMITED
CSV ();

SELECT * FROM R NATURAL JOIN S WHERE R.A < S.C;
