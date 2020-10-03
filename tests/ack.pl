% test for optimization 
ack(0,N,X) :- X is N+1.
ack(M, 0, X) :- M>0, M1 is M-1, ack(M1, 1, X).
ack(M, N, X) :- M>0, N>0, M1 is M-1, N1 is N-1, ack(M, N1, X1), ack(M1, X1, X).