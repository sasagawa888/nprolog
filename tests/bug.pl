% test of module system

:- use_module(list).

foo(X,Y) :- last(X,Y).
