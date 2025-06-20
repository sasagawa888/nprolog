
perm_inversion([],0).
perm_inversion([X|Xs],N) :-
    perm_inversion1(X,Xs,N1),
    perm_inversion(Xs,N2),
    N is N1+N2.

perm_inversion1(X,[],0).
perm_inversion1(X,[Y|Ys],N) :-
    Y < X,
    perm_inversion1(X,Ys,N1),
    N is N1+1. 
perm_inversion1(X,[Y|Ys],N) :-
    Y >= X,
    perm_inversion1(X,Ys,N).