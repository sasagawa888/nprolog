% not tail recursive optimization

alpha_list([], []).
alpha_list([A|As], [A1|As1]) :-
    alpha(A, A1),
    alpha_list(As, As1).

