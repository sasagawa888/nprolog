/*
multiplex world system by Hideaki Nakashima

[with/2]
[assertz]
with(w2,assertz(fly(X) :- bird(X))).  in world w2 predicate or clause is true.
translate follwing clause.
fly(w2,X) :-
    bird(w2,X).

[deny]
with(w3,deny(fly(penguin))). in world w3 predicate or clause is fail.
translate following predicate.
deny(fly(w3,penguin)).

[call]
with(w1,with(w2,with(w3,fly(penguin))). -> no
with(w1,with(w2,with(w3,fly(canary))). -> yes

*/


with(W,assertz(X)) :-
    mp_add_world(X,W,Y),
    assertz(Y).
with(W,deny(X)) :-
    mp_add_world(X,W,Y),
    assertz(deny(Y)).

with(W,with(X,Y)) :-
    mp_with1(with(X,Y),[W]).
with(W,X) :-
    mp_add_world(X,W,X1),!,
    mp_call_with(X1,[W]).

mp_with1(with(W,X),L) :-
    mp_with1(X,[W|L]).
mp_with1(X,[L|L1]) :-
    mp_add_world(X,L,X1),!,
    mp_call_with(X1,[L|L1]).

% if predicate X is built_in predicate, not add world.
mp_add_world(X,W,X) :-
    predicate_property(X,built_in).

% if predicate X is user_defined predicate add world.
mp_add_world(X,W,Y) :-
    predicate_property(X,dynamic),
    X =.. X1,
    mp_add_world1(X1,W,L),
    Y =.. L.

% if 1st argument is clause, add world to head and body.
mp_add_world((H :- B),W,(H1 :- B1)) :-
    mp_add_world(H,W,H1),
    mp_add_world_body(B,W,B1).

% if 1st argument is conjunction add world to each predicate.
mp_add_world((B1,B2),W,(C1,C2)) :-
    mp_add_world1(B1,W,C1),
    mp_add_world(B2,W,C2).

% if 1st argument is disjunction add world to each predicate.
mp_add_world((B1;B2),W,(C1;C2)) :-
    mp_add_world1(B1,W,C2),
    mp_add_world(B2,W,C2).

% base of conjunction or disjunction. 
mp_add_world(P,W,P1) :-
    P =.. L,
    mp_add_world1(L,W,L1),
    P1 =.. L1.

% add world to listed predicate. 
mp_add_world1([L|Ls],W,[L,W|Ls]).

% add varialbe world to conjunction body
mp_add_world_body((B1,B2),W,(C1,C2)) :-
    mp_add_world(B1,W,C1),
    mp_add_world_body(B2,W,C2).
% add variable world to disjunction body
mp_add_world_body((B1;B2),W,(C1;C2)) :-
    mp_add_world(B1,W,C1),
    mp_add_world_body(B2,W,C2).
% base of body
mp_add_world_body(B,W,C) :-
    mp_add_world(B,W,C).

mp_call_with((X,Y),L) :-
    mp_call_with(X,L),
    mp_call_with(Y,L).

mp_call_with((X;Y),L) :-
    mp_call_with(X,L).

mp_call_with((X;Y),L) :-
    mp_call_with(Y,L).

% if X is built_in predicate, call X.
mp_call_with(X,L) :-
    predicate_property(X,built_in),
    mp_call(X).

% if X ls user_defined predicate and the 1st argument is member of world and deny, fail.
mp_call_with(X,L) :-
    predicate_property(X,dynamic),
    X =.. [H,_|[A]],
    X1 =.. [H,W|[A]],
    X2 =.. [deny,X1],
    clause(X2,true),
    member(W,L),!,
    fail.

% if X ls user_defined predicate and the 1st argument is member of world and X not has clause, call X.
mp_call_with(X,L) :-
    predicate_property(X,dynamic),
    X =.. [H,_|[A]],
    X1 =.. [H,W|[A]],
    clause(X1,true),
    member(W,L).


% if X ls user_defined predicate and the 1st argument is member of world and X is clause, call clause.
mp_call_with(X,L) :-
    predicate_property(X,dynamic),
    X =.. [H,_|[A]],
    X1 =.. [H,W|[A]],
    clause(X1,Y),
    Y \= true,
    member(W,L),
    mp_call_with(Y,L).


% dummy data to avoid existance error.
deny(dummy).
