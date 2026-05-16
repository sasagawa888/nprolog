% mode-inferencer

% test case
foo(X,Y) :- Z is Y,true,X is Z,X > Z.


test(P) :-
    n_arity_count(P,L),
    test1(P,L).

test1(_,[]).

test1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    write('clause = '), write(C1), nl,
    infer_clause(C1,State,Env),
    write('State = '),write(State),nl,
    write('Env = '),write(Env),nl,
    test1(P,Ls).

infer_clause([],[],[]).
infer_clause([C|Cs],State, Env) :-
    infer_a_clause(C,S1,E1),
    infer_clause(Cs,S2,E2),
    append(S1,S2,State),
    append(E1,E2,Env).


infer_a_clause((Head :- Body), State1, Env1) :- 
    head_args(Head,Args),
    head_env(Args,Env0),
    infer_body(Body,[],Env0,State1,Env1).

infer_a_clause(Head, State1, Env1) :-
    head_args(Head,Args),
    head_env(Args,Env0),
    infer_head(Head,[],Env0,State1,Env1).


head_args(H,Args) :-
    H =.. [_|Args].


head_env([],[]).
head_env([X|Xs],[X|Es]) :-
    n_compiler_variable(X),
    head_env(Xs,Es).
head_env([_|Xs],Es) :-
    head_env(Xs,Es).


infer_body(end,State,Env,State,Env).
infer_body((A,B),State,Env,States,Envs) :-
    infer_a_body(A,State,Env,State1,Env1),
    infer_body(B,State1,Env1,States,Envs).
infer_body(A,State,Env,State1,Env1) :- 
    infer_a_body(A,State,Env,State1,Env1),
    infer_body(end,State1,Env1,State1,Env1).


infer_a_body((X is Y),State,Env,[s(X,out),s(Y,in)|State],Env).
infer_a_body((X > Y),State,Env,[s(X,in),s(Y,in)|State],Env).
infer_a_body(true,State,Env,State,Env).

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


