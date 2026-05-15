% mode-inferencer

% mode(predicate,arity,modelist). e,g, mode(qsort,3,[+,-,+]).

test(P) :-
    n_arity_count(P,L),
    test1(P,L).

test1(P,[]).
test1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,X),
    infer(X,[],R).

infer([],R).
infer([T|Ts],[R|Rs]) :-
    infer1(T,[],[],R),
    infer(Ts,Rs). 



same_struct(X,Y) :-
    same_struct1(X,Y,0).
same_struct1([],[],N) :-
    N > 0.
same_struct1(X,Y,N) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    N > 0.
same_struct1(X,X,N) :-
    n_compiler_variable(X).
same_struct1([X|Xs],[X|Ys],N) :-
    n_compiler_variable(X),
    N1 is N+1,
    same_struct1(Xs,Ys,N1).
same_struct1([X|Xs],[Y|Ys],N) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),
    same_struct1(Xs,Ys,N).


get_var(X,V) :-
    X =.. [_|X1],
    get_var1(X1,V).
get_var1([],[]).
get_var1([V|Ls],[V|Vs]) :-
    n_compiler_variable(V),
    get_var1(Ls,Vs).
get_var1([L|Ls],Vs) :-
    atomic(L),
    get_var1(Ls,Vs).
