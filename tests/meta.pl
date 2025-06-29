% meta interpreter

resolve(true,Env,Cont) :- !.
resolve((P, Q),Env,Cont) :- !, resolve(P,Env,Cont), resolve(Q,Env,Cont).
resolve((P; Q),Env,Cont) :- !, resolve(P,Env,Cont) ; resolve(Q,Env,Cont).
resolve(Goal,Env,Cont) :-
    predicate_property(Goal, built_in), !,
    call(Goal).    
resolve(Head,Env,Cont) :-
    functor(Head, F, N),
    functor(Copy, F, N),
    clause(Copy, Body),
    =(Head, Copy),
    resolve(Body,Env_Cont).


repl :- 
    repeat,
    nl,write(': ?- '),
    read(X),
    (X=halt -> (get(_),abort);true),
    (resolve(X,[],[]) -> write(yes);write(no)),
    fail.
