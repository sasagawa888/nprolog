#include "jump.h"
int b_sum1(int arglist, int rest);
int b_sum1(int arglist, int rest){
int arg1,arg2,varI,varS,varJ,varS1,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_const(Jmakeint(0),arg1) == YES && Junify_const(Jmakeint(0),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varI = Jmakevariant();
varS = Jmakevariant();
varJ = Jmakevariant();
varS1 = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varJ,arg1) == YES && Junify_var(varS1,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varI,Jwcons(Jwcons(1395,Jwcons(varJ,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("sum1"),Jwcons(varI,Jwcons(varS,NIL))),Jwcons(168,Jwcons(varS1,Jwcons(Jwcons(1354,Jwcons(varS,Jwcons(varJ,NIL))),NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("sum1"),arglist);
return(NO);}
int b_sum2(int arglist, int rest);
int b_sum2(int arglist, int rest){
int arg1,arg2,varI,varS,varJ,varS1,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_const(Jmakeint(0),arg1) == YES && Junify_const(Jmakeint(0),arg2) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
varI = Jmakevariant();
varS = Jmakevariant();
varJ = Jmakevariant();
varS1 = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varJ,arg1) == YES && Junify_var(varS1,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(56,Jwcons(varJ,Jwcons(Jmakeint(0),NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varI,Jwcons(Jwcons(1395,Jwcons(varJ,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("sum2"),Jwcons(varI,Jwcons(varS,NIL))),Jwcons(168,Jwcons(varS1,Jwcons(Jwcons(1354,Jwcons(varS,Jwcons(varJ,NIL))),NIL))))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("sum2"),arglist);
return(NO);}
int b_sigma(int arglist, int rest);
int b_sigma(int arglist, int rest){
int arg1,arg2,varC,varA,varB,varSum,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varC = Jmakevariant();
varA = Jmakevariant();
varB = Jmakevariant();
varSum = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(1395,Jwcons(varA,Jwcons(varB,NIL))),arg1) == YES && Junify_var(varSum,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varC,Jwcons(Jwcons(1395,Jwcons(varB,Jwcons(varA,NIL))),NIL))),Jwcons(Jmakecomp("sigma_aux"),Jwcons(Jwlistcons(varA,Jwlistcons(varC,Jwlistcons(varSum,NIL))),Jwcons(Jmakeint(0),Jwcons(varA,NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("sigma"),arglist);
return(NO);}
int b_sigma_aux(int arglist, int rest);
int b_sigma_aux(int arglist, int rest){
int arg1,arg2,arg3,var_1,varN1,varSum1,varConst,varN,varA,varC,varSum,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varA = Jmakevariant();
varC = Jmakevariant();
varSum = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,Jwlistcons(varC,Jwlistcons(varSum,NIL))),arg1) == YES && Junify_var(varC,arg2) == YES && Junify_var(varSum,arg3) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
var_1 = Jmakevariant();
varA = Jmakevariant();
varN1 = Jmakevariant();
varSum1 = Jmakevariant();
varConst = Jmakevariant();
varN = Jmakevariant();
varSum = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varConst,arg1) == YES && Junify_var(varN,arg2) == YES && Junify_var(varSum,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(178,Jwcons(varConst,Jwcons(Jwlistcons(varA,var_1),NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varN1,Jwcons(Jwcons(1354,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varSum1,Jwcons(Jwcons(1354,Jwcons(Jwcons(1354,Jwcons(varSum,Jwcons(varN1,NIL))),Jwcons(varA,NIL))),NIL))),Jwcons(Jmakecomp("sigma_aux"),Jwcons(varConst,Jwcons(varN1,Jwcons(varSum1,NIL)))))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("sigma_aux"),arglist);
return(NO);}
int b_not0(int arglist, int rest);
int b_not0(int arglist, int rest){
int arg1,varP,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varP = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varP,arg1) == YES && 1)
{body = Jwcons(20,Jwcons(varP,NIL));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = 586;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varP = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varP,arg1) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("not0"),arglist);
return(NO);}
int b_for(int arglist, int rest);
int b_for(int arglist, int rest){
int arg1,arg2,varI1,varK,varJ,varI,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varI = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(78,Jwcons(varI,Jwcons(varI,NIL))),arg1) == YES && Junify_var(varI,arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varJ = Jmakevariant();
varI = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(78,Jwcons(varI,Jwcons(varJ,NIL))),arg1) == YES && Junify_var(varI,arg2) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
varI1 = Jmakevariant();
varI = Jmakevariant();
varJ = Jmakevariant();
varK = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(78,Jwcons(varI,Jwcons(varJ,NIL))),arg1) == YES && Junify_var(varK,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varI1,Jwcons(Jwcons(1354,Jwcons(varI,Jwcons(Jmakeint(1),NIL))),NIL))),Jwcons(Jmakecomp("for"),Jwcons(Jwcons(78,Jwcons(varI1,Jwcons(varJ,NIL))),Jwcons(varK,NIL))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("for"),arglist);
return(NO);}
int b_f99(int arglist, int rest);
int b_f99(int arglist, int rest){
int varZ,varX,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 0){
varZ = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("for"),Jwcons(Jwcons(78,Jwcons(Jmakeint(1),Jwcons(Jmakeint(9),NIL))),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("for"),Jwcons(Jwcons(78,Jwcons(Jmakeint(1),Jwcons(Jmakeint(9),NIL))),Jwcons(varY,NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varZ,Jwcons(Jwcons(1436,Jwcons(varX,Jwcons(varY,NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(1197,Jwcons(Jwcons(178,Jwcons(varZ,Jwcons(Jwcons(1436,Jwcons(varX,Jwcons(varY,NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),807,586)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("f99"),arglist);
return(NO);}
int b_test(int arglist, int rest);
int b_test(int arglist, int rest){
int varX,varA,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 0){
varX = Jmakevariant();
varA = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(178,Jwcons(varX,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),NIL))))),NIL))),Jwlist3(Jmakeope(","),Jwcons(1235,Jwcons(varA,Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(1197,Jwcons(varA,NIL)),Jwlist3(Jmakeope(","),Jwcons(1143,Jwcons(Jmakeint(1),NIL)),586))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
int b_positive(int arglist, int rest);
int b_positive(int arglist, int rest){
int arg1,varX,varL,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varL,arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(1235,Jwcons(varX,Jwcons(varL,NIL))),Jwcons(40,Jwcons(Jwcons(56,Jwcons(varX,Jwcons(Jmakeint(0),NIL))),Jwcons(586,Jwcons(Jwcons(12,Jwcons(10,Jwcons(586,NIL))),NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varL,arg1) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("positive"),arglist);
return(NO);}
int b_member2(int arglist, int rest);
int b_member2(int arglist, int rest){
int arg1,arg2,arg3,var_1,varB,varA,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varB = Jmakevariant();
varA = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varA,arg1) == YES && Junify_var(varB,arg2) == YES && Junify(Jwlistcons(varA,varY),arg3) == YES && 1)
{body = Jwcons(1235,Jwcons(varB,Jwcons(varY,NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varA = Jmakevariant();
varB = Jmakevariant();
var_1 = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varA,arg1) == YES && Junify_var(varB,arg2) == YES && Junify(Jwlistcons(var_1,varY),arg3) == YES && 1)
{body = Jwcons(Jmakecomp("member2"),Jwcons(varA,Jwcons(varB,Jwcons(varY,NIL))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("member2"),arglist);
return(NO);}
int b_set(int arglist, int rest);
int b_set(int arglist, int rest){
int arg1,varL0,varM0,varL,varM,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varL0 = Jmakevariant();
varM0 = Jmakevariant();
varL = Jmakevariant();
varM = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(188,Jwcons(varL,Jwcons(varM,NIL))),arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(1069,Jwcons(varL,Jwcons(varL0,NIL))),Jwlist3(Jmakeope(","),Jwcons(1069,Jwcons(varM,Jwcons(varM0,NIL))),Jwcons(188,Jwcons(varL0,Jwcons(varM0,NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varL0 = Jmakevariant();
varM0 = Jmakevariant();
varL = Jmakevariant();
varM = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(188,Jwcons(varL,Jwcons(varM,NIL))),arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(1069,Jwcons(varL,Jwcons(varL0,NIL))),Jwlist3(Jmakeope(","),Jwcons(1069,Jwcons(varM,Jwcons(varM0,NIL))),Jwcons(188,Jwcons(varL,Jwcons(varM0,NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("set"),arglist);
return(NO);}
int b_isl(int arglist, int rest);
int b_isl(int arglist, int rest){
int arg1,arg2,varLC,varC,varCL,varLA,varZ,varA,varX,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varY,arg1) == YES && Junify(Jwcons(1354,Jwcons(NIL,Jwcons(varY,NIL))),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varZ,arg1) == YES && Junify(Jwcons(1354,Jwcons(Jwlistcons(varA,varX),Jwcons(varY,NIL))),arg2) == YES && 1)
{body = Jwcons(1235,Jwcons(varA,Jwcons(varY,NIL)));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1354,Jwcons(varX,Jwcons(varY,NIL))),NIL)));
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,varZ),arg1) == YES && Junify(Jwcons(1354,Jwcons(Jwlistcons(varA,varX),Jwcons(varY,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1354,Jwcons(varX,Jwcons(varY,NIL))),NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varY,arg1) == YES && Junify(Jwcons(1354,Jwcons(NIL,Jwcons(varY,NIL))),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varZ,arg1) == YES && Junify(Jwcons(1354,Jwcons(Jwlistcons(varA,varX),Jwcons(varY,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("memberd"),Jwcons(varA,Jwcons(varY,NIL)));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1354,Jwcons(varX,Jwcons(varY,NIL))),NIL)));
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,varZ),arg1) == YES && Junify(Jwcons(1354,Jwcons(Jwlistcons(varA,varX),Jwcons(varY,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1354,Jwcons(varX,Jwcons(varY,NIL))),NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify(Jwcons(1436,Jwcons(NIL,Jwcons(varY,NIL))),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varX = Jmakevariant();
varA = Jmakevariant();
varZ = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,varZ),arg1) == YES && Junify(Jwcons(1436,Jwcons(Jwlistcons(varA,varZ),Jwcons(varY,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("memberd"),Jwcons(varA,Jwcons(varX,NIL)));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1436,Jwcons(varX,Jwcons(varY,NIL))),NIL)));
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varZ,arg1) == YES && Junify(Jwcons(1436,Jwcons(Jwlistcons(varA,varX),Jwcons(varY,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1436,Jwcons(varX,Jwcons(varY,NIL))),NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify(Jwcons(1395,Jwcons(NIL,Jwcons(varA,NIL))),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varLA = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varZ,arg1) == YES && Junify(Jwcons(1395,Jwcons(Jwlistcons(varA,varLA),Jwcons(varX,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("memberd"),Jwcons(varA,Jwcons(varX,NIL)));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1395,Jwcons(varLA,Jwcons(varX,NIL))),NIL)));
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varZ = Jmakevariant();
varA = Jmakevariant();
varLA = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,varZ),arg1) == YES && Junify(Jwcons(1395,Jwcons(Jwlistcons(varA,varLA),Jwcons(varX,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varZ,Jwcons(Jwcons(1395,Jwcons(varLA,Jwcons(varX,NIL))),NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify(Jwcons(52,Jwcons(NIL,Jwcons(varA,NIL))),arg2) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
varX = Jmakevariant();
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify(Jwcons(52,Jwcons(Jwlistcons(varA,varX),Jwcons(varA,NIL))),arg2) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varLC = Jmakevariant();
varX = Jmakevariant();
varC = Jmakevariant();
varCL = Jmakevariant();
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varC,varX),arg1) == YES && Junify(Jwcons(52,Jwcons(Jwlistcons(varC,varCL),Jwcons(varA,NIL))),arg2) == YES && 1)
{body = Jwcons(Jmakecomp("isl"),Jwcons(varX,Jwcons(Jwcons(52,Jwcons(varLC,Jwcons(varA,NIL))),NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("isl"),arglist);
return(NO);}
int b_memberr(int arglist, int rest);
int b_memberr(int arglist, int rest){
int arg1,arg2,arg3,var_1,varR1,varLA,varY,varR,varA,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varA = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,NIL),arg1) == YES && Junify_var(varX,arg2) == YES && Junify_const(Jmakeint(1),arg3) == YES && 1)
{body = Jwcons(1235,Jwcons(varA,Jwcons(varX,NIL)));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varR1 = Jmakevariant();
varLA = Jmakevariant();
varA = Jmakevariant();
varY = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,varLA),arg1) == YES && Junify(Jwlistcons(varA,varY),arg2) == YES && Junify_var(varR,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(56,Jwcons(varR,Jwcons(Jmakeint(1),NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varR1,Jwcons(Jwcons(1395,Jwcons(varR,Jwcons(Jmakeint(1),NIL))),NIL))),Jwcons(Jmakecomp("memberr"),Jwcons(varLA,Jwcons(varY,Jwcons(varR1,NIL))))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varA = Jmakevariant();
var_1 = Jmakevariant();
varY = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varA,arg1) == YES && Junify(Jwlistcons(var_1,varY),arg2) == YES && Junify_var(varR,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(56,Jwcons(varR,Jwcons(Jmakeint(1),NIL))),Jwcons(Jmakecomp("memberr"),Jwcons(varA,Jwcons(varY,Jwcons(varR,NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("memberr"),arglist);
return(NO);}
int b_generate_e(int arglist, int rest);
int b_generate_e(int arglist, int rest){
int arg1,arg2,varN,varE,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varN = Jmakevariant();
varE = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varN,arg1) == YES && Junify_var(varE,arg2) == YES && 1)
{body = Jwcons(Jmakecomp("gene_e_aux"),Jwcons(varE,Jwcons(varN,Jwcons(NIL,NIL))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("generate_e"),arglist);
return(NO);}
int b_gene_e_aux(int arglist, int rest);
int b_gene_e_aux(int arglist, int rest){
int arg1,arg2,arg3,varN1,varResult,varN,varL,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varL,arg1) == YES && Junify_const(Jmakeint(0),arg2) == YES && Junify_var(varL,arg3) == YES && 1)
{body = NIL;
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varN1 = Jmakevariant();
varResult = Jmakevariant();
varN = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varResult,arg1) == YES && Junify_var(varN,arg2) == YES && Junify_var(varL,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varN1,Jwcons(Jwcons(1395,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL))),Jwcons(Jmakecomp("gene_e_aux"),Jwcons(varResult,Jwcons(varN1,Jwcons(Jwlistcons(varN,varL),NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("gene_e_aux"),arglist);
return(NO);}
int b_comb(int arglist, int rest);
int b_comb(int arglist, int rest){
int arg1,arg2,varX,varA,varN,varR,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varX = Jmakevariant();
varA = Jmakevariant();
varN = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varN,arg1) == YES && Junify_var(varR,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("generate_e"),Jwcons(varN,Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("memberr"),Jwcons(varA,Jwcons(varX,Jwcons(varR,NIL)))),Jwlist3(Jmakeope(","),Jwcons(1197,Jwcons(varA,NIL)),Jwlist3(Jmakeope(","),807,586))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("comb"),arglist);
return(NO);}
int b_permutation(int arglist, int rest);
int b_permutation(int arglist, int rest){
int arg1,arg2,varY1,varA,varX1,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify_nil(NIL,arg2) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
varY1 = Jmakevariant();
varA = Jmakevariant();
varX1 = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varA,varX1),arg1) == YES && Junify_var(varY,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("delete0"),Jwcons(Jwcons(178,Jwcons(varY1,Jwcons(Jwcons(1395,Jwcons(varY,Jwcons(varA,NIL))),NIL))),NIL)),Jwcons(Jmakecomp("permutation"),Jwcons(varX1,Jwcons(varY1,NIL))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("permutation"),arglist);
return(NO);}
int b_delete0(int arglist, int rest);
int b_delete0(int arglist, int rest){
int arg1,varY,varB,varX,varA,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varX = Jmakevariant();
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(178,Jwcons(varX,Jwcons(Jwcons(1395,Jwcons(Jwlistcons(varA,varX),Jwcons(varA,NIL))),NIL))),arg1) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
varY = Jmakevariant();
varB = Jmakevariant();
varX = Jmakevariant();
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(178,Jwcons(Jwlistcons(varB,varY),Jwcons(Jwcons(1395,Jwcons(Jwlistcons(varB,varX),Jwcons(varA,NIL))),NIL))),arg1) == YES && 1)
{body = Jwcons(Jmakecomp("delete0"),Jwcons(Jwcons(178,Jwcons(varY,Jwcons(Jwcons(1395,Jwcons(varX,Jwcons(varA,NIL))),NIL))),NIL));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("delete0"),arglist);
return(NO);}
int b_newton(int arglist, int rest);
int b_newton(int arglist, int rest){
int arg1,arg2,varX,varA,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varX = Jmakevariant();
varA = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varA,arg2) == YES && 1)
{body = Jwcons(Jmakecomp("newton1"),Jwcons(Jmakestrflt("1.0"),Jwcons(varA,Jwcons(varA,Jwcons(varX,NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("newton"),arglist);
return(NO);}
int b_newton1(int arglist, int rest);
int b_newton1(int arglist, int rest){
int arg1,arg2,arg3,arg4,varY,varX1,varX2,varA,varX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
varX1 = Jmakevariant();
varX2 = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX1,arg1) == YES && Junify_var(varX2,arg2) == YES && Junify_var(varA,arg3) == YES && Junify_var(varX,arg4) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(68,Jwcons(Jwcons(Jmakefun("abs"),Jwcons(Jwcons(1395,Jwcons(varX1,Jwcons(varX2,NIL))),NIL)),Jwcons(Jmakestrflt("1e-05"),NIL))),Jwcons(168,Jwcons(varX,Jwcons(varX2,NIL))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
varY = Jmakevariant();
varX1 = Jmakevariant();
varX2 = Jmakevariant();
varA = Jmakevariant();
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX1,arg1) == YES && Junify_var(varX2,arg2) == YES && Junify_var(varA,arg3) == YES && Junify_var(varX,arg4) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varY,Jwcons(Jwcons(1354,Jwcons(Jwcons(52,Jwcons(varX1,Jwcons(Jmakeint(2),NIL))),Jwcons(Jwcons(52,Jwcons(varA,Jwcons(Jwcons(1436,Jwcons(Jmakeint(2),Jwcons(varX1,NIL))),NIL))),NIL))),NIL))),Jwcons(Jmakecomp("newton1"),Jwcons(varY,Jwcons(varX1,Jwcons(varA,Jwcons(varX,NIL))))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("newton1"),arglist);
return(NO);}
int b_factor(int arglist, int rest);
int b_factor(int arglist, int rest){
int arg1,arg2,varJ,varJ1,varR,varP,varI,varQ,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varR = Jmakevariant();
varP = Jmakevariant();
varI = Jmakevariant();
varQ = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varP,arg1) == YES && Junify(Jwcons(1436,Jwcons(varI,Jwcons(varQ,NIL))),arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varQ,Jwcons(Jwcons(716,Jwcons(Jwcons(1354,Jwcons(Jwcons(52,Jwcons(varP,Jwcons(varI,NIL))),Jwcons(Jmakestrflt("0.001"),NIL))),NIL)),NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varR,Jwcons(Jwcons(1395,Jwcons(varP,Jwcons(Jwcons(1436,Jwcons(varI,Jwcons(varQ,NIL))),NIL))),NIL))),Jwlist3(Jmakeope(";"),Jwcons(188,Jwcons(varR,Jwcons(Jmakeint(0),NIL))),Jwcons(68,Jwcons(varQ,Jwcons(varI,NIL))))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}if(n == 1){
arg1 = Jnth(arglist,1);
varQ = Jmakevariant();
varP = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(52,Jwcons(varP,Jwcons(Jmakeint(2),NIL))),arg1) == YES && 1)
{body = Jwcons(Jmakecomp("factor"),Jwcons(varP,Jwcons(Jwcons(1436,Jwcons(Jmakeint(2),Jwcons(varQ,NIL))),NIL)));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varJ = Jmakevariant();
varQ = Jmakevariant();
varJ1 = Jmakevariant();
varP = Jmakevariant();
varI = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(52,Jwcons(varP,Jwcons(varI,NIL))),arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("for"),Jwcons(Jwcons(78,Jwcons(varI,Jwcons(varP,NIL))),Jwcons(varJ,NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varJ1,Jwcons(Jwcons(1354,Jwcons(Jwcons(1436,Jwcons(Jmakeint(2),Jwcons(varJ,NIL))),Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("factor"),Jwcons(varP,Jwcons(Jwcons(1436,Jwcons(varJ1,Jwcons(varQ,NIL))),NIL))),Jwcons(40,Jwcons(Jwcons(68,Jwcons(varQ,Jwcons(varJ1,NIL))),Jwcons(Jwcons(178,Jwcons(varI,Jwcons(varP,NIL))),Jwcons(Jwcons(178,Jwcons(varI,Jwcons(varJ1,NIL))),NIL)))))));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("factor"),arglist);
return(NO);}
int b_res_q(int arglist, int rest);
int b_res_q(int arglist, int rest){
int arg1,varA,varB,varQ,varR,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varA = Jmakevariant();
varB = Jmakevariant();
varQ = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(178,Jwcons(varA,Jwcons(Jwcons(1354,Jwcons(Jwcons(1436,Jwcons(varB,Jwcons(varQ,NIL))),Jwcons(varR,NIL))),NIL))),arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(108,Jwcons(varB,Jwcons(Jmakestrflt("0.0"),NIL))),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varQ,Jwcons(Jwcons(716,Jwcons(Jwcons(52,Jwcons(varA,Jwcons(varB,NIL))),NIL)),NIL))),Jwcons(168,Jwcons(varR,Jwcons(Jwcons(1395,Jwcons(varA,Jwcons(Jwcons(1436,Jwcons(varB,Jwcons(varQ,NIL))),NIL))),NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("res_q"),arglist);
return(NO);}
int b_ju(int arglist, int rest);
int b_ju(int arglist, int rest){
int arg1,varQ,varR,varA1,varA,varB,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varQ = Jmakevariant();
varR = Jmakevariant();
varA1 = Jmakevariant();
varA = Jmakevariant();
varB = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(52,Jwcons(varA,Jwcons(varB,NIL))),arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("res_q"),Jwcons(Jwcons(178,Jwcons(varA,Jwcons(Jwcons(1354,Jwcons(Jwcons(1436,Jwcons(varB,Jwcons(varQ,NIL))),Jwcons(varR,NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(1197,Jwcons(varQ,NIL)),Jwlist3(Jmakeope(","),Jwcons(1143,Jwcons(Jmakeint(1),NIL)),Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varA1,Jwcons(Jwcons(1436,Jwcons(varR,Jwcons(Jmakeint(10),NIL))),NIL))),Jwcons(Jmakecomp("ju"),Jwcons(Jwcons(52,Jwcons(varA1,Jwcons(varB,NIL))),NIL))))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ju"),arglist);
return(NO);}
int b_while_do(int arglist, int rest);
int b_while_do(int arglist, int rest){
int arg1,arg2,varP,varQ,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varP = Jmakevariant();
varQ = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varP,arg1) == YES && Junify_var(varQ,arg2) == YES && 1)
{body = Jwcons(20,Jwcons(varP,NIL));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(20,Jwcons(varQ,NIL)),586);
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
varP = Jmakevariant();
varQ = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varP,arg1) == YES && Junify_var(varQ,arg2) == YES && 1)
if(Jexec_all(rest,Jget_sp()) == YES) return(YES);
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("while_do"),arglist);
return(NO);}
int b_read_file(int arglist, int rest);
int b_read_file(int arglist, int rest){
int arg1,varC,varH,varFile_nameX,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varC = Jmakevariant();
varH = Jmakevariant();
varFile_nameX = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varFile_nameX,arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(865,Jwcons(varH,Jwcons(varFile_nameX,Jwcons(Jmakeconst("r"),NIL)))),Jwlist3(Jmakeope(","),1223,Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("while_do"),Jwcons(Jwcons(648,Jwcons(varH,Jwcons(varC,NIL))),Jwcons(Jwcons(883,Jwcons(varC,NIL)),NIL))),Jwcons(424,Jwcons(varH,NIL)))));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("read_file"),arglist);
return(NO);}
int b_copy_file(int arglist, int rest);
int b_copy_file(int arglist, int rest){
int arg1,arg2,varC,varH1,varH2,varFile_nameX,varFile_nameY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varC = Jmakevariant();
varH1 = Jmakevariant();
varH2 = Jmakevariant();
varFile_nameX = Jmakevariant();
varFile_nameY = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varFile_nameX,arg1) == YES && Junify_var(varFile_nameY,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(865,Jwcons(varH1,Jwcons(varFile_nameX,Jwcons(Jmakeconst("r"),NIL)))),Jwlist3(Jmakeope(","),Jwcons(460,Jwcons(varH2,Jwcons(varFile_nameY,NIL))),Jwlist3(Jmakeope(","),1223,Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("while_do"),Jwcons(Jwcons(648,Jwcons(varH1,Jwcons(varC,NIL))),Jwcons(Jwcons(883,Jwcons(varH2,Jwcons(varC,NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(424,Jwcons(varH1,NIL)),Jwcons(424,Jwcons(varH2,NIL)))))));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("copy_file"),arglist);
return(NO);}
int b_cont_frc(int arglist, int rest);
int b_cont_frc(int arglist, int rest){
int arg1,varA,varB,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varA = Jmakevariant();
varB = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(52,Jwcons(varA,Jwcons(varB,NIL))),arg1) == YES && 1)
{body = Jwcons(Jmakecomp("cont_frc_aux"),Jwcons(Jwcons(52,Jwcons(varA,Jwcons(varB,NIL))),NIL));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("cont_frc"),arglist);
return(NO);}
int b_cont_frc_aux(int arglist, int rest);
int b_cont_frc_aux(int arglist, int rest){
int arg1,varQ,varR,varA,varB,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
varQ = Jmakevariant();
varR = Jmakevariant();
varA = Jmakevariant();
varB = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(52,Jwcons(varA,Jwcons(varB,NIL))),arg1) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("res_q"),Jwcons(Jwcons(178,Jwcons(varA,Jwcons(Jwcons(1354,Jwcons(Jwcons(1436,Jwcons(varB,Jwcons(varQ,NIL))),Jwcons(varR,NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(1197,Jwcons(varQ,NIL)),Jwlist3(Jmakeope(","),Jwcons(1143,Jwcons(Jmakeint(1),NIL)),Jwcons(Jmakecomp("cont_frc_aux"),Jwcons(Jwcons(52,Jwcons(varB,Jwcons(varR,NIL))),NIL)))));
if((res=Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);}
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("cont_frc_aux"),arglist);
return(NO);}
int b_memberd(int arglist, int rest);
int b_memberd(int arglist, int rest){
int arg1,arg2,varX,varL,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varX = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify_var(varX,arg1) == YES && Junify_var(varL,arg2) == YES && 1)
{body = Jwcons(1235,Jwcons(varX,Jwcons(varL,NIL)));
if((res=Jexec_all(body,Jget_sp())) == YES)
{body = NIL;
if((Jexec_all(Jaddtail_body(rest,body),Jget_sp())) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
return(NO);}
}
Junbind(save2);
Jset_wp(save1);
return(FALSE);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("memberd"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("sum1",b_sum1);
(deftpred)("sum2",b_sum2);
(deftpred)("sigma",b_sigma);
(deftpred)("sigma_aux",b_sigma_aux);
(deftpred)("not0",b_not0);
(deftpred)("for",b_for);
(deftpred)("f99",b_f99);
(deftpred)("test",b_test);
(deftpred)("positive",b_positive);
(deftpred)("member2",b_member2);
(deftpred)("set",b_set);
(deftinfix)("isl",b_isl,700,XFX);
(deftpred)("memberr",b_memberr);
(deftpred)("generate_e",b_generate_e);
(deftpred)("gene_e_aux",b_gene_e_aux);
(deftpred)("comb",b_comb);
(deftpred)("permutation",b_permutation);
(deftpred)("delete0",b_delete0);
(deftpred)("newton",b_newton);
(deftpred)("newton1",b_newton1);
(deftpred)("factor",b_factor);
(deftpred)("res_q",b_res_q);
(deftpred)("ju",b_ju);
(deftpred)("while_do",b_while_do);
(deftpred)("read_file",b_read_file);
(deftpred)("copy_file",b_copy_file);
(deftpred)("cont_frc",b_cont_frc);
(deftpred)("cont_frc_aux",b_cont_frc_aux);
(deftpred)("memberd",b_memberd);
}
void init_declare(void){int body;
body = no