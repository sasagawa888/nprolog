/* template. generate c file as following

#include "jump.h"
int b_<name>(int arglist, int rest, int th);
int b_<name>(int arglist, int rest, int th){
int arg1,arg2,arg4,varX,varY,varZ,...,save1,save2,goal,cont;
save2 = Jget_sp(th);
if(n == 2){
    arg1 = Jnth(arglist,1);
    arg2 = Jnth(arglist,2);
  
    % first clause
    varX = Jmakevariant(th);
    varZ = Jmakevariant(th);
    varY = Jmakevariant(th);
    save1 = Jget_wp(th);
    if(Junify(term1,arg1,th) == YES && Junify_var(term2,arg2,th) == YES){
        body =Jwcons(119,Jwcons(varX,Jwcons(varY,NIL),th),th);
        if(Jexec_all(Jaddtail_body(rest,body,th),save2,th) == YES)
            return(YES);
    }
    Junbind(save2,th);
    Jset_wp(save1,th);}

    % second clause
    varX1 = Jmakevariant(th);
    varY1 = Jmakevariant(th);
    varZ1 = Jmakevariant(th);
    ...
    save1 = Jget_wp(th);
    if(Junify(term1,arg1,th) == YES && Junify_const(term1,arg2,th) == YES){
        body = Jwlist3(Jmakeope(","),Jwcons(173,Jwc ...., th)),th);
        if(Jexec_all(Jaddtail_body(rest,body,th),save2,th) == YES)
            return(YES);
    }
    Junbind(save2,th);
    Jset_wp(save1,th);

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
Junify(head,arg,th)  all-round
Junify_const(head,arg,th)  for constant term
Junify_var(head,arg,th)    for variable term
Junify_nil(arg,th)    for [] check.
*/

:- module(jump,[compile_file/1,compile_file1/1,compile_file2/1]).

% optimize flag
optimize(on).
typed_optimize(off).

optimize(X) :-
    abolish(jump_typed_optimize/1),
    assert(jump_typed_optimize(X)).

% main
compile_file(X) :-
    pass1(X),
    pass2(X),
    invoke_gcc(X).

% for debug not remove C code.
compile_file1(X) :-
    pass1(X),
    pass2(X),
    invoke_gcc_not_remove(X).


% genrate only c code 
compile_file2(X) :-
    pass1(X),
    pass2(X).

% generate object from c code
compile_file3(X) :-
    invoke_gcc_not_remove(X).
 

/*
for tail recursive optimize code 
now ignore
*/
pass1(X) :-
	write(user_output,'pass1'),
    nl(user_output),
    abolish(pred_data/2),
    assert(pred_data(dummy,-1)),
    reconsult(X),
    pass1_analize.

pass1_analize :-
    n_reconsult_predicate(P),
    analize(P),
    fail.
pass1_analize.

/*
pass2 generate each clause or predicate code.
and write to <filename>.c
when all code is generated, close file and abolish optimizable/1
*/
pass2(X) :-
	write(user_output,'pass2'),
    nl(user_output),
	n_filename(X,F),
    atom_concat(F,'.c',Cfile),
	tell(Cfile),
	write('#include "jump.h"'),nl,
    gen_c_pred,
    gen_c_exec,
    abolish(pred_data/2),
    n_reconsult_abolish,
    told.

/*
when OS is Linux
system builtin predicate invoke GCC
gcc -O3 -w -shared -fPIC -o <filenam>.c <filename>.o <option>
*/
invoke_gcc(X) :-
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

invoke_gcc_not_remove(X) :-
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
gen_c_pred :-
    gen_pred,
    gen_c_def.

% generate all predicate code
gen_pred :-
    n_reconsult_predicate(P),
    not(n_dynamic_predicate(P)),
    gen_pred1(P),
    fail.
gen_pred :-
    n_reconsult_predicate(P),
    n_dynamic_predicate(P),
    gen_dynamic(P),
    fail.
gen_pred.

gen_pred1(P) :-
    pred_data(P,type1),
    gen_tail_pred(P),!.
gen_pred1(P) :-
    pred_data(P,type2),
    gen_tail_pred(P),!.    
gen_pred1(P) :-
    not(pred_data(P,type1)),
    gen_a_pred(P),!.

