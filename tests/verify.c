#include "jump.h"
int b_verify(int arglist, int rest);
int b_verify(int arglist, int rest){
int varX,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(varX,NIL),arglist) == YES)
{body = Jwcons(40,Jwcons(Jwcons(20,Jwcons(varX,NIL)),Jwcons(1023,Jwcons(Jwcons(12,Jwcons(Jwcons(1037,Jwcons(Jmakeconst("wrong "),NIL)),Jwcons(Jwcons(12,Jwcons(Jwcons(1037,Jwcons(varX,NIL)),Jwcons(737,NIL))),NIL))),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
int b_alltest(int arglist, int rest);
int b_alltest(int arglist, int rest){
int varTest,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 0){varTest = Jmakevariant();
save1 = Jget_wp();
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("test"),Jwcons(varTest,NIL)),540);
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
return(YES);
}return(NO);}
int b_test(int arglist, int rest);
int b_test(int arglist, int rest){
int varA,var2,var1,varT,varL,varL1,varZ,varC,varB,varE1,varE2,varE3,varA1,varB1,var,varY,varX,n,body,save1,save2,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 1){save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("atmark"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(146,Jwcons(Jmakeint(3),Jwcons(Jmakestrflt("2.1"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(156,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(146,Jwcons(Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),NIL))),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(384,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(384,Jwcons(Jwcons(Jmakepred("a"),NIL),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(384,Jwcons(Jmakeint(1),NIL)),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(384,Jwcons(Jmakestrflt("1.1"),NIL)),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(384,Jwcons(Jmakeconst("a*b"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(384,Jwcons(Jmakeconst("123abc"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(384,Jwcons(Jmakeconst("=$"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(384,Jwcons(1023,NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(384,Jwcons(Jmakeconst("動物"),NIL)),NIL)))))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(396,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(396,Jwcons(Jmakeint(1),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(396,Jwcons(Jmakeconst("abc"),NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(396,Jwcons(Jmakestrflt("1.0"),NIL)),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(771,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(771,Jwcons(Jmakeint(1),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(771,Jwcons(Jmakestrflt("1.0"),NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(771,Jwcons(Jmakestrflt("10.0"),NIL)),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(658,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(658,Jwcons(Jmakeint(0),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(658,Jwcons(Jmakeint(1),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(658,Jwcons(Jmakestrlong("10000000000"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(658,Jwcons(Jmakeint(-1),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(658,Jwcons(Jmakeint(0),NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(658,Jwcons(Jmakebig("100000000000000000000000000000000000000000001"),NIL)),NIL)))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(552,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(552,Jwcons(Jmakestrflt("1.0"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(552,Jwcons(Jmakestrflt("1e-06"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(552,Jwcons(Jmakestrflt("10000000000.0"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(552,Jwcons(Jmakeint(1),NIL)),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(166,Jwcons(varX,Jwcons(Jwcons(552,Jwcons(Jmakeint(100),NIL)),NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(552,Jwcons(varX,NIL)),NIL)))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(753,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varX,Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(753,Jwcons(varX,NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(753,Jwcons(varY,NIL)),NIL)),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
var = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(var,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1029,Jwcons(varX,NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varY,Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(1029,Jwcons(varY,NIL)),NIL)),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("radix"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakeint(255),Jwcons(Jmakeint(255),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakeint(63),Jwcons(Jmakeint(63),NIL))),NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("sharp"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakeint(120),Jwcons(Jmakeint(120),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakeint(48),Jwcons(Jmakeint(48),NIL))),NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("arithmetic"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(2),Jwcons(Jwcons(1231,Jwcons(Jmakeint(1),Jwcons(Jmakeint(1),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(-1),Jwcons(Jwcons(1273,Jwcons(Jmakeint(3),Jwcons(Jmakeint(4),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(6),Jwcons(Jwcons(1315,Jwcons(Jmakeint(2),Jwcons(Jmakeint(3),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(8),Jwcons(Jwcons(52,Jwcons(Jmakeint(16),Jwcons(Jmakeint(2),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("2.3"),Jwcons(Jwcons(1231,Jwcons(Jmakestrflt("1.1"),Jwcons(Jmakestrflt("1.2"),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("1.2"),Jwcons(Jwcons(1231,Jwcons(Jmakestrflt("0.7"),Jwcons(Jmakestrflt("0.5"),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("2.3"),Jwcons(Jwcons(1273,Jwcons(Jmakestrflt("3.4"),Jwcons(Jmakestrflt("1.1"),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("0.36"),Jwcons(Jwcons(1315,Jwcons(Jmakestrflt("0.6"),Jwcons(Jmakestrflt("0.6"),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(8),Jwcons(Jwcons(1327,Jwcons(Jmakeint(2),Jwcons(Jmakeint(3),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(16),Jwcons(Jwcons(1321,Jwcons(Jmakeint(2),Jwcons(Jmakeint(4),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("-1.0"),Jwcons(Jwcons(Jmakefun("cos"),Jwcons(Jwcons(Jmakefun("acos"),Jwcons(Jmakeint(-1),NIL)),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(4),Jwcons(Jwcons(1355,Jwcons(Jmakeint(1),Jwcons(Jmakeint(2),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(8),Jwcons(Jwcons(1355,Jwcons(Jmakeint(1),Jwcons(Jmakeint(3),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(1),Jwcons(Jwcons(1361,Jwcons(Jmakeint(8),Jwcons(Jmakeint(3),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(1),Jwcons(Jwcons(1361,Jwcons(Jmakeint(4),Jwcons(Jmakeint(2),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(3),Jwcons(Jwcons(Jmakefun("abs"),Jwcons(Jmakeint(-3),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("3.3"),Jwcons(Jwcons(Jmakefun("abs"),Jwcons(Jmakestrflt("-3.3"),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(1),Jwcons(Jwcons(Jmakefun("min"),Jwcons(Jmakeint(3),Jwcons(Jmakeint(1),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(3),Jwcons(Jwcons(Jmakefun("max"),Jwcons(Jmakeint(3),Jwcons(Jmakeint(1),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("2.718281828459045"),Jwcons(Jwcons(Jmakefun("exp"),Jwcons(Jmakeint(1),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(0),Jwcons(Jwcons(Jmakefun("log"),Jwcons(Jmakeint(1),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(2),Jwcons(Jwcons(Jmakefun("ceiling"),Jwcons(Jmakestrflt("1.1"),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(1),Jwcons(Jwcons(Jmakefun("floor"),Jwcons(Jmakestrflt("1.1"),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(1),Jwcons(Jwcons(Jmakefun("truncate"),Jwcons(Jmakestrflt("1.1"),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakestrflt("1.0"),Jwcons(Jwcons(552,Jwcons(Jmakeint(1),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(1),Jwcons(Jwcons(Jmakefun("sign"),Jwcons(Jmakeint(10),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(0),Jwcons(Jwcons(Jmakefun("sign"),Jwcons(Jmakeint(0),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(166,Jwcons(Jmakeint(-1),Jwcons(Jwcons(Jmakefun("sign"),Jwcons(Jmakeint(-9),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakeint(2),Jwcons(Jmakeint(2),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakestrflt("1.23"),Jwcons(Jmakestrflt("1.23"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(Jmakestrflt("1e-14"),Jwcons(Jmakestrflt("1e-14"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(96,Jwcons(Jmakeint(2),Jwcons(Jmakeint(2),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(206,Jwcons(Jmakeint(2),Jwcons(Jmakeint(3),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(106,Jwcons(Jmakeint(2),Jwcons(Jmakeint(3),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(206,Jwcons(Jmakeint(2),Jwcons(Jmakestrflt("0.3"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(54,Jwcons(Jmakeint(2),Jwcons(Jmakeint(1),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(54,Jwcons(Jmakeint(1),Jwcons(Jmakeint(1),NIL))),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(54,Jwcons(Jmakestrflt("3.2"),Jwcons(Jmakeint(3),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(86,Jwcons(Jmakeint(2),Jwcons(Jmakeint(1),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(86,Jwcons(Jmakeint(1),Jwcons(Jmakeint(1),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(66,Jwcons(Jmakeint(1),Jwcons(Jmakeint(2),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(66,Jwcons(Jmakeint(1),Jwcons(Jmakeint(1),NIL))),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(66,Jwcons(Jmakeint(1),Jwcons(Jmakestrflt("2.0"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(66,Jwcons(Jmakestrflt("1.0"),Jwcons(Jmakebig("999999999999999999999999"),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(76,Jwcons(Jmakeint(1),Jwcons(Jmakeint(1),NIL))),NIL))))))))))))))))))))))))))))))))))))))))))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(921,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(921,Jwcons(Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(1),NIL))),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(670,Jwcons(Jwlistcons(Jwcons(1273,Jwcons(Jmakeint(25),Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeconst("e"),Jwcons(Jmakeint(100),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeconst("n"),Jwcons(Jmakeint(5),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeint(12),Jwcons(Jmakeconst("o"),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeint(50),Jwcons(Jmakeconst("t"),NIL))),NIL))))),Jwcons(varY,NIL))),Jwcons(Jmakecomp("verify"),Jwcons(varY,Jwcons(Jwlistcons(Jwcons(1273,Jwcons(Jmakeint(12),Jwcons(Jmakeconst("o"),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeint(25),Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeint(50),Jwcons(Jmakeconst("t"),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeconst("e"),Jwcons(Jmakeint(100),NIL))),Jwlistcons(Jwcons(1273,Jwcons(Jmakeconst("n"),Jwcons(Jmakeint(5),NIL))),NIL))))),NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(945,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(945,Jwcons(Jmakestr("asdf"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(945,Jwcons(Jmakestr("123"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(945,Jwcons(Jmakestr("hello world!"),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(Jmakestr("asdf"),Jwcons(Jmakestr("asdf"),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(206,Jwcons(Jmakestr("asdf"),Jwcons(Jmakestr("qwer"),NIL))),NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("true_fail_not"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(1023,NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(540,NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(14,Jwcons(540,Jwcons(1023,NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(747,Jwcons(1023,NIL)),NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(186,Jwcons(Jmakeint(1),Jwcons(Jmakeint(2),NIL))),NIL)),NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(1069,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1069,Jwcons(Jwcons(52,Jwcons(1037,Jwcons(Jmakeint(1),NIL))),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1069,Jwcons(Jwcons(52,Jwcons(1023,Jwcons(Jmakeint(0),NIL))),NIL)),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1069,Jwcons(Jwcons(52,Jwcons(624,Jwcons(Jmakeint(0),NIL))),NIL)),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varZ = Jmakevariant();
varC = Jmakevariant();
varB = Jmakevariant();
varE1 = Jmakevariant();
varE2 = Jmakevariant();
varE3 = Jmakevariant();
varA1 = Jmakevariant();
varB1 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("unify"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(Jwcons(Jmakepred("c"),Jwcons(varZ,NIL)),Jwcons(Jwcons(Jmakepred("c"),Jwcons(Jwcons(Jmakepred("c"),Jwcons(Jmakeconst("z"),NIL)),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varZ,Jwcons(Jwcons(Jmakepred("c"),Jwcons(Jmakeconst("z"),NIL)),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(Jwcons(Jmakepred("a"),Jwcons(Jwcons(Jmakepred("b"),NIL),Jwcons(varC,NIL))),Jwcons(Jwcons(Jmakepred("a"),Jwcons(varB,Jwcons(Jwcons(Jmakepred("c"),NIL),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varC,Jwcons(Jwcons(Jmakepred("c"),NIL),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varB,Jwcons(Jwcons(Jmakepred("b"),NIL),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(Jwlistcons(varE1,Jwlistcons(varE2,Jwlistcons(varE3,NIL))),Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("c"),NIL),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varE1,Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varE2,Jwcons(Jwcons(Jmakepred("b"),NIL),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varE3,Jwcons(Jwcons(Jmakepred("c"),NIL),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(176,Jwcons(Jwcons(Jmakepred("a"),Jwcons(Jwcons(Jmakepred("a"),NIL),Jwcons(Jwcons(Jmakepred("b"),NIL),NIL))),Jwcons(Jwcons(Jmakepred("b"),Jwcons(Jwcons(Jmakepred("a"),NIL),Jwcons(Jwcons(Jmakepred("b"),NIL),NIL))),NIL))),NIL)),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(Jwcons(Jmakepred("a"),Jwcons(Jwcons(Jmakepred("a"),NIL),Jwcons(varA1,NIL))),Jwcons(Jwcons(Jmakepred("a"),Jwcons(varA1,Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varA1,Jwcons(Jwcons(Jmakepred("a"),NIL),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(176,Jwcons(Jwcons(Jmakepred("a"),Jwcons(Jwcons(Jmakepred("a"),NIL),Jwcons(varB1,NIL))),Jwcons(Jwcons(Jmakepred("a"),Jwcons(varB1,Jwcons(Jwcons(Jmakepred("b"),NIL),NIL))),NIL))),NIL)),NIL))))))))))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varT = Jmakevariant();
varL = Jmakevariant();
varL1 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("list_difference"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varL,Jwcons(Jwcons(1273,Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),varT),Jwcons(varT,NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varT,Jwcons(NIL,NIL))),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varL,Jwcons(Jwcons(1273,Jwcons(varL1,Jwcons(NIL,NIL))),NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varL1,Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),NIL),NIL))),NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varL = Jmakevariant();
varT = Jmakevariant();
varL1 = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("list_difference"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varL,Jwcons(Jwcons(1273,Jwcons(varT,Jwcons(varT,NIL))),NIL))),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varL1,Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),varT)),NIL))),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varT,Jwcons(Jwlistcons(Jwcons(Jmakepred("c"),NIL),Jwlistcons(Jmakeconst("d"),NIL)),NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varL1,Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("c"),NIL),Jwlistcons(Jmakeconst("d"),NIL)))),NIL))),NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(Jmakeconst("univ"),NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(216,Jwcons(varX,Jwcons(Jwlistcons(Jwcons(Jmakepred("sin"),NIL),Jwlistcons(Jmakeint(3),NIL)),NIL))),Jwlist3(Jmakeope(","),Jwcons(216,Jwcons(Jwcons(Jmakefun("cos"),Jwcons(Jmakeint(2),NIL)),Jwcons(varY,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varX,Jwcons(Jwcons(Jmakepred("sin"),Jwcons(Jmakeint(3),NIL)),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varY,Jwcons(Jwlistcons(Jmakefun("cos"),Jwlistcons(Jmakeint(2),NIL)),NIL))),NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(564,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(564,Jwcons(Jwcons(Jmakepred("book"),Jwcons(Jmakeconst("pooh"),Jwcons(Jmakeconst("miline"),Jwcons(Jmakeconst("aa"),NIL)))),Jwcons(Jwcons(Jmakepred("book"),NIL),Jwcons(Jmakeint(3),NIL)))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(564,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),Jwcons(Jmakeconst("."),Jwcons(Jmakeint(2),NIL)))),NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(348,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(348,Jwcons(Jmakeint(1),Jwcons(Jwcons(Jmakepred("book"),Jwcons(Jmakeconst("poetry"),Jwcons(Jmakeconst("milne"),Jwcons(Jmakeconst("poetry"),NIL)))),NIL))),Jwcons(354,Jwcons(Jmakeint(0),Jwcons(Jwcons(Jmakepred("book"),Jwcons(Jmakeconst("poetry"),Jwcons(Jmakeconst("milne"),Jwcons(Jmakeconst("poetry"),NIL)))),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(438,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(438,Jwcons(Jmakeconst("a123"),Jwcons(Jmakeconst("asdf"),Jwcons(varX,NIL)))),Jwlist3(Jmakeope(","),Jwcons(176,Jwcons(varX,Jwcons(Jmakeconst("a123asdf"),NIL))),Jwlist3(Jmakeope(","),Jwcons(438,Jwcons(Jmakestr("asdf"),Jwcons(Jmakestr("123"),Jwcons(varY,NIL)))),Jwcons(176,Jwcons(varY,Jwcons(Jmakestr("asdf123"),NIL))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(1099,NIL),arglist) == YES)
{body = Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1099,Jwcons(Jwcons(52,Jwcons(Jwcons(Jmakecomp("verify"),NIL),Jwcons(Jmakeint(1),NIL))),NIL)),NIL));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(492,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(492,Jwcons(Jmakeint(10),Jwcons(varX,NIL))),Jwcons(186,Jwcons(varX,Jwcons(Jmakeint(9),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(646,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(646,Jwcons(Jmakeint(9),Jwcons(varX,NIL))),Jwcons(186,Jwcons(varX,Jwcons(Jmakeint(10),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
var2 = Jmakevariant();
varX = Jmakevariant();
var1 = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(558,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(558,Jwcons(Jmakestrflt("1.23"),Jwcons(varX,Jwcons(var2,NIL)))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jmakestr("1.23"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(558,Jwcons(varY,Jwcons(Jmakestr("1.23"),Jwcons(var1,NIL)))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(186,Jwcons(varY,Jwcons(Jmakestrflt("1.23"),NIL))),NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(682,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(682,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),Jwcons(Jmakeint(3),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(682,Jwcons(NIL,Jwcons(Jmakeint(0),NIL))),NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(1081,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1081,Jwcons(Jwcons(Jmakepred("b"),NIL),Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("c"),NIL),NIL))),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1081,Jwcons(Jmakeint(1),Jwcons(Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(1),NIL))),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(747,Jwcons(Jwcons(1081,Jwcons(Jwcons(Jmakepred("a"),NIL),Jwcons(Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(1),NIL))),NIL))),NIL)),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
save1 = Jget_wp();
if(Junify(Jwcons(1075,NIL),arglist) == YES)
{body = Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(1075,Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("c"),NIL),NIL))),Jwcons(Jwlistcons(Jmakeconst("d"),Jwlistcons(Jmakeconst("e"),Jwlistcons(Jmakeconst("f"),NIL))),Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("c"),NIL),Jwlistcons(Jmakeconst("d"),Jwlistcons(Jmakeconst("e"),Jwlistcons(Jmakeconst("f"),NIL)))))),NIL)))),NIL));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(879,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(879,Jwcons(Jwlistcons(Jwcons(Jmakepred("a"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("c"),NIL),NIL))),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jwlistcons(Jwcons(Jmakepred("c"),NIL),Jwlistcons(Jwcons(Jmakepred("b"),NIL),Jwlistcons(Jwcons(Jmakepred("a"),NIL),NIL))),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(879,Jwcons(Jwlistcons(Jmakeint(1),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(3),NIL))),Jwcons(Jwlistcons(Jmakeint(3),Jwlistcons(Jmakeint(2),Jwlistcons(Jmakeint(1),NIL))),NIL))),NIL))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
varA = Jmakevariant();
varB = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(729,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(729,Jwcons(Jmakeconst("asdf"),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(729,Jwcons(varY,Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varY,Jwcons(Jmakeconst("asdf"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(729,Jwcons(Jmakeconst("笹川賢一"),Jwcons(varA,NIL))),Jwlist3(Jmakeope(","),Jwcons(729,Jwcons(varB,Jwcons(varA,NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varB,Jwcons(Jmakeconst("笹川賢一"),NIL))),NIL)))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(711,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(711,Jwcons(Jwlistcons(Jmakeint(97),Jwlistcons(Jmakeint(115),Jwlistcons(Jmakeint(100),NIL))),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jmakeconst("asd"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(711,Jwcons(Jwlistcons(Jmakeint(97),Jwlistcons(Jmakeint(115),Jwlistcons(Jmakeint(115),Jwlistcons(Jmakeint(101),Jwlistcons(Jmakeint(114),Jwlistcons(Jmakeint(116),NIL)))))),Jwcons(varY,NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varY,Jwcons(360,NIL))),NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(664,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(664,Jwcons(Jmakeint(6),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jmakestr("6"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(664,Jwcons(varY,Jwcons(Jmakestr("7"),NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varY,Jwcons(Jmakeint(7),NIL))),NIL)),Jwcons(Jmakecomp("verify"),Jwcons(Jmakeint(5),Jwcons(Jmakestr("5"),NIL)))))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(957,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(957,Jwcons(Jmakestr("sin(3)"),Jwcons(varX,NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jwcons(Jmakepred("sin"),Jwcons(Jmakeint(3),NIL)),NIL))),NIL)));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
varX = Jmakevariant();
varY = Jmakevariant();
save1 = Jget_wp();
if(Junify(Jwcons(390,NIL),arglist) == YES)
{body = Jwlist3(Jmakeope(","),Jwcons(390,Jwcons(Jmakeconst("orange"),Jwcons(varX,NIL))),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varX,Jwcons(Jmakestr("orange"),NIL))),NIL)),Jwlist3(Jmakeope(","),Jwcons(390,Jwcons(varY,Jwcons(Jmakestr("apple"),NIL))),Jwcons(Jmakecomp("verify"),Jwcons(Jwcons(176,Jwcons(varY,Jwcons(Jmakeconst("apple"),NIL))),NIL)))));
if((res=Jprove_all(Jaddtail_body(rest,body),Jget_sp(),0)) == YES)
return(YES);}
Junbind(save2);
Jset_wp(save1);
if(res == NPLFALSE) return(NO);
}return(NO);}
void init_tpredicate(void){(deftpred)("verify",b_verify);
(deftpred)("alltest",b_alltest);
(deftpred)("test",b_test);
}
void init_declare(void){int body;
body = Jwlist3(Jmakeope(","),Jmakecomp("alltest"),Jwlist3(Jmakeope(","),Jwcons(1037,Jwcons(Jmakeconst("All tests are done"),NIL)),737));
Jprove_all(body,Jget_sp(),0);
}