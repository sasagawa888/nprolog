#include "jump.h"
int b_p(int arglist, int rest);
int b_p(int arglist, int rest){
int varD,varE,varA,varB,varC,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){varD = Jmakevariant();
varE = Jmakevariant();
varA = Jmakevariant();
varB = Jmakevariant();
varC = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varA,Jwcons(varB,Jwcons(varC,NIL))),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(62,Jwcons(varA,Jwcons(varB,NIL))),Jwlist3(Jmakeope(","),Jwcons(122,Jwcons(varD,Jwcons(Jwcons(528,Jwcons(Jwcons(624,Jwcons(varA,Jwcons(Jmakeint(2),NIL))),Jwcons(Jwcons(624,Jwcons(varB,Jwcons(Jmakeint(2),NIL))),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(122,Jwcons(varE,Jwcons(Jwcons(624,Jwcons(varC,Jwcons(Jmakeint(2),NIL))),NIL))),Jwcons(134,Jwcons(varD,Jwcons(varE,NIL))))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
void init_tpredicate(void){(deftpred)("p",b_p);
}void init_declare(void){}