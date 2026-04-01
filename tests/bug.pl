% CLP-test  

:- use_module(clpfd).

:- dynamic(nqueens/1).
nqueens(Queens) :-
    length(Queens, 9),       
    Queens ins 1..9,         
    all_different(Queens),   
    safe(Queens),     
    label(Queens,trace).

:- dynamic(safe/1).
safe([]).
safe([Q|Rest]) :-
    safe(Rest),
    no_attack(Q, Rest, 1).

:- dynamic(no_attack/3).
no_attack(_, [], _).
no_attack(Q, [Q2|Rest], Dist) :-
    Q #\= Q2 + Dist,  
    Q #\= Q2 - Dist,
    Dist1 #= Dist + 1,
    no_attack(Q, Rest, Dist1).

