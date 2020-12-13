foo(0).
foo(X) :-
    write(X),
    X1 is X - 1,foo(X1).

fact(0, 1).
fact(X, Sum) :-
    X > 0, X1 is X - 1, fact(X1, Sum1), Sum is X * Sum1. 

nodiag([], _, _). 
nodiag([N|L],B,D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L,B,D1).

