
foo(X,Y) :-
    append(A,B,[1,2,3]),
    Y is X * X.

% recompute_test(2,A,Z).
recompute_test(N, X, Y) :-
    between(1, N, X),
    Y is X * X.
