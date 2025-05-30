% AC-3 test

:- use_module(clpfd).

test1(X,Y,Z) :-
    X in 1..3,
    Y in 1..3,
    Z in 1..5,
    X+Y+Z#=3,
    label([X,Y,Z],trace). 

test2(X,Y) :-
    X in 1..3,
    Y in 1..3,
    X #< Y,
    label([X,Y],trace). 

test3(X,Y) :-
    X in 1..3,
    Y in 2..6,
    Y #< X,
    label([X,Y],trace). 

test4(X,Y) :-
    X in 2..3,
    Y in 1..5,
    Y #<= X,
    label([X,Y],trace). 

test5(X,Y) :-
    X in 2..3,
    Y in 1..5,
    X #> Y,
    label([X,Y],trace). 

test6(X,Y) :-
    X in 2..3,
    Y in 1..5,
    X #>= Y,
    label([X,Y],trace). 

test7(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y mod 3,
    label([X,Y],trace).

test8(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y ^ 3,
    label([X,Y],trace).

test9(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y ** 3,
    label([X,Y],trace).


test10(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y // 3,
    label([X,Y],trace).

