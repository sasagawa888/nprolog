:- dynamic(boo/0).

boo :-
    between(0,10,N),
    write(N),
    fail.


foo(X,Y,Z) :- X -> Y ; Z.

bar(X,Y) :- X -> Y.


test(cut) :-
    (true -> X = 1 ; X = 2),
    X == 1.

test(cut_failure) :-
    (fail -> X = 1 ; X = 2),
    X == 2.


test1(X) :-
    (true -> X = 1),
    X = 1.


test2(cut_failure1) :-
    (fail -> X = 1),
    X = 1.
