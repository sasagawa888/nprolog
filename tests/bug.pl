

% ⑧ 強力チェック（同一化バグ検出）
test_anon6 :-
    ( (_ = X, _ = Y, X == Y) ->
        write('OK'), nl
    ; write('NG'), nl ).



p(1).
p(2).


test31(X) :-
    ( p(_) -> X = then_branch ; X = else_branch ).


