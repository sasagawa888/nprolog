
:- use_module(dcg).

test_anon_dcg -->
    [_],
    [_].

% recompute_test(2,A,Z).
recompute_test(N, X, Y) :-
    between(1, N, X),
    Y is X * X.
