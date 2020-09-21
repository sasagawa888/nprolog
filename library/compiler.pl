/* template. generate c file as following

#include "jump.h"
int b_<name>(int arglist, int rest);
int b_<name>(int arglist, int rest){
int arg1,arg2,arg4,varX,varY,varZ,...,save1,save2,body;
save2 = Jget_sp();
if(n == 2){
    arglist = Jderef(arglist);
    arg1 = Jcar(arglist);
    arg2 = Jcadr(arglist);
  
    % first clause
    varX = Jmakevariant();
    varZ = Jmakevariant();
    varY = Jmakevariant();
    save1 = Jget_wp();
    if(Junify(cdr(<head>),arglist) == YES){
        body =Jwcons(119,Jwcons(varX,Jwcons(varY,NIL)));
        if(Jpove_all(Jaddtail_body(rest,body),save2,0) == YES)
            return(YES);
    }
    Junbind(save2);
    Jset_wp(save1);}

    % second clause
    varX1 = Jmakevariant();
    varY1 = Jmakevariant();
    varZ1 = Jmakevariant();
    ...
    save1 = Jget_wp();
    if(Junify(cdr(<head>),arglist) == YES){
        body = Jwlist3(Jmakeope(","),Jwcons(173,Jwc ....)));
        if(Jprove_all(Jaddtail_body(rest,body),save2,0) == YES)
            return(YES);
    }
    Junbind(save2);
    Jset_wp(save1);

    return(NO);
}

% initialize predicate
void init_tpredicate(void){(deftpred)("<name>",b_<name>);
}
% set execution code
void init_declare(void){
  ...execution 
}

*/


%main
compile_file(X) :-
    jump_pass1(X),
    jump_pass2(X),
    jump_invoke_gcc(X).

compile_file1(X) :-
    jump_invoke_gcc(X).

/*
for tail recursive optimize code 
now ignore
*/
jump_pass1(X) :-
	write(user_output,'pass1'),
    nl(user_output),
    reconsult(X).

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
    atom_concat('gcc -O3 -w -shared -fPIC -o ',Files,Sys),
    shell(Sys).


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
    jump_gen_a_pred(P),
    fail.
jump_gen_pred.

% define compiled predicate
jump_gen_c_def :-
	write('void init_tpredicate(void){'),
    jump_gen_c_def1,
    write('}').

jump_gen_c_def1 :-
    n_reconsult_predicate(P),
	jump_gen_def(P),
    fail.
jump_gen_c_def1.


% generate deftpred for normal predicate
jump_gen_def(P) :-
	write('(deftpred)("'),
    write(P),
    write('",'),
    write('b_'),
    n_atom_convert(P,P1),
    write(P1),
    write(');'),
    nl.

% generate deftpred for optimized predicate
jump_gen_defsys(P) :-
	write('(deftsys)("'),
    write(P),
    write('",'),
    write('b_'),
    n_atom_convert(P,P1),
    write(P1),
    write(');'),
    nl.

/*
last C code to make direct execute
void init_declare(void){
    execute code...
}
*/
jump_gen_c_exec :-
	write('void init_declare(void){'),
    %jump_gen_exec,
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
	n_arity_count(P,L),
    write('int '),
    n_generate_all_variable(P,V),
    jump_gen_all_var(V),
    write('n,body,save1,save2;'),nl,!.

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
    write('n = Jlength(arglist);'),
    nl,
    n_arity_count(P,L),
    jump_gen_a_pred1(P,L),
    write('}'),nl.

% pred1,pred2,...,predN
jump_gen_a_pred1(P,[]) :-
	write('return(NO);').

jump_gen_a_pred1(P,[L|Ls]) :-
	jump_gen_a_pred2(P,L),
    jump_gen_a_pred1(P,Ls).

% if(n == N){...}
jump_gen_a_pred2(P,N) :-
	write('if(n == '),
    write(N),
    write('){'),
    jump_gen_a_pred3(P,N),
    write('}'),!.

% select all clauses that arity is N
jump_gen_a_pred3(P,N) :-
	n_clause_with_arity(P,N,C),
    jump_gen_a_pred4(C).

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
    write('if(Jprove_all(rest,Jget_sp(),0) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl.


% varA,varB,...
jump_gen_all_var([]).
jump_gen_all_var([L|Ls]) :-
	write(L),
    write(','),
    jump_gen_all_var(Ls).

% varA = Jmakevariant(), varB = Jmakevariant();
jump_gen_var([]).
jump_gen_var([L|Ls]) :-
    n_compiler_anoymous(L),
    jmp_gen_var(Ls).
jump_gen_var([L|Ls]) :-
    write(L),
    write(' = Jmakevariant();'),nl,
    jump_gen_var(Ls).



/*
body for compiler
foo(X),bar(X),boo(X).

if(unify(....)){
    body = ...;
    if(Jprove_all(body,Jget_sp(),0) == YES)
        return(YES)};

Junbind(save2);
Jset_wp(save1);


*/
jump_gen_body(X) :-
    write('{body = '),
    jump_gen_body1(X),
    write(';'),nl,
    write('if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)'),nl,
    write('return(YES);}'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl,!.

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
    functor(X,P,_),
    n_argument_list(X,L),
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    n_property(X,predicate),
    functor(X,P,_),
    n_argument_list(X,L),
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
    functor(X,P,_),
    n_argument_list(X,L),
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
    functor(X,P,_),
    n_argument_list(X,L),
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    jump_gen_argument(L),
    write(')').
jump_gen_a_body(X) :-
    n_property(X,userop),
    functor(X,P,0),
    n_argument_list(X,L),
    write('Jmakeuser("'),
    write(P),
    write('")').
jump_gen_a_body(X) :-
    n_property(X,userop),
    functor(X,P,_),
    n_argument_list(X,L),
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
e.g.  foo(X) -> if(Junify(arg1,varX))
anoymous variable generate 1 as true.
e.g   foo(_) -> if(1)
*/

jump_gen_head(X) :-
    functor(X,_,0).
jump_gen_head(X) :-
    n_argument_list(X,Y),
    write('if(Junify('),
    jump_gen_argument(Y),
    write(',arglist) == YES)'),nl.


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
    write('Jderef('),
    write(X),
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
    n_compiler_anoymous(X),
    write('ANOYVAR').
jump_gen_a_argument(X) :-
	n_compiler_variable(X),
    write(X).
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
    n_defined_predicate(X),
    functor(X,Y,_),
    n_argument_list(X,Z),
    write('Jwcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    jump_gen_argument(Z),
    write(')').
jump_gen_a_argument(X) :-
    n_property(X,predicate),
    functor(X,Y,_),
    n_argument_list(X,Z),
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
    functor(X,Y,_),
    n_findatom(Y,builtin,A),
    n_argument_list(X,Z),
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
    functor(X,Y,_),
    n_findatom(Y,compiled,A),
    n_argument_list(X,Z),
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
    functor(X,Y,_),
    n_findatom(Y,operator,A),
    n_argument_list(X,Z),
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
    functor(X,F,_),
    n_argument_list(X,Z),
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
    functor(X,Y,_),
    n_argument_list(X,Z),
	write('Jwcons(Jmakeuser("'),
    write(Y),
    write('"),'),
    jump_gen_a_argument(Z),
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

