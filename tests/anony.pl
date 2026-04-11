%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Anonymous variable (_) tests for compiler correctness
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ① 基本：無名変数は独立
test_anon1 :-
    ( _ = a, _ = b -> write('OK'), nl
    ; write('NG'), nl ).

% ② 同一節内での独立性
test_anon2 :-
    ( (_ = X, _ = X) ->
        write('OK'), nl
    ;   write('NG'), nl ).

% ③ 構造内
test_anon3 :-
    ( f(_, _) = f(a, b) ->
        write('OK'), nl
    ; write('NG'), nl ).

% ④ 同一化してはいけないケース（重要）
test_anon4 :-
    ( f(_, _) = f(X, X) ->
        write('OK'), nl
    ; write('NG'), nl ).

% ⑤ DCG 基本
:- use_module(dcg).

test_anon_dcg -->
    [_],
    [_].

% ?- phrase(test_anon_dcg, [a,b]).  % true

% ⑥ DCG 同一化チェック
test_anon_dcg2 -->
    [X],
    [X].

% ?- phrase(test_anon_dcg2, [a,b]). % false

test_anon_dcg3 -->
    [_],
    [_].

% ?- phrase(test_anon_dcg3, [a,b]). % true

% ⑦ findall
test_anon5(Result) :-
    findall(_, member(_, [a,b,c]), Result).

% 期待: Result = [_,_,_]

% ⑧ 強力チェック（同一化バグ検出）
test_anon6 :-
    ( (_ = X, _ = Y, X == Y) ->
        write('OK'), nl
    ; write('NG'), nl ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 一括実行
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

run_all_tests :-
    write('test_anon1: '), test_anon1,
    write('test_anon2: '), test_anon2,
    write('test_anon3: '), test_anon3,
    write('test_anon4: '), test_anon4,
    write('test_anon6: '), test_anon6,
    write('test_anon5: '),
    test_anon5(R), write(R), nl,
    write('DCG test_anon_dcg: '),
    ( phrase(test_anon_dcg, [a,b]) -> write('OK') ; write('NG') ), nl,
    write('DCG test_anon_dcg2: '),
    ( phrase(test_anon_dcg2, [a,b]) -> write('NG') ; write('OK') ), nl,
    write('DCG test_anon_dcg3: '),
    ( phrase(test_anon_dcg3, [a,b]) -> write('OK') ; write('NG') ), nl.