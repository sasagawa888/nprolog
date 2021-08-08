#include "jump.h"
int b_ack(int arglist, int rest);
int b_ack(int arglist, int rest){
int arg1,arg2,arg3,varN1,varX1,varM1,varM,varN,varX,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varN = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jmakeint(0),arg1) == YES && Junify(varN,arg2) == YES && Junify(varX,arg3) == YES && 1)
{body = Jwcons(166,Jwcons(varX,Jwcons(Jwcons(1233,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varM1 = Jmakevariant();
varM = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(varM,arg1) == YES && Junify(Jmakeint(0),arg2) == YES && Junify(varX,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(54,Jwcons(varM,Jwcons(Jmakeint(0),NIL))),Jwlist3(Jmakeope(","),Jwcons(166,Jwcons(varM1,Jwcons(Jwcons(1275,Jwcons(varM,Jwcons(Jmakeint(1),NIL))),NIL))),Jwcons(Jmakecomp("ack"),Jwcons(varM1,Jwcons(Jmakeint(1),Jwcons(varX,NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varN1 = Jmakevariant();
varM1 = Jmakevariant();
varX1 = Jmakevariant();
varM = Jmakevariant();
varN = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(varM,arg1) == YES && Junify(varN,arg2) == YES && Junify(varX,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(54,Jwcons(varM,Jwcons(Jmakeint(0),NIL))),Jwlist3(Jmakeope(","),Jwcons(54,Jwcons(varN,Jwcons(Jmakeint(0),NIL))),Jwlist3(Jmakeope(","),Jwcons(166,Jwcons(varM1,Jwcons(Jwcons(1275,Jwcons(varM,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(166,Jwcons(varN1,Jwcons(Jwcons(1275,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("ack"),Jwcons(varM,Jwcons(varN1,Jwcons(varX1,NIL)))),Jwcons(Jmakecomp("ack"),Jwcons(varM1,Jwcons(varX1,Jwcons(varX,NIL)))))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
void init_tpredicate(void){(deftpred)("ack",b_ack);
}
void init_declare(void){int body;
}