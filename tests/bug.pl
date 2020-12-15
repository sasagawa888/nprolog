
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


clear_light1(25, Board, Board, Push, Push) :- !.

clear_light1(N, Board, Result, Push, PushResult) :-
    M is N - 5,
    %write(1),
    (Board /\ (1 << M)) > 0,
    %write(2),
    pattern(N, Pattern),
    %write(3),
    NewBoard is Board xor Pattern,
    write(4),
    NewPush is Push \/ (1 << N),
    write(5),
    N1 is N + 1, !, clear_light1(N1, NewBoard, Result, NewPush, PushResult).

clear_light(N, Board, Result, Push, PushResult) :-
    N1 is N + 1, clear_light1(N1, Board, Result, Push, PushResult).


