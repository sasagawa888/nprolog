% test for association 


fib(0,0). 
fib(1,1). 
fib(N,A) :-
    N1 is N-1, N2 is N-2,
    fib(N1,A1),fib(N2,A2),
    A is A1+A2,
    asserta(fib(N,A)).

