

p10(N, X) :-
    ( N > 0 ->
        Y is N * 2,
        X is Y*3
    ;
        Y is N * 3,
        X is Y*2
    ).
