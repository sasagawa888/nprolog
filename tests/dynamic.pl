% test of dynamic/1. see SUPERSET.md


:- dynamic(foo/1).
:- dynamic(baa/1). %ignore

foo :- write(1).

foo(X) :- write(X).

boo(X) :- foo(X).

bar(X) :- foo.
