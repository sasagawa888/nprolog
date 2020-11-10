#include "../jump.h"
int b_fib(int arglist, int rest);
int b_fib(int arglist, int rest){
int varM,varK,varY,varZ,varN,varX,varR,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){varR = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeint(0),Jwcons(varR,NIL)),arglist) == YES)
{body = Jwlist3(Jmakeope(","),10,Jwcons(128,Jwcons(varR,Jwcons(Jmakeint(0),NIL))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeint(1),Jwcons(varR,NIL)),arglist) == YES)
{body = Jwlist3(Jmakeope(","),10,Jwcons(128,Jwcons(varR,Jwcons(Jmakeint(1),NIL))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
varM = Jmakevariant();
varK = Jmakevariant();
varY = Jmakevariant();
varZ = Jmakevariant();
varN = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varN,Jwcons(varX,NIL)),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(122,Jwcons(varM,Jwcons(Jwcons(570,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("fib"),Jwcons(varM,Jwcons(varY,NIL))),Jwlist3(Jmakeope(","),Jwcons(122,Jwcons(varK,Jwcons(Jwcons(570,Jwcons(varM,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("fib"),Jwcons(varK,Jwcons(varZ,NIL))),Jwcons(122,Jwcons(varX,Jwcons(Jwcons(528,Jwcons(varY,Jwcons(varZ,NIL))),NIL)))))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
void init_tpredicate(void){(deftpred)("fib",b_fib);
}void init_declare(void){}