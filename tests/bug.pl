

p10(N, X) :-
    ( N > 0 ->
        A is N + 10,
        X is A * 2
    ;
        B is N - 10,
        X is B * 2
    ).
