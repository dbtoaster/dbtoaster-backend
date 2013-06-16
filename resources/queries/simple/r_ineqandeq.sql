CREATE STREAM R(A int, B int)
FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
CSV ();

SELECT SUM(A) FROM R WHERE A = B AND A <= B;
