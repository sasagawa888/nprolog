/* idea memo for new compiler */
#include "jump.h"
int fact(int arg1, int arg2){
    int varX1,varY1,varX,varY,body,save1;
    save1 = Jget_wp();
if(Jmatch(Jmakeint(0),arg1) != NO && Jmatch(Jmakeint(1),arg2) != NO && 1){
    return(Jwlist2(arg1,arg2));
}
varX1 = Jmakevariant();
varY1 = Jmakevariant();
save1 = Jget_wp();
if((varX=Jmatch(varX,arg1)) != NO && (varY=Jmatch(varY,arg2)) != NO && 1)
body = Jwlist3(Jmakeope(","),Jwcons(168,Jwcons(varX1,Jwcons(Jwcons(1395,Jwcons(varX,Jwcons(Jmakeint(1),NIL))),NIL))),NIL);
Jexec_all(body,Jget_sp());
return(fact(varX,varY));
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
Jtakeout(arg1,Jnth(res,0));
Jtakeout(arg2,Jnth(res,1));
return(Jexec_all(rest,Jget_sp()));}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("fact"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("fact",b_fact);
}
void init_declare(void){int body;
}