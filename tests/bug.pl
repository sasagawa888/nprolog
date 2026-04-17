
test16 :-
    between(0,5,N),
    (N < 3 ->
        ((N < 1 -> X = a ; X = b),
        Y = left)
    ;
        ((N < 5 -> X = c ; X = d),
        Y = right)
    ),
    write(test16), write(' : '), write(X), write(','), write(Y), nl,
    fail.
test16.