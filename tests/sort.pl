/*
    exercize to remember prolog for me
*/

bubble(X,X) :-
    bubble1(X,X1),
    X == X1.
bubble(X,X2) :-
    bubble1(X,X1),
    bubble(X1,X2).

bubble1([],[]).
bubble1([X],[X]).
bubble1([X1,X2|Xs],[X1|Y]) :-
    X1 =< X2,
    bubble1([X2|Xs],Y).

bubble1([X1,X2|Xs],[X2|Y]) :-
    X1 > X2,
    bubble1([X1|Xs],Y).

