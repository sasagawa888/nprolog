#include "jump.h"
int b_test(int arglist, int rest, int th);
int b_test(int arglist, int rest, int th){
int arg1,arg2,varX,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varX,arg1,th) == YES && Junify_var(varY,arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(172,Jwcons(varX,Jwcons(Jwcons(1476,Jwcons(Jwcons(Jmakefun("sin"),Jwcons(Jmakeint(1),NIL,th),th),Jwcons(Jwcons(Jmakefun("cos"),Jwcons(Jmakeint(2),NIL,th),th),NIL,th),th),th),NIL,th),th),th),Jwcons(222,Jwcons(varY,Jwcons(Jwlistcons(Jmakefun("sin"),Jwlistcons(Jmakeint(3),NIL,th),th),NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("test",b_test);
}
void init_declare(void){int body,th; th=0;
}