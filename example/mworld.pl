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
with(w1,with(w2,with(w3,fly(penguin)))). -> no
with(w1,with(w2,with(w3,fly(canary)))). -> yes

*/


with(W,assertz(X)) :-
    add_world(X,W,Y),
    assertz(Y).
with(W,deny(X)) :-
    add_world(X,W,Y),
    assertz(deny(Y)).

with(W,with(X,Y)) :-
    with1(with(X,Y),[W]).
with(W,X) :-
    add_world(X,W,X1),!,
    call_with(X1,[W]).

with1(with(W,X),L) :-
    with1(X,[W|L]).
with1(X,[L|L1]) :-
    add_world(X,L,X1),!,
    call_with(X1,[L|L1]).

% if predicate X is built_in predicate, not add world.
add_world(X,W,X) :-
    predicate_property(X,built_in).

% if predicate X is user_defined predicate add world.
add_world(X,W,Y) :-
    predicate_property(X,dynamic),
    X =.. X1,
    add_world1(X1,W,L),
    Y =.. L.

% if 1st argument is clause, add world to head and body.
add_world((H :- B),W,(H1 :- B1)) :-
    add_world(H,W,H1),
    add_world_body(B,W,B1).

% if 1st argument is conjunction add world to each predicate.
add_world((B1,B2),W,(C1,C2)) :-
    add_world1(B1,W,C1),
    add_world(B2,W,C2).

% if 1st argument is disjunction add world to each predicate.
add_world((B1;B2),W,(C1;C2)) :-
    add_world1(B1,W,C2),
    add_world(B2,W,C2).

% base of conjunction or disjunction. 
add_world(P,W,P1) :-
    P =.. L,
    add_world1(L,W,L1),
    P1 =.. L1.

% add world to listed predicate. 
add_world1([L|Ls],W,[L,W|Ls]).

% add varialbe world to conjunction body
add_world_body((B1,B2),W,(C1,C2)) :-
    add_world(B1,W,C1),
    add_world_body(B2,W,C2).
% add variable world to disjunction body
add_world_body((B1;B2),W,(C1;C2)) :-
    add_world(B1,W,C1),
    add_world_body(B2,W,C2).
% base of body
add_world_body(B,W,C) :-
    add_world(B,W,C).

call_with((X,Y),L) :-
    call_with(X,L),
    call_with(Y,L).

call_with((X;Y),L) :-
    call_with(X,L).

call_with((X;Y),L) :-
    call_with(Y,L).

% if X is built_in predicate, call X.
call_with(X,L) :-
    predicate_property(X,built_in),
    call(X).

% if X ls user_defined predicate and the 1st argument is member of world and deny, fail.
call_with(X,L) :-
    predicate_property(X,dynamic),
    X =.. [H,W|[A]],
    X1 =.. [H,W1|[A]],
    X2 =.. [deny,X1],
    inner_world(W,L,L1),
    clause(X2,true),
    member(W1,L1),!,
    fail.

% if X ls user_defined predicate and the 1st argument is member of world and X not has clause, call X.
call_with(X,L) :-
    predicate_property(X,dynamic),
    X =.. [H,W|[A]],
    X1 =.. [H,W1|[A]],
    inner_world(W,L,L1),
    clause(X1,true),
    member(W1,L1).


% if X ls user_defined predicate and the 1st argument is member of world and X is clause, call clause.
call_with(X,L) :-
    predicate_property(X,dynamic),
    X =.. [H,_|[A]],
    X1 =.. [H,W|[A]],
    clause(X1,Y),
    Y \= true,
    member(W,L),
    call_with(Y,L).

% make inner world w.g. inner_world(w2,[w3,w2,w1],X). X is [w2,w1]
inner_world(W,[],[]).
inner_world(W,[W|Ls],[W|Ls]).
inner_world(W,[L|Ls],X) :-
    inner_world(W,Ls,X).
    

% dummy data to avoid existance error.
deny(dummy).

%example1
:- with(a,assertz(p(a))).
:- with(b,assertz(p(b))).
:- with(c,assertz(p(c1))).
:- with(c,assertz(p(c2))).

%example2
:- with(w1,assertz(bird(canary))).
:- with(w1,assertz(bird(penguin))).
:- with(w2,assertz((fly(X) :- bird(X)))).
:- with(w3,deny(fly(penguin))).