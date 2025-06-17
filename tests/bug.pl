

foo(O,X) :-
    member([],O),!,
    member(X,O),!,
    forall(select2(O,[X,Y]),write([X,Y])),!.