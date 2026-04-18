% TCO stress test for N-Prolog
% 目的:
%   1. tail と判定すべきもの
%   2. tail と判定してはいけないもの
%   3. conjunction / disjunction / if-then-else / cut / built-in を含むもの
% をまとめて検証する

show(Test, Goal) :-
    write(Test),
    write(' : '),
    call(Goal),
    nl.

run_all :-
    show(test1, test1),
    show(test2, test2),
    show(test3, test3),
    show(test4, test4),
    show(test5, test5),
    show(test6, test6),
    show(test7, test7),
    show(test8, test8),
    show(test9, test9),
    show(test10, test10),
    show(test11, test11),
    show(test12, test12),
    show(test13, test13),
    show(test14, test14),
    show(test15, test15),
    show(test16, test16),
    show(test17, test17),
    show(test18, test18),
    show(test19, test19),
    show(test20, test20),
    show(test21, test21),
    show(test22, test22),
    show(test23, test23),
    show(test24, test24),
    show(test25, test25).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 1. これは tail と判定すべき
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test1: 最も基本的な末尾再帰
t1(0, A, A).
t1(N, A, X) :-
    N > 0,
    B is A + N,
    M is N - 1,
    t1(M, B, X).

test1 :-
    t1(5, 0, X),
    write(X).              % 15

% test2: 構造体生成をしてから末尾再帰
t2(0, X, X).
t2(N, A, X) :-
    N > 0,
    B = foo(A, N),
    M is N - 1,
    t2(M, B, X).

test2 :-
    t2(3, z, X),
    write(X).              % foo(foo(foo(z,3),2),1)

% test3: 条件分岐あり、各枝の最後が再帰
t3(0, A, A).
t3(N, A, X) :-
    ( N > 0 ->
        B is A + 1,
        M is N - 1,
        t3(M, B, X)
    ;
        X = A
    ).

test3 :-
    t3(4, 10, X),
    write(X).              % 14

% test4: else側も再帰
t4(0, A, A).
t4(N, A, X) :-
    ( N > 0 ->
        B is A + N,
        M is N - 1,
        t4(M, B, X)
    ;
        B is A - 1,
        t4(0, B, X)
    ).

test4 :-
    t4(3, 0, X),
    write(X).              % 5

% test5: cut の後に末尾再帰
t5(0, A, A) :- !.
t5(N, A, X) :-
    N > 0,
    !,
    B is A + 2,
    M is N - 1,
    t5(M, B, X).

test5 :-
    t5(3, 0, X),
    write(X).              % 6

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 2. これは tail と判定してはいけない
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test6: 再帰呼び出しのあとに is/2
t6(0, 0).
t6(N, X) :-
    N > 0,
    M is N - 1,
    t6(M, Y),
    X is Y + 1.

test6 :-
    t6(5, X),
    write(X).              % 5

% test7: 再帰呼び出しのあとに構造体化
t7(0, z).
t7(N, X) :-
    N > 0,
    M is N - 1,
    t7(M, Y),
    X = s(Y).

test7 :-
    t7(3, X),
    write(X).              % s(s(s(z)))

% test8: 再帰呼び出しのあとに write/1
t8(0).
t8(N) :-
    N > 0,
    M is N - 1,
    t8(M),
    write(done).

test8 :-
    t8(2).                 % donedone

% test9: 再帰呼び出しのあとに比較
t9(0, 0).
t9(N, X) :-
    N > 0,
    M is N - 1,
    t9(M, X),
    X >= 0.

test9 :-
    t9(3, X),
    write(X).              % 0

% test10: 再帰呼び出しのあとに cut
t10(0).
t10(N) :-
    N > 0,
    M is N - 1,
    t10(M),
    !.

test10 :-
    t10(3),
    write(ok).             % ok

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 3. 判定を誤りやすい連言
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test11: 再帰の前に無関係な処理、最後が再帰 -> tail
t11(0, A, A).
t11(N, A, X) :-
    N > 0,
    dummy11(A),
    B is A + 1,
    M is N - 1,
    t11(M, B, X).

dummy11(_).

test11 :-
    t11(3, 0, X),
    write(X).              % 3

% test12: 再帰の後に true -> 非tail
t12(0).
t12(N) :-
    N > 0,
    M is N - 1,
    t12(M),
    true.

test12 :-
    t12(3),
    write(ok).             % ok

