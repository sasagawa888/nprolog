
test(X,Y) :-
    X is sin(1)+cos(2),
    Y =.. [sin,3].

test1(X,Y,Z) :- Z is X << Y. 
test2(X,Y,Z) :- Z is X >> Y.
test3(X,Y)  :- Y is randi(X).
test4(X)  :- X is random.
