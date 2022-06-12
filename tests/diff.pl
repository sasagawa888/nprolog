dif(F,X,Z) :- d(F,X,Y),simple(Y,Z).

d(N,X,0) :- number(N).
d(X,X,1).
d(X^N,X,N*X^(N-1)).
d(N*X,X,N).
d(1/X,X,-1/X^2).
d(sqrt(X),X,1/(2*sqrt(X))).
d(sin(X),X,cos(X)).
d(cos(X),X,-sin(X)).
d(tan(X),X,1/cos(X)^2).
d(e^X,X,e^X).
d(A^X,x,A^X*log(e,A)).
d(log(e,X),X,1/X).
d(log(A,X),X,1/(X*log(e,A))).
d(F1+F2,X,A1+A2) :-
    d(F1,X,A1),
    d(F2,X,A2).
d(F1-F2,X,A1-A2) :-
    d(F1,X,A1),
    d(F2,X,A2).    


simple(X^0,1).
simple(X^1,X).
simple(0*X,0).
simple(X*0,0).
simple(1*X,X1) :- simple(X,X1).
simple(X*1,X1) :- simple(X,X1).
simple(0+X,X1) :- simple(X,X1).
simple(X+0,X1) :- simple(X,X1).
simple(X*Y,Z) :- simple(X,X1),not(X=X1),!,simple(X1*Y,Z).
simple(X*Y,Z) :- simple(Y,Y1),not(Y=Y1),!,simple(X*Y1,Z).
simple(X+Y,Z) :- simple(X,X1),not(X=X1),!,simple(X1+Y,Z).
simple(X+Y,Z) :- simple(Y,Y1),not(Y=Y1),!,simple(X+Y1,Z).
simple(X,X).
