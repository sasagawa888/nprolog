% 10-queens program in parallel  

:- mt_create(2);
%parallel 10queens
para :- mt_and([test1,test2]).

test1 :- queens1,queens2,queens3,queens4,queens5.
test2 :- queens6,queens7,queens8,queens9,queens10.  

queens1 :- pqueen(1,[2,3,4,5,6,7,8,9,10],X),fail.  
queens1.
queens2 :- pqueen(2,[1,3,4,5,6,7,8,9,10],X),fail.  
queens2.
queens3 :- pqueen(3,[1,2,4,5,6,7,8,9,10],X),fail.  
queens3.
queens4 :- pqueen(4,[1,2,3,5,6,7,8,9,10],X),fail.  
queens4.
queens5 :- pqueen(5,[1,2,3,4,6,7,8,9,10],X),fail.
queens5. 
queens6 :- pqueen(6,[1,2,3,4,5,7,8,9,10],X),fail.  
queens6.
queens7 :- pqueen(7,[1,2,3,4,5,6,8,9,10],X),fail.  
queens7.
queens8 :- pqueen(8,[1,2,3,4,5,6,7,9,10],X),fail.  
queens8.
queens9 :- pqueen(9,[1,2,3,4,5,6,7,8,10],X),fail.  
queens9.
queens10 :- pqueen(10,[1,2,3,4,5,6,7,8,9],X),fail.  
queens10.

pqueen(N, Data, [N|Out]) :-  
 pqueen_2(N, Data, [N], Out).  


 pqueen_2(_, [], _, []).  
 pqueen_2(N, [H|T], History, [Q|M]) :-  
  qdelete(Q, H, T, L1),  
  nodiag(History, Q, 1),  
  pqueen_2(N, L1, [Q|History], M).  
 
% sequential 10queens
seq :- queen([1,2,3,4,5,6,7,8,9,10],X),fail.

queen(Data, Out) :-
     queen_2(Data, [], Out).


queen_2([], _, []).
queen_2([H|T], History, [Q|M]) :-
        qdelete(Q, H, T, L1),
        nodiag(History, Q, 1),
        queen_2(L1, [Q|History], M).
    

qdelete(A, A, L, L).  
qdelete(X, A, [H|T], [A|R]) :-  
 qdelete(X, H, T, R).  


nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).
 