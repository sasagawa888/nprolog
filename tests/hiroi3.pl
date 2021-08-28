% Thanks to M.Hiroi

next(a, f). next(a, h). next(b, g). next(b, i).
next(c, d). next(c, h). next(d, i). next(d, k).
next(e, j). next(e, l). next(f, g). next(f, k).
next(g, l). next(i, j).

jump(X, Y) :- next(X, Y).
jump(X, Y) :- next(Y, X).

search(12, Path) :-
    reverse(Answer, Path), write(Answer), nl, !, fail.

search(N, [Postion | Rest]) :-
    jump(Postion, NextPostion),
    not(member(NextPostion, Rest)),
    N1 is N + 1,
    search(N1, [NextPostion, Postion | Rest]).

test :- search(1, [a]).