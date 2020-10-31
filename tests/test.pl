
fact(0,1).
fact(X,Y) :- 
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.

hanoi(1, From, To, _) :- write([From, to, To]), nl.
hanoi(N, From, To, Via) :-
        N1 is N - 1, hanoi(N1, From, Via, To),
        write([From, to, To]), nl,
        hanoi(N1, Via, To, From).

bar(0).
bar(N) :-
    N1 is N-1,
    bar(N1).

my_member(X, [X | Ls]).
my_member(X, [Y | Ls]) :- my_member(X, Ls).

intersection([],Y,[]).
intersection([X|Xs],Y,[X|Z]) :-
    member(X,Y),
    intersection(Xs,Y,Z).
intersection([X|Xs],Y,Z) :-
    intersection(Xs,Y,Z).

union([],Y,Y).
union([X|Xs],Y,Z) :-
    member(X,Y),
    union(Xs,Y,Z).
union([X|Xs],Y,[X|Z]) :-
    union(Xs,Y,Z).

square(X,Y) :- Y is X*X.

first([X | Ys], X).
rest([X | Ys], Ys).
add_to_list(X, Ls, [X | Ls]).

retrieve(1,  [X | Ls], X).
retrieve(N, [Y | Ls], X) :-
    N > 1, N1 is N - 1, retrieve(N1, Ls, X).

insert_at(1, X, Ls, [X | Ls]).
insert_at(N, X, [Y | Ls], [Y | Zs]) :-
    N > 1, N1 is N - 1, insert_at(N1, X, Ls, Zs).

remove_at(1, [X | Ls], Ls).
remove_at(N, [X | Ls], [X | Zs]) :-
    N > 0, N1 is N - 1, remove_at(N1, Ls, Zs). 

my_length([], 0).
my_length([X | Xs], N) :- my_length(Xs, N1), N is N1 + 1.

my_append([], Xs, Xs).
my_append([X | Ls], Ys, [X | Zs]) :- my_append(Ls, Ys, Zs).

my_reverse([], []).
my_reverse([X | Xs], Ys) :-
    my_reverse(Xs, Zs), append(Zs, [X], Ys).

my_select(X, [X | Xs], Xs).
my_select(X, [Y | Ys], [Y | Zs]) :- my_select(X, Ys, Zs).

selects([], Ys).
selects([X | Xs], Ys) :- my_select(X, Ys, Ys1), selects(Xs, Ys1).


my_flatten([X | Xs], Ys) :-
    my_flatten(X, Ys1), my_flatten(Xs, Ys2), append(Ys1, Ys2, Ys).
my_flatten(X, [X]) :- atomic(X), X \== [].
my_flatten([], []).

/*
written by M.Hiroi
thanks

?- solve.
*/
set_op(N, Exp, [N, + | Exp]).
set_op(N, Exp, [N, - | Exp]).
set_op(N, [N1 | Rest], [N2 | Rest]) :- N2 is N1 * 10 + N.

make_exp(10, Exp) :-
    reverse(Exp, Exp1), calc_exp(Exp1, N), N =:= 100, write(Exp1), nl, fail.

make_exp(N, Exp):-
    N < 10, set_op(N, Exp, Exp1), N1 is N + 1, make_exp(N1, Exp1).

calc_one_exp(A, +, B, N):- N is A + B.
calc_one_exp(A, -, B, N):- N is A - B.

calc_exp([Num], Num).
calc_exp([A, Op, B | Rest], Num) :-
    calc_one_exp(A, Op, B, Num1), calc_exp([Num1 | Rest], Num).

solve :- make_exp(2, [1]).



/*
written by M.Hiroi
thanks.

?- depth_search([[left, left, left, left]]).
*/
/* 農夫だけ */
move([F, G, W, C], [NF, G, W, C]) :- (F == left -> NF = right ; NF = left).

/* 農夫と山羊 */
move([F, F, W, C], [NF, NF, W, C]) :- (F == left -> NF = right ; NF = left).

/* 農夫と狼 */
move([F, G, F, C], [NF, G, NF, C]) :- (F == left -> NF = right ; NF = left).

/* 農夫とキャベツ */
move([F, G, W, F], [NF, G, W, NF]) :- (F == left -> NF = right ; NF = left).

safe([F, G, W, C]) :-
    safe_cabbage(F, G, C), safe_goat(F, G, W).

safe_cabbage(F, G, C) :- F == C.
safe_cabbage(F, G, C) :- G \== C.

safe_goat(F, G, W) :- F == G.
safe_goat(F, G, W) :- G \== W.

depth_search([State | History]) :-
    State == [right, right, right, right], !, print_answer([State | History]).

depth_search([State | History]) :-
    move(State, NewState),
    safe(NewState),
    not(member(NewState, History)),
    depth_search([NewState, State | History]).

print_answer([]) :- !.
print_answer([State | Rest]) :-
    print_answer(Rest), write(State), nl. 