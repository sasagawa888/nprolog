% short_stress.pl
%
% N-Prolog short stress test
% check:
%   - deterministic predicates
%   - nondeterministic predicates
%   - recursion
%   - arithmetic
%   - list processing
%   - if-then-else
%   - nested if-then-else

% ----------------------------
% basic deterministic
% ----------------------------

inc1(X, Y) :-
    Y is X + 1.

classify(N, X) :-
    ( N < 0 ->
        X = neg
    ; N =:= 0 ->
        X = zero
    ; N < 10 ->
        X = small
    ; N < 100 ->
        X = medium
    ;
        X = large
    ).

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

% ----------------------------
% recursion
% ----------------------------

fact(0, 1).
fact(N, F) :-
    N > 0,
    N1 is N - 1,
    fact(N1, F1),
    F is N * F1.

sumlist([], 0).
sumlist([X|Xs], S) :-
    sumlist(Xs, S1),
    S is X + S1.

% ----------------------------
% nondeterministic
% ----------------------------

memb(X, [X|_]).
memb(X, [_|Xs]) :-
    memb(X, Xs).

choose_pair(X, Y) :-
    memb(X, [a,b,c]),
    memb(Y, [1,2]).

% ----------------------------
% list processing
% ----------------------------

append1([], Ys, Ys).
append1([X|Xs], Ys, [X|Zs]) :-
    append1(Xs, Ys, Zs).

reverse1([], []).
reverse1([X|Xs], Ys) :-
    reverse1(Xs, Zs),
    append1(Zs, [X], Ys).

% ----------------------------
% test runner
% ----------------------------

test1 :-
    inc1(1, X),
    write('test1: '), write(X), nl.

test2 :-
    classify(-5, X),
    write('test2: '), write(X), nl.

test3 :-
    classify(0, X),
    write('test3: '), write(X), nl.

test4 :-
    classify(7, X),
    write('test4: '), write(X), nl.

test5 :-
    classify(55, X),
    write('test5: '), write(X), nl.

test6 :-
    classify(123, X),
    write('test6: '), write(X), nl.

test7 :-
    nested_classify(-1, X),
    write('test7: '), write(X), nl.

test8 :-
    nested_classify(5, X),
    write('test8: '), write(X), nl.

test9 :-
    nested_classify(15, X),
    write('test9: '), write(X), nl.

test10 :-
    nested_classify(30, X),
    write('test10: '), write(X), nl.

test11 :-
    fact(5, X),
    write('test11: '), write(X), nl.

test12 :-
    sumlist([1,2,3,4,5], X),
    write('test12: '), write(X), nl.

test13 :-
    append1([a,b], [c,d], X),
    write('test13: '), write(X), nl.

test14 :-
    reverse1([1,2,3,4], X),
    write('test14: '), write(X), nl.

test15 :-
    choose_pair(X, Y),
    write('test15: '), write(X), write(','), write(Y), nl,
    fail.
test15.

test_all :-
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

    