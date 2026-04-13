
nested_classify(N, X) :-
    ( N >= 0 ->
        ( N < 10 ->
            X = a
        ; N < 20 ->
            X = b
        ;
            X = c
        )
    ;
        X = neg
    ).
    