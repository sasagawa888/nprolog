% ex Herbrand Thorem

%e.g. forall(x,exist(y,and(p(x),q(y)))).

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
    member(A,[x,y,z]).

snf(X,X) :-
    term(X).

snf(forall(E1,E2),X) :-
    snf(E2,X).

snf(imply(E1,E2),or(neg(X),Y)) :-
    snf(E1,X),
    snf(E2,Y).

snf(neg(neg(E)),E).

snf(neg(and(E1,E2)),or(neg(E1),neg(E2))) :-
    term(E1),
    term(E2).