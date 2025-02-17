% testing compile code for diterministic predicate


foo(X) :- bar(X).

bar(X) :- write(X).

uoo(X) :- write(X),uoo(X).
