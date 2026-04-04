:- dynamic(dyn1/1).

reset_dyn :-
    retractall(dyn1(_)).

set_dyn :-
    assertz(dyn1(a)),
    assertz(dyn1(b)).