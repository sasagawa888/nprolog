/*
Copyright c M.Hiroi All Rights Reserved.
http://www.geocities.jp/m_hiroi/prolog/index.html
*/
:- module(math).
:- export([union/3,set_of_list/2,intersection/3,difference/3,comb_num/3,
gcd/3,lcm/3,make_ratio/4,addr/3,subr/3,mulr/3,filter/3,sieve/2,
power_set/2,subset/2,seteql/2,exclusive_or/3,product/3,kakko/2,
kakko_num/2,factorization/2,fold_left/4,divisor_num/2,prime_sum/4,
divisor_sum/2,divisor_num1/3,partition_of_integer/2,
divisor_sub/4,divisor_product/3,divisor/2,partition_number/2,
perfect_permutation/2,montmort_number/2,partition_of_set/2,
bell_number/2,group_partition/4,group_partition_number/3]).


:- end_module(math).

:- body(math).
/*
?- set_of_list([a, b, c, a, d], X).
X = [b, c, a, d].
*/
set_of_list([], []).
set_of_list([X | Xs], Ys) :- member(X, Xs), !, set_of_list(Xs, Ys).
set_of_list([X | Xs], [X | Ys]) :- set_of_list(Xs, Ys).

/*
?- union([a, b, c, d], [c, d, e, f], X).
X = [a, b, c, d, e, f].
*/
union([], Xs, Xs).
union([X | Xs], Ys, Zs) :- member(X, Ys), !, union(Xs, Ys, Zs).
union([X | Xs], Ys, [X | Zs]) :- union(Xs, Ys, Zs).

/*
?- intersection([a, b, c, d], [c, d, e, f], X).
X = [c, d].
*/
intersection([], _, []).
intersection([X | Xs], Ys, [X | Zs]) :-
    member(X, Ys), !, intersection(Xs, Ys, Zs).
intersection([_ | Xs], Ys, Zs) :- intersection(Xs, Ys, Zs).

/*
?- difference([a, b, c, d], [c, d, e, f], X).
X = [a, b].
*/
difference([], _, []).
difference([X | Xs], Ys, Zs) :-
    member(X, Ys), !, difference(Xs, Ys, Zs).
difference([X | Xs], Ys, [X | Zs]) :- difference(Xs, Ys, Zs).

/*
?- comb_num(5, 3, X).
X = 10 ;
false.

?- comb_num(10, 5, X).
X = 252 ;
false.
*/
comb_num(_,0,1).
comb_num(N, N, 1) :- N > 0.
comb_num(N, R, M) :-
  R > 0, N =\= R, R1 is R - 1, comb_num(N, R1, A), M is A * (N - R + 1) / R.

/*
?-  gcd(42, 30, X).
X = 6 ;
false.
*/
gcd(A, 0, A).
gcd(A, B, G) :-
    B > 0, C is A mod B, gcd(B, C, G).

/*
?- lcm(14, 35, L).
L = 70 ;
false.
*/
lcm(A, B, L) :-
    gcd(A, B, G), L is A * B // G.

/*
?- make_ratio(2, 4, X).
X = raito(1, 2) ;
false.

?- make_ratio(9, 3, X).
X = raito(3, 1) ;
false.
*/
make_ratio(P, Q, ratio(P1, Q1)) :-
    (Q < 0 -> (P0 is -P, Q0 is -Q) ; (P0 is P, Q0 is Q)), 
    gcd(P0, Q0, G), 
    P1 is P0 // G, Q1 is Q0 // G.

/*
?- addr(ratio(1, 3), ratio(1, 4), X).
X = ratio(7, 12) ;
false.

?- subr(ratio(1, 3), ratio(1, 4), X).
X = ratio(1, 12) ;
false.

?- mulr(ratio(1, 3), ratio(1, 4), X).
X = ratio(1, 12) ;
false.

?- divr(ratio(1, 3), ratio(1, 4), X).
X = ratio(4, 3) ;
false.
*/
addr(ratio(P1, Q1), ratio(P2, Q2), R) :-
    P3 is P1 * Q2 + P2 * Q1, Q3 is Q1 * Q2, make_ratio(P3, Q3, R).

