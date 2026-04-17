
p42(N, A, X) :-
    ( N > 0 ->
        (B is A + N,
        M is N - 1,
        p42(M, B, X))
    ;
        X = A
    ).