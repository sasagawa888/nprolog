% testing compile code for diterministic predicate

nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).


/*
foo(X) :- bar(X).

bar(X) :- write(X).

uoo(X) :- write(X),uoo(X).


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

qdelete(A, A, L, L).
qdelete(X, A, [H|T], [A|R]) :-
    qdelete(X, H, T, R).

% List of 50 elements for another test
list50([27, 74, 17, 33, 94, 18, 46, 83, 65, 2, 32, 53, 28, 85, 99, 47, 28, 82, 6, 11,
        55, 29, 39, 81, 90, 37, 10, 0, 66, 51, 7, 21, 85, 27, 31, 63, 75, 4, 95, 99, 11, 28, 61,
        74, 18, 92, 40, 55, 59, 8]).
*/