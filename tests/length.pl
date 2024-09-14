% length naive definition. it has problem when backtrack.

len([],0).
len([L|Ls],N) :- len(Ls,N1),N is N1+1.
 