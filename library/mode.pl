% mode-inferencer

:- module(mode,[infer/1,mode/3]).
:- use_module(list).

mode(dummy,0,[]).
flag(dummy).

mode_system(write,1,[+]).
%-----------------------------
infer(File) :-
    infer1(File),
    infer2.

infer1(File) :-
    write('inference1'),nl,
    abolish(mode/3),
    assert(mode(dummy,0,[])),
    reconsult(File),
    mode_inference.

infer2 :-
    write('inference2'),nl,
    mode_inference.

mode_inference :-
    n_reconsult_predicate(P),
    predicate_inference(P),
    fail.
mode_inference.

test(P) :- 
    predicate_inference(P).

predicate_inference(P) :- mode(P,_,_),!.
predicate_inference(P) :-
    n_arity_count(P,L),
    predicate_inference1(P,L).

predicate_inference1(_,[]) :- !.
predicate_inference1(P,[N|Ls]) :-
    n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    abolish(flag/1),
    assert(flag(dummy)),
    infer_clause(P,C1,State,_),
    gen_mode(P,N,State),!,
    predicate_inference1(P,Ls).

gen_mode(_,_,_) :- flag(incomplete).
gen_mode(P,N,State) :-
    infer_mode(State,Mode),
    mode_pick(Mode,A,B),
    complete_mode(A),
    complete_mode(B),
    assert(mode(P,N,A)),
    ifthenelse(
        A == B,
        true,
        assert(mode(P,N,B))).

complete_mode([]).
complete_mode([+|Ls]) :-
    complete_mode(Ls).
complete_mode([-|Ls]) :-
    complete_mode(Ls).

mode_pick(S, M1, M2) :-
    pick_cols(S, Pairs),
    split_pairs(Pairs, M1, M2).

pick_cols([[]|_], []) :- !.
pick_cols(S, [P|Ps]) :-
    pick_col(S, P, Rest),
    pick_cols(Rest, Ps).

pick_col([], ?, []).
pick_col([[X|Xs]|Rows], P, [Xs|Rest]) :-
    pick_col(Rows, P0, Rest),
    pick_pair(X, P0, P).

pick_pair(?, P, P) :- !.
pick_pair(['-','-'],['+','-']).
pick_pair(['-','-'],['-','+']).
pick_pair(X, _, X).

split_pairs([], [], []).
split_pairs(['?'|Xs], ['?'|As], ['?'|Bs]) :-
    split_pairs(Xs, As, Bs).
split_pairs([[A,B]|Xs], [A|As], [B|Bs]) :-
    split_pairs(Xs, As, Bs).

infer_mode([],[]).
infer_mode([S|Ss], [M1|M2]) :-
    infer_mode1(1, S, M1),!,
    infer_mode(Ss,M2).

infer_mode1(N, State, [M|Ms]) :-
    connect_arg(N, State, Arg),!,
    infer_arg_mode(N, Arg, State, M),
    N1 is N + 1,
    infer_mode1(N1, State, Ms).
infer_mode1(_, _, []).

connect_arg(N, [c(N,Arg)|_], Arg) :- !.
connect_arg(N, [_|Xs], Arg) :-
    connect_arg(N, Xs, Arg).

infer_arg_mode(N,_,State,['+','+']) :-
    member(a(N,'+'),State),!.
infer_arg_mode(N,_,State,['-','-']) :-
    member(a(N,'-'),State),!.
infer_arg_mode(N,_,State,['+','-']) :-
    member(e(N,_),State),!.
infer_arg_mode(N,_,State,['-','+']) :-
    member(e(_,N),State),!.    
infer_arg_mode(_, Arg, State, ['+','+']) :-
    n_compiler_variable(Arg),
    member(s(Arg,'+'), State),!.
infer_arg_mode(_, Arg, State, ['-','-']) :-
    n_compiler_variable(Arg),
    member(s(Arg,'-'), State),!.
infer_arg_mode(N,[X|Xs], State, M) :- !,
    infer_arg_mode(N,X, State, M1),
    infer_arg_mode(N,Xs, State, M2),
    same_mode(M1, M2, M).
infer_arg_mode(_, _, _, '?').

same_mode(['+','+'], ['+','+'], ['+','+']).
same_mode(['-','-'], ['-','-'], ['-','-']).
same_mode(_, _, ?).