% define compiled predicate
gen_c_def :-
	write('void init_tpredicate(void){'),
    gen_c_def1,
    write('}'),nl.

gen_c_def1 :-
    n_reconsult_predicate(P),
    not(n_dynamic_predicate(P)),
	gen_def(P),
    fail.
gen_c_def1.


% generate deftpred for normal predicate
gen_def(P) :-
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
gen_def(P) :-
    n_defined_userop(P),
	write('(deftinfix)("'),
    write(P),
    write('",'),
    write('b_'),
    n_atom_convert(P,P1),
    write(P1),
    write(','),
    current_op(W,S,P),
    spec_to_c(S,S1),
    write(W),
    write(','),
    write(S1),
    write(');'),
    nl,!.


spec_to_c(fx,'FX').
spec_to_c(fy,'FY').
spec_to_c(xfx,'XFX').
spec_to_c(xfy,'XFY').
spec_to_c(yfx,'YFX').
spec_to_c(xf,'XF').
spec_to_c(yf,'YF').
spec_to_c(fx_xfx,'FX_XFX').
spec_to_c(fy_xfx,'FY_XFX').
spec_to_c(fx_yfx,'FX_YFX').
spec_to_c(fy_yfx,'FY_YFX').
spec_to_c(fx_xf,'FX_XF').
spec_to_c(fx_yf,'FX_YF').
spec_to_c(fy_xf,'FY_XF').
spec_to_c(fy_yf,'FY_YF').


/*
last C code to make direct execute
void init_declare(void){
    execute code...
}
*/
gen_c_exec :-
	write('void init_declare(void){'),
    gen_dyn_exec,
    gen_exec,
    write('}').

/*
parts for gen_predicate
C type declare.
int_b_foo(int arglist, int rest);
*/
gen_type_declare(P) :-
	write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest, int th);'),
    nl.
/*
C variable declare.
generate following code
int(int arg1,arg2,...,argN){
int arg1,arg2 ... argN,body,save1,save2;

*/
gen_var_declare(P) :-
    write('int '),
    n_arity_count(P,L),
    max_list(L,E),
    gen_var_declare1(1,E),
    n_generate_all_variable(P,V),
    gen_all_var(V),
    write('n,body,save1,save2,goal,cont,res;'),nl,!.

max_list([N],N).
max_list([X|Xs],X) :-
    max_list(Xs,Y),
    X >= Y.
max_list([X|Xs],Y) :-
    max_list(Xs,Y),
    X < Y.

% arg1,arg2,...argN
gen_var_declare1(S,E) :-
	S > E.
gen_var_declare1(S,E) :-
	write(arg),
    write(S),
    write(','),
    S1 is S+1,
    gen_var_declare1(S1,E).


/*
generate predicate for not tail recursive
int b_<name>(int arglist, int rest){
int varX,varY,...
save2 = Jget_sp(th);
if(n == N){
    ...main code...
}
return(NO);
}
*/
gen_a_pred(P) :-
	atom_concat('compiling ',P,M),
    write(user_output,M),
    nl(user_output),
    gen_type_declare(P),
	write('int b_'),
    n_atom_convert(P,P1),
    write(P1),
    write('(int arglist, int rest, int th){'),nl,
    gen_var_declare(P),
    write('save2 = Jget_sp(th);'),nl,
    write('n = Jlength(arglist);'),nl,
    n_arity_count(P,L),
    gen_a_pred1(P,L),
    write('}'),nl.

% pred1,pred2,...,predN
gen_a_pred1(P,[]) :-
    nl,
    write('Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("'),
    write(P),
    write('"),arglist);'),nl,
	write('return(NO);').

gen_a_pred1(P,[L|Ls]) :-
	gen_a_pred2(P,L),
    gen_a_pred1(P,Ls).

% if(n == N){...}
gen_a_pred2(P,N) :-
	write('if(n == '),
    write(N),
    write('){\n'),
    gen_a_pred3(P,N),
    write('return(NO);}'),!.

% select all clauses that arity is N
gen_a_pred3(P,N) :-
    gen_var_assign(1,N),
	n_clause_with_arity(P,N,C),
    gen_a_pred4(C).

