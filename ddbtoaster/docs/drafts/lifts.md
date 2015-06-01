# Problems with Lifts/Exists

*Note:* The term "classic semantics" in this document refers to the semantics currently implemented in alpha5, while "new semantics" refers to the semantics defined in the VLDBJ paper.

## Example queries

### Simple aggregate query

```
SELECT A, SUM(B) FROM R GROUP BY A;
```

Here, the problem with the classic semantics is that we are not able to distinguish between groups that have an aggregate that is 0 and groups that do not exist.
alpha5 currently generates the following calculus expression for this query:

```
__SQL_SUM_AGGREGATE_1:
AggSum([R_A], (R(R_A, R_B) * R_B))
```

We would actually need an `EXISTS(R(R_A, R_B))` in front of the expression for it to be correct.

### Not exists

```
SELECT A FROM R WHERE NOT EXISTS (SELECT R2.B FROM R AS R2 WHERE R2.B < R.A);
```

This is a query that we can not express using the new semantics.
The problem is that we can not check if something has multiplicity 0 because 0 multiplicity is "contagous".
alpha5 produces the following calculus expression:

```
COUNT:
AggSum([R_A],
  (R(R_A, R_B, R_C) *
    AggSum([],
      ((__domain_1 ^= AggSum([], (R(R2_A, R2_B, R2_C) * {R2_B < R_A}))) *
        (__domain_1 ^= 0)))))
```

A similar problem arises with the SQL operator `ALL`:

```
SELECT A FROM R WHERE R.A < ALL (SELECT R2.B FROM R AS R2);
```

This query essentially gets translated to a `NOT EXISTS` query with the inverse of the predicate:

```
COUNT:
AggSum([R_A],
  (R(R_A, R_B, R_C) *
    AggSum([],
      ((__domain_1 ^= AggSum([], (R(R2_A, R2_B, R2_C) * {R_A >= R2_B}))) *
        (__domain_1 ^= 0)))))
```
