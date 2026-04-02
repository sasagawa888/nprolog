

test(A) :-
    open(S,'./tests/plm1.pl',r),
    read_codes(S,C),
    tokenize(C,T),write(T),nl,
    compile(T,A),
    close(S).

compile(T,A) :-
    parse(T,A).

parse(S,A) :-
    phrase(program(A),S).

program(A) --> pl_module(A).
program(A) --> statements(A).
