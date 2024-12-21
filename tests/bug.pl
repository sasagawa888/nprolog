:- mt_create(2).

foo(0).
foo(N) :- write(N),N1 is N-1,foo(N1).

boo(0).
boo(N) :- write(N),N1 is N-1,boo(N1).
% mt_and([foo(2),boo(3)]).