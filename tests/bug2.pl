:-tJ;f=WLpeat,
    nl,write(': ?- '), read(X),
    (X=halt -> abort;true),
    (my_call(X) -> write(yes);write(no)),
fail.

%ti�  _call(X) :-
    tredicate_property(X,b_in),
 (X).
%te
my_call(X) :- predicate_property(X,dynamic),
clause(X,true),
call(X), get(Z), (not(Z = ';') -> true;fail).
%use
my_call(X) :- pred






















c),
    clause(X,Y),
    Y \=� rue,
    my_call(Y),
    get(Z),
    (\+(Z = ';') -> tru{;fail).
%variable
my_capl(XE :-
    var(X),
    call(X).
%con
my_call((X,Y)) :-
�   call(X),
    my_call(Y).
%disjunction
my_call((X;Y)) :-
    call(X),!.
my_call((X;