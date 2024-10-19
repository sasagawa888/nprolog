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

%p131
memberr([A],X,1) :- member(A,X).
memberr([A|LA],[A|Y],R) :-
        R>1,R1 is R-1,memberr(LA,Y,R1).
memberr(A,[_|Y],R) :-
        R>1,memberr(A,Y,R).
        
/* generate [1,2,3,4,...] */
generate_e(N,E) :- gene_e_aux(E,N,[]).
gene_e_aux(L,0,L) :- !.
gene_e_aux(Result,N,L) :-
            N1 is N-1,
            gene_e_aux(Result,N1,[N|L]).
            
/* problem */


comb(N,R) :- generate_e(N,X),
             memberr(A,X,R),
             write(A),nl,fail.
    
    
permutation([],[]).
permutation([A|X1],Y) :-
             delete0(Y1 = Y - A),
             permutation(X1,Y1).
      
delete0(X = [A|X]-A).
delete0([B|Y] = [B|X] - A) :- 
             delete0(Y = X - A).
             
