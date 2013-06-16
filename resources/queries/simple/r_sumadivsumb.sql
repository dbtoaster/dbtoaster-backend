CREATE STREAM R(A float, B float) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED
  CSV ();

SELECT SUM(A)/(1+SUM(B)) FROM R;
