#include "jump.h"
int b_test16(int arglist, int rest);
int b_test16(int arglist, int rest){
int varX,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 0){
varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(1115,Jwcons(Jmakeint(1),Jwcons(Jmakeint(16),Jwcons(varX,NIL)))),Jwlist3(Jmakeope(","),Jmakecomp("test1"),532));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test16"),arglist);
return(NO);}
int b_test(int arglist, int rest);
int b_test(int arglist, int rest){
int varX,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 0){
varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("queen"),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL))))))))),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(1041,Jwcons(varX,NIL)),Jwlist3(Jmakeope(","),735,532)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
int b_test1(int arglist, int rest);
int b_test1(int arglist, int rest){
int varX,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 0){
varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("queen"),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL))))))))),Jwcons(varX,NIL))),532);
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test1"),arglist);
return(NO);}
int b_queen(int arglist, int rest);
int b_queen(int arglist, int rest){
int arg1,arg2,varData,varOut,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varData = Jmakevariant();
varOut = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varData,arg1) == YES && Junify_var(varOut,arg2) == YES && 1)
{body = Jwcons(Jmakecomp("queen_2"),Jwcons(varData,Jwcons(NIL,Jwcons(varOut,NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("queen"),arglist);
return(NO);}
int b_queen_2(int arglist, int rest);
int b_queen_2(int arglist, int rest){
int arg1,arg2,arg3,varL1,varH,varT,varHistory,varQ,varM,var_1,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
var_1 = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify_nil(NIL,arg3) == YES && 1)
if(Jprove_all(rest,Jget_sp()) == YES)
return(YES);
Jset_up(save3);
Junbind(save2);
Jset_wp(save1);
varL1 = Jmakevariant();
varH = Jmakevariant();
varT = Jmakevariant();
varHistory = Jmakevariant();
varQ = Jmakevariant();
varM = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varH,varT),arg1) == YES && Junify_var(varHistory,arg2) == YES && Junify(Jwlistcons(varQ,varM),arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qdelete"),Jwcons(varQ,Jwcons(varH,Jwcons(varT,Jwcons(varL1,NIL))))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("nodiag"),Jwcons(varHistory,Jwcons(varQ,Jwcons(Jmakeint(1),NIL)))),Jwcons(Jmakecomp("queen_2"),Jwcons(varL1,Jwcons(Jwlistcons(varQ,varHistory),Jwcons(varM,NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("queen_2"),arglist);
return(NO);}
int b_qdelete(int arglist, int rest);
int b_qdelete(int arglist, int rest){
int arg1,arg2,arg3,arg4,varX,varH,varT,varR,varA,varL,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
varA = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varA,arg1) == YES && Junify_var(varA,arg2) == YES && Junify_var(varL,arg3) == YES && Junify_var(varL,arg4) == YES && 1)
if(Jprove_all(rest,Jget_sp()) == YES)
return(YES);
Jset_up(save3);
Junbind(save2);
Jset_wp(save1);
varX = Jmakevariant();
varH = Jmakevariant();
varT = Jmakevariant();
varA = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varA,arg2) == YES && Junify(Jwlistcons(varH,varT),arg3) == YES && Junify(Jwlistcons(varA,varR),arg4) == YES && 1)
{body = Jwcons(Jmakecomp("qdelete"),Jwcons(varX,Jwcons(varH,Jwcons(varT,Jwcons(varR,NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO); 
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("qdelete"),arglist);
return(NO);}
int b_nodiag(int arglist, int rest);
int b_nodiag(int arglist, int rest){
int n,head,varD1,varN,varL,varB,varD,var_2,var_1;
n = Jlength(arglist);
if(n == 3){
loop:
Jinc_proof();
var_2 = Jmakevariant();
var_1 = Jmakevariant();
head = Jwcons(NIL,Jwcons(var_2,Jwcons(var_1,NIL)));
if(Jcar(arglist) == NIL && 1){if(Junify(arglist,head)==YES) return(Jprove_all(rest,Jget_sp())); else return(NO);}
varN = Jcar(Jcar(arglist));
varL = Jcdr(Jcar(arglist));
varB = Jcar(Jcdr(arglist));
varD = Jcar(Jcdr(Jcdr(arglist)));
{if(!Jnot_numeqp(Jderef(varD),Jminus(Jderef(varN),Jderef(varB)))) return(NO);
if(!Jnot_numeqp(Jderef(varD),Jminus(Jderef(varB),Jderef(varN)))) return(NO);
varD1 = Jplus(Jderef(varD),Jmakeint(1));
arglist = Jwcons(varL,Jwcons(varB,Jwcons(varD1,NIL)));
goto loop;
}}return(NO);
}
void init_tpredicate(void){(deftpred)("test16",b_test16);
(deftpred)("test",b_test);
(deftpred)("test1",b_test1);
(deftpred)("queen",b_queen);
(deftpred)("queen_2",b_queen_2);
(deftpred)("qdelete",b_qdelete);
(deftpred)("nodiag",b_nodiag);
}
void init_declare(void){int body;
}