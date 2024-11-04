
foo(X) :- bar(X,Y),write(Y).

bar(X) :- fail;fail;true.

boo(X) :- write(X),!,write(X).

a :- write('Disjunction test: a succeeded').
b :- write('Disjunction test: b succeeded').
or_test :- a ; b.

x :- write('Cut test: x succeeded'), nl.
y :- write('Cut test: y succeeded'), nl, !.
z :- write('Cut test: z succeeded'), nl.

cut_test :- x, (y; z).


fact(0,1).
fact(N,X) :-
    N1 is N-1,
    fact(N1,X1),
    X is N*X1.
