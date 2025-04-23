% CLP-test

solve :-
    X in 1..3, Y in 1..3,
    X #= Y + 1, X #\= Y,
    label([X, Y]).
