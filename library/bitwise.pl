/*
Copyright c M.Hiroi All Rights Reserved.
http://www.geocities.jp/m_hiroi/prolog/index.html
*/
:- module(bitwise).
:- export([log_and/3,log_or/3,log_xor/3,half_adder/4,full_adder/5,
uint_and/3,uint_or/3,uint_xor/3,log_not/2,uint_not/2,uint_add/4,
uint_inc/3,uint_sub/4,uint_sll/3,uint_srl/3,uint_greater/2,
uint_lesser/2,uint_zero/1,uint_equal/2,make_zero/2,uint_mul/3,
make_one/2,uint_div/4]).


:- end_module(bitwise).

:- body(bitwise).
/*
?- log_and(X, Y, Z), write([X, Y, Z]), nl, fail.
[0, 0, 0]
[1, 0, 0]
[0, 1, 0]
[1, 1, 1]

No
?- log_or(X, Y, Z), write([X, Y, Z]), nl, fail.
[0, 0, 0]
[1, 0, 1]
[0, 1, 1]
[1, 1, 1]

No
?- log_xor(X, Y, Z), write([X, Y, Z]), nl, fail.
[0, 0, 0]
[1, 0, 1]
[0, 1, 1]
[1, 1, 0]


*/
log_and(0, 0, 0).
log_and(1, 0, 0).
log_and(0, 1, 0).
log_and(1, 1, 1).

log_or(0, 0, 0).
log_or(1, 0, 1).
log_or(0, 1, 1).
log_or(1, 1, 1).

log_xor(0, 0, 0).
log_xor(1, 0, 1).
log_xor(0, 1, 1).
log_xor(1, 1, 0).

/*
?- half_adder(P, Q, S, C), write([P, Q, S, C]), nl, fail.
[0, 0, 0, 0]
[1, 0, 1, 0]
[0, 1, 1, 0]
[1, 1, 0, 1]
*/
half_adder(P, Q, S, C) :- log_xor(P, Q, S), log_and(P, Q, C).

/*
?- full_adder(P, Q, R, S, C), write([P, Q, R, S, C]), nl, fail.
[0, 0, 0, 0, 0]
[0, 0, 1, 1, 0]
[1, 0, 0, 1, 0]
[1, 0, 1, 0, 1]
[0, 1, 0, 1, 0]
[0, 1, 1, 0, 1]
[1, 1, 0, 0, 1]
[1, 1, 1, 1, 1]
*/
full_adder(P, Q, R, C, E) :-
    half_adder(P, Q, A, B),
    half_adder(A, R, C, D),
    log_or(B, D, E).

/*
?- integer_to_uint(255, 8, N).

N = [1, 1, 1, 1, 1, 1, 1, 1] ;

No
?- integer_to_uint(0, 8, N).

N = [0, 0, 0, 0, 0, 0, 0, 0] ;

No
?- integer_to_uint(127, 8, N).

N = [0, 1, 1, 1, 1, 1, 1, 1] ;

No
?- uint_to_integer([0, 0, 0, 0, 0, 0, 0, 0], N).

N = 0 ;

No
?- uint_to_integer([0, 1, 1, 1, 1, 1, 1, 1], N).

N = 127 ;

No
?- uint_to_integer([1, 1, 1, 1, 1, 1, 1, 1], N).

N = 255 ;
*/
i_to_u(_, M, Acc, Acc) :- length(Acc, M), !.
i_to_u(Num, M, Acc, Uint) :-
    N is Num mod 2,
    Num1 is Num // 2,
    i_to_u(Num1, M, [N | Acc], Uint).
integer_to_uint(N, M, Uint) :- i_to_u(N, M, [], Uint).

u_to_i([], Acc, Acc).
u_to_i([X | Xs], Acc, Num) :-
    Acc1 is Acc * 2 + X,
    u_to_i(Xs, Acc1, Num).
uint_to_integer(Uint, Num) :- u_to_i(Uint, 0, Num).

