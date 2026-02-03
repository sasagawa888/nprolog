% ex Herbrand Thorem

%e.g. forall(x,exist(y,and(p(x),q(y)))).

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