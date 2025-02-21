#include "jump.h"
int b_nreverse(int arglist, int rest, int th);
int b_nreverse(int arglist, int rest, int th){
int arg1,arg2,varL1,varX,varL0,varL,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL0 = Jmakevariant(th);
varL = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL0,th),th) == YES && Junify_var(arg2,varL,th) == YES && 1)
if (Jcall(Jmakecomp("nreverse"),Jwlistcons(varL0,Jwlistcons(varL1,NIL,th),th),th) == YES)
if (Jcall(Jmakecomp("concatenate"),Jwlistcons(varL1,Jwlistcons(Jwlistcons(varX,NIL,th),Jwlistcons(varL,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg2,th) == YES && 1)

return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("nreverse"),arglist);
return(NO);}
int b_concatenate(int arglist, int rest, int th);
int b_concatenate(int arglist, int rest, int th){
int arg1,arg2,arg3,varL,varL1,varL2,varX,varL3,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varL1 = Jmakevariant(th);
varL2 = Jmakevariant(th);
varX = Jmakevariant(th);
varL3 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL1,th),th) == YES && Junify_var(arg2,varL2,th) == YES && Junify_pair(arg3,Jwlistcons(varX,varL3,th),th) == YES && 1)

if (Jcall(Jmakecomp("concatenate"),Jwlistcons(varL1,Jwlistcons(varL2,Jwlistcons(varL3,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));varL = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,varL,th) == YES && Junify_var(arg3,varL,th) == YES && 1)

return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("concatenate"),arglist);
return(NO);}
int b_list30(int arglist, int rest, int th);
int b_list30(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
save1 = Jget_wp(th);
if(Junify(arg1,Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),Jwlistcons(Jmakeint(10),Jwlistcons(Jmakeint(11),Jwlistcons(Jmakeint(12),Jwlistcons(Jmakeint(15),Jwlistcons(Jmakeint(14),Jwlistcons(Jmakeint(15),Jwlistcons(Jmakeint(16),Jwlistcons(Jmakeint(17),Jwlistcons(Jmakeint(18),Jwlistcons(Jmakeint(19),Jwlistcons(Jmakeint(20),Jwlistcons(Jmakeint(21),Jwlistcons(Jmakeint(22),Jwlistcons(Jmakeint(25),Jwlistcons(Jmakeint(24),Jwlistcons(Jmakeint(25),Jwlistcons(Jmakeint(26),Jwlistcons(Jmakeint(27),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(29),Jwlistcons(Jmakeint(30),NIL,th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("list30"),arglist);
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
Jdunbind(save3,th);
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
if(Jsmallerp(Jderef(varX,th),Jderef(varY,th)) && Jinc_proof(th))

if (Jcall(Jmakecomp("partition"),Jwlistcons(varL,Jwlistcons(varY,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));varL = Jmakevariant(th);
varY = Jmakevariant(th);
varL1 = Jmakevariant(th);
varX = Jmakevariant(th);
varL2 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varL,th),th) == YES && Junify_var(arg2,varY,th) == YES && Junify_var(arg3,varL1,th) == YES && Junify_pair(arg4,Jwlistcons(varX,varL2,th),th) == YES && 1)

if (Jcall(Jmakecomp("partition"),Jwlistcons(varL,Jwlistcons(varY,Jwlistcons(varL1,Jwlistcons(varL2,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));var_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_nil(arg3,th) == YES && Junify_nil(arg4,th) == YES && 1)

return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("partition"),arglist);
return(NO);}
int b_list50(int arglist, int rest, int th);
int b_list50(int arglist, int rest, int th){
int arg1,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
save1 = Jget_wp(th);
if(Junify(arg1,Jwlistcons(Jmakeint(27),Jwlistcons(Jmakeint(74),Jwlistcons(Jmakeint(17),Jwlistcons(Jmakeint(33),Jwlistcons(Jmakeint(94),Jwlistcons(Jmakeint(18),Jwlistcons(Jmakeint(46),Jwlistcons(Jmakeint(83),Jwlistcons(Jmakeint(65),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(32),Jwlistcons(Jmakeint(53),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(85),Jwlistcons(Jmakeint(99),Jwlistcons(Jmakeint(47),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(82),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(11),Jwlistcons(Jmakeint(55),Jwlistcons(Jmakeint(29),Jwlistcons(Jmakeint(39),Jwlistcons(Jmakeint(81),Jwlistcons(Jmakeint(90),Jwlistcons(Jmakeint(37),Jwlistcons(Jmakeint(10),Jwlistcons(Jmakeint(0),Jwlistcons(Jmakeint(66),Jwlistcons(Jmakeint(51),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(21),Jwlistcons(Jmakeint(85),Jwlistcons(Jmakeint(27),Jwlistcons(Jmakeint(31),Jwlistcons(Jmakeint(63),Jwlistcons(Jmakeint(75),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(95),Jwlistcons(Jmakeint(99),Jwlistcons(Jmakeint(11),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(61),Jwlistcons(Jmakeint(74),Jwlistcons(Jmakeint(18),Jwlistcons(Jmakeint(92),Jwlistcons(Jmakeint(40),Jwlistcons(Jmakeint(55),Jwlistcons(Jmakeint(59),Jwlistcons(Jmakeint(8),NIL,th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("list50"),arglist);
return(NO);}
int b_repeat_for(int arglist, int rest, int th);
int b_repeat_for(int arglist, int rest, int th){
int arg1,varM,varN,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp(th),th)) == YES)
{body = 566;
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
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varN,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(172,Jwcons(varM,Jwcons(Jwcons(1811,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th),Jwcons(Jmakecomp("repeat_for"),Jwcons(varM,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("repeat_for"),arglist);
return(NO);}
int b_run(int arglist, int rest, int th);
int b_run(int arglist, int rest, int th){
int arg1,arg2,var_2,varX,var_1,varN,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_atom(arg1,Jmakeconst("none"),th) == YES && Junify_var(arg2,varN,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("repeat_for"),Jwcons(varN,NIL,th),th),566,th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
varX = Jmakevariant(th);
var_1 = Jmakevariant(th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_atom(arg1,Jmakecomp("qsort"),th) == YES && Junify_var(arg2,varN,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("list50"),Jwcons(varX,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("repeat_for"),Jwcons(varN,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qsort"),Jwcons(varX,Jwcons(var_1,NIL,th),th),th),566,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
varX = Jmakevariant(th);
var_1 = Jmakevariant(th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_atom(arg1,Jmakeconst("reverse"),th) == YES && Junify_var(arg2,varN,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("list30"),Jwcons(varX,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("repeat_for"),Jwcons(varN,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("nreverse"),Jwcons(varX,Jwcons(var_1,NIL,th),th),th),566,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_2 = Jmakevariant(th);
var_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("run"),arglist);
return(NO);}
int b_test(int arglist, int rest, int th);
int b_test(int arglist, int rest, int th){
int arg1,arg2,varF,varN,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varF = Jmakevariant(th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varF,th) == YES && Junify_var(arg2,varN,th) == YES && 1)
if (Jcall(761,Jwlistcons(Jwcons(Jmakecomp("run"),Jwcons(varF,Jwcons(varN,NIL,th),th),th),NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("nreverse",b_nreverse);
(deftpred)("concatenate",b_concatenate);
(deftpred)("list30",b_list30);
(deftpred)("qsort",b_qsort);
(deftpred)("partition",b_partition);
(deftpred)("list50",b_list50);
(deftpred)("repeat_for",b_repeat_for);
(deftpred)("run",b_run);
(deftpred)("test",b_test);
}
void init_declare(void){int body,th; th=0;
}