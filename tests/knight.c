#include "jump.h"
static int b_fastest(int arglist, int rest, int th);
static int b_fastest(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,arg5,varR1,varC1,varR2,varC2,varR3,varC3,varR4,varC4,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 5){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
arg5 = Jnth(arglist,5);
loop5:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR2 = Jmakevariant(th);
varC2 = Jmakevariant(th);
varR3 = Jmakevariant(th);
varC3 = Jmakevariant(th);
varR4 = Jmakevariant(th);
varC4 = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES && Junify(arg2,Jwlistcons(varR2,Jwlistcons(varC2,NIL,th),th),th) == YES && Junify(arg3,Jwlistcons(varR3,Jwlistcons(varC3,NIL,th),th),th) == YES && Junify(arg4,Jwlistcons(varR4,Jwlistcons(varC4,NIL,th),th),th) == YES && Junify_var(arg5,varX,th) == YES && 1)
if (Jcall(1641,Jwlistcons(Jwlistcons(Jwcons(Jmakecomp("tour"),Jwcons(varR1,Jwcons(varC1,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("tour"),Jwcons(varR2,Jwcons(varC2,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("tour"),Jwcons(varR3,Jwcons(varC3,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("tour"),Jwcons(varR4,Jwcons(varC4,Jwcons(varX,NIL,th),th),th),th),NIL,th),th),th),th),NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fastest"),arglist);
return(NO);}
static int b_ptour8(int arglist, int rest, int th);
static int b_ptour8(int arglist, int rest, int th){
int arg1,arg2,arg3,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if (Jcall(1641,Jwlistcons(Jwlistcons(Jwcons(Jmakecomp("pmove81"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove82"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove83"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove84"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove85"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove86"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove87"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove88"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),NIL,th),th),th),th),th),th),th),th),NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ptour8"),arglist);
return(NO);}
static int b_ptour4(int arglist, int rest, int th);
static int b_ptour4(int arglist, int rest, int th){
int arg1,arg2,arg3,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if (Jcall(1641,Jwlistcons(Jwlistcons(Jwcons(Jmakecomp("pmove1"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove2"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove3"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),Jwlistcons(Jwcons(Jmakecomp("pmove4"),Jwcons(varR,Jwcons(varC,Jwcons(varX,NIL,th),th),th),th),NIL,th),th),th),th),NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ptour4"),arglist);
return(NO);}
static int b_pmove1(int arglist, int rest, int th);
static int b_pmove1(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
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
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jplus(Jderef(varR,th),Jmakeint(2),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jplus(Jderef(varC,th),Jmakeint(1),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);
body = 
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jplus(Jderef(varR,th),Jmakeint(1),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jplus(Jderef(varC,th),Jmakeint(2),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove1"),arglist);
return(NO);}
static int b_pmove2(int arglist, int rest, int th);
static int b_pmove2(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
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
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jminus(Jderef(varR,th),Jmakeint(2),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jminus(Jderef(varC,th),Jmakeint(1),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);
body = 
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jminus(Jderef(varR,th),Jmakeint(1),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jminus(Jderef(varC,th),Jmakeint(2),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove2"),arglist);
return(NO);}
static int b_pmove3(int arglist, int rest, int th);
static int b_pmove3(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
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
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jplus(Jderef(varR,th),Jmakeint(2),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jminus(Jderef(varC,th),Jmakeint(1),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);
body = 
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jplus(Jderef(varR,th),Jmakeint(1),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jminus(Jderef(varC,th),Jmakeint(2),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove3"),arglist);
return(NO);}
static int b_pmove4(int arglist, int rest, int th);
static int b_pmove4(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
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
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jminus(Jderef(varR,th),Jmakeint(2),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jplus(Jderef(varC,th),Jmakeint(1),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);
body = 
Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varR1,th),Jminus(Jderef(varR,th),Jmakeint(1),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1917,Jwlist2(Jderef(varC1,th),Jplus(Jderef(varC,th),Jmakeint(2),th),th),th),Jwcons(Jmakecomp("move"),Jwcons(varR1,Jwcons(varC1,Jwcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwcons(varX,NIL,th),th),th),th),th),th),th);
if(Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th) == YES)
return(YES);
Junbind(dp[3],th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove4"),arglist);
return(NO);}
static int b_pmove81(int arglist, int rest, int th);
static int b_pmove81(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove81"),arglist);
return(NO);}
static int b_pmove82(int arglist, int rest, int th);
static int b_pmove82(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove82"),arglist);
return(NO);}
static int b_pmove83(int arglist, int rest, int th);
static int b_pmove83(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove83"),arglist);
return(NO);}
static int b_pmove84(int arglist, int rest, int th);
static int b_pmove84(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove84"),arglist);
return(NO);}
static int b_pmove85(int arglist, int rest, int th);
static int b_pmove85(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove85"),arglist);
return(NO);}
static int b_pmove86(int arglist, int rest, int th);
static int b_pmove86(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove86"),arglist);
return(NO);}
static int b_pmove87(int arglist, int rest, int th);
static int b_pmove87(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove87"),arglist);
return(NO);}
static int b_pmove88(int arglist, int rest, int th);
static int b_pmove88(int arglist, int rest, int th){
int arg1,arg2,arg3,varR1,varC1,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pmove88"),arglist);
return(NO);}
static int b_tour(int arglist, int rest, int th);
static int b_tour(int arglist, int rest, int th){
int arg1,arg2,arg3,varR,varC,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR,Jwlistcons(varC,Jwlistcons(Jwlistcons(Jwlistcons(varR,Jwlistcons(varC,NIL,th),th),NIL,th),Jwlistcons(varX,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("tour"),arglist);
return(NO);}
static int b_safe(int arglist, int rest, int th);
static int b_safe(int arglist, int rest, int th){
int arg1,arg2,varR,varC,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varR = Jmakevariant(th);
varC = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && 1)
if(Jeqgreaterp(Jderef(varR,th),Jmakeint(1)) && Jinc_proof(th))
if(Jeqsmallerp(Jderef(varR,th),Jmakeint(5)) && Jinc_proof(th))

if(Jeqgreaterp(Jderef(varC,th),Jmakeint(1)) && Jinc_proof(th))
if(Jeqsmallerp(Jderef(varC,th),Jmakeint(5)) && Jinc_proof(th))

return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("safe"),arglist);
return(NO);}
static int b_move(int arglist, int rest, int th);
static int b_move(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,varR1,varC1,varR,varC,varA,ano_2,ano_1,varP,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
loop4:
ano_2 = Jmakevariant(th);
ano_1 = Jmakevariant(th);
varP = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varP,th) == YES && 1)
if (Jcall(755,Jwlistcons(varP,Jwlistcons(Jmakeint(25),NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jplus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jminus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varR1 = Jmakevariant(th);
varC1 = Jmakevariant(th);
varR = Jmakevariant(th);
varC = Jmakevariant(th);
varP = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varR,th) == YES && Junify_var(arg2,varC,th) == YES && Junify_var(arg3,varP,th) == YES && Junify_var(arg4,varA,th) == YES && 1)
if(Junify(varR1,Jminus(Jderef(varR,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if(Junify(varC1,Jplus(Jderef(varC,th),Jmakeint(2),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("safe"),Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),th) == YES)
if (Jcall(264,Jwlistcons(Jwcons(1234,Jwcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),Jwcons(varP,NIL,th),th),th),NIL,th),th) == YES)
if (Jcall(Jmakecomp("move"),Jwlistcons(varR1,Jwlistcons(varC1,Jwlistcons(Jwlistcons(Jwlistcons(varR1,Jwlistcons(varC1,NIL,th),th),varP,th),Jwlistcons(varA,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("move"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("fastest",b_fastest);
(deftpred)("ptour8",b_ptour8);
(deftpred)("ptour4",b_ptour4);
(deftpred)("pmove1",b_pmove1);
(deftpred)("pmove2",b_pmove2);
(deftpred)("pmove3",b_pmove3);
(deftpred)("pmove4",b_pmove4);
(deftpred)("pmove81",b_pmove81);
(deftpred)("pmove82",b_pmove82);
(deftpred)("pmove83",b_pmove83);
(deftpred)("pmove84",b_pmove84);
(deftpred)("pmove85",b_pmove85);
(deftpred)("pmove86",b_pmove86);
(deftpred)("pmove87",b_pmove87);
(deftpred)("pmove88",b_pmove88);
(deftpred)("tour",b_tour);
(deftpred)("safe",b_safe);
(deftpred)("move",b_move);
}
void init_declare(void){int body,th; th=0;
}