#include "jump.h"
int b_foo(int arglist, int rest);
int b_foo(int arglist, int rest){
int arg1,varY,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varY = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && 1)
{goal = Jwcons(Jmakecomp("bar"),Jwcons(varX,Jwcons(varY,NIL)));
cont = Jwcons(1197,Jwcons(varY,NIL));
if(Jcps(goal,cont) == YES){
if(rest != NIL) Jprove_all(rest,Jget_sp());
return(YES);}}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("foo"),arglist);
return(NO);}
int b_bar(int arglist, int rest);
int b_bar(int arglist, int rest){
int arg1,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && 1)
{goal = 586;
cont = NIL;
if(Jcps(goal,cont) == YES){
if(rest != NIL) Jprove_all(rest,Jget_sp());
return(YES);}}
Junbind(save2);
Jset_wp(save1);
{goal = 586;
cont = NIL;
if(Jcps(goal,cont) == YES){
if(rest != NIL) Jprove_all(rest,Jget_sp());
return(YES);}}
Junbind(save2);
Jset_wp(save1);
{goal = 1183;
cont = NIL;
if(Jcps(goal,cont) == YES){
if(rest != NIL) Jprove_all(rest,Jget_sp());
return(YES);}}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("bar"),arglist);
return(NO);}
int b_boo(int arglist, int rest);
int b_boo(int arglist, int rest){
int arg1,varY,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varY = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && 1)
{goal = Jwcons(1197,Jwcons(varX,NIL));
cont = NIL;
if(Jcps(goal,cont) == YES){
{goal = Jwcons(1197,Jwcons(varY,NIL));
cont = NIL;
if(Jcps(goal,cont) == YES){
if(rest != NIL) Jprove_all(rest,Jget_sp());
return(YES);}}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(YES);}}
Junbind(save2);
Jset_wp(save1);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("boo"),arglist);
return(NO);}
int b_fact(int arglist, int rest);
int b_fact(int arglist, int rest){
int arg1,arg2,varN1,varX1,varN,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_const(Jmakeint(0),arg1) == YES && Junify_const(Jmakeint(1),arg2) == YES && 1)
{if(rest == NIL) return(YES);
if(Jprove_all(rest,Jget_sp()) == YES) return(YES);}
Junbind(save2);
Jset_wp(save1);
varN1 = Jmakevariant();
varX1 = Jmakevariant();
varN = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varN,arg1) == YES && Junify_var(varX,arg2) == YES && 1)
{goal = Jwcons(168,Jwcons(varN1,Jwcons(Jwcons(1395,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL)));
cont = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("fact"),Jwcons(varN1,Jwcons(varX1,NIL))),Jwcons(168,Jwcons(varX,Jwcons(Jwcons(1436,Jwcons(varN,Jwcons(varX1,NIL))),NIL))));
if(Jcps(goal,cont) == YES){
if(rest != NIL) Jprove_all(rest,Jget_sp());
return(YES);}}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("foo",b_foo);
(deftpred)("bar",b_bar);
(deftpred)("boo",b_boo);
(deftpred)("fact",b_fact);
}
void init_declare(void){int body;
}