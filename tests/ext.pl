findall(X,G,_) :-
    asserta(item(no_more)),
    call(G),
    asserta(item(X)),
    fail.

findall(_,_,List) :-
    collect_item([],L),!,
    List = L.


collect_item(S,L) :-
    next_item(X),!,
    collect_item([X|S],L).
collect_item(L,L).

next_item(X) :-
    retract(item(X)),!,
    X \== no_more.


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


