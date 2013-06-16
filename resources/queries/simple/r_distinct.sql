CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;

SELECT A, B FROM R;

SELECT DISTINCT A, B FROM R;
