independ(Head) :-
    Head =.. [_|A],
    independ1(A).


independ1([X|Xs]) :-
    list(X),
    flatten(Xs,F),
    not(independ2(X,F)),!,fail.
independ1([X|Xs]) :-
    list(X),
    flatten(Xs,F),
    independ2(X,F),
    independ1(Xs).
independ1([X|Xs]) :-
    independ1(Xs).
independ1(X).        

independ2([],F).
independ2([X|Xs],F) :-
    n_compiler_variable(X),
    write(X), write(F),
    member(X,F),
    !,fail.
independ2([X|Xs],F) :-
    independ2(Xs,F).
independ2(X,F) :-
    n_compiler_variable(X),
    member(X,F),
    !,fail.
independ2(X,F) :-
    atomic(X).
        
            
flatten([],[]).
flatten([L|Ls],[L,Ls]) :-
    atomic(L),
    atomic(Ls).
flatten([L|Ls],[L|Y]) :-
    atomic(L),
    flatten(Ls,Y).
flatten([L|Ls],Z) :-
    list(L),
    flatten(L,Y1),
    flatten(Ls,Y2),
    append(Y1,Y2,Z).
        

