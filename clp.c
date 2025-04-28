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
	constraint_set =
	    listcons(copy_heap(variable_convert1(arg1)), constraint_set);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_constraint_set(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("constraint_set", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (unify(arg1, constraint_set, th) == YES)
	    return (prove_all(rest, sp[th], th));

	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int constraint_propagate()
{
    int expr;

    constraint_set = reverse(constraint_set);
    constraint_var = NIL;
    constraint_env = NIL;
    constraint_domain = NIL;

    while (constraint_set != NIL) {
        expr = car(constraint_set);
        //if (expr is (X #= Y)) {
            // If only one solution exists, remove from constraint_set
            // If none, break
            // Otherwise, narrow range and search
        //} else if (expr is (X in A..Z)) {
            // Register variable and initial range
        //}
        constraint_set = cdr(constraint_set);
    }
    return NO;
}

void constraint_search(int expr, int var, int env) {
    // Try all candidates, like Lisp’s dolist
    // Save valid values to domain
    // Merge into existing domains
}