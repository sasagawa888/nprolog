#include "jump.h"
int b_foo(int arglist, int rest);
int b_foo(int arglist, int rest){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && 1)
{goal = Jwcons(1197,Jwcons(varX,NIL));
cont = NIL
;
if(Jcps(goal,cont) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
}
void init_declare(void){int body;
}