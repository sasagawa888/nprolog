/*
* lambda calculas for Montague
* e.g. ?- reduce([l(x,x),y],X). X = y .
*/
:- module(lambda,[reduce/2]).

reduce(X,X) :-
    atom(X).
reduce(l(A,B),l(A1,B1)) :-
    compound(B),
    alpha(A,l(A,B),0,l(A1,B1)).
reduce(l(A,B),l(A,B)). 
reduce([l(A,B),R],X) :-
    reduce(l(A,B),l(A1,B1)),
    beta(A1,B1,R,X).
reduce([L,R],X) :-
    list(L),
    reduce(L,L1),
    reduce([L1,R],X).

alpha(A,B,N,X) :-
    compound(B),
    B =.. B1,
    alpha_list(A,B1,N,X1),
    X =.. X1.

alpha(A,B,N,X) :-
    list(B),
    alpha_list(A,B,N,X).

alpha_list(A,[],N,[]) :- !.
alpha_list(A,[A|Bs],N,[A1|X]) :-
    atom_codes(A,L),
    N1 is N+48,
    append(L,[N1],L1),
    atom_codes(A1,L1),
    alpha_list(A,Bs,N,X),!.
alpha_list(A,[l(A1,B1)|Bs],N,[B3|X]) :-
    N1 is N+1,
    alpha(A1,l(A1,B1),N1,B2),
    alpha(A,B2,N,B3),
    alpha_list(A,Bs,N,X),!.
alpha_list(A,[B|Bs],N,[B1|X]) :-
    list(B),
    alpha_list(A,B,N,B1),
    alpha_list(A,Bs,N,X),!.
alpha_list(A,[B|Bs],N,[B|X]) :-
    alpha_list(A,Bs,N,X),!.

beta(A,A,R,R) :-
    atom(A),!.
beta(A,B,R,B) :-
    atom(B),!.

beta(A,[A1,B1],R,X) :-
    beta_list(A,[A1,B1],R,X1),
    reduce(X1,X).


beta(A,B,R,X) :-
    compound(B),
    B =.. B1,
    beta_list(A,B1,R,X1),
    X =.. X1.



beta_list(A,[],R,[]).
beta_list(A,[B|Bs],R,[X1|X]) :-
    beta(A,B,R,X1),
    beta_list(A,Bs,R,X).

