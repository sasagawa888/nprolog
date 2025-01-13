

dt('∃xy〜(x)∧(y)').

encode(X,N) :- name(X,Y).

atom_to_code(A,X) :- name(A,X),code_list(Y),atom_to_code1(X,Y,L). 

code_list([]).
 %[〜,∧,\,∃,=,0,s,'(',')','"',x,y])
prime_list([2,3,5,7,11,13,17,19,23]).



prime_factor(N,[]) :-
    N < 2.
prime_factor(N,[2|L]) :-
    X is N mod 2,
    X == 0,
    N1 is N // 2,
    M is sqrt(N),
    prime_factor(N1,L).
prime_factor(N,L) :-
    M is sqrt(N),
    prime_factor1(N,3,M,L).

prime_factor1(N,P,M,[N]) :-
    P > M.
prime_factor1(N,P,M,[P|L]) :-
    X is N mod P,
    X == 0,
    N1 is N // P,
    P1 is P+2,
    prime_factor1(N1,P1,M,L).
prime_factor1(N,P,M,L) :-
    P1 is P+2,
    prime_factor1(N,P1,M,L).


