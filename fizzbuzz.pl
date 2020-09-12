% ?- test(0).

test(20). 
test(N) :-
    fizzbuzz(N),
    N1 is N+1,
    test(N1).

fizzbuzz(N) :-
    N mod 3 =:= 0,
    write(fizz).
fizzbuzz(N) :-
    N mod 5 =:= 0,
    write(buzz).
fizzbuzz(N) :-
    N mod 15 =:= 0,
    write(fizzbuzz).
fizzbuzz(N) :-
    write(N).
