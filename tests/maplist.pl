% -----------------------------
% maplist/3 test for N-Prolog
% -----------------------------

show(Test, X) :-
    write(Test),
    write(' : '),
    write(X),
    nl.

inc1(X, Y) :-
    Y is X + 1.

double(X, Y) :-
    Y is X * 2.

square(X, Y) :-
    Y is X * X.

to_atom_num(X, Y) :-
    Y = num(X).

positive_to_ok(X, Y) :-
    X > 0,
    Y = ok.

same(X, X).

test1 :-
    maplist(inc1, [1,2,3], X),
    show(test1, X).

test2 :-
    maplist(double, [1,2,3,4], X),
    show(test2, X).

test3 :-
    maplist(square, [2,3,4], X),
    show(test3, X).

test4 :-
    maplist(to_atom_num, [5,6,7], X),
    show(test4, X).

test5 :-
    maplist(same, [a,b,c], X),
    show(test5, X).

test6 :-
    maplist(inc1, [], X),
    show(test6, X).

test7 :-
    maplist(positive_to_ok, [1,2,3], X),
    show(test7, X).

test8 :-
    ( maplist(positive_to_ok, [1,0,3], X) ->
        show(test8, X)
    ;
        show(test8, fail)
    ).

test9 :-
    ( maplist(inc1, [1,2], [2,3]) ->
        show(test9, ok)
    ;
        show(test9, fail)
    ).

test10 :-
    ( maplist(inc1, [1,2], [2,4]) ->
        show(test10, ok)
    ;
        show(test10, fail)
    ).

test11 :-
    ( maplist(inc1, [1,2,3], [2,3]) ->
        show(test11, ok)
    ;
        show(test11, fail)
    ).

test12 :-
    ( maplist(inc1, [1,2], [2,3,4]) ->
        show(test12, ok)
    ;
        show(test12, fail)
    ).

test13 :-
    maplist(same, [foo,bar,baz], [foo,bar,baz]),
    show(test13, ok).

test14 :-
    ( maplist(same, [foo,bar,baz], [foo,zzz,baz]) ->
        show(test14, ok)
    ;
        show(test14, fail)
    ).

test15 :-
    maplist(to_atom_num, [], X),
    show(test15, X).

run_all :-
    test1,
    test2,
    test3,
    test4,
    test5,
    test6,
    test7,
    test8,
    test9,
    test10,
    test11,
    test12,
    test13,
    test14,
    test15.