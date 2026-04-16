run_all :-
    test1,
    test2,
    test3,
    test4.

show(T) :-
    write(T), nl.

test1 :-
    show(test1),
    between(0, 9, N),
    write(N),
    M is N mod 5,
    (M == 4 -> nl ; true),
    fail.
test1.

test2 :-
    show(test2),
    between(0, 9, N),
    (N < 5 -> write(a) ; write(b)),
    fail.
test2 :-
    nl.

test3 :-
    show(test3),
    between(0, 9, N),
    (N < 5 -> write(a) ; write(b)),
    M is N mod 5,
    (M == 4 -> nl ; true),
    fail.
test3.

test4 :-
    show(test4),
    print_answer(123).

print_answer(PushPattern) :-
    nl,
    between(0, 24, N),
    ((PushPattern /\ (1 << N)) > 0 -> write('1') ; write('0')),
    M is N mod 5,
    (M == 4 -> nl ; true),
    fail.
print_answer(_).