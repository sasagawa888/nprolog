% ========================================
% Prolog 比較・評価テスト
% == / =:= / is の違い確認
% ========================================

% ---- 1. 構文的同一性 (==) ----

test1 :- 1+2 == 1+2.
test2 :- \+ (1+2 == 3+0).
test3 :- \+ (1+2 == 2+1).
test4 :- (1+(2)) == (1+2).

% ---- 2. 算術比較 (=:=) ----

test5 :- 1+2 =:= 3+0.
test6 :- 2*3 =:= 3*2.
test7 :- 10-3 =:= 2+5.

% ---- 3. is/2 ----

test8(X) :- X is 1+2.

test9(X) :-
    A = 3,
    X is A*2.

test10 :-
    Y = 1,
    \+ (X is Y+1, X = 3).

% ---- 4. 混合 ----

test11 :-
    X is 1+2,
    X == 3.

test12 :-
    X is 1+2,
    X =:= 3.

test13 :-
    X is 3,
    \+ (X == 1+2).

% ---- 5. 再評価（バックトラック確認） ----

test14(Y) :-
    member(X,[1,2,3]),
    Y is X*10.

% ---- 6. 明確な対比 ----

test15 :- \+ (1+2 == 3).
test16 :- 1+2 =:= 3.


% ========================================
% テストランナー
% ========================================

run :-
    run_test(test1),
    run_test(test2),
    run_test(test3),
    run_test(test4),
    run_test(test5),
    run_test(test6),
    run_test(test7),
    run_test(test10),
    run_test(test11),
    run_test(test12),
    run_test(test13),
    run_test(test15),
    run_test(test16),
    write('--- tests done ---'), nl.

run_test(Name) :-
    ( call(Name) ->
        (write(Name), write(' : ok'), nl)
    ;
        (write(Name), write(' : ng'), nl)
    ).