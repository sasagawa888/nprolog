
case_arg((X;Y),[X1->X5|Z]) :-
    X = (X1 -> (X2 -> X3 ; X4)),
    case_arg((X2->X3;X4),L),
    X5 =.. [case,L],
    case_arg(Y,Z).
case_arg((X;Y),[X|Z]) :-
    case_arg(Y,Z).
case_arg(X,X).



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
    