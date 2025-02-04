%compile dynamic idea memo

foo(X) :- boo(X).
foo(X) :- bar(X).

:- dynamic(foo/1).
:- dynamic(bar/1).
:- n_dynamic_list(X),write(X).

test :- 
    n_clause_with_arity(foo,1,C),
    n_variable_convert(C,X),
    jump_gen_dynamics(X).

jump_gen_dynamics([]).
jump_gen_dynamics([X|Xs]) :-
    jump_gen_dynamic(X),nl,
    jump_gen_dynamics(Xs).

jump_gen_dynamic([]).
jump_gen_dynamic((X :- Y)) :-
    write('Jlist3(Jmakesys(":-"),'),
    jump_gen_dynamic(X),
    write(','),
    jump_gen_dynamic(Y),
    write(');').

jump_gen_dynamic((X,Y)) :-
    write('Jlist3(Jmakesys(","),'),
    jump_gen_dynamic(X),
    write(','),
    jump_gen_dynamic(Y),
    write(');').

jump_gen_dynamic((X;Y)) :-
    write('Jlist3(Jmakesys(";")),'),
    jump_gen_dynamic(X),
    write(','),
    jump_gen_dynamic(Y),
    write(');').
    
jump_gen_dynamic(X) :-
    n_property(X,predicate),
    X =.. [P|L],
    write('Jcons(Jmakepred("'),
    write(P),
    write('"),'),
    jump_gen_dynamic_argument(L),
    write(',th)').

jump_gen_dynamic(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).
jump_gen_dynamic(X) :-
    n_property(X,builtin),
    X =.. [P|L],
    n_findatom(P,builtin,A),
    write('Jcons('),
    write(A),
    write(','),
    jump_gen_dynamic_argument(L),
    write(',th)').
jump_gen_dynamic(X) :-
    n_property(X,operation),
    X =.. [P|L],
    n_findatom(P,operator,A),
    write('Jcons('),
    write(A),
    write(','),
    jump_gen_dynamic_argument(L),
    write(',th)').
jump_gen_dynamic(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),
    write(P),
    write('")').

jump_gen_dynamic(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jcons(Jmakeuser("'),
    write(P),
    write('"),'),
    jump_gen_dynamic_argument(L),
    write(',th)').
jump_gen_dynamic(X) :-
    n_compiler_variable(X),
    write('Jmakevar("'),
    write(X),
    write('")').
jump_gen_dynamic(X) :-
    atom(X),
	write('Jmakepred("'),
    write(X),
    write('")').
jump_gen_dynamic(X) :-
    jump_invoke_error('illegal clause ',X).

jump_gen_dynamic_argument([]) :-
    write('NIL').
jump_gen_dynamic_argument([X|Xs]) :-
    write('Jcons('),
    jump_gen_dynamic(X),
    write(','),
    jump_gen_dynamic_argument(Xs),
    write(',th)').
