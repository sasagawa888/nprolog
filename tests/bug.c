#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,arg2,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_const(Jmakeint(1),arg1,th) == YES && Junify_var(varX,arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}