

listn(0,[]).
listn(N,[R|X]) :- R is randi(100),N1 is N-1,listn(N1,X). 
