#include "jump.h"
int b_isc(int arglist, int rest);
int b_isc(int arglist, int rest){
int varR,varI,n,body,save1,save2,save3,tree,res;
save2 = Jget_sp();
save3 = Jget_up();
n = Jlength(arglist);
if(n == -1){
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("isc"),arglist);
return(NO);}
void init_tpredicate(void){(deftinfix)("isc",b_isc,700,XFX);
}
void init_declare(void){int body;
body = Jwcons(775,Jwcons(Jmakeint(700),Jwcons(Jmakeconst("xfx"),Jwcons(Jmakeconst("isc"),NIL))));
Jprove_all(body,Jget_sp());
}