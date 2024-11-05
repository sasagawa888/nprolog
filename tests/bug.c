#include "jump.h"
int b_qdelete(int arglist, int rest);
int b_qdelete(int arglist, int rest){
int arg1,arg2,arg3,arg4,varX,varH,varT,varR,varA,varL,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
varA = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varA,arg1) == YES && Junify_var(varA,arg2) == YES && Junify_var(varL,arg3) == YES && Junify_var(varL,arg4) == YES && 1)
{if(rest == NIL) return(YES);
if(Jprove_all(rest,Jget_sp()) == YES) return(YES);}
Junbind(save2);
Jset_wp(save1);
varX = Jmakevariant();
varH = Jmakevariant();
varT = Jmakevariant();
varA = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varA,arg2) == YES && Junify(Jwlistcons(varH,varT),arg3) == YES && Junify(Jwlistcons(varA,varR),arg4) == YES && 1)
{goal = Jwcons(Jmakecomp("qdelete"),Jwcons(varX,Jwcons(varH,Jwcons(varT,Jwcons(varR,NIL)))));
cont = NIL;
if(Jcps(goal,cont) == YES){
if(rest==NIL) return(YES);
if(Jprove_all(rest,Jget_sp())==YES)
return(YES);}}
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("qdelete"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("qdelete",b_qdelete);
}
void init_declare(void){int body;
}