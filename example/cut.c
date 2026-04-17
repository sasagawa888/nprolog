#include "jump.h"
static int b_ticket(int arglist, int rest, int th);
static int b_ticket(int arglist, int rest, int th){
int arg1,arg2,varAge,varMoney,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varAge = Jmakevariant(th);
varMoney = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varAge,th) == YES && Junify_var(arg2,varMoney,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(77,Jwlist2(varAge,Jmakeint(13),th),th),Jwcons(187,Jwlist2(varMoney,Jmakeint(500),th),th),th);
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
varAge = Jmakevariant(th);
varMoney = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varAge,th) == YES && Junify_var(arg2,varMoney,th) == YES && 1)
{body = Jwcons(187,Jwlist2(varMoney,Jmakeint(1000),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ticket"),arglist);
return(NO);}
static int b_take_integer(int arglist, int rest, int th);
static int b_take_integer(int arglist, int rest, int th){
int arg1,arg2,varYs1,varYs2,varX,varXs,varYs,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varYs1 = Jmakevariant(th);
varYs2 = Jmakevariant(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
varYs = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varXs,th),th) == YES && Junify_var(arg2,varYs,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("take_integer"),Jwcons(varX,Jwcons(varYs1,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("take_integer"),Jwcons(varXs,Jwcons(varYs2,NIL,th),th),th),Jwcons(1240,Jwcons(varYs1,Jwcons(varYs2,Jwcons(varYs,NIL,th),th),th),th),th),th);
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
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify(arg2,Jwlistcons(varX,NIL,th),th) == YES && 1)
{body = Jwcons(725,Jwcons(varX,NIL,th),th);
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
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify_nil(arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varYs1 = Jmakevariant(th);
varYs2 = Jmakevariant(th);
varX = Jmakevariant(th);
varXs = Jmakevariant(th);
varYs = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(varX,varXs,th),th) == YES && Junify_var(arg2,varYs,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("take_integer"),Jwcons(varX,Jwcons(varYs1,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("take_integer"),Jwcons(varXs,Jwcons(varYs2,NIL,th),th),th),Jwcons(1240,Jwcons(varYs1,Jwcons(varYs2,Jwcons(varYs,NIL,th),th),th),th),th),th);
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
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify(arg2,Jwlistcons(varX,NIL,th),th) == YES && 1)
{body = Jwcons(725,Jwcons(varX,NIL,th),th);
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
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify_nil(arg2,th) == YES && 1)
if(Jexec_all(rest,Jget_sp(th),th) == YES) return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("take_integer"),arglist);
return(NO);}
static int b_fact(int arglist, int rest, int th);
static int b_fact(int arglist, int rest, int th){
int arg1,arg2,varX1,varY1,varX,varY,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
save1 = Jget_wp(th);
if(Junify_int(arg1,Jmakeint(0),th) == YES && Junify_int(arg2,Jmakeint(1),th) == YES && 1)

return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
varX1 = Jmakevariant(th);
varY1 = Jmakevariant(th);
varX = Jmakevariant(th);
varY = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varX,th) == YES && Junify_var(arg2,varY,th) == YES && 1)
if(Junify(varX1,Jminus(Jderef(varX,th),Jmakeint(1),th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("fact"),Jwlistcons(varX1,Jwlistcons(varY1,NIL,th),th),th) == YES)
if(Junify(varY,Jmult(Jderef(varX,th),Jderef(varY1,th),th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
static int b_yes_or_no(int arglist, int rest, int th);
static int b_yes_or_no(int arglist, int rest, int th){
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
if (Jcall(1234,NIL,th) == YES)
if (Jcall(1212,Jwlistcons(Jmakeconst("yes or no >"),NIL,th),th) == YES)
if (Jcall(912,Jwlistcons(varX,NIL,th),th) == YES)
if (Jcall(