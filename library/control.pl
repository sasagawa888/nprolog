% control library

:- module(control,[forall/2]).

forall(P, Q) :-
    \+ (P, \+ Q).

