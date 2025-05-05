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
	arg1 = revderef(car(arglist), th);
	fd_sets = listcons(copy_heap(variable_convert1(arg1)), fd_sets);
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
	if (unify(arg1, fd_sets, th) == YES)
	    return (prove_all(rest, sp[th], th));

	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_constraint_var(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, var, min, max;

    n = length(arglist);
    ind = makeind("constraint_var", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	var = variable_convert1(arg1);
	SET_ARITY(var, fd_var_max);
	min = GET_INT(cadr(arg2));
	max = GET_INT(caddr(arg2));
	fd_min[fd_var_max] = min;
	fd_max[fd_var_max] = max;
	fd_len[fd_var_max] = max - min;
	fd_var_max++;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_constraint_vars(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, elt, var, min, max;

    n = length(arglist);
    ind = makeind("constraint_vars", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	while (arg1 != NIL) {
	    elt = car(arg1);
	    var = variable_convert1(elt);
	    SET_ARITY(var, fd_var_max);
	    min = GET_INT(cadr(arg2));
	    max = GET_INT(caddr(arg2));
	    fd_min[fd_var_max] = min;
	    fd_max[fd_var_max] = max;
	    fd_len[fd_var_max] = max - min;
	    fd_var_max++;
	    arg1 = cdr(arg1);
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_all_different(int arglist, int rest, int th)
{
    int n, ind, arg1, idx;

    n = length(arglist);
    ind = makeind("all_different", n, th);
    if (n == 1) {
	arg1 = variable_convert1(car(arglist));
	while (arg1 != NIL) {
	    idx = GET_ARITY(car(arg1));
	    fd_unique[idx] = 1;
	    arg1 = cdr(arg1);
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int fd_eq(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("#=")))
	return (1);
    else
	return (0);
}

int fd_neq(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("#\\=")))
	return (1);
    else
	return (0);
}

int fd_greater(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("#>")))
	return (1);
    else
	return (0);
}

int fd_eqgreater(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("#>=")))
	return (1);
    else
	return (0);
}

int fd_smaller(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("#<")))
	return (1);
    else
	return (0);
}

int fd_eqsmaller(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("#<=")))
	return (1);
    else
	return (0);
}


int uniquep()
{
    int idx1, idx2, val;

    idx1 = fd_var_idx;
    while (idx1 > 0) {
	val = fd_domain[idx1] + fd_min[idx1];
	idx2 = idx1 - 1;
	while (idx2 >= 0) {
	    if (fd_unique[idx2] == 1
		&& fd_domain[idx2] + fd_min[idx2] == val)
		return (NO);

	    idx2--;
	}
	idx1--;
    }
    return (YES);
}


int inc_domain()
{
    int i;

    i = 0;
    // fine unbind var index
    while (i < fd_var_max) {
	if (fd_domain[i] == -1) {
	    fd_domain[i] = 0;
	    fd_var_idx = i;
	    return (YES);
	}
	i++;
    }
    i = fd_var_max - 1;
    // increment
    fd_domain[i]++;
    // carry
    if (fd_domain[i] > fd_len[i]) {
	fd_domain[i] = -1;
	i--;
	while (i >= 0) {
	    fd_domain[i]++;
	    if (fd_domain[i] > fd_len[i]) {
		if (i == 0)	// already incremented
		    return (NO);
		fd_domain[i] = -1;
		i--;
		fd_var_idx = i;
	    } else {
		fd_var_idx = i;
		return (YES);
	    }
	}

    } else
	return (YES);

    return (NO);
}

int next_domain()
{
    int res;

  retry:
    res = inc_domain();
    if (res == NO)
	return (NO);
    else if (fd_unique[fd_var_idx] == 0)	//not unique var
	return (YES);
    else if (fd_unique[fd_var_idx] == 1 && uniquep() == YES)
	return (YES);
    else
	goto retry;
}

int prune_domain()
{
    int i;

    i = fd_var_idx + 1;
    while (i < fd_var_max) {
	fd_domain[i] = 0;
	i++;
    }

    i = fd_var_idx;
    // increment
    fd_domain[i]++;
    // carry
    if (fd_domain[i] > fd_len[i]) {
	fd_domain[i] = -1;
	i--;
	while (i >= 0) {
	    fd_domain[i]++;
	    if (fd_domain[i] > fd_len[i]) {
		if (i == 0)	// already incremented
		    return (NO);
		fd_domain[i] = -1;
		i--;
		fd_var_idx = i;
	    } else {
		fd_var_idx = i;
		return (YES);
	    }
	}

    } else
	return (YES);

    return (NO);
}

/* e.g. X+Y+Z#=3 X<-1 1+Y+Z#=3*/
void bind_variable(int expr)
{
    int idx, val;

    if (nullp(expr))
	return;
    else if (compiler_variable_p(expr)) {
	idx = GET_ARITY(expr);
	val = fd_domain[idx] + fd_min[idx];
	SET_CDR(expr, makeint(val));
	return;
    } else if (atomp(expr)) {
	return;
    } else if (structurep(expr)) {
	bind_variable(cadr(expr));
	bind_variable(caddr(expr));
	return;
    }
}

