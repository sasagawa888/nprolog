#include "jump.h"
void nqueens(void){dynamic_clause = Jlist3(Jmakeope(":-"),Jcons(Jmakepred("nqueens"),Jcons(Jmakevar("varQueens"),NIL)),Jlist3(Jmakeope(","),Jcons(755,Jcons(Jmakevar("varQueens"),Jcons(Jmakeint(9),NIL))),Jlist3(Jmakeope(","),Jcons(Jmakeuser("ins"),Jcons(Jmakevar("varQueens"),Jcons(Jcons(Jmakeuser(".."),Jcons(Jmakeint(1),Jcons(Jmakeint(9),NIL))),NIL))),Jlist3(Jmakeope(","),Jcons(1761,Jcons(Jmakevar("varQueens"),NIL)),Jlist3(Jmakeope(","),Jcons(Jmakepred("safe"),Jcons(Jmakevar("varQueens"),NIL)),Jcons(Jmakepred("label"),Jcons(Jmakevar("varQueens"),Jcons(1186,NIL))))))));
Jadd_dynamic(dynamic_clause);
}void safe(void){dynamic_clause = Jcons(Jmakepred("safe"),Jcons(,NIL));
Jadd_dynamic(dynamic_clause);
dynamic_clause = Jlist3(Jmakeope(":-"),Jcons(Jmakepred("safe"),Jcons(Jlistcons(Jmakevar("varQ"),Jmakepred("varQ"),