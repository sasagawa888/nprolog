foo(N) :-
    N1 is N+1,foo(N1).


divisor(N,L) :-
    divisor1(N,N,L).

divisor1(N,0,[]).
divisor1(N,M,[M|L]) :-
    0 is N mod M,
    M1 is M-1,
    divisor1(N,M1,L).
divisor1(N,M,L) :-
    M1 is M-1,
    divisor1(N,M1,L).


perfect(N) :-
    divisor(N,[L|Ls]),
    sigma(Ls,M),!,
    N == M.

sigma([],0).
sigma([L|Ls],N) :-
    sigma(Ls,M),
    N is L+M.