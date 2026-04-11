

% ⑧ 強力チェック（同一化バグ検出）
test_anon6 :-
    ( (_ = X, _ = Y, X == Y) ->
        write('OK'), nl
    ; write('NG'), nl ).



test9(X) :-
    ( true -> fail ; X = else_branch ).

