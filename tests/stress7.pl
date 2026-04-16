:- use_module(utils).

run_all :-
    test11, test12, test13, test14, test15.

test11 :-
    ( (A=1 ; A=2) -> B=A ; B=0 ),
    writeln(test11), writeln(B).

test12 :-
    ( (fail ; X=2) -> Y=X ; Y=0 ),
    writeln(test12), writeln(Y).

test13 :-
    ( (X=1 ; X=2) -> true ; true ),
    writeln(test13), writeln(X).

test14 :-
    ( true -> (X=1 ; X=2) ; X=0 ),
    writeln(test14), writeln(X).

test15 :-
    ( fail -> X=1 ; (Y=2 ; Y=3) ),
    writeln(test15), writeln(Y).