partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.


nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).

foo(0).
foo(N) :-
    N1 is N-1,
    foo(N1).
foo(N) :-
    N1 is N-1,
    foo(N1).

fact(0,1).
fact(N,X) :-
    N1 is N-1,
    fact(N1,X1),
    X is N*X1.


safe(R,C) :- 
    R >= 1,R =< 5,
    C >= 1,C =< 5.


move(_,_,P,P) :-
    length(P,25).

move(R,C,P,A) :-
    R1 is R+2,
    C1 is C+1,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).
