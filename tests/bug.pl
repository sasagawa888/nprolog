% testing compile code for diterministic predicate

foo(0) :- !.
foo(X) :- write(X),X1 is X-1,foo(X1).