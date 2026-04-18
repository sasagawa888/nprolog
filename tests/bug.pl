
selects([], Ys).
selects([X | Xs], Ys) :- select(X, Ys, Ys1), selects(Xs, Ys1).
