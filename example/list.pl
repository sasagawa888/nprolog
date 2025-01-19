% list tests from M.Hiroi's page

my_flatten([X | Xs], Ys) :-
    my_flatten(X, Ys1), my_flatten(Xs, Ys2), append(Ys1, Ys2, Ys).
my_flatten(X, [X]) :- atomic(X), X \== [].
my_flatten([], []).

%? my_flatten([a, [b, [c], d], [e, f]], X).
%? my_flatten([[a, b], [], [c, d]], X).

take_integer([X | Xs], Ys) :-
    take_integer(X, Ys1), take_integer(Xs, Ys2), append(Ys1, Ys2, Ys).
take_integer(X, [X]) :- integer(X).
take_integer(X, []).

%? take_integer([1, a, [2, b]], X).

