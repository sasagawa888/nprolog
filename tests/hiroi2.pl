%
% komachi.swi : パズル「小町算」の解法
%
%               Copyright (C) 2005 Makoto Hiroi
%

%
% 式の計算 (+, -) だけ
%
calc_one_exp(A, +, B, N):- N is A + B.
calc_one_exp(A, -, B, N):- N is A - B.

calc_exp([Num], Num).
calc_exp([A, Op, B | Rest], Num) :-
    calc_one_exp(A, Op, B, Num1), calc_exp([Num1 | Rest], Num).

%
% 式の生成
%
set_op(N, Exp, [N, + | Exp]).
set_op(N, Exp, [N, - | Exp]).
set_op(N, [N1 | Rest], [N2 | Rest]) :- N2 is N1 * 10 + N.

make_exp(10, Exp) :-
    reverse(Exp, Exp1), calc_exp(Exp1, N), N =:= 100, write(Exp1), nl, fail.

make_exp(N, Exp):-
    N < 10, set_op(N, Exp, Exp1), N1 is N + 1, make_exp(N1, Exp1).

solve :- make_exp(2, [1]).

% リスト：覆面算

% 部分集合の判定
selects([], Ys).
selects([X | Xs], Ys) :- select(X, Ys, Ys1), selects(Xs, Ys1).

% Send + More = Money のチェック
check(S, E, N, D, O, R, Y, Send, More, Money) :-
    Send  is S * 1000 + E * 100 + N * 10 + D,
    More  is 1000 + O * 100 + R * 10 + E,
    Money is 10000 + O * 1000 + N * 100 + E * 10 + Y,
    Money =:= Send + More.

% パズルの解法
solve_puz(Send, More, Money) :-
    selects([S, E, N, D, O, R, Y], [0, 2, 3, 4, 5, 6, 7, 8, 9]),
    check(S, E, N, D, O, R, Y, Send, More, Money).

% ?- solve_puz(Send, More, Money).