/*
?- uint_and([0, 0, 1, 1], [0, 1, 0, 1], X).

X = [0, 0, 0, 1] ;

No
?- uint_or([0, 0, 1, 1], [0, 1, 0, 1], X).

X = [0, 1, 1, 1] ;

No
?- uint_xor([0, 0, 1, 1], [0, 1, 0, 1], X).

X = [0, 1, 1, 0] ;

No
?- uint_not([0, 1, 0, 1], X).

X = [1, 0, 1, 0] ;

No
*/
uint_and([], [], []).
uint_and([X | Xs], [Y | Ys], [Z | Zs]) :-
    log_and(X, Y, Z),
    uint_and(Xs, Ys, Zs).

uint_or([], [], []).
uint_or([X | Xs], [Y | Ys], [Z | Zs]) :-
    log_or(X, Y, Z),
    uint_or(Xs, Ys, Zs).

uint_xor([], [], []).
uint_xor([X | Xs], [Y | Ys], [Z | Zs]) :-
    log_xor(X, Y, Z),
    uint_xor(Xs, Ys, Zs).

log_not(0, 1).
log_not(1, 0).

uint_not([], []).
uint_not([X | Xs], [Y | Ys]) :-
    log_not(X, Y),
    uint_not(Xs, Ys).

/*
?- uint_add([0, 0, 0, 0], [0, 0, 0, 1], X, C).

X = [0, 0, 0, 1],
C = 0 ;

No
?- uint_add([0, 0, 0, 1], [0, 0, 0, 1], X, C).

X = [0, 0, 1, 0],
C = 0 ;

No
?- uint_add([1, 1, 1, 1], [0, 0, 0, 1], X, C).

X = [0, 0, 0, 0],
C = 1

No
*/
uint_add([X], [Y], [Z], C) :- half_adder(X, Y, Z, C).
uint_add([X | Xs], [Y | Ys], [Z | Zs], C) :-
    uint_add(Xs, Ys, Zs, C1),
    full_adder(X, Y, C1, Z, C).

/*
?- uint_inc([0, 0, 0, 0], X, C).

X = [0, 0, 0, 1],
C = 0 ;

No
?- uint_inc([0, 0, 0, 1], X, C).

X = [0, 0, 1, 0],
C = 0 ;

No
?- uint_inc([1, 1, 1, 1], X, C).

X = [0, 0, 0, 0],
C = 1 ;
*/
uint_inc([X], [Z], C) :- half_adder(X, 1, Z, C).
uint_inc([X | Xs], [Z | Zs], C) :-
    uint_inc(Xs, Zs, C1),
    half_adder(X, C1, Z, C).

/*
?- uint_sub([0, 0, 0, 1], [0, 0, 0, 1], X, C).

X = [0, 0, 0, 0],
C = 0 ;

No
?- uint_sub([0, 0, 0, 0], [0, 0, 0, 1], X, C).

X = [1, 1, 1, 1],
C = 1 ;

No
?- uint_sub([0, 0, 1, 1], [0, 0, 0, 1], X, C).

X = [0, 0, 1, 0],
C = 0 ;
*/
uint_sub(Xs, Ys, Zs, C) :-
    uint_not(Ys, Ys1),
    uint_inc(Ys1, Ys2, _),
    uint_add(Xs, Ys2, Zs, C1),
    log_not(C1, C).

/*
?- uint_sll([1, 1, 1, 1], X, C).

X = [1, 1, 1, 0],
C = 1 ;

No
?- uint_sll([0, 1, 1, 1], X, C).

X = [1, 1, 1, 0],
C = 0 ;

No
?- uint_srl([1, 1, 1, 1], X, C).

X = [0, 1, 1, 1],
C = 1 ;

No
?- uint_srl([1, 1, 1, 0], X, C).

X = [0, 1, 1, 1],
C = 0 ;
*/
uint_srl(Xs, [0 | Zs], C) :- append(Zs, [C], Xs).
uint_sll([C | Xs], Ys, C) :- append(Xs, [0], Ys).

