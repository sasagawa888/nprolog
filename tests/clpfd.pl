% CLP-test 

:- use_module(clpfd).

foo(L) :-
    L = [A, B, C],
    L ins 1..3,
    all_different(L),
    A#>C,
    label(L).

n_factorial(0, 1).
n_factorial(N, F) :-
        N #> 0,
        N1 #= N - 1,
        n_factorial(N1, F1),
        F #= N * F1.

test1(X) :-
    X in 1..3,
    label([X]).

%not good
test2(X, Y) :-
    X in 1..3,
    Y in 1..3,
    X #< Y,
    label([X, Y]).

test3(X, Y) :-
    X in 1..2,
    Y in 1..2,
    all_different([X, Y]),
    label([X, Y]).

test4(X) :-
    X in 1..5,
    X #\= 3,
    label([X]).