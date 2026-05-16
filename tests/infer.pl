% mode-inferencer

% test case
foo(X,Y) :- true.


test(P) :-
    n_arity_count(P,L),
    test1(P,L).

test1(_,[]).

test1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    write('clause = '), write(C1), nl,
    infer_clause(C1,State,Env,Mode),
    write('Env = '),write(Env),nl,
    test1(P,Ls).

infer_clause([],[],[],Mode).
infer_clause([C|Cs],State, Env ,Mode) :-
    infer_a_clause(C,S1,E1,Mode),
    infer_clause(Cs,State,E2,Mode),
    append(E1,E2,Env).


infer_a_clause((Head :- Body), State, Env1 ,Mode) :- 
    head_args(Head,Args),
    head_env(Args,Env0),
    infer_body(Body,Env0,Env1).

infer_a_clause(Head,State, Env, Mode) :-
    head_args(Head,Args),
    head_env(Args,Env0).


head_args(H,Args) :-
    H =.. [_|Args].


head_env([],[]).
head_env([X|Xs],[X|Es]) :-
    n_compiler_variable(X),
    head_env(Xs,Es).
head_env([_|Xs],Es) :-
    head_env(Xs,Es).


infer_body(true,Env,Env).
infer_body((A,B),Env0,Env2) :-
    infer_a_body(A,Env0,Env1),
    infer_body(B,Env1,Env2).
infer_body(A,Env0,Env1) :-
    infer_goal(A,Env0,Env1).


infer_a_body(X,Env0,Env0).


same_struct(X,Y) :-
    same_struct1(X,Y,0).
same_struct1([],[],N) :-
    N > 0.
same_struct1(X,Y,N) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    N > 0.
same_struct1(X,X,_) :-
    n_compiler_variable(X).
same_struct1([X|Xs],[X|Ys],N) :-
    n_compiler_variable(X),
    N1 is N + 1,
    same_struct1(Xs,Ys,N1).
same_struct1([X|Xs],[Y|Ys],N) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    same_struct1(Xs,Ys,N).


