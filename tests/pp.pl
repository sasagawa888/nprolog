
%prolog in prolog

pp :- 
    repeat,
    nl,write(': ?- '),
    read(X),
    (X=halt -> abort;true),
    (my_call(X) -> write(yes);write(no)),
    fail.

%builtin
my_call(X) :-
    predicate_property(X,built_in),
    call(X).
%user predicate
my_call(X) :-
    predicate_property(X,dynamic),
    clause(X,true),
    write(X),
    get(D), %discard EOL
    get(Z),
    (\+(Z = ';') -> true;fail).
%user clause
my_call(X) :-
    predicate_property(X,dynamic),
    clause(X,Y),
    Y \= true,
    my_call(Y),
    write(X),
    get(D), %discard EOL
    get(Z),
    (\+(Z = ';') -> true;fail).
%variable
my_call(X) :-
    var(X),
    call(X).
%conjunction
my_call((X,Y)) :-
    call(X),
    my_call(Y).
%disjunction
my_call((X;Y)) :-
    call(X),!.
my_call((X;Y)) :-
    call(Y).