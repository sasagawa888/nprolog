#include "jump.h"
int b_my_select(int arglist, int rest, int th);
int b_my_select(int arglist, int rest, int th){
int arg1,arg2,arg3,varYs,varY,varZs,varX,varXs,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varX,arg1,th) == YES && Junify(Jwlistcons(varX,varXs,th),arg2,th) == YES && Junify_var(varXs,arg3,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varX = Jmakevariant(th);
varYs = Jmakevariant(th);
varY = Jmakevariant(th);
varZs = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varX,arg1,th) == YES && Junify(Jwlistcons(varY,varYs,th),arg2,th) == YES && Junify(Jwlistcons(varY,varZs,th),arg3,th) == YES && 1)
{body = Jwcons(Jmakecomp("my_select"),Jwcons(varX,Jwcons(varYs,Jwcons(varZs,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("my_select"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("my_select",b_my_select);
}
void init_declare(void){int body,th; th=0;
}