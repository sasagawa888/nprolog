/*
written by M.Hiroi
Thanks 

?- solve(0x1ffffff).
*/


pattern(0, 0x0000023). pattern(1, 0x0000047). pattern(2, 0x000008e). pattern(3, 0x000011c).
pattern(4, 0x0000218). pattern(5, 0x0000461). pattern(6, 0x00008e2). pattern(7, 0x00011c4).
pattern(8, 0x0002388). pattern(9, 0x0004310). pattern(10, 0x0008c20). pattern(11, 0x0011c40).
pattern(12, 0x0023880). pattern(13, 0x0047100). pattern(14, 0x0086200). pattern(15, 0x0118400).
pattern(16, 0x0238800). pattern(17, 0x0471000). pattern(18, 0x08e2000). pattern(19, 0x10c4000).
pattern(20, 0x0308000). pattern(21, 0x0710000). pattern(22, 0x0e20000). pattern(23, 0x1c40000).
pattern(24, 0x1880000).

test :-
    solve(0x1ffffff).


solve(Board) :-
    between(0, 31, N),
    push_button(N, 0, Board, NewBoard),
    clear_light(5, NewBoard, Result, N, PushPattern),
    Result == 0,
    print_answer(PushPattern).

push_button(_, 5, Board, Board) :- !.

push_button(N, M, Board, Result) :-
    ((1 << M) /\ N) > 0,          % ビットオンならばボタンを押す
    pattern(M, Pattern),
    NewBoard is Board xor Pattern,
    M1 is M + 1, !, push_button(N, M1, NewBoard, Result).

push_button(N, M, Board, Result) :-
    M1 is M + 1, push_button(N, M1, Board, Result).

clear_light(25, Board, Board, Push, Push) :- !.

clear_light(N, Board, Result, Push, PushResult) :-
    M is N - 5,
    (Board /\ (1 << M)) > 0,
    pattern(N, Pattern),
    NewBoard is Board xor Pattern,
    NewPush is Push \/ (1 << N),
    N1 is N + 1, !, clear_light(N1, NewBoard, Result, NewPush, PushResult).

clear_light(N, Board, Result, Push, PushResult) :-
    N1 is N + 1, clear_light(N1, Board, Result, Push, PushResult).

print_answer(PushPattern) :-
    nl,
    between(0, 24, N),
    ((PushPattern /\ (1 << N)) > 0 -> write('1') ; write('0')),
    M is N mod 5,
    (M == 4 -> nl),
    fail.