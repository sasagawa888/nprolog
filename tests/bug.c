#include "jump.h"
int b_repeat_for(int arglist, int rest, int th);
int b_repeat_for(int arglist, int rest, int th){
int arg1,varM,varN,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
save1 = Jget_wp(th);
if(Junify_const(Jmakeint(0),arg1,th) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp(th),th)) == YES)
{body = 566;
if((Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
Junbind(save2,th);
Jset_wp(save1,th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varN,arg1,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varN,arg1,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(172,Jwcons(varM,Jwcons(Jwcons(1803,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th),Jwcons(Jmakecomp("repeat_for"),Jwcons(varM,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("repeat_for"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("repeat_for",b_repeat_for);
}
void init_declare(void){int body,th; th=0;
}