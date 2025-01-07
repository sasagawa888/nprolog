foo([],0).
foo([X|Xs],N) :- foo(Xs,N1),N is N1+1.