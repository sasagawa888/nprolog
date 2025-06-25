
:- module(test,[main/0,fact/2,dyn/0]).

:- op(700,xfx,isl).

X isl Y :- write(X),write(Y).

:- dynamic(fact/2).
fact(0,1).
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.


main :- write(asdf).

dyn :- asserta(fact(0,0)),
       fact(0,0),
       write(dyn_test_ok).

:- initialization(main).
%:- initialization(dyn).

