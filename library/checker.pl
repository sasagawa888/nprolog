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
    fail.


check_arity(P) :-
    check_arity1(P),!.

check_singleton(P) :-
    check_singleton1(P),!.

check_singleton1(P) :-
    n_arity_count(P,L),
    check_singleton2(P,L).

check_singleton2(P,[]).
check_singleton2(P,[L|Ls]) :-
    n_clause_with_arity(P,L,C),
    n_variable_convert(C,C1),
    detect_singleton(C1).
    
check_arity2(P,[]).
check_arity2(P,[L|Ls]) :-
    n_clause_with_arity(P,L,C),
    n_variable_convert(C,C1),
    detect_arity(C1).
    

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
    detect_body_arity(Head,Body),
    detect_arity(Cs).
detect_arity([C|Cs]) :-
    detect_arity(Cs).

detect_body_arity(Head,(X,Y)) :-
    n_property(X,predicate),
    functor(X,P,N),
    n_arity_count(P,L),
    member(N,L),
    detect_body_arity(Head,Y).
detect_body_arity(Head,(X,Y)) :-
    n_property(X,builtin),
    functor(X,P,N),
    system(P/N),
    detect_body_arity(Head,Y).
detect_body_arity(Head,(X,Y)) :-
    write('detect arity '),write(X),
    write(' in '),write(Head),nl,
    detect_body_arity(Head,Y).
detect_body_arity(Head,X) :-
    n_property(X,predicate),
    functor(X,P,N),
    n_arity_count(P,L),
    member(N,L).
detect_body_arity(Head,X) :-
    n_property(X,builtin),
    functor(X,P,N),
    system(P/N).
detect_body_arity(Head,X) :-
    write('detect arity '),write(X),
    write(' in '),write(Head),nl.


detect_singleton([]).
detect_singleton([(Head :- Body)|Cs]) :-
    detect_singleton(Cs).
detect_singleton([X|Cs]) :-
    n_property(X,predicate),
    X =.. [P|A],
    detect_pred_singleton(P,A),
    detect_singleton(Cs).
detect_singleton(X) :-
    n_property(X,operation).
detect_singleton(X) :-
    n_property(X,predicate),
    X =.. [P|A],
    detect_pred_singleton(P,A).

detect_pred_singleton([]).
detect_pred_singleton(P,[A|As]) :-
    n_compiler_variable(A),
    write('detect singleton '),write(A),
    write(' in '),write(P),nl.