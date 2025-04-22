% clpfd idea memo

:- op(600, xfy, '..').
:- op(600, xfy, #=).
:- op(600, xfy, #>).
:- op(600, xfy, #<).
:- op(600, xfy, #\=).
:- op(600, xfy, #<=).
:- op(600, xfy, #>=).

X #= Y :-
    add_constraint(X #= Y).


