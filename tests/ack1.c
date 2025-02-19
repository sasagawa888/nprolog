#include "jump.h"
int b_ack(int arglist, int rest, int th);
int b_ack(int arglist, int rest, int th){
int arg1,arg2,arg3,varM,varN,varX,n,body,save1,save2,save3,goal,cont,res;
save2 = Jget_sp(th);
save3 = Jget_ac(th);
n = Jlength(arglist);
if(n == 3){
arg1 = Jnth(arglist,1);
arg2 = Jnth(arglist,2);
arg3 = Jnth(arglist,3);
varM = Jmakevariant(th);
varN = Jmakevariant(th);
varX = Jmakevariant(th);
save1 = Jget_wp(th);
if(Junify_var(arg1,varM,th) == YES && Junify_var(arg2,varN,th) == YES && Junify_var(arg3,varX,th) == YES && 1)
{ //ackermann function
          int a(int m, int n){
              if(m==0) return(n+1);
              else if(n==0) return(a(m-1,1));
              else return(a(m-1,a(m,n-1)));
          }
          int m = Jget_int(Jderef(varM,th));
          int n = Jget_int(Jderef(varN,th));
          int res = a(m,n);
          Junify(varX,Jmakeint(res),th);
          return(Jexec_all(rest,Jget_sp(th),th)); }
return(NO);}
Jerrorcomp(Jmakeint(ARITY_ERR),Jmakecomp("ack"),arglist);
return(NO);}
void init_tpredicate(void){(deftpred)("ack",b_ack);
}
void init_declare(void){int body,th; th=0;
}