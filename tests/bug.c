#include "jump.h"
int b_myappend(int arglist, int rest);
int b_myappend(int arglist, int rest){
int n,head,varB,varA,varC,varL;
n = Jlength(arglist);
if(n == 3){
loop:
Jinc_proof();
varL = Jmakevariant();
head = Jwcons(NIL,Jwcons(varL,Jwcons(varL,NIL)));
if(Jcar(arglist) == NIL && 1){if(Junify(arglist,head)==YES) return(Jprove_all(rest,Jget_sp())); else return(NO);}
varA = Jcar(Jcar(arglist));
varL = Jcdr(Jcar(arglist));
varB = Jcar(Jcdr(arglist));
varA = Jcar(Jcar(Jcdr(Jcdr(arglist))));
varC = Jcdr(Jcar(Jcdr(Jcdr(arglist))));
{arglist = Jwcons(varL,Jwcons(varB,Jwcons(varC,NIL)));
goto loop;
}}return(NO);
}
void init_tpredicate(void){(deftpred)("myappend",b_myappend);
}
void init_declare(void){int body;
}