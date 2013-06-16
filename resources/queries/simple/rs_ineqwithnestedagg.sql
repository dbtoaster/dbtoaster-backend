CREATE TABLE R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
  CSV ();

CREATE STREAM S(B int, C int) 
  FROM FILE 'examples/data/simple/s.dat' LINE DELIMITED
  CSV ();

SELECT A FROM R r, (SELECT S.B, COUNT(*) FROM S GROUP BY S.B) s2 WHERE r.B < s2.B;
