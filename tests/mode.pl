/*
mode inferencer  Idea memo

e.g.

% Partition list for quicksort
partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.

% Quicksort
qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).
qsort([], R, R) :- !.


infer(Term,Result) :- ... .
partition/4
mode(varX,+).  -- X < Y
mode(varY,+).  -- X < Y
+ means input (instantated)
- means output (not instantated)

assume1 a1:+ -> varL:+ -> a2:+ -> a3:- (L1 = [X|L1] varX:+) -> a4:- (L2 = [X|L2]).   
assume2 a1:- -> varL:- -> a2:+ -> a3:+ (varX:+) -> a4:+ (L2 = [X|L2])

qsort/3
mode(x,+). 

assume1 a1(partition/2):+ -> a1:+ -> varL:+ ->

</2 >/2 =:=/2 /==/2 -> left and rigth must be +
right is left   -> right is -, left is +.
*/