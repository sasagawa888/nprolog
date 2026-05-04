:- use_module(utils).

test15 :-
    ( fail -> (X=1, Y=0) ; (Y=2 ; Y=3) ),
    writeln(test15), writeln(Y).