subr(ratio(P1, Q1), ratio(P2, Q2), R) :-
    P3 is P1 * Q2 - P2 * Q1, Q3 is Q1 * Q2, make_ratio(P3, Q3, R).

mulr(ratio(P1, Q1), ratio(P2, Q2), R) :-
    P3 is P1 * P2, Q3 is Q1 * Q2, make_ratio(P3, Q3, R).

divr(ratio(P1, Q1), ratio(P2, Q2), R) :-
    P3 is P1 * Q2, Q3 is Q1 * P2, make_ratio(P3, Q3, R).



filter(_, [], []).
filter(X, [Y | Ys], Zs) :- Y mod X =:= 0, filter(X, Ys, Zs).
filter(X, [Y | Ys], [Y | Zs]) :- Y mod X =\= 0, filter(X, Ys, Zs).

sieve(N, Ps) :- iota(2, N, Ns), sieve(Ns, [], Ps).
sieve([], Xs, Ps) :- reverse(Xs, Ps).
sieve([X | Xs], Ys, Ps) :- filter(X, Xs, Zs), sieve(Zs, [X | Ys], Ps).

check(_, nil) :- !.
check(X, Y) :- X =< Y.

/*
?- power_set([a,b], Xs).

Xs = [[], [b], [a], [a, b]] ;

No
?- power_set([a,b,c], Xs).

Xs = [[], [c], [b], [b, c], [a], [a, c], [a, b], [a|...]] ;
*/
power_set_sub([], []).
power_set_sub([_ | Xs], Ys) :- power_set_sub(Xs, Ys).
power_set_sub([X | Xs], [X | Ys]) :- power_set_sub(Xs, Ys).

power_set(Ls, Xs) :- findall(X, power_set_sub(Ls, X), Xs).

/*
?- subset([a, b], [a, b, c]).

Yes
?- subset([b, a], [a, b, c]).

Yes
?- subset(Xs, [a, b, c]), write(Xs), nl, fail.
[]
[a]
[a, b]
[a, b, c]
[a, c]
[a, c, b]
[b]
[b, a]
[b, a, c]
[b, c]
[b, c, a]
[c]
[c, a]
[c, a, b]
[c, b]
[c, b, a]
*/
subset([], Ys).
subset([X | Xs], Ys) :- select(X, Ys, Ys1), subset(Xs, Ys1).

/*
?- seteql([a, b, c], [a, b, c]).

Yes
?- seteql([a, b, c], [c, a, b]).

Yes
?- seteql([a, b, c], [a, b]).

No
?- seteql(Xs, [a,b,c]), write(Xs), nl, fail.
[a, b, c]
[a, c, b]
[b, a, c]
[b, c, a]
[c, a, b]
[c, b, a]

No
*/
seteql(Xs, Ys) :- subset(Xs, Ys), subset(Ys, Xs).

/*
?- exclusive_or([a, b, c, d], [c, d, e, f], Xs).

Xs = [a, b, e, f] ;

No
*/
exclusive_or(Xs, Ys, Zs):-
    difference(Xs, Ys, Zs1),
    difference(Ys, Xs, Zs2),
    union(Zs1, Zs2, Zs).

/*
?- product([a, b, c], [1, 2], L).

L = [[a, 1], [a, 2], [b, 1], [b, 2], [c, 1], [c, 2]] ;

No
*/
product_sub(Xs, Ys, [X, Y]) :- member(X, Xs), member(Y, Ys).
product(Xs, Ys, Zs) :- findall(Z, product_sub(Xs, Ys, Z), Zs).

/*
?- kakko(3, K), name(K1, K), write(K1), nl, fail.
((()))
(()())
(())()
()(())
()()()

No
?- kakko(4, K), name(K1, K), write(K1), nl, fail.
(((())))
((()()))
((())())
((()))()
(()(()))
(()()())
(()())()
(())(())
(())()()
()((()))
()(()())
()(())()
()()(())
()()()()

*/
kakko_sub(X, Y, M, Acc, Ans) :-
    X =:= Y,
    Y =:= M,
    reverse(Acc, Ans).
kakko_sub(X, Y, M, Acc, Ans) :-
    X < M,
    X1 is X + 1,
    kakko_sub(X1, Y, M, ['(' | Acc], Ans).
