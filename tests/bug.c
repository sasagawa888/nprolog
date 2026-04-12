#include "jump.h"
static int b_test13(int arglist, int rest, int th);
static int b_test13(int arglist, int rest, int th){
int varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(varX,Jmakeint(3),th)==YES && Jinc_proof(th))
if (Jcall(1600,Jwlistcons(Jwcons(209,Jwcons(varX,Jwcons(Jwcons(2400,Jwcons(Jmakeint(1),Jwcons(Jmakeint(2),NIL,th),th),th),NIL,th),th),th),NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test13"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("test13",b_test13);
}
void init_declare(void){int body,th; th=0;
}