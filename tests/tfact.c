#include "jump.h"
int b_fact(int arglist, int rest, int th);
int b_fact(int arglist, int rest, int th){
int arg1,arg2,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
{body = Jwcons(Jmakecomp("fact_"),Jwcons(varN,Jwcons(Jmakeint(1),Jwcons(varX,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
int b_fact_(int arglist, int rest, int th);
int b_fact_(int arglist, int rest, int th){
int arg1,arg2,arg3,targ1,targ2,targ3,varN1,varP1,varN,varP,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = targ1 = Jnth(arglist,1);
arg2 = targ2 = Jnth(arglist,2);
arg3 = targ3 = Jnth(arglist,3);
loop3:
varN1 = Jmakevariant(th);
varP1 = Jmakevariant(th);
varN = Jmakevariant(th);
varP = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varP,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
if(Jgreaterp(Jderef(varN,th),Jmakeint(0)) && Jinc_proof(th))if(Junify(varN1,Jminus(Jderef(varN,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))if(Junify(varP1,Jmult(Jderef(varP,th),Jderef(varN,th),th),th)==YES && Jinc_proof(th)){
arg1 = Jcopy_work(Jderef(varN1,th),th);
arg2 = Jcopy_work(Jderef(varP1,th),th);
arg3 = Jcopy_work(Jderef(varX,th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop3;
}
varX = Jmakevariant(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_var(arg2,varX,th) == YES && Junify_var(arg3,varX,th) == YES && 1){
Junify(targ1,arg1,th);Junify(targ2,arg2,th);Junify(targ3,arg3,th);
return(Jexec_all(rest,Jget_sp(th),th));}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact_"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("fact",b_fact);
(deftpred)("fact_",b_fact_);
}
void init_declare(void){int body,th; th=0;
}