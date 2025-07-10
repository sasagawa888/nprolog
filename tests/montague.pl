:- use_module(dcg).


% sentence = noun + verb
sentence(Sem) -->
    noun_phrase(NP),
    verb_phrase(VP),
    { Sem = app(NP, VP) }.  % generate lambda

% every man → λP. ∀x.(man(x) → P(x))
noun_phrase(lambda(P, forall(X, implies(man(X), app(P, X))))) -->
    [every, man].

% loves Mary → λx. loves(x, mary)
verb_phrase(lambda(X, loves(X, mary))) -->
    [loves, mary].

