% clpfd idea memo

:- op(500, xfy, '..').
:- op(500, xfy, #=).
:- op(500, xfy, #>).
:- op(500, xfy, #<).
:- op(500, xfy, #\=).
:- op(500, xfy, #<=).
:- op(500, xfy, #>=).

X #= Y :-
    add_constraint(var(X) #= var(Y)).

