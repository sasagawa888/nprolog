
:- module(asdf,[bar/1,fact/2]).

bar(X) :- boo(X).

boo(X) :- write(X).

fact(0,1).
fact(X,Y) :-
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.