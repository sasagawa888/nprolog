#include "jump.h"
int b_test(int arglist, int rest);
int b_test(int arglist, int rest){
int arg1,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && 1)
{body = 
Jwcons(178,Jwcons(varX,Jwcons(Jmakeint(1),NIL)));
if(Jexec_all(Jaddtail_body(rest,body),Jget_sp()) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
body = 
Jwcons(178,Jwcons(varX,Jwcons(Jmakeint(2),NIL)));
if(Jexec_all(Jaddtail_body(rest,body),Jget_sp()) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("test",b_test);
}
void init_declare(void){int body;
}