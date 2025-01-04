
test(X,Y) :-
    X is sin(1)+cos(2),
    Y =.. [sin,3].

test1(X,Y,Z) :- Z is X << Y. 
test2(X,Y,Z) :- Z is X >> Y.
test3(X,Y)  :- Y is randi(X).
test4(X)  :- X is random.
test5(X,Y,Z) :- Z is X / Y.
test6(X,Y,Z) :- Z is X // Y.
test7(X,Y,Z) :- Z is X*Y+1-3.
test8(X,Y,Z) :- Z is X mod Y.
test9(X,Y,Z) :- Z is X^Y.
test10(X,Y)  :- Y is sin(X).
test11(X,Y)  :- Y is cos(X).
test12(X,Y)  :- Y is tan(X).
test13(X,Y)  :- Y is integer(X).
test14(X,Y)  :- Y is abs(X).

