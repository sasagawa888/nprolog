% checker
/*
use_module(checker).
check_file(FileName).
*/
:- module(checker,[check_file/1]).

check_file(F) :-
    reconsult(F),
    check.


check :-
    n_reconsult_predicate(P),
    check_arity(P),
    check_singleton(P),
    check_callable(P),
    fail.


check_arity(P) :-
    write('--- arity check ---'),
    write(P),nl,
    check_arity1(P),!.

check_singleton(P) :-
    write('--- singleton check ---'),
    write(P),nl.

check_callable(P) :-
    write('--- callable check ---'),
    write(P),nl.


check_arity1(P) :-
    n_arity_count(P,L),
    check_arity2(P,L).

check_arity2(P,[]).
check_arity2(P,[L|Ls]) :-
    n_clause_with_arity(P,L,C),
    n_variable_convert(C,C1),
    detect_arity(C1).

detect_arity([]).
detect_arity([(Head :- Body)|Cs]) :-
    detect_body_arity(Body),
    detect_arity(Cs).
detect_arity([C|Cs]) :-
    detect_arity(Cs).

detect_body_arity((X,Y)) :-
    n_property(X,predicate),
    functor(X,P,N),
    n_arity_count(P,L),
    member(N,L),
    detect_body_arity(Y).
detect_body_arity((X,Y)) :-
    n_property(X,builtin),
    functor(X,P,N),
    system(P/N),
    detect_body_arity(Y).
detect_body_arity((X,Y)) :-
    write('detect '),write(X),nl,
    detect_body_arity(Y).
detect_body_arity(X) :-
    n_property(X,predicate),
    functor(X,P,N),
    n_arity_count(P,L),
    member(N,L).
detect_body_arity(X) :-
    n_property(X,builtin),
    functor(X,P,N),
    system(P/N).
detect_body_arity(X) :-
    write('detect '),write(X),nl.