/*
toy prover
| ?- proof(a=>b=>a).
rule7 rule5 rule6 rule7 rule5 rule6 yes
|

*/


:- op(800,xfy,=>).
:- op(700,xfy,v).
:- op(600,xfy,&).
:- op(500,fy,~).


proof(X) :- cnf(X,Y),tautology(Y).

%Logical expressions are represented by symbolic atoms
cnf(X,X) :- atomic(X).
%De Morgans law
cnf(~(X & Y),Z) :- write('rule1 '),cnf(~X v ~Y,Z).

%The rule of double negation
cnf(~ ~ X,Z) :- write('rule2 '),cnf(X,Z).


%Distribution rule
cnf((A & B) v (A & C),Z) :-
     write('rule3 '),cnf(A & (B v C),Z).

%Recursive structure
cnf(X & Y,X1 & Y1) :- write('rule4 '),cnf(X,X1),cnf(Y,Y1).

cnf(X v Y,X1 v Y1) :- write('rule5 '),cnf(X,X1),cnf(Y,Y1).

cnf(~ X,~ Z) :- write('rule6 '),cnf(X,Z).

%Implication
cnf(X => Y,Z) :- write('rule7 '),cnf(~X v Y,Z).


%tautology
tautology(X & Y) :- or_tautology(X),tautology(Y).
tautology(X) :- or_tautology(X).

%Complementary check of partial logical expressions
or_tautology(X v Y) :-  complement(~X,Y).
or_tautology(~X v Y) :- complement(X,Y).

%Complementary
complement(X,X).
complement(X,X v _).
complement(X,Y v Ys) :- complement(X,Ys).
