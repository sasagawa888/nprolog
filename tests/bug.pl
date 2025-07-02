
:- dynamic(foo/2).

foo(0,_) :- asserta((foo(X,Y) :- Y is X+3)).
foo(X,Y) :- Y is X+2.
