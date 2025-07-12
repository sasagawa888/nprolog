:- use_module(dcg).
:- use_module(lambda).

sentence(Sem) -->
    noun_phrase(NP),
    verb_phrase(VP),
    { Sem = [NP, VP] }.

% every man → l(P, forall(X, implies(man(X), [P, X])))
noun_phrase(l(p, forall(x, implies(man(x), [p, x])))) -->
    [every, man].

% loves Mary → l(X, loves(X, mary))
verb_phrase(l(x, loves(x, mary))) -->
    [loves, mary].

% ?- phrase(sentence(S), [every, man, loves, mary]).
% ?- phrase(sentence(S), [every, man, loves, mary]),reduce(S,X).


beta_list(A,[],R,[]).
beta_list(A,[B|Bs],R,[X1|X]) :-
    beta(A,B,R,X1),
    beta_list(A,Bs,R,X).

