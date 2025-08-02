% checker
/*
use_module(checker).
check_file(FileName).
*/
:- module(checker,[check_file/1,check_file/2]).

check_file(F,full) :-
    reconsult(F),
    (check;true).

check_file(F) :-
    reconsult(F),
    (check_without_single_clause;true).

check :-
    n_reconsult_predicate(P),
    check_arity(P),
    check_singleton(P),
    check_single_clause(P),
    fail.

check_without_single_clause :-
    n_reconsult_predicate(P),
    check_arity(P),
    check_singleton(P),
    fail.


check_arity(P) :-
    check_arity1(P),!.

check_singleton(P) :-
    check_singleton1(P),!.

check_single_clause(P) :-
    check_single_clause1(P),!.

check_singleton1(P) :-
    n_arity_count(P,L),
    check_singleton2(P,L).

check_singleton2(P,[]).
check_singleton2(P,[L|Ls]) :-
    n_clause_with_arity(P,L,C),
    n_variable_convert(C,C1),
    detect_singleton(C1),
    check_singleton2(P,Ls).
    
check_arity2(P,[]).
check_arity2(P,[L|Ls]) :-
    n_clause_with_arity(P,L,C),
    n_variable_convert(C,C1),
    detect_arity(C1),
    check_arity2(P,Ls).
    

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
    n_property(Head,userop), % ignore user operation
    detect_arity(Cs).
detect_arity([(Head :- Body)|Cs]) :-
    detect_body_arity(Head,Body),
    detect_arity(Cs).
detect_arity([C|Cs]) :-
    detect_arity(Cs).

detect_body_arity(Head,(X;Y)) :-
    detect_body_arity(Head,X),
    detect_body_arity(Head,Y).
detect_body_arity(Head,((X;Y),Z)) :-
    detect_body_arity(Head,X),
    detect_body_arity(Head,Y),
    detect_body_arity(Head,Z).
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
    functor(Head,P,_),
    (detect_clause_singleton(P,Head,Body);true),
    detect_singleton(Cs).
detect_singleton([X|Cs]) :-
    n_property(X,predicate),
    (detect_pred_singleton(X);true),
    detect_singleton(Cs).
detect_singleton((Head :- Body)) :-
    functor(Head,P,_),
    (detect_clause_singleton(P,Head,Body);true).
detect_singleton(X) :-
    n_property(X,operation).
detect_singleton(X) :-
    n_property(X,predicate),
    (detect_pred_singleton(X);true).

detect_pred_singleton(Pred) :-
    get_pred_variable(Pred,V1),!,
    single_variable(V1,Y),
    detect_clause_singleton1(Pred,Y),fail.

detect_clause_singleton(P,Head,Body) :-
    get_pred_variable(Head,V1),
    get_body_variable(Body,V2),
    append(V1,V2,V3),!,
    single_variable(V3,Y),
    detect_clause_singleton1(Head,Y),fail.

detect_clause_singleton1(P,Y) :-
    write('detect singleton '),write(Y),
    write(' in '),write(P),nl.

get_pred_variable(X,V) :-
    X =.. [_|A],
    get_pred_variable1(A,V).

get_pred_variable1([],[]).
get_pred_variable1([A|As],V3) :-
    list(A),
    flatten(A,A1),
    get_pred_variable1(A1,V1),
    get_pred_variable1(As,V2),
    append(V1,V2,V3),!.
get_pred_variable1([A|As],V3) :-
    compound(A),
    A =.. [_|A1],
    get_pred_variable1(A1,V1),
    get_pred_variable1(As,V2),
    append(V1,V2,V3),!.
get_pred_variable1([A|As],[A|V]) :-
    n_compiler_variable(A),
    not(n_compiler_anonymous(A)),
    get_pred_variable1(As,V),!.
get_pred_variable1([A|As],V) :-
    not(n_compiler_variable(A)),
    get_pred_variable1(As,V),!.
get_pred_variable1([A|As],V) :-
    n_compiler_anonymous(A),
    get_pred_variable1(As,V),!.

get_body_variable((X,Y),V) :-
    get_pred_variable(X,V1),
    get_body_variable(Y,V2),
    append(V1,V2,V),!.
get_body_variable(X,V) :-
    get_pred_variable(X,V),!.

single_variable(Xs, X) :-
    select(X, Xs, Rest),
    \+ n_compiler_anonymous(X),
    \+ member(X, Rest).

        
flatten([],[]).
flatten([L|Ls],[L,Ls]) :-
    atomic(L),
    atomic(Ls).
flatten([L|Ls],[L|Y]) :-
    atomic(L),
    flatten(Ls,Y).
flatten([L|Ls],[L|Y]) :-
    n_property(L,predicate),
    flatten(Ls,Y).
flatten([L|Ls],Z) :-
    list(L),
    flatten(L,Y1),
    flatten(Ls,Y2),
    append(Y1,Y2,Z).
            

check_single_clause1(P) :-
    n_arity_count(P,L),
    check_single_clause2(P,L).

check_single_clause2(P,[]).
check_single_clause2(P,[L|Ls]) :-
    n_clause_with_arity(P,L,C),
    n_variable_convert(C,C1),
    detect_single_clause3(C1).
    check_single_clause2(P,Ls).

detect_single_clause3(X) :-
    length(X,1),
    X = [(Head :- Body)],
    X = [Y],
    write('detect single clause '),write(Y),nl.
detect_single_clause3(X). 