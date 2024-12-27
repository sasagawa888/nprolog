#include "jump.h"
int b_boo(int arglist, int rest, int th);
int b_boo(int arglist, int rest, int th){
int arg1,arg2,varN1,varN,varM,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp(th);
if(Junify_const(Jmakeint(0),arg1,th) == YES && Junify_nil(NIL,arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varN1 = Jmakevariant(th);
varN = Jmakevariant(th);
varM = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varN,arg1,th) == YES && Junify(Jwlistcons(varN,varM,th),arg2,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(172,Jwcons(varN1,Jwcons(Jwcons(1517,Jwcons(varN,Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th),th),Jwcons(Jmakecomp("boo"),Jwcons(varN1,Jwcons(varM,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NFALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("boo"),arglist);
return(NO);}
int b_foo(int arglist, int rest, int th);
int b_foo(int arglist, int rest, int th){
int n,head,varN1,varN;
n = Jlength(arglist);
if(n == 1){
loop:
Jinc_proof(th);
head = Jwcons(Jmakeint(0),NIL,th);
if(Jnumeqp(Jmakeint(0),Jcar(arglist)) && 
1){if(Junify(arglist,head,th)==YES) return(Jexec_all(rest,Jget_sp(th),th)); else return(NO);}
varN = Jcar(arglist);
{varN1 = Jminus(Jderef(varN,th),Jmakeint(1));
arglist = Jwcons(varN1,NIL,th);
goto loop;
}}return(NO);
}
void init_tpredicate(void){(deftpred)("boo",b_boo);
(deftpred)("foo",b_foo);
}
void init_declare(void){int body;
}