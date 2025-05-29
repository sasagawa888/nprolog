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
	fd_sets = listcons(variable_convert1(arg1), fd_sets);
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
	if (unify(arg1, reverse(fd_sets), th) == YES)
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
	SET_VAR(var, 1);
	fd_vars = cons(var, fd_vars);
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
	    SET_VAR(var, 1);
	    fd_vars = cons(var, fd_vars);
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
    fd_sel_idx++;
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

int fd_removed_p(int idx, int x){
	int i;

	for (i = 0; i < fd_rem_idx[idx]; i++) {
	if (fd_removed[idx][i] == x)
	    return(1);
    }

	return(0);
}

int increment(int idx)
{
    if (fd_unique[idx] == 0) {
	fd_domain[idx]++;
    } else {
	while (1) {
	    if (fd_duplicate(fd_domain[idx] + fd_min[idx]))
		fd_domain[idx]++;
		else if(fd_removed_p(idx,fd_domain[idx]))
		fd_domain[idx]++;
	    else
		break;
	}
    }
    return (NO);
}


int next_domain()
{
    int i;


    if (fd_domain[0] > fd_len[0])
	return (COMPLETE);	// all incremented

    i = 0;
    // find unbind var index
    while (i < fd_var_max) {
	if (fd_domain[i] == UNBOUND) {
	    increment(i);
	    fd_var_idx = i;
	    if (fd_unique[i] == 1)
		fd_push(fd_domain[i] + fd_min[i]);
	    return (YES);
	}
	i++;
    }
    i = fd_var_max - 1;
    // increment
    increment(i);
    // carry
    if (fd_domain[i] > fd_len[i]) {
	fd_domain[i] = UNBOUND;
	if (fd_unique[i] == 1)
	    fd_pop();
	if (i == 0)
	    return (NO);	//all incremented
	i--;
	while (i >= 0) {
	    increment(i);
	    // already incremented
	    if (fd_domain[i] > fd_len[i]) {
		if (i == 0)
		    return (COMPLETE);
		fd_domain[i] = UNBOUND;
		if (fd_unique[i] == 1)
		    fd_pop();
		i--;
		fd_var_idx = i;
	    } else {
		fd_var_idx = i;
		if (fd_unique[i] == 1) {
		    fd_pop();
		    fd_push(fd_domain[i] + fd_min[i]);
		}
		return (YES);
	    }
	}
    } else {
	if (fd_unique[i] == 1) {
	    fd_pop();
	    fd_push(fd_domain[i] + fd_min[i]);
	}
	return (YES);
    }
    return (NO);
}

int prune_domain()
{
    int i;

    if (fd_domain[0] > fd_len[0])
	return (COMPLETE);	// all incremented

    i = fd_var_idx;
    // increment
    increment(i);
    // carry
    if (fd_domain[i] > fd_len[i]) {
	fd_domain[i] = UNBOUND;
	if (fd_unique[i] == 1)
	    fd_pop();
	i--;
	while (i >= 0) {
	    increment(i);
	    // already incremented
	    if (fd_domain[i] > fd_len[i]) {
		if (i == 0)
		    return (COMPLETE);
		fd_domain[i] = UNBOUND;
		if (fd_unique[i] == 1)
		    fd_pop();
		// if unique variable remove duplicate data
		i--;
		fd_var_idx = i;
	    } else {
		fd_var_idx = i;
		if (fd_unique[i] == 1) {
		    fd_pop();
		    fd_push(fd_domain[i] + fd_min[i]);
		}
		return (YES);
	    }
	}

    } else {
	if (fd_unique[i] == 1) {
	    fd_pop();
	    fd_push(fd_domain[i] + fd_min[i]);
	}
	return (YES);
    }
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

int fd_div(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("//")))
	return (1);
    else
	return (0);
}

int fd_mod(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("mod")))
	return (1);
    else
	return (0);
}

int fd_expt(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("**")))
	return (1);
    else if (structurep(x) && eqlp(car(x), makeconst("^")))
	return (1);
    else
	return (0);
}

int fd_compute_expt(int x, int y)
{
    int res = 1;
    int base = x;

    while (y > 0) {
	if (y % 2 == 1) {
	    res *= base;
	}
	base *= base;
	y /= 2;
    }
    return (res);
}

void unbind_free_var()
{
    int i;

    for (i = 0; i < fd_var_free; i++) {
	fd_domain[i + fd_var_max] = UNBOUND;
	fd_min[i + fd_var_max] = -999999999;
	fd_max[i + fd_var_max] = 999999999;
    }
}

