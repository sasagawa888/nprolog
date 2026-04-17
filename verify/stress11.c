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
{body = Jwlist3(Jmakeope(","),Jmakecomp("test41"),Jwlist3(Jmakeope(","),Jmakecomp("test42"),Jwlist3(Jmakeope(","),Jmakecomp("test43"),Jwlist3(Jmakeope(","),Jmakecomp("test44"),Jmakecomp("test45"),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("run_all"),arglist);
return(NO);}
static int b_test41(int arglist, int rest, int th);
static int b_test41(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("p41"),Jwcons(Jmakeint(2),Jwcons(varX,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("writeln"),Jwcons(Jmakecomp("test41"),NIL,th),th),Jwcons(Jmakepred("writeln"),Jwcons(varX,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test41"),arglist);
return(NO);}
static int b_p41(int arglist, int rest, int th);
static int b_p41(int arglist, int rest, int th){
int arg1,arg2,varM,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varM = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(