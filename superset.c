/*
*     superset builtin predicates 
*/
#include "npl.h"

int b_select(int arglist, int rest, int th)
{
    int arg1, arg2, arg3, varYs, varY, varZs, varX, varXs, n, body, save1,
	save2;
    save2 = sp[th];
    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (!wide_variable_p(arg1) && !atomicp(arg1))
	    error(WRONG_ARGS, "select ", arg1, th);
	if (!listp(arg2) && !nullp(arg2))
	    error(NOT_LIST, "select ", arg2, th);
	if (listp(arg2) && length(arg2 == -1))
	    error(WRONG_ARGS, "select ", arg2, th);
	if (!wide_variable_p(arg3) && !atomicp(arg3))
	    error(WRONG_ARGS, "select ", arg3, th);

	varX = makevariant(th);
	varXs = makevariant(th);
	save1 = get_wp(th);
	if (unify_var(varX, arg1, th) == YES
	    && unify(wlistcons(varX, varXs, th), arg2, th) == YES
	    && unify_var(varXs, arg3, th) == YES)
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);
	unbind(save2, th);
	wp[th] = save1;
	varX = makevariant(th);
	varYs = makevariant(th);
	varY = makevariant(th);
	varZs = makevariant(th);
	save1 = wp[th];
	if (unify_var(varX, arg1, th) == YES
	    && unify(wlistcons(varY, varYs, th), arg2, th) == YES
	    && unify(wlistcons(varY, varZs, th), arg3, th) == YES) {
	    body =
		wcons(makesys("select"),
		      wcons(varX, wcons(varYs, wcons(varZs, NIL, th), th),
			    th), th);
	    if (prove_all(addtail_body(rest, body, th), sp[th], th) == YES)
		return (YES);
	    unbind(save2, th);
	    set_wp(save1, th);
	}
	return (NO);
    }
    error(ARITY_ERR, "select ", arglist, th);
    return (NO);
}


int b_succ(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "succ ", arglist, th);
	if (!wide_integer_p(arg1) && !wide_variable_p(arg1))
	    error(WRONG_ARGS, "succ ", arglist, th);
	if (!wide_integer_p(arg2) && !wide_variable_p(arg2))
	    error(WRONG_ARGS, "succ ", arglist, th);
	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "succ ", arglist, th);
	if (negativep(arg1) || negativep(arg2))
	    error(LESS_THAN_ZERO, "succ", arglist, th);

	if (wide_integer_p(arg1)) {
	    if (unify(arg2, plus(arg1, makeint(1), th), th) == YES) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
		else
		    return (NO);
	    }
	} else if (wide_integer_p(arg2)) {
	    if (unify(arg1, minus(arg2, makeint(1), th), th) == YES) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
		else
		    return (NO);
	    }
	}
    }
    error(ARITY_ERR, "succ ", arglist, th);
    return (NO);
}


int b_maplist(int arglist, int rest, int th)
{
    int arg1, arg2, varE, varEs, varP, n, pred, arg, body, save1, save2;
    save2 = sp[th];
    pred = NIL;
    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!structurep(arg1) && !atomp(arg1))
	    error(WRONG_ARGS, "maplist ", arg1, th);
	if (!listp(arg2) && !nullp(arg2))
	    error(NOT_LIST, "maplist ", arg2, th);
	if (listp(arg2) && length(arg2) == -1)
	    error(WRONG_ARGS, "maplist ", arg2, th);

	varP = makevariant(th);
	save1 = wp[th];
	if (unify_var(varP, arg1, th) == YES && unify_nil(arg2, th) == YES)
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);
	unbind(save2, th);
	wp[th] = save1;
	varP = makevariant(th);
	varE = makevariant(th);
	varEs = makevariant(th);
	save1 = wp[th];
	if (unify_var(varP, arg1, th) == YES
	    && unify(wlistcons(varE, varEs, th), arg2, th) == YES)
	    pred = deref(varP, th);
	arg = deref(varE, th);
	if (structurep(pred))
	    pred = wappend(pred, wlist1(arg, th), th);
	else
	    pred = wlist2(pred, arg, th);
	pred = list_to_structure(pred);
	if (prove_all(pred, sp[th], th) == NO) {
	    unbind(save2, th);
	    wp[th] = save1;
	    return (NO);
	}
	body =
	    wcons(makesys("maplist"),
		  wcons(varP, wcons(varEs, NIL, th), th), th);
	if (prove_all(addtail_body(rest, body, th), sp[th], th) == YES)
	    return (YES);
	unbind(save2, th);
	wp[th] = save1;
	return (NO);
    }
    error(ARITY_ERR, "maplist", arglist, th);
    return (NO);
}

int b_once(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "once ", arg1, th);
	if (!callablep(arg1))
	    error(NOT_CALLABLE, "once ", arg1, th);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "once ", arg1, th);
	if (atom_constant_p(arg1))
	    arg1 = makeatom(GET_NAME(arg1), PRED);

	if(prove_all(arg1,sp[th],th) == YES)
	return (prove_all(rest, sp[th], th));
	else 
	return(NO);
    }
    error(ARITY_ERR, "call ", arglist, th);
    return (NO);
}
