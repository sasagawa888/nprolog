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


%p41
% quarternion q(A,B,C,D) see quarternion.pl


%63 
newton(X, A) :-
        newton1(1.0, A, A, X).

newton1(X1, X2, A, X) :-
        abs(X1 - X2) < 0.00001,
        X is X2.
newton1(X1, X2, A, X) :-
        Y is X1 / 2 + A / (2 * X1),
        newton1(Y, X1, A, X).

%p126
factor(P,I*Q) :-
        Q is integer(P/I + 0.001),
        R is P - I*Q,
        (R==0 ; Q < I).

factor(P/2):- factor(P,2*Q),!.
factor(P/I):- for(I =< P,J),
              J1 is 2*J+1,
              factor(P,J1*Q),
              ifthenelse(Q<J1,I=P,I=J1),!.



%p64
res_q(A=B*Q + R) :-
        B=\=0.0,Q is integer(A/B),R is A - B*Q.

ju(A/B) :- res_q(A=B*Q+R),
           write(Q),tab(1),
           A1 is R*10,
           ju(A1/B).
           

%p101
while_do(P,Q):- P,!,Q,fail.
while_do(P,Q).

%105
read_file(File_nameX):-
           open(H,File_nameX,r),
           repeat,
           while_do(get0(H,C),put(C)),
           close(H),!.

copy_file(File_nameX,File_nameY):-
           open(H1,File_nameX,r),
           create(H2,File_nameY),
           repeat,
           while_do(get0(H1,C),put(H2,C)),
           close(H1),close(H2),!.
           
%p78
cont_frc(A/B):- cont_frc_aux(A/B).
cont_frc_aux(A/B):-
     res_q(A=B*Q+R),write(Q),tab(1),
     cont_frc_aux(B/R).

%P141
set(L==M) :- sort(L,L0),sort(M,M0),L==M0.

%p100
memberd(X,L) :- member(X,L),!.

%p143
:- op(700,xfx,isl).
Y isl [] + Y :-!.
Z isl [A|X] + Y :-
memberd(A,Y),!,Z isl X + Y.
[A|Z] isl [A|X] + Y :- Z isl X + Y.

%p144
[] isl [] * Y :-!.
[A|Z] isl [A|Z] * Y :-
memberd(A, X),!,Z isl X * Y.
Z isl [A|X] * Y :- Z isl X * Y.

%p147
[] isl [] - A :- !.
Z isl [A|LA] - X :- memberd(A,X),!,Z isl LA -X.
[A|Z] isl [A|LA] - X :- Z isl LA - X.

%p147
[] isl [] / A.
X isl [A|X] / A :- !.
[C|X] isl [C|CL] / A :- X isl LC / A.

%p179
arg_list(K,Y,M) :- PY =.. [prd|Y],arg(K,PY,M).


:- op(700,xfx,isq).
% product of permutations X isq [2,3,1]*[2,3,1]. X = [3,1,2]
[J] isq X * [I] :-
    arg_list(I,X,J),!.
[J|LJ] isq X * [I|LI] :-
    arg_list(I,X,J),!,LJ isq X * LI.

%p180
:- op(700,xfx,:).
% listr_map([a,b,c],X). X = [1:a,2:b,3:c]
listr_map(List,Mapr) :- listr_map_aux(List,Mapr,1).
listr_map_aux([],[],_) :- !.
listr_map_aux([A|WL],[I:A | WMap1], I) :-
        I1 is I+1,!,
        listr_map_aux(WL,WMap1,I1).

%p171 delete1(X=[1,2,3]-2). X = [1,3]
delete1(X = [A|X]-A) :- !.
delete1([B|Y] = [B|X]-A) :- delete1(Y = X - A).

%p134
delete0(X = [A|X]-A).
delete0([B|Y] = [B|X]-A) :- delete0(Y = X - A).


    
%p193
:- op(700,xfx,[isq,isg]).
Z isg X*Y :-
      p(GX,X),p(GY,Y),GZ isq GX*GY,p(GZ,Z),!.

%p196
generate_e(N,E) :- gene_e_aux(E,N,[]).
gene_e_aux(L,0,L) :- !.
gene_e_aux(Const,N,L) :-
        N1 is N - 1,
        gene_e_aux(Const,N1,[N|L]).
        
%p165 chapter9 problem
my_maplist([],_,[]).
mt_maplist([L|Ls],F,[M|Ms]) :-
        X =.. [F,L,M],
        call(X),
        my_maplist(Ls,F,Ms).

double(X,Y) :- Y is 2*X.


%p148
Y isl subset([A|X]) :-
        memberd(A,Y),
        Y0 isl Y / A,
        Y0 isl subset(X).
