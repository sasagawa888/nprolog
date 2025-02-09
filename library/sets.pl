% sets library

:- module(sets,[make_set/2,union/3,intersection/3,difference/3,subset/2,equal/2]).

make_set(X,Y) :- sort(X,Y).


union([], L, L).
union([X|Xs], L, [X|Ys]) :- 
    \+ member(X, L),
    union(Xs, L, Ys).
union([X|Xs], L, Ys) :- 
    member(X, L), 
    union(Xs, L, Ys).

intersection([], _, []).
intersection([X|Xs], L, [X|Ys]) :- 
    member(X, L), 
    intersection(Xs, L, Ys).
intersection([X|Xs], L, Ys) :- 
    \+ member(X, L), 
    intersection(Xs, L, Ys).

difference([], _, []).
difference([X|Xs], L, [X|Ys]) :- 
    \+ member(X, L), 
    difference(Xs, L, Ys).
difference([X|Xs], L, Ys) :- 
    member(X, L), 
    difference(Xs, L, Ys).

subset([],_).
subset([X|Xs],Y) :-
    member(X,Y),
    subset(Xs,Y).
subset([X|Xs],Y) :-
    \+ member(X,Y),fail.

equal(X,Y) :-
    subset(X,Y),
    subset(Y,X).