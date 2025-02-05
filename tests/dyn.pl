%compile dynamic idea memo

foo(X) :- boo([X]).
foo(X) :- bar(X).

:- dynamic(foo/1).
:- dynamic(bar/1).
:- n_dynamic_predicate(foo/1),write('foo/1 is dynamic').

test :- 
    n_clause_with_arity(foo,1,C),
    n_variable_convert(C,X),
    jump_gen_dyn2s(X).

jump_gen_dyn(P/A) :-
    n_clause_with_arity(P,A,C),
    n_variable_convert(C,X),
    write('void '),
    write(P),
    write('(void){'),
    jump_gen_dyn1(X),
    write('}').

jump_gen_dyn1([]).
jump_gen_dyn1([X|Xs]) :-
    write('dynamic_clause = '),
    jump_gen_dyn2(X),nl,
    jump_gen_dyn1(Xs).

jump_gen_dyn2([]).
jump_gen_dyn2((X :- Y)) :-
    write('Jlist3(Jmakesys(":-"),'),
    jump_gen_dyn2(X),
    write(','),
    jump_gen_dyn2(Y),
    write(');').

jump_gen_dyn2((X,Y)) :-
    write('Jlist3(Jmakesys(","),'),
    jump_gen_dyn2(X),
    write(','),
    jump_gen_dyn2(Y),
    write(');').

jump_gen_dyn2((X;Y)) :-
    write('Jlist3(Jmakesys(";")),'),
    jump_gen_dyn2(X),
    write(','),
    jump_gen_dyn2(Y),
    write(');').
    
jump_gen_dyn2(X) :-
    n_property(X,predicate),
    X =.. [P|L],
    write('Jcons(Jmakepred("'),
    write(P),
    write('"),'),
    jump_gen_dyn2_argument(L),
    write(',th)').

jump_gen_dyn2(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).
jump_gen_dyn2(X) :-
    n_property(X,builtin),
    X =.. [P|L],
    n_findatom(P,builtin,A),
    write('Jcons('),
    write(A),
    write(','),
    jump_gen_dyn2_argument(L),
    write(',th)').
jump_gen_dyn2(X) :-
    n_property(X,operation),
    X =.. [P|L],
    n_findatom(P,operator,A),
    write('Jcons('),
    write(A),
    write(','),
    jump_gen_dyn2_argument(L),
    write(',th)').
jump_gen_dyn2(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),
    write(P),
    write('")').
jump_gen_dyn2(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jcons(Jmakeuser("'),
    write(P),
    write('"),'),
    jump_gen_dyn2_argument(L),
    write(',th)').
jump_gen_dyn2(X) :-
    n_compiler_variable(X),
    write('Jmakevar("'),
    write(X),
    write('")').
jump_gen_dyn2(X) :-
    n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
jump_gen_dyn2(X) :-
    n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
jump_gen_dyn2(X) :-
    integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
jump_gen_dyn2(X) :-
    float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
jump_gen_dyn2(X) :-
    list(X),
    jump_gen_dyn2_list(X).
jump_gen_dyn2(X) :-
    atom(X),
	write('Jmakepred("'),
    write(X),
    write('")').
jump_gen_dyn2(X) :-
    string(X),
	write('Jmakestr("'),
    write(X),
    write('")').
jump_gen_dyn2(X) :-
    jump_invoke_error('illegal clause ',X).

jump_gen_dyn2_argument([]) :-
    write('NIL').
jump_gen_dyn2_argument([X|Xs]) :-
    write('Jcons('),
    jump_gen_dyn2(X),
    write(','),
    jump_gen_dyn2_argument(Xs),
    write(',th)').

jump_gen_dyn2_list([]) :-
    write('NIL').
jump_gen_dyn2_list([L|Ls]) :-
    write('Jlistcons('),
    jump_gen_dyn2(L),
    write(','),
    jump_gen_dyn2_list(Ls),
    write(')').
