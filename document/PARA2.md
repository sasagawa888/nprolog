# Multi-thread Parallel
under construction

This is a multi-thread parallel extension for N-Prolog. N-Prolog is oriented toward computational experiments and aims to explore the potential of Prolog in medium-scale parallel computation with distributed parallel.


# Spec

    mt_create(N): Generate N threads.

    mt-and([p0,p1, ...,pn]): It executes the predicates from P0 to PN in parallel. If all of them return YES, it returns YES. If even one returns NO, it returns NO.

    mt_or([p0,p1, ...,n]): It executes the predicates from P0 to PN in parallel. If any one of them returns YES, it interrupts the other computations and returns YES.

    mt_prove(Nth,Pred): Prove Predicate on the Nth thread for testing.

    mt_close: Close all threads.
   

# Example

```
% multi-thread parallel example

:- mt_create(2).

para(X) :- list50(Y),psort(Y,X).

psort([Pivot|Rest], Sorted) :-
    partition(Pivot, Rest, Left, Right), 
    mt_and([qsort(Left, SortedLeft), qsort(Right, SortedRight)]),       
    append(SortedLeft, [Pivot|SortedRight], Sorted). 

seq(X) :- list50(Y),qsort(Y,X).

qsort([], []).
qsort([Pivot|Rest], Sorted) :-
    partition(Pivot, Rest, Left, Right), 
    qsort(Left, SortedLeft),          
    qsort(Right, SortedRight),       
    append(SortedLeft, [Pivot|SortedRight], Sorted). 

partition(_, [], [], []). 
partition(Pivot, [H|T], [H|Left], Right) :-
    H =< Pivot,  
    partition(Pivot, T, Left, Right).
partition(Pivot, [H|T], Left, [H|Right]) :-
    H > Pivot,  
    partition(Pivot, T, Left, Right).

% List of 50 elements for another test
list50([27, 74, 17, 33, 94, 18, 46, 83, 65, 2, 32, 53, 28, 85, 99, 47, 28, 82, 6, 11,
        55, 29, 39, 81, 90, 37, 10, 0, 66, 51, 7, 21, 85, 27, 31, 63, 75, 4, 95, 99, 11, 28, 61,
        74, 18, 92, 40, 55, 59, 8]).

```
[MT](para3.png)

# Thread pooling
source code extension.c line 2139

mt-create... b_mt_create
mt-amd... f_mt_and
mt-or... f_mt_or
mp-close... f_mt_close

queue[] = 1,2,3,... worker_count

worker_count = core_count - 1(main + GC);


initital
queue  [1,2,3,4]  hexa core
queue_pt = 4;

eval_para(arg)
dequeue [2,3,4]
queue_pt = 3
main thread send signal to worker1 thread.
worker1 eval(arg) -> para_output[1]=result.
worker1 send signal to main thread.
enqueue [2,3,4,1]
queue_pt = 4

[thread](para4.png)