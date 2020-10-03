/*
deterministic e.g.

% type1 tail_recursive and body is unidirectory

bar(0).
bar(N) :- N1 is N-1,bar(N1).

% type2 base has cut and clause is tail recursive
append([],L,L) :- !.
append([A|L],B, [A|C]):-
	append(L,B,C).
 

optimizable <=> deterministic

template e.g. nodiag/3 in 9queens problem
nodiag([], _, _).
nodiag([N|L], B, D) :-
	D =\= N - B,
	D =\= B - N,
	D1 is D + 1,
	nodiag(L, B, D1).

int b_nodiag(int nest, int n);
int b_nodiag(int nest, int n){
int n,arg1,arg2,arg3,varD1,varN,varL,varB,varD;
if(n == 3){
    loop:
    head = Jwlist3(NIL,makeconst("_"),makeconst("_"));
    if(Junify(arglist,head))
        return(YES);

    varN = Jcar(car(arglist));
    varL = Jcdr(car(arglist));
    varB = cadr(arglist);
    varD = caddr(arglist);
    if(!(Jnot_numeqp(varD),Jminus(varN,varB)))
        return(NO);
    if(!(Jnot_numeqp(varD),Jminus(varB),varN))))
        return(NO);
    varD1 = Jplus(varD,Jmakeint(1));
    arglist = Jwlist3(varL,varB,varD1);
    goto loop;
    }
    return(NO);
}
*/

%------------------------------------
%for tail recursive optimization
test(P) :-
    jump_gen_tail_pred(P).

