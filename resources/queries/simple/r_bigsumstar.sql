CREATE STREAM R(A int, B int) 
  FROM FILE 'examples/data/simple/r.dat' LINE DELIMITED csv;

SELECT r1.A, SUM(r1.B + r2.B + r3.B + r4.B)
FROM R r1, R r2, R r3, R r4
WHERE r1.A = r2.A
  AND r2.A = r3.A
  AND r3.A = r4.A
GROUP BY r1.A;
