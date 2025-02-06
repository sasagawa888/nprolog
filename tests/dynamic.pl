% test of dynamic/1. see SUPERSET.md


:- dynamic(foo/1).
:- dynamic(baa/1).

foo(X) :- write(X).

foo(Y,X) :- write(Y).

boo(X) :- write(X).
