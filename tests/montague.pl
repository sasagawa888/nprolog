:- use_module(dcg).


sentence(Sem) -->
    noun_phrase(NP),
    verb_phrase(VP),
    { Sem = [NP, VP] }.

% every man → l(P, forall(X, implies(man(X), [P, X])))
noun_phrase(l(P, forall(X, implies(man(X), [P, X])))) -->
    [every, man].

% loves Mary → l(X, loves(X, mary))
verb_phrase(l(X, loves(X, mary))) -->
    [loves, mary].

% ?- phrase(sentence(S), [every, man, loves, mary]).

/*
* lambda calculas for Montague
* e.g. ?- reduce([l(x,x),y],X). X = y .
*/
reduce(X,X) :-
    atom(X).
reduce(l(A,B),l(A,B1)) :-
    reduce(B,B1).
reduce([l(A,B),R],X) :-
    reduce(R,R1),
    beta(A,B,R1,B1),
    reduce(B1,X).

beta(A,A,R,R) :-
    atom(A).
beta(A,B,R,B) :-
    atom(B).

beta(A,B,R,X) :-
    compound(B),
    B =.. B1,
    beta_list(A,B1,R,X1),
    X =.. X1.

beta_list((A,[],R,[])).
beta_list(A,[B|Bs],R,[X1|X]) :-
    beta(A,B,R,X1),
    beta_list(A,Bs,R,X).


