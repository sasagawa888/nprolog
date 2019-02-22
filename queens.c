#include "jump.h"
int b_test16(int nest, int n);
int b_test16(int nest, int n){
int varX,body,save1,save2;
save2 = Jget_sp();
if(n == 0){varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("between"),Jwcons(Jmakeint(1),Jwcons(Jmakeint(16),Jwcons(varX,NIL)))),Jwlist3(Jmakeope(","),Jmakecomp("test"),285));
if(Jproceed(body,nest) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_test(int nest, int n);
int b_test(int nest, int n){
int varX,body,save1,save2;
save2 = Jget_sp();
if(n == 0){varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("queen"),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL))))))))),Jwcons(varX,NIL))),285);
if(Jproceed(body,nest) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_queen(int nest, int n);
int b_queen(int nest, int n){
int arg1,arg2,varData,varOut,body,save1,save2;
save2 = Jget_sp();
if(n == 2){arg1 = Jderef(Jget_goal(2));
arg2 = Jderef(Jget_goal(3));
varData = Jmakevariant();
varOut = Jmakevariant();
save1 = Jget_wp();
if(Junify(arg1,varData) == YES && 
Junify(arg2,varOut) == YES)
{body = Jwcons(Jmakecomp("queen_2"),Jwcons(varData,Jwcons(NIL,Jwcons(varOut,NIL))));
if(Jproceed(body,nest) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_queen_2(int nest, int n);
int b_queen_2(int nest, int n){
int arg1,arg2,arg3,varL1,varH,varT,varHistory,varQ,varM,var1,body,save1,save2;
save2 = Jget_sp();
if(n == 3){arg1 = Jderef(Jget_goal(2));
arg2 = Jderef(Jget_goal(3));
arg3 = Jderef(Jget_goal(4));
var1 = Jmakevariant();
save1 = Jget_wp();
if(Junify(arg1,NIL) == YES && 
Junify(arg2,var1) == YES && 
Junify(arg3,NIL) == YES)
if(Jproceed(NIL,nest) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
varL1 = Jmakevariant();
varH = Jmakevariant();
varT = Jmakevariant();
varHistory = Jmakevariant();
varQ = Jmakevariant();
varM = Jmakevariant();
save1 = Jget_wp();
if(Junify(arg1,Jwlistcons(varH,varT)) == YES && 
Junify(arg2,varHistory) == YES && 
Junify(arg3,Jwlistcons(varQ,varM)) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qdelete"),Jwcons(varQ,Jwcons(varH,Jwcons(varT,Jwcons(varL1,NIL))))),Jwlist3(Jmakeope(","),Jwcons(Jmakesys("nodiag"),Jwcons(varHistory,Jwcons(varQ,Jwcons(Jmakeint(1),NIL)))),Jwcons(Jmakecomp("queen_2"),Jwcons(varL1,Jwcons(Jwlistcons(varQ,varHistory),Jwcons(varM,NIL))))));
if(Jproceed(body,nest) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_qdelete(int nest, int n);
int b_qdelete(int nest, int n){
int arg1,arg2,arg3,arg4,varX,varH,varT,varR,varA,varL,body,save1,save2;
save2 = Jget_sp();
if(n == 4){arg1 = Jderef(Jget_goal(2));
arg2 = Jderef(Jget_goal(3));
arg3 = Jderef(Jget_goal(4));
arg4 = Jderef(Jget_goal(5));
varA = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify(arg1,varA) == YES && 
Junify(arg2,varA) == YES && 
Junify(arg3,varL) == YES && 
Junify(arg4,varL) == YES)
if(Jproceed(NIL,nest) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
varX = Jmakevariant();
varH = Jmakevariant();
varT = Jmakevariant();
varA = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify(arg1,varX) == YES && 
Junify(arg2,varA) == YES && 
Junify(arg3,Jwlistcons(varH,varT)) == YES && 
Junify(arg4,Jwlistcons(varA,varR)) == YES)
{body = Jwcons(Jmakecomp("qdelete"),Jwcons(varX,Jwcons(varH,Jwcons(varT,Jwcons(varR,NIL)))));
if(Jproceed(body,nest) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_nodiag(int nest, int n);
int b_nodiag(int nest, int n){
int arg1,save1,arg2,save2,arg3,save3,varD1,varN,varL,varB,varD,var2,var1;
if(n == 3){arg1 = save1 = Jderef(Jget_goal(2));
arg2 = save2 = Jderef(Jget_goal(3));
arg3 = save3 = Jderef(Jget_goal(4));
loop:
if(arg1 == NIL &&
1){var2 = Jmakevariant();
var1 = Jmakevariant();
if(Junify(arg1,NIL)==NO) goto exit1;
Junify(save1,arg1);
if(Junify(arg2,var2)==NO) goto exit1;
Junify(save2,arg2);
if(Junify(arg3,var1)==NO) goto exit1;
Junify(save3,arg3);
return(YES);}
exit1:
varN = Jcar(arg1);
varL = Jcdr(arg1);
varB = arg2;
varD = arg3;
if(Jnot_numeqp(Jderef(varD),Jminus(Jderef(varN),Jderef(varB)))){if(Jnot_numeqp(Jderef(varD),Jminus(Jderef(varB),Jderef(varN)))){varD1 = Jplus(Jderef(varD),Jmakeint(1));{arg1 = varL;
arg2 = varB;
arg3 = varD1;
goto loop;
}}}return(NO);
}return(NO);}
void init_tpredicate(void){(deftpred)("test16",b_test16);
(deftpred)("test",b_test);
(deftpred)("queen",b_queen);
(deftpred)("queen_2",b_queen_2);
(deftpred)("qdelete",b_qdelete);
(deftpred)("nodiag",b_nodiag);
Jset_aux(Jmakecomp("nodiag"),SYS);
}void init_declare(void){}