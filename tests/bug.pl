max(X,Y,X) :- X>=Y,!.
max(X,Y,Y).

/*
% Partition list for quicksort
partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.


foo(X) :- write(X),!,write(X).

bar :- fail;true.

boo :- fail;fail;true.


fact(0,1) :- !.
fact(X,Y) :- 
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.

qdelete(A, A, L, L).
qdelete(X, A, [H|T], [A|R]) :-
    qdelete(X, H, T, R).

*/