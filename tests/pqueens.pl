% 10-queens program in parallel  

para :- dp_and([test1,test2]).
seq :- test1,test2.

test1 :- queens1,queens2,queens3,queens4,queens5.
test2 :- queens6,queens7,queens8,queens9,queens10.  

queens1 :- queen(1,[2,3,4,5,6,7,8,9,10],X),fail.  
queens1.
queens2 :- queen(2,[1,3,4,5,6,7,8,9,10],X),fail.  
queens2.
queens3 :- queen(3,[1,2,4,5,6,7,8,9,10],X),fail.  
queens3.
queens4 :- queen(4,[1,2,3,5,6,7,8,9,10],X),fail.  
queens4.
queens5 :- queen(5,[1,2,3,4,6,7,8,9,10],X),fail.
queens5. 
queens6 :- queen(6,[1,2,3,4,5,7,8,9,10],X),fail.  
queens6.
queens7 :- queen(7,[1,2,3,4,5,6,8,9,10],X),fail.  
queens7.
queens8 :- queen(8,[1,2,3,4,5,6,7,9,10],X),fail.  
queens8.
queens9 :- queen(9,[1,2,3,4,5,6,7,8,10],X),fail.  
queens9.
queens10 :- queen(10,[1,2,3,4,5,6,7,8,9],X),fail.  
queens10.

queen(N, Data, [N|Out]) :-  
 queen_2(N, Data, [N], Out).  

queen_2(_, [], _, []).  
queen_2(N, [H|T], History, [Q|M]) :-  
 qdelete(Q, H, T, L1),  
 nodiag(History, Q, 1),  
 queen_2(N, L1, [Q|History], M).  

qdelete(A, A, L, L).  
qdelete(X, A, [H|T], [A|R]) :-  
 qdelete(X, H, T, R).  


nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).
 