#include "jump.h"
static int b_p42(int arglist, int rest, int th);
static int b_p42(int arglist, int rest, int th){
int arg1,arg2,arg3,varM,varB,varN,varA,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varM = Jmakevariant(th);
varB = Jmakevariant(th);
varN = Jmakevariant(th);
varA = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varA,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if (Jcall(