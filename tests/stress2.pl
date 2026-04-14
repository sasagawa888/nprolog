% stress_short.pl
% N-Prolog short stress tests
% 別観点からの短いストレスコード集

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% simple test runner
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 8,13,20 bug in compiler

run_all :-
    test1,  nl,
    test2,  nl,
    test3,  nl,
    test4,  nl,
    test5,  nl,
    test6,  nl,
    test7,  nl,
    test8,  nl,
    test9,  nl,
    test10, nl,
    test11, nl,
    test12, nl,
    test13, nl,
    test14, nl,
    test15, nl,
    test16, nl,
    test17, nl,
    test18, nl,
    test19, nl,
    test20, nl.

show(Name, X) :-
    write(Name), write(' : '), write(X).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 1. variable sharing
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p1(X, Y) :- X = Y.
test1 :-
    p1(A, B),
    A = hello,
    show(test1, B).
% expected: hello

p2(X, Y, Z) :- X = Y, Y = Z.
test2 :-
    p2(A, B, C),
    C = ok,
    show(test2, A).
% expected: ok

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2. unification + backtracking
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p3(a).
p3(b).

test3 :-
    p3(X),
    show(test3, X),
    fail.
test3 :-
    true.
% expected: a b

p4(X) :- X = 1 ; X = 2.
test4 :-
    p4(X),
    show(test4, X),
    fail.
test4 :-
    true.
% expected: 1 2

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 3. arithmetic evaluation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p5(X) :- Y is 1+2, X is Y*3.
test5 :-
    p5(X),
    show(test5, X).
% expected: 9

p6(X) :- X is (2+3)*(4-1).
test6 :-
    p6(X),
    show(test6, X).
% expected: 15

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 4. cut interaction
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p7(X) :- X = a, !.
p7(X) :- X = b.

test7 :-
    p7(X),
    show(test7, X).
% expected: a

p8(X) :- (X = 1 ; X = 2), !.
p8(3).

test8 :-
    p8(X),
    show(test8, X).
% expected: 1

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 5. negation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p9(a).
p9(b).

test9 :-
    \+ p9(c),
    show(test9, ok).
% expected: ok

test10 :-
    \+ p9(a),
    show(test10, ng).
test10 :-
    show(test10, ok).
% expected: ok

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 6. list / structure decomposition
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p10([H|T], H, T).

test11 :-
    p10([1,2,3], H, T),
    write(test11), write(' : '), write(H), write(','), write(T).
% expected: 1,[2,3]

p11(foo(X,bar), X).

test12 :-
    p11(foo(abc,bar), X),
    show(test12, X).
% expected: abc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 7. multiple answers
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p12(X, Y) :-
    (X = a ; X = b),
    (Y = 1 ; Y = 2).

test13 :-
    p12(X, Y),
    write(test13), write(' : '), write(X), write(','), write(Y),
    fail.
test13 :-
    true.
% expected:
% a,1
% a,2
% b,1
% b,2

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 8. failure propagation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p13 :- a = b.
p13 :- true.

test14 :-
    p13,
    show(test14, ok).
% expected: ok

p14(X) :- X = 1, fail.
p14(2).

test15 :-
    p14(X),
    show(test15, X).
% expected: 2

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 9. same variable repeated
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p15(X, X).

test16 :-
    p15(abc, abc),
    show(test16, ok).
% expected: ok

test17 :-
    p15(abc, def),
    show(test17, ng).
test17 :-
    show(test17, ok).
% expected: ok

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 10. nested structure + arithmetic
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p16(pair(X,Y), Z) :- Z is X + Y.

test18 :-
    p16(pair(10,20), Z),
    show(test18, Z).
% expected: 30

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 11. choice point cleanup
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p17(X) :- (X = a ; X = b), X = a.

test19 :-
    p17(X),
    show(test19, X).
% expected: a

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 12. deterministic tail-like simple chain
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p18(0, X, X).
p18(N, X, Y) :-
    N > 0,
    M is N - 1,
    Z is X + 1,
    p18(M, Z, Y).

test20 :-
    p18(5, 0, Y),
    show(test20, Y).
% expected: 5
