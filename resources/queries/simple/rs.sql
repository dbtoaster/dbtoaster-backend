CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;
  
CREATE STREAM S(B int, C int) 
  FROM FILE 'examples/data/simple/s.dat' LINE DELIMITED csv;

SELECT sum(A*C), sum(A+C) FROM R,S WHERE R.B=S.B;
