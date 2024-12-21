:- mt_create(2).

foo(0).
foo(N) :- write(N),N1 is N-1,foo(N1).

% mt_and([foo(2),write(1)]).