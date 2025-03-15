#include "jump.h"
#define a 1
static int b_foo(int arglist, int rest, int th);
static int b_foo(int arglist, int rest, int th){
int arg1,targ1,arg2,targ2,varY,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = targ1 = Jnth(arglist,1);
loop1:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
{body = Jwcons(1178,Jwcons(Jmakeint(1),Jwcons(Jmakeint(2),Jwcons(varX,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}if(n == 2){
arg1 = targ1 = Jnth(arglist,1);
arg2 = targ2 = Jnth(arglist,2);
loop2:
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varY,th) == YES && Junify_int(arg2,Jmakeint(1),th) == YES && 1)
{body = Jwcons(1560,Jwcons(varY,NIL,th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}