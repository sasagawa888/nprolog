#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,varX1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && 1)

return(Jexec_all(rest,Jget_sp(th),th));varX1 = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if(Junify(varX1,Jminus(Jderef(varX,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("foo"),Jwlistcons(varX1,NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}