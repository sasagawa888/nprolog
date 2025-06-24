
:- module(test,[main/0,main2/0]).

:- op(700,xfx,isl).

X isl Y+Y :- write(X),write(Y).

main :- write(asdf).

main2 :- write(second).

:- initialization(main).
:- initialization(main2).

