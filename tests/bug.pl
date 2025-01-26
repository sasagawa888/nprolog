
:- module(foo,[bar/1]).

bar(X) :- boo(X),write(X).

boo(X) :- uoo(X).