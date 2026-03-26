% not tail recursive optimization

:- use_module(utils).

output_disp(_S, 0) :- !.
output_disp(S, N) :-
    N > 0, !,
    format(S, $+~D$, [N]).
output_disp(S, N) :-
    N < 0,
    N1 is -N,
    format(S, $-~D$, [N1]).
