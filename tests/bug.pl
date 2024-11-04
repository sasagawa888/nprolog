
foo(X) :- bar(X,Y),write(Y).

bar(X) :- fail;fail;true.

boo(X) :- write(X),!,write(X).

fact(0,1).
fact(N,X) :-
    N1 is N-1,
    fact(N1,X1),
    X is N*X1.
