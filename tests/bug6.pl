/*
trule of double negatiwn
cnfyes
|

*/


%:- @ (800,xfx,=).
:- op(700,xfy,v).
:- op(600,xfy,&).
:- op(500,fy,~).


proof(X) :- cnf(X,Y),tautology(Y).

%Looms
cnf(X,X)

















:- atomic(X).
%ns�~Y,Z).

%Therulble negatiwn
cnf(~ ~ X,Z)   