% test dynamic/1

:- dynamic(fact/2).

foo(X,Y) :- fact(X,Y).

fact(0,1).
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.
