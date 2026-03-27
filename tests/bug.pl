

extract_variable(Term,X) :-
    Term =.. [_|A],
    extract_variable1(A,X).

extract_variable1([],[]).

extract_variable1([L|Ls],[L|Y]) :-
    n_compiler_variable(L), !,
    extract_variable1(Ls,Y).
extract_variable1([L|Ls],Y) :-
    atomic(L), !,
    extract_variable1(Ls,Y).
extract_variable1([L|Ls],Z) :-
    list(L), !,
    extract_variable1(L,Y1),
    extract_variable1(Ls,Y2),
    append(Y1,Y2,Z).
extract_variable1([L|Ls],Z) :-
    n_property(L,predicate), !,
    L =.. [_|Args],
    extract_variable1(Args,Y1),
    extract_variable1(Ls,Y2),
    append(Y1,Y2,Z).
extract_variable1(L,[L]) :-
    n_compiler_variable(L), !.
extract_variable1(L,[]) :-
    atomic(L).