jump_gen_tail_pred(P) :-
    atom_concat('compiling tail ',P,M),
    write(user_output,M),nl(user_output),
    write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest){'),
    nl,
    jump_gen_tail_var_declare(P),
    n_arity_count(P,[N]),
    jump_gen_tail_pred1(P,N),
    write('}'),nl.

% int a,varA,varB...
jump_gen_tail_var_declare(P) :-
    n_arity_count(P,L),
    write('int n,head,'),
    n_generate_all_variable(P,V),
    jump_gen_tail_all_var(V).


% varA,varB,...
jump_gen_tail_all_var([]) :-
    write('dummy;'),nl.
jump_gen_tail_all_var([L]) :-
    write(L),
    write(';'),nl.
jump_gen_tail_all_var([L|Ls]) :-
    write(L),
    write(','),
    jump_gen_tail_all_var(Ls).

% n = Jlength(arglist);
% if(n == N){arg1 = ;  loop: ...}
jump_gen_tail_pred1(P,N) :-
    write('n = Jlength(arglist);'),nl,
    write('if(n == '),
    write(N),
    write('){'),,nl,
    write('loop:'),nl,
    jump_gen_tail_pred2(P,N),
    write('}'),
    write('return(NO);'),nl.
    


% select clauses that arity is N
jump_gen_tail_pred2(P,N) :-
    n_clause_with_arity(P,N,C),
    jump_gen_tail_pred3(C).

% generate each predicate or clause
jump_gen_tail_pred3([]).
    
jump_gen_tail_pred3([L|Ls]) :-
	n_variable_convert(L,X),
    jump_gen_tail_pred4(X),
    jump_gen_tail_pred3(Ls).

% clause with cut
jump_gen_tail_pred4((Head :- !)) :-
    n_property(Head,predicate),
    jump_gen_tail_head_unify(Head).

% clause
jump_gen_tail_pred4((Head :- Body)) :-
    jump_gen_tail_var(Head),
	jump_gen_tail_head(Head),
    jump_gen_tail_body(Body,Head).

% predicate
jump_gen_tail_pred4(P) :-
    n_property(P,predicate),
    jump_gen_tail_head_unify(P).

% foo([A|B]) -> varA = car(car(arglist)); varB = cdr(car(arglist));
jump_gen_tail_var(X) :-
    functor(X,_,0).
jump_gen_tail_var(X) :-
    n_argument_list(X,Y),
    jump_gen_tail_var1(Y,[]).

jump_gen_tail_var1([],L).
% anoymous variable ignore
jump_gen_tail_var1(X,L) :-
    n_compiler_anoymous(X).
% normal variable
jump_gen_tail_var1(X,L) :-
    n_compiler_variable(X),
    write(X),
    write(' = '),
    jump_gen_tail_head3(X,L),
    write(';'),nl.
% ignore atom and number []
jump_gen_tail_var1(X,L) :-
    atomic(X).

% list
jump_gen_tail_var1([X|Xs],L) :-
    jump_gen_tail_var1(X,[car|L]),
    jump_gen_tail_var1(Xs,[cdr|L]).


% generate head of clause
% foo(1,2) ->
% if(car(arglist) == makeint(1) && cadr(arglist) == makeint(2))
jump_gen_tail_head(X) :-
    functor(X,_,0).
jump_gen_tail_head(X) :-
    n_argument_list(X,Y),
    jump_all_var(Y).
jump_gen_tail_head(X) :-
    n_argument_list(X,Y),
    write('if('),
    jump_gen_tail_head1(Y,1),
    write(')').

%  varA = makevariant();
%  head = wlist1(varA);
%  if(Junify(arglist,head) == YES) return(YES);
jump_gen_tail_head_unify(Pred) :-
    n_argument_list(Pred,Args),
    n_generate_variable(Args,V),
    jump_gen_tail_head_unify1(V),
    write('head = '),
    jump_gen_a_argument(Args),
    write(';'),nl,
    jump_gen_tail_head_unify2(Args).

% varA = Jmakevariant(); varB = Jmakevariant(); ...
jump_gen_tail_head_unify1([]).
jump_gen_tail_head_unify1([X|Xs]) :-
    write(X),
    write(' = Jmakevariant();'),nl,
    jump_gen_tail_head_unify1(Xs).

% if(Junify(arg1,varA)==YES) return(YES);
jump_gen_tail_head_unify2([]).
jump_gen_tail_head_unify2([X|Xs]) :-
    write('if(Junify(arglist'),
    write(','),
    jump_gen_a_argument(X),
    write(')==YES) return(YES)'),
    write(';'),nl.
    


jump_gen_tail_head1([X],N) :-
    jump_gen_tail_head2(X,N,[]),
    write(1).
jump_gen_tail_head1([[]|Xs],N) :-
    write('arg'),
    write(N),
    write(' == NIL &&'),nl,
    jump_gen_tail_head1(Xs,N).
jump_gen_tail_head1([X|Xs],N) :-
    jump_gen_tail_head2(X,N,[]),
    N1 is N + 1,
    jump_gen_tail_head1(Xs,N1).

%NIL []
jump_gen_tail_head2([],N,L) :-
    jump_gen_tail_head3(X,N,L),
    write(' == NIL &&').

%ignore anoymous
jump_gen_tail_head2(X,N,L) :-
    n_compiler_anoymous(X).
%ignore variable
jump_gen_tail_head2(X,N,L) :-
    n_compiler_variable(X).
%atom
jump_gen_tail_head2(X,N,L) :-
    not(n_property(X,builtin)),
    atom(X),
    write('Jmakeconst("'),
    write(X),
    write('") != '),
    jump_gen_tail_head3(X,N,L),
    write(' && '),nl.
%integer
jump_gen_tail_head2(X,N,L) :-
    integer(X),
    write('Jnumeqp(Jmakeint('),
    write(X),
    write('),'),
    jump_gen_tail_head3(X,N,L),
    write(') && '),nl.
%float number
jump_gen_tail_head2(X,N,L) :-
    real(X),
    write('Jnumeqp(Jmakestrflt("'),
    write(X),
    write('"),'),
    jump_gen_tail_head3(X,N,L),
    write(') && '),nl.
%list  ignore list
jump_gen_tail_head2(X,N,L) :-
    list(X).


% write L=[car,cdr] -> Jcar(Jcdr(arglist))
jump_gen_tail_head3(X,[]) :-
    write('arglist').
jump_gen_tail_head3(X,[L|Ls]) :-
    write('J'),
    write(L),
    write('('),
    jump_gen_tail_head3(X,Ls),
    write(')').

%if all elements are compiler_variable -> true
jump_all_var(X) :-
    member([],X),!,fail.
jump_all_var(X) :-
    jump_all_var1(X).
jump_all_var1([]).
jump_all_var1(X) :-
    n_compiler_variable(X).
jump_all_var1([X|Xs]) :-
    jump_all_var1(X),
    jump_all_var1(Xs).

%generate body that has tail call
jump_gen_tail_body((X,Xs),Head) :-
    jump_gen_tail_a_body(X,Head),
    jump_gen_tail_body(Xs,Head).
jump_gen_tail_body(X,Head) :-
    jump_gen_tail_a_body(X,Head).

jump_gen_tail_a_body(X is Y,Head) :-
    write(X),
    write(' = '),
    jump_eval_form(Y),
    write(';'),nl.

jump_gen_tail_a_body(X =:= Y,Head) :-
    write('if(!Jnumeqp('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')) return(NO);'),nl.

jump_gen_tail_a_body(X =\= Y,Head) :-
    write('if(!Jnot_numeqp('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')) return(NO);'),nl.

jump_gen_tail_a_body(X < Y,Head) :-
    write('if(!Jsmallerp('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')) return(NO);'),nl.

jump_gen_tail_a_body(X =< Y,Head) :-
    write('if(!Jeqsmallerp('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')) return(NO);'),nl.

jump_gen_tail_a_body(X > Y,Head) :-
    write('if(!Jgreaterp('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')) return(NO);'),nl.

jump_gen_tail_a_body(X >= Y,Head) :-
    write('if(!Jeqgreaterp('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')) return(NO);'),nl.

% builtin call
jump_gen_tail_a_body(X,Head) :-
    n_property(X,builtin),
    X =.. L,
    write('Jcallsubr('),
    jump_gen_a_argument(L),
    write(',NIL);'),nl.

% tail call
jump_gen_tail_a_body(X,Head) :-
    functor(X,P,A),
    functor(Head,P,A),
    n_argument_list(X,Xs),
    jump_gen_tail_call(Xs).

%gen_tail_a_body(X,Head) :-
%    write(user_output,X).
jump_gen_tail_a_body(X,Head).

jump_gen_tail_call(X) :-
    write('arglist = '),
    jump_gen_a_argument(X),
    write(';'),nl,
    write('goto loop;'),nl.


%analize tail recursive optimization
%if clauses P is optimizable assert jump_optimize(dt1,dt2)
bar(0).
bar(N) :- N1 is N-1,bar(N1).

myappend([],L,L) :- !.
myappend([A|L],B, [A|C]):-
	myappend(L,B,C).
 
nodiag([], _, _).
nodiag([N|L], B, D) :-
	D =\= N - B,
	D =\= B - N,
	D1 is D + 1,
	nodiag(L, B, D1).

jump_analize(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    jump_deterministic(P,C1).

jump_deterministic(P,C) :-
    jump_type1_deterministic(C),
    assert(jump_optimize(P,diterministic)).

jump_deterministic(P,C) :-
    jump_type2_deterministic(C),
    assert(jump_optimize(P,deterministic)).



% type1 if clause has tail recursive and body is unidirectory
jump_type1_deterministic([]).
jump_type1_deterministic([C|Cs]) :-
    n_property(C,predicate),
    jump_type1_deterministic(Cs).
jump_type1_deterministic([(Head :- Body)|Cs]) :-
    jump_tail_recursive(Head,Body),
    jump_unidirectory(Body),
    jump_type1_deterministic(Cs).

% type2 if base has cut and other clause is tail recursive.
jump_type2_deterministic([]).
jump_type2_deterministic([(Head :- !)|Cs]) :-
    jump_type2_deterministic(Cs).
jump_type2_deterministic([(Head :- Body)|Cs]) :-
    jump_tail_recursive(Head,Body),
    jump_type2_deterministic(Cs).


jump_tail_recursive(Head,Body) :-
    jump_last_body(Body,Last),
    functor(Head,Pred1,Arity1),
    functor(Last,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2.

jump_last_body((_,Body),Last) :-
    jump_last_body(Body,Last).
jump_last_body(Body,Body).


% body has is/2 
jump_unidirectory((G,Gs)) :-
    G = is(_,_).
jump_unidirectory((G,Gs)) :-
    jump_unidirectory(Gs).
jump_unidirectory(_) :- fail.

