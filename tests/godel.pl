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
lh(X,N) :- 
    length(X,N).

star(X,Y,Z) :-
    append(X,Y,Z).

% fs(X).  X is formal symbol. 
fs(X) :-
    fv(X).
fs(X) :-
    bv(X).
fs(X) :-
    num(X).
fs(X) :-
    member(X,[not,or,and,imply,forall,exist,0,'=','+','`']).


% fv(X). X is free variable
fv(X) :-
    atom(X),
    atom_chars(X,[a,C]),
    char_code(C,A),
    A >= 48,
    A =< 57.

% bv(X). X is binded variable.
bv(X) :-
    atom(X),
    atom_chars(X,[x,C]),
    char_code(C,A),
    A >= 48,
    A =< 57.

% sq(X). X is sequence of formal symbol.
sq([]).
sq([X|Xs]) :-
    fs(X),
    sq(Xs).

% natural number
num(0).
num(s(X)):-
    num(X).


% term(X)
tm(X) :-
    fv(X).
tm(X) :-
    num(X).
tm([X,+,Y]) :-
    tm(X),
    tm(Y).
tm([X,*,Y]) :-
    tm(X),
    tm(Y).

% formula(φ)
fm(T1 = T2) :- tm(T1), tm(T2).    
fm(not(P)) :- fm(P).
fm(and(P,Q)) :- fm(P), fm(Q).
fm(or(P,Q))  :- fm(P), fm(Q).
fm(imply(P,Q)) :- fm(P), fm(Q).
fm(forall(X,P)) :- bv(X), fm(P).
fm(exist(X,P))  :- bv(X), fm(P).
