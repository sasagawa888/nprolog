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