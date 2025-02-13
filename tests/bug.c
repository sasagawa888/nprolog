#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,varL,varLs,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varL = Jmakevariant(th);
varLs = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varL,varLs,th),th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(1159,Jwcons(varL,NIL,th),th),Jwcons(1159,Jwcons(varLs,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
int b_qsort(int arglist, int rest, int th);
int b_qsort(int arglist, int rest, int th){
int arg1,arg2,arg3,varL2,varL1,varR1,varX,varL,varR,varR0,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varL2 = Jmakevariant(th);
varL1 = Jmakevariant(th);
varR1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL = Jmakevariant(th);
varR = Jmakevariant(th);
varR0 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varR,th) == YES && Junify_var(arg3,varR0,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("partition"),Jwcons(varL,Jwcons(varX,Jwcons(varL1,Jwcons(varL2,NIL,th),th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qsort"),Jwcons(varL2,Jwcons(varR1,Jwcons(varR0,NIL,th),th),th),th),Jwcons(Jmakecomp("qsort"),Jwcons(varL1,Jwcons(varR,Jwcons(Jwlistcons(varX,varR1,th),NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
varR = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varR,th) == YES && Junify_var(arg3,varR,th) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp(th),th)) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("qsort"),arglist);
return(NO);}
int b_partition(int arglist, int rest, int th);
int b_partition(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,var_1,varL,varY,varX,varL1,varL2,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
varL = Jmakevariant(th);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
varL1 = Jmakevariant(th);
varL2 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_pair(arg3,Jwlistcons(varX,varL1,th),th) == YES && Junify_var(arg4,varL2,th) == YES && 1)
{body = Jwcons(72,Jwcons(varX,Jwcons(varY,NIL,th),th),th);
if((res=Jexec_all(body,Jget_sp(th),th)) == YES)
{body = Jwcons(Jmakecomp("partition"),Jwcons(varL,Jwcons(varY,Jwcons(varL1,Jwcons(varL2,NIL,th),th),th),th),th);
if((Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varL = Jmakevariant(th);
varY = Jmakevariant(th);
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL2 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varL1,th) == YES && Junify_pair(arg4,Jwlistcons(varX,varL2,th),th) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp(th),th)) == YES)
{body = Jwcons(Jmakecomp("partition"),Jwcons(varL,Jwcons(varY,Jwcons(varL1,Jwcons(varL2,NIL,th),th),th),th),th);
if((Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg3,th) == YES && Junify_nil(arg4,th) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp(th),th)) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
}
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("partition"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
(deftpred)("qsort",b_qsort);
(deftpred)("partition",b_partition);
}
void init_declare(void){int body,th; th=0;
}