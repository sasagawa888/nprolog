/*
*     CLPFD builtin predicates 
*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "npl.h"

#define UNBOUND -1

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

	var = variable_convert1(revderef(arg1, th));
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
	    var = variable_convert1(revderef(elt, th));
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
	arg1 = variable_convert1(revderef(car(arglist), th));
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


void fd_push(int x)
{
    fd_selected[fd_sel_idx] = x;
}

void fd_pop()
{
    fd_sel_idx--;
}

int fd_duplicate(int x)
{
    int i;

    for (i = 0; i < fd_sel_idx; i++) {
	if (fd_selected[i] == x)
	    return (1);
    }
    return (0);
}

int next_domain()
{
    int i;

    if (fd_domain[0] > fd_len[0])
	return (NO);		// all incremented

    i = 0;
    // fine unbind var index
    while (i < fd_var_max) {
	if (fd_domain[i] == UNBOUND) {
	    fd_domain[i] = 0;
	    fd_var_idx = i;
	    if (fd_unique[i] == 1)
		fd_push(fd_domain[i] + fd_min[i]);
	    return (YES);
	}
	i++;
    }
    i = fd_var_max - 1;
    // increment
    fd_domain[i]++;
	// if unique variable and duplicate then skip
    if (fd_unique[i] == 1 && fd_duplicate(fd_domain[i] + fd_min[i]))
	fd_domain[i]++;
    // carry
    if (fd_domain[i] > fd_len[i]) {
	fd_domain[i] = UNBOUND;
	if (fd_unique[i] == 1)
	    fd_pop();
	if (i == 0)
	    return (NO);	//all incremented
	i--;
	while (i >= 0) {
	    fd_domain[i]++;
		// if unique variable and duplicate then skip
	    if (fd_unique[i] == 1
		&& fd_duplicate(fd_domain[i] + fd_min[i]))
		fd_domain[i]++;
		// already incremented
	    if (fd_domain[i] > fd_len[i]) {
		if (i == 0)	
		    return (NO);
		fd_domain[i] = UNBOUND;
		// if unique variable remove duplicate data
		if (fd_unique[i] == 1)
		    fd_pop();
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

int prune_domain()
{
    int i;

    i = fd_var_idx;
    // increment
    fd_domain[i]++;
	// if unique variable and duplicate then skip
    if (fd_unique[i] == 1 && fd_duplicate(fd_domain[i] + fd_min[i]))
	fd_domain[i]++;
    // carry
    if (fd_domain[i] > fd_len[i]) {
	fd_domain[i] = UNBOUND;
	// if unique variable remove duplicate data
	if (fd_unique[i] == 1)
	    fd_pop();
	i--;
	while (i >= 0) {
	    fd_domain[i]++;
		// if unique variable and duplicate then skip
	    if (fd_unique[i] == 1
		&& fd_duplicate(fd_domain[i] + fd_min[i]))
		fd_domain[i]++;
		// already incremented
	    if (fd_domain[i] > fd_len[i]) {
		if (i == 0)	
		    return (NO);
		fd_domain[i] = UNBOUND;
		// if unique variable remove duplicate data
		if (fd_unique[i] == 1)
		    fd_pop();
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
	if (fd_domain[idx] == UNBOUND && flag == 0) {
	    fd_analyze_sw = 1;
	    return (fd_min[idx]);
	} else if (fd_domain[idx] == UNBOUND && flag == 1) {
	    fd_analyze_sw = 1;
	    return (fd_max[idx]);
	} else
	    return (fd_domain[idx] + fd_min[idx]);
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
	var = variable_convert1(car(varlist));
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
    if (!(greaterp(car(right), cadr(left))
	  || greaterp(car(left), cadr(right))))
	return (1);
    else
	return (0);
}

int fd_satisfiable(int expr)
{
    int left, right;

    if (expr == NIL)
	return (YES);

    left = fd_analyze(cadr(expr));
    right = fd_analyze(caddr(expr));
    //print(left);print(right);printf("\n");
    if (fd_eq(expr)) {		//#=
	if (length(left) == 1 && length(right) == 1) {
	    if (eqlp(car(left), car(right)))	// value left ==value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (in_interval(right, left))	// value right is in_interval range left
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (in_interval(left, right))	// value left is in_interval range right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (overlap(left, right))	// range left and range right has overlap
		return (YES);
	    else
		return (NO);
	}
    } else if (fd_neq(expr)) {	//#\=
	if (length(left) == 1 && length(right) == 1) {
	    if (!eqlp(car(left), car(right)))	// value left != value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (!in_interval(right, left))	// value right is not in_interval left range
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (!in_interval(left, right))	// value left is not in_interval right range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (!overlap(left, right))	// range left and range right has no overlap
		return (YES);
	    else
		return (NO);
	}
    } else if (fd_smaller(expr)) {	//#<
	if (length(left) == 1 && length(right) == 1) {
	    if (smallerp(car(left), car(right)))	// value left < value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (smallerp(cadr(left), car(right)))	//max of range < value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (smallerp(car(left), car(right)))	//min of range  < value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (smallerp(cadr(left), car(right)))	//max of range left < min of range right
		return (YES);
	    else
		return (NO);
	}
    } else if (fd_eqsmaller(expr)) {	//#<=
	if (length(left) == 1 && length(right) == 1) {
	    if (eqsmallerp(car(left), car(right)))	//value left < value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (eqsmallerp(cadr(left), car(right)))	//max of range <= value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (eqsmallerp(car(left), car(right)))	//min of range  <= value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (eqsmallerp(cadr(left), car(right)))	//max of range left <= min of range right
		return (YES);
	    else
		return (NO);
	}
    } else if (fd_greater(expr)) {	//#>
	if (length(left) == 1 && length(right) == 1) {
	    if (greaterp(car(left), car(right)))	// value left > value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (greaterp(car(left), car(right)))	//min of range > value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (greaterp(car(left), cadr(right)))	//value of max of range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (greaterp(car(left), cadr(right)))	//min of range left > max of range right
		return (YES);
	    else
		return (NO);
	}
    } else if (fd_eqgreater(expr)) {	//#>=
	if (length(left) == 1 && length(right) == 1) {
	    if (eqgreaterp(car(left), car(right)))
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (eqgreaterp(car(left), car(right)))	//min of range > value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (eqgreaterp(car(left), cadr(right)))	//value of max of range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (eqgreaterp(car(left), cadr(right)))	//min of range left > max of range right
		return (YES);
	    else
		return (NO);
	}
    }
    return (UNKNOWN);
}

int fd_propagate(int sets)
{
    int res;

    if (sets == NIL)
	return (YES);
    else {
	res = fd_satisfiable(car(sets));
	if (res == YES || res == UNKNOWN)
	    return (fd_propagate(cdr(sets)));
	else if (res == NO)
	    return (NO);
    }
    return (NO);
}

int fd_solve()
{
    int res;

  loop:
    if (fd_var_idx == fd_var_max - 1)
	return (YES);

    res = fd_propagate(fd_sets);
    if (res == YES) {
	res = next_domain();
	if (res == NO)
	    return (NO);
	goto loop;
    } else if (res == NO) {
	res = prune_domain();
	if (res == NO)
	    return (NO);
	goto loop;
    } else if (res == UNKNOWN) {
	res = next_domain();
	if (res == NO)
	    return (NO);
	goto loop;
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
	fd_var_idx = 0;
	res = fd_solve();

	if (res == NO)
	    return (NO);

      loop:
	unify(arg1, domain_to_value(revderef(arg1, th), th), th);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);

	unbind(save, th);
	res = next_domain();
	if (res == NO)
	    return (NO);

	res = fd_solve();
	if (res == YES)
	    goto loop;
	else
	    return (NO);
    }

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
