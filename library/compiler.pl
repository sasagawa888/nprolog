/* template. generate c file as following

#include "jump.h"
int b_<name>(int arglist, int rest);
int b_<name>(int arglist, int rest){
int arg1,arg2,arg4,varX,varY,varZ,...,save1,save2,save3,tree,body;
save2 = Jget_sp();
save3 = Jget_up();
if(n == 2){
    arg1 = Jnth(arglist,1);
    arg2 = Jnth(arglist,2);
  
    % first clause
    varX = Jmakevariant();
    varZ = Jmakevariant();
    varY = Jmakevariant();
    save1 = Jget_wp();
    if(Junify(term1,arg1) == YES && Junify_var(term2,arg2) == YES){
        body =Jwcons(119,Jwcons(varX,Jwcons(varY,NIL)));
        if(Jpove_all(Jaddtail_body(rest,body),save2,0) == YES)
            return(YES);
    }
    Jset_up(save3);
    Junbind(save2);
    Jset_wp(save1);}

    % second clause
    varX1 = Jmakevariant();
    varY1 = Jmakevariant();
    varZ1 = Jmakevariant();
    ...
    save1 = Jget_wp();
    if(Junify(term1,arg1) == YES && Junify_const(term1,arg2) == YES){
        body = Jwlist3(Jmakeope(","),Jwcons(173,Jwc ....)));
        if(Jprove_all(Jaddtail_body(rest,body),save2) == YES)
            return(YES);
    }
    Jset_up(save3);
    Junbind(save2);
    Jset_wp(save1);

    Jerrorcomp(makeint(AIRTY_ERR),Jmakecomp(<name>),arglist);
    return(NO);
}

% initialize predicate
void init_tpredicate(void){(deftpred)("<name>",b_<name>);
}
% set execution code
void init_declare(void){
  ...execution 
}


unification 
Junify(head,arg)  all-round
Junify_const(head,arg)  for constant term
Junify_var(head,arg)    for variable term
Junify_nil(head,arg)    for [] check.
*/

% optimize flag
jump_optimize(on).
jump_typed_optimize(off).

optimize(X) :-
    abolish(jump_typed_optimize/1),
    assert(jump_typed_optimize(X)).

% main
compile_file(X) :-
    jump_pass1(X),
    jump_pass2(X),
    jump_invoke_gcc(X).

% for debug not remove C code.
compile_file1(X) :-
    jump_pass1(X),
    jump_pass2(X),
    jump_invoke_gcc_not_remove(X).

% generate object from c code
compile_file1(X) :-
    jump_invoke_gcc(X).

% genrate only c code 
compile_file2(X) :-
    jump_pass1(X),
    jump_pass2(X).

/*
for tail recursive optimize code 
now ignore
*/
jump_pass1(X) :-
	write(user_output,'pass1'),
    nl(user_output),
    abolish(jump_pred_data/2),
    assert(jump_pred_data(jump_dummy,-1)),
    reconsult(X,true),
    jump_pass1_analize.

jump_pass1_analize :-
    n_reconsult_predicate(P),
    jump_analize(P),
    fail.
jump_pass1_analize.

/*
pass2 generate each clause or predicate code.
and write to <filename>.c
when all code is generated, close file and abolish optimizable/1
*/
jump_pass2(X) :-
	write(user_output,'pass2'),
    nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c',Cfile),
	tell(Cfile),
	write('#include "jump.h"'),nl,
    jump_gen_c_pred,
    jump_gen_c_exec,
    abolish(jump_pred_data/2),
    n_reconsult_abolish,
    told.

/*
when OS is Linux
system builtin predicate invoke GCC
gcc -O3 -w -shared -fPIC -o <filenam>.c <filename>.o <option>
*/
jump_invoke_gcc(X) :-
	write(user_output,'invoke GCC'),
    nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -w -shared -fPIC -I$HOME/nprolog -o ',Files,Gen),
    shell(Gen),
    atom_concat('rm ',Cfile,Del),
    shell(Del).

jump_invoke_gcc_not_remove(X) :-
	write(user_output,'invoke GCC'),
    nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -w -shared -fPIC -I$HOME/nprolog -o ',Files,Gen),
    shell(Gen).


/*
generate C code for predicate or clause.
They are provided by list.
e.g. [foo,bar,boo]
generate each predicate to make compiled pred
*/