int free_variablep(int x)
{

    if (compiler_variable_p(x) && GET_VAR(x) == 2)
	return (1);
    else
	return (0);
}

int out_of_max(int left, int right)
{
    if (left >= 999999999 || right >= 999999999)
	return (1);
    else
	return (0);
}

int out_of_min(int left, int right)
{
    if (left <= -999999999 || right <= -999999999)
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
	// new free variable
	if (GET_VAR(form) == 0) {
	    idx = fd_var_max + fd_var_free;
	    SET_ARITY(form, idx);
	    SET_VAR(form, 2);
	    fd_vars = cons(form, fd_vars);
	    fd_min[idx] = -999999999;
	    fd_max[idx] = 999999999;
	    fd_var_free++;
	}

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
	if (out_of_min(left, right))
	    return (-999999999);
	else if (out_of_max(left, right))
	    return (999999999);
	else
	    return (left + right);
    } else if (fd_minus(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	if (out_of_min(left, right))
	    return (-999999999);
	else if (out_of_max(left, right))
	    return (999999999);
	else
	    return (left - right);
    } else if (fd_mult(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	if (out_of_min(left, right))
	    return (-999999999);
	else if (out_of_max(left, right))
	    return (999999999);
	else
	    return (left * right);
    } else if (fd_div(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	return (left / right);
    } else if (fd_mod(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	return (left % right);
    } else if (fd_expt(form)) {
	left = fd_analyze1(cadr(form), flag);
	right = fd_analyze1(caddr(form), flag);
	return (fd_compute_expt(left, right));
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
    if (!fd_analyze_sw)
	return (wlist1(res1, 0));
    else {
	res2 = fd_analyze1(form, 1);
	return (wlist2(res1, res2, 0));
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
    if (car(range) <= car(value)
	&& (cadr(range) >= car(value)))
	return (1);
    else
	return (0);
}

int overlap(int left, int right)
{
    if (!(car(right) > cadr(left))
	|| ((car(left) > cadr(right))))
	return (1);
    else
	return (0);
}

int fd_satisfiable(int expr)
{
    int left, right;

    if (expr == NIL)
	return (YES);

    proof[0]++;
    left = fd_analyze(cadr(expr));
    right = fd_analyze(caddr(expr));
    //print(expr);print(left);print(right);printf("\n");
    if (fd_eq(expr)) {		//#=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) == car(right))	// value left ==value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (free_variablep(cadr(expr))) {
		fd_domain[GET_ARITY(cadr(expr))] = car(right);
		fd_min[GET_ARITY(cadr(expr))] = 0;
		return (YES);
	    } else if (in_interval(right, left))	// value right is in_interval range left
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (in_interval(left, right))	// value left is in_interval range right
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (overlap(left, right))	// range left and range right has overlap
		return (YES);
	    else
		return (UNKNOWN);
	}
    } else if (fd_neq(expr)) {	//#\=
	if (length(left) == 1 && length(right) == 1) {
	    if (!(car(left) == car(right)))	// value left != value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (!in_interval(right, left))	// value right is not in_interval left range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (!in_interval(left, right))	// value left is not in_interval right range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (!overlap(left, right))	// range left and range right has no overlap
		return (YES);
	    else
		return (UNKNOWN);
	}
    } else if (fd_smaller(expr)) {	//#<
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) < car(right))	// value left < value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (cadr(left) < car(right))	//max of range < value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) < car(right))	//min of range  < value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (cadr(left) < car(right))	//max of range left < min of range right
		return (YES);
	    else
		return (UNKNOWN);
	}
    } else if (fd_eqsmaller(expr)) {	//#<=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) <= car(right))	//value left < value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (cadr(left) <= car(right))	//max of range <= value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) <= car(right))	//min of range  <= value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (cadr(left) <= car(right))	//max of range left <= min of range right
		return (YES);
	    else
		return (UNKNOWN);
	}
    } else if (fd_greater(expr)) {	//#>
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) > car(right))	// value left > value right
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (car(left) > car(right))	//min of range > value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) > cadr(right))	//value of max of range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (car(left) > cadr(right))	//min of range left > max of range right
		return (YES);
	    else
		return (UNKNOWN);
	}
    } else if (fd_eqgreater(expr)) {	//#>=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) >= car(right))
		return (YES);
	    else
		return (NO);
	} else if (length(left) == 2 && length(right) == 1) {
	    if (car(left) >= car(right))	//min of range > value
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) >= cadr(right))	//value of max of range
		return (YES);
	    else
		return (UNKNOWN);
	} else if (length(left) == 2 && length(right) == 2) {
	    if (car(left) >= cadr(right))	//min of range left > max of range right
		return (YES);
	    else
		return (UNKNOWN);
	}
    }
    return (UNKNOWN);
}

