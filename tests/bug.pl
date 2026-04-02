
:- use_module(dcg).


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

statement(proc(N,P,S,T)) -->
    identifier(N),[':'],['PROCEDURE'],param(P),data_type(T),[';'],
    statements(S),['END'],identifier(N),[';'].