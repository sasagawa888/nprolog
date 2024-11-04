foo(X) :- write(X),!,write(X).

max(X,Y,X) :- X>=Y,!.
max(X,Y,Y).

fact(0,1) :- !.
fact(X,Y) :- 
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.