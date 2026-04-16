#include "jump.h"
static int b_test16(int arglist, int rest, int th);
static int b_test16(int arglist, int rest, int th){
int varN,varX,varY,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varN = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jwcons(1252,Jwcons(Jmakeint(0),Jwcons(Jmakeint(5),Jwcons(varN,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(707,Jwlist1(Jwlistcons(Jwcons(12,Jwcons(Jwcons(38,Jwcons(Jwcons(77,Jwcons(varN,Jwcons(Jmakeint(3),NIL,th),th),th),Jwcons(Jwcons(14,Jwcons(Jwcons(38,Jwcons(Jwcons(77,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("a"),NIL,th),th),th),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("b"),NIL,th),th),th),NIL,th),th),th),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varY,Jwcons(Jmakeconst("left"),NIL,th),th),th),NIL,th),th),th),Jwcons(12,Jwcons(Jwcons(14,Jwcons(Jwcons(38,Jwcons(Jwcons(77,Jwcons(varN,Jwcons(Jmakeint(5),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("c"),NIL,th),th),th),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varX,Jwcons(Jmakeconst("d"),NIL,th),th),th),NIL,th),th),th),Jwcons(Jwcons(198,Jwcons(varY,Jwcons(Jmakeconst("right"),NIL,th),th),th),NIL,th),th),th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1212,Jwcons(Jmakecomp("test16"),NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1212,Jwcons(Jmakeconst(" : "),NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1212,Jwcons(varX,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1212,Jwcons(Jmakeconst(","),NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1212,Jwcons(varY,NIL,th),th),Jwlist3(Jmakeope(","),816,601,th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(Jexec_all(rest,Jget_sp(th),th));
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test16"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("test16",b_test16);
}
void init_declare(void){int body,th; th=0;
}