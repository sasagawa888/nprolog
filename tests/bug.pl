

p12(X, Y) :-
    (X = a ; X = b),
    (Y = 1 ; Y = 2).

    
p18(0, X, X).
p18(N, X, Y) :-
    N > 0,
    M is N - 1,
    Z is X + 1,
    p18(M, Z, Y).
