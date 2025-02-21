% testing compile code for diterministic predicate

foo(X) :- X is 3*4.
bar(X,Y) :- Y is sin(X).
test3(X,Y)  :- Y is randi(X).
%test4(X)  :- X is random.
%test13(X,Y)  :- Y is integer(X).
%test14(X,Y)  :- Y is abs(X).
test15(X,Y)  :- Y is sqrt(X).