CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
  CSV ();

CREATE STREAM S(B int, C int) 
  FROM FILE 'examples/data/simple/s.dat' LINE DELIMITED
  CSV ();

SELECT A FROM R r, (SELECT s2.B, COUNT(*) AS CNT FROM S s2 GROUP BY s2.B) s WHERE r.B = s.B AND r.A < CNT;
