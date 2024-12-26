#include "jump.h"
int b_para(int arglist, int rest, int th);
int b_para(int arglist, int rest, int th){
int arg1,varY,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varX,arg1,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("list50"),Jwcons(varY,NIL,th),th),Jwcons(Jmakecomp("psort"),Jwcons(varY,Jwcons(varX,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("para"),arglist);
return(NO);}
int b_psort(int arglist, int rest, int th);
int b_psort(int arglist, int rest, int th){
int arg1,arg2,varLeft,varRight,varSortedLeft,varSortedRight,varPivot,varRest,varSorted,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varLeft = Jmakevariant(th);
varRight = Jmakevariant(th);
varSortedLeft = Jmakevariant(th);
varSortedRight = Jmakevariant(th);
varPivot = Jmakevariant(th);
varRest = Jmakevariant(th);
varSorted = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(Jwlistcons(varPivot,varRest,th),arg1,th) == YES && Junify_var(varSorted,arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("partition"),Jwcons(varPivot,Jwcons(varRest,Jwcons(varLeft,Jwcons(varRight,NIL,th),th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1357,Jwcons(Jwlistcons(Jwcons(Jmakecomp("qsort"),Jwcons(varLeft,Jwcons(varSortedLeft,NIL,th),th),th),Jwlistcons(Jwcons(Jmakecomp("qsort"),Jwcons(varRight,Jwcons(varSortedRight,NIL,th),th),th),NIL,th),th),NIL,th),th),Jwcons(1233,Jwcons(varSortedLeft,Jwcons(Jwlistcons(varPivot,varSortedRight,th),Jwcons(varSorted,NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("psort"),arglist);
return(NO);}
int b_seq(int arglist, int rest, int th);
int b_seq(int arglist, int rest, int th){
int arg1,varY,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varY = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varX,arg1,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("list50"),Jwcons(varY,NIL,th),th),Jwcons(Jmakecomp("qsort"),Jwcons(varY,Jwcons(varX,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("seq"),arglist);
return(NO);}
int b_qsort(int arglist, int rest, int th);
int b_qsort(int arglist, int rest, int th){
int arg1,arg2,varLeft,varRight,varSortedLeft,varSortedRight,varPivot,varRest,varSorted,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp(th);
if(Junify_nil(NIL,arg1,th) == YES && Junify_nil(NIL,arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varLeft = Jmakevariant(th);
varRight = Jmakevariant(th);
varSortedLeft = Jmakevariant(th);
varSortedRight = Jmakevariant(th);
varPivot = Jmakevariant(th);
varRest = Jmakevariant(th);
varSorted = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(Jwlistcons(varPivot,varRest,th),arg1,th) == YES && Junify_var(varSorted,arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("partition"),Jwcons(varPivot,Jwcons(varRest,Jwcons(varLeft,Jwcons(varRight,NIL,th),th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qsort"),Jwcons(varLeft,Jwcons(varSortedLeft,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qsort"),Jwcons(varRight,Jwcons(varSortedRight,NIL,th),th),th),Jwcons(1233,Jwcons(varSortedLeft,Jwcons(Jwlistcons(varPivot,varSortedRight,th),Jwcons(varSorted,NIL,th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("qsort"),arglist);
return(NO);}
int b_partition(int arglist, int rest, int th);
int b_partition(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,varPivot,varT,varH,varLeft,varRight,var_1,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
var_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(NIL,arg2,th) == YES && Junify_nil(NIL,arg3,th) == YES && Junify_nil(NIL,arg4,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varPivot = Jmakevariant(th);
varT = Jmakevariant(th);
varH = Jmakevariant(th);
varLeft = Jmakevariant(th);
varRight = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varPivot,arg1,th) == YES && Junify(Jwlistcons(varH,varT,th),arg2,th) == YES && Junify(Jwlistcons(varH,varLeft,th),arg3,th) == YES && Junify_var(varRight,arg4,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(82,Jwcons(varH,Jwcons(varPivot,NIL,th),th),th),Jwcons(Jmakecomp("partition"),Jwcons(varPivot,Jwcons(varT,Jwcons(varLeft,Jwcons(varRight,NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
varPivot = Jmakevariant(th);
varT = Jmakevariant(th);
varLeft = Jmakevariant(th);
varH = Jmakevariant(th);
varRight = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varPivot,arg1,th) == YES && Junify(Jwlistcons(varH,varT,th),arg2,th) == YES && Junify_var(varLeft,arg3,th) == YES && Junify(Jwlistcons(varH,varRight,th),arg4,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(60,Jwcons(varH,Jwcons(varPivot,NIL,th),th),th),Jwcons(Jmakecomp("partition"),Jwcons(varPivot,Jwcons(varT,Jwcons(varLeft,Jwcons(varRight,NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("partition"),arglist);
return(NO);}
int b_list50(int arglist, int rest, int th);
int b_list50(int arglist, int rest, int th){
int arg1,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
save1 = Jget_wp(th);
if(Junify(Jwlistcons(Jmakeint(27),Jwlistcons(Jmakeint(74),Jwlistcons(Jmakeint(17),Jwlistcons(Jmakeint(33),Jwlistcons(Jmakeint(94),Jwlistcons(Jmakeint(18),Jwlistcons(Jmakeint(46),Jwlistcons(Jmakeint(83),Jwlistcons(Jmakeint(65),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(32),Jwlistcons(Jmakeint(53),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(85),Jwlistcons(Jmakeint(99),Jwlistcons(Jmakeint(47),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(82),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(11),Jwlistcons(Jmakeint(55),Jwlistcons(Jmakeint(29),Jwlistcons(Jmakeint(39),Jwlistcons(Jmakeint(81),Jwlistcons(Jmakeint(90),Jwlistcons(Jmakeint(37),Jwlistcons(Jmakeint(10),Jwlistcons(Jmakeint(0),Jwlistcons(Jmakeint(66),Jwlistcons(Jmakeint(51),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(21),Jwlistcons(Jmakeint(85),Jwlistcons(Jmakeint(27),Jwlistcons(Jmakeint(31),Jwlistcons(Jmakeint(63),Jwlistcons(Jmakeint(75),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(95),Jwlistcons(Jmakeint(99),Jwlistcons(Jmakeint(11),Jwlistcons(Jmakeint(28),Jwlistcons(Jmakeint(61),Jwlistcons(Jmakeint(74),Jwlistcons(Jmakeint(18),Jwlistcons(Jmakeint(92),Jwlistcons(Jmakeint(40),Jwlistcons(Jmakeint(55),Jwlistcons(Jmakeint(59),Jwlistcons(Jmakeint(8),NIL,th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),th),arg1,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("list50"),arglist);
return(NO);}
int b_list500(int arglist, int rest, int th);
int b_list500(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varX,arg1,th) == YES && 1)
{body = Jwcons(Jmakecomp("listn"),Jwcons(Jmakeint(500),Jwcons(varX,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("list500"),arglist);
return(NO);}
int b_listn(int arglist, int rest, int th);
int b_listn(int arglist, int rest, int th){
int n,head,varN1,varN,varR,varX;
n = Jlength(arglist);
if(n == 2){
loop:
Jinc_proof(th);
head = Jwcons(Jmakeint(0),Jwcons(NIL,NIL,th),th);
if(Jnumeqp(Jmakeint(0),Jcar(arglist)) && 
Jcar(Jcdr(arglist)) == NIL && 1){if(Junify(arglist,head,th)==YES) return(Jexec_all(rest,Jget_sp(th),th)); else return(NO);}
varN = Jcar(arglist);
varR = Jcar(Jcar(Jcdr(arglist)));
varX = Jcdr(Jcar(Jcdr(arglist)));
{varR = Jrandi(Jmakeint(100));
varN1 = Jminus(Jderef(varN,th),Jmakeint(1));
arglist = Jwcons(varN1,Jwcons(varX,NIL,th),th);
goto loop;
}}return(NO);
}
void init_tpredicate(void){(deftpred)("para",b_para);
(deftpred)("psort",b_psort);
(deftpred)("seq",b_seq);
(deftpred)("qsort",b_qsort);
(deftpred)("partition",b_partition);
(deftpred)("list50",b_list50);
(deftpred)("list500",b_list500);
(deftpred)("listn",b_listn);
}
void init_declare(void){int body;
}