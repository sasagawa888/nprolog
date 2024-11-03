
foo(X) :- bar(X,Y),write(Y).

bar(X,Y) :- Y is X+1.