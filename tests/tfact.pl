
fact(N, X) :- fact_(N, 1, X).
fact_(N, P, X) :- N > 0,
    N1 is N - 1,
    P1 is P * N,
    fact_(N1, P1, X).
fact_(0, X, X).