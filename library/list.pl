/*
Copyright c M.Hiroi All Rights Reserved.
http://www.geocities.jp/m_hiroi/prolog/index.html
*/

:- module(list).
:- export([single/1,pair/1,longer/2,last/2,butlast/2,take/3,
drop/3,subseq/4,group/3,position/3,count/3,sum_list/2,
max_list/2,min_list/2,adjacent/3,befor/3,iota/3,merge_list/3,
merge_sort/2,prefix/2,suffix/2,sublist/2,subst/4,permutation/3,
repeat_perm/3,combination/3,repeat_comb/3,split_nth/4,partition/3,
split_find/4,split_ge/4,pack/2,pack_num_list/2,expand_num_list/2,
drop_same_code/3,encode/2,fill_list/3,decode/2,make_list/3,tabulate/3]).

:- end_module(list).

:- body(list).

single([_]).

pair([_ | _]).

/*
?- longer([a, b, c], [d, e]).
true.
*/
longer([_ | Xs], [_ | Ys]) :- !, longer(Xs, Ys).
longer([_ | _], []).

/*
?- last([a, b, c, d, e], X).
X = [e] ;
false.
*/
last(Xs, Xs) :- single(Xs).       % last([X], [X]).
last([_ | Xs], Ys) :- last(Xs, Ys).

/*
?- butlast([a, b, c, d, e], X).
X = [a, b, c, d] ;
false.
*/
butlast(Xs, []) :- single(Xs).    % butlast([_], []). 
butlast([X | Xs], [X | Ys]) :- butlast(Xs, Ys).

/*
?- take([a, b, c, d, e], 3, X).
X = [a, b, c] ;
false.
*/
take(_, 0, []).
take([], N, []) :- N > 0.
take([X | Xs], N, [X | Ys]) :-
    N > 0, N1 is N - 1, take(Xs, N1, Ys).

/*
?- drop([a, b, c, d, e], 3, X).
X = [d, e] ;
fales.
*/
drop(Xs, 0, Xs).
drop([], N, []) :- N > 0.
drop([_ | Xs], N, Ys) :-
    N > 0, N1 is N - 1, drop(Xs, N1, Ys).

/*
?- subseq([a, b, c, d, e], 2, 4, X).
X = [b, c, d] ;
false.
*/
subseq(_, N, M, []) :- N > M.
subseq(Xs, N, M, Ys) :-
    N > 0, M >= N, N1 is N - 1, K is M - N1, drop(Xs, N1, Zs), take(Zs, K, Ys).

%butlast(Xs, N, Ys) :-
%    length(Xs, M), K is M - N, take(Xs, K, Ys).

/*
?- group([a, b, c, d, e, f], 2, X).
X = [[a, b], [c, d], [e, f]] ;
false.
*/
group([], _, []).
group(Xs, N, [As | Ys]) :-
    Xs \= [], take(Xs, N, As), drop(Xs, N, Rs), group(Rs, N, Ys).

/*
?- position(c, [a, b, c, d, e, f], X).
X = 3 ;
false.
*/
position(X, Ls, N) :- position(X, Ls, N, 1).
position(X, [X | _], N, N).
position(X, [_ | Ys], N, M) :-
    M1 is M + 1, position(X, Ys, N, M1).

/*
?- count(b, [a, b, a, b, a], X).
X = 2 ;
false.
*/
count(_, [], 0).
count(X, [X | Xs], M) :- count(X, Xs, N), M is N + 1.
count(X, [Y  |Xs], N) :- X \= Y, count(X, Xs, N).

/*
?- sum_list([1, 2, 3, 4, 5], N).
N = 15.
*/
sum_list([], 0).
sum_list([X | Xs], Sum) :-
    sum_list(Xs, Sum1), Sum is Sum1 + X.

/*
?- max_list([5, 6, 4, 7, 3, 8, 2, 9, 1], N).
N = 9 ;
false.
*/
max_list([X | Xs], M) :- max_list(Xs, X, M).
max_list([], M, M).
max_list([X | Xs], Y, M) :- X > Y, max_list(Xs, X, M).
max_list([X | Xs], Y, M) :- X =< Y, max_list(Xs, Y, M).

