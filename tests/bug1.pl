
%:- module(test,[]).

:- op(700,xfx,isl).

X isl Y+Y :- write(X),write(Y).

main :- write(asdf).

:- initialization(main).

