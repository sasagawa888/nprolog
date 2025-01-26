
:- module(asdf,[bar/1]).

bar(X) :- boo(X).

boo(X) :- write(X).