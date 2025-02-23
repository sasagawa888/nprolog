#include "jump.h"
int b_nreverse(int arglist, int rest, int th);
int b_nreverse(int arglist, int rest, int th){
int arg1,arg2,varL1,varX,varL0,varL,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL0 = Jmakevariant(th);
varL = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL0,th),th) == YES && Junify_var(arg2,varL,th) == YES && 1)
if (Jcall(Jmakecomp("nreverse"),Jwlistcons(varL0,Jwlistcons(varL1,NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("concatenate"),Jwlistcons(varL1,Jwlistcons(Jwlistcons(varX,NIL,th),Jwlistcons(varL,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES && 1)

return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nreverse"),arglist);
return(NO);}
int b_concatenate(int arglist, int rest, int th);
int b_concatenate(int arglist, int rest, int th){
int arg1,arg2,arg3,varL,varL1,varL2,varX,varL3,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varL1 = Jmakevariant(th);
varL2 = Jmakevariant(th);
varX = Jmakevariant(th);
varL3 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL1,th),th) == YES && Junify_var(arg2,varL2,th) == YES && Junify_pair(arg3,Jwlistcons(varX,varL3,th),th) == YES && 1)
{
if (Jcall(10,NIL,th) == YES){
Jmakeconst("[]"),th) == YES){
