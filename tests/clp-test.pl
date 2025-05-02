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

n_factorial(0, 1).
n_factorial(N, F) :-
        N #> 0,
        N1 #= N - 1,
        n_factorial(N1, F1),
        F #= N * F1.