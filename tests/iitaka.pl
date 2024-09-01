% codes from Dr. iidaka's book


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

not0(P) :- P,!,fail.
not0(P).

for(I =< I,I) :- !.
for(I =< J,I).
for(I =< J,K) :- I1 is I+1,for(I1 =< J,K).

f99 :- for( 1 =< 9,X),for(1 =< 9,Y),
        Z is X*Y, write((Z = X * Y)),nl,fail.


test :- 
    X = [1,2,3,4,5],
    member(A,X),
    write(A),
    tab(1),
    fail.

positive(L) :- member(X,L),ifthenelse(X>0,fail,(!,fail)).
positive(L).


member2(A,B,[A|Y]) :- member(B,Y).
member2(A,B,[_|Y]) :- member2(A,B,Y).

set(L==M) :-
    sort(L,L0),
    sort(M,M0),
    L0 == M0.

:- op(700,xfx,isl).

Y isl [] + Y :- !.
Z isl [A|X] + Y :- member(A,Y),!,Z isl X + Y.
[A|Z] isl [A|X] + Y :- Z isl X + Y.