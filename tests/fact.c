#include "jump.h"
int b_fact(int arglist, int rest);
int b_fact(int arglist, int rest){
int arg1,arg2,varX1,varY1,varX,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_const(Jmakeint(0),arg1) == YES && Junify_const(Jmakeint(1),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varX1 = Jmakevariant();
varY1 = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varY,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varX1,Jwcons(Jwcons(1395,Jwcons(varX,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("fact"),Jwcons(varX1,Jwcons(varY1,NIL))),Jwcons(168,Jwcons(varY,Jwcons(Jwcons(1436,Jwcons(varX,Jwcons(varY1,NIL))),NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("fact",b_fact);
}
void init_declare(void){int body;
}