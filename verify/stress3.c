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
{body = Jwlist3(Jmakeope(","),Jmakecomp("test1"),Jwlist3(Jmakeope(","),Jmakecomp("test2"),Jwlist3(Jmakeope(","),Jmakecomp("test3"),Jwlist3(Jmakeope(","),Jmakecomp("test4"),Jwlist3(Jmakeope(","),Jmakecomp("test5"),Jwlist3(Jmakeope(","),Jmakecomp("test6"),Jwlist3(Jmakeope(","),Jmakecomp("test7"),Jwlist3(Jmakeope(","),Jmakecomp("test8"),Jwlist3(Jmakeope(","),Jmakecomp("test9"),Jwlist3(Jmakeope(","),Jmakecomp("test10"),Jwlist3(Jmakeope(","),Jmakecomp("test11"),Jwlist3(Jmakeope(","),Jmakecomp("test12"),Jwlist3(Jmakeope(","),Jmakecomp("test13"),Jwlist3(Jmakeope(","),Jmakecomp("test14"),Jwlist3(Jmakeope(","),Jmakecomp("test15"),Jwlist3(Jmakeope(","),Jmakecomp("test16"),Jwlist3(Jmakeope(","),Jmakecomp("test17"),Jwlist3(Jmakeope(","),Jmakecomp("test18"),Jwlist3(Jmakeope(","),Jmakecomp("test19"),Jmakecomp("test20"),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th);
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
int arg1,arg2,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("positive"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("nonpositive"),NIL,th),th),th),th),th),th) == YES)
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
if (Jcall(Jmakecomp("p1"),Jwlistcons(Jmakeint(3),Jwlistcons(varX,NIL,th),th),th) == YES)
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
int arg1,arg2,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("positive"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("zero_or_negative"),NIL,th),th),th),th),th),th) == YES)
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
if (Jcall(Jmakecomp("p2"),Jwlistcons(Jmakeint(0),Jwlistcons(varX,NIL,th),th),th) == YES)
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
int arg1,arg2,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(99,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(707,Jwcons(Jwlistcons(Jwcons(38,Jwcons(Jwcons(110,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("zero"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("pos"),NIL,th),th),th),th),NIL,th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("neg"),NIL,th),th),th),th),th),th) == YES)
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
if (Jcall(Jmakecomp("p3"),Jwlistcons(Jmakeint(0),Jwlistcons(varX,NIL,th),th),th) == YES)
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
int arg1,arg2,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varN,Jwcons(Jmakeint(10),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakepred("big"),NIL,th),th),th),NIL,th),th),th),Jwcons(707,Jwcons(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakepred("small"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("nonpositive"),NIL,th),th),th),th),NIL,th),th),th),th),th) == YES)
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
if (Jcall(Jmakecomp("p4"),Jwlistcons(Jmakeint(3),Jwlistcons(varX,NIL,th),th),th) == YES)
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
int arg1,arg2,arg3,varC,varA,varB,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varC = Jmakevariant(th);
varA = Jmakevariant(th);
varB = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varA,th) == YES && Junify_var(arg2,varB,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varC,Jplus(Jderef(varA,th),Jderef(varB,th),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varC,Jwcons(Jmakeint(10),NIL,th),th),th),Jwcons(Jwcons(187,Jwcons(varX,Jwcons(Jwcons(2440,Jwcons(varC,Jwcons(Jmakeint(2),NIL,th),th),th),NIL,th),th),th),NIL,th),th),th),Jwcons(187,Jwcons(varX,Jwcons(Jwcons(2399,Jwcons(varC,Jwcons(Jmakeint(2),NIL,th),th),th),NIL,th),th),th),th),th),th) == YES)
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
if (Jcall(Jmakecomp("p5"),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(3),Jwlistcons(varX,NIL,th),th),th),th) == YES)
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