/* e.g.  1+Y+Z#=3 -> X+Y+Z#=3*/
void unbind_variable(int expr)
{
    if (nullp(expr))
	return;
    else if (compiler_variable_p(expr)) {
	SET_CDR(expr, NIL);
	return;
    } else if (atomp(expr)) {
	return;
    } else if (structurep(expr)) {
	unbind_variable(cadr(expr));
	unbind_variable(caddr(expr));
	return;
    }
}

int fd_plus(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("+")))
	return (1);
    else
	return (0);
}

int fd_minus(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("-")))
	return (1);
    else
	return (0);
}

int fd_mult(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("*")))
	return (1);
    else
	return (0);
}



int fd_analyze1(int form, int flag)
{
    int idx, left, right;

    if (numberp(form))
	return (GET_INT(form));
    else if (compiler_variable_p(form)) {
	idx = GET_ARITY(form);
	if (fd_domain[idx] == -1 && flag == 0) {
	    fd_analyze_sw = 1;
	    return (fd_min[idx]);
	} else if (fd_domain[idx] == -1 && flag == 1) {
	    fd_analyze_sw = 1;
	    return (fd_max[idx]);
	} else
	    return (fd_domain[idx]);
    } else if (fd_plus(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	return (left + right);
    } else if (fd_minus(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	return (left - right);
    } else if (fd_mult(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	return (left * right);
    }
    return (NO);
}

/* if form has unbind variable [min,max]
 * if form has no unbind variable [val] 
*/
int fd_analyze(int form)
{
    int res1, res2;

    fd_analyze_sw = 0;		// switch if form has unbind variable 1, else 0
    res1 = fd_analyze1(form, 0);
    if (fd_analyze_sw)
	return (list1(makeint(res1)));
    else {
	res2 = fd_analyze1(form, 1);
	return (list2(makeint(res1), makeint(res2)));
    }

}


int domain_to_value(int varlist, int th);
int domain_to_value(int varlist, int th)
{
    int var, val, idx;

    if (nullp(varlist))
	return (NIL);
    else {
	var = variable_convert1(revderef(car(varlist), th));
	idx = GET_ARITY(var);
	val = makeint(fd_domain[idx] + fd_min[idx]);
	return (listcons(val, domain_to_value(cdr(varlist), th)));
    }

}

int in_interval(int value, int range)
{
    if (eqsmallerp(car(range), car(value))
	&& eqgreaterp(cadr(range), car(value)))
	return (1);
    else
	return (0);
}

int overlap(int left, int right)
{
    if (!
	(greaterp(car(right), cadr(left))
	 || greaterp(car(left), cadr(right))))
	return (1);
    else
	return (0);
}

int satisfiablep(int expr)
{
    int left, right;

    if (expr == NIL)
	return (YES);
    else if (fd_eq(expr)) {	//#=
	left = fd_analyze(cadr(expr));
	right = fd_analyze(caddr(expr));
	if (length(left) == 1 && length(right) == 1) {
	    if (equalp(left, right))
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (in_interval(right, left))
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (in_interval(left, right))
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (overlap(left, right))
		return (YES);
	    else
		return (NO);
	}
    } else if (fd_neq(expr)) {	//#\=
	left = fd_analyze(cadr(expr));
	right = fd_analyze(caddr(expr));
	if (length(left) == 1 && length(right) == 1) {
	    if (smallerp(left, right))
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (!in_interval(right, left))
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (!in_interval(left, right))
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (!overlap(left, right))
		return (YES);
	    else
		return (UNKNOWN);
	}
    } else if (fd_smaller(expr)) {	//#<

    } else if (fd_eqsmaller(expr)) {	//#<=

    } else if (fd_greater(expr)) {	//#>

    } else if (fd_eqgreater(expr)) {	//#>=

    }
    return (0);
}

int propagate_all(int sets)
{
    int res;
    if (sets == NIL)
	return (YES);

    if (propagate(car(sets)) == YES) {
	return (propagate_all(cdr(sets)));
    } else {
	res = prune_domain();
	if (res == NO)
	    return (NO);

	propagate_all(fd_sets);
    }

    return (NO);
}

int propagate(int expr)
{
    int res;

    res = next_domain();
    if (res == NO)
	return (NO);
  loop:
    bind_variable(expr);
    if (satisfiablep(expr) == YES) {
	if (fd_var_idx == fd_var_max - 1)
	    return (YES);

	return (propagate(expr));
    } else {
	res = prune_domain();
	if (res == NO) {
	    unbind_variable(expr);
	    goto loop;
	}

	bind_variable(expr);
	if (satisfiablep(expr) == YES)
	    return (propagate(expr));
    }
    return (NO);
}

int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1, save, res;

    n = length(arglist);
    ind = makeind("label", n, th);
    save = sp[th];
    if (n == 1) {
	arg1 = car(arglist);

	fd_sets = reverse(fd_sets);
	if (fd_sets == NIL)
	    res = propagate(fd_sets);
	else
	    res = propagate_all(fd_sets);


	if (res == NO)
	    return (NO);

      loop:
	unify(arg1, domain_to_value(arg1, th), th);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);

	unbind(save, th);
	if (fd_sets == NIL)
	    res = propagate(fd_sets);
	else
	    res = propagate_all(fd_sets);

	if (res == YES)
	    goto loop;
	else
	    return (NO);
    }

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
