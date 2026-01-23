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


% fs(X).  X is gedel number of formal symbol. 
fs(2).
fs(3).
fs(5).
fs(7).
fs(11).
fs(13).
fs(17).
fs(19).
fs(31).
fs(37).
fs(41).
fs(43).
fs(47).


num(X) :-
    X = 2-31.