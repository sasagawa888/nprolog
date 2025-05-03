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
	fd_sets =
	    listcons(copy_heap(variable_convert1(arg1)), fd_sets);
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
    int n, ind, arg1, arg2, var, idx, min, max;

    n = length(arglist);
    ind = makeind("constraint_var", n, th);
    if (n == 2) {
	arg1 = car(arglist);
    arg2 = cadr(arglist);

    var = variable_convert1(arg1);
    idx = GET_ARITY(var);
    min = GET_INT(cadr(arg2));
    max = GET_INT(caddr(arg2));
    fd_min[idx] = min;
    fd_len[idx] = max-min;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_constraint_vars(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2,elt, var,idx,min,max;

    n = length(arglist);
    ind = makeind("constraint_vars", n, th);
    if (n == 2) {
	arg1 = car(arglist);
    arg2 = cadr(arglist);

    while(arg1 != NIL){
    elt = car(arg1);
    var = variable_convert1(elt);
    idx = GET_ARITY(var);
    min = GET_INT(cadr(arg2));
    max = GET_INT(caddr(arg2));
    fd_min[idx] = min;
    fd_len[idx] = max-min;
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
        idx = GET_ARITY(car(arg1));
        fd_unique[idx] = 1;
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




int inc_domain()
{   
    int i;

    i = 0;
    // fine unbind var index
    while(i < fd_var_max){
        if(fd_domain[i] == -1){
            fd_domain[i] = 0;
            fd_var_idx = i;
            return(YES);
        }
    }
    i = fd_var_max - 1;
    // increment
    while(i>=0){
        fd_domain[i]++;
        // carry
        if(fd_domain[i] >= fd_len[i]){
            fd_domain[i] = -1;
            i--;
        } else
            return(YES);
    }
    // already incremented
    return(NO);
}

int next_domain()
{
    return(inc_domain());
}

int prune_domain()
{
    return(1);
}

/* e.g. 1+Y+Z#=3 -> Y+Z#=2*/
int new_expr(int expr)
{
    return (1);
}

/* e.g. X+Y+Z#=3 X<-1 1+Y+Z#=3*/
int bind_variable(int expr)
{
    return (1);
}


int domain_to_value(int varlist)
{
    return(1);
}

int saticfiablep(int expr)
{
    if(expr == NIL) 
        return (1);
    else{

    }
    return(0);
}

int propagate_all(int sets)
{
    if (sets == NIL)
	return (YES);
    else {
	if (propagate(car(sets)) != NO) 
	    return(propagate_all(cdr(sets)));
	else
	    return (NO);
    }

    return (NO);
}

int propagate(int expr)
{
    int res;

    res = next_domain();
    if(res == NO)
        return(NO);
    bind_variable(expr);
    if (saticfiablep(expr) == YES) {
	res = next_domain();
    if(res == 0)
        return(NO);

	return (propagate(new_expr(expr)));
    } else {
	res = prune_domain();
    if(res == NO)
        return(NO);
    
    bind_variable(expr);
	if (saticfiablep(expr) == YES)
	    return (propagate(new_expr(expr)));
    }

    return (NO);
}

int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1, save,res;

    n = length(arglist);
    ind = makeind("label", n, th);
    save = sp[th];
    if (n == 1) {
	arg1 = car(arglist);
    
    fd_sets = reverse(fd_sets);
    propagate_all(fd_sets);
    loop:
    unify(arg1,domain_to_value(arg1),th);
    if (prove_all(rest,sp[th],th) == YES)
        return(YES);

    unbind(save,th);
    res = next_domain();
    if(res == NO)
        return(NO);
    
    propagate_all(fd_sets);
    goto loop;
    }
    
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
