:- module(compiler).
:- export([compile_file/1,invoke_gcc/1]).
:- end_module(compiler).


:- body(compiler).

%main
compile_file(X) :-
    assert(optimizable(0)),
    pass1(X),
    pass2(X),
    abolish(compiler_optimizable/1),
    invoke_gcc(X).


/*
read prolog code for compile by reconsult/1
o_recondult_predicate/1 return predicate name as list.
[foo,bar,boo ...]
tail_optimize/1 check a predicate if it is tail call optimizable.
if is is optimazable , assert optimizable/1 e.g. optimizable(foo).
pass1 check all predicate by fail repeat.
*/
pass1(X) :-
	  write(user_output, 'pass1'),
    nl(user_output),
    reconsult(X),
    o_reconsult_predicate(P),
    tail_optimize(P),
    assert(optimizable(P)),
    fail.
pass1(X).


/*
pass2 generate each clause or predicate code.
and write to <filename>.c
when all code is generated, close file and abolish optimizable/1
*/
pass2(X) :-
	  write(user_output,'pass2'),
    nl(user_output),
	  o_filename(X,F),
    atom_concat(F,'.c',Cfile),
	  open(Cfile,write,S,[type(text)]),
    set_output(S),
	  write('#include "jump.h"'),nl,
    gen_c_macro,
	  o_reconsult_predicate_list(L),
	  gen_c_pred(L),
    gen_c_def(L),
    gen_c_exec,
    close(S),
    set_output(user_output).


/*
when OS is Windows
system builtin predicate invoke GCC
gcc -O3 -shared -o <filenam>.c <filename>.o <option>
*/
invoke_gcc(X) :-
	  o_self_introduction(windows),
	  write(user_output,'invoke gcc'),
    nl(user_output),
	  o_filename(X,F),
    o_c_option(O),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -shared -o ',Files,Sys1),
    atom_concat(Sys1,O,Sys),
    system(Sys).
/*
when OS is Linux
system builtin predicate invoke GCC
gcc -O3 -w -shared -fPIC -o <filenam>.c <filename>.o <option>
*/
invoke_gcc(X) :-
	  o_self_introduction(linux),
	  write(user_output,'invoke GCC'),
    nl(user_output),
	  o_filename(X,F),
    o_c_option(O),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -w -shared -fPIC -o ',Files,Sys1),
    atom_concat(Sys1,O,Sys),
    system(Sys).

invoke_gcc(X) :-
    o_self_introduction(openbsd),
    write(user_output,'invoke GCC'),
    nl(user_output),
    o_filename(X,F),
    o_c_option(O),
    atom_concat(F,'.c ',Cfile),
    atom_concat(F,'.o ',Ofile),
    atom_concat(Ofile,Cfile,Files),
    atom_concat('gcc -O3 -w -shared -fPIC -o ',Files,Sys1),
    atom_concat(Sys1,O,Sys),
    system(Sys).

/*
for C wrapper
#include #define macro
c_include(' ... '). --> #include ...
c_define(' ... ').  --> #define  ...
c_global(' ... ').  --> on top level generate ...
*/gen_c_macro :-
	  o_c_include(I),
    gen_c_macro1(I),
	  o_c_define(D),
    gen_c_macro2(D),
    o_c_global(G),
    gen_c_macro3(G).

% #include macro
gen_c_macro1([]).
gen_c_macro1([L|Ls]) :-
	  write('#include '),
    write(L),nl,
    gen_c_macro1(Ls).

% #define macro
gen_c_macro2([]).
gen_c_macro2([[X|Y]|Ls]) :-
	  write('#define '),
    write(X),
    write(' '),
    write(Y),
    gen_c_macro2(Ls).

%global declare
gen_c_macro3([]).
gen_c_macro3([L|Ls]) :-
	  write(L),nl,
    gen_c_macro3(Ls).

/*
generate C code for predicate or clause.
They are provided by list.
e.g. [foo,bar,boo]
generate each predicate to make compiled pred
*/
gen_c_pred([]).
%when declare dynamic, not compile
gen_c_pred([P|Ps]) :-
	  o_dynamic_check(P),
    gen_c_pred(Ps).
%when predicate is tail call optimizable
gen_c_pred([P|Ps]) :-
    optimizable(P),
	  gen_type_declare(P),
    gen_tail_pred(P),
    gen_c_pred(Ps).
%normal predicate
gen_c_pred([P|Ps]) :-
	  gen_type_declare(P),
    gen_pred(P),
    gen_c_pred(Ps).

% code for C to define compiled predicate
gen_c_def(L) :-
	  write('void init_tpredicate(void){'),
    gen_c_def1(L),
    write('}').

gen_c_def1([]).
gen_c_def1([P|Ps]) :-
	  o_dynamic_check(P),
    gen_c_def1(Ps).
gen_c_def1([P|Ps]) :-
	  gen_def(P),
    gen_c_def1(Ps).

/*
last C code to make direct execute
void init_declare(void){
    dynamic code...
    execute code...
}
*/
gen_c_exec :-
	  write('void init_declare(void){'),
    gen_dynamic,
    gen_exec,
    write('}').
/*
dynamic predicate are entrusted to interpreter
dynamic predicate data are provided as list.
e.g. [foo/1,bar/2,boo/3...]
*/
gen_dynamic :-
	  o_get_dynamic(X),
    gen_dynamic1(X).

