

diterministic_body(!).
diterministic_body((X,(!,Y))) :-
    diterministic_body(Y).




% new compiler  
% type1 non deterministic predicate
% type2 deterministic non tail reursive predicate
% type3 deterministic tail recursive predicate
/*
optimizer for deterministic predicate

deterministic e.g.

% type1 tail_recursive and body is unidirectory

bar(0).
bar(N) :- N1 is N-1,bar(N1).

% type2,3... if find new optimization, use this typeN

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
    if(Jcar(arglist) == NIL){if(Junify(arglist,head,th)==YES) 
                                  return(Jexec_all(rest,Jget_sp(th),th));
                             else 
                                  return(NO);}

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
gen_tail_pred(P) :-
    atom_concat('compiling tail ',P,M),
    write(user_output,M),nl(user_output),
    gen_type_declare(P),
    write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest, int th){'),
    nl,
    gen_tail_var_declare(P),
    n_arity_count(P,[N]),
    gen_tail_pred1(P,N),
    write('}'),nl.

% int a,varA,varB...
gen_tail_var_declare(P) :-
    n_arity_count(P,L),
    write('int n,head,'),
    n_generate_all_variable(P,V),
    gen_tail_all_var(V).


% varA,varB,...
gen_tail_all_var([]) :-
    write('dummy;'),nl.
gen_tail_all_var([L]) :-
    write(L),
    write(';'),nl.
gen_tail_all_var([L|Ls]) :-
    write(L),
    write(','),
    gen_tail_all_var(Ls).

% n = Jlength(arglist);
% if(n == N){arg1 = ;  loop: ...}
gen_tail_pred1(P,N) :-
    write('n = Jlength(arglist);'),nl,
    write('if(n == '),
    write(N),
    write('){'),,nl,
    write('loop:'),nl,
    write('Jinc_proof(th);'),nl,
    gen_tail_pred2(P,N),
    write('}'),
    write('return(NO);'),nl.
    


% select clauses that arity is N
gen_tail_pred2(P,N) :-
    n_clause_with_arity(P,N,C),
    gen_tail_pred3(C).

% generate each predicate or clause
gen_tail_pred3([]).
    
gen_tail_pred3([L|Ls]) :-
	n_variable_convert(L,X),
    gen_tail_pred4(X),
    gen_tail_pred3(Ls).

% clause with cut
gen_tail_pred4((Head :- !)) :-
    n_property(Head,predicate),
    gen_tail_head_unify(Head).

% clause
gen_tail_pred4((Head :- Body)) :-
    gen_tail_var(Head),
	gen_tail_head(Head),
    write('{'),
    gen_tail_body(Body,Head),
    write('}').

% predicate
gen_tail_pred4(P) :-
    n_property(P,predicate),
    gen_tail_head_unify(P).

% foo([A|B]) -> varA = car(car(arglist)); varB = cdr(car(arglist));
gen_tail_var(X) :-
    functor(X,_,0).
gen_tail_var(X) :-
    X =.. [_|Y],
    gen_tail_var1(Y,[]).

gen_tail_var1([],L).
% anonymous variable ignore
gen_tail_var1(X,L) :-
    n_compiler_anonymous(X).
% normal variable
gen_tail_var1(X,L) :-
    n_compiler_variable(X),
    n_atom_convert(X,X1),
    write(X1),
    write(' = '),
    gen_tail_head3(X,L),
    write(';'),nl.
% ignore atom and number []
gen_tail_var1(X,L) :-
    atomic(X).

% list
gen_tail_var1([X|Xs],L) :-
    gen_tail_var1(X,[car|L]),
    gen_tail_var1(Xs,[cdr|L]).


% generate head of clause
% foo(1,2) ->
% if(car(arglist) == makeint(1) && cadr(arglist) == makeint(2))
gen_tail_head(X) :-
    functor(X,_,0).
% if element of X is all compiler var -> ignore
gen_tail_head(X) :-
    X =.. [_|Y],
    all_var(Y).
% if element of X include constant
gen_tail_head(X) :-
    X =.. [_|Y],
    write('if('),
    gen_tail_head2(Y,[]),
    write(')').

%  varA = makevariant(th);
%  head = wlist1(varA);
%  if(o && o && ... &1) return(Junify(arglist,head,th));
gen_tail_head_unify(Pred) :-
    Pred =.. [_|Args],
    n_generate_variable(Args,V),
    gen_tail_head_unify1(V),
    write('head = '),
    gen_argument(Args),
    write(';'),nl,
    gen_tail_head_unify2(Args).

% varA = Jmakevariant(th); varB = Jmakevariant(th); ...
gen_tail_head_unify1([]).
gen_tail_head_unify1([X|Xs]) :-
    write(X),
    write(' = Jmakevariant(th);'),nl,
    gen_tail_head_unify1(Xs).

% if( && &&) return(Junify(arglist,head,th));
gen_tail_head_unify2(X) :-
    write('if('),
    gen_tail_head2(X,[]),
    write('){if(Junify(arglist,head,th)==YES) return(Jexec_all(rest,Jget_sp(th),th)); else return(NO);}'),
    nl.
    
% unify head
% generate if(... && ... && 1) for constant value in head
% NIL []
gen_tail_head2([],L) :-
    gen_tail_head3(X,L),
    write(' == NIL && ').

% ignore anonymous
gen_tail_head2(X,L) :-
    n_compiler_anonymous(X).
% ignore variable
gen_tail_head2(X,L) :-
    n_compiler_variable(X).
% integer
gen_tail_head2(X,L) :-
    integer(X),
    write('Jnumeqp(Jmakeint('),
    write(X),
    write('),'),
    gen_tail_head3(X,L),
    write(') && '),nl.
% atom
gen_tail_head2(X,L) :-
    atom(X),
    write('Jmakeconst("'),
    write(X),
    write('") == '),
    gen_tail_head3(X,L),
    write(' && '),nl.
% float number
gen_tail_head2(X,L) :-
    float(X),
    write('Jnumeqp(Jmakestrflt("'),
    write(X),
    write('"),'),
    gen_tail_head3(X,L),
    write(') && '),nl.

% last element
gen_tail_head2([X],L) :-
    gen_tail_head2(X,[car|L]),
    write(1).

gen_tail_head2([X|Xs],L) :-
    gen_tail_head2(X,[car|L]),
    gen_tail_head2(Xs,[cdr|L]).


% write L=[car,cdr] -> Jcar(Jcdr(arglist))
gen_tail_head3(X,[]) :-
    write('arglist').
gen_tail_head3(X,[L|Ls]) :-
    write('J'),
    write(L),
    write('('),
    gen_tail_head3(X,Ls),
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
gen_tail_body(!,Head).
gen_tail_body((X,Xs),Head) :-
    gen_tail_a_body(X,Head),
    gen_tail_body(Xs,Head).
gen_tail_body((!,Xs),Head) :-
    gen_tail_body(Xs,Head).  
gen_tail_body(X,Head) :-
    gen_tail_a_body(X,Head).

gen_tail_a_body(X is Y,Head) :-
    write(X),
    write(' = '),
    eval_form(Y),
    write(';'),nl.

gen_tail_a_body(X = Y,Head) :-
    write('if(Junify('),
    gen_a_argument(X),
    write(','),
    gen_a_argument(Y),
    write(','),
    write(th),
    write(')==NO) return(NO);').

gen_tail_a_body(X =:= Y,Head) :-
    write('if(!Jnumeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')) return(NO);'),nl.

gen_tail_a_body(X =\= Y,Head) :-
    write('if(!Jnot_numeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')) return(NO);'),nl.

gen_tail_a_body(X < Y,Head) :-
    write('if(!Jsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')) return(NO);'),nl.

gen_tail_a_body(X =< Y,Head) :-
    write('if(!Jeqsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')) return(NO);'),nl.

gen_tail_a_body(X > Y,Head) :-
    write('if(!Jgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')) return(NO);'),nl.

gen_tail_a_body(X >= Y,Head) :-
    write('if(!Jeqgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')) return(NO);'),nl.

% builtin call
gen_tail_a_body(X,Head) :-
    n_property(X,builtin),
    write('Jcallsubr(Jmakesys("'),
    X =.. [P|L],
    write(P),
    write('"),'),
    gen_a_argument(L),
    write(',NIL,th);'),nl.

% tail call
gen_tail_a_body(X,Head) :-
    functor(X,P,A),
    functor(Head,P,A),
    X =.. [_|Xs],
    gen_tail_call(Xs).

% gen_tail_a_body(X,Head) :-
%    write(user_output,X).
gen_tail_a_body(X,Head).

gen_tail_call(X) :-
    write('arglist = '),
    gen_argument(X),
    write(';'),nl,
    write('goto loop;'),nl.


% analize tail recursive optimization
% if clauses P is optimizable assert pred_data(pred_name,dt)
analize(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    deterministic(P,C1).

deterministic(P,C) :-
    type1_deterministic(C,0),
    optimize(on),
    assert(pred_data(P,type1)).


% type1 if clause has tail recursive and body is unidirectory
type1_deterministic([],1).
type1_deterministic([],0) :- fail.
type1_deterministic([(Head :- Body)|Cs],_) :-
    tail_recursive(Head,Body),
    unidirectory(Head,Body),
    type1_deterministic(Cs,1).
type1_deterministic([C|Cs],Flag) :-
    n_property(C,predicate),
    self_independence(C),
    type1_deterministic(Cs,Flag).


tail_recursive(Head,Body) :-
    last_body(Body,Last),
    functor(Head,Pred1,Arity1),
    functor(Last,Pred2,Arity2),
    Pred1 == Pred2,
    Arity1 == Arity2,
    self_independence(Head).

last_body((_,Body),Last) :-
    last_body(Body,Last).
last_body(Body,Body).


flatten([],[]).
flatten([X|Xs],[X|Y]) :-
    atomic(X),
    flatten(Xs,Y).
flatten([X|Y],[X,Y]) :-
    atomic(X),
    atomic(Y).
flatten([X|Xs],Y) :-
    flatten(X,X1),
    flatten(Xs,X2),
    append(X1,X2,Y).

unidirectory(Head,Body) :-
    Head =.. [_|A],
    flatten(A,A1),
    unidirectory1(A1,Body).

% body elements are all builtin predicate but last
% if arguments of head depends on left-side of is/2, it is not unidirectory.
unidirectory1(A,(G1,G2)) :-
    n_property(G1,builtin),
    n_property(G2,predicate).
unidirectory1(A,((X is Y),Gs)) :-
    member(X,A),
    !,fail.
unidirectory1(A,(G,Gs)) :-
    n_property(G,builtin),
    unidirectory1(A,Gs).
unidirectory1(A,_) :- fail.


% foo([varX|varL],[varX|1]) -> no
% foo([varY|varL],[varX|1]) -> yes
self_independence(Pred) :-
    Pred =.. [_|Args],
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
    atom(Y),list(X),
    member(Y,X),!,fail.
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


