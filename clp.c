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
	arg1 = revderef(car(arglist),th);
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
        return(NIL);
    else 
        return(listcons(caar(x),each_car(cdr(x))));
}

int each_cdr(int x)
{
    if (nullp(x))
        return(NIL);
    else 
        return(listcons(cdar(x),each_cdr(cdr(x))));
}


int fd_eq(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("#=")))
        return(1);
    else 
        return(0);
}

int fd_neq(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("#\\=")))
        return(1);
    else 
        return(0);
}

int fd_greater(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("#>")))
        return(1);
    else 
        return(0);
}

int fd_eqgreater(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("#>=")))
        return(1);
    else 
        return(0);
}

int fd_smaller(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("#<")))
        return(1);
    else 
        return(0);
}

int fd_eqsmaller(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("#<=")))
        return(1);
    else 
        return(0);
}

int fd_in(int x)
{
    if(structurep(x) && eqlp(car(x),makeconst("in")))
        return(1);
    else 
        return(0);
}


int fd_var(int x)
{
    if(compiler_variable_p(x))
        return(1);
    else 
        return(0);
}

int fd_form(int x)
{
    if (structurep(x))
        return(1);
    else 
        return(0);
}

int iota(int min, int max)
{
    int i,j,res;

    i = GET_INT(min);
    j = GET_INT(max);
    res = NIL;

    while(j>=i){
        res = listcons(makeint(j),res);
        j--;
    }
    return(res);
}

int fd_index(int var){
    int i,vars;

    i = 1;
    vars = constraint_var;
    while(vars != NIL){
        if(eqlp(var,car(vars)))
            return(i);

        i++;
        vars = cdr(vars);
    }
    return(0);
}

int fd_get_domain(int var)
{
    int index = fd_index(var);
    if(index == 0)
        exception(SYSTEM_ERR,makeind("constraint_propergate",0,0),NIL,0);
    
    return(nth(constraint_domain,index));
}

void fd_set_domain(int var,int val)
{
    int vars,domain,new;

    vars = constraint_var;
    domain = constraint_domain;
    new = NIL;
    while(vars != NIL){
        if(eqlp(var,car(vars)))
            new = listcons(val,new);
        else 
            new = listcons(car(domain),new);

    vars = cdr(vars);
    domain = cdr(domain);
    }
    constraint_domain = reverse(new);
}

int fd_min(int x, int y)
{
    if(x < y)
        return(x);
    else
        return(y);
}

int fd_max(int x, int y)
{
    if(x > y)
        return(x);
    else
        return(y);
}

int constraint_propagate()
{
    int expr,var,min,max,left,right,domain;

    constraint_set = reverse(constraint_set);
    constraint_var = NIL;
    constraint_domain = NIL;

    while (constraint_set != NIL) {
        expr = car(constraint_set);
        if (fd_eq(expr)) {
            left = cadr(expr);
            right = caddr(expr);
            // e.g. X #= Y
            if(fd_var(left) && fd_var(right)){ 
                min = fd_max(car(fd_get_domain(left)),car(fd_get_domain(right)));
                max = fd_min(last(fd_get_domain(left)),last(fd_get_domain(right)));
                domain = iota(min,max);
                fd_set_domain(left,domain);
                fd_set_domain(right,domain); 
            }
        } else if (fd_in(expr)) {
            // e.g. X in 1..3 
            var = cadr(expr);
            min = cadr(caddr(expr));
            max = caddr(caddr(expr));
            constraint_var = cons(var,constraint_var);
            constraint_env = cons(iota(min,max),constraint_env);
        }
        constraint_set = cdr(constraint_set);
    }
    return(YES);
}

void constraint_search(int expr, int var, int env) {
    // Try all candidates, like Lisp’s dolist
    // Save valid values to domain
    // Merge into existing domains
}

int b_label(int arglist, int rest, int th)
{
    int n, ind, arg1,compvar,result,save1,save2,save3;

    n = length(arglist);
    ind = makeind("label", n, th);
    if (n == 1) {
	arg1 = car(arglist);
       
    constraint_propagate();
    compvar = variable_convert1(revderef(arg1,th));
    result = NIL;
    while(!nullp(compvar)){
        result = cons(fd_get_domain(car(compvar)),result);
        compvar = cdr(compvar);
    }
    save1 = wp[th];
	save2 = sp[th];
	save3 = ac[th];
    while(car(result) != NIL){
        unify(arg1,each_car(result),th);
            if (prove_all(rest, sp[th], th) == YES)
                return(YES);

        wp[th] = save1;
        unbind(save2, th);
        ac[th] = save3;
        result = each_cdr(result);
    }
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
