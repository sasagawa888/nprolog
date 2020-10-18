
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

bar(0).
bar(N) :-
    N1 is N-1,
    bar(N1).

myappend([],L,L) :- !.
myappend([A|L],B, [A|C]):-
	myappend(L,B,C).

intersection([],Y,[]).
intersection([X|Xs],Y,[X|Z]) :-
    member(X,Y),
    intersection(Xs,Y,Z).
intersection([X|Xs],Y,Z) :-
    intersection(Xs,Y,Z).

union([],Y,Y).
union([X|Xs],Y,Z) :-
    member(X,Y),
    union(Xs,Y,Z).
union([X|Xs],Y,[X|Z]) :-
    union(Xs,Y,Z).
