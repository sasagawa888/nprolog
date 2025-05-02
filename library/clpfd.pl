% clpfd idea memo

:- op(600, xfy, '..').
:- op(600, xfy, #=).
:- op(600, xfy, #>).
:- op(600, xfy, #<).
:- op(600, xfy, #\=).
:- op(600, xfy, #<=).
:- op(600, xfy, #>=).
:- op(600, xfy, in).
:- op(600, xfy, ins).

X #= Y+Z :-
    integer(X),
    var(Y),
    integer(Z),
    R is X-Z,
    add_constraint(Y #= R),
    Y is R.
X #= Y+Z :-
    var(X),
    integer(Y),
    integer(Z),
    X is Y+Z.
X #= Y-Z :-
    var(X),
    integer(Y),
    integer(Z),
    X is Y-Z.
X #= Y*Z :-
    var(X),
    integer(Y),
    integer(Z),
    X is Y*Z.
X #= Y :-
    add_constraint(X #= Y).

X #> Y :-
    integer(X),
    integer(Y),
    X > Y.

X #\= Y :-
    add_constraint(X #\= Y).

X in Y :-
    add_constraint(X in Y).
X ins Y :-
    add_constraint((X ins Y)).

