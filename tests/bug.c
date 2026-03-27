#include "jump.h"
static int b_s(int arglist, int rest, int th);
static int b_s(int arglist, int rest, int th){
int arg1,arg2,var_v61,var_v44,var_v62,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakepred("np"),Jwcons(NIL,Jwcons(NIL,NIL,th),th),th),Jwcons(Jmakepred("vp"),Jwcons(NIL,Jwcons(NIL,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("s"),arglist);
return(NO);}
static int b_nil(int arglist, int rest, int th);
static int b_nil(int arglist, int rest, int th){
int 