int fd_generate(int sets)
{
    int res;

    if (sets == NIL)
	return (YES);
    else {
	res = fd_satisfiable(car(sets));
	if (res == YES || res == UNKNOWN)
	    return (fd_generate(cdr(sets)));
	else if (res == NO)
	    return (NO);
    }
    return (NO);
}

int fd_solve()
{
    int res, res1;

  loop:

    // constraint generate&test
    res = fd_generate(fd_sets);
    if (res == YES) {
	// if all variables are bounded, then success
	if (fd_domain[0] != UNBOUND && fd_var_idx == fd_var_max - 1)
	    return (YES);

	// if there are unbound variable, then next domain
	res1 = next_domain();
	// if domain is all selected, then end return complete
	if (res1 == COMPLETE)
	    return (COMPLETE);
	goto loop;
    } else if (res == NO) {
	unbind_free_var();
	// if constraint set is not satistificate, then prune and go on
	res1 = prune_domain();
	// if domain is all selected, then end return complete
	if (res1 == COMPLETE)
	    return (COMPLETE);
	goto loop;
    } else if (res == UNKNOWN) {
	// if there is possibility, then go on solving 
	res1 = next_domain();
	// if domain is all selected, then end return complete
	if (res1 == COMPLETE)
	    return (COMPLETE);
	goto loop;
    }

    return (NO);
}


/*
*  AC-3 
*/

// each element [var1,var2,expr]
void fd_enqueue(int x)
{
    fd_queue[fd_enque_idx] = x;
    fd_enque_idx++;
}

int fd_dequeue()
{
    int res;

    res = fd_queue[fd_deque_idx];
    fd_deque_idx++;
    return (res);
}


void fd_enqueue_affected_arcs(int idx)
{
    int i, arc;

    for (i = 0; i < fd_deque_idx; i++) {
	arc = fd_queue[i];
	if (GET_ARITY(car(arc)) == idx)
	    fd_enqueue(arc);
    }
}

void fd_add_removed(int idx, int x)
{
    int i;

    // if already removed return
    for (i = 0; i < fd_rem_idx[idx]; i++) {
	if (fd_removed[idx][i] == x)
	    return;
    }

    fd_removed[idx][fd_rem_idx[idx]] = x;
    fd_rem_idx[idx]++;

    // for retest consistency for removed variable, enqueue arcs 
    fd_enqueue_affected_arcs(idx);

	fd_rem_sw = 1;
	if(fd_trace){
		 printf("remove val=%d\n",fd_min[idx] + fd_domain[idx]);
	}

}

int fd_find_variables(int expr)
{
    if (compiler_variable_p(expr))
	return (wlist1(expr, 0));
    else if (structurep(expr))
	return (append(fd_find_variables(cadr(expr)),
		       (fd_find_variables(caddr(expr)))));
    else
	return (NIL);
}

int pair_with(int x, int lst)
{
    if (nullp(lst))
	return (NIL);
    else
	return (wcons(wlist2(x, car(lst), 0), pair_with(x, cdr(lst)), 0));
}

int comb_two1(int head, int tail)
{
    if (nullp(head))
	return (NIL);
    else
	return (append(pair_with(car(head), tail),
		       comb_two1(cdr(head), cdr(tail))));
}


// combination of 2 elements. [a,b,c] -> [[a,b],[a,c],[b.c]]
int comb_two(int lst)
{
    return (comb_two1(lst, cdr(lst)));
}

void fd_enqueue_arc(int expr)
{
    int vars, pairs, pair, arc;

    vars = fd_find_variables(expr);
    pairs = comb_two(vars);

    while (!nullp(pairs)) {
	pair = car(pairs);
	arc = wlist3(car(pair), cadr(pair), expr, 0);
	fd_enqueue(arc);
	arc = wlist3(cadr(pair), car(pair), expr, 0);
	fd_enqueue(arc);
	pairs = cdr(pairs);
    }

}

