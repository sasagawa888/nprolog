% CLP-test idea memo

solve :-
    X in 1..3, Y in 1..3,
    X #= Y + 1, X #\= Y,
    label([X, Y]),
    write(X),nl,
    write(Y),nl.

foo :-
    X in 1..3,
    Y in 1..3,
    Z in 1..3,
    X+Y+Z #= 3.

