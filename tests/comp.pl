% idea for new compiler opimizer

% test data
foo(X) :- write(1).
bar(X) :- write(X),bar(X).

analize(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),!,
    analize1(P,C1),
    fail.


analize1(P,C) :-
    deterministic(C,0),
    assert(pred_data(P,det)).
analize1(P,C) :-
    tail_recursive(C,0),
    assert(pred_data(P,tail)),!.


deterministic([],_).
deterministic([],0) :- fail.
deterministic([(Head :- Body)|Cs],_) :-
    det_body(Body),
    deterministic(Cs,1).

tail_recursive([],_).
tail_recursive([],0) :- fail.
tail_recursive([(Head :- Body)|Cs],_) :-
    tail_body(Head,Body),
    tail_recursive(Cs,1).


unidirectory(Head,Body) :-
    det_body(Body).

% deterministic body case !
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

det_builtin(write(_)).
det_builtin(write(_,_)).
det_builtin(true).
det_builtin(fail).
det_builtin((_<_)).
det_builtin((_>_)).

% about bodies 
/*
this is not deterministic
e.g.
how prove exclusive?
foo(X) :- X is 1.
foo(X) :- X is 2.
*/

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