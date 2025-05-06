% CLP-test 

:- use_module(clpfd).

foo(L) :-
    L = [A, B, C],
    L ins 1..3,
    all_different(L),
    A#<C,
    label(L).

n_factorial(0, 1).
n_factorial(N, F) :-
        N #> 0,
        N1 #= N - 1,
        n_factorial(N1, F1),
        F #= N * F1.