% ex Herbrand Thorem

%e.g. 
ex(forall(x,imply(p(x),
                  exist(y,
                          and( imply(q(x,y), p(a)),
                          forall(z, imply(q(y,z), p(x)))
               ))))).

test(X) :-
    ex(Y),
    snf(Y,X).

% 102 is ascii code of atom f
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

skolem1(X,V,Y) :-
    foo(X).

alpha(forall(X,F), forall(X1,F1)) :-
    uniquev(X, X1),
    subst(F, X, X1, F1).

alpha(exist(X,F), exist(X1,F1)) :-
    uniquev(X, X1),
    subst(F, X, X1, F1).

subst(X,Y,Z,X) :-
    atomic(X),
    X \=Y,!.
subst(X,Y,Z,R) :-
    compound(X),
    X =.. S,
    subst1(S,Y,Z,S1),
    R =.. S1.

subst1([],Y,Z,[]).
subst1([Y|Ss],Y,Z,[Z|S1]) :-
    subst1(Ss,Y,Z,S1).
subst1([S|Ss],Y,Z,[S2|S1]) :-
    subst(S,Y,Z,S2),
    subst1(Ss,Y,Z,S1).


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

snf(X,Z) :-
    snf1(X,Y),
    alpha(Y,Z).

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