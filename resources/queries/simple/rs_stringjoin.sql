CREATE STREAM R(A int, B string) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
  CSV ();

CREATE STREAM S(B string, C int) 
  FROM FILE 'examples/data/simple/s.dat' LINE DELIMITED
  CSV ();

SELECT r.A, SUM(s.C)
FROM R r, S s
WHERE r.B = S.B
GROUP BY r.A;
