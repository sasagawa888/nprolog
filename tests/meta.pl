% meta interpreter

resolve(true,Env,Cont) :- !.
resolve((P, Q),Env,Cont) :- 
    connect(Q,Cont,Cont1),
    resolve(P,Env,Cont1).
resolve((P; Q),Env,Cont) :- 
    !, resolve(P,Env,Cont) ; resolve(Q,Env,Cont).

% is builtin
resolve(Goal,Env,Cont) :-
    functor(Goal,is,2), 
    arg(1,Goal,X),
    arg(2,Goal,Y),
    eval(Y,Y1,Env),
    unify(X,Y1,Env,Env1),
    resolve(Cont, Env1, true).
% other builtin
resolve(Goal,Env,Cont) :-
    predicate_property(Goal, built_in), !,
    deref(Goal,Goal1,Env), 
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
    connect(Body,Cont,Body1),
    resolve(Body1, Env1, true).

prolog :- 
    repeat,
    nl,write('?> '),
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
unify(X,Y,Env,[[X,Y]|Env]) :-
    variable(X),
    not(variable(Y)),
    findvar(X,X,Env).
unify(X,Y,Env,[[Y,X]|Env]) :-
    not(variable(X)),
    variable(Y),
    findvar(Y,Y,Env).
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
unify(X,Y,Env,Env1) :-
    compound(X),
    compound(Y),
    X =.. X1,
    Y =.. Y1,
    unify1(X1,Y1,Env,Env1).

% unify list
unify1([],[],Env,Env).
unify1([X|Xs],[Y|Ys],Env,Env2) :-
    unify(X,Y,Env,Env1),
    unify1(Xs,Ys,Env1,Env2).


eval(X,X,Env) :-
    number(X).
eval(X,X1,Env) :-
    variable(X),
    findvar(X,X1,Env).
eval(X,Y,Env) :-
    functor(X,'+',2),
    arg(1,X,X1),
    arg(2,X,X2),
    eval(X1,X3,Env),
    eval(X2,X4,Env),
    Y is X3+X4.
eval(X,Y,Env) :-
    functor(X,'-',2),
    arg(1,X,X1),
    arg(2,X,X2),
    eval(X1,X3,Env),
    eval(X2,X4,Env),
    Y is X3-X4.
eval(X,Y,Env) :-
    functor(X,'*',2),
    arg(1,X,X1),
    arg(2,X,X2),
    eval(X1,X3,Env),
    eval(X2,X4,Env),
    Y is X3*X4.
eval(X,Y,Env) :-
    functor(X,'/',2),
    arg(1,X,X1),
    arg(2,X,X2),
    eval(X1,X3,Env),
    eval(X2,X4,Env),
    Y is X3/X4.

connect((A,B),C,(A,Z)) :-
    connect(B,C,Z).
connect(A,B,(A,B)).