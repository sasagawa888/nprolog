
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

myappend([],L,L) :- !.
myappend([A|L],B, [A|C]):-
	myappend(L,B,C).

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


/* quick sort OK */
/* 農夫問題　答えがNO */
/* 経路の探索（２）　ok*/
/* 積み木の移動　OK*/
/* ライツアウト　リソースエラー*/

test(N) :-
    ifthenelse(odd(N),write(odd_number),write(even_numver)).

test1(N) :-
    odd(N)->write(odd_number);write(even_number).


odd(N) :- X is N mod 2,X \= 0.

/*
written by M.Hiroi
thanks.
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