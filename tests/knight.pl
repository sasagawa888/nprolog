% Knight tour
% 5*5
/*
fastest([R1,C1],[R2,C2],[R3,C3],[R4,C4],X) :-
    dp_or([tour(R1,C1,X),tour(R2,C2,X),tour(R3,C3,X),tour(R4,C4,X)]).

ptour8(R,C,X) :-
    dp_or([pmove81(R,C,X),pmove82(R,C,X),pmove83(R,C,X),pmove84(R,C,X),
           pmove85(R,C,X),pmove86(R,C,X),pmove87(R,C,X),pmove88(R,C,X)]).

ptour4(R,C,X) :-
    dp_or([pmove1(R,C,X),pmove2(R,C,X),pmove3(R,C,X),pmove4(R,C,X)]).

pmove1(R,C,X) :-
    (R1 is R+2,C1 is C+1,move(R1,C1,[[R1,C1],[R,C]],X);
     R1 is R+1,C1 is C+2,move(R1,C1,[[R1,C1],[R,C]],X)).

pmove2(R,C,X) :-
    (R1 is R-2,C1 is C-1,move(R1,C1,[[R1,C1],[R,C]],X);
     R1 is R-1,C1 is C-2,move(R1,C1,[[R1,C1],[R,C]],X)).

pmove3(R,C,X) :-
    (R1 is R+2,C1 is C-1,move(R1,C1,[[R1,C1],[R,C]],X);
     R1 is R+1,C1 is C-2,move(R1,C1,[[R1,C1],[R,C]],X)).

pmove4(R,C,X) :-
    (R1 is R-2,C1 is C+1,move(R1,C1,[[R1,C1],[R,C]],X);
     R1 is R-1,C1 is C+2,move(R1,C1,[[R1,C1],[R,C]],X)).
    
pmove81(R,C,X) :-
    R1 is R+2,C1 is C+1,move(R1,C1,[[R1,C1],[R,C]],X).

pmove82(R,C,X) :-
    R1 is R+1,C1 is C+2,move(R1,C1,[[R1,C1],[R,C]],X).

pmove83(R,C,X) :-
    R1 is R-2,C1 is C-1,move(R1,C1,[[R1,C1],[R,C]],X).

pmove84(R,C,X) :-
    R1 is R-1,C1 is C-2,move(R1,C1,[[R1,C1],[R,C]],X).

pmove85(R,C,X) :-
    R1 is R+2,C1 is C-1,move(R1,C1,[[R1,C1],[R,C]],X).

pmove86(R,C,X) :-
    R1 is R+1,C1 is C-2,move(R1,C1,[[R1,C1],[R,C]],X).

pmove87(R,C,X) :-
    R1 is R-2,C1 is C+1,move(R1,C1,[[R1,C1],[R,C]],X).

pmove88(R,C,X) :-
    R1 is R-1,C1 is C+2,move(R1,C1,[[R1,C1],[R,C]],X).
*/
    
% tour start from (R,C), X is path
tour(R,C,X) :-
    move(R,C,[[R,C]],X).

safe(R,C) :- 
    R >= 1,R =< 5,
    C >= 1,C =< 5.

move(_,_,P,P) :-
    write(P),
    length(P,25).


move(R,C,P,A) :-
    R1 is R+2,
    C1 is C+1,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R+1,
    C1 is C+2,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R-2,
    C1 is C-1,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R-1,
    C1 is C-2,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R+2,
    C1 is C-1,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R+1,
    C1 is C-2,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R-2,
    C1 is C+1,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).

move(R,C,P,A) :-
    R1 is R-1,
    C1 is C+2,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).
