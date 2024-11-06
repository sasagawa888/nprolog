#include "jump.h"
int b_partition(int arglist, int rest);
int b_partition(int arglist, int rest){
int arg1,arg2,arg3,arg4,var_1,varL,varY,varX,varL1,varL2,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
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
{body = Jwcons(68,Jwcons(varX,Jwcons(varY,NIL)));
if(Jexec_all(body,Jget_sp()) == YES){
body = Jwcons(68,Jwcons(varX,Jwcons(varY,NIL)));
if(Jexec_all(Jaddtail_body(rest,body),Jget_sp()) == YES)
return(YES);
else{Junbind(save2);Jset_wp(save1);return(FALSE);}}
Junbind(save2);
Jset_wp(save1);}
varL = Jmakevariant();
varY = Jmakevariant();
varL1 = Jmakevariant();
varX = Jmakevariant();
varL2 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varX,varL),arg1) == YES && Junify_var(varY,arg2) == YES && Junify_var(varL1,arg3) == YES && Junify(Jwlistcons(varX,varL2),arg4) == YES && 1)
{body = NIL;
if(Jexec_all(body,Jget_sp()) == YES){
body = NIL;
if(Jexec_all(Jaddtail_body(rest,body),Jget_sp()) == YES)
return(YES);
else{Junbind(save2);Jset_wp(save1);return(FALSE);}}
Junbind(save2);
Jset_wp(save1);}
var_1 = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify_nil(NIL,arg3) == YES && Junify_nil(NIL,arg4) == YES && 1)
{body = NIL;
if(Jexec_all(body,Jget_sp()) == YES){
body = NIL;
if(Jexec_all(Jaddtail_body(rest,body),Jget_sp()) == YES)
return(YES);
else{Junbind(save2);Jset_wp(save1);return(FALSE);}}
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("partition"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("partition",b_partition);
}
void init_declare(void){int body;
}