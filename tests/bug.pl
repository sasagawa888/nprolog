test(X) :-
    X = 1;
    X = 2.

test1 :-
    test(X),
    write(X), nl,
    fail.

test2(X) :-
    X = a;
    X = b;
    X = c.
