% about one body

det_body(!).
det_body((X,!)).
det_body((X,(!,Y))) :-
    det_body(Y).
det_body(X) :- 
    det_builtin(X).
det_body((X,Y)) :-
    det_builtin(X),
    det_body(Y).

det_builtin(write(_)).
det_builtin(write(_,_)).
det_builtin(true).
det_builtin(fail).
det_builtin((_<_)).
det_builtin((_>_)).

% about bodies 
/*
this is not deterministic
e.g.
how prove exclusive?
foo(X) :- X is 1.
foo(X) :- X is 2.
*/