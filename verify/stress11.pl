:- use_module(utils).

run_all :-
    test41, test42, test43, test44, test45.

test41 :-
    p41(2, X),
    writeln(test41),
    writeln(X).


p41(N, X) :-
    ( N > 0 ->
        (M is N - 1,
        p41(M, X))
    ;
        X = done
    ).

test42 :-
    p42(3, 0, X),
    writeln(test42),
    writeln(X).

p42(N, A, X) :-
    ( N > 0 ->
        (B is A + N,
        M is N - 1,
        p42(M, B, X))
    ;
        X = A
    ).

test43 :-
    ( (A=3, A>0) -> X=A ; X=0 ),
    writeln(test43),
    writeln(X).

test44 :-
    ( (A=0, A>0) -> X=A ; X=no ),
    writeln(test44),
    writeln(X).

test45 :-
    ( (A=2 ; A=3) -> B is A + 10 ; B=0 ),
    writeln(test45),
    writeln(B).