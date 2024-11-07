#include "jump.h"
int b_max(int arglist, int rest);
int b_max(int arglist, int rest){
int arg1,arg2,arg3,varY,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varY = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varY,arg2) == YES && Junify_var(varX,arg3) == YES && 1)
{body = Jwcons(88,Jwcons(varX,Jwcons(varY,NIL)));
if(Jexec_all(body,Jget_sp()) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
}
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varY,arg2) == YES && Junify_var(varY,arg3) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("max"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("max",b_max);
}
void init_declare(void){int body;
}