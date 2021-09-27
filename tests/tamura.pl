 /*
    from Mr. tamura's page (koube university)
 */
 
 %https://tamura70.gitlab.io/web-prolog/intro/nat.html
 
nat(0).
    nat(s(X)) :- nat(X).

plus(0, Y, Y).
    plus(s(X), Y, s(Z)) :- plus(X, Y, Z).

times(0, _, 0).
    times(s(X), Y, Z) :- times(X, Y, Z1), plus(Z1, Y, Z).

le(X, Y) :- plus(X, _, Y).

lt(X, Y) :- le(s(X), Y).

quot(X, Y, 0, X) :- lt(X, Y).
    quot(X, Y, s(Q), R) :- plus(Y, X1, X), quot(X1, Y, Q, R).

prime(s(X)) :- df(X, s(X)).

df(s(0), _).
    df(s(s(M)), N) :- dnd(s(s(M)), N), df(s(M), N).

dnd(M, N) :- quot(N, M, _, s(_)).

%?- nat(N), prime(N).
/*
?- [-'tests/tamura.pl'].
yes
?- nat(N),prime(N).
N = s(s(0)) ;
N = s(s(s(0))) ;
N = s(s(s(s(s(0))))) ;
N = s(s(s(s(s(s(s(0))))))) ;
N = s(s(s(s(s(s(s(s(s(s(s(0))))))))))) ;
N = s(s(s(s(s(s(s(s(s(s(s(s(s(0))))))))))))) ;
N = s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(0))))))))))))))))) ;
N = s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(s(0))))))))))))))))))) .
yes
?- 
*/

%https://tamura70.gitlab.io/web-prolog/intro/search.html

arc(a1, v1, v2).
arc(a2, v2, v3).
arc(a3, v3, v4).
arc(a4, v4, v1).
arc(a5, v3, v5).

walk(U, U).
    walk(U, V) :- arc(_, U, U1), walk(U1, V).

path(U, U, _, []).
    path(U, V, L, [A|P]) :-
        arc(A, U, U1),
        \+ member(U1, L),
        path(U1, V, [U1|L], P).

path_find(U, V, P) :- path(U, V, [U], P).

/*
?- [-'tests/tamura.pl'].
yes
?- path_find(v1, v5, P).
P = [a1,a2,a5] .
yes
?- 
*/

%https://tamura70.gitlab.io/web-prolog/intro/compile.html

%
%  簡単なコンパイラ
%
    
%
%  命令文のコンパイル
%
c(X = A) :-
    !,
    c_assign(X, A).
    
% 代入命令
c_assign(X, A) :-
    atom(X),
    !,
    c_exp(A),
    instr('ST', ['GR1',X]).
c_assign(_, _) :-
    write('代入命令の左辺は変数でなければならない'),
    fail.
    
%
%  式のコンパイル
%
c_exp(A) :-
    integer(A),
    !,
    instr('LEA', ['GR1',A]).
c_exp(A) :-
    atom(A),
    !,
    instr('LD', ['GR1',A]).
c_exp(A + B) :-
    !,
    c_exp(B),
    instr('PUSH', [0,'GR1']),
    c_exp(A),
    instr('ADD', ['GR1',0,'GR4']),
    instr('POP', ['GR0']).
    
%
%  CASL命令の表示
%
instr(Instr, Args) :-
    put(9),
    write(Instr),
    put(9),
    instr_args(Args),
    nl.
    
instr_args([]).
instr_args([A]) :-
    !,
    write(A).
instr_args([A|Args]) :-
    write(A),
    write(','),
    instr_args(Args).

/*
?- [-'tests/tamura.pl'].
yes
?- c(a = x + y + 123).
        LEA     GR1,123
        PUSH    0,GR1
        LD      GR1,y
        PUSH    0,GR1
        LD      GR1,x
        ADD     GR1,0,GR4
        POP     GR0
        ADD     GR1,0,GR4
        POP     GR0
        ST      GR1,a
yes
?-     
*/