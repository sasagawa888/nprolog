# Distributed Parallel
under construction

![DP](para.png)

# Invoke

npl -n on child machine terminal. N-Prolog runs with network mode.

N-Prolog on parent machine terminal. and dp_create/1 to establish TCP/IP between child Prolog.

# Spec

    npl -n: Launches child Prolog in network mode with the -n option.

    dp_create([IP0,IP1, …,IPn]): Provides IP addresse of child machines to establish TCP/IP communication with the parent Lisp. IP addresse is provided as atom. e.g. '178.1.166.2'

    dp-and([p0,p1, ...,pn]): It executes the predicates from P0 to PN in parallel. If all of them return YES, it returns YES. If even one returns NO, it returns NO.

    dp_or([p0,p1, ...,n]): It executes the predicates from P0 to PN in parallel. If any one of them returns YES, it interrupts the other computations and returns YES.

    dp_transfer(Fn): Transfers file Fn to all child machines from the parent machine.

    dp_compile(Fn): Compiles file Fn on both parent and child machines.

    dp_consult(Fn): Loads file Fn on both parent and child machines.

    dp_prove(Nth,Pred): Prove Predicate on the Nth child Prolog for testing.

    dp_report(Str): Display String on parent terminal.

    dp_close: Sends termination command to child machines and closes communication.


# Example

```
qsort([], []). 
qsort([Pivot|Tail], Sorted) :-
    partition(Pivot, Tail, Left, Right),
    dp_and([qsort(Left, LeftSorted),qsort(Right, RightSorted)]),   
    append(LeftSorted, [Pivot|RightSorted], Sorted). 

?- dp_create(['178.1.166.1','178.1.166.2']).
?- dp_transfer('./tests/qsort.pl').
?- dp_compile('./tests/qsort.pl').
?- dp_consult('./tests/qsort.o').
?- qsort([2,3,1],X).
 X = [1,2,3] 

?- dp_close.
```

The aforementioned qsort example is intended to illustrate the mechanism, not as a practical example, because the overhead is large compared to the small computational cost. The use case for dp_and/1 is better suited for larger, time-consuming computations that can be computed in parallel independently.

The use case for dp_or/1 is when not all computations are necessarily required. For example, it can be used in determining whether a large number is prime or a pseudoprime. If a single prime factor is found, it is immediately clear that the number is composite, and the remaining computations are unnecessary. This is the kind of situation where dp_or/1 is useful.

The parallel functionality provided by N-Prolog is simple and clear. By isolating and executing large, parallelizable computations within the scope of Prolog's syntax, it aims to dramatically increase the computational capacity of Prolog.