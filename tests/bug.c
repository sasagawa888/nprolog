#include "jump.h"
int b_my_length(int arglist, int rest);
int b_my_length(int arglist, int rest){
int arg1,arg2,varN1,varL,varLs,varN,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify(Jmakeint(0),arg2) == YES && 1)
if(Jprove_all(rest,Jget_sp(),0) == YES)
return(YES);
Junbind(save2);
Jset_wp(save1);
varN1 = Jmakevariant();
varL = Jmakevariant();
varLs = Jmakevariant();
varN = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwlistcons(varL,varLs),arg1) == YES && Junify(varN,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("my_length"),Jwcons(varLs,Jwcons(varN1,NIL))),Jwcons(166,Jwcons(varN,Jwcons(Jwcons(1233,Jwcons(varN1,Jwcons(Jmakeint(1),NIL))),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
int b_rotate(int arglist, int rest);
int b_rotate(int arglist, int rest){
int arg1,arg2,varRight,varLeft,varL1,varL2,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varRight = Jmakevariant();
varLeft = Jmakevariant();
varL1 = Jmakevariant();
varL2 = Jmakevariant();
save1 = Jget_wp();
if(Junify(varL1,arg1) == YES && Junify(varL2,arg2) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("append"),Jwcons(varLeft,Jwcons(varRight,Jwcons(varL1,NIL)))),Jwcons(Jmakecomp("append"),Jwcons(varRight,Jwcons(varLeft,Jwcons(varL2,NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
int b_rotate1(int arglist, int rest);
int b_rotate1(int arglist, int rest){
int arg1,arg2,arg3,varRight,varLeft,varL1,varN,varL2,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varRight = Jmakevariant();
varLeft = Jmakevariant();
varL1 = Jmakevariant();
varN = Jmakevariant();
varL2 = Jmakevariant();
save1 = Jget_wp();
if(Junify(varL1,arg1) == YES && Junify(varN,arg2) == YES && Junify(varL2,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(682,Jwcons(varRight,Jwcons(varN,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("append"),Jwcons(varLeft,Jwcons(varRight,Jwcons(varL1,NIL)))),Jwcons(Jmakecomp("append"),Jwcons(varRight,Jwcons(varLeft,Jwcons(varL2,NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
int b_reverse_x(int arglist, int rest);
int b_reverse_x(int arglist, int rest){
int arg1,arg2,arg3,varAx,varAy,varD,varC,varA,varB,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varA = Jmakevariant();
varB = Jmakevariant();
save1 = Jget_wp();
if(Junify(varA,arg1) == YES && Junify(varB,arg2) == YES && 1)
{body = Jwcons(Jmakecomp("reverse_x"),Jwcons(varA,Jwcons(varB,Jwcons(NIL,NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varB = Jmakevariant();
varC = Jmakevariant();
save1 = Jget_wp();
if(Junify_nil(NIL,arg1) == YES && Junify(varB,arg2) == YES && Junify(varC,arg3) == YES && 1)
{body = Jwcons(176,Jwcons(varB,Jwcons(varC,NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varAx = Jmakevariant();
varAy = Jmakevariant();
varD = Jmakevariant();
varA = Jmakevariant();
varB = Jmakevariant();
varC = Jmakevariant();
save1 = Jget_wp();
if(Junify(varA,arg1) == YES && Junify(varB,arg2) == YES && Junify(varC,arg3) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varA,Jwcons(Jwlistcons(varAx,varAy),NIL))),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varD,Jwcons(Jwlistcons(varAx,varC),NIL))),Jwcons(Jmakecomp("reverse_x"),Jwcons(varAy,Jwcons(varB,Jwcons(varD,NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
int b_foo(int arglist, int rest);
int b_foo(int arglist, int rest){
int arg1,var1,var2,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
var1 = Jmakevariant();
var2 = Jmakevariant();
save1 = Jget_wp();
if(Junify(var2,arg1) == YES && 1)
{body = Jwcons(1037,Jwcons(var1,NIL));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
void init_tpredicate(void){(deftpred)("my_length",b_my_length);
(deftpred)("rotate",b_rotate);
(deftpred)("rotate1",b_rotate1);
(deftpred)("reverse_x",b_reverse_x);
(deftpred)("foo",b_foo);
}
void init_declare(void){int body;
}