/*
?- min_list([5, 6, 4, 7, 3, 8, 2, 9, 1], N).
N = 1 ;
false.
*/
min_list([X | Xs], M) :- min_list(Xs, X, M).
min_list([], M, M).
min_list([X | Xs], Y, M) :- X < Y, min_list(Xs, X, M).
min_list([X | Xs], Y, M) :- X >= Y, min_list(Xs, Y, M).

/*
?- adjacent(a, b, [a, b, c, d, e]).
true ;
false.

?- adjacent(X, Y, [a, b, c, d, e]).
X = a,
Y = b ;
X = b,
Y = c ;
X = c,
Y = d ;
X = d,
Y = e ;
false.
*/
adjacent(X, Y, [X, Y | _]).
adjacent(X, Y, [_ | Zs]) :- adjacent(X, Y, Zs).


members(X, [X | Xs], Xs).
members(X, [_ | Xs], Ys) :- members(X, Xs, Ys).

/*
?- before(a, c, [a, b, c, d, e]).
true ;
false.

?- before(X, c, [a, b, c, d, e]).
X = a ;
X = b ;
false.

?- before(X, Y, [a, b, c, d, e]).
X = a,
Y = b ;
X = a,
Y = c ;
X = a,
Y = d ;
X = a,
Y = e
*/
before(X, Y, Ls) :- 
    members(X, Ls, Xs), member(Y, Xs).

/*
?- iota(1, 5, X).
X = [1, 2, 3, 4, 5] ;
false.
*/
iota(N, M, []) :- N > M.
iota(N, M, [N | Xs]) :-
    N =< M, N1 is N + 1, iota(N1, M, Xs).


/*
?- merge_list([1, 3, 5, 7, 9], [2, 4, 6, 8], X).
X = [1, 2, 3, 4, 5, 6, 7, 8, 9] ;
false.
*/
merge_list([], Ys, Ys).
merge_list(Xs, [], Xs).
merge_list([X | Xs], [Y | Ys], [X | Zs]) :- X < Y, merge_list(Xs, [Y | Ys], Zs).
merge_list([X | Xs], [Y | Ys], [Y | Zs]) :- X >= Y, merge_list([X | Xs], Ys, Zs).

/*
?- merge_sort([5, 6, 4, 7, 3, 1, 2, 9, 8], X).
X = [1, 2, 3, 4, 5, 6, 7, 8, 9] ;
false.
*/
merge_sort(Xs, Ys) :- length(Xs, N), merge_sort(N, Xs, Ys).
merge_sort(_, [], []).
merge_sort(1, [X | _], [X]).
merge_sort(N, Xs, Ys) :-
    N > 1,
    M1 is N // 2,
    merge_sort(M1, Xs, Zs1),
    M2 is N - M1,
    drop(Xs, M1, Xs1),
    merge_sort(M2, Xs1, Zs2),
    merge_list(Zs1, Zs2, Ys).

/*
?- prefix([a, b, c, d], X).
X = [] ;
X = [a] ;
X = [a, b] ;
X = [a, b, c] ;
X = [a, b, c, d].
*/
prefix(_, []).
prefix([X | Xs], [X | Ys]) :- prefix(Xs, Ys).

/*
?- suffix([a, b, c, d], X).
X = [a, b, c, d] ;
X = [b, c, d] ;
X = [c, d] ;
X = [d] ;
X = [].
*/
suffix(Xs, Xs).
suffix([_ | Xs], Ys) :- suffix(Xs, Ys).

/*
?- sublist([b, c, d], [a, b, c, d, e]).
true

?- sublist(X, [a, b, c]).
X = [] ;
X = [a] ;
X = [a, b] ;
X = [a, b, c] ;
X = [b] ;
X = [b, c] ;
X = [c] ;
false.
*/
sublist([], _).
sublist(Sub, Ls) :- prefix(Ls, Ps), suffix(Ps, Sub), Sub \= [].


/*
?- subst(5, 50, [1, 2, [3, 4, [5, 6], 7], 8], X).
X = [1, 2, [3, 4, [50, 6], 7], 8] ;
false.
*/
subst(X, Y, X, Y) :- !.
subst(X, _, Z, Z) :- atomic(Z), X \= Z.
subst(X, Y, [Ls | Rs], [Ls1 | Rs1]) :-
    subst(X, Y, Ls, Ls1), subst(X, Y, Rs, Rs1).

