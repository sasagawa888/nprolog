
fact(0,1).
fact(X,Y) :- 
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.

hanoi(1, From, To, _) :- write([From, to, To]), nl.
hanoi(N, From, To, Via) :-
        N1 is N - 1, hanoi(N1, From, Via, To),
        write([From, to, To]), nl,
        hanoi(N1, Via, To, From).