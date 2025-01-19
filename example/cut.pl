/*
written by M.Hiroi
Thanks

*/

ticket(Age, Money) :- Age < 13, Money is 500, !.
ticket(Age, Money) :- Money is 1000.

take_integer([X | Xs], Ys) :-
    take_integer(X, Ys1), take_integer(Xs, Ys2), append(Ys1, Ys2, Ys), !.
take_integer(X, [X]) :- integer(X), !.
take_integer(X, []).
% cut test from M.Hiroi's page

fact(0,1) :- !.
fact(X,Y) :- 
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.

yes_or_no(X) :- 
    repeat, write('yes or no >'), read(X), (X == yes ; X == no), !.

take_integer([X | Xs], Ys) :-
    take_integer(X, Ys1), take_integer(Xs, Ys2), append(Ys1, Ys2, Ys), !.
take_integer(X, [X]) :- integer(X), !.
take_integer(X, []).

%?- take_integer([1, a, [2, b]], X).