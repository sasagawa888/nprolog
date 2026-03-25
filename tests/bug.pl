% not tail recursive optimization
print_answer1(0,[]).
print_answer1(N,[B|L]) :-
    B is N /\ 0x1f,
    N1 is N >> 5,
    print_answer1(N1,L) .

