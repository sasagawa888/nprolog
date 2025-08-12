
            
pmove1(R,C,X) :-
    (R1 is R+2,C1 is C+1,move(R1,C1,[[R1,C1],[R,C]],X);
     R1 is R+1,C1 is C+2,move(R1,C1,[[R1,C1],[R,C]],X)).
