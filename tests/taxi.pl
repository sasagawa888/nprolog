/*
The Hardy–Ramanujan number 
Originaly written by 犬童, modified by K.Sasagawa
?- r(X,Y,Z).
X = 1729
Y = 12
Z = [[1,12],[9,10]]
yes
*/

len([],0).
len([L|Ls],X) :- len(Ls,X1),X is X1 + 1.
len(X,Y) :- fail.

i(X,Y) :- length(L,Y),count(L,X).

count(L,N) :-
  length(L,N).
count([L|Ls],N) :-
  count(Ls,N).


c( X, Z, Y):- i( Z, Y), X is Z ^3.  

d( X, Y, [Z, W]):- 
     c( P, Z, Y),
     c( Q, W, Y),
     P < Q,
     X is P + Q.  


r(X, Y, [Z, W]):-
     d(X, Y, Z),
     d(X, Y, W),
     Z @< W .