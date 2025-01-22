
my_select(X, [X | Xs], Xs).
my_select(X, [Y | Ys], [Y | Zs]) :- my_select(X, Ys, Zs).