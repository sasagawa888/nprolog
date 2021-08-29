%
% kaeru.swi : 蛙跳びゲーム
%
%             Copyright (C) 2005 Makoto Hiroi
%

% 新しい局面の生成
new_state([b, s | Rest], [s, b | Rest]).
new_state([s, w | Rest], [w, s | Rest]).
new_state([b, w, s | Rest], [s, w, b | Rest]).
new_state([s, b, w | Rest], [w, b, s | Rest]).
new_state([X | R1], [X | R2]) :- new_state(R1, R2).

% 手順の表示
print_answer([]) :- !.
print_answer([State | Rest]) :-
    print_answer(Rest), write(State), nl. 

% 反復深化による解法
depth_search(Limit, Limit, [State | History]) :-
    State == [w,w,w,s,b,b,b], 
    write(Limit),nl,
    print_answer([State | History]),
    fail.

depth_search(N, Limit, [State | History]) :-
    N < Limit,
    new_state(State, NewState),
    not(member(NewState, History)),
    N1 is N + 1, 
    depth_search(N1, Limit, [NewState, State | History]).

solve :- 
    between(1, 20, N),
    depth_search(0, N, [[b,b,b,s,w,w,w]]).

