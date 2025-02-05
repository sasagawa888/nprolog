#include "jump.h"
void init_tpredicate(void){}
void init_declare(void){int body,th; th=0;
body = Jwcons(1493,Jwcons(Jwcons(52,Jwcons(Jmakecomp("foo"),Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
Jexec_all(body,Jget_sp(th),th);
}