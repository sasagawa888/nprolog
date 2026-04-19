#include "jump.h"
static int b_run(int arglist, int rest, int th);
static int b_run(int arglist, int rest, int th){
int arg1,varTest,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varTest = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varTest,th) == YES && 1)
if (Jcall(1212,Jwlistcons(varTest,NIL,th),th) == YES)
if (Jcall(1212,Jwlistcons(Jmakeconst(" : "),NIL,th),th) == YES)
if (Jcall(Jmakesys("case"),Jwlist1(Jwlistcons(Jwcons(38,Jwcons(Jwcons(20,Jwcons(varTest,NIL,th),th),Jwcons(Jwcons(Jmakepred("writeln"),Jwcons(Jmakeconst("ok"),NIL,th),th),NIL,th),th),th),Jwcons(Jmakepred("writeln"),Jwcons(601,NIL,th),th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("run"),arglist);
return(NO);}
static int b_foo(int arglist, int rest, int th);
static int b_foo(int arglist, int rest, int th){
int arg1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jcall(20,Jwlistcons(varX,NIL,th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("run",b_run);
(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}