#include "jump.h"
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int arg1,arg2,varN1,varX,varXs,varN,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_const(Jmakeint(0),arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varN1 = Jmakevariant(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
varN = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(Jwlistcons(varX,varXs,th),arg1,th) == YES && Junify_var(varN,arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("foo"),Jwcons(varXs,Jwcons(varN1,NIL,th),th),th),Jwcons(172,Jwcons(varN,Jwcons(Jwcons(1476,Jwcons(varN1,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
}
void init_declare(void){int body,th; th=0;
}