#include "jump.h"
int b_maplist(int arglist, int rest, int th);
int b_maplist(int arglist, int rest, int th){
int arg1,arg2,varE,varEs,varP,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varP = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varP,arg1,th) == YES && Junify_nil(arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Junbind(save2,th);
Jset_wp(save1,th);
varP = Jmakevariant(th);
varE = Jmakevariant(th);
varEs = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(varP,arg1,th) == YES && Junify(Jwlistcons(varE,varEs,th),arg2,th) == YES && 1)
{body = Jwcons(Jmakecomp("maplist"),Jwcons(varP,Jwcons(varEs,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("maplist"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("maplist",b_maplist);
}
void init_declare(void){int body,th; th=0;
}