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

fibo1(0, 0).
fibo1(N, F) :- fibo1(N, 1, 0, F).
fibo1(1, A1, _, A1).
fibo1(N, A1, A2, F) :-
    N > 1, N1 is N - 1, A3 is A1 + A2, fibo1(N1, A3, A1, F).