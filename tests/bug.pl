% testing compile code for diterministic predicate


foo(X) :- bar(X).

bar(X) :- write(X).

uoo(X) :- write(X),uoo(X).

nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).

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

reverse([],[]).
reverse([X|Xs],Y) :-
    reverse(Xs,Y1),
    append(Y1,[X],Y).

fact(0,1) :- !.
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.
