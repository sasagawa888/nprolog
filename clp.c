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

int iota(int min, int max)
{
    int i, j, res;

    i = GET_INT(min);
    j = GET_INT(max);
    res = NIL;

    while (j >= i) {
	res = listcons(makeint(j), res);
	j--;
    }
    return (res);
}


int b_constraint_var(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2,var,range;

    n = length(arglist);
    ind = makeind("constraint_var", n, th);
    if (n == 2) {
	arg1 = car(arglist);
    arg2 = cadr(arglist);

    var = variable_convert1(arg1);
    range = iota(GET_INT(cadr(arg2)),GET_INT(caddr(arg2)));
    SET_CDR(var,range);
    constraint_var = cons(var,constraint_var);

	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_all_different(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("all_different", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	constraint_unique = copy_heap(variable_convert1(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int each_car(int x)
{
    if (nullp(x))
	return (NIL);
    else
	return (listcons(caar(x), each_car(cdr(x))));
}

int each_cdr(int x)
{
    if (nullp(x))
	return (NIL);
    else
	return (listcons(cdar(x), each_cdr(cdr(x))));
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

int fd_in(int x)
{
    if (structurep(x) && eqlp(car(x), makeconst("in")))
	return (1);
    else
	return (0);
}


int fd_var(int x)
{
    if (compiler_variable_p(x))
	return (1);
    else
	return (0);
}

int fd_form(int x)
{
    if (structurep(x))
	return (1);
    else
	return (0);
}


int fd_index(int var)
{
    int i, vars;

    i = 1;
    vars = constraint_var;
    while (vars != NIL) {
	if (eqlp(var, car(vars)))
	    return (i);

	i++;
	vars = cdr(vars);
    }
    return (0);
}

int fd_get_domain(int var)
{
    int index = fd_index(var);
    if (index == 0)
	exception(SYSTEM_ERR, makeind("constraint_propergate", 0, 0), NIL,
		  0);

    return (nth(constraint_domain, index));
}

void fd_set_domain(int var, int val)
{
    int vars, domain, new;

    vars = constraint_var;
    domain = constraint_domain;
    new = NIL;
    while (vars != NIL) {
	if (eqlp(var, car(vars)))
	    new = listcons(val, new);
	else
	    new = listcons(car(domain), new);

	vars = cdr(vars);
	domain = cdr(domain);
    }
    constraint_domain = reverse(new);
}

int fd_min(int x, int y)
{
    if (x < y)
	return (x);
    else
	return (y);
}

int fd_max(int x, int y)
{
    if (x > y)
	return (x);
    else
	return (y);
}

int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("label", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

/* make initial index [1] */
int init_index(int env)
{
    return (list1(makeint(1)));
}

int new_index(int index)
{
    return (1);
}

int new_expr(int expr)
{
    return (1);
}

int bind_variable(int expr, int env, int index)
{
    return (1);
}

int saticfiablep(int expr, int env)
{
    return (1);
}

int propagate_all(int set, int env, int domain)
{
    if (set == NIL)
	return (domain);
    else {
	if (propagate(car(set), env, init_index(env)) == YES)
	    //e.g. init_index(env) = [1] 
	    propagate_all(cdr(set), env, domain);
	else
	    return (NO);
    }

    return (NO);
}

int propagate(int expr, int env, int domain)
{
    if (expr == NIL)
	return (domain);

    domain = bind_variable(expr, env, domain);
    if (saticfiablep(expr, env) == YES) {
	domain = new_index(domain);
	return (propagate(new_expr(expr), env, domain));
    } else if (bind_variable(expr, env, new_index(domain)) == YES) {
	domain = new_index(domain);
	bind_variable(expr, env, domain);
	if (saticfiablep(expr, env) == YES)
	    return (propagate(new_expr(expr), env, domain));
    } else
	return (NO);

    return (NO);
}
