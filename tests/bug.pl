
%BIGNUM test
:- dynamic(foo/2).

foo(X,Y) :- Y is X + 111111111111111111111111111111111111111111111111111111111111111111111.

fact(0,1).
fact(N,A) :-
    N1 is N-1,
    fact(N1,A1),
    A is N*A1.
 
 % fact(1000,X). 