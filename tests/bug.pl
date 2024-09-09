% tests functions

test1(X,Y) :-
    Y is round(X,2).

test2(X) :-
    X is randi(10).

test3(X) :-
    X is random.