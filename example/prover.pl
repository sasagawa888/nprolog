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

%論理式は記号アトムで表される
cnf(X,X) :- atomic(X).
%ドモルガンの法則
cnf(~(X & Y),Z) :- write('rule1 '),cnf(~X v ~Y,Z).

%二重否定の法則
cnf(~ ~ X,Z) :- write('rule2 '),cnf(X,Z).


%分配律
cnf((A & B) v (A & C),Z) :-
     write('rule3 '),cnf(A & (B v C),Z).

%再帰構造
cnf(X & Y,X1 & Y1) :- write('rule4 '),cnf(X,X1),cnf(Y,Y1).

cnf(X v Y,X1 v Y1) :- write('rule5 '),cnf(X,X1),cnf(Y,Y1).

cnf(~ X,~ Z) :- write('rule6 '),cnf(X,Z).

%含意
cnf(X => Y,Z) :- write('rule7 '),cnf(~X v Y,Z).


%トートロジー
tautology(X & Y) :- or_tautology(X),tautology(Y).
tautology(X) :- or_tautology(X).

%部分論理式の相補確認
or_tautology(X v Y) :-  complement(~X,Y).
or_tautology(~X v Y) :- complement(X,Y).

%相補的
complement(X,X).
complement(X,X v _).
complement(X,Y v Ys) :- complement(X,Ys).