kakko_sub(X, Y, M, Acc, Ans) :-
    Y < X,
    Y1 is Y + 1,
    kakko_sub(X, Y1, M, [')' | Acc], Ans).

kakko(M, Ks) :- kakko_sub(0, 0, M, [], Ks).

kakko_num1([], Ys, Zs) :- reverse(Ys, Zs).
kakko_num1([X | Xs], [Y | Ys], Zs) :-
    N is X + Y,
    kakko_num1(Xs, [N, Y | Ys], Zs).

kakko_num2([N], N) :- !.
kakko_num2([_ | Xs], N) :-
    kakko_num1(Xs, [0], [_ | Zs]),
    kakko_num2(Zs, N).

/*
?- between(1, 10, I), kakko_num(I, N), write(N), nl, fail.
1
2
5
14
42
132
429
1430
4862
16796

*/
kakko_num(M, N) :- 
    M1 is M + 1,
    make_list(M1, 1, L),
    kakko_num2(L, N).

/*
?- factorization(12345678, L).

L = [[2, 1], [3, 2], [47, 1], [14593, 1]] ;

No
?- factorization(1234567890, L).

L = [[2, 1], [3, 2], [5, 1], [3607, 1], [3803, 1]] ;

No
?- factorization(1999999991, L).

L = [[11, 1], [349, 1], [520969, 1]] ;

No
*/
factor_sub(N, M, C, [N, C]) :- N mod M =\= 0.
factor_sub(N, M, C, Z) :-
    N mod M =:= 0,
    A is N // M,
    C1 is C + 1,
    factor_sub(A, M, C1, Z).

factor_loop(I, N, Acc, Ans) :-
    N < I * I,
    (N > 1 -> reverse([[N, 1] | Acc], Ans) ; reverse(Acc, Ans)).
factor_loop(I, N, Acc, Ans) :-
    N >= I * I,
    factor_sub(N, I, 0, [M, C]),
    I2 is I + 2,
    (C > 0 -> factor_loop(I2, M, [[I, C] | Acc], Ans) ; factor_loop(I2, N, Acc, Ans)).

factorization(N, Ans) :-
    factor_sub(N, 2, 0, [M, C]),
    (C > 0 -> factor_loop(3, M, [[2, C]], Ans) ; factor_loop(3, N, [], Ans)).


fold_left(_, A, [], A).
fold_left(F, A, [X | Xs], C) :-
    Z =.. [F,A,X,B],
    call(Z), fold_left(F, B, Xs, C).

/*
?- divisor_num(12345678, M).

M = 24 ;

No
?- divisor_num(1234567890, M).

M = 48 ;

No
?- divisor_num(1999999991, M).

M = 8 ;

No
*/
divisor_num1(A, [_, X], B) :- B is A * (X + 1).
divisor_num(N, Ans) :- 
   factorization(N, Ls), fold_left(divisor_num1, 1, Ls, Ans).

prime_sum(_, 0, Acc, Ans) :- Ans is Acc + 1.
prime_sum(P, N, Acc, Ans) :-
    N < 0,
    N1 is N - 1,
    Acc1 is Acc + P ^ N,
    prime_sum(P, N1, Acc1, Ans).

/*
?- divisor_sum(12, M).

M = 28 ;

No
?- divisor_sum(12345678, M).

M = 27319968 ;

No
*/
divisor_sum1(Acc, [P, N], Ans) :- prime_sum(P, N, 0, X), Ans is Acc * X.
divisor_sum(N, Ans) :-
    factorization(N, Ls), fold_left(divisor_sum1, 1, Ls, Ans).


divisor_sub(_, 0, Acc, [1 | Acc]).
divisor_sub(P, N, Acc, Ans) :-
    N > 0,
    M is P ^ N,
    N1 is N - 1,
    divisor_sub(P, N1, [M | Acc], Ans).

divisor_product(Xs, Ys, Z) :-
    member(X, Xs), member(Y, Ys), Z is X * Y.

divisor_sub1([], Ans, Ans).
divisor_sub1([[P, N] | Xs], Acc, Ans) :-
    divisor_sub(P, N, [], Ys),
    findall(Z, divisor_product(Acc, Ys, Z), Acc1),
    divisor_sub1(Xs, Acc1, Ans).

