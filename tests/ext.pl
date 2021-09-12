
writeln(X) :-
    write(X),
    nl.


maplist(_,[]).
maplist(P,[L|Ls]) :-
    atom(P),
    P1 =.. [P,L],
    call(P1),
    maplist(P,Ls).
maplist(P,[L|Ls]) :-
    P =.. L1,
    append(L1,[L],L2),
    P1 =.. L2,
    call(P1),
    maplist(P,Ls).


maplist(_,[],[]).
maplist(P,[L|Ls],[Y|Z]) :-
    my_call2(P,L,Y),
    maplist(P,Ls,Z).

my_call2(X,A,Y) :-
    P =.. [X,A,Y],
    call(P).


nth0(0,[X|_],X).
nth0(N,[_|Xs],Y) :-
    N>0,
    N1 is N-1,
    nth0(N1,Xs,Y).

partition(_,[],[],[]).
partition(P,[L|Ls],[L|Y],Z) :-
    P1 =.. [P,L],
    call(P1),
    partition(P,Ls,Y,Z).
partition(P,[L|Ls],Y,[L|Z]) :-
    partition(P,Ls,Y,Z).


conc([],List,List).
conc([X|L1],L2,[X|List]) :-
    conc(L1,L2,List).

last([X],X).
last([_|List],X) :-
    last(List,X).

list_to_atom(Atoms,Name) :-
    ascii(Atoms,List),
    name(Name,List).

ascii([Atom],List) :-!,
    name(Atom,List).
ascii([Atom|Atoms],List)    :-
    name(Atom,L),
    conc(L,Rest,List),
    !,
    ascii(Atoms,Rest).


retract_all(X) :-
    retract(X),
    fail.
retract_all(X) :-
    retract((X :- _)),
    fail.
retract_all(_).
