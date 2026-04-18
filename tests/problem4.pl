%
% problem4.pl : 宣教師と先住民
%
%               Copyright (C) 2005-2023 Makoto Hiroi
%
% データ
% [Boat, M_left, E_left, M_right, E_right]
% Boat    : left or right
% M_left  : 左岸にいる宣教師の数
% E_left  : 左岸にいる先住民の数
% M_right : 左岸にいる宣教師の数
% E_right : 左岸にいる先住民の数
:- use_module(utils).　% for format/3
% ボートに乗る組み合わせ : boat(M, E)
boat(1, 0).
boat(0, 1).
boat(1, 1).
boat(2, 0).
boat(0, 2).

% 移動
move_boat([left,A,B,C,D], [right,A1,B1,C1,D1]) :-
    boat(X, Y),
    A1 is A - X,
    A1 >= 0,
    B1 is B - Y, 
    B1 >= 0,
    C1 is C + X,
    D1 is D + Y.

move_boat([right,A,B,C,D], [left,A1,B1,C1,D1]) :-
    boat(X, Y),
    C1 is C - X,
    C1 >= 0,
    D1 is D - Y,
    D1 >= 0,
    A1 is A + X,
    B1 is B + Y.

% 安全確認
safe([_,A,B,C,D]) :- A >= B, C >= D.
safe([_,0,_,_,_]).
safe([_,_,_,0,_]).

% 手順の表示
print_answer([]) :- !.
print_answer([State | Rest]) :-
    print_answer(Rest), write(State), nl. 

% 反復深化
depth_search(Limit, Limit, [State | History]) :-
    State == [right,0,0,3,3],
    format(user_output,"----- ~D -----~n", [Limit]),
    print_answer([State | History]).

depth_search(N, Limit, [State | History]) :-
    N < Limit,
    move_boat(State, NewState),
    safe(NewState),
    not(member(NewState, History)),
    N1 is N + 1,
    depth_search(N1, Limit, [NewState, State | History]).

solver4 :- 
    between(1, 15, N),
    depth_search(0, N, [[left,3,3,0,0]]).