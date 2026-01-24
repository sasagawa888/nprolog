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

foo :-
    foo.

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
    member(X,[not,or,and,imply,forall,exist,'(',')',0,'=','`','+',star]).


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

num(0).
num(['(',X,')','`']):-
    num(X).

tm(0).
tm(X) :-
    fv(X).

axiom(eq(X,X)).
axiom(a0+0=a0).
proof(F,axiom(F)) :- axiom(F).