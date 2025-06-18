% mathematics library
:- module(math,[isl/2,union/3,intersection/3,difference/3,subset/2,eqset/2,
                powerset/2,forall/2,topology/2,topology_space/2,
                map_val/3,map_set/3,map_compose/3,surjection/3,injection/3,
                list_map/2,map_list/2,map_inv/2,map_list/2,
                perm_prod/3,perm_inv/2,perm_div/3,perm_ident/2]).

% infix notation
%:- op(700,xfx,isl).
%Z isl X + Y :- union(X,Y,Z).
%Z isl X - Y :- difference(X,Y,Z).
%Z isl X * Y :- intersection(X,Y,Z).


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


% map function
:- op(700,xfx,:).

map_val([],X,Y) :- fail,!.
map_val([Y:X|Fs],X,Y) :- !.
map_val([F|Fs],X,Y) :-
    map_val(Fs,X,Y).

map_set(F,X,S) :-
    map_set1(F,X,S1),
    sort(S1,S).
map_set1([],_,[]).
map_set1([Y:X|Fs],[X|Xs],[Y|S]) :-
    map_set1(Fs,Xs,S).
map_set1([F|Fs],[X|Xs],S) :-
    map_set1(Fs,Xs,S).

map_compose([],[],[]) :- !.
map_compose([Y1:X1|Fs],[Y2:X2|Gs],[Y1:Y2|S]) :-
    map_compose(Fs,Gs,S).
map_compose([F|Fs],[G|Gs],S) :-
    map_compose(Fs,Gs,S).

list_map(X,Y) :- 
    list_map1(X,1,Y).

list_map1([],N,[]).
list_map1([L|Ls],N,[N:L|M]) :-
    N1 is N+1,
    list_map1(Ls,N1,M).


map_inv([],[]).
map_inv([X:Y|Ms],[Y:X|R]) :-
    map_inv(Ms,R).

map_list([],[]).
map_list([X:Y|Ms],[Y|L]) :-
    map_list(Ms,L).


% surjection([a:1,b:2],[1,2],[a,b]). yes
surjection(F,S,T) :-
    map_set(F,S,F1),
    eqset(F1,T).

% injection([a:1,b:2,c:3],[1,2,3],_). yes
% injection([a:1,a:2,c:3],[1,2,3],_). no(false)
injection(F,S,_) :-
    forall(math_select2(S,[X,Y]),
           (mapval(F,X,X1),mapval(F,Y,Y1),X1 \== Y1)).

% groupe


% product of permutations perm_prod([2,3,1]*[2,3,1],X). X = [3,1,2]
perm_prod(X,[I],[J]) :-
    nth1(I,X,J),!.
perm_prod(X,[I|Is],[J|Js]) :-
    nth1(I,X,J),!,
    perm_prod(X,Is,Js).

nth1(1,[X|Xs],X).
nth1(N,[X|Xs],Y) :-
    N1 is N-1,
    nth1(N1,Xs,Y).

% inverse of permutation
perm_inv(X,Z) :-
    list_map(X,M),
    map_inv(M,Y),
    sort(Y,Y1),
    map_list(Y1,Z).

perm_div(X,Y,Z) :-
    perm_inv(Y,Y1),
    perm_prod(X,Y1,Z).

perm_ident(N,X) :-
    perm_ident1(1,N,X).
perm_ident1(N,N,[N]).
perm_ident1(M,N,[M|X]) :-
    M1 is M+1,
    perm_ident1(M1,N,X).