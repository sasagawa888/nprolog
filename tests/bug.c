#include "jump.h"
int b_qsort(int arglist, int rest);
int b_qsort(int arglist, int rest){
int arg1,arg2,arg3,varL2,varL1,varR1,varX,varL,varR,varR0,n,body,save1,save2,save3,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varL2 = Jmakevariant();
varL1 = Jmakevariant();
varR1 = Jmakevariant();
varX = Jmakevariant();
varL = Jmakevariant();
varR = Jmakevariant();
varR0 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varX,varL),arg1) == YES && Junify_var(varR,arg2) == YES && Junify_var(varR0,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("partition"),Jwcons(varL,Jwcons(varX,Jwcons(varL1,Jwcons(varL2,NIL))))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qsort"),Jwcons(varL2,Jwcons(varR1,Jwcons(varR0,NIL)))),Jwcons(Jmakecomp("qsort"),Jwcons(varL1,Jwcons(varR,Jwcons(Jwlistcons(varX,varR1),NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify_var(varR,arg2) == YES && Junify_var(varR,arg3) == YES && 1)
{body = 10;
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("qsort"),arglist);
return(NO);}
int b_partition(int arglist, int rest);
int b_partition(int arglist, int rest){
int arg1,arg2,arg3,arg4,var_1,varL,varY,varX,varL1,varL2,n,body,save1,save2,save3,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
varL = Jmakevariant();
varY = Jmakevariant();
varX = Jmakevariant();
varL1 = Jmakevariant();
varL2 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varX,varL),arg1) == YES && Junify_var(varY,arg2) == YES && Junify(Jwlistcons(varX,varL1),arg3) == YES && Junify_var(varL2,arg4) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(68,Jwcons(varX,Jwcons(varY,NIL))),Jwlist3(Jmakeope(","),10,Jwcons(Jmakecomp("partition"),Jwcons(varL,Jwcons(varY,Jwcons(varL1,Jwcons(varL2,NIL)))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
varL = Jmakevariant();
varY = Jmakevariant();
varL1 = Jmakevariant();
varX = Jmakevariant();
varL2 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varX,varL),arg1) == YES && Junify_var(varY,arg2) == YES && Junify_var(varL1,arg3) == YES && Junify(Jwlistcons(varX,varL2),arg4) == YES && 1)
{body = Jwlist3(Jmakeope(","),10,Jwcons(Jmakecomp("partition"),Jwcons(varL,Jwcons(varY,Jwcons(varL1,Jwcons(varL2,NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
var_1 = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify_nil(NIL,arg3) == YES && Junify_nil(NIL,arg4) == YES && 1)
{body = 10;
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("partition"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("qsort",b_qsort);
(deftpred)("partition",b_partition);
}
void init_declare(void){int body;
}