% arg1 = Jnth(arglist,1);
% arg2 = Jnth(arglist,2);
% argn = Jnth(artglist,n);
gen_var_assign(S,E) :-
	S > E.
gen_var_assign(S,E) :-
	write(arg),
    write(S),
    write(' = Jnth(arglist,'),
    write(S),
    write(');\n'),
    S1 is S+1,
    gen_var_assign(S1,E).


% generate each clause in CPS
gen_a_pred4([]).
gen_a_pred4([C|Cs]) :-
	n_variable_convert(C,X),
    n_generate_variable(X,V),
    gen_var(V),
    gen_a_pred5(X),
    gen_a_pred4(Cs).


/*
save1 = Jget_wp(th);
save2 = jget_sp(th);
if( )... head
{body = }
...
*/


/*
   
*/
% clause
gen_a_pred5((Head :- Body)) :-
    write('save1 = Jget_wp(th);'),nl,
	gen_head(Head),
    gen_body(Body,0).

% predicate with no arity
gen_a_pred5(P) :-
	n_property(P,predicate),
    functor(P,_,0),
    not(n_dynamic_predicate(P)),
    write('return(Jexec_all(rest,Jget_sp(th),th));'),nl.

gen_a_pred5(P) :-
    n_property(P,predicate),
    functor(P,_,0),
    n_dynamic_predicate(P),
    write('Jmakepred("'),
    write(P),
    write(')'),nl.

