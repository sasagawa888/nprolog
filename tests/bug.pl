:- mt_create(2).

foo(0).
foo(N) :- write(N),N1 is N-1,foo(N1).

boo(0).
boo(N) :- write(N),N1 is N-1,boo(N1).

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


% mt_and([qsort([2,3,1],X),boo(3)]).
% mt_and([qsort([2,3,1],X),qsort([3,2,1],Y)]).