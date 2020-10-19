#include "jump.h"
int b_test16(int arglist, int rest);
int b_test16(int arglist, int rest){
int varX,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 0){varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("between"),Jwcons(Jmakeint(1),Jwcons(Jmakeint(16),Jwcons(varX,NIL)))),Jwlist3(Jmakeope(","),Jmakecomp("test1"),Jwlist3(Jmakeope(","),Jwcons(394,Jwcons(varX,NIL)),260)));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_test(int arglist, int rest);
int b_test(int arglist, int rest){
int varX,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 0){varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("queen"),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL))))))))),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(394,Jwcons(varX,NIL)),Jwlist3(Jmakeope(","),310,260)));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_test1(int arglist, int rest);
int b_test1(int arglist, int rest){
int varX,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 0){varX = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("queen"),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(4),Jwlistcons(Jmakeint(5),Jwlistcons(Jmakeint(6),Jwlistcons(Jmakeint(7),Jwlistcons(Jmakeint(8),Jwlistcons(Jmakeint(9),NIL))))))))),Jwcons(varX,NIL))),260);
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_queen(int arglist, int rest);
int b_queen(int arglist, int rest){
int varData,varOut,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){varData = Jmakevariant();
varOut = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varData,Jwcons(varOut,NIL)),arglist) == YES)
{body = Jwcons(Jmakecomp("queen_2"),Jwcons(varData,Jwcons(NIL,Jwcons(varOut,NIL))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_queen_2(int arglist, int rest);
int b_queen_2(int arglist, int rest){
int varL1,varH,varT,varHistory,varQ,varM,var1,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){var1 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(NIL,Jwcons(var1,Jwcons(NIL,NIL))),arglist) == YES)
if(Jprove_all(rest,Jget_sp(),0) == YES)
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
if(Junify(Jwcons(Jwlistcons(varH,varT),Jwcons(varHistory,Jwcons(Jwlistcons(varQ,varM),NIL))),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("qdelete"),Jwcons(varQ,Jwcons(varH,Jwcons(varT,Jwcons(varL1,NIL))))),Jwlist3(Jmakeope(","),Jwcons(Jmakesys("nodiag"),Jwcons(varHistory,Jwcons(varQ,Jwcons(Jmakeint(1),NIL)))),Jwcons(Jmakecomp("queen_2"),Jwcons(varL1,Jwcons(Jwlistcons(varQ,varHistory),Jwcons(varM,NIL))))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_qdelete(int arglist, int rest);
int b_qdelete(int arglist, int rest){
int varX,varH,varT,varR,varA,varL,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 4){varA = Jmakevariant();
varL = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varA,Jwcons(varA,Jwcons(varL,Jwcons(varL,NIL)))),arglist) == YES)
if(Jprove_all(rest,Jget_sp(),0) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
varX = Jmakevariant();
varH = Jmakevariant();
varT = Jmakevariant();
varA = Jmakevariant();
varR = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varX,Jwcons(varA,Jwcons(Jwlistcons(varH,varT),Jwcons(Jwlistcons(varA,varR),NIL)))),arglist) == YES)
{body = Jwcons(Jmakecomp("qdelete"),Jwcons(varX,Jwcons(varH,Jwcons(varT,Jwcons(varR,NIL)))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_nodiag(int arglist, int rest);
int b_nodiag(int arglist, int rest){
int n,head,varD1,varN,varL,varB,varD,var2,var1;
n = Jlength(arglist);
if(n == 3){
loop:
Jinc_proof();
var2 = Jmakevariant();
var1 = Jmakevariant();
head = Jwcons(NIL,Jwcons(var2,Jwcons(var1,NIL)));
if(Jcar(arglist) == NIL && 1) return(Junify(arglist,head));
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
(deftsys)("nodiag",b_nodiag);
}void init_declare(void){}