Y isl subset([A|X]) :-
        Y isl subset(X).
[] isl subset([]).

%p153
power0(Power1,Set) :-
    bagof(X,(X isl subset(Set)),Power0),
    sort(Power0,Power),
    Power1 isl Power - [[],Set].

%p154
topology_c(U,V,O) :-
        (Z isl U+V,sort(Z,Zs), memberd(Za,O)),
        (Z1 isl U*V,sort(Z1,Z1s),memberd(Z1s,O)).

top_condition(O0,O) :-
        for_any(memberr([U,V],O0,2),
                topology_c(U,V,O)).

ptop(Set0) :-
        sort(Set0,Set),
        ctr_set(0,1),
        power0(Power,Set),
        O0 isl subset(Power),
        O isl [[]|O0] + [Set],
        top_condition(O0,O),
        write_count(O),
        fail.



%p194
writeln(P) :-
        write(P),nl.
write_count(O) :-
        ctr_inc(0,N),
        writeln(N = O).

for_any(P,Q) :-
        P,
        ifthenelse(Q,fail,(!,fail)).
for_any(P,Q).


%p195
smallbag(X,P,_) :-
        end_rr([]),
        call(P),
        begin_rr(A),
        small(X,A,A0),
        end_rr(A0),
        fail.
smallbag(_,_,List) :-
        begin_rr(List),!.

small(X,A,A0) :-
        ifthenelse(memberd(X,A),A0=A,A0=[X|A]).

begin_rr(A) :-
        recorded('0',A,Nref),erase(Nref).
end_rr(A) :-
        recorda('0',A,_).

/* generate(10,X) -> [1,2,3,4,5,6,7,8,9,10] */
generate_e(N,E) :-
        gene_e_aux(E,N,[]).
gene_e_aux(L,0,L) :- !.
gene_e_aux(Const,N,L) :-
        N1 is N-1,
        gene_e_aux(Const,N1,[N|l]).

/* arg_list(2,[1,2,3],M). M=2*/
arg_list(K,Y,M) :-
        PY =.. [prd|Y],arg(K,PY,M).

% inverse Z isq 1//[1,2,3]. Z = [1,2,3]
Z isq 1//X :-
        listr_map(X,Mapr),
        map_list3(Mapr,Z).
% devide 
Z isq X/Y :-
        !,Y1 isq 1//Y,Z isq X*Y1.

% power
E isq F^0 :- 
        length(F,N0),
        generate_e(N0,E),!.
F isq F^1 :- !.
G isq F^N :- 
        N>0,gc(full),
        powerq_aux([F,N,G],N,F),!.
G isq F^N :-
        N1 is -1*N,
        G1 isq F^N1,
        G isq 1//G1,
        powerq_aux([F,N,G],1,G).

powerq_aux([F,N,G],1,G).
powerq_aux(Const,WN,WG) :-
        Const = [F|_],
        WN1 is WN-1,
        write(WN1),
        tab(3),
        WG1 isq WG*F,
        powerq_aux(Const,WN1,WG1).

1 isq ord(E,E) :- !.
N isq ord(X,E) :-
        prder_aux([N,X,E],X,1).


%p171 map_list3([a:1,b:2],X). X = [a,b] 
map_list3(Map,List) :-
        length(Map,N),
        !,map_list3_aux(List,[],Map,N).
map_list3_aux(WM,WM,[],0) :- !.
map_list3_aux(Const,WM,WL,WN) :-
        WN1 is WN - 1,
        delete1(WL1 = WL - (Q:WN)),!,
        map_list3_aux(Const,[Q|WM],WL1,WN1).

%p165 map and function
:- op(700,xfx,ism).
% Y ism val([a:1,b:2,c:3], 2). Y = b 
Y ism val([],X) :- !.
Y ism val([Y:X |F],X) :- !.
Y ism val([A|F],X) :- !,Y ism val(F,X).
% Y ism set([a:1,b:2,c:3], [1,2]). Y = [a,b]
[] ism set(F,[]) :- !.
B ism set(F,[X|A0]) :- 
        Y ism val(F,X),!,
        B0 ism set(F,A0),
        small(Y,B0,B).

% C ism inv_set([a:1,b:2,c:3,d:2], [1,2,3], [a,b]). C = [1,2] 
[] ism inv_set(F,S,[]) :- !.
[] ism inv_set(F,[],A) :- !.
C ism inv_set(F,[X|S0],A) :-
        Y ism val(F,X),
        C0 ism inv_set(F,S0,A),!,
        ifthenelse(memberd(Y,A),small(X,C0,C),C=C0).

