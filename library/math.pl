% mathematics library
:- module(math,[union/3,intersection/3,difference/3,subset/2,eqset/2,
                powerset/2,forall/2,topology/2,topology_space/2]).

%sets
union(X,Y,Z1) :-
    union1(X,Y,Z),
    sort(Z,Z1),!.

union1([], L, L).
union1([X|Xs], L, [X|Ys]) :- 
    \+ member(X, L),
    union1(Xs, L, Ys).
union1([X|Xs], L, Ys) :- 
    member(X, L), 
    union1(Xs, L, Ys).

intersection(X,Y,Z1) :-
    intersection1(X,Y,Z),
    sort(Z,Z1),!.

intersection1([], _, []).
intersection1([X|Xs], L, [X|Ys]) :- 
    member(X, L), 
    intersection1(Xs, L, Ys).
intersection1([X|Xs], L, Ys) :- 
    \+ member(X, L), 
    intersection1(Xs, L, Ys).

difference(X,Y,Z1) :-
    difference1(X,Y,Z),
    sort(Z,Z1),!.

difference1([], _, []).
difference1([X|Xs], L, [X|Ys]) :- 
    \+ member(X, L), 
    difference1(Xs, L, Ys).
difference1([X|Xs], L, Ys) :- 
    member(X, L), 
    difference1(Xs, L, Ys).

subset([],[]).
subset([X|L],[X|S]) :-
subset(L,S).
subset(L, [_|S]) :-
subset(L,S).

eqset(X,Y) :-
    subset(X,Y),
    subset(Y,X).

powerset([], [[]]).
powerset([X|Xs], P) :-
    powerset(Xs, Ps),
    add_elem(X, Ps, Ps1),
    append(Ps, Ps1, P).

add_elem(_, [], []).
add_elem(X, [Set|Sets], [[X|Set]|Sets1]) :-
    add_elem(X, Sets, Sets1).

% control
forall(P, Q) :-
    \+ (P, \+ Q).


% topology 
topology(O,Z) :-
    member([],O),!,
    member(Z,O),!,
    forall(math_select2(O,[X,Y]),math_topology1([X,Y],O)),!.

select2(O,[X,Y]) :-
    select(X,O,O1),
    select(Y,O1,_).

topology1([X,Y],O) :-
    union(X,Y,U),
    member(U,O),
    intersection(X,Y,I),
    member(I,O),!.

topology_space(X,Z) :-
    powerset(X,Y),
    subset(Z,Y),
    topology(Z,X).