gen_dynamic1([]).
gen_dynamic1([P/A|Ls]) :-
	  gen_dynamic2(P,A),
    gen_dynamic1(Ls).
/*
when p has no module
Jset_car(Jmakepred("<predicate_name>"),NIL);
...predicate code for dynamic declare...
when P has module
Jset_car(Jmakepred("<predicate_name>"),NIL);
...predicate code for dynamic declare...
Jset_car(Jmakepred("<predicate_name>"),Jmakeconst("<module_name>"));
*/
gen_dynamic2(P,A) :-
    o_generated_module(P,[]),
	  write('Jset_car(Jmakepred("'),
    write(P),
    write('"),NIL);'),nl,
	  o_clause_with_arity(P,A,C),
    o_variable_convert(C,C1),
    gen_dynamic3(C1).

gen_dynamic2(P,A) :-
    o_generated_module(P,M),
	  write('Jset_car(Jmakepred("'),
    write(P),
    write('"),NIL);'),nl,
	  o_clause_with_arity(P,A,C),
    o_variable_convert(C,C1),
    gen_dynamic3(C1),
    write('Jset_var(Jmakepred("'),
    write(P),
    write('"),Jmakeconst("'),
    write(M),
    write('"));').

/*
for dynamic declare predicate
when predicate
Jexecute(...generated dynamic code1...);
Jexecute(...generated dynamic code2...);
...
when clause
Jexecute(Jlist3(Jmakeope(":-"),head_code1,body_code1)) ;
Jexecute(Jlist3(Jmakeope(":-"),head_code2,body_code2)) ;
...
*/
gen_dynamic3([]).
gen_dynamic3([L|Ls]) :-
	  o_property(L,predicate),
    write('Jexecute('),
    gen_org(L),
    write(');'),nl,
    gen_dynamic3(Ls).
gen_dynamic3([(H :- B)|Ls]) :-
    write('Jexecute(Jlist3(Jmakeope(":-"),'),
    gen_org(H),
    write(','),
    gen_org(B),
    write('));'),nl.
    gen_dynamic3(Ls).

/*
generate execute code for compiled function
e.g  :- ensuare_loaded('foo.pl')).
ignore dynamic declared predicate and C wraped code.
ignore module/1 export/1 import/1 import/2 body/1 end_module/1 end body/1
meta/1
*/
gen_exec :-
	  o_get_execute(X),
    gen_exec1(X).

