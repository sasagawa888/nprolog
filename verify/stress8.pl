:- use_module(utils).

run_all :-
    test16, test17, test18, test19, test20.

test16 :-
    N = 1,
    ( N > 0 -> X=pos ; X=neg ),
    writeln(test16), writeln(X).

test17 :-
    N = 0,
    ( N > 0 -> X=pos ; N =:= 0 -> X=zero ; X=neg ),
    writeln(test17), writeln(X).

test18 :-
    ( \+ fail -> X=yes ; X=no ),
    writeln(test18), writeln(X).

test19 :-
    ( \+ true -> X=yes ; X=no ),
    writeln(test19), writeln(X).

test20 :-
    ( true -> (A=1, B=2) ; (A=3, B=4) ),
    writeln(test20), writeln(A), writeln(B).