void fd_consistent1(int expr, int idx1, int idx2, int flag);
void fd_check_removed(int expr, int idx1, int idx2)
{
    int i;

    for (i = 0; i < fd_rem_idx[idx2]; i++) {
	fd_domain[idx2] = fd_removed[idx2][i];
	fd_consistent1(expr, idx1, idx2, 1);
	fd_domain[idx2] = UNBOUND;
    }
}


void fd_consistent1(int expr, int idx1, int idx2, int flag)
{
    int left, right;

    left = fd_analyze(cadr(expr));
    right = fd_analyze(caddr(expr));

    if (fd_eq(expr)) {		//#=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) == car(right)) {	
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (free_variablep(cadr(expr))) {
		return;
	    } else if (in_interval(right, left)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (in_interval(left, right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
	    return;

	}
    } else if (fd_neq(expr)) {	//#\=
	if (length(left) == 1 && length(right) == 1) {
	    if (!(car(left) == car(right))) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		fd_add_removed(idx1, fd_domain[idx1]);
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    return;
	} else if (length(left) == 1 && length(right) == 2) {
		return;
	} else if (length(left) == 2 && length(right) == 2) {
	    return;
	}
    } else if (fd_smaller(expr)) {	//#<
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) < car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
		return;
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) < cadr(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
	    return;
	}
    } else if (fd_eqsmaller(expr)) {	//#<=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) <= car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    return;
	} else if (length(left) == 1 && length(right) == 2) {
	    return;
	} else if (length(left) == 2 && length(right) == 2) {
	    return;
	}
    } else if (fd_greater(expr)) {	//#>
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) > car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (cadr(left) > car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left)  < car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
	    return;
	}
    } else if (fd_eqgreater(expr)) {	//#>=
	if (length(left) == 1 && length(right) == 1) {
	    if (car(left) >= car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 1) {
	    if (car(left) >= car(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 1 && length(right) == 2) {
	    if (car(left) >= cadr(right)) {
		if (flag == 1) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    } else {
		if (flag == 0) {
		    fd_add_removed(idx1, fd_domain[idx1]);
		}
		return;
	    }
	} else if (length(left) == 2 && length(right) == 2) {
	    return;
	}
    }
    return;

}

void fd_consistent(int c)
{
    int var1, var2, expr, idx1, idx2, len, i;

    if(fd_trace){
		 print(c); printf("\n");
	}
    var1 = car(c);
    var2 = cadr(c);
    expr = caddr(c);
    idx1 = GET_ARITY(var1);
    idx2 = GET_ARITY(var2);
    len = fd_len[idx1];
    for (i = 0; i <= len; i++) {
	fd_domain[idx1] = i;
	fd_rem_sw = 0;
	fd_consistent1(expr, idx1, idx2, 0);
    }
    fd_domain[idx1] = UNBOUND;
}

int fd_empty()
{
    if (fd_deque_idx == fd_enque_idx)
	return (1);
    else
	return (0);
}


void fd_propagate()
{
    int arc;
    while (!fd_empty()) {
	arc = fd_dequeue();
	fd_consistent(arc);
    }
}


int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save1, save2, save3, res, sets;

    n = length(arglist);
    ind = makeind("label", n, th);
    save1 = wp[th];
    save2 = sp[th];
    save3 = ac[th];
    if (n == 1) {
	arg1 = car(arglist);

	label:
	fd_sets = reverse(fd_sets);

	/* AC-3 */
	sets = fd_sets;
	while (!nullp(sets)) {
	    fd_enqueue_arc(car(sets));
	    sets = cdr(sets);
	}
	while (!fd_empty()) {
	    int arc;
	    arc = fd_dequeue();
	    fd_consistent(arc);
	}
	fd_trace = 0;

	/* generate and test */
	fd_var_idx = 0;
	res = fd_solve();

	if (res == NO || res == COMPLETE)
	    return (NO);

      loop:
	unify(arg1, domain_to_value(revderef(arg1, th), th), th);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);

	wp[th] = save1;
	unbind(save2, th);
	ac[th] = save3;
	res = next_domain();
	if (res == NO)
	    return (NO);
	if (res == COMPLETE)
	    return (YES);

	res = fd_solve();

	if (res == COMPLETE)
	    return (YES);
	else if (res == YES)
	    goto loop;
	else if (res == NO)
	    return (NO);
    }
	else if(n == 2){
		arg1 = car(arglist);
		arg2 = cadr(arglist);
		if(!eqlp(arg2,makeconst("trace")))
		exception(SYSTEM_ERR, ind, arg2,th);

		fd_trace = 1;
		goto label;
	}

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

