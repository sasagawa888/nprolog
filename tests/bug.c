#include "jump.h"
int b_listn(int arglist, int rest, int th);
int b_listn(int arglist, int rest, int th){
int n,head,varN1,varN,varR,varX;
n = Jlength(arglist);
if(n == 2){
loop:
Jinc_proof(th);
head = Jwcons(Jmakeint(0),Jwcons(NIL,NIL,th),th);
if(Jnumeqp(Jmakeint(0),Jcar(arglist)) && 
Jcar(Jcdr(arglist)) == NIL && 1){if(Junify(arglist,head,th)==YES) return(Jexec_all(rest,Jget_sp(th),th)); else return(NO);}
varN = Jcar(arglist);
varR = Jcar(Jcar(Jcdr(arglist)));
varX = Jcdr(Jcar(Jcdr(arglist)));
{varR = Jrandi(Jmakeint(100));
varN1 = Jminus(Jderef(varN,th),Jmakeint(1));
arglist = Jwcons(varN1,Jwcons(varX,NIL,th),th);
goto loop;
}}return(NO);
}
void init_tpredicate(void){(deftpred)("listn",b_listn);
}
void init_declare(void){int body,th; th=0;
}