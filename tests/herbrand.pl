% ex Herbrand Thorem

:- use_module(list).

%e.g. 
ex1(exist(x,p(x))).
ex2(exist(x,(forall(y,p(x,y))))).

ex3(forall(x,imply(p(x),
                  exist(y,
                          and( imply(q(x,y), p(a)),
                          forall(z, imply(q(y,z), p(x)))
               ))))).


% 102 is ascii code of atom f
:- ctr_set(1,0).
:- ctr_set(2,102).

uniquev(X,Y) :-
    ctr_inc(1,N),
    number_chars(N,C),
    atom_chars(A,C),
    atom_concat(X,A,Y).

uniquef(X) :-
    ctr_inc(2,N),
    char_code(X,N).

skolem(X,Y) :-
    skolem1(X,[],Y). 

skolem1(forall(V,E1),A,forall(V,Y)) :-
    skolem1(E1,[V|A],Y).
skolem1(exist(V,E1),A,Y) :-
    uniquef(F),
    reverse(A,A1),
    Func =.. [F|A1],
    subst(E1,V,Func,Y).
skolem1(and(E1,E2),A,and(X,Y)) :-
    skolem1(E1,A,X),
    slolem1(E2,A,Y).
skolem1(or(E1,E2),A,or(X,Y)) :-
    skolem1(E1,A,X),
    skolem1(E2,A,Y).
skolem1(neg(E),A,neg(E)).


alpha(forall(X,F), forall(X1,F2)) :-
    uniquev(X, X1),
    alpha(F,F1),
    subst(F1, X, X1, F2).

alpha(exist(X,F), exist(X1,F2)) :-
    uniquev(X, X1),
    alpha(F,F1),
    subst(F1, X, X1, F2).

alpha(and(A,B), and(A1,B1)) :-
    alpha(A,A1),
    alpha(B,B1).

alpha(or(A,B), or(A1,B1)) :-
    alpha(A,A1),
    alpha(B,B1).

alpha(imply(A,B), imply(A1,B1)) :-
    alpha(A,A1),
    alpha(B,B1).

alpha(neg(A), neg(A1)) :-
    alpha(A,A1).

alpha(X,X) :-
    atomic(X), !.

alpha(X,Z) :-
    compound(X),
    X =.. [F|Args],
    alpha_list(Args, Args1),
    Z =.. [F|Args1].

alpha_list([], []).
alpha_list([A|As], [A1|As1]) :-
    alpha(A, A1),
    alpha_list(As, As1).


subst(X, Y, Y1, Z) :-
    X == Y, !,
    Z = Y1.
subst(X, Y, Y1, Z) :-
    compound(X), !,
    X =.. [F|Args],
    subst_list(Args, Y, Y1, Args1),
    Z =.. [F|Args1].
subst(X, _Y, _Y1, X).

subst_list([], _Y, _Y1, []).
subst_list([A|As], Y, Y1, [B|Bs]) :-
    subst(A, Y, Y1, B),
    subst_list(As, Y, Y1, Bs).




term(X) :-
    compound(X),
    X =.. [P,A],
    member(P,[p,q,r]),
    member(A,[x,y,z,a,b,c]).


term(X) :-
    compound(X),
    X =.. [P,A1,A2],
    member(P,[p,q,r]),
    member(A1,[x,y,z,a,b,c]),
    member(A2,[x,y,z,a,b,c]).


%?- snf(exist(x,p(x)),X).
%X = p(f) .
%yes

snf(X,X2) :-
    snf1(X,X1),
    alpha(X1,X2).
    %skolem(X2,Z).

snf1(X,X) :-
    term(X).

snf1(forall(E1,E2),forall(E1,X)) :-
    snf1(E2,X).

snf1(exist(E1,E2),exist(E1,X)) :-
    snf1(E2,X).

snf1(and(E1,E2),and(X,Y)) :-
    snf1(E1,X),
    snf1(E2,Y).


snf1(or(E1,E2),or(X,Y)) :-
    snf1(E1,X),
    snf1(E2,Y).

snf1(imply(E1,E2),or(neg(X),Y)) :-
    snf1(E1,X),
    snf1(E2,Y).

snf1(neg(neg(E)),E).

snf1(neg(and(E1,E2)),or(neg(E1),neg(E2))) :-
    term(E1),
    term(E2).