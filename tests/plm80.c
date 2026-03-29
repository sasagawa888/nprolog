#include "jump.h"
static int b_plm80(int arglist, int rest, int th);
static int b_plm80(int arglist, int rest, int th){
int arg1,varC,varT,varAst,varOut,varAsm,varS,varFile,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varC = Jmakevariant(th);
var_3533 = Jmakevariant(th);
varAst = Jmakevariant(th);
varOut = Jmakevariant(th);
varAsm = Jmakevariant(th);
varS = Jmakevariant(th);
varFile = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varFile,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(868,Jwcons(varS,Jwcons(varFile,Jwcons(Jmakeconst("r"),NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("read_codes"),Jwcons(varS,Jwcons(varC,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("tokenize"),Jwcons(varC,Jwcons(var_3533,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("compile"),Jwcons(var_3533,Jwcons(varAst,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(441,Jwcons(varS,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("encode"),Jwcons(varAst,Jwcons(varAsm,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("change_ext"),Jwcons(varFile,Jwcons(Jmakeconst("asm"),Jwcons(varOut,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(868,Jwcons(varS,Jwcons(varOut,Jwcons(Jmakeconst("w"),NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("format"),Jwcons(varS,Jwcons(Jmakestr("INCLUDE ~A"),Jwcons(Jwlistcons(Jmakeconst("plmbase.asm"),NIL,th),NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(810,Jwcons(varS,NIL,th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("output_asm"),Jwcons(varS,Jwcons(varAsm,NIL,th),th),th),Jwcons(441,Jwcons(varS,NIL,th),th),th),th),th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("plm80"),arglist);
return(NO);}
static int b_test(int arglist, int rest, int th);
static int b_test(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v4795,var_v4816,var_v4804,var_v4770,var_v4825,var_v4761,var_v4817,varC,varT,varS,varA,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 1){
arg1 = Jnth(arglist,1);
loop1:
varC = Jmakevariant(th);
var_3533 = Jmakevariant(th);
varS = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varA,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(868,Jwcons(varS,Jwcons(Jmakeconst("./tests/plm1.pl"),Jwcons(Jmakeconst("r"),NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("read_codes"),Jwcons(varS,Jwcons(varC,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakepred("tokenize"),Jwcons(varC,Jwcons(var_3533,NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(1206,Jwcons(var_3533,NIL,th),th),Jwlist3(Jmakeope(","),810,Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("compile"),Jwcons(var_3533,Jwcons(varA,NIL,th),th),th),Jwcons(441,Jwcons(varS,NIL,th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v4795 = Jmakevariant(th);
var_v4816 = Jmakevariant(th);
var_v4804 = Jmakevariant(th);
var_v4770 = Jmakevariant(th);
var_v4825 = Jmakevariant(th);
var_v4761 = Jmakevariant(th);
var_v4817 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("comp"),Jwcons(var_v4804,Jwcons(var_v4770,Jwcons(var_v4825,NIL,th),th),th),th),th) == YES && Junify_var(arg2,var_v4761,th) == YES && Junify_var(arg3,var_v4817,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("expression"),Jwcons(var_v4770,Jwcons(var_v4761,Jwcons(var_v4795,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("comparison_op"),Jwcons(var_v4804,Jwcons(var_v4795,Jwcons(var_v4816,NIL,th),th),th),th),Jwcons(Jmakecomp("expression"),Jwcons(var_v4825,Jwcons(var_v4816,Jwcons(var_v4817,NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("test"),arglist);
return(NO);}
static int b_compile(int arglist, int rest, int th);
static int b_compile(int arglist, int rest, int th){
int arg1,arg2,varT,varA,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
var_3533 = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_3533,th) == YES && Junify_var(arg2,varA,th) == YES && 1)
{body = Jwcons(Jmakecomp("parse"),Jwcons(var_3533,Jwcons(varA,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("compile"),arglist);
return(NO);}
static int b_parse(int arglist, int rest, int th);
static int b_parse(int arglist, int rest, int th){
int arg1,arg2,varS,varA,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
loop2:
varS = Jmakevariant(th);
varA = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varS,th) == YES && Junify_var(arg2,varA,th) == YES && 1)
{body = Jwcons(Jmakepred("phrase"),Jwcons(Jwcons(Jmakecomp("program"),Jwcons(varA,NIL,th),th),Jwcons(varS,NIL,th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("parse"),arglist);
return(NO);}
static int b_program(int arglist, int rest, int th);
static int b_program(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v89,var_v80,var_v81,var_v44,var_v35,var_v36,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v44 = Jmakevariant(th);
var_v35 = Jmakevariant(th);
var_v36 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v44,th) == YES && Junify_var(arg2,var_v35,th) == YES && Junify_var(arg3,var_v36,th) == YES && 1)
if (Jcall(Jmakecomp("pl_module"),Jwlistcons(var_v44,Jwlistcons(var_v35,Jwlistcons(var_v36,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v89 = Jmakevariant(th);
var_v80 = Jmakevariant(th);
var_v81 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v89,th) == YES && Junify_var(arg2,var_v80,th) == YES && Junify_var(arg3,var_v81,th) == YES && 1)
if (Jcall(Jmakecomp("statements"),Jwlistcons(var_v89,Jwlistcons(var_v80,Jwlistcons(var_v81,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("program"),arglist);
return(NO);}
static int b_pl_module(int arglist, int rest, int th);
static int b_pl_module(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v176,var_v208,var_v240,var_v268,var_v306,var_v334,var_v359,var_v343,var_v277,var_v138,var_v365,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v176 = Jmakevariant(th);
var_v208 = Jmakevariant(th);
var_v240 = Jmakevariant(th);
var_v268 = Jmakevariant(th);
var_v306 = Jmakevariant(th);
var_v334 = Jmakevariant(th);
var_v359 = Jmakevariant(th);
var_v343 = Jmakevariant(th);
var_v277 = Jmakevariant(th);
var_v138 = Jmakevariant(th);
var_v365 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(1510,Jwcons(var_v343,Jwcons(var_v277,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v138,th) == YES && Junify_var(arg3,var_v365,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v343,Jwcons(var_v138,Jwcons(var_v176,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v176,Jwcons(Jwlistcons(Jmakeconst(":"),var_v208,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v208,Jwcons(Jwlistcons(Jmakeconst("DO"),var_v240,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v240,Jwcons(Jwlistcons(Jmakeconst(";"),var_v268,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("statements"),Jwcons(var_v277,Jwcons(var_v268,Jwcons(var_v306,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v306,Jwcons(Jwlistcons(Jmakeconst("END"),var_v334,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v343,Jwcons(var_v334,Jwcons(var_v359,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v359,Jwcons(Jwlistcons(Jmakeconst(";"),var_v365,th),NIL,th),th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("pl_module"),arglist);
return(NO);}
static int b_statements(int arglist, int rest, int th);
static int b_statements(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v462,var_v450,var_v471,var_v441,var_v463,var_v395,var_v394,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v395 = Jmakevariant(th);
var_v394 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,var_v395,th) == YES && Junify_var(arg3,var_v394,th) == YES && 1)
if(Junify(var_v395,var_v394,th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v462 = Jmakevariant(th);
var_v450 = Jmakevariant(th);
var_v471 = Jmakevariant(th);
var_v441 = Jmakevariant(th);
var_v463 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(var_v450,var_v471,th),th) == YES && Junify_var(arg2,var_v441,th) == YES && Junify_var(arg3,var_v463,th) == YES && 1)
if (Jcall(Jmakecomp("statement"),Jwlistcons(var_v450,Jwlistcons(var_v441,Jwlistcons(var_v462,NIL,th),th),th),th) == YES)
if (Jcall(Jmakecomp("statements"),Jwlistcons(var_v471,Jwlistcons(var_v462,Jwlistcons(var_v463,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("statements"),arglist);
return(NO);}
static int b_statement(int arglist, int rest, int th);
static int b_statement(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v2595,var_v2586,var_v2587,var_v2547,var_v2528,var_v2553,var_v2447,var_v2472,var_v2456,var_v2419,var_v2478,var_v2342,var_v2357,var_v2313,var_v2366,var_v2304,var_v2358,var_v2193,var_v2227,var_v2252,var_v2202,var_v2236,var_v2165,var_v2258,var_v2050,var_v2084,var_v2109,var_v2059,var_v2093,var_v2022,var_v2115,var_v1966,var_v1947,var_v1972,var_v1866,var_v1891,var_v1875,var_v1838,var_v1897,var_v1729,var_v1757,var_v1782,var_v1700,var_v1766,var_v1691,var_v1788,var_v1388,var_v1420,var_v1448,var_v1482,var_v1520,var_v1548,var_v1586,var_v1614,var_v1639,var_v1623,var_v1457,var_v1557,var_v1491,var_v1350,var_v1645,var_v1239,var_v1277,var_v1292,var_v1248,var_v1301,var_v1211,var_v1293,var_v1030,var_v1068,var_v1096,var_v1134,var_v1149,var_v1039,var_v1105,var_v1158,var_v1002,var_v1150,var_v795,var_v823,var_v861,var_v889,var_v927,var_v946,var_v832,var_v898,var_v763,var_v952,var_v556,var_v584,var_v622,var_v650,var_v688,var_v707,var_v593,var_v659,var_v524,var_v713,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v556 = Jmakevariant(th);
var_v584 = Jmakevariant(th);
var_v622 = Jmakevariant(th);
var_v650 = Jmakevariant(th);
var_v688 = Jmakevariant(th);
var_v707 = Jmakevariant(th);
var_v593 = Jmakevariant(th);
var_v659 = Jmakevariant(th);
var_v524 = Jmakevariant(th);
var_v713 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("while"),Jwcons(var_v593,Jwcons(var_v659,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v524,th) == YES && Junify_var(arg3,var_v713,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v524,Jwcons(Jwlistcons(Jmakeconst("DO"),var_v556,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v556,Jwcons(Jwlistcons(Jmakeconst("WHILE"),var_v584,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("test"),Jwcons(var_v593,Jwcons(var_v584,Jwcons(var_v622,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v622,Jwcons(Jwlistcons(Jmakeconst(";"),var_v650,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("statements"),Jwcons(var_v659,Jwcons(var_v650,Jwcons(var_v688,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v688,Jwcons(Jwlistcons(Jmakeconst("END"),var_v707,th),NIL,th),th),th),Jwcons(198,Jwcons(var_v707,Jwcons(Jwlistcons(Jmakeconst(";"),var_v713,th),NIL,th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v795 = Jmakevariant(th);
var_v823 = Jmakevariant(th);
var_v861 = Jmakevariant(th);
var_v889 = Jmakevariant(th);
var_v927 = Jmakevariant(th);
var_v946 = Jmakevariant(th);
var_v832 = Jmakevariant(th);
var_v898 = Jmakevariant(th);
var_v763 = Jmakevariant(th);
var_v952 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("case"),Jwcons(var_v832,Jwcons(var_v898,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v763,th) == YES && Junify_var(arg3,var_v952,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v763,Jwcons(Jwlistcons(Jmakeconst("DO"),var_v795,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v795,Jwcons(Jwlistcons(Jmakeconst("CASE"),var_v823,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("test"),Jwcons(var_v832,Jwcons(var_v823,Jwcons(var_v861,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v861,Jwcons(Jwlistcons(Jmakeconst(";"),var_v889,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("statements"),Jwcons(var_v898,Jwcons(var_v889,Jwcons(var_v927,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v927,Jwcons(Jwlistcons(Jmakeconst("END"),var_v946,th),NIL,th),th),th),Jwcons(198,Jwcons(var_v946,Jwcons(Jwlistcons(Jmakeconst(";"),var_v952,th),NIL,th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v1030 = Jmakevariant(th);
var_v1068 = Jmakevariant(th);
var_v1096 = Jmakevariant(th);
var_v1134 = Jmakevariant(th);
var_v1149 = Jmakevariant(th);
var_v1039 = Jmakevariant(th);
var_v1105 = Jmakevariant(th);
var_v1158 = Jmakevariant(th);
var_v1002 = Jmakevariant(th);
var_v1150 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("if"),Jwcons(var_v1039,Jwcons(var_v1105,Jwcons(var_v1158,NIL,th),th),th),th),th) == YES && Junify_var(arg2,var_v1002,th) == YES && Junify_var(arg3,var_v1150,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1002,Jwcons(Jwlistcons(Jmakeconst("IF"),var_v1030,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("test"),Jwcons(var_v1039,Jwcons(var_v1030,Jwcons(var_v1068,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1068,Jwcons(Jwlistcons(Jmakeconst("THEN"),var_v1096,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("statement"),Jwcons(var_v1105,Jwcons(var_v1096,Jwcons(var_v1134,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1134,Jwcons(Jwlistcons(Jmakeconst("ELSE"),var_v1149,th),NIL,th),th),th),Jwcons(Jmakecomp("statement"),Jwcons(var_v1158,Jwcons(var_v1149,Jwcons(var_v1150,NIL,th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v1239 = Jmakevariant(th);
var_v1277 = Jmakevariant(th);
var_v1292 = Jmakevariant(th);
var_v1248 = Jmakevariant(th);
var_v1301 = Jmakevariant(th);
var_v1211 = Jmakevariant(th);
var_v1293 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("if"),Jwcons(var_v1248,Jwcons(var_v1301,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v1211,th) == YES && Junify_var(arg3,var_v1293,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1211,Jwcons(Jwlistcons(Jmakeconst("IF"),var_v1239,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("test"),Jwcons(var_v1248,Jwcons(var_v1239,Jwcons(var_v1277,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1277,Jwcons(Jwlistcons(Jmakeconst("THEN"),var_v1292,th),NIL,th),th),th),Jwcons(Jmakecomp("statement"),Jwcons(var_v1301,Jwcons(var_v1292,Jwcons(var_v1293,NIL,th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v1388 = Jmakevariant(th);
var_v1420 = Jmakevariant(th);
var_v1448 = Jmakevariant(th);
var_v1482 = Jmakevariant(th);
var_v1520 = Jmakevariant(th);
var_v1548 = Jmakevariant(th);
var_v1586 = Jmakevariant(th);
var_v1614 = Jmakevariant(th);
var_v1639 = Jmakevariant(th);
var_v1623 = Jmakevariant(th);
var_v1457 = Jmakevariant(th);
var_v1557 = Jmakevariant(th);
var_v1491 = Jmakevariant(th);
var_v1350 = Jmakevariant(th);
var_v1645 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("proc"),Jwcons(var_v1623,Jwcons(var_v1457,Jwcons(var_v1557,Jwcons(var_v1491,NIL,th),th),th),th),th),th) == YES && Junify_var(arg2,var_v1350,th) == YES && Junify_var(arg3,var_v1645,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v1623,Jwcons(var_v1350,Jwcons(var_v1388,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1388,Jwcons(Jwlistcons(Jmakeconst(":"),var_v1420,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1420,Jwcons(Jwlistcons(Jmakeconst("PROCEDURE"),var_v1448,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("param"),Jwcons(var_v1457,Jwcons(var_v1448,Jwcons(var_v1482,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("data_type"),Jwcons(var_v1491,Jwcons(var_v1482,Jwcons(var_v1520,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1520,Jwcons(Jwlistcons(Jmakeconst(";"),var_v1548,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("statements"),Jwcons(var_v1557,Jwcons(var_v1548,Jwcons(var_v1586,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1586,Jwcons(Jwlistcons(Jmakeconst("END"),var_v1614,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v1623,Jwcons(var_v1614,Jwcons(var_v1639,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v1639,Jwcons(Jwlistcons(Jmakeconst(";"),var_v1645,th),NIL,th),th),th),th),th),th),th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v1729 = Jmakevariant(th);
var_v1757 = Jmakevariant(th);
var_v1782 = Jmakevariant(th);
var_v1700 = Jmakevariant(th);
var_v1766 = Jmakevariant(th);
var_v1691 = Jmakevariant(th);
var_v1788 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("assign"),Jwcons(var_v1700,Jwcons(var_v1766,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v1691,th) == YES && Junify_var(arg3,var_v1788,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v1700,Jwcons(var_v1691,Jwcons(var_v1729,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1729,Jwcons(Jwlistcons(198,var_v1757,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("expression"),Jwcons(var_v1766,Jwcons(var_v1757,Jwcons(var_v1782,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v1782,Jwcons(Jwlistcons(Jmakeconst(";"),var_v1788,th),NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v1866 = Jmakevariant(th);
var_v1891 = Jmakevariant(th);
var_v1875 = Jmakevariant(th);
var_v1838 = Jmakevariant(th);
var_v1897 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("return"),Jwcons(var_v1875,NIL,th),th),th) == YES && Junify_var(arg2,var_v1838,th) == YES && Junify_var(arg3,var_v1897,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1838,Jwcons(Jwlistcons(Jmakeconst("RETURN"),var_v1866,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("expression"),Jwcons(var_v1875,Jwcons(var_v1866,Jwcons(var_v1891,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v1891,Jwcons(Jwlistcons(Jmakeconst(";"),var_v1897,th),NIL,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v1966 = Jmakevariant(th);
var_v1947 = Jmakevariant(th);
var_v1972 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("return"),Jwcons(Jmakeconst("void"),NIL,th),th),th) == YES && Junify_var(arg2,var_v1947,th) == YES && Junify_var(arg3,var_v1972,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v1947,Jwcons(Jwlistcons(Jmakeconst("RETURN"),var_v1966,th),NIL,th),th),th),Jwcons(198,Jwcons(var_v1966,Jwcons(Jwlistcons(Jmakeconst(";"),var_v1972,th),NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v2050 = Jmakevariant(th);
var_v2084 = Jmakevariant(th);
var_v2109 = Jmakevariant(th);
var_v2059 = Jmakevariant(th);
var_v2093 = Jmakevariant(th);
var_v2022 = Jmakevariant(th);
var_v2115 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("declare"),Jwcons(var_v2059,Jwcons(var_v2093,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v2022,th) == YES && Junify_var(arg3,var_v2115,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v2022,Jwcons(Jwlistcons(Jmakeconst("DECLARE"),var_v2050,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("param"),Jwcons(var_v2059,Jwcons(var_v2050,Jwcons(var_v2084,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("data_type"),Jwcons(var_v2093,Jwcons(var_v2084,Jwcons(var_v2109,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v2109,Jwcons(Jwlistcons(Jmakeconst(";"),var_v2115,th),NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v2193 = Jmakevariant(th);
var_v2227 = Jmakevariant(th);
var_v2252 = Jmakevariant(th);
var_v2202 = Jmakevariant(th);
var_v2236 = Jmakevariant(th);
var_v2165 = Jmakevariant(th);
var_v2258 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("declare"),Jwcons(var_v2202,Jwcons(var_v2236,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v2165,th) == YES && Junify_var(arg3,var_v2258,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v2165,Jwcons(Jwlistcons(Jmakeconst("DECLARE"),var_v2193,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v2202,Jwcons(var_v2193,Jwcons(var_v2227,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("data_type"),Jwcons(var_v2236,Jwcons(var_v2227,Jwcons(var_v2252,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v2252,Jwcons(Jwlistcons(Jmakeconst(";"),var_v2258,th),NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v2342 = Jmakevariant(th);
var_v2357 = Jmakevariant(th);
var_v2313 = Jmakevariant(th);
var_v2366 = Jmakevariant(th);
var_v2304 = Jmakevariant(th);
var_v2358 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("label"),Jwcons(var_v2313,Jwcons(var_v2366,NIL,th),th),th),th) == YES && Junify_var(arg2,var_v2304,th) == YES && Junify_var(arg3,var_v2358,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v2313,Jwcons(var_v2304,Jwcons(var_v2342,NIL,th),th),th),th),Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v2342,Jwcons(Jwlistcons(Jmakeconst(":"),var_v2357,th),NIL,th),th),th),Jwcons(Jmakecomp("statement"),Jwcons(var_v2366,Jwcons(var_v2357,Jwcons(var_v2358,NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v2447 = Jmakevariant(th);
var_v2472 = Jmakevariant(th);
var_v2456 = Jmakevariant(th);
var_v2419 = Jmakevariant(th);
var_v2478 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakepred("goto"),Jwcons(var_v2456,NIL,th),th),th) == YES && Junify_var(arg2,var_v2419,th) == YES && Junify_var(arg3,var_v2478,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v2419,Jwcons(Jwlistcons(Jmakeconst("GOTO"),var_v2447,th),NIL,th),th),th),Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("identifier"),Jwcons(var_v2456,Jwcons(var_v2447,Jwcons(var_v2472,NIL,th),th),th),th),Jwcons(198,Jwcons(var_v2472,Jwcons(Jwlistcons(Jmakeconst(";"),var_v2478,th),NIL,th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v2547 = Jmakevariant(th);
var_v2528 = Jmakevariant(th);
var_v2553 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_atom(arg1,685,th) == YES && Junify_var(arg2,var_v2528,th) == YES && Junify_var(arg3,var_v2553,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(198,Jwcons(var_v2528,Jwcons(Jwlistcons(Jmakeconst("HALT"),var_v2547,th),NIL,th),th),th),Jwcons(198,Jwcons(var_v2547,Jwcons(Jwlistcons(Jmakeconst(";"),var_v2553,th),NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
var_v2595 = Jmakevariant(th);
var_v2586 = Jmakevariant(th);
var_v2587 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwcons(Jmakecomp("block"),Jwcons(var_v2595,NIL,th),th),th) == YES && Junify_var(arg2,var_v2586,th) == YES && Junify_var(arg3,var_v2587,th) == YES && 1)
{body = Jwcons(Jmakecomp("block"),Jwcons(var_v2595,Jwcons(var_v2586,Jwcons(var_v2587,NIL,th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("statement"),arglist);
return(NO);}
static int b_block(int arglist, int rest, int th);
static int b_block(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v2680,var_v2708,var_v2746,var_v2765,var_v2717,var_v2648,var_v2771,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v2680 = Jmakevariant(th);
var_v2708 = Jmakevariant(th);
var_v2746 = Jmakevariant(th);
var_v2765 = Jmakevariant(th);
var_v2717 = Jmakevariant(th);
var_v2648 = Jmakevariant(th);
var_v2771 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v2717,th) == YES && Junify_var(arg2,var_v2648,th) == YES && Junify_var(arg3,var_v2771,th) == YES && 1)
if(Junify(var_v2648,Jwlistcons(Jmakeconst("DO"),var_v2680,th),th)==YES && Jinc_proof(th))
if(Junify(var_v2680,Jwlistcons(Jmakeconst(";"),var_v2708,th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("statements"),Jwlistcons(var_v2717,Jwlistcons(var_v2708,Jwlistcons(var_v2746,NIL,th),th),th),th) == YES)
if(Junify(var_v2746,Jwlistcons(Jmakeconst("END"),var_v2765,th),th)==YES && Jinc_proof(th))
if(Junify(var_v2765,Jwlistcons(Jmakeconst(";"),var_v2771,th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("block"),arglist);
return(NO);}
static int b_param(int arglist, int rest, int th);
static int b_param(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v2849,var_v2874,var_v2858,var_v2821,var_v2880,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v2849 = Jmakevariant(th);
var_v2874 = Jmakevariant(th);
var_v2858 = Jmakevariant(th);
var_v2821 = Jmakevariant(th);
var_v2880 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v2858,th) == YES && Junify_var(arg2,var_v2821,th) == YES && Junify_var(arg3,var_v2880,th) == YES && 1)
if(Junify(var_v2821,Jwlistcons(Jmakeconst("("),var_v2849,th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("params"),Jwlistcons(var_v2858,Jwlistcons(var_v2849,Jwlistcons(var_v2874,NIL,th),th),th),th) == YES)
if(Junify(var_v2874,Jwlistcons(Jmakeconst(")"),var_v2880,th),th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("param"),arglist);
return(NO);}
static int b_params(int arglist, int rest, int th);
static int b_params(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v3195,var_v3210,var_v3166,var_v3219,var_v3157,var_v3211,var_v3084,var_v3099,var_v3055,var_v3108,var_v3046,var_v3100,var_v2997,var_v2988,var_v2989,var_v2952,var_v2943,var_v2944,var_v2910,var_v2909,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v2910 = Jmakevariant(th);
var_v2909 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_nil(arg1,th) == YES && Junify_var(arg2,var_v2910,th) == YES && Junify_var(arg3,var_v2909,th) == YES && 1)
if(Junify(var_v2910,var_v2909,th)==YES && Jinc_proof(th))
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v2952 = Jmakevariant(th);
var_v2943 = Jmakevariant(th);
var_v2944 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwlistcons(var_v2952,NIL,th),th) == YES && Junify_var(arg2,var_v2943,th) == YES && Junify_var(arg3,var_v2944,th) == YES && 1)
if (Jcall(Jmakecomp("identifier"),Jwlistcons(var_v2952,Jwlistcons(var_v2943,Jwlistcons(var_v2944,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v2997 = Jmakevariant(th);
var_v2988 = Jmakevariant(th);
var_v2989 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify(arg1,Jwlistcons(var_v2997,NIL,th),th) == YES && Junify_var(arg2,var_v2988,th) == YES && Junify_var(arg3,var_v2989,th) == YES && 1)
if (Jcall(Jmakecomp("pl_constant"),Jwlistcons(var_v2997,Jwlistcons(var_v2988,Jwlistcons(var_v2989,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v3084 = Jmakevariant(th);
var_v3099 = Jmakevariant(th);
var_v3055 = Jmakevariant(th);
var_v3108 = Jmakevariant(th);
var_v3046 = Jmakevariant(th);
var_v3100 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(var_v3055,var_v3108,th),th) == YES && Junify_var(arg2,var_v3046,th) == YES && Junify_var(arg3,var_v3100,th) == YES && 1)
if (Jcall(Jmakecomp("identifier"),Jwlistcons(var_v3055,Jwlistcons(var_v3046,Jwlistcons(var_v3084,NIL,th),th),th),th) == YES)
if(Junify(var_v3084,Jwlistcons(Jmakeconst(","),var_v3099,th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("params"),Jwlistcons(var_v3108,Jwlistcons(var_v3099,Jwlistcons(var_v3100,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v3195 = Jmakevariant(th);
var_v3210 = Jmakevariant(th);
var_v3166 = Jmakevariant(th);
var_v3219 = Jmakevariant(th);
var_v3157 = Jmakevariant(th);
var_v3211 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_pair(arg1,Jwlistcons(var_v3166,var_v3219,th),th) == YES && Junify_var(arg2,var_v3157,th) == YES && Junify_var(arg3,var_v3211,th) == YES && 1)
if (Jcall(Jmakecomp("pl_constant"),Jwlistcons(var_v3166,Jwlistcons(var_v3157,Jwlistcons(var_v3195,NIL,th),th),th),th) == YES)
if(Junify(var_v3195,Jwlistcons(Jmakeconst(","),var_v3210,th),th)==YES && Jinc_proof(th))
if (Jcall(Jmakecomp("params"),Jwlistcons(var_v3219,Jwlistcons(var_v3210,Jwlistcons(var_v3211,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("params"),arglist);
return(NO);}
static int b_expression(int arglist, int rest, int th);
static int b_expression(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v3354,var_v3345,var_v3346,var_v3309,var_v3300,var_v3301,var_v3264,var_v3255,var_v3256,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v3264 = Jmakevariant(th);
var_v3255 = Jmakevariant(th);
var_v3256 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v3264,th) == YES && Junify_var(arg2,var_v3255,th) == YES && Junify_var(arg3,var_v3256,th) == YES && 1)
if (Jcall(Jmakecomp("pl_constant"),Jwlistcons(var_v3264,Jwlistcons(var_v3255,Jwlistcons(var_v3256,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v3309 = Jmakevariant(th);
var_v3300 = Jmakevariant(th);
var_v3301 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v3309,th) == YES && Junify_var(arg2,var_v3300,th) == YES && Junify_var(arg3,var_v3301,th) == YES && 1)
if (Jcall(Jmakecomp("pl_function"),Jwlistcons(var_v3309,Jwlistcons(var_v3300,Jwlistcons(var_v3301,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
var_v3354 = Jmakevariant(th);
var_v3345 = Jmakevariant(th);
var_v3346 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v3354,th) == YES && Junify_var(arg2,var_v3345,th) == YES && Junify_var(arg3,var_v3346,th) == YES && 1)
if (Jcall(Jmakecomp("add_expr"),Jwlistcons(var_v3354,Jwlistcons(var_v3345,Jwlistcons(var_v3346,NIL,th),th),th),th) == YES)
return(Jexec_all(rest,Jget_sp(th),th));
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("expression"),arglist);
return(NO);}
static int b_add_expr(int arglist, int rest, int th);
static int b_add_expr(int arglist, int rest, int th){
int arg1,arg2,arg3,var_v3433,var_v3424,var_v3437,var_v3403,var_v3425,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
loop3:
var_v3433 = Jmakevariant(th);
var_v3424 = Jmakevariant(th);
var_v3437 = Jmakevariant(th);
var_v3403 = Jmakevariant(th);
var_v3425 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v3437,th) == YES && Junify_var(arg2,var_v3403,th) == YES && Junify_var(arg3,var_v3425,th) == YES && 1)
{body = Jwlist3(Jmakeope(","),Jwcons(Jmakecomp("mul_expr"),Jwcons(var_v3433,Jwcons(var_v3403,Jwcons(var_v3424,NIL,th),th),th),th),Jwcons(Jmakecomp("add_rest"),Jwcons(var_v3433,Jwcons(var_v3437,Jwcons(var_v3424,Jwcons(var_v3425,NIL,th),th),th),th),th),th);
if((res=Jexec_all(Jaddtail_body(rest,body,th),Jget_sp(th),th)) == YES)
return(YES);
Jset_ac(save3,th);
Junbind(save2,th);
Jset_wp(save1,th);}
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("add_expr"),arglist);
return(NO);}
static int b_add_rest(int arglist, int rest, int th);
static int b_add_rest(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,var_v3607,var_v3616,var_v3615,var_v3524,var_v3499,var_v3533,var_v3556,var_v3575,var_v3566,var_v3461,var_v3579,var_v3490,var_v3567,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
loop4:
var_v3524 = Jmakevariant(th);
var_v3499 = Jmakevariant(th);
var_v3533 = Jmakevariant(th);
var_v3556 = Jmakevariant(th);
var_v3575 = Jmakevariant(th);
var_v3566 = Jmakevariant(th);
var_v3461 = Jmakevariant(th);
var_v3579 = Jmakevariant(th);
var_v3490 = Jmakevariant(th);
var_v3567 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v3461,th) == YES && Junify_var(arg2,var_v3579,th) == YES && Junify_var(arg3,var_v3490,th) == YES && Junify_var(arg4,var_v3567,th) == YES && 1)
if (Jcall(Jmakecomp("add_op"),Jwlistcons(var_v3499,Jwlistcons(var_v3490,Jwlistcons(var_v3524,NIL,th),th),th),th) == YES)
if (Jcall(Jmakecomp("mul_expr"),Jwlistcons(var_v3533,Jwlistcons(var_v3524,Jwlistcons(var_v3556,NIL,th),th),th),th) == YES)
if (Jcall(