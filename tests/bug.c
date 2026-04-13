#include "jump.h"
static int b_classify_num(int arglist, int rest, int th);
static int b_classify_num(int arglist, int rest, int th){
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
{body = Jwcons(707,Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(77,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("negative"),NIL,th),th),th),NIL,th),th),th),Jwlistcons(Jwcons(38,Jwcons(Jwcons(110,Jwcons(varN,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("zero"),NIL,th),th),th),NIL,th),th),th),Jwlistcons(Jwcons(38,Jwcons(Jwcons(77,Jwcons(varN,Jwcons(Jmakeint(10),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("small"),NIL,th),th),th),NIL,th),th),th),Jwlistcons(Jwcons(38,Jwcons(Jwcons(77,Jwcons(varN,Jwcons(Jmakeint(100),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("medium"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("large"),NIL,th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("classify_num"),arglist);
return(NO);}
static int b_goal(int arglist, int rest, int th);
static int b_goal(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(1246,Jwcons(Jmakeconst("a"),Jwcons(Jwlistcons(Jmakeconst("x"),Jwlistcons(Jmakeconst("a"),Jwlistcons(Jmakeconst("z"),NIL,th),th),th),NIL,th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(1240,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),NIL,th),th),Jwcons(Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),NIL,th),th),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),NIL,th),th),th),th),NIL,th),th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(1252,Jwcons(Jmakeint(1),Jwcons(Jmakeint(3),Jwcons(Jmakeint(2),NIL,th),th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakecomp("classify_num"),Jwcons(Jmakeint(15),Jwcons(Jmakeconst("medium"),NIL,th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("goal"),arglist);
return(NO);}
static int b_run_goal(int arglist, int rest, int th);
static int b_run_goal(int arglist, int rest, int th){
int arg1,arg2,arg3,varName,varGoal,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varName = Jmakevariant(th);
varGoal = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varName,th) == YES && Junify_var(arg2,varGoal,th) == YES && Junify_atom(arg3,Jmakeconst("ok"),th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("named_goal"),Jwcons(varName,Jwcons(varGoal,NIL,th),th),th),Jwcons(20,Jwcons(varGoal,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("run_goal"),arglist);
return(NO);}
static int b_named_goal(int arglist, int rest, int th);
static int b_named_goal(int arglist, int rest, int th){
int arg1,arg2,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
save1 = Jget_wp(th);
if(Junify_atom(arg1,Jmakeconst("g1"),th) == YES && Junify(arg2,Jwcons(1246,Jwcons(Jmakeconst("a"),Jwcons(Jwlistcons(Jmakeconst("x"),Jwlistcons(Jmakeconst("a"),Jwlistcons(Jmakeconst("z"),NIL,th),th),th),NIL,th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
save1 = Jget_wp(th);
if(Junify_atom(arg1,Jmakeconst("g2"),th) == YES && Junify(arg2,Jwcons(1240,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),NIL,th),th),Jwcons(Jwlistcons(Jmakeint(3),NIL,th),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL,th),th),th),NIL,th),th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("named_goal"),arglist);
return(NO);}
static int b_nested_if(int arglist, int rest, int th);
static int b_nested_if(int arglist, int rest, int th){
int arg1,arg2,arg3,varA,varB,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varA = Jmakevariant(th);
varB = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varA,th) == YES && Junify_var(arg2,varB,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
{body = Jwcons(707,Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varA,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(14,Jwcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varB,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("both_positive"),NIL,th),th),th),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("a_only"),NIL,th),th),th),NIL,th),th),th),NIL,th),th),th),Jwlistcons(Jwcons(38,Jwcons(Jwcons(64,Jwcons(varB,Jwcons(Jmakeint(0),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("b_only"),NIL,th),th),th),NIL,th),th),th),Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("none_positive"),NIL,th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nested_if"),arglist);
return(NO);}
static int b_test_meta(int arglist, int rest, int th);
static int b_test_meta(int arglist, int rest, int th){
int arg1,varName,ano_1,varL,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varName = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varL = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varL,th) == YES && 1)
if (Jcall(613,Jwlistcons(varName,Jwlistcons(Jwcons(Jmakecomp("run_goal"),Jwcons(varName,Jwcons(ano_1,Jwcons(Jmakeconst("ok"),NIL,th),th),th),th),Jwlistcons(varL,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test_meta"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("classify_num",b_classify_num);
(deftpred)("goal",b_goal);
(deftpred)("run_goal",b_run_goal);
(deftpred)("named_goal",b_named_goal);
(deftpred)("nested_if",b_nested_if);
(deftpred)("test_meta",b_test_meta);
}
void init_declare(void){int body,th; th=0;
}