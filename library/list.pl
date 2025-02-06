% list library (test of module system)
:- module(list,[last/2,butlast/2,second/2,cons/3,
                nth/3,nth0/3,iota/3,take/3,drop/3,make_list/3,reverse/2,
                remove_at/3,insert_at/4,qsort/2]).

last([],[]).
last([X],[X]).
last([X|Xs],Y) :-
    last(Xs,Y).

butlast([],[]).
butlast([X],[]).
butlast([X|Xs],[X|Y]) :-
    butlast(Xs,Y).

cons(X,[],[X]).
cons(X,Y,[X|Y]).

second([],[]).
second([_,X|_],X).

nth(N,[],[]).
nth(1,[X|Xs],X).
nth(N,[X|Xs],Y) :-
    N1 is N-1,
    nth(N1,Xs,Y).

nth0(N,[],[]).
nth0(0,[X|Xs],X).
nth0(N,[X|Xs],Y) :-
    N1 is N-1,
    nth0(N1,Xs,Y).

iota(S,S,[S]).
iota(S,E,[S|L]) :-
    S1 is S+1,
    iota(S1,E,L).

take(0,L,[]).
take(N,[L|Ls],[L|Y]) :-
    N1 is N-1,
    take(N1,Ls,Y).

drop(0,L,L).
drop(N,[L|Ls],Y) :-
    N1 is N-1,
    drop(N1,Ls,Y).

make_list(0,X,[]).
make_list(N,X,[X|Y]) :-
    N1 is N-1,
    make_list(N1,X,Y).

reverse([],[]).
reverse([X|Xs],Y) :-
    reverse(Xs,Y1),
    append(Y1,[X],Y).

remove_at(0,[X|Xs],Xs).
remove_at(N,[X|Xs],[X|Y]) :-
    N1 is N-1,
    remove_at(N1,Xs,Y).

insert_at(0,X,L,[X|L]).
insert_at(N,X,[L|Ls],[L|Y]) :-
    N1 is N-1,
    insert_at(N1,X,Ls,Y).

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
