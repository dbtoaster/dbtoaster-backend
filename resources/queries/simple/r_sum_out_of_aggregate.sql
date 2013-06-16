CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
CSV ();

SELECT 1+SUM(A) FROM R;
