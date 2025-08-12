#include "jump.h"
static int b_pmove1(int arglist, int rest, int th);
static int b_pmove1(int arglist, int rest, int th){
int arg1,targ1,arg2,targ2,arg3,targ3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = targ1 = Jnth(arglist,1);
arg2 = targ2 = Jnth(arglist,2);
arg3 = targ3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
{dp[3]=Jget_sp(th);
body = 
Jwlist3(Jmakeope(","),Jwcons(1949,Jwlist2(Jderef(varR1,th),Jplus(Jderef(varR,th),Jmakeint(2),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1949,Jwlist2(Jderef(varC1,th),Jplus(Jderef(varC,th),Jmakeint(1),th),th),th),Jwcons(Jmakepred("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);
body = 
Jwlist3(Jmakeope(","),Jwcons(1949,Jwlist2(Jderef(varR1,th),Jplus(Jderef(varR,th),Jmakeint(1),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1949,Jwlist2(Jderef(varC1,th),Jplus(Jderef(varC,th),Jmakeint(2),th),th),th),Jwcons(Jmakepred("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove1"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("pmove1",b_pmove1);
}
void init_declare(void){int body,th; th=0;
}