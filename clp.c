/*
*     CLPFD builtin predicates 
*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "npl.h"


int b_add_constraint(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("add_constraint", n, th);
    if (n == 1) {
	arg1 = car(arglist);
    constraint_set = cons(arg1,constraint_set);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

