% Arithmetic / comparison / control stress test for N-Prolog

check(A, B) :-
    Q is A div B,
    R is A mod B,
    T is Q * B + R,
    write((A,B,T)), nl.
/*
?- check(7,2).
7,2,7
yes
?- check(-7,2).
-7,2, -7
yes
?- check(7,-2).
7,-2,7
yes
?- check(-7,-2).
-7,-2, -7
yes
?- 
*/

check2(A, B) :-
    Q is A div B,
    R is A mod B,
    T is Q * B + R,
    write(q=Q), write(' '),
    write(r=R), write(' '),
    write(t=T), nl.

/*
*/

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
%% 1. 比較演算
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test1 :-
    ( 3 < 5 -> write(ok) ; write(ng) ).

test2 :-
    ( 5 =< 5 -> write(ok) ; write(ng) ).

test3 :-
    ( 5 =:= 2 + 3 -> write(eq) ; write(ne) ).

test4 :-
    ( 5 =\= 2 + 2 -> write(ok) ; write(ng) ).

test5 :-
    ( 3 > 5 -> write(ng) ; write(ok) ).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 2. 負数を含む整数除算・剰余
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test6 :-
    X is -7 // 2,
    write(X).              % 実装依存になりうる

test7 :-
    X is -7 mod 2,
    write(X).              % 実装依存になりうる


test8 :-
    X is 7 mod (-2),
    write(X).              % 実装依存になりうる

test9 :-
    X is -7 mod (-2),
    write(X).              % 実装依存になりうる


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 3. 算術関数
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test10 :-
    X is abs(-5),
    write(X).              % 5

test11 :-
    X is sin(0),
    write(X).              % 0.0

test12 :-
    X is cos(0),
    write(X).              % 1.0

test13 :-
    X is sqrt(9),
    write(X).              % 3.0


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 4. 優先順位・単項マイナス
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test14 :-
    X is 1 + 2 * 3 - 4 // 2,
    write(X).              % 5

test15 :-
    X is -(1 + 2) * 3,
    write(X).              % -9

test16 :-
    X is (-1) * (-2) + 3,
    write(X).              % 5

test17 :-
    X is -(-3),
    write(X).              % 3

test18 :-
    X is -(2 * 3),
    write(X).              % -6


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 5. if-then-else と算術
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p1(N, X) :-
    ( N > 0 ->
        X is N * 2
    ;
        X is N - 2
    ).

test19 :-
    p1(3, X),
    write(X).              % 6

test20 :-
    p1(0, X),
    write(X).              % -2


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 6. 分岐 + 再帰 + 算術
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

q1(0, A, A).
q1(N, A, X) :-
    ( N mod 2 =:= 0 ->
        B is A + 10
    ;
        B is A + 1
    ),
    M is N - 1,
    q1(M, B, X).

test21 :-
    q1(4, 0, X),
    write(X).              % 22


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 7. 乗算を含む末尾再帰
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fact_acc(0, A, A).
fact_acc(N, A, X) :-
    N > 0,
    B is A * N,
    M is N - 1,
    fact_acc(M, B, X).

test22 :-
    fact_acc(5, 1, X),
    write(X).              % 120


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 8. 一時変数の連鎖
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test23 :-
    A = 2,
    B = 3,
    C is A + B,
    D is C * 4,
    E is D - A,
    F is E // 3,
    write(F).              % 6

test24 :-
    A = 5,
    B = 2,
    C is A * B,
    D is C + A,
    E is D - B,
    write(E).              % 13


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 9. 少し深い算術ネスト
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test25 :-
    X is ((2 + 3) * (4 + 1) - (6 // 2)) + abs(-4),
    write(X).              % 26