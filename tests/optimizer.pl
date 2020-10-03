/*
deterministic e.g.

% all sub goals are deterministic
foo(X) :- write(X).
bar(X) :- foo(X),write(X). % require two pass

% is/2 is unidirection
fact(0,1).
fact(X,Y) :- 
    X1 is X-1,
    fact(X1,Y1),
    Y is X*Y1.

% base has cut
append([],L,L) :- !.
append([A|L],B, [A|C]):-
	append(L,B,C).
 

tail_recursive e.g.

bar(0).
bar(N) :- N1 is N-1,bar(N1).

optimizable <=> deterministic or (determinisutic and tail recursive)

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
    arg1 = Jcar(arglist);
    arg2 = Jcadr(arglist);
    arg3 = Jcaddr(arglist);
    loop:
    if(Jeqp(arg1,NIL))
        return(YES);

    varN = Jcar(arg1);
    varL = Jcdr(arg1);
    varB = arg2;
    varD = arg3;
    if(!(Jnot_numeqp(varD),Jminus(varN,varB)))
        return(NO);
    if(!(Jnot_numeqp(varD),Jminus(varB),varN))))
        return(NO);
    varD1 = Jplus(varD,Jmakeint(1));
    arg1 = varL;
    arg2 = varB;
    arg3 = varD1;
    goto loop;
    }
    return(NO);
}
*/

