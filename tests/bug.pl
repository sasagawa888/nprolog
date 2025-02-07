% test of dynamic/1. see SUPERSET.md


:- dynamic(fact/1).
:- dynamic(bar/1). 

foo(X,Y) :- fact(X,Y).

fact(0,1).
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.

bar(1,2).
bar(a,b).
bar([1,2,3],a).
bar(X) :- write($a$).
