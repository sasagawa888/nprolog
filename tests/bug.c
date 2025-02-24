#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,varX1,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && 1)
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
varX1 = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && 1)
if (Jcall(1159,Jwlistcons(varX,NIL,th),th) == YES)if(Junify(varX1,Jminus(Jderef(varX,th),Jmakeint(1),th),th)==YES && Jinc_proof(th)){
arg1 = Jcopy_work(Jderef(varX1,th),th);
Junbind(save2,th);
Jset_ac(save3,th);
goto loop1;
}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}