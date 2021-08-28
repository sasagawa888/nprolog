% test for robustness 

ack(0,N,A) :- 
    A is N+1,asserta(ack(0,N,A)).
ack(M,0,A) :- 
    M1 is M-1,ack(M1,1,A),
    asserta(ack(M1,1,A)),
    asserta(ack(M,0,A)).
ack(M,N,A) :- 
    M1 is M-1,N1 is N-1,
    ack(M,N1,A1), ack(M1,A1,A),
    asserta(ack(M,N1,A1)),
    asserta(ack(M1,A1,A)).
