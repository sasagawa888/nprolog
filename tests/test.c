#include "jump.h"
int b_fact(int arglist, int rest);
int b_fact(int arglist, int rest){
int varX1,varY1,varX,varY,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){save1 = Jget_wp();
if(Junify(Jwcons(Jmakeint(0),Jwcons(Jmakeint(1),NIL)),arglist) == YES)
if(Jprove_all(rest,Jget_sp(),0) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
varX1 = Jmakevariant();
varY1 = Jmakevariant();
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varX,Jwcons(varY,NIL)),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(116,Jwcons(varX1,Jwcons(Jwcons(542,Jwcons(varX,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakesys("fact"),Jwcons(varX1,Jwcons(varY1,NIL))),Jwcons(116,Jwcons(varY,Jwcons(Jwcons(584,Jwcons(varX,Jwcons(varY1,NIL))),NIL)))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_hanoi(int arglist, int rest);
int b_hanoi(int arglist, int rest){
int varN1,varN,varVia,varFrom,varTo,var1,n,body,save1,save2;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 4){varFrom = Jmakevariant();
varTo = Jmakevariant();
var1 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeint(1),Jwcons(varFrom,Jwcons(varTo,Jwcons(var1,NIL)))),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(382,Jwcons(Jwlistcons(varFrom,Jwlistcons(Jmakeconst("to"),Jwlistcons(varTo,NIL))),NIL)),302);
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
varN1 = Jmakevariant();
varN = Jmakevariant();
varFrom = Jmakevariant();
varTo = Jmakevariant();
varVia = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varN,Jwcons(varFrom,Jwcons(varTo,Jwcons(varVia,NIL)))),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(116,Jwcons(varN1,Jwcons(Jwcons(542,Jwcons(varN,Jwcons(Jmakeint(1),NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakesys("hanoi"),Jwcons(varN1,Jwcons(varFrom,Jwcons(varVia,Jwcons(varTo,NIL))))),Jwlist3(Jmakeope(","),Jwcons(382,Jwcons(Jwlistcons(varFrom,Jwlistcons(Jmakeconst("to"),Jwlistcons(varTo,NIL))),NIL)),Jwlist3(Jmakeope(","),302,Jwcons(Jmakesys("hanoi"),Jwcons(varN1,Jwcons(varVia,Jwcons(varTo,Jwcons(varFrom,NIL)))))))));
if(Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
}return(NO);}
int b_bar(int arglist, int rest);
int b_bar(int arglist, int rest){
int n,head,varN1,varN;
n = Jlength(arglist);
if(n == 1){
head = Jwcons(Jmakeint(0),NIL);
loop:
if(Jnumeqp(Jmakeint(0),Jcar(arglist)) && 
1) return(Junify(arglist,head));
varN = Jcar(arglist);
{varN1 = Jminus(Jderef(varN),Jmakeint(1));
arglist = Jwcons(varN1,NIL);
goto loop;
}}return(NO);
}
int b_myappend(int arglist, int rest);
int b_myappend(int arglist, int rest){
int n,head,varB,varA,varC,varL;
n = Jlength(arglist);
if(n == 3){
varL = Jmakevariant();
head = Jwcons(NIL,Jwcons(varL,Jwcons(varL,NIL)));
loop:
if(Jcar(arglist) == NIL && 1) return(Junify(arglist,head));
varA = Jcar(Jcar(arglist));
varL = Jcdr(Jcar(arglist));
varB = Jcar(Jcdr(arglist));
varA = Jcar(Jcar(Jcdr(Jcdr(arglist))));
varC = Jcdr(Jcar(Jcdr(Jcdr(arglist))));
{arglist = Jwcons(varL,Jwcons(varB,Jwcons(varC,NIL)));
goto loop;
}}return(NO);
}
int b_nodiag(int arglist, int rest);
int b_nodiag(int arglist, int rest){
int n,head,varD1,varN,varL,varB,varD,var2,var1;
n = Jlength(arglist);
if(n == 3){
var2 = Jmakevariant();
var1 = Jmakevariant();
head = Jwcons(NIL,Jwcons(var2,Jwcons(var1,NIL)));
loop:
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
void init_tpredicate(void){
(deftpred)("fact",b_fact);
(deftpred)("hanoi",b_hanoi);
(deftsys)("bar",b_bar);
(deftsys)("myappend",b_myappend);
(deftsys)("nodiag",b_nodiag);
}void init_declare(void){}