#include "jump.h"
void foo(void){dynamic_clause = Jlist3(Jmakesys(":-"),Jcons(Jmakepred("foo"),Jcons(Jmakevar("varX"),NIL)),Jcons(1159,Jcons(Jmakevar("varX"),NIL)));
}void boo(void){dynamic_clause = Jlist3(Jmakesys(":-"),Jcons(Jmakepred("boo"),Jcons(Jmakevar("varY"),NIL)),Jcons(1159,Jcons(Jmakevar("varY"),NIL)));
}void init_tpredicate(void){}
void init_declare(void){int body,th; th=0;
body = Jwcons(1493,Jwcons(Jwcons(52,Jwcons(Jmakecomp("foo"),Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
Jexec_all(body,Jget_sp(th),th);
body = Jwcons(1493,Jwcons(Jwcons(52,Jwcons(Jmakecomp("boo"),Jwcons(Jmakeint(1),NIL,th),th),th),NIL,th),th);
Jexec_all(body,Jget_sp(th),th);
}