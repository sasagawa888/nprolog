#include "jump.h"
static int b_run_all(int arglist, int rest, int th);
static int b_run_all(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jmakecomp("test1"),Jwlist3(Jmakeope(","),Jmakecomp("test2"),Jwlist3(Jmakeope(","),Jmakecomp("test3"),Jmakecomp("test4"),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("run_all"),arglist);
return(NO);}
static int b_show(int arglist, int rest, int th);
static int b_show(int arglist, int rest, int th){
int arg1,varT,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varT = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varT,th) == YES && 1)
if (Jcall(1212,Jwlistcons(varT,NIL,th),th) == YES)
if (Jcall(816,NIL,th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("show"),arglist);
return(NO);}
static int b_test1(int arglist, int rest, int th);
static int b_test1(int arglist, int rest, int th){
int varN,varM,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varN = Jmakevariant(th);
varM = Jmakevariant(th);
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("show"),Jwcons(Jmakecomp("test1"),NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1252,Jwcons(Jmakeint(0),Jwcons(Jmakeint(9),Jwcons(varN,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(1212,Jwcons(varN,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(187,Jwlist2(varM,Jwlist3(Jmakeope("mod"),varN,Jmakeint(5),th),th),th),Jwlist3(Jmakeope(","),Jwlist3(Jmakeope(";"),Jwcons(2025,Jwlist2(Jwcons(209,Jwlist2(varM,Jmakeint(4),th),th),816,th),th),1198,th),601,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(Jexec_all(rest,Jget_sp(th),th));
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test1"),arglist);
return(NO);}
static int b_test2(int arglist, int rest, int th);
static int b_test2(int arglist, int rest, int th){
int varN,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varN = Jmakevariant(th);
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("show"),Jwcons(Jmakecomp("test2"),NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1252,Jwcons(Jmakeint(0),Jwcons(Jmakeint(9),Jwcons(varN,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwlist3(Jmakeope(";"),Jwcons(2025,Jwlist2(Jwcons(77,Jwlist2(varN,Jmakeint(5),th),th),Jwcons(1212,Jwcons(Jmakeconst("a"),NIL,th),th),th),th),Jwcons(1212,Jwcons(Jmakeconst("b"),NIL,th),th),th),601,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
save1 = Jget_wp(th);
{body = 816;
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test2"),arglist);
return(NO);}
static int b_test3(int arglist, int rest, int th);
static int b_test3(int arglist, int rest, int th){
int varN,varM,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
varN = Jmakevariant(th);
varM = Jmakevariant(th);
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("show"),Jwcons(Jmakecomp("test3"),NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(1252,Jwcons(Jmakeint(0),Jwcons(Jmakeint(9),Jwcons(varN,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwlist3(Jmakeope(";"),Jwcons(2025,Jwlist2(Jwcons(77,Jwlist2(varN,Jmakeint(5),th),th),Jwcons(1212,Jwcons(Jmakeconst("a"),NIL,th),th),th),th),Jwcons(1212,Jwcons(Jmakeconst("b"),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(187,Jwlist2(varM,Jwlist3(Jmakeope("mod"),varN,Jmakeint(5),th),th),th),Jwlist3(Jmakeope(","),Jwlist3(Jmakeope(";"),Jwcons(2025,Jwlist2(Jwcons(209,Jwlist2(varM,Jmakeint(4),th),th),816,th),th),1198,th),601,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(Jexec_all(rest,Jget_sp(th),th));
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test3"),arglist);
return(NO);}
static int b_test4(int arglist, int rest, int th);
static int b_test4(int arglist, int rest, int th){
int n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 0){
loop0:
save1 = Jget_wp(th);
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("show"),Jwcons(Jmakecomp("test4"),NIL,th),th),Jwcons(Jmakecomp("print_answer"),Jwcons(Jmakeint(123),NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test4"),arglist);
return(NO);}
static int b_print_answer(int arglist, int rest, int th);
static int b_print_answer(int arglist, int rest, int th){
int arg1,ano_1,varN,varM,varPushPattern,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varN = Jmakevariant(th);
varM = Jmakevariant(th);
varPushPattern = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varPushPattern,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),816,Jwlist3(Jmakeope(","),Jwcons(1252,Jwcons(Jmakeint(0),Jwcons(Jmakeint(24),Jwcons(varN,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwlist3(Jmakeope(";"),Jwcons(2025,Jwlist2(Jwcons(64,Jwlist2(Jwlist3(Jmakeope("/\\"),varPushPattern,Jwlist3(Jmakeope("<<"),Jmakeint(1),varN,th),th),Jmakeint(0),th),th),Jwcons(1212,Jwcons(Jmakeconst("1"),NIL,th),th),th),th),Jwcons(1212,Jwcons(Jmakeconst("0"),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(187,Jwlist2(varM,Jwlist3(Jmakeope("mod"),varN,Jmakeint(5),th),th),th),Jwlist3(Jmakeope(","),Jwlist3(Jmakeope(";"),Jwcons(2025,Jwlist2(Jwcons(209,Jwlist2(varM,Jmakeint(4),th),th),816,th),th),1198,th),601,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
ano_1 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,ano_1,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("print_answer"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("run_all",b_run_all);
(deftpred)("show",b_show);
(deftpred)("test1",b_test1);
(deftpred)("test2",b_test2);
(deftpred)("test3",b_test3);
(deftpred)("test4",b_test4);
(deftpred)("print_answer",b_print_answer);
}
void init_declare(void){int body,th; th=0;
}