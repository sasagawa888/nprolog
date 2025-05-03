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

int variable_index(int var)
{
    int total,idx,vars;

    total = length(constraint_var);
    idx = 0;
    vars = constraint_var;
    while(vars != NIL){
        if(eqlp(var,car(vars)))
            return(total-idx);

        vars = cdr(vars);
    }

    return(-1);
}

#define FD_IDX 0
#define FD_START 1
#define FD_END 2
#define FD_LEN 3
#define FD_UNIQUE 4

int b_constraint_var(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, var, start, end;

    n = length(arglist);
    ind = makeind("constraint_var", n, th);
    if (n == 2) {
	arg1 = car(arglist);
    arg2 = cadr(arglist);

    var = variable_convert1(arg1);
    start = GET_INT(cadr(arg2));
    end = GET_INT(caddr(arg2));
    constraint_domain[constraint_var_idx][FD_START] = start;
    constraint_domain[constraint_var_idx][FD_END] = end;
    constraint_domain[constraint_var_idx][FD_LEN] = end-start;
    constraint_var = cons(var,constraint_var);
    constraint_var_idx++;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_constraint_vars(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2,elt, var,start,end;

    n = length(arglist);
    ind = makeind("constraint_vars", n, th);
    if (n == 2) {
	arg1 = car(arglist);
    arg2 = cadr(arglist);

    while(arg1 != NIL){
    elt = car(arg1);
    var = variable_convert1(elt);
    start = GET_INT(cadr(arg2));
    end = GET_INT(caddr(arg2));
    constraint_domain[constraint_var_idx][FD_START] = start;
    constraint_domain[constraint_var_idx][FD_END] = end;
    constraint_domain[constraint_var_idx][FD_LEN] = end-start;
    constraint_var = cons(var,constraint_var);
    constraint_var_idx++;
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
    while(arg1 != NIL){
        idx = variable_index(car(arg1));
        constraint_domain[idx][FD_UNIQUE] = 1;
        arg1 = cdr(arg1);
    }
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


/* この処理においてall_differentのことを考慮して生成*/
int next_domain(int domain)
{   

    if(domain == NIL){
        return(list1(makeint(1)));
    }
    else {
        return (1);
    }
    return(0);
}


/* e.g. 1+Y+Z#=3 -> Y+Z#=2*/
int new_expr(int expr)
{
    return (1);
}

/* e.g. X+Y+Z#=3 X<-1 1+Y+Z#=3*/
int bind_variable(int expr, int domain)
{
    return (1);
}


int domain_to_value(int domain, int varlist)
{
    return(1);
}

int saticfiablep(int expr, int domain)
{
    if(expr == NIL) // 制約式がなければ充足可能
        return (1);
    else{

    }
    return(0);
}

int propagate_all(int set, int domain)
{
    if (set == NIL)
	return (domain); /*制約式がなくなればdomainが求まっている*/
    else {
	if (propagate(car(set), domain) != NO) /*制約式があるなら先頭で制約計算*/
	    propagate_all(cdr(set), domain);
	else
	    return (NO);
    }

    return (NO);
}

int propagate(int expr, int domain)
{
    
    domain = next_domain(domain);
    domain = bind_variable(expr, domain);
    if (saticfiablep(expr, domain) == YES) {
	domain = next_domain(domain);
	return (propagate(new_expr(expr), domain));
    } else if (bind_variable(expr, next_domain(domain)) == YES) {
	domain = next_domain(domain);
	bind_variable(expr, domain);
	if (saticfiablep(expr, domain) == YES)
	    return (propagate(new_expr(expr), domain));
    } else
	return (NO);

    return (NO);
}

int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1, domain, save;

    n = length(arglist);
    ind = makeind("label", n, th);
    save = sp[th];
    if (n == 1) {
	arg1 = car(arglist);
    
    constraint_set = reverse(constraint_set);
    domain = propagate_all(constraint_set,NIL);
    loop:
    unify(arg1,domain_to_value(domain,arg1),th);
    if (prove_all(rest,sp[th],th) == YES)
        return(YES);

    unbind(save,th);
    domain = propagate_all(constraint_set,next_domain(domain));
    if(nullp(domain)){
        return(NO);
    }
    else {
        goto loop;
    }
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
