para(X) :- list50(Y),psort(Y,X).

psort([Pivot|Rest], Sorted) :-
    partition(Pivot, Rest, Left, Right), 
    dp_and([qsort(Left, SortedLeft), qsort(Right, SortedRight)]),       
    append(SortedLeft, [Pivot|SortedRight], Sorted). 

seq(X) :- list50(Y),qsort(Y,X).

qsort([], []).
qsort([Pivot|Rest], Sorted) :-
    partition(Pivot, Rest, Left, Right), 
    qsort(Left, SortedLeft),          
    qsort(Right, SortedRight),       
    append(SortedLeft, [Pivot|SortedRight], Sorted). 

partition(_, [], [], []). 
partition(Pivot, [H|T], [H|Left], Right) :-
    H =< Pivot,  
    partition(Pivot, T, Left, Right).
partition(Pivot, [H|T], Left, [H|Right]) :-
    H > Pivot,  
    partition(Pivot, T, Left, Right).

% List of 50 elements for another test
list50([27, 74, 17, 33, 94, 18, 46, 83, 65, 2, 32, 53, 28, 85, 99, 47, 28, 82, 6, 11,
        55, 29, 39, 81, 90, 37, 10, 0, 66, 51, 7, 21, 85, 27, 31, 63, 75, 4, 95, 99, 11, 28, 61,
        74, 18, 92, 40, 55, 59, 8]).