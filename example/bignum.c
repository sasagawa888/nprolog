#include "jump.h"
int b_fact(int arglist, int rest, int th);
int b_fact(int arglist, int rest, int th){
int arg1,arg2,varN1,varA1,varN,varA,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp(th);
if(Junify_const(Jmakeint(0),arg1,th) == YES && Junify_const(Jmakeint(1),arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varN1 = Jmakevariant(th);
varA1 = Jmakevariant(th);
varN = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varN,arg1,th) == YES && Junify_var(varA,arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(172,Jwcons(varN1,Jwcons(Jwcons(1803,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("fact"),Jwcons(varN1,Jwcons(varA1,NIL,th),th),th),Jwcons(172,Jwcons(varA,Jwcons(Jwcons(1844,Jwcons(varN,Jwcons(varA1,NIL,th),th),th),NIL,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void foo(void){dynamic_clause = Jlist3(Jmakeope(":-"),Jcons(Jmakepred("foo"),Jcons(Jmakevar("varX"),Jcons(Jmakevar("varY"),NIL))),Jcons(172,Jcons(Jmakevar("varY"),Jcons(Jcons(1762,Jcons(Jmakevar("varX"),Jcons(Jmakebig("111111111111111111111111111111111111111111111111111111111111111111111"),NIL))),NIL))));
Jadd_dynamic(dynamic_clause);
}void init_tpredicate(void){(deftpred)("fact",b_fact);
}
void init_declare(void){int body,th; th=0;
foo();
}