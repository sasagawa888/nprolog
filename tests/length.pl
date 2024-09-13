
len([],0).
len([_|Ls],N) :- len(Ls,N1),N is N1 + 1.