/*
?- permutation(3, [a, b, c], X).
X = [a, b, c] ;
X = [a, c, b] ;
X = [b, a, c] ;
X = [b, c, a] ;
X = [c, a, b] ;
X = [c, b, a] ;
false.
*/
permutation(0, Xs, Xs).
permutation(N, Xs, [X | Ys]) :-
    N > 0, N1 is N - 1, select(X, Xs, Zs), permutation(N1, Zs, Ys).

/*
?- repeat_perm(2, [a, b, c], X).
X = [a, a] ;
X = [a, b] ;
X = [a, c] ;
X = [b, a] ;
X = [b, b] ;
X = [b, c] ;
X = [c, a] ;
X = [c, b] ;
X = [c, c] ;
false.
*/
repeat_perm(0, _, []).
repeat_perm(N, Xs, [X | Ys]) :-
    N > 0, N1 is N - 1, member(X, Xs), repeat_perm(N1, Xs, Ys).

/*
?- combination(3, [a, b, c, d, e], X).
X = [a, b, c] ;
X = [a, b, d] ;
X = [a, b, e] ;
X = [a, c, d] ;
X = [a, c, e] ;
X = [a, d, e] ;
X = [b, c, d] ;
X = [b, c, e] ;
X = [b, d, e] ;
X = [c, d, e] ;
false.
*/
combination(0, _, []).
combination(N, [X | Xs], [X | Zs]) :- N > 0, N1 is N - 1, combination(N1, Xs, Zs).
combination(N, [_ | Xs], Zs) :- N > 0, combination(N, Xs, Zs).

/*
?- repeat_comb(3, [a, b, c, d], X).
X = [a, a, a] ;
X = [a, a, b] ;
X = [a, a, c] ;
X = [a, a, d] ;
X = [a, b, b] ;
X = [a, b, c] ;
X = [a, b, d] ;
X = [a, c, c] ;
X = [a, c, d] ;
X = [a, d, d] ;
X = [b, b, b] ;
X = [b, b, c] ;
X = [b, b, d] ;
X = [b, c, c] ;
X = [b, c, d] ;
X = [b, d, d] ;
X = [c, c, c] ;
X = [c, c, d] ;
X = [c, d, d] ;
X = [d, d, d] ;
false.
*/
repeat_comb(0, _, []).
repeat_comb(N, [X | Xs], [X | Zs]) :-
    N > 0, N1 is N - 1, repeat_comb(N1, [X | Xs], Zs).
repeat_comb(N, [_ | Xs], Zs) :- N > 0, repeat_comb(N, Xs, Zs).

/*
?- split_nth([1, 2, 3, 4, 5, 6], 3, X, Y).
X = [1, 2]
Y = [3, 4, 5, 6] ;
false.
*/
split_nth(Xs, N, As, Bs) :- 
    N > 0, N1 is N - 1, take(Xs, N1, As), drop(Xs, N1, Bs).

/*
?- partition([a, b, c, d, e, f], X, Y).
X = [a, c, e],
Y = [b, d, f].
*/
partition(Xs, Os, Es) :- odd_part(Xs, Os, Es).

odd_part([], [], []).
odd_part([X | Xs], [X | Os], Es) :- even_part(Xs, Os, Es).
even_part([],[],[]).
even_part([X | Xs], Os, [X | Es]) :- odd_part(Xs, Os, Es).

/*
?- split_find(c, [a, b, c, d, e, f], X, Y).
X = [a, b],
Y = [c, d, e, f] ;
false.
*/
split_find(X, [X | Xs], [], [X | Xs]).
split_find(X, [Y | Ys], [Y | As], Bs) :- split_find(X, Ys, As, Bs).

/*
split_ge(3, [1, 3, 5, 2, 4, 6], X, Y).
X = [1, 3, 2],
Y = [5, 4, 6] ;
false.
*/
split_ge(_, [], [], []).
split_ge(X, [Y | Ys], Ls, [Y | Bs]) :- X < Y, split_ge(X, Ys, Ls, Bs).
split_ge(X, [Y | Ys], [Y | Ls], Bs) :- X >= Y, split_ge(X, Ys, Ls, Bs).

