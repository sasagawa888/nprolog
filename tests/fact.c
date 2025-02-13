#include "jump.h"
int b_fact(int arglist, int rest, int th);
int b_fact(int arglist, int rest, int th){
int arg1,arg2,varN1,varX1,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
//save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
//save1 = Jget_wp(th);
if(Junify_const(Jmakeint(0),arg1,th) == YES && Junify_const(Jmakeint(1),arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
else {
//Jset_ac(save3,th);
Junbind(save2,th);
//Jset_wp(save1,th);
return(NO);
}
varN1 = Jmakevariant(th);
varX1 = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
//save1 = Jget_wp(th);
if(Junify_var(varN,arg1,th) == YES && Junify_var(varX,arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(172,Jwcons(varN1,Jwcons(Jwcons(1809,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("fact"),Jwcons(varN1,Jwcons(varX1,NIL,th),th),th),Jwcons(172,Jwcons(varX,Jwcons(Jwcons(1850,Jwcons(varN,Jwcons(varX1,NIL,th),th),th),NIL,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
//Jset_ac(save3,th);
//Junbind(save2,th);
//Jset_wp(save1,th);
}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("fact",b_fact);
}
void init_declare(void){int body,th; th=0;
}

