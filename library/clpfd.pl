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
X #= Y :-
    add_constraint(X #= Y).

X #\= Y :-
    add_constraint(X #\= Y).

X in Y :-
    add_constraint(X in Y).
X ins Y :-
    add_constraint((X ins Y)).

