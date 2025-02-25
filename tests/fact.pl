
fact(0,1).
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.

bar(X).
bar(1).
bar(Y).
boo(X).