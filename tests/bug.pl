
case_arg((X;Y),[X1->X5|Z]) :-
    X = (X1 -> (X2 -> X3 ; X4)),
    case_arg((X2->X3;X4),L),
    X5 =.. [case,L],
    case_arg(Y,Z).
case_arg((X;Y),[X|Z]) :-
    case_arg(Y,Z).
case_arg(X,X).


test16 :-
    between(0,5,N),
    (N < 3 ->
        (N < 1 -> X = a ; X = b),
        Y = left
    ;
        (N < 5 -> X = c ; X = d),
        Y = right
    ),
    write(test16), write(' : '), write(X), write(','), write(Y), nl,
    fail.
test16.