:- use_module(utils).

run_all :-
    test21, test22, test23, test24, test25,
    test26, test27, test28, test29, test30.

% \+ と ; の優先順位確認
test21 :-
    ( (\+ fail ; true) -> X=ok ; X=ng ),
    writeln(test21),
    writeln(X).

% \+ の中に選言
test22 :-
    ( \+ (fail ; fail) -> X=yes ; X=no ),
    writeln(test22),
    writeln(X).

% \+ の中に成功枝あり
test23 :-
    ( \+ (fail ; true) -> X=yes ; X=no ),
    writeln(test23),
    writeln(X).

% 条件部に連言
test24 :-
    ( (A=1, B=2) -> X=ok ; X=ng ),
    writeln(test24),
    writeln(X).

% 条件部の連言の途中で失敗
test25 :-
    ( (A=1, fail, B=2) -> X=ok ; X=ng ),
    writeln(test25),
    writeln(X).

% 条件部に連言＋選言
test26 :-
    ( ((fail ; A=1), B=2) -> X=A ; X=ng ),
    writeln(test26),
    writeln(X).

% then部に連言＋選言
test27 :-
    ( true -> (A=1, (B=2 ; B=3), X=B) ; X=0 ),
    writeln(test27),
    writeln(X).

% else部に連言＋選言
test28 :-
    ( fail -> X=0 ; (A=1, (B=2 ; B=3), X=B) ),
    writeln(test28),
    writeln(X).

% cut の確認
test29 :-
    ( (A=1, !) -> X=A ; X=ng ),
    writeln(test29),
    writeln(X).

% cut + 選言
test30 :-
    ( ((A=1 ; A=2), !) -> X=A ; X=ng ),
    writeln(test30),
    writeln(X).