/*
pack([a, a, b, b, b, c, d, d, d, d], X).
X = [[a, a], [b, b, b], [c], [d, d, d, d]].
*/
pack([X | Xs], Ys) :- pack(Xs, [[X]], Ys).
pack([], Xs, Ys) :- reverse(Xs, Ys).
pack([X | Xs], [[X | Ys] | Ls], Zs) :- !, pack(Xs, [[X, X | Ys] | Ls], Zs).
pack([X | Xs], Ys, Zs) :- pack(Xs, [[X] | Ys], Zs).

/*
?- pack_num_list([1, 2, 3, 4, 6, 8, 9], X).
X = [[1 | 4], 6, [8 | 9]] ;
false.
*/
pack_num_list([X | Xs], Ys) :- pack_num_list(Xs, [X], Ys).
pack_num_list([], Xs, Ys) :- reverse(Xs, Ys).
pack_num_list([X | Xs], [[S | E] | Ys], Zs) :-
    X =:= E + 1, pack_num_list(Xs, [[S | X] | Ys], Zs).
pack_num_list([X | Xs], [[S | E] | Ys], Zs) :-
    X =\= E + 1, pack_num_list(Xs, [X, [S | E] | Ys], Zs).
pack_num_list([X | Xs], [Y | Ys], Zs) :-
    X =:= Y + 1, pack_num_list(Xs, [[Y | X] | Ys], Zs).
pack_num_list([X | Xs], [Y | Ys], Zs) :-
    X=\= Y + 1, pack_num_list(Xs, [X, Y | Ys], Zs).

/*
?- expand_num_list([[1 | 4], 6, [8 | 9]], X).
X = [1, 2, 3, 4, 6, 8, 9] ;
false.
*/
expand_num_list([], []).
expand_num_list([[S | E] | Xs], Zs) :-
    expand_num_list(Xs, Ys), iota(S, E, Ls), append(Ls, Ys, Zs).
expand_num_list([X | Xs], [X | Zs]) :-
    integer(X), expand_num_list(Xs, Zs).


drop_same_code([_], [], 1).
drop_same_code([X, Y | Ys], [Y | Ys], 1) :- X \= Y.
drop_same_code([X, X | Xs], Ys, N) :-
    drop_same_code([X | Xs], Ys, M), N is M + 1.

/*
?- encode([a, a, a, b, b, c, d, d, d, d], X).
X = [[a, 3], [b, 2], [c, 1], [d, 4]] ;
false.
*/
encode([], []).
encode([X | Xs], [[X, N] | Ls]) :-
    drop_same_code([X | Xs], Ys, N), encode(Ys, Ls).

/*

*/
fill_list(_, 0, []).
fill_list(X, N, [X | Xs]) :-
    N > 0, N1 is N - 1, fill_list(X, N1, Xs).

/*
?- decode([[a, 3], [b, 2], [c, 1], [d, 4]], X).
X = [a, a, a, b, b, c, d, d, d, d] ;
false.
*/
decode([], []).
decode([[Code, N] | Xs], Zs) :-
    decode(Xs, Ys), fill_list(Code, N, Ls), append(Ls, Ys, Zs).

/*
?- make_list(5, 1, Ls).

Ls = [1, 1, 1, 1, 1] ;

No
?- assert(identity(X, X)).

Yes
?- identity(1, X).

X = 1 ;

No
?- tabulate(8, identity, Ls).

Ls = [0, 1, 2, 3, 4, 5, 6, 7] ;

No
?- assert(square(X, A) :- A is X * X).

Yes
?- tabulate(8, square, Ls).

Ls = [0, 1, 4, 9, 16, 25, 36, 49] ;

No
*/
make_list(0, _, []).
make_list(N, X, [X | Xs]) :-
    N > 0, N1 is N - 1, make_list(N1, X, Xs).

tabulate_sub(N, N, _, []).
tabulate_sub(I, N, Pred, [X | Ys]) :-
    I < N,
    G =.. [Pred, I, X],
    call(G),
    I1 is I + 1,
    tabulate_sub(I1, N, Pred, Ys).
tabulate(N, Pred, Ls) :- tabulate_sub(0, N, Pred, Ls).

:- end_body(list).
