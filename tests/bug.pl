

p10(N, X) :-
    ( N > 0 ->
        X is N * 2
    ;
        X is N * 3
    ).
