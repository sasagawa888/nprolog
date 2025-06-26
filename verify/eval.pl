% Author: Jan Wielemaker
% This code is in the public domain

% Evaluate large arithmetic expressions

%:- mode(add(+,-)).

top :-
    t_(1000, 1).

t(D,N) :-
    time(t_(D,N)).

t_(D,N) :-
    add(D, Expr),
    (   repeat(N),
        V is Expr,
        integer(V),                     % avoid optimization
        fail
    ;   true
    ).

add(0, 1) :- !.
add(N, (Expr+N)) :-
    N2 is N - 1,
    add(N2, Expr).

/*
repeat(N) :-
    (   true
    ;   N > 0,
        N1 is N-1,
        repeat(N1)
    ).
*/