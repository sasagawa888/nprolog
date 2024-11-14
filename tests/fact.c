/* idea memo for new compiler */
#include "jump.h"
int fact(int arg1, int arg2){
    int varX1,varY1,varX,varY,body,save1,res;
    save1 = Jget_wp();
if(Jmatch(arg1,Jmakeint(0)) != NO && Jmatch(arg2,Jmakeint(1)) != NO && 1){
    return(Jwlist2(Jmakeint(0),Jmakeint(1)));
}
varX1 = Jmakevariant();
varY1 = Jmakevariant();
save1 = Jget_wp();
if((varX=Jmatch(varX,arg1)) != NO && 1)
body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varX1,Jwcons(Jwcons(1395,Jwcons(varX,Jwcons(Jmakeint(1),NIL))),NIL))),NIL);
Jexec_all(body,Jget_sp());
res = fact(Jderef(varX1),varY);
Junify(varY1,Jnth(res,2));
body = Jwcons(168,Jwcons(varY,Jwcons(Jwcons(1436,Jwcons(varY1,Jwcons(varX,NIL))),NIL)));
Jexec_all(body,Jget_sp());
return(Jwlist2(Jnth(res,1),Jderef(varY)));
}

int b_fact(int arglist, int rest);
int b_fact(int arglist, int rest){
int arg1,arg2,varX1,varY1,varX,varY,n,body,save1,save2,goal,cont,res;
save2 = Jget_sp();
n = Jlength(arglist);
if(n == 2){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
varX=Jtakein(arg1);
varY=Jtakein(arg2);
res = fact(varX,varY);
Jtakeout(arg1,Jnth(res,1));
Jtakeout(arg2,Jnth(res,2));
return(Jexec_all(rest,Jget_sp()));}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("fact",b_fact);
}
void init_declare(void){int body;
}