/*
?- divisor(12, L).

L = [1, 2, 3, 4, 6, 12] ;

No
?- divisor(12345678, L), length(L, N).

L = [1, 2, 3, 6, 9, 18, 47, 94, 141|...],
N = 24 ;

No
?- divisor(1234567890, L), length(L, N).

L = [1, 2, 3, 5, 6, 9, 10, 15, 18|...],
N = 48 ;

No
?- divisor(1999999991, L), length(L, N).

L = [1, 11, 349, 3839, 520969, 5730659, 181818181, 1999999991],
N = 8 ;


*/
divisor(N, L) :-
    factorization(N, Xs),
    divisor_sub1(Xs, [1], Ys),
    sort(Ys, L).

part_num(0, _, 1).
part_num(1, _, 1).
part_num(_, 1, 1).
part_num(N, K, 0) :- (N < 0 ; K < 1).

part_num(N, K, A) :-
    N1 is N - K,
    part_num(N1, K, A1),
    K1 is K - 1,
    part_num(N, K1, A2),
    A is A1 + A2.

/*
?- between(1, 20, I), partition_number(I, N), write(N), nl, fail.
1
2
3
5
7
11
15
22
30
42
56
77
101
135
176
231
297
385
490
627

*/
partition_number(N, A) :- part_num(N, N, A).


/*
?- partition_of_integer(6, L), write(L), nl, fail.
[6]
[5, 1]
[4, 2]
[4, 1, 1]
[3, 3]
[3, 2, 1]
[3, 1, 1, 1]
[2, 2, 2]
[2, 2, 1, 1]
[2, 1, 1, 1, 1]
[1, 1, 1, 1, 1, 1]


*/
part_int(0, _, []) :- !.

part_int(N, K, [K | A]) :-
    N1 is N - K,
    N1 >= 0,
    part_int(N1, K, A).

part_int(N, K, A) :-
    K1 is K - 1,
    K1 >= 1,
    part_int(N, K1, A).

partition_of_integer(N, A) :- part_int(N, N, A).


/*
?- perfect_permutation(4, X), write(X), nl, fail.
[2, 1, 4, 3]
[2, 3, 4, 1]
[2, 4, 1, 3]
[3, 1, 4, 2]
[3, 4, 1, 2]
[3, 4, 2, 1]
[4, 1, 2, 3]
[4, 3, 1, 2]
[4, 3, 2, 1]

*/
perfect_perm_sub(_, [], Acc, Ans) :- reverse(Acc, Ans).
perfect_perm_sub(N, Ls, Acc, Ans) :-
    select(X, Ls, Xs),
    N =\= X,
    N1 is N + 1,
    perfect_perm_sub(N1, Xs, [X | Acc], Ans).
perfect_permutation(M, Ans) :-
    iota(1, M, Ls),
    perfect_perm_sub(1, Ls, [], Ans).

/*
?- between(1, 16, I), montmort_number(I, A), write(A), nl, fail.
0
1
2
9
44
265
1854
14833
133496
1334961
14684570
176214841
2290792932
32071101049
481066515734
7697064251745

*/
montmort_number(1, 0).
montmort_number(2, 1).
montmort_number(N, A) :-
    N > 2,
    N1 is N - 1,
    montmort_number(N1, A1),
    N2 is N - 2,
    montmort_number(N2, A2),
    A is N1 * (A1 + A2).

% \95ʉ\F0
montmort_sub(N, N, A, _, A).
montmort_sub(I, N, A, B, Ans) :-
    I < N,
    I1 is I + 1,
    A1 is I1 * (A + B),
    montmort_sub(I1, N, B, A1, Ans).
montmort_number_fast(N, A) :- montmort_sub(1, N, 0, 1, A).

