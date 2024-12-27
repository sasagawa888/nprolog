

boo(0,[]).
boo(N,[N|M]) :- N1 is N-1,boo(N1,M).

foo(0).
foo(N) :- N1 is N-1,foo(N1).