% predicate
gen_a_pred5(P) :-
	n_property(P,predicate),
    P =.. [P1|_],
    not(n_dynamic_predicate(P1)),
    write('save1 = Jget_wp(th);'),nl,
	gen_head(P),
    write('if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.

gen_a_pred5(P) :-
    n_property(P,predicate),
    P =.. [P1|_],
    n_dynamic_predicate(P),
    write('Jwcons(Jmakepred("'),
    write(P1),
    write('"),'),
    gen_argument(L),
    write(')').



% user ope
gen_a_pred5(P) :-
	n_property(P,userop),
    write('save1 = Jget_wp(th);'),nl,
	gen_head(P),
    write('if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.



% varA,varB,...
gen_all_var([]).
gen_all_var([L|Ls]) :-
    n_atom_convert(L,L1),
	write(L1),
    write(','),
    gen_all_var(Ls).

% varA = Jmakevariant(th), varB = Jmakevariant(th);
gen_var([]).
gen_var([L|Ls]) :-
    n_atom_convert(L,L1),
    write(L1),
    write(' = Jmakevariant(th);'),nl,
    gen_var(Ls).



/*
body for compiler
foo(X),bar(X),boo(X).

if(unify(....)){
    body = ...;
    if(Jexec_all(body,Jget_sp(th),th) == YES)
        return(YES)};

Junbind(save2,th);
Jset_wp(save1,th);


*/


% disjunction
gen_body(((X1;X2);Y),N) :-
    write('{dp['),write(N),write(']=Jget_sp(th);'),nl,
    N1 is N+1,
    gen_body(X,N1),
    write('Junbind(dp['),write(N),write('],th);'),nl,
    write('body = '),nl,
    gen_body1(Y,N),
    write(';'),nl,
    write('if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(dp['),write(N),write('],th);}'),nl.


gen_body((X;(Y1;Y2)),N) :-
    write('{dp['),write(N),write(']=Jget_sp(th);'),nl,
    write('body = '),nl,
    gen_body1(X,N),
    write(';'),nl,
    write('if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(dp['),write(N),write('],th);'),nl,
    N1 is N+1,
    gen_body((Y1;Y2),N1),
    write('Junbind(dp['),write(N),write('],th);}'),nl.


gen_body((X;Y),N) :-
    n_has_cut(X),
    write('{dp['),write(N),write(']=Jget_sp(th);'),nl,
    gen_body(X,N),
    write('Junbind(dp['),write(N),write('],th);'),nl,
    write('body = '),nl,
    gen_body1(Y,N),
    write(';'),nl,
    write('if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(dp['),write(N),write('],th);}'),nl.

gen_body((X;Y),N) :-
    write('{dp['),write(N),write(']=Jget_sp(th);'),nl,
    write('body = '),nl,
    gen_body1(X,N),
    write(';'),nl,
    write('if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(dp['),write(N),write('],th);'),nl,
    write('body = '),nl,
    gen_body1(Y,N),
    write(';'),nl,
    write('if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(dp['),write(N),write('],th);}'),nl.


% has cut
gen_body(X,N) :-
    n_has_cut(X),
    n_before_cut(X,X1),
    n_after_cut(X,X2),
    not(n_has_cut(X2)),
    write('{body = '),
    gen_body1(X1,N),
    write(';'),nl,
    write('if((res=Jexec_all(body,Jget_sp(th),th)) == YES)'),nl,
    gen_after_body(X2,N),
    write('}'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.

% nested has cut
gen_body(X,N) :-
    n_has_cut(X),
    n_before_cut(X,X1),
    n_after_cut(X,X2),
    n_has_cut(X2),
    write('{body = '),
    gen_body1(X1,N),
    write(';'),nl,
    write('if(Jexec_all(body,Jget_sp(th),th) == YES)'),nl,
    gen_body(X2,N),
    write('}'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl.
    
    
% conjunction 
gen_body(X,N) :-
    write('{body = '),
    gen_body1(X,N),
    write(';'),nl,
    write('if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);}'),nl.
    
gen_after_body(X,N) :-
    write('{body = '),
    gen_body1(X,N),
    write(';'),nl,
    write('if((Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(save2,th);'),nl,
    write('Jset_wp(save1,th);'),nl,
    write('return(NO);}'),nl.


gen_body1([],N) :-
    write('NIL').

gen_body1((D1;D2),N) :-
	write('Jwlist3(Jmakeope(";"),'),
	gen_body1(D1,N),
    write(','),
    gen_body1(D2,N),
    write(',th)').
gen_body1(((D1;D2),Xs),N) :-
    write('Jwlist3(Jmakeope(","),'),
	write('Jwlist3(Jmakeope(";"),'),
	gen_body1(D1,N),
    write(','),
    gen_body1(D2,N),
    write(',th),'),
    gen_body1(Xs,N),
    write(',th)').
    
gen_body1((X,Xs),N) :-
	write('Jwlist3(Jmakeope(","),'),
	gen_a_body(X),
    write(','),
    gen_body1(Xs,N),
    write(',th)').

gen_body1(X,N) :-
	gen_a_body(X).

/*
generate one operation,user,builtin or compiled predicate.
when except of above type, invoke error.
*/
gen_a_body((X;Xs)) :-
	write('Jwlist3(Jmakeope(";"),'),
	gen_a_body(X),
    write(','),
    gen_body1(Xs),
    write(',th)').
% defined predicate will become compiled predicate
gen_a_body(X) :-
    n_defined_predicate(X),
    functor(X,P,0),
    not(n_dynamic_predicate(P)),
    write('Jmakecomp("'),
    write(P),
    write('")').

gen_a_body(X) :-
    n_defined_predicate(X),
    functor(X,P,0),
    n_dynamic_predicate(P),
    write('Jmakepred("'),
    write(P),
    write('")').

% defined predicate will become compiled predicate
gen_a_body(X) :-
    n_defined_predicate(X),
    X =.. [P|L],
    not(n_dynamic_predicate(P)),
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_body(X) :-
    n_property(X,predicate),
    X =.. [P|L],
    write('Jwcons(Jmakepred("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
% atom builtin e.g. nl fail
gen_a_body(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).
gen_a_body(X) :-
    n_property(X,builtin),
    X =.. [P|L],
    n_findatom(P,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    gen_argument(L),
    write(',th)').
gen_a_body(X) :-
    n_property(X,operation),
    gen_body1(X).
gen_a_body(X) :-
    n_property(X,compiled),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_body(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),
    write(P),
    write('")').
gen_a_body(X) :-
    n_defined_userop(X),
    X =.. [P|L],
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_body(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jwcons(Jmakeuser("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(',th)').
gen_a_body(X) :-
    atom(X),
    n_dynamic_predicate(X),
	write('Jmakepred("'),
    write(X),
    write('")').
gen_a_body(X) :-
    invoke_error('illegal body ',X).


/*
generate_unify of head
e.g.  foo(X) -> if(Junify(arg1,varX,th) == YES)
anoymous variable generate 1 as true.
e.g   foo(_) -> if(1)
*/

gen_head(X) :-
    functor(X,_,0).
gen_head(X) :-
    X =.. [_|Y],
    write('if('),
    gen_head1(Y,1),
    write(')\n').

gen_head1([],_) :-
    write(1).

gen_head1([[]|Xs],N) :-
    write('Junify_nil('),
    write('arg'),
    write(N),
    write(','),
    write(th),
    write(') == YES && '),
    N1 is N + 1,
    gen_head1(Xs,N1).

gen_head1([X|Xs],N) :-
    n_compiler_anoymous(X),
    N1 is N + 1,
    gen_head1(Xs,N1).  

gen_head1([X|Xs],N) :-
    n_compiler_variable(X),
    write('Junify_var('),
    gen_a_argument(X),
    write(',arg'),
    write(N),
    write(','),
    write(th),
    write(') == YES && '),
    N1 is N + 1,
    gen_head1(Xs,N1). 

gen_head1([X|Xs],N) :-
    atomic(X),
    write('Junify_const('),
    gen_a_argument(X),
    write(',arg'),
    write(N),
    write(','),
    write(th),
    write(') == YES && '),
    N1 is N + 1,
    gen_head1(Xs,N1). 

gen_head1([X|Xs],N) :-
    write('Junify('),
    gen_a_argument(X),
    write(',arg'),
    write(N),
    write(','),
    write(th),
    write(') == YES && '),
    N1 is N + 1,
    gen_head1(Xs,N1).


/*
generate evauation code
e.g.  X is 1+2.  X == 3*4.
*/
eval_form([]) :-
	write('NIL').
eval_form([X]) :-
	write('Jmakeconst("'),
    write(X),
    write('")').
eval_form(pi) :-
	write('Jmakestrflt("3.14159265358979")').
eval_form(random) :-
	write('Jrandom()').    
eval_form(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
eval_form(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
eval_form(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
eval_form(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
eval_form(X) :-
	atom(X),
    n_compiler_variable(X),
    n_atom_convert(X,X1),
    write('Jderef('),
    write(X1),
    write(','),
    write(th),
    write(')').
eval_form(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
eval_form(X) :-
    list(X),
    gen_a_argument(X).
eval_form(X + Y) :-
	write('Jplus('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X - Y) :-
	write('Jminus('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X * Y) :-
	write('Jmult('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X / Y) :-
	write('Jdivide('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X//Y) :-
	write('Jdiv('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X ^ Y) :-
	write('Jexpt('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X mod Y) :-
	write('Jmod('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(sin(X)) :-
	write('Jsin('),
    eval_form(X),
    write(',th)').
eval_form(asin(X)) :-
	write('Jasin('),
    eval_form(X),
    write(',th)').
eval_form(cos(X)) :-
	write('Jcos('),
    eval_form(X),
    write(',th)').
eval_form(acos(X)) :-
	write('Jacos('),
    eval_form(X),
    write(',th)').
eval_form(tan(X)) :-
	write('Jtan('),
    eval_form(X),
    write(',th)').
eval_form(atan(X)) :-
	write('Jatan('),
    eval_form(X),
    write(',th)').
eval_form(exp(X)) :-
	write('Jexp('),
    eval_form(X),
    write(',th)').
eval_form(log(X)) :-
	write('Jlog('),
    eval_form(X),
    write(',th)').
eval_form(ln(X)) :-
	write('Jln('),
    eval_form(X),
    write(',th)').

eval_form(X << Y) :-
	write('Jleftshift('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X >> Y) :-
	write('Jrightshift('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').

eval_form(X /\ Y) :-
	write('Jlogicaland('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(X \/ Y) :-
	  write('Jlogicalor('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(',th)').
eval_form(\ X) :-
	write('Jcomplement('),
    eval_form(X),
    write(',th)').
eval_form(randi(X)) :-
	write('Jrandi('),
    eval_form(X),
    write(',th)').
eval_form(round(X,Y)) :-
	  write('Jround('),
    eval_form(X),
    eval_form(Y),
    write(',th)').


/*
generate arguments for pred ope fun.
arguments are provided by list.
e.g. [3,14,A,foo(2)]
*/
gen_argument([]) :-
    write('NIL').
gen_argument([X|Xs]) :-
	write('Jwcons('),
    gen_a_argument(X),
    write(','),
    gen_argument(Xs),
    write(',th)').
/*
generate one argument
there are all type of prolog object
*/
gen_a_argument([]) :-
	write('NIL').
gen_a_argument(X) :-
	n_compiler_variable(X),
    n_atom_convert(X,X1),
    write(X1).
gen_a_argument(pi) :-
	write('Jmakestrflt("3.14159265358979")').
gen_a_argument(X) :-
	n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
gen_a_argument(X) :-
	float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	string(X),
    write('Jmakestr("'),
    write(X),
    write('")').
gen_a_argument(X) :-
    n_defined_predicate(X),
    functor(X,Y,0),
    write('Jmakecomp("'),
    write(Y),
    write('")').
gen_a_argument(X) :-
    n_defined_predicate(X),
    X =.. [Y|Z],
    write('Jwcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,predicate),
    X =.. [Y|Z],
    write('Jwcons(Jmakepred("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,builtin),
    functor(X,Y,0),
    n_findatom(Y,builtin,A),
    write(A).
gen_a_argument(X) :-
    n_property(X,builtin),
    X =.. [Y|Z],
    n_findatom(Y,builtin,A),
	write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,compiled),
    functor(X,Y,0),
    n_findatom(Y,compiled,A),
    write(A).
gen_a_argument(X) :-
    n_property(X,compiled),
    X =.. [Y|Z],
    n_findatom(Y,compiled,A),
    write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,operation),
    functor(X,Y,0),
    n_findatom(Y,operator,A),
    write(A).
gen_a_argument(X) :-
    n_property(X,operation),
    X =.. [Y|Z],
    n_findatom(Y,operator,A),
	write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(',th)').
%predicate indicator  e.g. foo/1
gen_a_argument(A/B) :-
    atom(A),
    integer(B),
    write('Jwlist3(Jmakefun("/"),Jmakepred("'),
    write(A),
    write('"),'),
    gen_a_argument(B),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,function),
    functor(X,F,0),
    write('Jmakefun("'),
    write(F),
    write('")').
gen_a_argument(X) :-
    n_property(X,function),
    X =.. [F|Z],
	write('Jwcons(Jmakefun("'),
    write(F),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
    n_property(X,userop),
    functor(X,Y,0),
    write('Jmakeuser("'),
    write(X),
    write('")').
gen_a_argument(X) :-
    n_property(X,userop),
    X =.. [Y|Z],
	write('Jwcons(Jmakeuser("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(',th)').
gen_a_argument(X) :-
	atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	list(X),
    gen_argument_list(X).
gen_a_argument(X) :-
    invoke_error('illegal argument ',X).

gen_argument_list([X|Xs]) :-
	write('Jwlistcons('),
    gen_a_argument(X),
    write(','),
    gen_a_argument(Xs),
    write(','),
    write(th),
    write(')').

/*
assert dynamic predicate
:- dynamic(foo/1)
foo(X) :- ...
dyn = Jcons(Jmakesys(":-"),...;
Jadd_data(dyn); 
*/

gen_dynamic(P) :-
    n_arity_count(P,L),
    write('void '),
    write(P),
    write('(void){'),
    gen_dynamics(P,L),
    write('}'),!.

gen_dynamics(P,[]).
gen_dynamics(P,[L|Ls]) :-
    gen_dyn(P,L),
    gen_dynamics(P,Ls).

gen_dyn(P,A) :-
    n_clause_with_arity(P,A,C),
    n_variable_convert(C,X),
    gen_dyn1(X).


gen_dyn1([]).
gen_dyn1([X|Xs]) :-
    n_property(X,operation),
    write('dynamic_clause = '),
    gen_dyn2(X),
    write(';'),nl,
    write('Jadd_dynamic(dynamic_clause);'),nl,
    gen_dyn1(Xs).
gen_dyn1([X|Xs]) :-
    n_property(X,predicate),
    write('dynamic_clause = '),
    gen_dyn2(X),
    write(';'),nl,
    write('Jadd_dynamic(dynamic_clause);'),nl,
    gen_dyn1(Xs).

gen_dyn2([]).
gen_dyn2((X :- Y)) :-
    write('Jlist3(Jmakeope(":-"),'),
    gen_dyn2(X),
    write(','),
    gen_dyn2(Y),
    write(')').

gen_dyn2((X,Y)) :-
    write('Jlist3(Jmakeope(","),'),
    gen_dyn2(X),
    write(','),
    gen_dyn2(Y),
    write(')').

gen_dyn2((X;Y)) :-
    write('Jlist3(Jmakeope(";")),'),
    gen_dyn2(X),
    write(','),
    gen_dyn2(Y),
    write(')').
    
gen_dyn2(X) :-
    compound(X),
    n_property(X,predicate),
    X =.. [P|L],
    write('Jcons(Jmakepred("'),
    write(P),
    write('"),'),
    gen_dyn2_argument(L),
    write(')').

gen_dyn2(X) :-
    atom(X),
    n_dynamic_predicate(X),
    write('Jmakepred("'),
    write(X),
    write('")').

gen_dyn2(X) :-
    n_property(X,builtin),
    functor(X,P,0),
    n_findatom(P,builtin,A),
    write(A).
gen_dyn2(X) :-
    n_property(X,builtin),
    X =.. [P|L],
    n_findatom(P,builtin,A),
    write('Jcons('),
    write(A),
    write(','),
    gen_dyn2_argument(L),
    write(')').
gen_dyn2(X) :-
    n_property(X,operation),
    X =.. [P|L],
    n_findatom(P,operator,A),
    write('Jcons('),
    write(A),
    write(','),
    gen_dyn2_argument(L),
    write(')').
gen_dyn2(X) :-
    n_property(X,userop),
    functor(X,P,0),
    write('Jmakeuser("'),
    write(P),
    write('")').
gen_dyn2(X) :-
    n_property(X,userop),
    X =.. [P|L],
    write('Jcons(Jmakeuser("'),
    write(P),
    write('"),'),
    gen_dyn2_argument(L),
    write(')').
gen_dyn2(X) :-
    n_compiler_variable(X),
    write('Jmakevar("'),
    write(X),
    write('")').
gen_dyn2(X) :-
    n_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
gen_dyn2(X) :-
    n_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
gen_dyn2(X) :-
    integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
gen_dyn2(X) :-
    float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
gen_dyn2(X) :-
    list(X),
    gen_dyn2_list(X).
gen_dyn2(X) :-
    atom(X),
	write('Jmakepred("'),
    write(X),
    write('")').
gen_dyn2(X) :-
    string(X),
	write('Jmakestr("'),
    write(X),
    write('")').
gen_dyn2(X) :-
    invoke_error('illegal clause ',X).

gen_dyn2_argument([]) :-
    write('NIL').
gen_dyn2_argument([X|Xs]) :-
    write('Jcons('),
    gen_dyn2(X),
    write(','),
    gen_dyn2_argument(Xs),
    write(')').

gen_dyn2_list([]) :-
    write('NIL').
gen_dyn2_list([L|Ls]) :-
    write('Jlistcons('),
    gen_dyn2(L),
    write(','),
    gen_dyn2_list(Ls),
    write(')').

/*
invoke error
display error message and error code.
and close output file, finaly abort to REPL
*/
invoke_error(Message,Code) :-
	write(user_output,Message),
    write(user_output,Code),nl(user_output),
    told,
    abort.

/* generate execute definition of dynamic clause*/
gen_dyn_exec :-
    write('int body,th; th=0;'),nl,
    n_get_dynamic(X),
    gen_dyn_exec1(X).

gen_dyn_exec1([]).
gen_dyn_exec1([L|Ls]) :-
    write(L),
    write('();'),nl,
    gen_dyn_exec1(Ls).



/*
e.g. :- op(...)
generate execution 
*/
gen_exec :-
    n_get_execute(X),
    gen_exec1(X).

gen_exec1([]).
gen_exec1([L|Ls]) :-
    gen_exec2(L),
    nl,
    gen_exec1(Ls).


gen_exec2(X) :-
    write('body = '),
    gen_body1(X,0),
    write(';'),nl,
    write('Jexec_all(body,Jget_sp(th),th);'),!.

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
% anoymous variable ignore
gen_tail_var1(X,L) :-
    n_compiler_anoymous(X).
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

% ignore anoymous
gen_tail_head2(X,L) :-
    n_compiler_anoymous(X).
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