gen_exec1([]).
gen_exec1([dynamic(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([c_include(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([c_define(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([c_option(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([c_global(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([module(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([export(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([import(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([import(X,Y)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([body(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([end_module(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([end_body(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([meta(X)|Ls]) :-
	  gen_exec1(Ls).
gen_exec1([L|Ls]) :-
	  write('Jexecute(Jlist2(Jmakeope(":-"),'),
    gen_a_argument(L),
    write('));'),nl,
    gen_exec1(Ls).
/*
parts for gen_predicate
C type declare.
int_b_foo(int nest, int n);
*/
gen_type_declare(P) :-
	  write('int b_'),
    o_atom_convert(P,P1),
    write(P1),
    write('(int nest, int n);'),
    nl.
/*
C variable declare.
generate following code
int(int arg1,arg2,...,argN){
int arg1,arg2 ... argN,body,save1,save2;
save2 = Jget_sp();

*/
gen_var_declare(P) :-
	  o_arity_count(P,L),
    max_element(L,M),
    write('int '),
    gen_var_declare1(1,M),
    o_generate_all_variable(P,V),
    gen_all_var(V),
    gen_cut_var(P),
    write('body,save1,save2;'),nl,
    write('save2 = Jget_sp();'),nl.


% for cut operater
% if clause has cut, add 'save4,save5' variable
gen_cut_var(P) :-
	  o_include_cut(P),
    write('save4,save5,').
gen_cut_var(P).

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
max element in list
this is used by gen_var_declare,for to find max arity
*/
max_element([L],L).
max_element([L|Ls],A) :-
	  max_element(Ls,A),
    L < A.
max_element([L|Ls],L).

/*
generate predicate for not tail recursive
int b_<name>(int nest, int n){
int varX,varY,...
if(n == N){
    ...main code...
}
return(NO);
}
*/
gen_pred(P) :-
	  atom_concat('compiling ',P,M),
    write(user_output,M),nl(user_output),
	  write('int b_'),
    o_atom_convert(P,P1),
    write(P1),
    write('(int nest, int n){'),
    nl,
    gen_var_declare(P),
    o_arity_count(P,L),
    gen_pred1(P,L),
    write('}'),nl.

% pred1,pred2,...,predN
gen_pred1(P,[]) :-
	  write('return(NO);').
    gen_pred1(P,[L|Ls]) :-
	  gen_pred2(P,L),
    gen_pred1(P,Ls).

% if(n == N){...}
gen_pred2(P,N) :-
	  write('if(n == '),
    write(N),
    write('){'),
    gen_receive_var(1,N),
    gen_pred3(P,N),
    write('}').

%select all clauses that arity is N
gen_pred3(P,N) :-
	  o_clause_with_arity(P,N,C),
    gen_pred4(C).

%generate each clause
gen_pred4([]).
gen_pred4([C|Cs]) :-
	  o_variable_convert(C,X),
    o_generate_variable(X,V),
    gen_var(V),
    gen_pred5(X),
    gen_pred4(Cs).

/*
save1 = Jget_wp();
If( )... head
{body = }
...
*/
%clause that has cut
gen_pred5((Head :- Body)) :-
    o_has_cut(Body),
    write('save1 = Jget_wp();'),nl,
	  gen_head(Head),
    gen_cut_body(Body).

%clause without cut
gen_pred5((Head :- Body)) :-
    write('save1 = Jget_wp();'),nl,
	  gen_head(Head),
    gen_body(Body).

% predicate with no arity
gen_pred5(P) :-
	  o_property(P,predicate),
    functor(P,_,0),
    write('return(YES);'),nl.

%CPS predicate
gen_pred5(P) :-
	  o_property(P,predicate),
    write('save1 = Jget_wp();'),nl,
	  gen_head(P),
    write('if(Jproceed(NIL,nest) == YES)'),nl,
    write('return(YES);'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl.


% varA,varB,...
gen_all_var([]).
gen_all_var([L|Ls]) :-
	  write(L),
    write(','),
    gen_all_var(Ls).

% varA = Jmakevariant(), varB = Jmakevariant();
gen_var([]).
gen_var([L|Ls]) :-
    o_compiler_anoymous(L),
    gen_var(Ls).
gen_var([L|Ls]) :-
    write(L),
    write(' = Jmakevariant();'),nl,
    gen_var(Ls).

/*
generate following argN code.
arg1 = Jderef(Jget_goal(2));
arg2 = Jderef(Jget_goal(3)); ...
if N=0 then not generate code.
*/
gen_receive_var(_,0).
gen_receive_var(S,N) :-
	  S > N.
gen_receive_var(S,N) :-
	  write('arg'),
    write(S),
    S1 is S + 1,
    write(' = Jderef(Jget_goal(' ),write(S1),write('));'),nl,
    %write('Jdisplay(arg'),write(S),write(');'),nl,
    gen_receive_var(S1,N).

/*
when generate body that has cut!
code is following format.
{body = ...;
 if(Jproceed(body,cont) == YES){
    body = ...;
    if(Jproceed(body,cont) == YES))
        return(YES);
 else{
    Junbind(save2);
    Jset_wp(save1);
    return(NO);
 }}
Junbind(save2);
Jset_wp(save1);
*/
gen_cut_body(X) :-
    write('{body ='),o_generate_before_cut(X,Y),gen_body1(Y),write(';'),nl,
    write('if(Jproceed(body,NIL) == YES){'),nl,
    write('body ='),o_generate_after_cut(X,Z),gen_body1(Z),write(';'),nl,
    write('if(Jproceed(body,nest) == YES)'),nl,
    write('return(YES);'),nl,
    write('else{'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl,
    write('return(NO);}}'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);}'),nl.

/*
generate body of clause
when include c_pred/1 in body.
*/
gen_body(X) :-
	  o_has_c_lang(X),
    gen_c_lang_body(X).

/*
body for new compier
foo(X),bar(X),boo(X).

if(unify(....)){
    body = ...;
    if(Jproceed(body,nest) == YES)
        return(YES)};

Junbind(save2);
Jset_wp(save1);


*/
gen_body(X) :-
    write('{body = '),
    gen_body1(X),
    write(';'),nl,
    write('if(Jproceed(body,nest) == YES)'),nl,
    write('return(YES);}'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl.

gen_body1([]) :-
    write('NIL').
gen_body1((X,Xs)) :-
	  write('Jwlist3(Jmakeope(","),'),
	  gen_a_body(X),
    write(','),
    gen_body1(Xs),
    write(')').
gen_body1((X;Xs)) :-
	  write('Jwlist3(Jmakeope(";"),'),
	  gen_body1(X),
    write(','),
    gen_body1(Xs),
    write(')').
gen_body1(X) :-
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
    write(')').

%defined dynamic declared predicate will become predicate
gen_a_body(X) :-
    functor(X,P,0),
    o_dynamic_check(P),
    write('Jmakepred("'),
    write(P),
    write('")').
gen_a_body(X) :-
    functor(X,P,_),
    o_dynamic_check(P),
    o_argument_list(X,L),
    write('Jwcons(Jmakepred("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(')').
%defined predicate and optimizable will become builtin
gen_a_body(X) :-
    o_defined_predicate(X),
    functor(X,P,_),
    optimizable(P),
    o_argument_list(X,L),
    write('Jwcons(Jmakesys("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(')').
%defined predicate will become compiled predicate
gen_a_body(X) :-
    o_defined_predicate(X),
    functor(X,P,0),
    write('Jmakecomp("'),
    write(P),
    write('")').
%defined predicate will become compiled predicate
gen_a_body(X) :-
    o_defined_predicate(X),
    functor(X,P,_),
    o_argument_list(X,L),
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(')').
gen_a_body(X) :-
    o_property(X,predicate),
    functor(X,P,_),
    o_argument_list(X,L),
    write('Jwcons(Jmakepred("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(')').
% atom builtin e.g. nl fail
gen_a_body(X) :-
    o_property(X,builtin),
    functor(X,P,0),
    o_findatom(P,builtin,A),
    write(A).
gen_a_body(X) :-
    o_property(X,builtin),
    functor(X,P,_),
    o_argument_list(X,L),
    o_findatom(P,builtin,A),
    write('Jwcons('),
    write(A),
    write(','),
    gen_argument(L),
    write(')').
gen_a_body(X) :-
    o_property(X,operation),
    gen_body1(X).
gen_a_body(X) :-
    o_property(X,compiled),
    functor(X,P,_),
    o_argument_list(X,L),
    write('Jwcons(Jmakecomp("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(')').
gen_a_body(X) :-
    o_property(X,userop),
    functor(X,P,0),
    o_argument_list(X,L),
    write('Jmakeuser("'),
    write(P),
    write('")').
gen_a_body(X) :-
    o_property(X,userop),
    functor(X,P,_),
    o_argument_list(X,L),
    write('Jwcons(Jmakeuser("'),
    write(P),
    write('"),'),
    gen_argument(L),
    write(')').
gen_a_body(X) :-
    atom(X),
	  write('Jmakepred("'),
    write(X),
    write('")').
gen_a_body(X) :-
    invoke_error('illegal body ',X).
/*
when body has c_lang\1 generate following code.
 body = ...;
 if(proceed(body,NIL) == YES){
    ... C code ...

    }
    return(proceed(NIL,nest));

 //when fail
 Junbind(save2);
 Jset_wp(save1);

*/

gen_c_lang_body(X) :-
    o_generate_before_c_lang(X,B),
    o_generate_after_c_lang(X,A),
	  write('{body = '),
    gen_body1(B),
    write(';'),nl,
    write('if(Jproceed(body,NIL) == YES){'),nl,
    gen_c_lang_body1(A),
    write('return(Jproceed(NIL,nest));}}'),nl,
    write('Junbind(save2);'),nl,
    write('Jset_wp(save1);'),nl.

gen_c_lang_body1(c_lang(X)) :-
	  write(X),nl.
gen_c_lang_body1((c_lang(X),Y)) :-
	  write(X),nl,
    gen_c_lang_body1(Y).
gen_c_lang_body2((X,Y)) :-
	  invoke_error('illegal body ',X).

/*
generate_unify of head
e.g.  foo(X) -> if(Junify(arg1,varX))
anoymous variable generate 1 as true.
e.g   foo(_) -> if(1)
*/
gen_head(X) :-
    functor(X,_,0).
gen_head(X) :-
    o_argument_list(X,Y),
    write('if('),
    gen_head1(Y,1),
    write(')'),nl.

gen_head1([],N).
gen_head1([X],N) :-
    o_compiler_anoymous(X),
    write('1').
gen_head1([X|Xs],N) :-
    o_compiler_anoymous(X),
    write('1 && '),
    N1 is N + 1,
    gen_head1(Xs,N1).
gen_head1([X],N) :-
    gen_head2(N,X).
gen_head1([X|Xs],N) :-
    gen_head2(N,X),
    write(' && '),nl,
    N1 is N + 1,
    gen_head1(Xs,N1).


gen_head2(N,X) :-
	  write('Junify(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(') == YES').

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
eval_form(X) :-
	  o_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
eval_form(X) :-
	  o_longnum(X),
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
    o_compiler_variable(X),
    write('Jderef('),
    write(X),
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
    write(')').
eval_form(X - Y) :-
	  write('Jminus('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X * Y) :-
	  write('Jmult('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X / Y) :-
	  write('Jdivide('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X//Y) :-
	  write('Jdiv('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X ** Y) :-
	  write('Jexpt('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X ^ Y) :-
	  write('Jexpt('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X mod Y) :-
	  write('Jmod('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X rem Y) :-
	  write('Jrem('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(sin(X)) :-
	  write('Jsin('),
    eval_form(X),
    write(')').
eval_form(asin(X)) :-
	  write('Jasin('),
    eval_form(X),
    write(')').
eval_form(cos(X)) :-
	  write('Jcos('),
    eval_form(X),
    write(')').
eval_form(acos(X)) :-
	  write('Jacos('),
    eval_form(X),
    write(')').
eval_form(tan(X)) :-
	  write('Jtan('),
    eval_form(X),
    write(')').
eval_form(atan(X)) :-
	  write('Jatan('),
    eval_form(X),
    write(')').
eval_form(exp(X)) :-
	  write('Jexp('),
    eval_form(X),
    write(')').
eval_form(log(X)) :-
	  write('Jatan('),
    eval_form(X),
    write(')').
eval_form(floor(X)) :-
	  write('Jfloor('),
    eval_form(X),
    write(')').
eval_form(ceiling(X)) :-
	  write('Jseiling('),
    eval_form(X),
    write(')').
eval_form(truncate(X)) :-
	  write('Jtruncate('),
    eval_form(X),
    write(')').
eval_form(sign(X)) :-
	  write('Jsign('),
    eval_form(X),
    write(')').
eval_form(round(X)) :-
	  write('Jround('),
    eval_form(X),
    write(')').
eval_form(X << Y) :-
	  write('Jleftshift('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X >> Y) :-
	  write('Jrightshift('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X /\ Y) :-
	  write('Jlogicaland('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X \/ Y) :-
	  write('Jlogicalor('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(\ X) :-
	  write('Jcomplement('),
    eval_form(X),
    write(')').
eval_form(X xor Y) :-
	  write('Jexclusiveor('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(X iand Y) :-
	  write('Jinclusiveand('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write(')').
eval_form(random(X)) :-
	  write('Jrandom('),
    eval_form(X),
    write(')').

/*
define compiled predicate as compiled predicate.
But, for tail call recursive difinition.
tail call optimized predicate is compiled to builtin(not compiled).
*/
gen_def(P) :-
    optimizable(P),
	  write('(deftpred)("'),
    write(P),
    write('",'),
    write('b_'),
    o_atom_convert(P,P1),
    write(P1),
    write(');'),
    nl,
    write('Jset_aux(Jmakecomp("'),
    write(P),
    write('"),SYS);'),
    nl.
%for normal
gen_def(P) :-
	  write('(deftpred)("'),
    write(P),
    write('",'),
    write('b_'),
    o_atom_convert(P,P1),
    write(P1),
    write(');'),
    gen_def1(P),
    nl.

%for calling_context
gen_def1(P) :-
    o_generated_module(P,[]).
gen_def1(P) :-
    o_generated_module(P,M),
    write('Jset_var(Jmakeconst("'),
    write(P),
    write('"),Jmakeconst("'),
    write(M),
    write('"));'),
    nl.

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
    write(')').
/*
generate one argument
there are all type of prolog object
*/
gen_a_argument([]) :-
	  write('NIL').
gen_a_argument(X) :-
    o_compiler_anoymous(X),
    write('ANOYVAR').
gen_a_argument(X) :-
	  o_compiler_variable(X),
    write(X).
gen_a_argument(pi) :-
	  write('Jmakestrflt("3.14159265358979")').
gen_a_argument(X) :-
	  o_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
gen_a_argument(X) :-
	  o_longnum(X),
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
%defined predicate(with out dynamic) will becomes to compiled predicate.
gen_a_argument(X) :-
    o_defined_predicate(X),
    functor(X,Y,_),
    o_argument_list(X,Z),
    not(o_dynamic_check(Y)),
    write('Jwcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(')').
gen_a_argument(X) :-
    o_property(X,predicate),
    functor(X,Y,_),
    o_argument_list(X,Z),
    write('Jwcons(Jmakepred("'),
    write(Y),
    write('"),'),
    gen_argument(Z),
    write(')').
gen_a_argument(X) :-
    o_property(X,builtin),
    functor(X,Y,0),
    o_findatom(Y,builtin,A),
    write(A).
gen_a_argument(X) :-
    o_property(X,builtin),
    functor(X,Y,_),
    o_findatom(Y,builtin,A),
    o_argument_list(X,Z),
	  write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(')').
gen_a_argument(X) :-
    o_property(X,compiled),
    functor(X,Y,0),
    o_findatom(Y,compiled,A),
    write(A).
gen_a_argument(X) :-
    o_property(X,compiled),
    functor(X,Y,_),
    o_findatom(Y,compiled,A),
    o_argument_list(X,Z),
    write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(')').
gen_a_argument(X) :-
    o_property(X,operation),
    functor(X,Y,0),
    o_findatom(Y,operator,A),
    write(A).
gen_a_argument(X) :-
    o_property(X,operation),
    functor(X,Y,_),
    o_findatom(Y,operator,A),
    o_argument_list(X,Z),
	  write('Jwcons('),
    write(A),
    write(','),
    gen_argument(Z),
    write(')').
%predicate indicator  e.g. foo/1
gen_a_argument(A/B) :-
    atom(A),
    integer(B),
    write('Jwlist3(Jmakefun("/"),Jmakepred("'),
    write(A),
    write('"),'),
    gen_a_argument(B),
    write(')').
gen_a_argument(X) :-
    o_property(X,function),
    functor(X,F,0),
    write('Jmakefun("'),
    write(F),
    write('")').
gen_a_argument(X) :-
    o_property(X,function),
    functor(X,F,_),
    o_argument_list(X,Z),
	  write('Jwcons(Jmakefun("'),
    write(F),
    write('"),'),
    gen_argument(Z),
    write(')').
gen_a_argument(X) :-
    o_property(X,userop),
    functor(X,Y,0),
    write('Jmakeuser("'),
    write(X),
    write('")').
gen_a_argument(X) :-
    o_property(X,userop),
    functor(X,Y,_),
    o_argument_list(X,Z),
	  write('Jwcons(Jmakeuser("'),
    write(Y),
    write('"),'),
    gen_a_argument(Z),
    write(')').
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


/*
for dynamic clause retract orginal clause or predicate.
generate original list.
compiler variable is retract to original expression. e.g. varX -> X
*/
gen_org([]) :-
	write('NIL').
gen_org(X) :-
	  o_compiler_variable(X),
    write('Jmakevar("'),
    o_write_original_variable(X),
    write('")').
gen_org(X) :-
	  o_bignum(X),
    write('Jmakebig("'),
    write(X),
    write('")').
gen_org(X) :-
	  o_longnum(X),
    write('Jmakestrlong("'),
    write(X),
    write('")').
gen_org(X) :-
	  integer(X),
    write('Jmakeint('),
    write(X),
    write(')').
gen_org(X) :-
	  float(X),
    write('Jmakestrflt("'),
    write(X),
    write('")').
%predicate
gen_org(X) :-
	  o_property(X,predicate),
    functor(X,Y,0),
	  write('Jmakepred("'),
    write(Y),
    write('")').
gen_org(X) :-
	  o_property(X,predicate),
    functor(X,Y,_),
    o_argument_list(X,Z),
	  write('Jcons(Jmakepred("'),
    write(Y),
    write('"),'),
    gen_org(Z),
    write(')').
%builtin
gen_org(X) :-
	  o_property(X,builtin),
    functor(X,Y,0),
    o_findatom(Y,builtin,A),
    write(A).
gen_org(X) :-
	  o_property(X,builtin),
    functor(X,Y,_),
    o_argument_list(X,Z),
    o_findatom(Y,builtin,A),
	  write('Jcons('),
    write(A),
    write(','),
    gen_org(Z),
    write(')').
%compiled
gen_org(X) :-
	  o_property(X,compiled),
    functor(X,Y,0),
    write('Jmakecomp("'),
    write(Y),
    write('")').
gen_org(X) :-
	  o_property(X,compiled),
    functor(X,Y,_),
    o_argument_list(X,Z),
	  write('Jcons(Jmakecomp("'),
    write(Y),
    write('"),'),
    gen_org(Z),
    write(')').
%operation
gen_org(X) :-
    o_property(X,operation),
    functor(X,Y,0),
	  write('Jmakeope("'),
    write(Y),
    write('")').
gen_org(X) :-
    o_property(X,operation),
    functor(X,Y,_),
    o_argument_list(X,Z),
	  write('Jcons(Jmakeope("'),
    write(Y),
    write('"),'),
    gen_org(Z),
    write(')').
%user operation
gen_org(X) :-
    o_property(X,userop),
    functor(X,Y,0),
	  write('Jmakeuser("'),
    write(Y),
    write('")').
gen_org(X) :-
    o_property(X,operation),
    functor(X,Y,_),
    o_argument_list(X,Z),
	write('Jcons(Jmakeuser("'),
    write(Y),
    write('"),'),
    gen_org(Z),
    write(')').
%function
gen_org(X) :-
    o_property(X,function),
    functor(X,Y,0),
    write('Jmakefun("'),
    write(Y),
    write('")').
gen_org(X) :-
    o_property(X,function),
    functor(X,Y,_),
    o_argument_list(X,Z),
	  write('Jcons(Jmakefun("'),
    write(Y),
    write('"),'),
    gen_org(Z),
    write(')').
%list
gen_org([X|Xs]) :-
    list([X|Xs]),
    write('Jlistcons('),
    gen_org(X),
    write(','),
    gen_org(Xs),
    write(')').
%conjunction
gen_org((Body1,Body2)) :-
    write('Jlist3(Jmakeope(","),'),
    gen_org(Body1),
    write(','),
    gen_org(Body2),
    write(')'),nl.
%disjunction
gen_org((Body1;Body2)) :-
	  write('Jlist3(Jmakeope(";"),'),
    gen_org(Body1),
    write(','),
    gen_org(Body2),
    write(')'),nl.
%atom
gen_org(X) :-
	  atom(X),
    write('Jmakeconst("'),
    write(X),
    write('")').

%------------------------------------
%for tail recursive optimization
gen_tail_pred(P) :-
    atom_concat('compiling tail ',P,M),
    write(user_output,M),nl(user_output),
    write('int b_'),
    o_atom_convert(P,P1),
    write(P1),
    write('(int nest, int n){'),
    nl,
    gen_tail_var_declare(P),
    o_arity_count(P,[N]),
    gen_tail_pred1(P,N),
    write('}'),nl.

% int arg1,arg2,...argN,varA,varB...
gen_tail_var_declare(P) :-
    o_arity_count(P,L),
    max_element(L,M),
    write('int '),
    gen_tail_var_declare1(1,M),
    o_generate_all_variable(P,V),
    gen_tail_all_var(V).

% arg1,save1,arg1,save2,...,argN,saveN
gen_tail_var_declare1(S,E) :-
	S > E.
gen_tail_var_declare1(S,E) :-
    write(arg),
    write(S),
    write(','),
    write(save),
    write(S),
    write(','),
    S1 is S+1,
    gen_tail_var_declare1(S1,E).


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

% if(n == N){arg1 = ;  loop: ...}
gen_tail_pred1(P,N) :-
    write('if(n == '),
    write(N),
    write('){'),
    gen_tail_receive_var(1,N),
    write('loop:'),nl,
    gen_tail_pred2(P,N),
    write('}'),
    write('return(NO);').

% arg1 = save1 = Jderef(Jget_goal(2));
% arg2 = save1 = Jderef(Jget_goal(3)); ...
gen_tail_receive_var(S,N) :-
    S > N.
gen_tail_receive_var(S,N) :-
    write('arg'),
    write(S),
    write(' = save'),
    write(S),
    S1 is S + 1,
    write(' = Jderef(Jget_goal(' ),
    write(S1),
    write('));'),nl,
    gen_tail_receive_var(S1,N).

%select clauses that arity is N
gen_tail_pred2(P,N) :-
    o_clause_with_arity(P,N,C),
    gen_tail_pred3(C,1).

%generate each predicate
gen_tail_pred3([],N) :-
    write('return(NO);'),nl.
gen_tail_pred3([L|Ls],N) :-
	  o_variable_convert(L,X),
    gen_tail_pred4(X,N),
    N1 is N + 1,
    gen_tail_pred3(Ls,N1).

% clause
gen_tail_pred4((Head :- Body),N) :-
    gen_tail_var(Head),
	  gen_tail_head(Head),
    gen_tail_body(Body,Head).

% predicate
gen_tail_pred4(P,N) :-
    o_property(P,predicate),
    gen_tail_head(P),
    write('{'),
    gen_tail_head_unify(P,N),
    write('return(YES);}'),nl,
    write('exit'),write(N),write(':'),nl.

% foo([A|B]) -> varA = car(arg1); varB = cdr(arg1);
gen_tail_var(X) :-
    functor(X,_,0).
gen_tail_var(X) :-
    o_argument_list(X,Y),
    gen_tail_var1(Y,1,[]).

gen_tail_var1([],N,L).
% anoymous variable
gen_tail_var1(X,N,L) :-
    o_compiler_anoymous(X).
%normal variable
gen_tail_var1(X,N,L) :-
    o_compiler_variable(X),
    write(X),
    write(' = '),
    gen_tail_head3(X,N,L),
    write(';'),nl.
%ignore atom and number []
    gen_tail_var1(X,N,L) :-
        atomic(X).

%list
gen_tail_var1([[Y|Ys]|Xs],N,L) :-
    gen_tail_var1(Y,N,[car|L]),
    gen_tail_var1(Ys,N,[cdr|L]),
    N1 is N + 1,
    gen_tail_var1(Xs,N1,[]).

gen_tail_var1([X|Xs],N,L) :-
    gen_tail_var1(X,N,[]),
    N1 is N + 1,
    gen_tail_var1(Xs,N1,[]).

% foo(1,2) ->
% if(arg1 == makeint(1) && arg2 == makeint(2)) return(YES);
gen_tail_head(X) :-
    functor(X,_,0).
gen_tail_head(X) :-
    o_argument_list(X,Y),
    all_var(Y).
gen_tail_head(X) :-
    o_argument_list(X,Y),
    write('if('),
    gen_tail_head1(Y,1),
    write(')').

% {varA = makevariant();
%  if(Junify(varA,arg1) == NO) goto exitN;
%  Junify(save1,varA);
% ... return(YES);}
gen_tail_head_unify(Pred,N) :-
    o_argument_list(Pred,Args),
    o_generate_variable(Args,V),
    gen_tail_head_unify1(V),
    gen_tail_head_unify2(Args,1,N).

% varA = Jmakevariant(); varB = Jmakevariant(); ...
gen_tail_head_unify1([]).
gen_tail_head_unify1([X|Xs]) :-
    write(X),
    write(' = Jmakevariant();'),nl,
    gen_tail_head_unify1(Xs).

% if(Junify(arg1,varA)==NO) goto exitN;
% Junify(save1,varA); ...
gen_tail_head_unify2([],N,M).
gen_tail_head_unify2([X|Xs],N,M) :-
    write('if(Junify(arg'),
    write(N),
    write(','),
    gen_a_argument(X),
    write(')==NO) goto exit'),write(M),write(';'),nl,
    write('Junify(save'),
    write(N),
    write(',arg'),
    write(N),
    write(');'),nl,
    N1 is N + 1,
    gen_tail_head_unify2(Xs,N1,M).


gen_tail_head1([X],N) :-
    gen_tail_head2(X,N,[]),
    write(1).
gen_tail_head1([[]|Xs],N) :-
    write('arg'),
    write(N),
    write(' == NIL &&'),nl,
    gen_tail_head1(Xs,N).
gen_tail_head1([X|Xs],N) :-
    gen_tail_head2(X,N,[]),
    N1 is N + 1,
    gen_tail_head1(Xs,N1).

%NIL []
gen_tail_head2([],N,L) :-
    gen_tail_head3(X,N,L),
    write(' == NIL &&').

%ignore anoymous
gen_tail_head2(X,N,L) :-
    o_compiler_anoymous(X).
%ignore variable
gen_tail_head2(X,N,L) :-
    o_compiler_variable(X).
%atom
gen_tail_head2(X,N,L) :-
    not(o_property(X,builtin)),
    atom(X),
    write('Jmakeconst("'),
    write(X),
    write('") != '),
    gen_tail_head3(X,N,L),
    write(' && '),nl.
%integer
gen_tail_head2(X,N,L) :-
    integer(X),
    write('Jnumeqp(Jmakeint('),
    write(X),
    write('),'),
    gen_tail_head3(X,N,L),
    write(') && '),nl.
%float number
gen_tail_head2(X,N,L) :-
    real(X),
    write('Jnumeqp(Jmakestrflt("'),
    write(X),
    write('"),'),
    gen_tail_head3(X,N,L),
    write(') && '),nl.
%list  ignore list
gen_tail_head2(X,N,L) :-
    list(X).


%write element N=1, L=[car,cdr] -> car(cdr(arg1))
gen_tail_head3(X,N,[]) :-
    write('arg'),
    write(N).
gen_tail_head3(X,N,[L|Ls]) :-
    write('J'),
    write(L),
    write('('),
    gen_tail_head3(X,N,Ls),
    write(')').

%if all elements are compiler_variable -> true
all_var(X) :-
    member([],X),!,fail.
all_var(X) :-
    all_var1(X).
all_var1([]).
all_var1(X) :-
    o_compiler_variable(X).
all_var1([X|Xs]) :-
    all_var1(X),
    all_var1(Xs).

%generate body that has tail call
gen_tail_body((X,Xs),Head) :-
    gen_tail_a_body(X,Head),
    write('{'),
    gen_tail_body(Xs,Head),
    write('}').
gen_tail_body(X,Head) :-
    gen_tail_a_body(X,Head).

gen_tail_a_body(X is Y,Head) :-
    write(X),
    write(' = '),
    eval_form(Y),
    write(';').

gen_tail_a_body(X =:= Y,Head) :-
    write('if(Jnumeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_tail_a_body(X =\= Y,Head) :-
    write('if(Jnot_numeqp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_tail_a_body(X < Y,Head) :-
    write('if(Jsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_tail_a_body(X =< Y,Head) :-
    write('if(Jeqsmallerp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_tail_a_body(X > Y,Head) :-
    write('if(Jgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_tail_a_body(X >= Y,Head) :-
    write('if(Jeqgreaterp('),
    eval_form(X),
    write(','),
    eval_form(Y),
    write('))').

gen_tail_a_body(X,Head) :-
    o_property(X,builtin),
    functor(X,_,L),
    L1 is L+1,
    write('Jset_goal(0,'),
    write(L1),
    write(');'),nl,
    X =.. L2,
    gen_tail_set_goal(L2,1),
    write('Jcallsubr(Jget_goal(1),0,Jget_goal(0) - 1);').

gen_tail_a_body(X,Head) :-
    functor(X,P,A),
    functor(Head,P,A),
    o_argument_list(X,Xs),
    gen_tail_call(Xs,1).

%gen_tail_a_body(X,Head) :-
%    write(user_output,X).
gen_tail_a_body(X,Head).

gen_tail_set_goal([],N).
gen_tail_set_goal([X|Xs],N) :-
    write('Jset_goal('),
    write(N),
    write(','),
    gen_a_argument(X),
    write(');'),nl,
    N1 is N + 1,
    gen_tail_set_goal(Xs,N1).

gen_tail_call([],N) :-
    write('goto loop;'),nl.
gen_tail_call([X|Xs],N) :-
    write('arg'),
    write(N),
    write(' = '),
    gen_a_argument(X),
    write(';'),nl,
    N1 is N + 1,
    gen_tail_call(Xs,N1).


%analize tail recursive optimization
%if clauses P is optimizable => true
tail_optimize(P) :-
    o_arity_count(P,[N]),
	  o_clause_with_arity(P,N,C),
    o_variable_convert(C,C1),
    deterministic(C1),
    tail_recursive(C1,0),
    unidirectional(C1),!.

% if clauses is all deterministic -> true
deterministic([]).
deterministic([C|Cs]) :-
    o_property(C,predicate),
    deterministic(Cs).
deterministic([(_ :- Body)|Cs]) :-
    deterministic1(Body),
    deterministic(Cs).

deterministic1((Body1,Body2)) :-
    o_property(Body1,builtin),
    deterministic1(Body2).
deterministic1(Body1).

last_body((_,Body),Last) :-
    last_body(Body,Last).
last_body(Body,Body).

% clause has tail recursive call -> true
tail_recursive(_,1) :- !.
tail_recursive([],0) :- fail.
tail_recursive([C|Cs],N) :-
	  o_property(C,predicate),
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
    o_property(C,predicate),
    unidirectional(Cs).
unidirectional([(H :- B)|Cs]) :-
    unidirectional1(B,H).

% clause body has is builtin and other are all builtin -> true
/*
unidirectional1((Body1,Body2),H) :-
	o_is(Body1,Y),
    H =.. A,
	subset(Y,A).
*/
unidirectional1((Body1,Body2),H) :-
    o_property(Body1,builtin),
    unidirectional1(Body2,H).

unidirectional1(Body,H) :-
    o_property(Body,predicate),
    functor(H,N,A),
    functor(Body,N,A).


subset([],_).
subset([X|Sub],Set) :-
    member(X,Set),
    subset(Sub,Set).

% foo([varA|varB])<=> foo(varA) false (depend)
% foo([varA|varB])<=> foo(varC) true (independ)
independence(Pred1,Pred2) :-
    o_argument_list(Pred1,Args1),
    o_argument_list(Pred2,Args2),
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
    o_argument_list(Pred,Args),
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
    o_compiler_variable(X).
deep_member(X,X) :-
    o_compiler_variable(X).
deep_member(X,[Y|Ys]) :-
    deep_member(X,Ys).

list_member([],Y) :- fail.
list_member(X,Y) :-
    atomic(X),deep_member(X,Y).
list_member([L|Ls],Y) :-
    deep_member(L,Y).
list_member([L|Ls],Y) :-
    list_member(Ls,Y).


:- end_body(compiler).
