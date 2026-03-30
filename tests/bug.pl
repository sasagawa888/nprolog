
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% test_ifthen.pl
% Tests for A -> B ; C   and   A -> B
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 基本事実
a.
b.
c.

p(1).
p(2).

q(2).
q(3).

r(hello).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 1. 基本動作
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test1(X) :-
    ( true -> X = yes ; X = no ).

test2(X) :-
    ( fail -> X = yes ; X = no ).

test3(X) :-
    ( a -> X = ok ; X = ng ).

test4(X) :-
    ( zzz -> X = ok ; X = ng ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2. A -> B の動作
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test5(X) :-
    ( true -> X = yes ).

test6(X) :-
    ( fail -> X = yes ).

test7(X) :-
    ( a -> X = ok ).

test8(X) :-
    ( zzz -> X = ok ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 3. then部が失敗する場合
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test9(X) :-
    ( true -> fail ; X = else_branch ).

test10(X) :-
    ( fail -> fail ; X = else_branch ).

test11(X) :-
    ( a -> fail ).

test12(X) :-
    ( zzz -> fail ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 4. 条件部の複合 goal
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test13(X) :-
    ( (a,b) -> X = yes ; X = no ).

test14(X) :-
    ( (a,zzz) -> X = yes ; X = no ).

test15(X) :-
    ( (fail;b) -> X = yes ; X = no ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 5. 条件部の choice point の扱い
% ISO風なら A が成功した時点で then へ進み、
% 条件部の別解には戻らないことを確認
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test16(X) :-
    ( p(X) -> true ; X = none ).

test17(X) :-
    ( q(X) -> true ; X = none ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 6. then部に choice point がある場合
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test18(X,Y) :-
    ( a -> p(X) ; X = 0 ),
    Y = done.

test19(X,Y) :-
    ( fail -> p(X) ; X = 0 ),
    Y = done.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 7. else部に choice point がある場合
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test20(X,Y) :-
    ( a -> X = 100 ; p(X) ),
    Y = done.

test21(X,Y) :-
    ( fail -> X = 100 ; p(X) ),
    Y = done.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 8. 変数束縛の確認
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test22(X) :-
    ( true -> X = 10 ; X = 20 ).

test23(X) :-
    ( fail -> X = 10 ; X = 20 ).

test24(X,Y) :-
    ( X = 1 -> Y = yes ; Y = no ).

test25(X,Y) :-
    ( X = 1, fail -> Y = yes ; Y = no ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 9. ネストした if-then-else
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test26(X) :-
    ( a ->
        ( b -> X = ab ; X = a_not_b )
    ;
        X = no_a
    ).

test27(X) :-
    ( a ->
        ( zzz -> X = az ; X = a_not_z )
    ;
        X = no_a
    ).

test28(X) :-
    ( zzz ->
        ( b -> X = zb ; X = z_not_b )
    ;
        X = no_z
    ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 10. A -> B ; C と (A -> B) ; C の優先順位確認
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test29(X) :-
    ( true -> fail ; X = else1 ).

test30(X) :-
    ( (true -> fail) ; X = else2 ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 11. カット的ふるまいの確認用
% 条件部で成功したら else へ行かない
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test31(X) :-
    ( p(_) -> X = then_branch ; X = else_branch ).

test32(X) :-
    ( zzz -> X = then_branch ; X = else_branch ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 12. 実行確認用ドライバ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

run_tests :-
    write('test1  : '),  test1(X1),   write(X1), nl,
    write('test2  : '),  test2(X2),   write(X2), nl,
    write('test3  : '),  test3(X3),   write(X3), nl,
    write('test4  : '),  test4(X4),   write(X4), nl,

    write('test5  : '),  test5(X5),   write(X5), nl,
    write('test6  : '),  (test6(X6) -> write(X6) ; write(fail)), nl,
    write('test7  : '),  test7(X7),   write(X7), nl,
    write('test8  : '),  (test8(X8) -> write(X8) ; write(fail)), nl,

    write('test9  : '),  (test9(X9) -> write(X9) ; write(fail)), nl,
    write('test10 : '),  test10(X10), write(X10), nl,
    write('test11 : '),  (test11(X11) -> write(X11) ; write(fail)), nl,
    write('test12 : '),  (test12(X12) -> write(X12) ; write(fail)), nl,

    write('test13 : '),  test13(X13), write(X13), nl,
    write('test14 : '),  test14(X14), write(X14), nl,
    write('test15 : '),  test15(X15), write(X15), nl,

    write('test16 : '),  test16(X16), write(X16), nl,
    write('test17 : '),  test17(X17), write(X17), nl,

    write('test18 : '),  test18(X18,Y18), write((X18,Y18)), nl, fail.
run_tests :-
    test19(X19,Y19), write('test19 : '), write((X19,Y19)), nl,
    test20(X20,Y20), write('test20 : '), write((X20,Y20)), nl,
    fail.
run_tests :-
    test21(X21,Y21), write('test21 : '), write((X21,Y21)), nl,
    fail.

/*
run_tests :-
    test22(X22), write('test22 : '), write(X22), nl,
    test23(X23), write('test23 : '), write(X23), nl,
    test24(X24,Y24), write('test24 : '), write((X24,Y24)), nl,
    test25(X25,Y25), write('test25 : '), write((X25,Y25)), nl,
    test26(X26), write('test26 : '), write(X26), nl,
    test27(X27), write('test27 : '), write(X27), nl,
    test28(X28), write('test28 : '), write(X28), nl,
    (test29(X29) -> write('test29 : '), write(X29), nl ; write('test29 : fail'), nl),
    (test30(X30) -> write('test30 : '), write(X30), nl ; write('test30 : fail'), nl),
    test31(X31), write('test31 : '), write(X31), nl,
    test32(X32), write('test32 : '), write(X32), nl.
*/