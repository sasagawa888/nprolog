

move(R,C,P,A) :-
    R1 is R+2,
    C1 is C+1,
    safe(R1,C1),
    not(member([R1,C1],P)),
    move(R1,C1,[[R1,C1]|P],A).
