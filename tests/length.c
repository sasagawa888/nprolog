#include "jump.h"
int b_len(int arglist, int rest);
int b_len(int arglist, int rest){
int arg1,arg2,varN1,var_1,varLs,varN,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify_const(Jmakeint(0),arg2) == YES && 1)
if(Jprove_all(rest,Jget_sp()) == YES)
return(YES);
Jset_up(save3);
Junbind(save2);
Jset_wp(save1);
varN1 = Jmakevariant();
var_1 = Jmakevariant();
varLs = Jmakevariant();
varN = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(var_1,varLs),arg1) == YES && Junify_var(varN,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("len"),Jwcons(varLs,Jwcons(varN1,NIL))),Jwcons(166,Jwcons(varN,Jwcons(Jwcons(1260,Jwcons(varN1,Jwcons(Jmakeint(1),NIL))),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("len"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("len",b_len);
}
void init_declare(void){int body;
}