has_input_var(Term, State) :-
    n_compiler_variable(Term),!,
    member(s(Term,+), State).

infer_clause(_,[],[],[]).
infer_clause(P,[C|Cs],[S1|S2],[E1|E2]) :-
    infer_a_clause(P,C,S1,E1),
    infer_clause(P,Cs,S2,E2).


infer_a_clause(P,(Head :- Body), State2, Env2) :- 
    term_variables(Head,Env0),
    Head =.. [_|Args],
    infer_head(P,Args,[],Env0,State1,Env1),
    infer_body(P,Body,State1,Env1,State2,Env2).

infer_a_clause(P,Head, State1, Env1) :-
    term_variables(Head,Env0),
    Head =.. [_|Args],
    infer_head(P,Args,[],Env0,State1,Env1).


%infer_head(Pred,Args,State,Env,State,Env).
infer_head(_,Args,State,Env,State2,Env3) :-
    connect_head(Args,State,Env,State1,Env1),
    exclusive_head(Args,State1,Env1,State2,Env2,1),
    term_variables(Args,Argvars),
    append(Argvars,Env2,Env3).

connect_head(Args,State,Env,State1,Env1) :-
    connect_head1(Args,State,Env,State1,Env1,1).

connect_head1([],State,Env,State,Env,_).
connect_head1([A|As],State,Env,State1,Env1,N) :-
    State2 = [c(N,A)|State],
    N1 is N+1,
    connect_head1(As,State2,Env,State1,Env1,N1).

exclusive_head([_],State,Env,State,Env,_).
exclusive_head([A|As],State,Env,State2,Env2,N) :-
    N1 is N+1,
    exclusive_head1(A,As,State,Env,State1,Env1,N,N1),
    exclusive_head(As,State1,Env1,State2,Env2,N1).

exclusive_head1(_,[],State,Env,State,Env,_,_).
exclusive_head1(A,[B|Bs],State,Env,State1,Env,N,M) :-
    same_struct(A,B),!,
    State2 = [e(N,M)|State],
    M1 is M+1,
    exclusive_head1(A,Bs,State2,Env,State1,Env,N,M1).
exclusive_head1(A,[_|Bs],State,Env,State1,Env,N,M) :-
    M1 is M+1,
    exclusive_head1(A,Bs,State,Env,State1,Env,N,M1).



infer_body(_,end,State,Env,State,Env) :- !.
infer_body(P,(A,B),State,Env,States,Envs) :-
    infer_a_body(P,A,State,Env,State1,Env1),
    infer_body(P,B,State1,Env1,States,Envs).
infer_body(P,A,State,Env,State1,Env1) :-  
    infer_a_body(P,A,State,Env,State1,Env1),
    infer_body(P,end,State1,Env1,State1,Env1).

gen_isright([],[]).
gen_isright([V|Vs],[s(V,'+')|Ss]) :-
    gen_isright(Vs,Ss).

infer_a_body(_,(X is Y),State,Env,State2,Env1) :-
    term_variables(Y,Vars),
    gen_isright(Vars,State1),
    append(State1,[s(X,'-')|State],State2),
    append(Vars,[X|Env],Env1).
