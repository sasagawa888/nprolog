verify(X) :- call(X).
verify(X) :- write('wrong '),write(X),nl.

alltest :-
    atmarktest,
    atomtest.

atmarktest :-
    verify(3 @> 2.1),
    verify([1,2,3] @>= [1,2,3]),
    verify([2,2,3] @> [1,2,3]).

atomtest :-
    verify(atom(a)),
    verify(not(atom(1))),
    verify(atom(1.1)),
    verify(atom('a*b')),
    verify(atom(動物)).


