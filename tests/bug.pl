% Repeat a procedure
repeat_for(0) :- !, fail.
repeat_for(N).
repeat_for(N) :-
    M is N - 1,
    repeat_for(M).
