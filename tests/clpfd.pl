% CLP-test 

:- use_module(clpfd).

ac :-
    X in 1..3,
    Y in 1..3,
    Z in 1..3,
    X+Y+Z#=3,
    ac3.

foo(L) :-
    L = [A, B, C],
    L ins 1..3,
    all_different(L),
    A#>C,
    label(L).

n_factorial(0, 1).
n_factorial(N, F) :-
        N #> 0,
        N1 #= N - 1,
        n_factorial(N1, F1),
        F #= N * F1.

test1(X) :-
    X in 1..3,
    label([X]).


test2(X, Y) :-
    X in 1..4,
    Y in 1..4,
    X #= Y+1,
    X #>= Y,
    label([X, Y]).

test3(X, Y) :-
    X in 1..2,
    Y in 2..3,
    all_different([X, Y]),
    label([X, Y]).

test4(X) :-
    X in 1..5,
    X #\= 3,
    label([X]).

test5(X,Y) :-
    X in 1..5,
    Y in 1..3,
    X #= Y,
    X+Y #= 6,
    label([X,Y]).

test6(X, Y, Z) :-
    X in 1..3,
    Y in 1..3,
    Z in 1..3,
    X + Y + Z #= 5,
    X #< Z,
    label([X, Y, Z]).

test7(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y mod 3,
    label([X,Y]).

test8(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y ^ 3,
    label([X,Y]).

test9(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y ** 3,
    label([X,Y]).


test10(X,Y) :-
    X in 1..10,
    Y in 1..10,
    X #= Y // 3,
    label([X,Y]).


test :- nqueens(X),fail.

nqueens(Queens) :-
    length(Queens, 9),       
    Queens ins 1..9,         
    all_different(Queens),   
    safe(Queens),       
    label(Queens).
    
safe([]).
safe([Q|Rest]) :-
    safe(Rest),
    no_attack(Q, Rest, 1).
    
no_attack(_, [], _).
no_attack(Q, [Q2|Rest], Dist) :-
    Q #\= Q2 + Dist,  
    Q #\= Q2 - Dist,
    Dist1 #= Dist + 1,
    no_attack(Q, Rest, Dist1).


magic(Xs) :-
    Xs = [A, B, C, D, E, F, G, H, I],
    Xs ins 1..9,
    all_different(Xs),
    N #= A + B + C,
    N #= D + E + F,
    N #= G + H + I,
    N #= A + D + G,
    N #= B + E + H,
    N #= C + F + I,
    N #= A + E + I,
    N #= C + E + G,
    label(Xs).


boo(Xs) :-
    Xs = [A,B,C],
    Xs ins 1..9,
    %all_different(Xs),
    N #= A+B,
    N #= B+C,
    label(Xs).

equations(X,Y,Z) :-
    X + Y + Z #= 10, 
    2*X + 4*Y + 6*Z #= 38,
    2*X + 4*Z #= 14,
    [X,Y,Z] ins 1..10,
    label([X,Y,Z]).

perm(Xs) :-
    Xs = [X, Y, Z], 
    Xs ins 1..3,
    X #\= Y,
    X #\= Z,
    Y #\= Z,
    label(Xs).

mask(Wrong,M,Right) :-
    Xs = [W, R, O, N, G, M, I, H, T],
    Xs ins 1..9,
    all_different(Xs),
    Wrong #= 10000*W + 1000*R + 100*O + 10*N + G,
    Right #= 10000*R + 1000*I + 100*G + 10*H + T,
    Wrong * M #= Right,
    label([Wrong,M,Right]).

send([S,E,N,D,M,O,R,Y]) :-
    Vars = [M,S,E,O,N,R,D,Y],
    Vars ins 0..9,
    all_different(Vars),
    S #\= 0,
    M #\= 0,
    (D+E) mod 10 #= Y,
    (((D+E) // 10) + N+R) mod 10 #= E,
    (((((D+E) // 10) + N+R) // 10) + E+O) mod 10 #= N,
    ((((((D+E) // 10) + N+R) // 10) + E+O) // 10) + S+M #= 10*M,
    1000*S + 100*E + 10*N + D + 1000*M + 100*O + 10*R + E
    #= 10000*M + 1000*O + 100*N + 10*E + Y,
    label(Vars).

taxi(Vars) :-
    Vars = [A1, B1, A2, B2],
    Vars ins 1..20, 
    all_different(Vars),
    A1 #< B1,
    A2 #< B2,
    N #= A1^3 + B1^3,
    N #= A2^3 + B2^3,
    label(Vars).
