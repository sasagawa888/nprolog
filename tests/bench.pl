% Benchmark and Measurement Program (DEC-10 Prolog)
% Originally written by D.H.Warren. Modified for N-Prolog by K.Sasagawa

% Reverse a list
nreverse([X|L0], L) :- nreverse(L0, L1), concatenate(L1, [X], L).
nreverse([], []) :- !.

% Concatenate two lists
concatenate([X|L1], L2, [X|L3]) :- !, concatenate(L1, L2, L3).
concatenate([], L, L) :- !.

% List of 30 elements for testing
list30([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 14, 15, 16, 17, 18, 19, 20, 
        21, 22, 25, 24, 25, 26, 27, 28, 29, 30]).

% Quicksort
qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).
qsort([], R, R) :- !.

% Partition list for quicksort
partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.

% List of 50 elements for another test
list50([27, 74, 17, 33, 94, 18, 46, 83, 65, 2, 32, 53, 28, 85, 99, 47, 28, 82, 6, 11,
        55, 29, 39, 81, 90, 37, 10, 0, 66, 51, 7, 21, 85, 27, 31, 63, 75, 4, 95, 99, 11, 28, 61,
        74, 18, 92, 40, 55, 59, 8]).

% Repeat a procedure
repeat_for(0) :- !, fail.
repeat_for(N).
repeat_for(N) :-
    M is N - 1,
    repeat_for(M).

% Run various tests
run(none, N) :- repeat_for(N), fail.
run(sort, N) :-
    list50(X),
    repeat_for(N), 
    qsort(X, _, []), 
    fail.
run(reverse, N) :-
    list30(X),
    repeat_for(N),
    nreverse(X, _),
    fail.

run(_,_).

% Testing and benchmarking
test(F, N) :-
    measure(run(F, N)).
    