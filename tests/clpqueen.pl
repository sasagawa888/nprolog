:- use_module(library(clpfd)).

not_attack(_, [], _).
not_attack(X, [Y | Ys], N) :-
    abs(X - Y) #\= N,
    N1 #= N + 1,
    not_attack(X, Ys, N1).

safe([_]).
safe([X | Xs]) :- not_attack(X, Xs, 1), safe(Xs).

nqueens(N, Xs) :-
    length(Xs, N),
    Xs ins 1 .. N,
    all_different(Xs),
    safe(Xs).
