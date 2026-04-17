#include "jump.h"
static int b_run_all(int arglist, int rest, int th);
static int b_run_all(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jmakecomp("test1"),Jwlist3(Jmakeope(","),Jmakecomp("test2"),Jwlist3(Jmakeope(","),Jmakecomp("test3"),Jwlist3(Jmakeope(","),Jmakecomp("test4"),Jwlist3(Jmakeope(","),Jmakecomp("test5"),Jwlist3(Jmakeope(","),Jmakecomp("test6"),Jwlist3(Jmakeope(","),Jmakecomp("test7"),Jwlist3(Jmakeope(","),Jmakecomp("test8"),Jwlist3(Jmakeope(","),Jmakecomp("test9"),Jwlist3(Jmakeope(","),Jmakecomp("test10"),Jwlist3(Jmakeope(","),Jmakecomp("test11"),Jwlist3(Jmakeope(","),Jmakecomp("test12"),Jwlist3(Jmakeope(","),Jmakecomp("test13"),Jwlist3(Jmakeope(","),Jmakecomp("test14"),Jwlist3(Jmakeope(","),Jmakecomp("test15"),Jwlist3(Jmakeope(","),Jmakecomp("test16"),Jwlist3(Jmakeope(","),Jmakecomp("test17"),Jwlist3(Jmakeope(","),Jmakecomp("test18"),Jwlist3(Jmakeope(","),Jmakecomp("test19"),Jwlist3(Jmakeope(","),Jmakecomp("test20"),Jwlist3(Jmakeope(","),Jmakecomp("test21"),Jwlist3(Jmakeope(","),Jmakecomp("test22"),Jwlist3(Jmakeope(","),Jmakecomp("test23"),Jwlist3(Jmakeope(","),Jmakecomp("test24"),Jmakecomp("test25"),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("run_all"),arglist);
return(NO);}
static int b_show(int arglist, int rest, int th);
static int b_show(int arglist, int rest, int th){
int arg1,arg2,varName,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varName = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varName,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(1212,Jwlistcons(varName,NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(Jmakeconst(" : "),NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(816,NIL,th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("show"),arglist);
return(NO);}
static int b_show2(int arglist, int rest, int th);
static int b_show2(int arglist, int rest, int th){
int arg1,arg2,arg3,varName,varX,varY,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varName = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varName,th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varY,th) == YES && 1)
if (Jcall(1212,Jwlistcons(varName,NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(Jmakeconst(" : "),NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(Jmakeconst(","),NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(varY,NIL,th),th) == YES)
if (Jcall(816,NIL,th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("show2"),arglist);
return(NO);}
static int b_p1(int arglist, int rest, int th);
static int b_p1(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varX,Jplus(Jmakeint(1),Jmakeint(2),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p1"),arglist);
return(NO);}
static int b_test1(int arglist, int rest, int th);
static int b_test1(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p1"),Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test1"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test1"),arglist);
return(NO);}
static int b_p2(int arglist, int rest, int th);
static int b_p2(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varX,Jplus(Jmakeint(1),Jmult(Jmakeint(2),Jmakeint(3),th),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p2"),arglist);
return(NO);}
static int b_test2(int arglist, int rest, int th);
static int b_test2(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p2"),Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test2"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test2"),arglist);
return(NO);}
static int b_p3(int arglist, int rest, int th);
static int b_p3(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varX,Jmult(Jplus(Jmakeint(1),Jmakeint(2),th),Jmakeint(3),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p3"),arglist);
return(NO);}
static int b_test3(int arglist, int rest, int th);
static int b_test3(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p3"),Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test3"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test3"),arglist);
return(NO);}
static int b_p4(int arglist, int rest, int th);
static int b_p4(int arglist, int rest, int th){
int arg1,varA,varB,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varA = Jmakevariant(th);
varB = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varA,Jplus(Jmakeint(10),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varB,Jmult(Jderef(varA,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varX,Jminus(Jderef(varB,th),Jmakeint(5),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p4"),arglist);
return(NO);}
static int b_test4(int arglist, int rest, int th);
static int b_test4(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p4"),Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test4"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test4"),arglist);
return(NO);}
static int b_p5(int arglist, int rest, int th);
static int b_p5(int arglist, int rest, int th){
int arg1,arg2,varA,varB,varC,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varA = Jmakevariant(th);
varB = Jmakevariant(th);
varC = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if(Junify(varA,Jplus(Jderef(varN,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varB,Jplus(Jderef(varA,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC,Jplus(Jderef(varB,th),Jmakeint(3),th),th)==YES && Jinc_proof(th))
if(Junify(varX,Jplus(Jderef(varC,th),Jmakeint(4),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p5"),arglist);
return(NO);}
static int b_test5(int arglist, int rest, int th);
static int b_test5(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p5"),Jwlistcons(Jmakeint(0),Jwlistcons(varX,NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test5"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test5"),arglist);
return(NO);}
static int b_p6(int arglist, int rest, int th);
static int b_p6(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varX,Jminus(Jmakeint(0),Jplus(Jmakeint(3),Jmakeint(2),th),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p6"),arglist);
return(NO);}
static int b_test6(int arglist, int rest, int th);
static int b_test6(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p6"),Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test6"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test6"),arglist);
return(NO);}
static int b_p7(int arglist, int rest, int th);
static int b_p7(int arglist, int rest, int th){
int arg1,varA,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varA = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varA,Jmakeint(-5),th)==YES && Jinc_proof(th))
if(Junify(varX,Jplus(Jderef(varA,th),Jmakeint(8),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p7"),arglist);
return(NO);}
static int b_test7(int arglist, int rest, int th);
static int b_test7(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p7"),Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test7"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test7"),arglist);
return(NO);}
static int b_p8(int arglist, int rest, int th);
static int b_p8(int arglist, int rest, int th){
int arg1,arg2,varX,varY,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && 1)
if(Junify(varX,Jdiv(Jmakeint(17),Jmakeint(5),th),th)==YES && Jinc_proof(th))
if(Junify(varY,Jmod(Jmakeint(17),Jmakeint(5),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p8"),arglist);
return(NO);}
static int b_test8(int arglist, int rest, int th);
static int b_test8(int arglist, int rest, int th){
int varX,varY,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p8"),Jwlistcons(varX,Jwlistcons(varY,NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("show2"),Jwlistcons(Jmakecomp("test8"),Jwlistcons(varX,Jwlistcons(varY,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test8"),arglist);
return(NO);}
static int b_p9(int arglist, int rest, int th);
static int b_p9(int arglist, int rest, int th){
int arg1,arg2,varA,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varA = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if(Junify(varA,Jmult(Jderef(varN,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varA,Jwcons(Jmakeint(10),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakepred("big"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakepred("small"),NIL,th),th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("p9"),arglist);
return(NO);}
static int b_test9(int arglist, int rest, int th);
static int b_test9(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if (Jcall(Jmakecomp("p9"),Jwlistcons(Jmakeint(4),Jwlistcons(varX,NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("show"),Jwlistcons(Jmakecomp("test9"),Jwlistcons(varX,NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test9"),arglist);
return(NO);}
static int b_p10(int arglist, int rest, int th);
static int b_p10(int arglist, int rest, int th){
int arg1,arg2,varA,varB,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varA = Jmakevariant(th);
varB = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(