% testing compile code for diterministic predicate

foo(0) :- !.
foo(X) :- X1 is X-1,foo(X1).

partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.
