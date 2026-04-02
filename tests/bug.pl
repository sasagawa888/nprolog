
% compile error

check_dyn1(X, yes) :-
    (dyn1(X) -> true ; fail ).
check_dyn1(X, no) :-
    call(dyn1(X)).

