% testing compile code for diterministic predicate

run(none, N) :- repeat_for(N), fail.
run(qsort, N) :-
    list50(X),
    repeat_for(N), 
    qsort(X, _, []), 
    fail.
