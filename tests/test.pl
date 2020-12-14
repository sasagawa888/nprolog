
sum1(0,0) :- !.
sum1(J,S1) :- I is J-1,sum1(I,S),S1 is S + J.

sum2(0,0).
sum2(J,S1) :- J>0,I is J-1,sum2(I,S),S1 is S + J.

sigma(A - B,Sum) :- 
    C is B - A,
    sigma_aux([A,C,Sum],0,A).

sigma_aux([A,C,Sum],C,Sum).
sigma_aux(Const,N,Sum) :-
    Const = [A|_],
    N1 is N+1,
    Sum1 is Sum + N1 + A,
    sigma_aux(Const,N1,Sum1).

