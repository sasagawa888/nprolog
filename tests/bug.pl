

:- use_module(utils).

test18 :-
    ( \+ fail -> X=yes ; X=no ),
    writeln(test18), writeln(X).