infer_a_body(_,(X > Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(_,(X < Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(_,(X >= Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(_,(X =< Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(_,(X =:= Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(_,(X =\= Y),State,Env,[s(X,'+'),s(Y,'+')|State],Env).
infer_a_body(P,X,State,Env,State,Env) :-
    n_property(X,predicate),
    functor(X,P1,N),
    P1 \= P,
    not(mode(P1,N,_)),
    assert(flag(incomplete)).
infer_a_body(P,X,State,Env,State4,Env1) :-
    n_property(X,predicate),
    functor(X,P1,N),
    P1 \= P,
    mode(P1,N,Mode),
    term_variables(X,Vars),
    free_variables(Vars,Env,Free),
    append(Free,Env,Env1),
    gen_free_state_other(Free,State1),
    append(State1,State,State2),
    gen_match(Vars,State2,Match),!,
    apply_match(Match,Mode,State3),
    append(State3,State2,State4).

infer_a_body(P,X,State,Env,State3,Env1) :-
    n_property(X,predicate),
    functor(X,P1,_),
    P1 = P,
    term_variables(X,Vars),
    free_variables(Vars,Env,Free),
    append(Free,Env,Env1),
    gen_free_state_self(Free,Vars,State1),
    append(State1,State,State2),   
    X =.. [_|Args],
    gen_output_arg(Args,State2,State3,1).

infer_a_body(_,X,State,Env,State4,Env1) :-
    n_property(X,builtin),
    functor(X,P1,N),
    mode_system(P1,N,Mode),
    term_variables(X,Vars),
    free_variables(Vars,Env,Free),
    append(Free,Env,Env1),
    gen_free_state_other(Free,State1),
    append(State1,State,State2),
    gen_match(Vars,State2,Match),!,
    apply_match(Match,Mode,State3),
    append(State3,State2,State4).

infer_a_body(_,_,State,Env,State,Env).

% only X is structure 
output_arg(X, _) :-
    n_compiler_variable(X), !, fail.
output_arg([], _) :- !, fail.
output_arg([X|Xs], State) :-
    contains_output_var(X, State), ! ;
    contains_output_var(Xs, State), !.

contains_output_var(X, State) :-
    n_compiler_variable(X),
    member(s(X,'-'), State), !.
contains_output_var([], _) :- !, fail.
contains_output_var([X|Xs], State) :-
    contains_output_var(X, State), ! ;
    contains_output_var(Xs, State), !.


gen_output_arg([],State,State,_).
gen_output_arg([A|As],State,State1,N) :-
    output_arg(A,State),
    State2 = [a(N,'+')|State],
    N1 is N+1,
    gen_output_arg(As,State2,State1,N1).
gen_output_arg([_|As],State,State1,N) :-
    N1 is N+1,
    gen_output_arg(As,State,State1,N1).


free_variables([],_,[]).
free_variables([V|Vs],Env,Fs) :-
    member(V,Env),
    free_variables(Vs,Env,Fs).
free_variables([V|Vs],Env,[V|Fs]) :-
    free_variables(Vs,Env,Fs).

%analize self predicate
gen_free_state_self([],_,[]).
gen_free_state_self([V|Vs],Vars,[a(N,'-'),s(V,'-')|Fs]) :-
    nth_var(V,Vars,N),
    gen_free_state_self(Vs,Vars,Fs).

%analize other predicate
gen_free_state_other([],[]).
gen_free_state_other([V|Vs],[s(V,'-')|Fs]) :-
    gen_free_state_other(Vs,Fs).


nth_var(F,[F|_],1).
nth_var(F,[_|Vs],N) :-
    nth_var(F,Vs,N1),
    N is N1+1.

gen_match([],_,[]).
gen_match([V|Vs],State,[X|Rs]) :-
    member(s(V,X),State),
    gen_match(Vs,State,Rs).
gen_match([V|Vs],State,[V|Rs]) :-
    gen_match(Vs,State,Rs).

apply_match([],[],[]).
apply_match([V|Vs],[M|Ms],[s(V,M)|Ss]) :-
    n_compiler_variable(V),
    apply_match(Vs,Ms,Ss).
apply_match([X|Vs],[X|Ms],Ss) :-
    apply_match(Vs,Ms,Ss).

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


term_variables(Term, Vars) :-
    term_variables(Term, [], Rev),
    reverse(Rev, Vars).

term_variables(X, Vars, Vars) :-
    atomic(X),
    \+ n_compiler_variable(X), !.

term_variables(X, Vars, Vars) :-
    member_eq(X, Vars), !.

term_variables(X, Vars, [X|Vars]) :-
    n_compiler_variable(X), !.

term_variables(Term, Vars0, Vars) :-
    list(Term),
    term_variables_list(Term, Vars0, Vars).

term_variables(Term, Vars0, Vars) :-
    Term =.. [_|Args],
    term_variables_list(Args, Vars0, Vars).

term_variables_list([], Vars, Vars).


term_variables_list([X|Xs], Vars0, Vars) :-
    list(X),
    term_variables_list(X, Vars0, Vars1),
    term_variables_list(Xs, Vars1, Vars).

term_variables_list([X|Y], Vars0, Vars) :-
    atom(Y),
    term_variables(X, Vars0, Vars1),
    term_variables(Y, Vars1, Vars).

term_variables_list([X|Xs], Vars0, Vars) :-
    term_variables(X, Vars0, Vars1),
    term_variables_list(Xs, Vars1, Vars).


member_eq(X,[Y|_]) :-
    X == Y, !.
member_eq(X,[_|Ys]) :-
    member_eq(X,Ys).
