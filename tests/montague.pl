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
reduce(l(A,B),l(A1,B1)) :-
    compound(B),
    alpha(A,l(A,B),0,l(A1,B1)).
reduce(l(A,B),l(A,B)). 
reduce([l(A,B),R],X) :-
    reduce(l(A,B),l(A1,B1)),
    beta(A1,B1,R,X).
reduce([L,R],X) :-
    list(L),
    reduce(L,L1),
    reduce([L1,R],X).

alpha(A,B,N,X) :-
    B =.. B1,
    alpha_list(A,B1,N,X1),
    X =.. X1.

alpha_list(A,[],N,[]) :- !.
alpha_list(A,[A|Bs],N,[A1|X]) :-
    atom_codes(A,L),
    N1 is N+48,
    append(L,[N1],L1),
    atom_codes(A1,L1),
    alpha_list(A,Bs,N,X),!.
alpha_list(A,[l(A1,B1)|Bs],N,[B3|X]) :-
    N1 is N+1,
    alpha(A1,l(A1,B1),N1,B2),
    alpha(A,B2,N,B3),
    alpha_list(A,Bs,N,X),!.
alpha_list(A,[B|Bs],N,[B|X]) :-
    alpha_list(A,Bs,N,X),!.

beta(A,A,R,R) :-
    atom(A),!.
beta(A,B,R,B) :-
    atom(B),!.

beta(A,B,R,X) :-
    compound(B),
    B =.. B1,
    beta_list(A,B1,R,X1),
    X =.. X1.

beta(A,B,R,X) :-
    list(B),
    beta_list(A,B,R,X).

beta_list(A,[],R,[]).
beta_list(A,[B|Bs],R,[X1|X]) :-
    beta(A,B,R,X1),
    beta_list(A,Bs,R,X).

% tests
test(identity) :- reduce([l(x,x), a], a).
test(constant) :- reduce([l(x,y), a], y).
test(nested1)  :- reduce([l(x, l(y, x)), a], l(y, a)).
test(nested2)  :- reduce([[l(x, l(y, x)), a], b], a).
test(non_app)  :- reduce(a, a).
test(lambda_only) :- reduce(l(x, x), l(x, x)).
test(app_in_arg) :- reduce([l(x, [x, z]), [l(y, y), a]], [[l(y, y), a], z]).
test(shadowing) :- reduce([l(x, l(x, x)), a], l(x1, x1)).
