
% compile error

check_dyn1(X, yes) :-
    (dyn1(X) -> true ; fail ).
check_dyn1(X, no) :-
    \+ dyn1(X).

