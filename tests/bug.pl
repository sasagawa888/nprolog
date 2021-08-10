foo([X|Y]) :- write(X),write(Y).

max_list([N],N) :- write(N).
max_list([L|Ls],L) :-
    max_list(Ls,Y),
    L >= Y.
max_list([L|Ls],Y) :-
    max_list(Ls,Y),
    L < Y.