/*
?- uint_equal([1, 0, 1, 0], [1, 0, 1, 0]).

Yes
?- uint_equal([1, 0, 1, 0], [1, 0, 1, 1]).

No
?- uint_greater([1, 0, 1, 1], [1, 0, 1, 0]).

Yes
?- uint_greater([1, 0, 1, 1], [1, 0, 1, 1]).

No
?- uint_lesser([1, 0, 1, 0], [1, 0, 1, 1]).

Yes
?- uint_lesser([1, 0, 1, 0], [1, 0, 0, 1]).

No
?- uint_zero([1, 0, 1, 0]).

No
?- uint_zero([0, 0, 0, 0]).

Yes
*/
uint_equal(Xs, Ys) :- Xs == Ys.

make_zero([], []).
make_zero([_ | Xs], [0 | Ys]) :- make_zero(Xs, Ys).

/*
?- uint_mul([0, 0, 0, 1], [1, 0, 0, 0], X).

X = [1, 0, 0, 0] ;

No
?- uint_mul([0, 0, 1, 1], [0, 1, 0, 0], X).

X = [1, 1, 0, 0] ;

No
?- uint_mul([0, 0, 1, 1], [0, 0, 1, 1], X).

X = [1, 0, 0, 1] ;

No
*/
uint_mul_sub(Xs, [1], Xs, Xs).
uint_mul_sub(Xs, [0], Xs, Ys) :- make_zero(Xs, Ys).
uint_mul_sub(Xs, [1 | Ys], Xs2, Zs) :-
    uint_mul_sub(Xs, Ys, Xs1, Zs1),
    uint_sll(Xs1, Xs2, _),
    uint_add(Zs1, Xs2, Zs, _).
uint_mul_sub(Xs, [0 | Ys], Xs2, Zs) :-
    uint_mul_sub(Xs, Ys, Xs1, Zs),
    uint_sll(Xs1, Xs2, _).
uint_mul(Xs, Ys, Ans) :- uint_mul_sub(Xs, Ys, _, Ans).

make_one([_], [1]).
make_one([_ | Xs], [0 | Ys]) :- make_one(Xs, Ys).


uint_lesser([X | _], [Y | _]) :- X < Y, !.
uint_lesser([X | Xs], [X | Ys]) :- uint_lesser(Xs, Ys).

/*
?- uint_div([0, 1, 0, 0], [0, 0, 1, 0], P, Q).

P = [0, 0, 1, 0],
Q = [0, 0, 0, 0] ;

No
?- uint_div([0, 1, 1, 0], [0, 0, 1, 0], P, Q).

P = [0, 0, 1, 1],
Q = [0, 0, 0, 0] ;

No
?- uint_div([0, 1, 1, 1], [0, 0, 1, 0], P, Q).

P = [0, 0, 1, 1],
Q = [0, 0, 0, 1] ;

No
?- uint_div([0, 1, 1, 1], [0, 0, 1, 1], P, Q).

P = [0, 0, 1, 0],
Q = [0, 0, 0, 1] ;

No
*/
uint_div(Xs, Ys, P, Xs) :-
    uint_lesser(Xs, Ys), make_zero(Xs, P), !.
uint_div(Xs, Ys, P, Q) :-
    uint_equal(Xs, Ys), make_one(Xs, P), make_zero(Xs, Q), !.
uint_div(Xs, [1 | Ys], P, Q) :-
    make_one(Xs, P), uint_sub(Xs, [1 | Ys], Q, _), !.
uint_div(Xs, Ys, P, Q) :-
    uint_sll(Ys, Ys1, _),
    uint_div(Xs, Ys1, P1, Q1),
    (uint_lesser(Q1, Ys) ->
        (uint_sll(P1, P, _), Q = Q1)
      ;
        (uint_sll(P1, P2, _), uint_inc(P2, P, _), uint_sub(Q1, Ys, Q, _))).
 
 :- end_body(bitwise).
 
