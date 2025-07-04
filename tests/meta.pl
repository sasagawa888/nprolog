% meta interpreter

resolve(true,Env,Cont) :- !.
resolve((P, Q),Env,Cont) :- !, resolve(P,Env,Cont), resolve(Q,Env,Cont).
resolve((P; Q),Env,Cont) :- !, resolve(P,Env,Cont) ; resolve(Q,Env,Cont).
% builtin
resolve(Goal,Env,Cont) :-
    predicate_property(Goal, built_in), !,
    deref(Goal,Gaol1,Env),
    call(Goal1),
    resolve(Cont, Env, true).    
% predicate
resolve(Head,Env,Cont) :-
    clause(Head, true),
    resolve(Cont,Env,true).
% clause
resolve(Head,Env,Cont) :-
    functor(Head, F, N),
    functor(Copy, F, N),
    clause(Copy, Body),
    unify(Head, Copy, Env, Env1),
    append_body(Body,Cont,Body1),
    resolve(Body1, Env1, Cont).


repl :- 
    repeat,
    nl,write(': ?- '),
    read(X),
    (X=halt -> (get(_),abort);true),
    (resolve(X,[],true) -> write(yes);write(no)),
    fail.

findvar(X,X,[]) :- !.
findvar(X,Y,[[X,Y]|_]) :- !.
findvar(X,Y,[L|Ls]) :-
    findvar(X,Y,Ls).

% prefix v is variable. e.g. vX vY
variable(X) :-  
    atom(X),
    atom_codes(X,[118|_]).

deref(X,Y,Env) :-
    variable(X),
    findvar(X,Y,Env).
deref(X,X,Env) :-
    atom(X).
deref(X,X,Env) :-
    atomic(X).
deref(X,Y,Env) :-
    list(X),
    deref1(X,Y,Env).
deref(X,Y,Env) :-
    compound(X),
    X =.. L,
    deref1(L,L1,Env),
    Y =.. L1.

% derefernece list
deref1([],[],Env).
deref1([X|Xs],[Y|Ys],Env) :-
    deref(X,Y,Env),
    deref1(Xs,Ys,Env).


unify(X,Y,Env,[[X,Y]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X,Env),
    findvar(Y,Y,Env).
unify(X,Y,Env,[[X,Y1]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X,Env),
    finvar(Y,Y1,Env).
unify(X,Y,Env,[[Y,X1]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X1,Env),
    findvar(Y,Y,Env).
unify(X,Y,Env,Env) :-
    variable(X),
    variable(Y),
    findvar(X,X1,Env),
    findvar(Y,Y1,Env),
    X1 == Y1.
unify(X,Y,Env,Env) :-
    atom(X),
    atom(Y),
    X == Y.
unify(X,Y,Env,Env) :-
    atomic(X),
    atomic(Y),
    X == Y.
unify(X,Y,Env,Env1) :-
    list(X),
    list(Y),
    unify1(X,Y,Env,Env1).
unify(X,Y,Env,Env) :-
    compound(X),
    compound(Y),
    deref(X,X1,Env),
    deref(Y,Y1,Env),
    X1 == Y1.

% unify list
unify1([X|Xs],[Y|Ys],Env,Env2) :-
    unify(X,Y,Env,Env1),
    unify1(Xs,Ys,Env1,Env2).


