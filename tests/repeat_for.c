/* Idea memo

repeat_for(0) :- !, fail.
repeat_for(N).
repeat_for(N) :-
    N > 0, !,
    M is N - 1,
    repeat_for(M).

*/


#include "jump.h"
int b_repeat_for(int arglist, int rest);
int b_repeat_for(int arglist, int rest) {
    int n, varN, varM;
    n = Jlength(arglist);
    if (n == 1) { 
        loop:
        Jinc_proof(); 
        if (Jcar(arglist) == Jmakeint(0) && 1) return(NO); 
        if (1) { //not unify
            varN = Jcar(arglist);
            if (Jprove_all(rest, Jget_sp()) == YES) return(YES);
        }
        if (1) { //not unify
            varN = Jcar(arglist);
            varM = Jminus(Jderef(varN), Jmakeint(1)); // M = N - 1
            arglist = Jwcons(varM, NIL); // new arglist
            goto loop; 
        }
    }
    return(NO); 
}

void init_tpredicate(void){
(deftpred)("repeat_for",b_repeat_for);
}
void init_declare(void){int body;
}