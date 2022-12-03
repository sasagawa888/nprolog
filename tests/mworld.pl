%multiple world system

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
with1(X,L) :-
    add_world(X,_,X1),!,
    call_with(X1,L).

add_world(X,W,X) :-
    predicate_property(X,built_in).

add_world(X,W,Y) :-
    predicate_property(X,dynamic),
    X =.. X1,
    add_world1(X1,W,L),
    Y =.. L.

add_world((H :- B),W,(H1 :- B1)) :-
    add_world(H,W,H1),
    add_world_body(B,W,H,B1).

add_world((B1,B2),W,(C1,C2)) :-
    add_world1(B1,W,C1),
    add_world(B2,W,C2).

add_world((B1;B2),W,(C1;C2)) :-
    add_world1(B1,W,C2),
    add_world(B2,W,C2).

add_world(P,W,P1) :-
    P =.. L,
    add_world1(L,W,L1),
    P1 =.. L1.

add_world1([L|Ls],W,[L,W|Ls]).


add_world_body((B1,B2),W,H,(B1,C2)) :-
    predicate_property(B1,built_in),
    add_world_body(B2,W,H,C2).

add_world_body((B1,B2),W,H,(C1,C2)) :-
    functor(B1,H1,A1),
    functor(H,H1,A1),
    add_world(B1,W,C1),
    add_world_body(B2,W,H,C2).

add_world_body((B1,B2),W,H,(C1,C2)) :-
    add_world1(B1,W,C1),
    add_world_body(B2,W,H,C2).

add_world_body(P,W,H,P1) :-
    functor(P,H1,A1),
    functor(H,H1,A1),
    add_world1(P,W,P1).

add_world_body(P,W,H,P1) :-
    add_world(P,_,P1).

call_with((X,Y),L) :-
    arg(1,X,W),
    member(W,L),
    call(X),
    call_with(Y,L).

call_with((X;Y),L) :-
    arg(1,X,W),
    member(W,L),
    call(X),!.

call_with((X;Y),L) :-
    arg(1,Y,W),
    member(W,L),
    call(Y).

call_with(X,L) :-
    predicate_property(X,built_int),
    call(X).

call_with(X,L) :-
    predicate_property(X,dynamic),
    arg(1,X,W),
    member(W,L),
    deny(X),!,
    fail.

call_with(X,L) :-
    predicate_property(X,dynamic),
    arg(1,X,W),
    member(W,L),
    clause(X,true).


call_with(X,L) :-
    predicate_property(X,dynamic),
    arg(1,X,W),
    member(W,L),
    clause(X,Y),
    Y \= true,
    call_with(Y,L).

