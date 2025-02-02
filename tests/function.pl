
test0(X,Y,Z) :- Z is X+Y.
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
test15(X,Y)  :- Y is sqrt(X).
test16(X,Y)  :- Y is log(X).
test17(X,Y)  :- Y is ln(X).
test18(X,Y)  :- Y is asin(X).
test19(X,Y)  :- Y is acos(X).
test20(X,Y)  :- Y is atan(X).
test21(X,Y)  :- Y is \X.
test22(X,Y,Z)  :- Z is X/\Y.
test23(X,Y,Z)  :- Z is X\/Y.


