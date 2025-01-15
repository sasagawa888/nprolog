% N-Prolog can't resolve bignumber prime factorization

dt('∃xy〜(x)∧(y)').

encode(A,N) :- name(A,X),prime_list(P),code_godel(X,P,N). 

code_godel([],_,1).
code_godel([C|Cs],[P|Ps],N) :-
    uni_code(C,C1),
    N1 is P^C1,
    code_godel(Cs,Ps,N2),
    N is N1*N2.

decode(N,A) :-
    prime_factor(N,L),
    compress(L,L1),
    decode1(L1,A).

decode1([],A).
decode1([C|Cs],X) :-
    uni_code(C1,C),
    name(A1,[C1]),
    decode1(Cs,A),
    atom_concat(A1,A,X).

compress(List, Result) :-
    compress1(List, [], Result).


compress1([], [], []). 
compress1([], [N, _], [N]). 
compress1([X|Xs], [], R) :- 
    compress1(Xs, [1, X], R).
compress1([X|Xs], [N, X], R) :- 
    N1 is N + 1,
    compress1(Xs, [N1, X], R).
compress1([X|Xs], [N, Y], [N|R]) :- 
    X \= Y,
    compress1(Xs, [1, X], R).


prime_list([2,3,5,7,11,13,17,19,23,29,31]).
 %[〜,∧,\,∃,=,0,s,'(',')','"',x,y])
uni_code(12316,1).
uni_code(8743,2).
uni_code(92,3).
uni_code(8707,4).
uni_code(61,5).
uni_code(48,6).
uni_code(115,7).
uni_code(40,8).
uni_code(41,9).
uni_code(34,10).
uni_code(120,11).
uni_code(121,12).



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

prime_factor1(N,P,M,[]) :-
    N < 2.
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


