%
% numplace.swi : ナンバープレースの解法
%
%                Copyright (C) 2016 Makoto Hiroi
%

% 述語 == による member
memq(X, [Y | _]) :- X == Y.
memq(X, [_ | Ys]) :- memq(X, Ys).

% memq による集合述語
unionq([], Ys, Ys).
unionq([X | Xs], Ys, Zs) :- memq(X, Ys), !, unionq(Xs, Ys, Zs).
unionq([X | Xs], Ys, [X | Zs]) :- unionq(Xs, Ys, Zs).

intersectq([], _, []).
intersectq([X | Xs], Ys, [X | Zs]) :-
    memq(X, Ys), !, intersectq(Xs, Ys, Zs).
intersectq([_ | Xs], Ys, Zs) :- intersectq(Xs, Ys, Zs).

differenceq([], _, []).
differenceq([X | Xs], Ys, Zs) :-
    memq(X, Ys), !, differenceq(Xs, Ys, Zs).
differenceq([X | Xs], Ys, [X | Zs]) :- differenceq(Xs, Ys, Zs).

% 行列の転置
head([X | _], X).
tail([_ | Xs], Xs).

transpose(Xs, []) :- member([], Xs), !.
transpose(Xs, [Y | Ys]) :-
    maplist(head, Xs, Y),
    maplist(tail, Xs, Xs1),
    transpose(Xs1, Ys).

% ブロックの生成
make_block_sub([],[],[],[]).
make_block_sub([X1, X2, X3 | Xs],
               [Y1, Y2, Y3 | Ys],
               [Z1, Z2, Z3 | Zs],
               [[X1, X2, X3, Y1, Y2, Y3, Z1, Z2, Z3] | Bs]) :-
    make_block_sub(Xs, Ys, Zs, Bs).
    
%
make_block([], []).
make_block([X, Y, Z | Ls], Gs) :-
    make_block_sub(X, Y, Z, Gs1),
    make_block(Ls, Gs2),
    append(Gs1, Gs2, Gs).

% 数字を取り出す
get_number(X, Y, Ls, N) :-  nth0(Y, Ls, L), nth0(X, L, N).

% 解析
analysis_sub(X, Y, N, Ls, Cs, Gs, [N, As, Bs]) :-
    nth0(Y, Ls, Ys),
    nth0(X, Cs, Xs),
    G is (Y // 3) * 3 + X // 3,
    nth0(G, Gs, Zs),
    % 数字と変数に分ける
    partition(integer, Ys, Ys1, Ys2),
    partition(integer, Xs, Xs1, Xs2),
    partition(integer, Zs, Zs1, Zs2),
    unionq(Ys1, Xs1, As1),
    unionq(Zs1, As1, As2),
    % 未確定の数字
    differenceq([1,2,3,4,5,6,7,8,9], As2, As),
    % 変数のリスト
    unionq(Ys2, Xs2, Bs1),
    unionq(Zs2, Bs1, Bs).

analysis(_, 9, _, _, _, []).
analysis(9, Y, Ls, Cs, Gs, Zs) :-
    Y1 is Y + 1, analysis(0, Y1, Ls, Cs, Gs, Zs).
analysis(X, Y, Ls, Cs, Gs, Zs) :-
    get_number(X, Y, Ls, N),
    nonvar(N),
    X1 is X + 1,
    analysis(X1, Y, Ls, Cs, Gs, Zs).
analysis(X, Y, Ls, Cs, Gs, [Z | Zs]) :-
    get_number(X, Y, Ls, N),
    var(N),
    analysis_sub(X, Y, N, Ls, Cs, Gs, Z),
    X1 is X + 1,
    analysis(X1, Y, Ls, Cs, Gs, Zs).

% 深さ優先探索
dfs([]).
dfs([[N, As, Bs] | Vs]) :-
    member(I, As),
    maplist(\==(I), Bs),
    N = I,
    dfs(Vs).

% 解法
solver(N) :-
    problem(N, Ls),
    transpose(Ls, Cs),
    make_block(Ls, Gs),
    analysis(0, 0, Ls, Cs, Gs, Vs),
    dfs(Vs),
    maplist(write, Ls),
    fail.

% N-Prologのための追加
writeln(X) :-
    write(X),
    nl.

% maplist/2
maplist(_,[]).
maplist(P,[L|Ls]) :-
    P1 =.. [P,L],
    call(P1),
    maplist(P,Ls).

% maplist/3
% require call/3 but N-Prolog does not have call/3
maplist(_,[],[]).
maplist(P,[L|Ls],[Y|Z]) :-
    my_call2(P,L,Y),
    maplist(P,Ls,Z).

my_call2(X,A,Y) :-
    P =.. [X,A,Y],
    call(P).

nth0(0,[X|_],X).
nth0(N,[_|Xs],Y) :-
    N1 is N-1,
    nth0(N1,Xs,Y).

partition(_,[],[],[]).
partition(P,[L|Ls],[L|Y],Z) :-
    P1 =.. [P,L],
    call(P1),
    partition(P,Ls,Y,Z).
partition(P,[L|Ls],Y,[L|Z]) :-
    partition(P,Ls,Y,Z).

% 問題 (出典: 数独 - Wikipedia の問題例)
problem(0, [[5,3,_,  _,7,_,  _,_,_],
            [6,_,_,  1,9,5,  _,_,_],
            [_,9,8,  _,_,_,  _,6,_],

            [8,_,_,  _,6,_,  _,_,3],
            [4,_,_,  8,_,3,  _,_,1],
            [7,_,_,  _,2,_,  _,_,6],

            [_,6,_,  _,_,_,  2,8,_],
            [_,_,_,  4,1,9,  _,_,5],
            [_,_,_,  _,8,_,  _,7,9]]).

