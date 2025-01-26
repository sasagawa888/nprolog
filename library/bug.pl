
:- module(foo,[bar/1]).

bar(X) :- boo(X).

boo(X) :- write(X).