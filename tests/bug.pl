% CLPFD test

:- use_module(clpfd).

foo(X,Y) :-
    X in 1..2,
    Y in 1..3,
    X #= Y,
    label([X,Y]).