% normal predicate
jump_gen_c_pred :-
    jump_gen_pred,
    jump_gen_c_def.

% generate all predicate code
jump_gen_pred :-
    n_reconsult_predicate(P),
    jump_gen_pred1(P),
    fail.
jump_gen_pred.

jump_gen_pred1(P) :-
    jump_pred_data(P,type1),
    jump_gen_tail_pred(P),!.
jump_gen_pred1(P) :-
    not(jump_pred_data(P,type1)),
    jump_gen_a_pred(P),!.

% define compiled predicate
jump_gen_c_def :-
	write('void init_tpredicate(void){'),
    jump_gen_c_def1,
    write('}'),nl.

jump_gen_c_def1 :-
    n_reconsult_predicate(P),
	jump_gen_def(P),
    fail.
jump_gen_c_def1.


% generate deftpred for normal predicate
jump_gen_def(P) :-
    n_defined_predicate(P),
	write('(deftpred)("'),
    write(P),
    write('",'),
    write('b_'),
    n_atom_convert(P,P1),
    write(P1),
    write(');'),
    nl,!.

% generate deftinfix for user op
jump_gen_def(P) :-
    n_defined_userop(P),
	write('(deftinfix)("'),
    write(P),
    write('",'),
    write('b_'),
    n_atom_convert(P,P1),
    write(P1),
    write(','),
    current_op(W,S,P),
    jump_spec_to_c(S,S1),
    write(W),
    write(','),
    write(S1),
    write(');'),
    nl,!.


jump_spec_to_c(fx,'FX').
jump_spec_to_c(fy,'FY').
jump_spec_to_c(xfx,'XFX').
jump_spec_to_c(xfy,'XFY').
jump_spec_to_c(yfx,'YFX').
jump_spec_to_c(xf,'XF').
jump_spec_to_c(yf,'YF').
jump_spec_to_c(fx_xfx,'FX_XFX').
jump_spec_to_c(fy_xfx,'FY_XFX').
jump_spec_to_c(fx_yfx,'FX_YFX').
jump_spec_to_c(fy_yfx,'FY_YFX').
jump_spec_to_c(fx_xf,'FX_XF').
jump_spec_to_c(fx_yf,'FX_YF').
jump_spec_to_c(fy_xf,'FY_XF').
jump_spec_to_c(fy_yf,'FY_YF').


/*
last C code to make direct execute
void init_declare(void){
    execute code...
}
*/
jump_gen_c_exec :-
	write('void init_declare(void){'),
    jump_gen_exec,
    write('}').

/*
parts for gen_predicate
C type declare.
int_b_foo(int arglist, int rest);
*/
jump_gen_type_declare(P) :-
	write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest);'),
    nl.
/*
C variable declare.
generate following code
int(int arg1,arg2,...,argN){
int arg1,arg2 ... argN,body,save1,save2;

*/
jump_gen_var_declare(P) :-
    write('int '),
    n_arity_count(P,L),
    jump_max_list(L,E),
    jump_gen_var_declare1(1,E),
    n_generate_all_variable(P,V),
    jump_gen_all_var(V),
    write('n,body,save1,save2,save3,tree,res;'),nl,!.

jump_max_list([N],N).
jump_max_list([X|Xs],X) :-
    jump_max_list(Xs,Y),
    X >= Y.
jump_max_list([X|Xs],Y) :-
    jump_max_list(Xs,Y),
    X < Y.

% arg1,arg2,...argN
jump_gen_var_declare1(S,E) :-
	S > E.
jump_gen_var_declare1(S,E) :-
	write(arg),
    write(S),
    write(','),
    S1 is S+1,
    jump_gen_var_declare1(S1,E).