/*
?- partition_of_set([1,2,3], Ls), write(Ls), nl, fail.
[[1, 2, 3]]
[[1], [2, 3]]
[[1, 2], [3]]
[[1, 3], [2]]
[[1], [2], [3]]

No
?- partition_of_set([1,2,3,4], Ls), write(Ls), nl, fail.
[[1, 2, 3, 4]]
[[1], [2, 3, 4]]
[[1, 2], [3, 4]]
[[1, 3, 4], [2]]
[[1], [2], [3, 4]]
[[1, 2, 3], [4]]
[[1, 4], [2, 3]]
[[1], [2, 3], [4]]
[[1, 2, 4], [3]]
[[1, 3], [2, 4]]
[[1], [2, 4], [3]]
[[1, 2], [3], [4]]
[[1, 3], [2], [4]]
[[1, 4], [2], [3]]
[[1], [2], [3], [4]]

*/

part_set([], Ys, Ys).
part_set([X | Xs], Ys, A) :-
    select(Z, Ys, Zs),
    part_set(Xs, [[X | Z] | Zs], A).
part_set([X | Xs], Ys, A) :-
    part_set(Xs, [[X] | Ys], A).

partition_of_set(Xs, Ys) :- 
    reverse(Xs, Xs1), part_set(Xs1, [], Ys).

/*
?- between(0, 10, I), bell_number(I, A), write(A), nl, fail.
1
1
2
5
15
52
203
877
4140
21147
115975


*/

bell_next(_, _, [], Acc, Acc).
bell_next(N, K, [B | Bs], Acc, Ans) :-
    comb_num(N, K, C),
    Acc1 is Acc + C * B,
    K1 is K + 1,
    bell_next(N, K1, Bs, Acc1, Ans).

bell_number_sub(N, N, [A | _], A).
bell_number_sub(I, N, Bs, A) :-
    I < N,
    bell_next(I, 0, Bs, 0, N1),
    I1 is I + 1,
    bell_number_sub(I1, N, [N1 | Bs], A).

bell_number(N, A) :-
    bell_number_sub(0, N, [1], A).

/*
?- group_partition(2, 2, [1,2,3,4], X), write(X), nl, fail.
[[1, 2], [3, 4]]
[[1, 4], [2, 3]]
[[1, 3], [2, 4]]

No
?- group_partition(2, 3, [1,2,3,4,5,6], X), write(X), nl, fail.
[[1, 2], [3, 4], [5, 6]]
[[1, 4], [2, 3], [5, 6]]
[[1, 3], [2, 4], [5, 6]]
[[1, 2], [3, 6], [4, 5]]
[[1, 6], [2, 3], [4, 5]]
[[1, 3], [2, 6], [4, 5]]
[[1, 2], [3, 5], [4, 6]]
[[1, 5], [2, 3], [4, 6]]
[[1, 3], [2, 5], [4, 6]]
[[1, 6], [2, 5], [3, 4]]
[[1, 5], [2, 6], [3, 4]]
[[1, 6], [2, 4], [3, 5]]
[[1, 4], [2, 6], [3, 5]]
[[1, 5], [2, 4], [3, 6]]
[[1, 4], [2, 5], [3, 6]]


*/

group_part(_, _, [], Ys, Ys).
group_part(N, M, [X | Xs], Ys, A) :-
    select(Z, Ys, Zs),
    length(Z, N1),
    N1 < N,
    group_part(N, M, Xs, [[X | Z] | Zs], A).
group_part(N, M, [X | Xs], Ys, A) :-
    length(Ys, M1),
    M1 < M,
    group_part(N, M, Xs, [[X] | Ys], A).

group_partition(N, M, Xs, Ys) :- 
    reverse(Xs, Xs1), group_part(N, M, Xs1, [], Ys).


group_part_sub(0, N, M, Acc, A) :- 
    fact(M, X),
    A is Acc // X.
group_part_sub(K, N, M, Acc, A) :-
    K > 0,
    K1 is K - N,
    comb_num(K, N, X),
    Acc1 is Acc * X,
    group_part_sub(K1, N, M, Acc1, A).
/*
?- group_partition_number(2,2,X).

X = 3 ;

No
?- group_partition_number(2,3,X).

X = 15 ;

No
?- group_partition_number(3,3,X).

X = 280 ;

No
?- group_partition_number(3,4,X).

X = 15400 ;

No
?- group_partition_number(3,5,X).

X = 1401400 ;
*/
group_partition_number(N, M, A) :-
    K is N * M,
    group_part_sub(K, N, M, 1, A).
    
:- end_body(math).
