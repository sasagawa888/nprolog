/*
    exercize to remember prolog for me
*/

bubble_sort(X,X) :-
    bubble1(X,X1),
    X == X1.
bubble_sort(X,X2) :-
    bubble1(X,X1),
    bubble_sort(X1,X2).

bubble1([],[]).
bubble1([X],[X]).
bubble1([X1,X2|Xs],[X1|Y]) :-
    X1 =< X2,
    bubble1([X2|Xs],Y).

bubble1([X1,X2|Xs],[X2|Y]) :-
    X1 > X2,
    bubble1([X1|Xs],Y).

merge_sort([X],Z) :- 
    merge([X],[],Z).
merge_sort([X,Y],Z) :-
    merge([X],[Y],Z).
merge_sort(X,Z) :-
    length(X,N),
    N1 is ceiling(N / 2),
    take(X,N1,X1),
    drop(X,N1,X2),
    merge_sort(X1,Y1),
    merge_sort(X2,Y2),
    merge(Y1,Y2,Z).

take(X,0,[]).
take([X|Xs],N,[X|Y]) :-
    N1 is N - 1,
    take(Xs,N1,Y).

drop(X,0,X).
drop([X|Xs],N,Y) :-
    N1 is N - 1,
    drop(Xs,N1,Y).

merge(X,[],X).
merge([],Y,Y).
merge([X|Xs],[Y|Ys],[X|Z]) :-
    X =< Y,
    merge(Xs,[Y|Ys],Z).
merge([X|Xs],[Y|Ys],[Y|Z]) :-
    X > Y,
    merge([X|Xs],Ys,Z).


% tests code from M.Hiroi's page
quick([X | Xs], Ys) :-
        partition(Xs, X, Littles, Bigs),
        quick(Littles, Ls),
        quick(Bigs, Bs),
        append(Ls, [X | Bs], Ys).
quick([], []).


partition([X | Xs], Y, [X | Ls], Bs) :-
        X =< Y, partition(Xs, Y, Ls, Bs).
partition([X | Xs], Y, Ls, [X | Bs]) :-
        X > Y, partition(Xs, Y, Ls, Bs).
partition([], Y, [], []).

quick1(Xs, Ys) :- quick_sub(Xs, [Ys, []]).
quick_sub([X | Xs], [Ys, Zs]) :-
        partition(Xs, X, Littles, Bigs),
        quick_sub(Littles, [Ys, [X | Ys1]]),
        quick_sub(Bigs, [Ys1, Zs]).
quick_sub([], [Xs, Xs]).
