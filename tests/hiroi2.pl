/*
written by M.Hiroi

thanks

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