%------------------------------------
%for tail recursive optimization
jump_gen_tail_pred(P) :-
    atom_concat('compiling tail ',P,M),
    write(user_output,M),nl(user_output),
    write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int nest, int n){'),
    nl,
    jump_gen_tail_var_declare(P),
    n_arity_count(P,[N]),
    gen_tail_pred1(P,N),
    write('}'),nl.

% int arg1,arg2,...argN,varA,varB...
jump_gen_tail_var_declare(P) :-
    n_arity_count(P,L),
    jump_max_element(L,M),
    write('int '),
    jump_gen_tail_var_declare1(1,M),
    n_generate_all_variable(P,V),
    jump_gen_tail_all_var(V).

% arg1,save1,arg1,save2,...,argN,saveN
jump_gen_tail_var_declare1(S,E) :-
	S > E.
jump_gen_tail_var_declare1(S,E) :-
    write(arg),
    write(S),
    write(','),
    write(save),
    write(S),
    write(','),
    S1 is S+1,
    jump_gen_tail_var_declare1(S1,E).


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

% if(n == N){arg1 = ;  loop: ...}
jump_gen_tail_pred1(P,N) :-
    write('if(n == '),
    write(N),
    write('){'),
    jump_gen_tail_receive_var(1,N),
    write('loop:'),nl,
    jump_gen_tail_pred2(P,N),
    write('}'),
    write('return(NO);').

% arg1 = save1 = Jderef(Jget_goal(2));
% arg2 = save1 = Jderef(Jget_goal(3)); ...
jump_gen_tail_receive_var(S,N) :-
    S > N.
jump_gen_tail_receive_var(S,N) :-
    write('arg'),
    write(S),
    write(' = save'),
    write(S),
    S1 is S + 1,
    write(' = Jderef(Jget_goal(' ),
    write(S1),
    write('));'),nl,
    jump_gen_tail_receive_var(S1,N).

%select clauses that arity is N
jump_gen_tail_pred2(P,N) :-
    n_clause_with_arity(P,N,C),
    jump_gen_tail_pred3(C,1).

%generate each predicate
jump_gen_tail_pred3([],N) :-
    write('return(NO);'),nl.
jump_gen_tail_pred3([L|Ls],N) :-
	n_variable_convert(L,X),
    jump_gen_tail_pred4(X,N),
    N1 is N + 1,
    jump_gen_tail_pred3(Ls,N1).

% clause
jump_gen_tail_pred4((Head :- Body),N) :-
    jump_gen_tail_var(Head),
	jump_gen_tail_head(Head),
    jump_gen_tail_body(Body,Head).

% predicate
jump_gen_tail_pred4(P,N) :-
    n_property(P,predicate),
    jump_gen_tail_head(P),
    write('{'),
    jump_gen_tail_head_unify(P,N),
    write('return(YES);}'),nl,
    write('exit'),write(N),write(':'),nl.

% foo([A|B]) -> varA = car(arg1); varB = cdr(arg1);
jump_gen_tail_var(X) :-
    functor(X,_,0).
jump_gen_tail_var(X) :-
    n_argument_list(X,Y),
    jump_gen_tail_var1(Y,1,[]).

jump_gen_tail_var1([],N,L).
% anoymous variable
jump_gen_tail_var1(X,N,L) :-
    n_compiler_anoymous(X).
%normal variable
jump_gen_tail_var1(X,N,L) :-
    n_compiler_variable(X),
    write(X),
    write(' = '),
    jump_gen_tail_head3(X,N,L),
    write(';'),nl.
%ignore atom and number []
jump_gen_tail_var1(X,N,L) :-
    atomic(X).

%list
jump_gen_tail_var1([[Y|Ys]|Xs],N,L) :-
    jump_gen_tail_var1(Y,N,[car|L]),
    jump_gen_tail_var1(Ys,N,[cdr|L]),
    N1 is N + 1,
    jump_gen_tail_var1(Xs,N1,[]).

jump_gen_tail_var1([X|Xs],N,L) :-
    jump_gen_tail_var1(X,N,[]),
    N1 is N + 1,
    jump_gen_tail_var1(Xs,N1,[]).

% foo(1,2) ->
% if(arg1 == makeint(1) && arg2 == makeint(2)) return(YES);
jump_gen_tail_head(X) :-
    functor(X,_,0).
jump_gen_tail_head(X) :-
    n_argument_list(X,Y),
    all_var(Y).
jump_gen_tail_head(X) :-
    n_argument_list(X,Y),
    write('if('),
    jump_gen_tail_head1(Y,1),
    write(')').

% {varA = makevariant();
%  if(Junify(varA,arg1) == NO) goto exitN;
%  Junify(save1,varA);
% ... return(YES);}
jump_gen_tail_head_unify(Pred,N) :-
    n_argument_list(Pred,Args),
    n_generate_variable(Args,V),
    jump_gen_tail_head_unify1(V),
    jump_gen_tail_head_unify2(Args,1,N).

% varA = Jmakevariant(); varB = Jmakevariant(); ...
jump_gen_tail_head_unify1([]).
jump_gen_tail_head_unify1([X|Xs]) :-
    write(X),
    write(' = Jmakevariant();'),nl,
    jump_gen_tail_head_unify1(Xs).

% if(Junify(arg1,varA)==NO) goto exitN;
% Junify(save1,varA); ...
jump_gen_tail_head_unify2([],N,M).
jump_gen_tail_head_unify2([X|Xs],N,M) :-
    write('if(Junify(arg'),
    write(N),
    write(','),
    jump_gen_a_argument(X),
    write(')==NO) goto exit'),write(M),write(';'),nl,
    write('Junify(save'),
    write(N),
    write(',arg'),
    write(N),
    write(');'),nl,
    N1 is N + 1,
    jump_gen_tail_head_unify2(Xs,N1,M).


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


%write element N=1, L=[car,cdr] -> car(cdr(arg1))
jump_gen_tail_head3(X,N,[]) :-
    write('arg'),
    write(N).
jump_gen_tail_head3(X,N,[L|Ls]) :-
    write('J'),
    write(L),
    write('('),
    jump_gen_tail_head3(X,N,Ls),
    write(')').

%if all elements are compiler_variable -> true
all_var(X) :-
    member([],X),!,fail.
all_var(X) :-
    all_var1(X).
all_var1([]).
all_var1(X) :-
    n_compiler_variable(X).
all_var1([X|Xs]) :-
    all_var1(X),
    all_var1(Xs).

%generate body that has tail call
jump_gen_tail_body((X,Xs),Head) :-
    jump_gen_tail_a_body(X,Head),
    write('{'),
    jump_gen_tail_body(Xs,Head),
    write('}').
jump_gen_tail_body(X,Head) :-
    jump_gen_tail_a_body(X,Head).

jump_gen_tail_a_body(X is Y,Head) :-
    write(X),
    write(' = '),
    eval_form(Y),
    write(';').

jump_gen_tail_a_body(X =:= Y,Head) :-
    write('if(Jnumeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

jump_gen_tail_a_body(X =\= Y,Head) :-
    write('if(Jnot_numeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

jump_gen_tail_a_body(X < Y,Head) :-
    write('if(Jsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

jump_gen_tail_a_body(X =< Y,Head) :-
    write('if(Jeqsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

jump_gen_tail_a_body(X > Y,Head) :-
    write('if(Jgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

jump_gen_tail_a_body(X >= Y,Head) :-
    write('if(Jeqgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

jump_gen_tail_a_body(X,Head) :-
    n_property(X,builtin),
    functor(X,_,L),
    L1 is L+1,
    write('Jset_goal(0,'),
    write(L1),
    write(');'),nl,
    X =.. L2,
    jump_gen_tail_set_goal(L2,1),
    write('Jcallsubr(Jget_goal(1),0,Jget_goal(0) - 1);').

jump_gen_tail_a_body(X,Head) :-
    functor(X,P,A),
    functor(Head,P,A),
    n_argument_list(X,Xs),
    gen_tail_call(Xs,1).

%gen_tail_a_body(X,Head) :-
%    write(user_output,X).
jump_gen_tail_a_body(X,Head).

jump_gen_tail_set_goal([],N).
jump_gen_tail_set_goal([X|Xs],N) :-
    write('Jset_goal('),
    write(N),
    write(','),
    jump_gen_a_argument(X),
    write(');'),nl,
    N1 is N + 1,
    jump_gen_tail_set_goal(Xs,N1).

jump_gen_tail_call([],N) :-
    write('goto loop;'),nl.
jump_gen_tail_call([X|Xs],N) :-
    write('arg'),
    write(N),
    write(' = '),
    jump_gen_a_argument(X),
    write(';'),nl,
    N1 is N + 1,
    jump_gen_tail_call(Xs,N1).


%analize tail recursive optimization
%if clauses P is optimizable => true
tail_optimize(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    deterministic(C1),
    tail_recursive(C1,0),
    unidirectional(C1),!.

% if clauses is all deterministic -> true
deterministic([]).
deterministic([C|Cs]) :-
    n_property(C,predicate),
    deterministic(Cs).
deterministic([(_ :- Body)|Cs]) :-
    deterministic1(Body),
    deterministic(Cs).

deterministic1((Body1,Body2)) :-
    n_property(Body1,builtin),
    deterministic1(Body2).
deterministic1(Body1).

last_body((_,Body),Last) :-
    last_body(Body,Last).
last_body(Body,Body).

% clause has tail recursive call -> true
tail_recursive(_,1) :- !.
tail_recursive([],0) :- fail.
tail_recursive([C|Cs],N) :-
	  n_property(C,predicate),
    tail_recursive(Cs,N).
tail_recursive([(H :- B)|Cs],N) :-
    tail_recursive1(H,B),
    tail_recursive(Cs,1).
tail_recursive([(H :- B)|Cs],N) :-
    tail_recursive2(H,B), %it has not independence
    tail_recursive([],0).

% body has tail recursive and it is independent
tail_recursive1(Head,Body) :-
    last_body(Body,Last),
    functor(Head,Pred1,Arity1),
    functor(Last,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2,
    independence(Head,Last),
    self_independence(Head).

% body has tail recursive but it is depend
tail_recursive2(Head,Body) :-
    last_body(Body,Last),
    functor(Head,Pred1,Arity1),
    functor(Last,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2,
    (not(independence(Head,Last));not(self_independence(Head))).

% if clauses are unidirectinal -> true
unidirectional([]).
unidirectional([C|Cs]) :-
    n_property(C,predicate),
    unidirectional(Cs).
unidirectional([(H :- B)|Cs]) :-
    unidirectional1(B,H).

% clause body has is builtin and other are all builtin -> true
/*
unidirectional1((Body1,Body2),H) :-
	n_is(Body1,Y),
    H =.. A,
	subset(Y,A).
*/
unidirectional1((Body1,Body2),H) :-
    n_property(Body1,builtin),
    unidirectional1(Body2,H).

unidirectional1(Body,H) :-
    n_property(Body,predicate),
    functor(H,N,A),
    functor(Body,N,A).


subset([],_).
subset([X|Sub],Set) :-
    member(X,Set),
    subset(Sub,Set).

% foo([varA|varB])<=> foo(varA) false (depend)
% foo([varA|varB])<=> foo(varC) true (independ)
independence(Pred1,Pred2) :-
    n_argument_list(Pred1,Args1),
    n_argument_list(Pred2,Args2),
    independence1(Args1,Args2).

independence1([],Y).
independence1([X|Xs],Y) :-
    atomic(X),
    independence1(Xs,Y).
independence1([X|Xs],Y) :-
    list(X),
    independence2(X,Y),
    independence1(Xs,Y).

independence2([],Y).
independence2(X,Y) :-
    atomic(X).
independence2([X|Xs],Y) :-
    atomic(X),
    not(member(X,Y)),
    independence2(Xs,Y).
independence2([[X|Xs]|Ys],Y) :-
    independence2([X|Xs],Y),
    independence2(Ys,Y).


% foo([varX|varL],[varX|1]) -> no
% foo([varY|varL],[varX|1]) -> yes
self_independence(Pred) :-
    n_argument_list(Pred,Args),
    self_independence1(Args).

self_independence1([]).
self_independence1([X]).
self_independence1([X1,X2|Xs]) :-
    self_independence2(X1,X2),
    self_independence1([X1|Xs]),
    self_independence1([X2|Xs]).

self_independence2(X,Y) :-
    list(X),list(Y),
    list_member(X,Y),!,fail.
self_independence2(X,Y) :-
    atom(X),list(Y),
    member(X,Y),!,fail.
self_independence2(X,Y) :-
    X = Y,!,fail.
self_independence2(X,Y).

deep_member(X,[X|Ys]) :-
    n_compiler_variable(X).
deep_member(X,X) :-
    n_compiler_variable(X).
deep_member(X,[Y|Ys]) :-
    deep_member(X,Ys).

list_member([],Y) :- fail.
list_member(X,Y) :-
    atomic(X),deep_member(X,Y).
list_member([L|Ls],Y) :-
    deep_member(L,Y).
list_member([L|Ls],Y) :-
    list_member(Ls,Y).
