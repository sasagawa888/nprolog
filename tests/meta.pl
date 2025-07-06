/* meta interpreter
*  by kenichi sasagawa
*  Env is assoc list e.g. [[vX,2],[vY,3]...]
*  Cont is continuation conjunction.
*  [-'./tests/meta']  -? prolog. change prompt to ?>
*/

%test case
fact(0,1).
fact(vN,vX) :-
    vN1 is vN-1,
    fact(vN1,vX1),
    vX is vN*vX1.

resolve(true,Env,Cont,N) :- !.
resolve((P, Q),Env,Cont,N) :- 
    deref(P,P1,Env),
    write(P1),write(in),write(Env),get(_),nl,
    connect(Q,Cont,Cont1),
    N1 is N+1,
    resolve(P1,Env,Cont1,N1).
resolve((P; Q),Env,Cont,N) :- 
    deref(P,P1,Env),
    deref(Q,Q1,Env),
    !, resolve(P1,Env,Cont,N) ; resolve(Q1,Env,Cont,N).

% is builtin
resolve(Goal,Env,Cont,N) :-
    functor(Goal,is,2), 
    arg(1,Goal,X),
    arg(2,Goal,Y),
    eval(Y,Y1,Env),
    unify(X,Y1,Env,Env1),
    N1 is N+1,
    resolve(Cont, Env1, [],N1),!.
% other builtin
resolve(Goal,Env,Cont,N) :-
    predicate_property(Goal, built_in), !,
    deref(Goal,Goal1,Env),
    call(Goal1),
    N1 is N+1,
    resolve(Cont, Env, [],N1),!.    
% predicate
resolve(Head,Env,Cont,N) :-
    clause(Head, true),
    N1 is N+1,
    resolve(Cont,Env,[],N1),!.

% clause
resolve(Head,Env,Cont,N) :-
    functor(Head, F, A), 
    functor(Copy, F, A), 
    clause(Copy, Body), 
    alpha_rename(Head,Head1,N),
    alpha_rename(Copy,Copy1,N),
    alpha_rename(Body,Body1,N),
    unify(Head1, Copy1, Env, Env1),
    Body = true, %Copy is base
    N1 is N+1,
    resolve(Cont, Env1, [],N1),!.

resolve(Head,Env,Cont,N) :-
    functor(Head, F, A), 
    functor(Copy, F, A), 
    clause(Copy, Body), 
    alpha_rename(Head,Head1,N),
    alpha_rename(Copy,Copy1,N),
    alpha_rename(Body,Body1,N),
    unify(Head1, Copy1, Env, Env1),
    connect(Body1,Cont,Body2),
    N1 is N+1,
    resolve(Body2, Env1, [],N1),!.

prolog :- 
    repeat,
    nl,write('?> '),
    read(X),
    (X=halt -> (get(_),abort);true),
    (resolve(X,[],true,0) -> write(yes);write(no)),
    fail.

findvar(X,X,Env) :-
    findvar1(X,Y,Env),
    X == Y.
findvar(X,Z,Env) :-
    findvar1(X,Y,Env),
    variable(Y),
    findvar(Y,Z,Env),!.
findvar(X,Y,Env) :-
    findvar1(X,Y,Env),
    not(variable(Y)),!.


findvar1(X,X,[]) :- !.
findvar1(X,Y,[[X,Y]|_]) :- !.
findvar1(X,Y,[L|Ls]) :-
    findvar1(X,Y,Ls).

% prefix v is variable. e.g. vX, vY
variable(X) :-  
    atom(X),
    atom_codes(X,[118|_]).

% dereference
deref(X,Y,Env) :-
    variable(X),
    findvar(X,Y,Env).
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

% dereference list
deref1([],[],Env).
deref1([X|Xs],[Y|Ys],Env) :-
    deref(X,Y,Env),
    deref1(Xs,Ys,Env).

% unify X and Y in Env(arg3) return new env(arg4)
unify(X,Y,Env,[[X,Y]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X1,Env),
    findvar(Y,Y1,Env),
    variable(X1),
    variable(Y1).
unify(X,Y,Env,[[X,Y1]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X1,Env),
    findvar(Y,Y1,Env),
    variable(X1),
    not(variable(Y1)).
unify(X,Y,Env,[[Y,X1]|Env]) :-
    variable(X),
    variable(Y),
    findvar(X,X1,Env),
    findvar(Y,Y1,Env),
    not(variable(X1)),
    variable(Y1).
unify(X,Y,Env,Env) :-
    variable(X),
    variable(Y),
    findvar(X,X1,Env),
    findvar(Y,Y1,Env),
    X1 == Y1.
unify(X,Y,Env,[[X,Y]|Env]) :-
    variable(X),
    not(variable(Y)),
    findvar(X,X1,Env),
    variable(X1).
unify(X,Y,Env,[[Y,X]|Env]) :-
    not(variable(X)),
    variable(Y),
    findvar(Y,Y1,Env),
    variable(Y1).
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

% evaluate X in Env
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

% connect conjunction
connect(A,[],A).
connect((A,B),C,(A,Z)) :-
    connect(B,C,Z).
connect(A,B,(A,B)).

%  e.g. vX -> vX0
uniqulify(V,V1,N) :-
    atom_codes(V,L),
    number_codes(N,L1),
    append(L,L1,L2),
    atom_codes(V1,L2).

% alpha convert term
alpha_rename(X,Y,N) :-
    variable(X),
    uniqulify(X,Y,N).
alpha_rename(X,X,N) :-
    atomic(X).
alpha_rename(X,Y,N) :-
    list(X),
    alpha_rename1(X,Y,N).
alpha_rename(X,Y,N) :-
    compound(X),
    X =.. L,
    alpha_rename1(L,L1,N),
    Y =.. L1.

% rename list
alpha_rename1([],[],N).
alpha_rename1([X|Xs],[Y|Ys],N) :-
    alpha_rename(X,Y,N),
    alpha_rename1(Xs,Ys,N).
