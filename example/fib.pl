 

fib(0, R) :- !, R = 0. 
fib(1, R) :- !, R = 1. 
fib(N, X) :- M is N-1, fib(M, Y), K is M-1, fib(K, Z), X is Y+Z. 
