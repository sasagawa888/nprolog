% clpfd idea memo

:- op(600, xfy, '..').
:- op(600, xfy, #=).
:- op(600, xfy, #>).
:- op(600, xfy, #<).
:- op(600, xfy, #\=).
:- op(600, xfy, #<=).
:- op(600, xfy, #>=).


X #= Y+Z :-
    integer(X),
    var(Y),
    integer(Z),
    R is X-Z,
    add_constraint(Y #= R).
X #= Y :-
    add_constraint(X #= Y).

