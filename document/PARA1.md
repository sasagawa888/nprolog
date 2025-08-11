# Distributed Parallel
This is a distributed parallel extension for N-Prolog. N-Prolog is oriented toward computational experiments and aims to explore the potential of Prolog in medium-scale distributed parallel computation.

![DP](para1.png)

# Invoke

npl -n on child machine terminal. N-Prolog runs with network mode.

N-Prolog on parent machine terminal. and dp_create/1 to establish TCP/IP between child Prolog.

# Spec

- npl -n: Launches child Prolog in network mode with the -n option.
A child can also function as a parent. By including dp_create/1 in network.pl, communication with the child is established immediately after starting in network mode using npl -n. With this functionality, the parent can delegate computations to a grandchild via the child.

- dp_create([IP0,IP1, …,IPn]): Provides IP addresse of child machines to establish TCP/IP communication with the parent Lisp. IP addresse is provided as atom. e.g. '178.1.166.2'
Up to 100 child devices can be connected.

- dp-and([p0,p1, ...,pn]): It executes the predicates from P0 to PN in parallel. If all of them return YES, it returns YES. If even one returns NO, it returns NO.

- dp_or([p0,p1, ...,n]): It executes the predicates from P0 to PN in parallel. If any one of them returns YES, it interrupts the other computations and returns YES.

- dp_transfer(Fn): Transfers file Fn to all child machines from the parent machine.

- dp_compile(Fn): Compiles file Fn on both parent and child machines.

- dp_consult(Fn): Loads file Fn on both parent and child machines.
    
- dp_reconsult(Fn): Loads file Fn on both parent and child machines.
    (Note) Internally, reconsult/1 is used. Existing predicates will be overwritten.

- dp_prove(Nth,Pred): Prove Predicate on the Nth child Prolog for testing.

- dp_close/0: Sends termination command to child machines and closes communication.In the case of a child device.
(Note) If halt is executed without performing dp_close, an error will occur. To terminate properly, dp_close is required.

- dp_halt/0: Sends termination command to child machines and closes communication.In the case of a child device, the OS will be shut down.

- dp_parent/0: When the system is operating as a parent, it returns YES; otherwise, it returns NO. Even if it is a child, it will return YES if it also functions as a parent with its own children.

- dp_child/0: Returns YES if it is a pure child machine without any child machines. Otherwise, returns NO.

    
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

# Protocol


# Error Handling


