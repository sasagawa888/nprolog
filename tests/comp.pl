% idea for new compiler opimizer

% test data
foo(X) :- write(1).
bar(X) :- write(X),bar(X).
boo(1).
boo(2).
uoo(a).
analize(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),!,
    analize1(P,C1),
    fail.


analize1(P,C) :-
    length(C,M),
    deterministic(C,0,0,M),
    assert(pred_data(P,det)).
analize1(P,C) :-
    length(C,M),
    tail_recursive(C,0,0,M),
    assert(pred_data(P,tail)),!.

% arguments = [clauses],det_count,pred_count,all_count
deterministic([],D,P,A) :-
    P =< 1,
    A =:= D+P.
deterministic([(Head :- Body)|Cs],D,P,A) :-
    det_body(Body),
    D1 is D+1,
    deterministic(Cs,D1,P,A).
deterministic([X|Cs],D,P,A) :-
    n_property(X,predicate),
    P1 is P+1,
    deterministic(Cs,D,P1,A).

% arguments = [clauses],tail_count,pred_count,all_count
tail_recursive([],T,P,A) :-
    P =< 1,
    T > 0,
    A =:= T+P.
tail_recursive([(Head :- Body)|Cs],T,P,A) :-
    tail_body(Head,Body),
    T1 is T+1,
    tail_recursive(Cs,T1,P,A).
tail_recursive([X|Cs],D,P,A) :-
    n_property(X,predicate),
    P1 is P+1,
    tail_recursive(Cs,D,P1,A).


% deterministic body case !
det((X;Y)) :- fail.
det_body(!).
det_body((X,!)).
det_body((X,(!,Y))) :-
    det_body(Y).
det_body(_).
% deterministic body case builtin
det_body1((X,Y)) :-
    det_builtin(X),
    det_body1(Y).
det_body1(X) :-
    det_buitlin(X).

% generaly builtin is deterministic. but some cases is non deterministic.
det_builtin(length(X,Y)) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),!,fail.

det_builtin(append(X,Y,_)) :-
    n_compiler_variable(X),
    n_compiler_variable(Y),!,fail.

det_builtin(X) :-
    n_property(X,builtin).



% tail recursive
tail_body(Head,Body) :-
    last_body(Body,Last),
    functor(Head,Pred1,Arity1),
    functor(Last,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2.

last_body((_,Body),Last) :-
    last_body(Body,Last).
last_body(Body,Body).

/*
 a,b,c ->  if(a==YES) if(b==YES) if(c==YES) return(Jexec_all(rest,Jget_sp(th),th));
*/
gen_det_body((X,Y)) :-
    gen_a_det_body(X),
    gen_det_body(Y).
gen_get_body(X) :-
    gen_a_det_body(X),
    write('return(Jexec_all(rest,Jget_sp(th),th));').

gen_a_det_body(X) :-
    X =.. [P|A],
    write('if (Jall('),
    gen_a_body(P),
    write(','),
    gen_a_argument(A),
    write(',th) == YES)').
