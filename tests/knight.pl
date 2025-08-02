% Knight tour
% 5*5


% tour start from (R,C), X is path
tour(R,C,X) :-
    move(R,C,[[R,C]],X).

safe(R,C) :- 
    R >= 1,R =< 5,
    C >= 1,C =< 5.

move(R,C,P,P) :-
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
