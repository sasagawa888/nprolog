#include "jump.h"
static int b_ex13(int arglist, int rest, int th);
static int b_ex13(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("forall"),Jwcons(Jmakeconst("x"),Jwcons(Jwcons(Jmakepred("imply"),Jwcons(Jwcons(Jmakepred("p"),Jwcons(Jmakeconst("x"),NIL,th),th),Jwcons(Jwcons(Jmakepred("exist"),Jwcons(Jmakeconst("y"),Jwcons(Jwcons(Jmakepred("and"),Jwcons(Jwcons(Jmakepred("imply"),Jwcons(Jwcons(Jmakepred("q"),Jwcons(Jmakeconst("x"),Jwcons(Jmakeconst("y"),NIL,th),th),th),Jwcons(Jwcons(Jmakepred("p"),Jwcons(Jmakeconst("a"),NIL,th),th),NIL,th),th),th),Jwcons(Jwcons(Jmakepred("imply"),Jwcons(Jwcons(Jmakepred("q"),Jwcons(Jmakeconst("y"),Jwcons(Jmakeconst("a"),NIL,th),th),th),Jwcons(Jwcons(Jmakepred("p"),Jwcons(Jmakeconst("x"),NIL,th),th),NIL,th),th),th),NIL,th),th),th),NIL,th),th),th),NIL,th),th),th),NIL,th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ex13"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("ex13",b_ex13);
}
void init_declare(void){int body,th; th=0;
}