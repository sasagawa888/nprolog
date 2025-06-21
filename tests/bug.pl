
:- use_module(math).


perm_even(X,Y) :-
    permutation(X,Y),
    perm_sign(Y,1).

perm_odd(X,Y) :-
    permutation(X,Y),
    perm_sign(Y,-1).