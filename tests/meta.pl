% meta interpreter

resolve(true,Env,Cont) :- !.
resolve((P, Q),Env,Cont) :- !, resolve(P,Env,Cont), resolve(Q,Env,Cont).
resolve((P; Q),Env,Cont) :- !, resolve(P,Env,Cont) ; resolve(Q,Env,Cont).
% builtin
resolve(Goal,Env,Cont) :-
    predicate_property(Goal, built_in), !,
    call(Goal).    
% predicate
resolve(Head,Env,Cont) :-
    functor(Head, F, N),
    functor(Copy, F, N),
    clause(Copy, true).
% clause
resolve(Head,Env,Cont) :-
    functor(Head, F, N),
    functor(Copy, F, N),
    clause(Copy, Body),
    unify(Head, Copy, Env),
    resolve(Body, Env, Cont).


repl :- 
    repeat,
    nl,write(': ?- '),
    read(X),
    (X=halt -> (get(_),abort);true),
    (resolve(X,[],[]) -> write(yes);write(no)),
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


unify(X,Y,[[X,Y]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X),
    findvar(Y,Y).
unify(X,Y,[[X,Y1]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X),
    finvar(Y,Y1).
unify(X,Y,[[Y,X1]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X1),
    findvar(Y,Y).
unify(X,Y,Env) :-
    variable(X),
    variable(Y),
    findvar(X,X1),
    findvar(Y,Y1),
    X1 == Y1.
unify(X,Y,Env) :-
    atom(X),
    atom(Y),
    X == Y.
unify(X,Y,Env) :-
    atomic(X),
    atomic(Y),
    X == Y.
unify(X,Y,Env) :-
    list(X),
    list(Y),
    unify1(X,Y,Env).
unify(X,Y,Env) :-
    compound(X),
    compound(Y),
    deref(X,X1,Env),
    deref(Y,Y1,Env),
    X1 == Y1.

% unify list
unify1([X|Xs],[Y|Ys],Env) :-
    unify(X,Y,Env),
    unify1(Xs,Ys,Env).


