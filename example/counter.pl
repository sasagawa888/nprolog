%example of counter predicates

now_tenof :-
    ctr_set(0,1),
    repeat,
    ctr_inc(0,Y),
    write(Y),nl,
    Y==10.
    