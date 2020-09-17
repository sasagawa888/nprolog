/*
toy production system
| ?-reaction([c,h2,o2,o2,h2,],Y).
[ch4,o2,o2]
[co2,h2o,h2o]
Y = [co2,h2o,h2o]
yes
|
*/

reaction(X,Y) :-
    rule(X,Y).


rule(X,Y) :-
    check(c,1,X),
    check(h2,2,X),
    remove(c,1,X,X1),
    remove(h2,2,X1,X2),
    append([ch4],X2,Z),
    write(Z),nl,
    rule(Z,Y).

rule(X,Y) :-
    check(c,1,X),
    check(o2,1,X),
    remove(c,1,X,X1),
    remove(o2,1,X1,X2),
    append([co2],X2,Z),
    write(Z),nl,
    rule(Z,Y).


rule(X,Y) :-
    check(h2,2,X),
    check(o2,1,X),
    remove(h2,2,X,X1),
    remove(o2,1,X1,X2),
    append([h2o,h2o],X2,Z),
    write(Z),nl,
    rule(Z,Y).


rule(X,Y) :-
    check(ch4,1,X),
    check(o2,2,X),
    remove(ch4,1,X,X1),
    remove(o2,2,X1,X2),
    append([co2,h2o,h2o],X2,Z),
    write(Z),nl,
    rule(Z,Y).

rule(X,X).

check(A,B,X) :-
    count(A,C,X),
    C >= B.


count(A,0,[]).
count(A,C,[A|L]) :-
    count(A,C1,L),
    C is C1 + 1.
count(A,C,[L|Ls]) :-
    count(A,C,Ls).


remove(A,0,L,L).
remove(A,B,[A|L],Y) :-
    B1 is B - 1,
    remove(A,B1,L,Y).
remove(A,B,[L|Ls],[L|Y]) :-
    remove(A,B,Ls,Y).
