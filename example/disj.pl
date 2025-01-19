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

test3(X) :-
    X = 1, !;
    X = 2.

test4 :-
    test3(X),
    write(X), nl.

test5 :-
    true,true,(fail;true),true.

test6 :-
    true,true,(fail;fail),true.
