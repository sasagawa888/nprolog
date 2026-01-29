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

% bv(X). X is bound variable. e.g. x0,x1... y0,y1,...
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

% Hilbert
ax(imply(P,imply(Q,P))).
ax(imply(imply(P,imply(Q,R)),imply(imply(P,Q),imply(P,R)))).
ax(imply(imply(neg(P),neg(Q)),imply(P,Q))).

% PM rule
ru(and(p,imply(p,q)),q).
ru(p(x1),forall(x1,p(x1))).

% proof
prf(X,Y) :-
    retractall(th(_)),
    prf1(X,Y).



prf1(X,[]) :-
    th(X),
    write('goal: '),
    write(X),nl.


prf1(X,[Y|Ys]) :-
    ax(Y),
    assert(th(Y)),
    write('axiom: '),
    write(Y),nl,
    prf1(X,Ys).

prf1(X,[Y|Ys]) :-
    th(Z),
    th(imply(Z,Y)),
    assert(th(Y)),
    write('theorem: '),
    write(Y),nl,
    prf1(X,Ys).


bew(X) :-
    def(X,Y),
    fp(X,Y),
    write('self reference detected'),nl.

bew(X) :-
    proof(X,Y),
    prf(X,Y).

proof(imply(p,p),
    [ imply(p,imply(p,p))                                        % A1
    , imply(p,imply(imply(p,p),p))                               % A1 (Q = imply(p,p))
    , imply(imply(p,imply(imply(p,p),p)),
            imply(imply(p,imply(p,p)),imply(p,p)))               % A2
    , imply(imply(p,imply(p,p)),imply(p,p))                      % A1+A2
    , imply(p,p)                                                 % goal
    ]).



% Godel's self-reference
% if X and Y are fixed point return yes.
fp(X,X) :- 
    atom(X).
fp(X,code(X)).
fp(X,Y) :-
    compound(Y),
    Y =.. [P,A],
    fp(X,A). 

% create g (I am unprovable)
phi(neg(bew(a0))).

diag(Name,G) :-
    phi(Phi),
    sb(Phi, a0, code(Name), G).

def(g,G) :-
    diag(g,G).