# Multi-thread Parallel
under construction

This is a multi-thread parallel extension for N-Prolog. N-Prolog is oriented toward computational experiments and aims to explore the potential of Prolog in medium-scale parallel computation with distributed parallel.


# Spec

    mt_create(N): 

    mt-and([p0,p1, ...,pn]): It executes the predicates from P0 to PN in parallel. If all of them return YES, it returns YES. If even one returns NO, it returns NO.

    mt_or([p0,p1, ...,n]): It executes the predicates from P0 to PN in parallel. If any one of them returns YES, it interrupts the other computations and returns YES.

    mt_prove(Nth,Pred): Prove Predicate on the Nth thread for testing.

    mt_close: 
   

# Example

```
mt_create(2).

foo(0).
foo(N) :- write(N),N1 is N-1,foo(N1).

boo(0).
boo(N) :- write(N),N1 is N-1,boo(N1).

 mt_and([foo(2),boo(3)]).
```
[MT](para3.png)
