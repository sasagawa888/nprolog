%fibonacci  max fib(16,X).

fib(0,0).
fib(1,1).
fib(N,X) :-
        N1 is N-1,
        fib(N1,X1),
        N2 is N-1,
        fib(N2,X2),
        X is X1+X2.

foo(X,Y) :- 
        X1 is X-1,
        X2 is X-2,
        mt_and([fib(X1,Y1),fib(X2,Y2)]),
        Y is Y1+Y2.
