partition(_, [], [], []). 
partition(Pivot, [H|T], [H|Left], Right) :-
    H =< Pivot,  
    partition(Pivot, T, Left, Right).
partition(Pivot, [H|T], Left, [H|Right]) :-
    H > Pivot,  
    partition(Pivot, T, Left, Right).