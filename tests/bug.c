#include "jump.h"
static int b_ac(int arglist, int rest, int th);
static int b_ac(int arglist, int rest, int th){
int arg1,arg2,arg3,varX,varY,varZ,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
varX = Jmakevariant(th);
varY = Jmakevariant(th);
varZ = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varZ,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakeuser("in"),Jwcons(varX,Jwcons(Jwcons(Jmakeuser(".."),Jwcons(Jmakeint(1),Jwcons(Jmakeint(3),NIL,th),th),th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakeuser("in"),Jwcons(varY,Jwcons(Jwcons(Jmakeuser(".."),Jwcons(Jmakeint(1),Jwcons(Jmakeint(3),NIL,th),th),th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakeuser("in"),Jwcons(varZ,Jwcons(Jwcons(Jmakeuser(".."),Jwcons(Jmakeint(1),Jwcons(Jmakeint(5),NIL,th),th),th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakeuser("#="),Jwcons(Jwcons(2379,Jwcons(Jwcons(2379,Jwcons(varX,Jwcons(varY,NIL,th),th),th),Jwcons(varZ,NIL,th),th),th),Jwcons(Jmakeint(3),NIL,th),th),th),Jwcons(Jmakepred("label"),Jwcons(Jwlistcons(varX,Jwlistcons(varY,Jwlistcons(varZ,NIL,th),th),th),NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ac"),arglist);
return(NO);}
void init_tpredicate(void){}
void init_declare(void){int body,th; th=0;
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jmakeuser(".."),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("#="),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("#>"),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("#<"),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("#\="),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("#<="),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("#>="),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("in"),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(862,Jwcons(Jmakeint(600),Jwcons(Jmakeconst("xfy"),Jwcons(Jwcons(Jmakecomp("ins"),NIL,th),NIL,th),th),th),th);
Jprove_all(body,Jget_sp(th),th);
body = Jwcons(1504,Jwcons(Jmakeconst("clpfd"),NIL,th),th);
Jprove_all(body,Jget_sp(th),th);
}