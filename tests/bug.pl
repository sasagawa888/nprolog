

nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
%    D1 is D + 1,
%    nodiag(L, B, D1).

