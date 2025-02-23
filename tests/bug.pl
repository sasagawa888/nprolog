% testing compile code for diterministic predicate

foo(0) :- !.
foo(X) :- write(X),X1 is X-1,foo(X1).

bar([]).
bar([X|Xs]) :-
    write(X),
    bar(Xs).


fact(0,1) :- !.
fact(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.
