:- dynamic(fact/2).
fact(0,1).
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.

dyn :- asserta(fact(0,0)).

:- initialization(dyn).
