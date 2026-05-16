% mode-inferencer

% mode(predicate,arity,modelist). e,g, mode(qsort,3,[+,-,+]).
foo(X,Y) :- true.

/*
    Simple mode inference prototype

    foo(X,Y) :- X is Y.

    =>
        mode(foo,[-,+])

    idea:

        Env = variable mode table

            var(X,unknown)
            var(Y,in)
            var(Z,out)

        body is scanned left-to-right
        built-in predicate modes update Env
        finally head arguments are converted to +/-

*/


/* =========================================
   entry
========================================= */

test(P) :-
    n_arity_count(P,L),
    test1(P,L).

test1(_,[]).

test1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    write('clause = '), write(C1), nl,
    infer_clause(C1,State,Env,Mode),write(Env),
    test1(P,Ls).


/* =========================================
   clause inference
========================================= */
infer_clause([],[],[],Mode).
infer_clause([C|Cs],State,[E1|Env],Mode) :-
    infer_a_clause(C,S1,E1,Mode),
    infer_clause(Cs,State,Env,Mode).


infer_a_clause((Head :- Body), State, [Env1|Env],Mode) :- 
    head_args(Head,Args),
    init_env(Args,Env0),
    infer_body(Body,Env0,Env1).

infer_a_clause(Head,State, Env, Mode) :-
    head_args(Head,Args),
    init_env(Args,Env0).


head_args(H,Args) :-
    H =.. [_|Args].



init_env([],[]).
init_env([X|Xs],[X|Es]) :-
    n_compiler_variable(X),
    init_env(Xs,Es).
init_env([_|Xs],Es) :-
    init_env(Xs,Es).



infer_body(true,Env,Env).
infer_body((A,B),Env0,Env2) :-
    infer_goal(A,Env0,Env1),
    infer_body(B,Env1,Env2).

infer_body(A,Env0,Env1) :-
    infer_goal(A,Env0,Env1).


infer_goal(X,Env0,Env0).


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



/* =========================================
   example
========================================= */

/*

foo(X,Y) :-
    X is Y.

?- test(foo).

clause = (foo(_A,_B):-_A is _B)
mode   = [-,+]

*/