% test13: 再帰の後に unification -> 非tail
t13(0, z).
t13(N, X) :-
    N > 0,
    M is N - 1,
    t13(M, Y),
    X = Y.

test13 :-
    t13(2, X),
    write(X).              % z

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 4. 選言・if-then-else まわり
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test14: 各枝とも最後が再帰 -> tail
t14(0, A, A).
t14(N, A, X) :-
    ( N mod 2 =:= 0 ->
        B is A + 10,
        M is N - 1,
        t14(M, B, X)
    ;
        B is A + 1,
        M is N - 1,
        t14(M, B, X)
    ).

test14 :-
    t14(4, 0, X),
    write(X).              % 22

% test15: then枝はtail, else枝は非tail
t15(0, 0).
t15(N, X) :-
    ( N > 0 ->
        M is N - 1,
        t15(M, X)
    ;
        t15(0, Y),
        X is Y + 1
    ).

test15 :-
    t15(3, X),
    write(X).              % 0

% test16: 選言の片側だけ末尾でない
t16(0, 0).
t16(N, X) :-
    ( N =:= 0, X = 0
    ;
      N > 0,
      M is N - 1,
      t16(M, Y),
      X is Y + 1
    ).

test16 :-
    t16(3, X),
    write(X).              % 3

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 5. 非決定性がからむケース
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test17: member/2 の後で再帰
t17([], A, A).
t17([X|Xs], A, Y) :-
    member(X, [1,2,3]),
    B is A + X,
    t17(Xs, B, Y).

test17 :-
    t17([1,2], 0, X),
    write(X).              % 3 が少なくとも一つ出る

% test18: 再帰呼び出し自体がchoice pointを持ちうる
t18(0, 0).
t18(N, X) :-
    N > 0,
    M is N - 1,
    t18(M, X).
t18(N, X) :-
    N > 0,
    M is N - 1,
    t18(M, Y),
    X is Y + 1.

test18 :-
    t18(2, X),
    write(X).              % 複数解ありうる

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 6. 相互再帰
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% self tail だけでなく mutual tail をどう扱うか確認
even_t(0).
even_t(N) :-
    N > 0,
    M is N - 1,
    odd_t(M).

odd_t(0) :-
    fail.
odd_t(N) :-
    N > 0,
    M is N - 1,
    even_t(M).

test19 :-
    even_t(4),
    write(ok).             % ok

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 7. accumulator 変数の依存関係チェック
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test20: A から B を作り B を渡す -> tail
t20(0, A, A).
t20(N, A, X) :-
    N > 0,
    B is A + N,
    M is N - 1,
    t20(M, B, X).

test20 :-
    t20(4, 0, X),
    write(X).              % 10

% test21: 再帰後に旧変数Aを使ってしまう -> 非tail
t21(0, _, 0).
t21(N, A, X) :-
    N > 0,
    M is N - 1,
    t21(M, A, Y),
    X is Y + A.

test21 :-
    t21(3, 2, X),
    write(X).              % 6

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 8. 組み込み述語が絡むケース
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test22: 再帰前の比較・算術のみ -> tail
t22(0, A, A).
t22(N, A, X) :-
    N > 0,
    N =< 1000,
    B is A + 3,
    M is N - 1,
    t22(M, B, X).

test22 :-
    t22(3, 0, X),
    write(X).              % 9

% test23: 再帰後に比較 -> 非tail
t23(0, 0).
t23(N, X) :-
    N > 0,
    M is N - 1,
    t23(M, X),
    X =:= 0.

test23 :-
    t23(3, X),
    write(X).              % 0

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 9. かなり紛らわしい if-then-else
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% test24: then/elseとも最後は再帰 -> tail
t24(0, A, A).
t24(N, A, X) :-
    ( N > 5 ->
        B is A + 100,
        M is N - 1,
        t24(M, B, X)
    ;
        N > 0 ->
        B is A + 1,
        M is N - 1,
        t24(M, B, X)
    ;
        X = A
    ).

test24 :-
    t24(3, 0, X),
    write(X).              % 3

% test25: else側の連言の最後が再帰でない -> 非tail
t25(0, A, A).
t25(N, A, X) :-
    ( N > 0 ->
        B is A + 1,
        M is N - 1,
        t25(M, B, X)
    ;
        t25(0, A, Y),
        X = Y
    ).

test25 :-
    t25(2, 0, X),
    write(X).              % 2