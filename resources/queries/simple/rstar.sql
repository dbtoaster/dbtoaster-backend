CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;

SELECT sum(1) 
FROM  R ra, R rb, R rc 
WHERE ra.A = rb.A AND
      rb.A = rc.A;

