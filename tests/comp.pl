
independ(Head) :-
    Head =.. [_|Args],
    flatten(Args,Args1),
    independ1(Args1).
    
independ1([]).
independ1([X|Xs]) :-
    n_compiler_variable(X),
    member(X,Xs),
    !,fail.
independ1([X|Xs]) :-
    n_compiler_variable(X),
    not(member(X,Xs)),
    independ1(Xs).
independ1([X|Xs]) :-
    independ1(Xs).
    
        
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
    
% clause as tail recursive
gen_a_pred5((Head :- Body),N) :-
    tail_body(Head,Body),
    Head =.. [P|Args],
    length(Args,L),
    pred_data(P,L,tail),
    write('save1 = Jget_wp(th);'),nl,
	gen_head(Head),
    gen_tail_body(Body,N).


    gen_tail_body((X,Y),N) :-
        gen_a_det_body(X),
        gen_tail_body(Y,N).
    gen_tail_body(X,N) :-
        X =.. [_|Args],
        write('{'),nl,
        gen_tail_args(Args,1),
        write('Jset_wp(save1,th);'),nl,
        write('Junbind(save2,th);'),nl,
        write('Jset_ac(save3,th);'),nl,
        write('goto loop'),write(N),write(';'),nl,
        write('}'),nl.
    