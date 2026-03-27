

:- use_module(clpfd).

ac(X,Y,Z) :-
    X in 1..3,
    Y in 1..3,
    Z in 1..5,
    X+Y+Z#=3,
    label([X,Y,Z]). 