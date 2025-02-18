#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jcall(Jmakecomp("bar"),Jwlistcons(varX,NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
int b_bar(int arglist, int rest, int th);
int b_bar(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jcall(1159,Jwlistcons(varX,NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bar"),arglist);
return(NO);}
int b_uoo(int arglist, int rest, int th);
int b_uoo(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jcall(1159,Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(Jmakecomp("uoo"),Jwlistcons(varX,NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("uoo"),arglist);
return(NO);}
int b_nodiag(int arglist, int rest, int th);
int b_nodiag(int arglist, int rest, int th){
int arg1,arg2,arg3,varD1,varN,varL,varB,varD,var_2,var_1,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
var_2 = Jmakevariant(th);
var_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varD1 = Jmakevariant(th);
varN = Jmakevariant(th);
varL = Jmakevariant(th);
varB = Jmakevariant(th);
varD = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varN,varL,th),th) == YES && Junify_var(arg2,varB,th) == YES && Junify_var(arg3,varD,th) == YES && 1)
if (Jcall(112,Jwlistcons(varD,Jwlistcons(Jwcons(1813,Jwcons(varN,Jwcons(varB,NIL,th),th),th),NIL,th),th),th) == YES)
if (Jcall(112,Jwlistcons(varD,Jwlistcons(Jwcons(1813,Jwcons(varB,Jwcons(varN,NIL,th),th),th),NIL,th),th),th) == YES)
if (Jcall(172,Jwlistcons(varD1,Jwlistcons(Jwcons(1772,Jwcons(varD,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("nodiag"),Jwlistcons(varL,Jwlistcons(varB,Jwlistcons(varD1,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nodiag"),arglist);
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
if (Jcall(Jmakecomp("partition"),Jwlistcons(varL,Jwlistcons(varX,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th),th) == YES)
if (Jcall(Jmakecomp("qsort"),Jwlistcons(varL2,Jwlistcons(varR1,Jwlistcons(varR0,NIL,th),th),th),th) == YES)
if (Jcall(Jmakecomp("qsort"),Jwlistcons(varL1,Jwlistcons(varR,Jwlistcons(Jwlistcons(varX,varR1,th),NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));varR = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varR,th) == YES && Junify_var(arg3,varR,th) == YES && 1)
if (Jcall(10,NIL,th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
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
if (Jcall(72,Jwlistcons(varX,Jwlistcons(varY,NIL,th),th),th) == YES)
if (Jcall(10,NIL,th) == YES)
if (Jcall(Jmakecomp("partition"),Jwlistcons(varL,Jwlistcons(varY,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));varL = Jmakevariant(th);
varY = Jmakevariant(th);
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL2 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varL1,th) == YES && Junify_pair(arg4,Jwlistcons(varX,varL2,th),th) == YES && 1)
if (Jcall(10,NIL,th) == YES)
if (Jcall(Jmakecomp("partition"),Jwlistcons(varL,Jwlistcons(varY,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));var_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg3,th) == YES && Junify_nil(arg4,th) == YES && 1)
if (Jcall(10,NIL,th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("partition"),arglist);
return(NO);}
int b_reverse(int arglist, int rest, int th);
int b_reverse(int arglist, int rest, int th){
int arg1,arg2,varY1,varX,varXs,varY,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varY1 = Jmakevariant(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varXs,th),th) == YES && Junify_var(arg2,varY,th) == YES && 1)
if (Jcall(Jmakecomp("reverse"),Jwlistcons(varXs,Jwlistcons(varY1,NIL,th),th),th) == YES)
if (Jcall(1187,Jwlistcons(varY1,Jwlistcons(Jwlistcons(varX,NIL,th),Jwlistcons(varY,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("reverse"),arglist);
return(NO);}
int b_fact(int arglist, int rest, int th);
int b_fact(int arglist, int rest, int th){
int arg1,arg2,varN1,varX1,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_int(arg2,Jmakeint(1),th) == YES && 1)
if (Jcall(10,NIL,th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));varN1 = Jmakevariant(th);
varX1 = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && Junify_var(arg2,varX,th) == YES && 1)
if (Jcall(172,Jwlistcons(varN1,Jwlistcons(Jwcons(1813,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("fact"),Jwlistcons(varN1,Jwlistcons(varX1,NIL,th),th),th) == YES)
if (Jcall(172,Jwlistcons(varX,Jwlistcons(Jwcons(1854,Jwcons(varN,Jwcons(varX1,NIL,th),th),th),NIL,th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
(deftpred)("bar",b_bar);
(deftpred)("uoo",b_uoo);
(deftpred)("nodiag",b_nodiag);
(deftpred)("qsort",b_qsort);
(deftpred)("partition",b_partition);
(deftpred)("reverse",b_reverse);
(deftpred)("fact",b_fact);
}
void init_declare(void){int body,th; th=0;
}