#include "jump.h"
static int b_add_rest(int arglist, int rest, int th);
static int b_add_rest(int arglist, int rest, int th){
int arg1,arg2,arg3,arg4,var_v169,var_v178,var_v177,var_v86,var_v61,var_v95,var_v118,var_v137,var_v128,var_v23,var_v141,var_v52,var_v129,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 4){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
arg4 = Jnth(arglist,4);
loop4:
var_v86 = Jmakevariant(th);
var_v61 = Jmakevariant(th);
var_v95 = Jmakevariant(th);
var_v118 = Jmakevariant(th);
var_v137 = Jmakevariant(th);
var_v128 = Jmakevariant(th);
var_v23 = Jmakevariant(th);
var_v141 = Jmakevariant(th);
var_v52 = Jmakevariant(th);
var_v129 = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,var_v23,th) == YES && Junify_var(arg2,var_v141,th) == YES && Junify_var(arg3,var_v52,th) == YES && Junify_var(arg4,var_v129,th) == YES && 1)
if (Jcall(Jmakepred("add_op"),Jwlistcons(var_v61,Jwlistcons(var_v52,Jwlistcons(var_v86,NIL,th),th),th),th) == YES)
if (Jcall(Jmakepred("mul_expr"),Jwlistcons(var_v95,Jwlistcons(var_v86,Jwlistcons(var_v118,NIL,th),th),th),th) == YES)
if (Jcall(