#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jall(Jmakecomp("bar"),Jwlistcons(varX,NIL,th),th) == YES)return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
int b_bar(int arglist, int rest, int th);
int b_bar(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jall(1159,Jwlistcons(varX,NIL,th),th) == YES)return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bar"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
(deftpred)("bar",b_bar);
}
void init_declare(void){int body,th; th=0;
}