/*
generate predicate for not tail recursive
int b_<name>(int arglist, int rest){
int varX,varY,...
save2 = Jget_sp();
if(n == N){
    ...main code...
}
return(NO);
}
*/
jump_gen_a_pred(P) :-
	atom_concat('compiling ',P,M),
    write(user_output,M),
    nl(user_output),
    jump_gen_type_declare(P),
	write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest){'),
    nl,
    jump_gen_var_declare(P),
    write('save2 = Jget_sp();'),
    nl,
    write('save3 = Jget_up();'),
    nl,
    write('n = Jlength(arglist);'),
    nl,
    n_arity_count(P,L),
    jump_gen_a_pred1(P,L),
    write('}'),nl.

% pred1,pred2,...,predN
jump_gen_a_pred1(P,[]) :-
    nl,
    write('Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("'),
    write(P),
    write('"),arglist);'),nl,
	write('return(NO);').

jump_gen_a_pred1(P,[L|Ls]) :-
	jump_gen_a_pred2(P,L),
    jump_gen_a_pred1(P,Ls).

% if(n == N){...}
jump_gen_a_pred2(P,N) :-
	write('if(n == '),
    write(N),
    write('){\n'),
    jump_gen_a_pred3(P,N),
    write('return(NO);}'),!.

% select all clauses that arity is N
jump_gen_a_pred3(P,N) :-
    jump_gen_var_assign(1,N),
	n_clause_with_arity(P,N,C),
    jump_gen_a_pred4(C).

% arg1 = Jnth(arglist,1);
% arg2 = Jnth(arglist,2);
% argn = Jnth(artglist,n);
jump_gen_var_assign(S,E) :-
	S > E.
jump_gen_var_assign(S,E) :-
	write(arg),
    write(S),
    write(' = Jnth(arglist,'),
    write(S),
    write(');\n'),
    S1 is S+1,
    jump_gen_var_assign(S1,E).

% generate each clause
jump_gen_a_pred4([]).
jump_gen_a_pred4([C|Cs]) :-
	n_variable_convert(C,X),
    n_generate_variable(X,V),
    jump_gen_var(V),
    jump_gen_a_pred5(X),
    jump_gen_a_pred4(Cs).

/*
save1 = Jget_wp();
save2 = jget_sp();
if( )... head
{body = }
...
*/

% generate clause
jump_gen_a_pred5((Head :- Body)) :-
    write('save1 = Jget_wp();'),nl,
	jump_gen_head(Head),
    jump_gen_body(Body).

% generate predicate with no arity
jump_gen_a_pred5(P) :-
	n_property(P,predicate),
    functor(P,_,0),
    write('return(YES);'),nl.

% CPS predicate
jump_gen_a_pred5(P) :-
	n_property(P,predicate),
    write('save1 = Jget_wp();'),nl,
	jump_gen_head(P),
    write('if(Jprove_all(rest,Jget_sp()) == YES)'),nl,
    write('return(YES);'),nl,
    write('Jset_up(save3);'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl.

jump_gen_a_pred5(P) :-
	n_property(P,userop),
    write('save1 = Jget_wp();'),nl,
	jump_gen_head(P),
    write('if(Jprove_all(rest,Jget_sp()) == YES)'),nl,
    write('return(YES);'),nl,
    write('Jset_up(save3);'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl.


% varA,varB,...
jump_gen_all_var([]).
jump_gen_all_var([L|Ls]) :-
    n_atom_convert(L,L1),
	write(L1),
    write(','),
    jump_gen_all_var(Ls).

% varA = Jmakevariant(), varB = Jmakevariant();
jump_gen_var([]).
jump_gen_var([L|Ls]) :-
    n_atom_convert(L,L1),
    write(L1),
    write(' = Jmakevariant();'),nl,
    jump_gen_var(Ls).



/*
body for compiler
foo(X),bar(X),boo(X).

if(unify(....)){
    body = ...;
    if(Jprove_all(body,Jget_sp()) == YES)
        return(YES)};

Junbind(save2);
Jset_wp(save1);


*/
jump_gen_body(X) :-
    write('{body = '),
    jump_gen_body1(X),
    write(';'),nl,
    write('if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)'),nl,
    write('return(YES);}'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl,
    write('if(res == NPLFALSE) return(NO); '),nl,
    !.


jump_gen_body1([]) :-
    write('NIL').
jump_gen_body1((X,Xs)) :-
	write('Jwlist3(Jmakeope(","),'),
	jump_gen_a_body(X),
    write(','),
    jump_gen_body1(Xs),
    write(')').
jump_gen_body1((X;Xs)) :-
	write('Jwlist3(Jmakeope(";"),'),
	jump_gen_body1(X),
    write(','),
    jump_gen_body1(Xs),
    write(')').
jump_gen_body1(X) :-
	jump_gen_a_body(X).

/*
generate one operation,user,builtin or compiled predicate.
when except of above type, invoke error.
*/
jump_gen_a_body((X;Xs)) :-
	write('Jwlist3(Jmakeope(";"),'),
	jump_gen_a_body(X),
    write(','),
    jump_gen_body1(Xs),
    write(')').
% defined predicate will become compiled predicate
jump_gen_a_body(X) :-
    n_defined_predicate(X),
    functor(X,P,0),
    write('Jmakecomp("'),
    write(P),
    write('")').
% defined predicate will become compiled predicate
jump_gen_a_body(X) :-
    n_defined_predicate(X),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    n_property(X,predicate),
    X =.. [P|L],
    write('Jwcons(Jmakepred("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
% atom builtin e.g. nl fail
jump_gen_a_body(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).
jump_gen_a_body(X) :-
    n_property(X,builtin),
    X =.. [P|L],
    n_findatom(P,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    n_property(X,operation),
    gen_body1(X).
jump_gen_a_body(X) :-
    n_property(X,compiled),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),
    write(P),
    write('")').
jump_gen_a_body(X) :-
    n_defined_userop(X),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jwcons(Jmakeuser("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    atom(X),
	write('Jmakepred("'),
    write(X),
    write('")').
jump_gen_a_body(X) :-
    jump_invoke_error('illegal body ',X).


/*
generate_unify of head
e.g.  foo(X) -> if(Junify(arg1,varX) == YES)
anoymous variable generate 1 as true.
e.g   foo(_) -> if(1)
*/

jump_gen_head(X) :-
    functor(X,_,0).
jump_gen_head(X) :-
    X =.. [_|Y],
    write('if('),
    jump_gen_head1(Y,1),
    write(')\n').

jump_gen_head1([],_) :-
    write(1).
jump_gen_head1([[]|Xs],N) :-
    write('Junify_nil('),
    jump_gen_a_argument(X),
    write(',arg'),
    write(N),
    write(') == YES && '),
    N1 is N + 1,
    jump_gen_head1(Xs,N1).
jump_gen_head1([X|Xs],N) :-
    n_compiler_anoymous(X),
    N1 is N + 1,
    jump_gen_head1(Xs,N1).  
jump_gen_head1([X|Xs],N) :-
    n_compiler_variable(X),
    write('Junify_var('),
    jump_gen_a_argument(X),
    write(',arg'),
    write(N),
    write(') == YES && '),
    N1 is N + 1,
    jump_gen_head1(Xs,N1).    
jump_gen_head1([X|Xs],N) :-
    atomic(X),
    write('Junify_const('),
    jump_gen_a_argument(X),
    write(',arg'),
    write(N),
    write(') == YES && '),
    N1 is N + 1,
    jump_gen_head1(Xs,N1). 
%testting list term compile
jump_gen_head1([X|Xs],N) :-
    jump_typed_optimize(on),
    list(X),
    write('( (({tree = arg'),
    write(N),
    write(';YES;}) == YES && '),
    jump_gen_head_list(X),
    write(') || (Jvariablep(Jderef(arg'),
    write(N),
    write(')) && Junify_var(arg'),
    write(N),
    write(','),
    jump_gen_a_argument(X),
    write(')==YES) ) && '),
    N1 is N + 1,
    jump_gen_head1(Xs,N1). 

jump_gen_head1([X|Xs],N) :-
    write('Junify('),
    jump_gen_a_argument(X),
    write(',arg'),
    write(N),
    write(') == YES && '),
    N1 is N + 1,
    jump_gen_head1(Xs,N1).


jump_gen_head_list(L) :-
    write('({int res;'),
    write('Jpush_ustack(tree);'),
    write('res = Jlistp(Jderef(tree));'),
    write('res;}) && '),
    jump_gen_head_list1(L).

jump_gen_head_list1([]) :-
    write('({int res;'),
    write('res = Junify_nil(NIL,tree);'),
    write('tree = Jpop_ustack();'),
    write('res;})==YES ').

jump_gen_head_list1(L) :-
    n_compiler_variable(L),
    write('({int res;'),
    write('res = Junify_var('),
    jump_gen_a_argument(L),
    write(',tree);'),
    write('tree = Jpop_ustack();'),
    write('res;})==YES ').

jump_gen_head_list1(L) :-
    atomic(L),
    write('({int res;'),
    write('res = Junify_const('),
    jump_gen_a_argument(L),
    write(',tree);'),
    write('tree = Jpop_ustack();'),
    write('res;})==YES ').

jump_gen_head_list1([L|Ls]) :-
    n_compiler_variable(L),
    write('({int res;'),
    write('res = Junify_var('),
    jump_gen_a_argument(L),
    write(',Jcar(tree));'),
    write('tree = Jcdr(tree);'),
    write('res;})==YES && '),
    jump_gen_head_list1(Ls).

jump_gen_head_list1([L|Ls]) :-
    atomic(L),
    write('({int res;'),
    write('res = Junify_const('),
    jump_gen_a_argument(L),
    write(','),
    write('Jcar(tree));'),
    write('tree = Jcdr(tree);'),
    write('res;})==YES && '),
    jump_gen_head_list1(Ls).

jump_gen_head_list1([L|Ls]) :-
    list(L),
    write('('),
    jump_gen_head_list(L),
    write(')'),
    jump_gen_head_list1(Ls,N,I1,Pos).

/*
generate evauation code
e.g.  X is 1+2.  X == 3*4.
*/
jump_eval_form([]) :-
	write('NIL').
jump_eval_form([X]) :-
	write('Jmakeconst("'),
    write(X),
    write('")').
jump_eval_form(pi) :-
	write('Jmakestrflt("3.14159265358979")').
jump_eval_form(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
jump_eval_form(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
jump_eval_form(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
jump_eval_form(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
jump_eval_form(X) :-
	atom(X),
    n_compiler_variable(X),
    n_atom_convert(X,X1),
    write('Jderef('),
    write(X1),
    write(')').
jump_eval_form(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
jump_eval_form(X) :-
    list(X),
    jump_gen_a_argument(X).
jump_eval_form(X + Y) :-
	write('Jplus('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X - Y) :-
	write('Jminus('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X * Y) :-
	write('Jmult('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X / Y) :-
	write('Jdivide('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X//Y) :-
	write('Jdiv('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X ** Y) :-
	write('Jexpt('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X ^ Y) :-
	write('Jexpt('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X mod Y) :-
	write('Jmod('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X rem Y) :-
	write('Jrem('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(sin(X)) :-
	write('Jsin('),
    jump_eval_form(X),
    write(')').
jump_eval_form(asin(X)) :-
	write('Jasin('),
    jump_eval_form(X),
    write(')').
jump_eval_form(cos(X)) :-
	write('Jcos('),
    jump_eval_form(X),
    write(')').
jump_eval_form(acos(X)) :-
	write('Jacos('),
    jump_eval_form(X),
    write(')').
jump_eval_form(tan(X)) :-
	write('Jtan('),
    jump_eval_form(X),
    write(')').
jump_eval_form(atan(X)) :-
	write('Jatan('),
    jump_eval_form(X),
    write(')').
jump_eval_form(exp(X)) :-
	write('Jexp('),
    jump_eval_form(X),
    write(')').
jump_eval_form(log(X)) :-
	write('Jatan('),
    jump_eval_form(X),
    write(')').
jump_eval_form(floor(X)) :-
	write('Jfloor('),
    jump_eval_form(X),
    write(')').
jump_eval_form(ceiling(X)) :-
	write('Jseiling('),
    jump_eval_form(X),
    write(')').
jump_eval_form(truncate(X)) :-
	write('Jtruncate('),
    jump_eval_form(X),
    write(')').
jump_eval_form(sign(X)) :-
	write('Jsign('),
    jump_eval_form(X),
    write(')').
jump_eval_form(round(X)) :-
	write('Jround('),
    jump_eval_form(X),
    write(')').

jump_eval_form(X << Y) :-
	write('Jleftshift('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X >> Y) :-
	write('Jrightshift('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').

jump_eval_form(X /\ Y) :-
	write('Jlogicaland('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X \/ Y) :-
	  write('Jlogicalor('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(\ X) :-
	  write('Jcomplement('),
    jump_eval_form(X),
    write(')').
jump_eval_form(X xor Y) :-
	  write('Jexclusiveor('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(X iand Y) :-
	  write('Jinclusiveand('),
    jump_eval_form(X),
    write(','),
    jump_eval_form(Y),
    write(')').
jump_eval_form(random(X)) :-
	  write('Jrandom('),
    jump_eval_form(X),
    write(')').



/*
generate arguments for pred ope fun.
arguments are provided by list.
e.g. [3,14,A,foo(2)]
*/
jump_gen_argument([]) :-
    write('NIL').
jump_gen_argument([X|Xs]) :-
	write('Jwcons('),
    jump_gen_a_argument(X),
    write(','),
    jump_gen_argument(Xs),
    write(')').
/*
generate one argument
there are all type of prolog object
*/
jump_gen_a_argument([]) :-
	write('NIL').
jump_gen_a_argument(X) :-
	n_compiler_variable(X),
    n_atom_convert(X,X1),
    write(X1).
jump_gen_a_argument(pi) :-
	write('Jmakestrflt("3.14159265358979")').
jump_gen_a_argument(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
jump_gen_a_argument(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
jump_gen_a_argument(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
jump_gen_a_argument(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
jump_gen_a_argument(X) :-
	string(X),
    write('Jmakestr("'),
    write(X),
    write('")').
jump_gen_a_argument(X) :-
    n_defined_predicate(X),
    X =.. [Y|Z],
    write('Jwcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,predicate),
    X =.. [Y|Z],
    write('Jwcons(Jmakepred("'),
    write(Y),
    write('"),'),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,builtin),
    functor(X,Y,0),
    n_findatom(Y,builtin,A),
    write(A).
jump_gen_a_argument(X) :-
    n_property(X,builtin),
    X =.. [Y|Z],
    n_findatom(Y,builtin,A),
	write('Jwcons('),
    write(A),
    write(','),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,compiled),
    functor(X,Y,0),
    n_findatom(Y,compiled,A),
    write(A).
jump_gen_a_argument(X) :-
    n_property(X,compiled),
    X =.. [Y|Z],
    n_findatom(Y,compiled,A),
    write('Jwcons('),
    write(A),
    write(','),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,operation),
    functor(X,Y,0),
    n_findatom(Y,operator,A),
    write(A).
jump_gen_a_argument(X) :-
    n_property(X,operation),
    X =.. [Y|Z],
    n_findatom(Y,operator,A),
	write('Jwcons('),
    write(A),
    write(','),
    jump_gen_argument(Z),
    write(')').
%predicate indicator  e.g. foo/1
jump_gen_a_argument(A/B) :-
    atom(A),
    integer(B),
    write('Jwlist3(Jmakefun("/"),Jmakepred("'),
    write(A),
    write('"),'),
    jump_gen_a_argument(B),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,function),
    functor(X,F,0),
    write('Jmakefun("'),
    write(F),
    write('")').
jump_gen_a_argument(X) :-
    n_property(X,function),
    X =.. [F|Z],
	write('Jwcons(Jmakefun("'),
    write(F),
    write('"),'),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,userop),
    functor(X,Y,0),
    write('Jmakeuser("'),
    write(X),
    write('")').
jump_gen_a_argument(X) :-
    n_property(X,userop),
    X =.. [Y|Z],
	write('Jwcons(Jmakeuser("'),
    write(Y),
    write('"),'),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
jump_gen_a_argument(X) :-
	list(X),
    jump_gen_argument_list(X).
jump_gen_a_argument(X) :-
    jump_invoke_error('illegal argument ',X).

jump_gen_argument_list([X|Xs]) :-
	write('Jwlistcons('),
    jump_gen_a_argument(X),
    write(','),
    jump_gen_a_argument(Xs),
    write(')').

/*
invoke error
display error message and error code.
and close output file, finaly abort to REPL
*/
jump_invoke_error(Message,Code) :-
	write(user_output,Message),
    write(user_output,Code),nl(user_output),
    told,
    abort.

/*
e.g. :- op(...)
generate execution 
*/
jump_gen_exec :-
    n_get_execute(X),
    write('int body;'),nl,
    jump_gen_exec1(X).

jump_gen_exec1([]).
jump_gen_exec1([L|Ls]) :-
    jump_gen_exec2(L),
    nl,
    jump_gen_exec1(Ls).


jump_gen_exec2(X) :-
    write('body = '),
    jump_gen_body1(X),
    write(';'),nl,
    write('Jprove_all(body,Jget_sp());'),!.

/*
optimizer for deterministic predicate

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
    if(Jcar(arglist) == NIL){if(Junify(arglist,head)==YES) 
                                  return(Jprove_all(rest,Jget_sp()));
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
jump_gen_tail_pred(P) :-
    atom_concat('compiling tail ',P,M),
    write(user_output,M),nl(user_output),
    jump_gen_type_declare(P),
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
    write('Jinc_proof();'),nl,
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
    write('{'),
    jump_gen_tail_body(Body,Head),
    write('}').

% predicate
jump_gen_tail_pred4(P) :-
    n_property(P,predicate),
    jump_gen_tail_head_unify(P).

% foo([A|B]) -> varA = car(car(arglist)); varB = cdr(car(arglist));
jump_gen_tail_var(X) :-
    functor(X,_,0).
jump_gen_tail_var(X) :-
    X =.. [_|Y],
    jump_gen_tail_var1(Y,[]).

jump_gen_tail_var1([],L).
% anoymous variable ignore
jump_gen_tail_var1(X,L) :-
    n_compiler_anoymous(X).
% normal variable
jump_gen_tail_var1(X,L) :-
    n_compiler_variable(X),
    n_atom_convert(X,X1),
    write(X1),
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
% if element of X is all compiler var -> ignore
jump_gen_tail_head(X) :-
    X =.. [_|Y],
    jump_all_var(Y).
% if element of X include constant
jump_gen_tail_head(X) :-
    X =.. [_|Y],
    write('if('),
    jump_gen_tail_head2(Y,[]),
    write(')').

%  varA = makevariant();
%  head = wlist1(varA);
%  if(o && o && ... &1) return(Junify(arglist,head));
jump_gen_tail_head_unify(Pred) :-
    Pred =.. [_|Args],
    n_generate_variable(Args,V),
    jump_gen_tail_head_unify1(V),
    write('head = '),
    jump_gen_argument(Args),
    write(';'),nl,
    jump_gen_tail_head_unify2(Args).

% varA = Jmakevariant(); varB = Jmakevariant(); ...
jump_gen_tail_head_unify1([]).
jump_gen_tail_head_unify1([X|Xs]) :-
    write(X),
    write(' = Jmakevariant();'),nl,
    jump_gen_tail_head_unify1(Xs).

% if( && &&) return(Junify(arglist,head));
jump_gen_tail_head_unify2(X) :-
    write('if('),
    jump_gen_tail_head2(X,[]),
    write('){if(Junify(arglist,head)==YES) return(Jprove_all(rest,Jget_sp())); else return(NO);}'),
    nl.
    
% unify head
% generate if(... && ... && 1) for constant value in head
% NIL []
jump_gen_tail_head2([],L) :-
    jump_gen_tail_head3(X,L),
    write(' == NIL && ').

% ignore anoymous
jump_gen_tail_head2(X,L) :-
    n_compiler_anoymous(X).
% ignore variable
jump_gen_tail_head2(X,L) :-
    n_compiler_variable(X).
% integer
jump_gen_tail_head2(X,L) :-
    integer(X),
    write('Jnumeqp(Jmakeint('),
    write(X),
    write('),'),
    jump_gen_tail_head3(X,L),
    write(') && '),nl.
% atom
jump_gen_tail_head2(X,L) :-
    atom(X),
    write('Jmakeconst("'),
    write(X),
    write('") == '),
    jump_gen_tail_head3(X,L),
    write(' && '),nl.
% float number
jump_gen_tail_head2(X,L) :-
    float(X),
    write('Jnumeqp(Jmakestrflt("'),
    write(X),
    write('"),'),
    jump_gen_tail_head3(X,L),
    write(') && '),nl.

% last element
jump_gen_tail_head2([X],L) :-
    jump_gen_tail_head2(X,[car|L]),
    write(1).

jump_gen_tail_head2([X|Xs],L) :-
    jump_gen_tail_head2(X,[car|L]),
    jump_gen_tail_head2(Xs,[cdr|L]).


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

jump_gen_tail_a_body(X = Y,Head) :-
    write('if(Junify('),
    jump_gen_a_argument(X),
    write(','),
    jump_gen_a_argument(Y),
    write(')==NO) return(NO);').

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
    write('Jcallsubr(Jmakesys("'),
    X =.. [P|L],
    write(P),
    write('"),'),
    jump_gen_a_argument(L),
    write(',NIL);'),nl.

% tail call
jump_gen_tail_a_body(X,Head) :-
    functor(X,P,A),
    functor(Head,P,A),
    X =.. [_|Xs],
    jump_gen_tail_call(Xs).

% gen_tail_a_body(X,Head) :-
%    write(user_output,X).
jump_gen_tail_a_body(X,Head).

jump_gen_tail_call(X) :-
    write('arglist = '),
    jump_gen_argument(X),
    write(';'),nl,
    write('goto loop;'),nl.


% analize tail recursive optimization
% if clauses P is optimizable assert jump_pred_data(pred_name,dt)
jump_analize(P) :-
    n_arity_count(P,[N]),
	n_clause_with_arity(P,N,C),
    n_variable_convert(C,C1),
    jump_deterministic(P,C1).

jump_deterministic(P,C) :-
    jump_type1_deterministic(C,0),
    jump_optimize(on),
    assert(jump_pred_data(P,type1)).

jump_deterministic(P,C) :-
    jump_type2_deterministic(C),
    jump_optimize(on),
    assert(jump_pred_data(P,type2)).



% type1 if clause has tail recursive and body is unidirectory
jump_type1_deterministic([],1).
jump_type1_deterministic([],0) :- fail.
jump_type1_deterministic([(Head :- Body)|Cs],_) :-
    jump_tail_recursive(Head,Body),
    jump_unidirectory(Body),
    jump_type1_deterministic(Cs,1).
jump_type1_deterministic([C|Cs],Flag) :-
    n_property(C,predicate),
    jump_self_independence(C),
    jump_type1_deterministic(Cs,Flag).

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
    Arity1 == Arity2,
    jump_independence(Head,Last),
    jump_self_independence(Head).

jump_last_body((_,Body),Last) :-
    jump_last_body(Body,Last).
jump_last_body(Body,Body).


% body elements are all builtin predicate but last
jump_unidirectory((G1,G2)) :-
    n_property(G1,builtin),
    n_property(G2,predicate).
jump_unidirectory((G,Gs)) :-
    n_property(G,builtin),
    jump_unidirectory(Gs).
jump_unidirectory(_) :- fail.


% foo([varA|varB])<=> foo(varA) false (depend)
% foo([varA|varB])<=> foo(varC) true (independ)
jump_independence(Pred1,Pred2) :-
    pred1 =.. [_|Args1],
    pred2 =.. [_|Args2],
    jump_independence1(Args1,Args2).

jump_independence1([],Y).
jump_independence1([X|Xs],Y) :-
    atomic(X),
    jump_independence1(Xs,Y).
jump_independence1([X|Xs],Y) :-
    list(X),
    jump_independence2(X,Y),
    jump_independence1(Xs,Y).

jump_independence2([],Y).
jump_independence2(X,Y) :-
    atomic(X).
jump_independence2([X|Xs],Y) :-
    atomic(X),
    not(member(X,Y)),
    jump_independence2(Xs,Y).
jump_independence2([[X|Xs]|Ys],Y) :-
    jump_independence2([X|Xs],Y),
    jump_independence2(Ys,Y).


% foo([varX|varL],[varX|1]) -> no
% foo([varY|varL],[varX|1]) -> yes
jump_self_independence(Pred) :-
    Pred =.. [_|Args],
    jump_self_independence1(Args).

jump_self_independence1([]).
jump_self_independence1([X]).
jump_self_independence1([X1,X2|Xs]) :-
    jump_self_independence2(X1,X2),
    jump_self_independence1([X1|Xs]),
    jump_self_independence1([X2|Xs]).

jump_self_independence2(X,Y) :-
    list(X),list(Y),
    jump_list_member(X,Y),!,fail.
jump_self_independence2(X,Y) :-
    atom(X),list(Y),
    member(X,Y),!,fail.
jump_self_independence2(X,Y) :-
    atom(Y),list(X),
    member(Y,X),!,fail.
jump_self_independence2(X,Y) :-
    X = Y,!,fail.
jump_self_independence2(X,Y).

jump_deep_member(X,[X|Ys]) :-
    n_compiler_variable(X).
jump_deep_member(X,X) :-
    n_compiler_variable(X).
jump_deep_member(X,[Y|Ys]) :-
    jump_deep_member(X,Ys).

jump_list_member([],Y) :- fail.
jump_list_member(X,Y) :-
    atomic(X),jump_deep_member(X,Y).
jump_list_member([L|Ls],Y) :-
    jump_deep_member(L,Y).
jump_list_member([L|Ls],Y) :-
    jump_list_member(Ls,Y).


