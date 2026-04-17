:- use_module(utils).

run_all :-
    test31, test32, test33, test34, test35,
    test36, test37, test38, test39, test40.

% 基本: 算術比較
test31 :-
    N = 5,
    ( N > 0 -> X=pos ; X=neg ),
    writeln(test31),
    writeln(X).

% 多段分岐 + 算術比較
test32 :-
    N = 0,
    ( N > 0 ->
        X=pos
    ; N =:= 0 ->
        X=zero
    ;
        X=neg
    ),
    writeln(test32),
    writeln(X).
/*
% then側で is/2
test33 :-
    N = 3,
    ( N > 0 ->
        M is N + 10,
        X = M
    ;
        X = 0
    ),
    writeln(test33),
    writeln(X).
*/


% else側で is/2
test34 :-
    N = -2,
    ( N > 0 ->
        X = 0
    ;
        M is N - 10,
        X = M
    ),
    writeln(test34),
    writeln(X).

% 条件部に連言 + 算術比較
test35 :-
    N = 4,
    ( (N > 0, N < 10) -> X=small ; X=other ),
    writeln(test35),
    writeln(X).

% 条件部に選言 + 算術比較
test36 :-
    N = 10,
    ( (N < 0 ; N =:= 10) -> X=hit ; X=miss ),
    writeln(test36),
    writeln(X).

% 条件部で is/2 + 比較
test37 :-
    N = 2,
    ( (M is N + 1, M =:= 3) -> X=ok ; X=ng ),
    writeln(test37),
    writeln(X).

% then側に選言を含む算術
/*
test38 :-
    N = 1,
    ( N > 0 ->
        (M is N + 1 ; M is N + 2),
        X = M
    ;
        X = 0
    ),
    writeln(test38),
    writeln(X).
*/

% else側に選言を含む算術
test39 :-
    N = -1,
    ( N > 0 ->
        X = 0
    ;
        (M is N - 1 ; M is N - 2),
        X = M
    ),
    writeln(test39),
    writeln(X).

/*
% cut + 算術
test40 :-
    N = 1,
    ( ((N =:= 1 ; N =:= 2), !) ->
        M is N + 100,
        X = M
    ;
        X = 0
    ),
    writeln(test40),
    writeln(X).
*/