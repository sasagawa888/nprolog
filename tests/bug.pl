
member(X, [X|_]).
member(X, [_|Xs]) :- member(X, Xs).
