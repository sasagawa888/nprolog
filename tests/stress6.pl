:- use_module(utils).

run_all :-
    test1, test2, test3, test4, test5,
    test6, test7, test8, test9, test10.

% 基本ネスト
test1 :-
    ( true -> (fail -> X=a ; X=b) ; X=c ),
    writeln(test1), writeln(X).

% else側に連言
test2 :-
    ( fail -> X=a ; (Y=1, X=Y) ),
    writeln(test2), writeln(X).

% then側に連言
test3 :-
    ( true -> (A=2, X=A) ; X=0 ),
    writeln(test3), writeln(X).

% 未束縛変数が条件に出る
test4 :-
    ( X=1 -> Y=ok ; Y=ng ),
    writeln(test4), writeln(Y).

% 条件が失敗＋変数残存
test5 :-
    ( fail -> X=1 ; true ),
    writeln(test5), writeln(X).

% 算術＋分岐
test6 :-
    N = 0,
    ( N > 0 -> X=pos ; X=zero ),
    writeln(test6), writeln(X).

% ネスト＋算術
test7 :-
    N = 1,
    ( N > 0 ->
        ( N > 10 -> X=big ; X=small )
    ; X=neg ),
    writeln(test7), writeln(X).

% バックトラック絡み（cut的挙動確認）
test8 :-
    ( member(X,[1,2]) -> Y=X ; Y=0 ),
    writeln(test8), writeln(Y).

% 連言＋ネストelse
test9 :-
    ( fail->
        X=a
    ;
        ( true -> X=b ; X=c )
    ),
    writeln(test9), writeln(X).

% 多段 if-then-else（case変換の核心）
test10 :-
    N = -1,
    ( N > 0 ->
        X=pos
    ;
        N =:= 0 ->
            X=zero
    ;
        ( M is N+1, M =:= 0 -> X=minus1 ; X=other )
    ),
    writeln(test10), writeln(X).

