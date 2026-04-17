% ----------------------------------------
% stress13.pl
% conjunction-embedded if-then-else tests
% ----------------------------------------

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

show(T) :-
    write(T), nl.

show2(T, X) :-
    write(T), write(' : '), write(X), nl.

show3(T, X, Y) :-
    write(T), write(' : '), write(X), write(','), write(Y), nl.


% 連言の真ん中に単純な if-then-else
test1 :-
    between(0, 9, N),
    (N < 5 -> X = a ; X = b),
    show2(test1, X),
    fail.
test1.

% then 側が連言
test2 :-
    between(0, 5, N),
    (N < 3 -> (A is N + 10, X = A) ; X = ng),
    show2(test2, X),
    fail.
test2.


% else 側が連言
test3 :-
    between(0, 5, N),
    (N < 3 -> X = ok ; A is N - 10, X = A),
    show2(test3, X),
    fail.
test3.

% 前後にゴールあり
test4 :-
    between(0, 5, N),
    write(test4), write(' : '),
    (N mod 2 =:= 0 -> write(e) ; write(o)),
    write(','), write(N), nl,
    fail.
test4.

% 連言の途中で if-then-else、その後にさらに算術
test5 :-
    between(1, 5, N),
    (N < 3 -> A is N + 1 ; A is N + 100),
    B is A * 2,
    show3(test5, A, B),
    fail.
test5.

% if の条件に算術比較
test6 :-
    between(0, 6, N),
    M is N mod 3,
    (M =:= 0 -> X = hit ; X = miss),
    show2(test6, X),
    fail.
test6.

% then 側に 2 個のゴール
test7 :-
    between(1, 4, N),
    (N =< 2 -> (A is N * 10, B is A + 1) ; B is -1),
    show2(test7, B),
    fail.
test7.


% else 側に 2 個のゴール
test8 :-
    between(1, 4, N),
    (N =< 2 -> B = small ; A is N * 10, B is A + 1),
    show2(test8, B),
    fail.
test8.

% ネスト1
test9 :-
    between(0, 5, N),
    (N < 2 ->
        (N =:= 0 -> X = zero ; X = one)
    ;
        X = big
    ),
    show2(test9, X),
    fail.
test9.

% ネスト2: else 側にさらに if
test10 :-
    between(0, 5, N),
    (N < 2 ->
        X = small
    ;
        N < 4 ->
        X = mid
    ;
        X = large
    ),
    show2(test10, X),
    fail.
test10.

% 連言中に if、その後ろにも連言
test11 :-
    between(1, 5, N),
    A is N + 1,
    (A < 4 -> B = low ; B = high),
    C is A * 10,
    write(test11), write(' : '),
    write(B), write(','), write(C), nl,
    fail.
test11.

% print_answer 型に近いもの
test12 :-
    nl,
    between(0, 14, N),
    ((13 /\ (1 << N)) > 0 -> write(1) ; write(0)),
    M is N mod 5,
    (M =:= 4 -> nl ; true),
    fail.
test12.

% 条件が複合連言
test13 :-
    between(0, 6, N),
    M is N mod 2,
    ((N > 2, M =:= 0) -> X = even_big ; X = other),
    show2(test13, X),
    fail.
test13.

% then/else がともに代入ではなく出力
test14 :-
    between(0, 5, N),
    write(test14), write(' : '),
    (N < 3 -> write(left) ; write(right)),
    write(','), write(done), nl,
    fail.
test14.

% 連言の末尾近くで if、その後 fail
test15 :-
    between(0, 5, N),
    (N =:= 3 -> X = hit ; X = miss),
    show2(test15, X),
    fail.
test15.

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

test17 :-
    between(0,5,N),
    (N < 3 ->
        X = left
    ;
        (N < 5 -> X = c ; X = d)
    ),
    write(test17), write(' : '), write(X), nl,
    fail.
test17.

test18 :-
    between(0,5,N),
    (N < 3 ->
        (N < 1 -> X = a ; X = b)
    ;
        X = right
    ),
    write(test18), write(' : '), write(X), nl,
    fail.
test18.

