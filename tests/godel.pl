/*
Godel incompleteness 
Inspired by Chaitin’s Lisp code, I expressed a similar idea in Prolog.
*/

provable(G) :- call(G).

unprovable(G) :- \+ call(G).

call2(X,Y) :-
    P =.. [X,Y],
    call(P).

g(X) :-
    unprovable(call2(X,X)).

% call2(g,g).




% From godel's paper


% tm(X).  X is term. 
tm(X) :-
    fv(X).
tm(X) :-
    bv(X).
tm(X) :-
    num(X).
tm(_+_).
tm(_=_).
tm(neg(_)).
tm(or(_,_)).
tm(and(_,_)).
tm(imply(_,_)).
tm(forall(_,_)).
tm(exist(_,_)).


% fv(X). X is free variable　e,g, a0,a1...
fv(X) :-
    atom(X),
    atom_chars(X,[a,C]),
    char_code(C,A),
    A >= 48,
    A =< 57.

% bv(X). X is binded variable. e.g. x0,x1... y0,y1,...
bv(X) :-
    atom(X),
    atom_chars(X,[x,C]),
    char_code(C,A),
    A >= 48,
    A =< 57.
bv(X) :-
    atom(X),
    atom_chars(X,[y,C]),
    char_code(C,A),
    A >= 48,
    A =< 57.

% sq(X). X is sequence of formal symbol.
sq(X) :-
    tm(X).
sq((X,Y)) :-
    tm(X),
    sq(Y).
sq((X;Y)) :-
    tm(X),
    sq(Y).


% natural number
num(0).
num(s(X)):-
    num(X).




% formula(P) 
fm(T1=T2) :-
    tm(T1),
    tm(T2).

fm(P) :-
    tm(P).

fm(neg(P)) :-
    fm(P).

fm(and(P,Q)) :-
    fm(P),
    fm(Q).

fm(or(P,Q)) :-
    fm(P),
    fm(Q).

fm(imply(P,Q)) :-
    fm(P),
    fm(Q).

fm(forall(X,P)) :-
    bv(X),
    fm(P).

fm(exist(X,P)) :-
    bv(X),
    fm(P).

% subst(sequence,free-var,term,Result)
sb(X,Y,Z,Z) :-
    fv(X),
    X == Y.
sb(X,Y,Z,X) :-
    atomic(X),
    X \=Y,!.
sb(X,Y,Z,R) :-
    compound(X),
    X =.. S,
    sb1(S,Y,Z,S1),
    R =.. S1.

sb1([],Y,Z,[]).
sb1([Y|Ss],Y,Z,[Z|S1]) :-
    sb1(Ss,Y,Z,S1).
sb1([S|Ss],Y,Z,[S2|S1]) :-
    sb(S,Y,Z,S2),
    sb1(Ss,Y,Z,S1).

% Hilbelt
ax(imply(p,imply(q,p))).
ax(imply(imply(p,imply(q,r)),imply(imply(p,q),imply(p,r)))).
ax(imply(imply(neg(p),neg(q)),imply(q,p))).

% PM rule
ru(and(p,imply(p,q)),q).
ru(p(x1),forall(x1,p(x1))).
