#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "npl.h"

void
defoperator(char *name, int (*func)(int, int, int), int weight, int spec,
	    int opt)
{
    int atom, old_weight, old_spec, new_weight, new_spec, ex_spec;

    if (opt == 0)
	atom = makeatom(name, OPE);
    else if (opt == 1)
	atom = makeatom(name, SYS);
    else
	atom = makeatom(name, USER);

    old_spec = GET_OPT(atom);
    if (old_spec == FX ||
	old_spec == FY ||
	old_spec == XFX ||
	old_spec == YFX || old_spec == XFY || old_spec == XF
	|| old_spec == YF)
	old_weight = GET_CDR(atom);
    else if (spec == FX || spec == FY || spec == XF || spec == YF)
	old_weight = get_1st_weight(atom);
    else
	old_weight = get_2nd_weight(atom);

    if (old_spec == NIL) {
	if (func != NIL)
	    SET_SUBR(atom, func);

	SET_CDR(atom, weight);
	SET_OPT(atom, spec);
	weight = makeint(weight);
	spec = makespec(spec);
	op_list = listcons(list3(weight, spec, atom), op_list);
	return;
    } else {
	new_weight = 0;
	new_spec = NIL;
	if (old_spec == XFX) {
	    if (spec == FX) {
		new_spec = FX_XFX;
		new_weight = weight * 10000 + old_weight;
	    } else if (spec == FY) {
		new_spec = FY_XFX;
		new_weight = weight * 10000 + old_weight;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == YFX) {
	    if (spec == FX) {
		new_spec = FX_YFX;
		new_weight = weight * 10000 + old_weight;
	    } else if (spec == FY) {
		new_spec = FY_YFX;
		new_weight = weight * 10000 + old_weight;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == XFY) {
	    if (spec == FX) {
		new_spec = FX_XFY;
		new_weight = weight * 10000 + old_weight;
	    } else if (spec == FY) {
		new_spec = FY_XFY;
		new_weight = weight * 10000 + old_weight;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == XF) {
	    if (spec == FX) {
		new_weight = weight * 10000 + old_weight;
		new_spec = FX_XF;
	    } else if (spec == FY) {
		new_weight = weight * 10000 + old_weight;
		new_spec = FY_XF;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == YF) {
	    if (spec == FX) {
		new_weight = weight * 10000 + old_weight;
		new_spec = FX_YF;
	    } else if (spec == FY) {
		new_weight = weight * 10000 + old_weight;
		new_spec = FY_YF;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == FX) {
	    if (spec == XFX) {
		new_weight = old_weight * 10000 + weight;
		new_spec = FX_XFX;
	    } else if (spec == YFX) {
		new_weight = old_weight * 10000 + weight;
		new_spec = FX_YFX;
	    } else if (spec == XFY) {
		new_weight = old_weight * 10000 + weight;
		new_spec = FX_XFY;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == FY) {
	    if (spec == XFX) {
		new_weight = old_weight * 10000 + weight;
		new_spec = FY_XFX;
	    } else if (spec == YFX) {
		new_weight = old_weight * 10000 + weight;
		new_spec = FY_YFX;
	    } else if (spec == XFY) {
		new_weight = old_weight * 10000 + weight;
		new_spec = FY_XFY;
	    } else {
		new_spec = spec;
		new_weight = weight;
	    }
	} else if (old_spec == FX_XFX) {
	    if (spec == FX) {
		new_spec = FX_XFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_XFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FX_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FX_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FX_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FX_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FX_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FX_YFX) {
	    if (spec == FX) {
		new_spec = FX_YFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_YFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FX_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FX_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FX_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FX_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FX_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FX_XFY) {
	    if (spec == FX) {
		new_spec = FX_XFY;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_XFY;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FX_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FX_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FX_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FX_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FX_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FY_XFX) {
	    if (spec == FX) {
		new_spec = FX_XFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_XFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FY_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FY_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FY_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FY_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FY_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FY_YFX) {
	    if (spec == FX) {
		new_spec = FX_YFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_YFX;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FY_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FY_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FY_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FY_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FY_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FY_XFY) {
	    if (spec == FX) {
		new_spec = FX_XFY;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_XFY;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FY_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FY_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FY_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FY_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FY_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FX_XF) {
	    if (spec == FX) {
		new_spec = FX_XF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_XF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FX_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FX_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FX_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FX_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FX_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FX_YF) {
	    if (spec == FX) {
		new_spec = FX_YF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_YF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FX_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FX_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FX_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FX_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FX_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FY_XF) {
	    if (spec == FX) {
		new_spec = FX_XF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_XF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FY_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FY_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FY_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FY_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FX_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	} else if (old_spec == FY_YF) {
	    if (spec == FX) {
		new_spec = FX_YF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == FY) {
		new_spec = FY_YF;
		new_weight = weight * 10000 + old_weight % 10000;
	    } else if (spec == XFX) {
		new_spec = FY_XFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YFX) {
		new_spec = FY_YFX;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XFY) {
		new_spec = FY_XFY;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == XF) {
		new_spec = FY_XF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    } else if (spec == YF) {
		new_spec = FY_YF;
		new_weight = (old_weight / 10000) * 10000 + weight;
	    }
	}

	if (func != NIL)
	    SET_SUBR(atom, func);
	SET_CDR(atom, new_weight);
	SET_OPT(atom, new_spec);

	ex_spec = makeexspec(old_spec, spec);
	weight = makeint(weight);
	spec = makespec(spec);
	op_list = listremove3(NIL, ex_spec, atom, op_list);
	op_list = cons(list3(weight, spec, atom), op_list);
	return;
    }
}

int op_arity(int x)
{
    switch (x) {
    case FX:
    case FY:
    case XF:
    case YF:
    case FX_XF:
    case FX_YF:
    case FY_XF:
    case FY_YF:
	return (cons(makeint(1), NIL));

    case XFX:
    case XFY:
    case YFX:
	return (cons(makeint(2), NIL));

    case FY_XFX:
    case FX_XFY:
    case FX_YFX:
    case FY_YFX:
	return (cons(makeint(2), cons(makeint(1), NIL)));
    }
    return (NIL);
}


void definfix(char *name, int (*func)(int, int, int), int weight, int spec)
{
    int atom, arity;

    atom = makeatom(name, SYS);
    arity = op_arity(spec);
    SET_SUBR(atom, func);
    SET_CDR(atom, weight);
    SET_OPT(atom, spec);
    weight = makeint(weight);
    spec = makespec(spec);
    op_list = cons(list3(weight, spec, atom), op_list);
    while (!nullp(arity)) {
	builtins = cons(list3(SLASH, atom, car(arity)), builtins);
	arity = cdr(arity);
    }
    return;
}

void defbuiltin(char *name, int (*func)(int, int, int), int arity)
{
    int atom;

    atom = makeatom(name, SYS);
    SET_SUBR(atom, func);
    if (structurep(arity) && length(arity) >= 2)
	while (!nullp(arity)) {
	    builtins =
		cons(list3(SLASH, atom, makeint(car(arity))), builtins);
	    arity = cdr(arity);
    } else
	builtins = cons(list3(SLASH, atom, makeint(arity)), builtins);
    return;
}

void defcompiled(char *name, int (*func)(int, int, int), int arity)
{
    int atom;

    atom = makeatom(name, COMP);
    SET_SUBR(atom, func);

    if (arity > 2 && structurep(arity))
	while (!nullp(arity)) {
	    builtins =
		cons(list3(SLASH, atom, makeint(car(arity))), builtins);
	    arity = cdr(arity);
    } else if (arity != -1)
	builtins = cons(list3(SLASH, atom, makeint(arity)), builtins);
    return;
}

void definfixcomp(char *name, int (*func)(int, int, int), int weight,
		  int spec)
{
    int atom;

    atom = makeatom(name, COMP);
    SET_SUBR(atom, func);
    SET_CDR(atom, weight);
    SET_OPT(atom, spec);
    weight = makeint(weight);
    spec = makespec(spec);
    op_list = cons(list3(weight, spec, atom), op_list);
    return;
}


void init_operator(void)
{
    defoperator(":-", o_define, 1200, XFX, 0);
    defoperator(":-", o_define, 1200, FX, 0);
    defoperator("-->", o_dcg, 1200, XFX, 0);
    defoperator("?-", o_ignore, 1200, FX, 0);
    defoperator(",", o_ignore, 1000, XFY, 0);
    defoperator(";", o_ignore, 1100, XFY, 0);
    defoperator(":", o_ignore, 50, XFX, 0);
    defoperator(".", o_cons, 50, FX, 0);
    defoperator("+", f_plus, 500, YFX, 0);
    defoperator("+", f_plus, 200, FY, 0);
    defoperator("-", f_minus, 500, YFX, 0);
    defoperator("-", f_minus, 200, FY, 0);
    defoperator("*", f_mult, 400, YFX, 0);
    defoperator("^", f_expt, 200, XFY, 0);
    defoperator("**", f_expt, 200, XFY, 0);
    defoperator("/", f_divide, 400, YFX, 0);
    defoperator("//", f_div, 400, YFX, 0);
    defoperator("mod", f_mod, 400, YFX, 0);
    defoperator("<<", f_leftshift, 400, YFX, 0);
    defoperator(">>", f_rightshift, 400, YFX, 0);
    defoperator("/\\", f_logicaland, 500, YFX, 0);
    defoperator("\\/", f_logicalor, 500, YFX, 0);
    defoperator("\\", f_complement, 200, FY, 0);
    return;
}



//function
int eval(int x, int th)
{
    int function, arg1, arg2;
    int result[3];

    if (nullp(x))
	return (NIL);
    else if (integerp(x))
	return (x);
    else if (floatp(x))
	return (x);
    else if (longnump(x))
	return (x);
    else if (bignump(x))
	return (x);
    else if (variablep(x)) {
	int res;
	res = deref(x, th);
	if (wide_variable_p(res))
	    exception(INSTANTATION_ERR, eval_context, x, th);
	return (res);
    } else if (!structurep(x)) {
	if (eqp(x, makefunc("pi")))
	    return (makeflt(3.14159265358979323846));
	else if (eqlp(x, makefunc("random")))
	    return (f_random(NIL, th));
	else
	    exception(NOT_NUM, eval_context, x, th);
    } else if (eqlp(car(x), makeatom("abs", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_abs(arg1, th));
    } else if (eqlp(car(x), makeatom("sin", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_sin(arg1, th));
    } else if (eqlp(car(x), makeatom("asin", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_asin(arg1, th));
    } else if (eqlp(car(x), makeatom("cos", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_cos(arg1, th));
    } else if (eqlp(car(x), makeatom("acos", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_acos(arg1, th));
    } else if (eqlp(car(x), makeatom("tan", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_tan(arg1, th));
    } else if (eqlp(car(x), makeatom("atan", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_atan(arg1, th));
    } else if (eqlp(car(x), makeatom("exp", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_exp(arg1, th));
    } else if (eqlp(car(x), makeatom("ln", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_ln(arg1, th));
    } else if (eqlp(car(x), makeatom("log", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_log(arg1, th));
    } else if (eqlp(car(x), makeatom("sqrt", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_sqrt(arg1, th));
    } else if (eqlp(car(x), makeatom("round", FUNC))) {
	if (length(x) != 3)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	arg2 = result[2];
	return (f_round(arg1, arg2, th));
    } else if (eqlp(car(x), makeatom("integer", SYS))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_integer(arg1, th));
    } else if (eqlp(car(x), makeatom("float", SYS))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_float(arg1, th));
    } else if (eqlp(car(x), makeatom("randi", FUNC))) {
	if (length(x) != 2)
	    exception(NOT_FUNCTION, eval_context, x, th);
	evalterm(x, result, th);
	arg1 = result[1];
	return (f_randi(arg1, th));
    } else if (structurep(x) && operatorp(car(x))) {
	evalterm(x, result, th);
	function = result[0];
	arg1 = result[1];
	arg2 = result[2];
	return ((GET_SUBR(function)) (arg1, arg2, th));
    }
    exception(NOT_FUNCTION, eval_context, x, th);
    return (NIL);
}

void evalterm(int x, int result[3], int th)
{

    result[0] = car(x);
    result[1] = eval(deref(cadr(x), th), th);
    result[2] = eval(deref(caddr(x), th), th);
    return;
}


int f_plus(int x, int y, int th)
{
    if (nullp(y))
	y = makeint(0);
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    return (plus(x, y, th));
}

int f_minus(int x, int y, int th)
{
    if (nullp(y)) {
	y = x;
	x = makeint(0);
    }
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (!nullp(y))
	return (minus(x, y, th));
    else
	return (mult(x, makeint(-1), th));
}

int f_mult(int x, int y, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    return (mult(x, y, th));
}

int f_divide(int x, int y, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (zerop(y))
	exception(DIV_ZERO, eval_context, NIL, th);
    return (exact_to_inexact(divide(x, y, th)));
}

int f_div(int x, int y, int th)
{
    int q;

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (zerop(y))
	exception(DIV_ZERO, eval_context, NIL, th);

    q = quotient(x, y, th);
    return (q);
}

int f_mod(int x, int y, int th)
{
    int res;

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (y == makeint(0))
	exception(DIV_ZERO, eval_context, y, th);
    if (!wide_integer_p(x))
	exception(NOT_INT, eval_context, x, th);
    if (!wide_integer_p(y))
	exception(NOT_INT, eval_context, y, th);

    if ((positivep(x) && positivep(y)) || (negativep(x) && negativep(y)))
	res = s_remainder(x, y, th);
    else if ((positivep(x) && negativep(y)))
	res = plus(y, s_remainder(x, y, th), th);
    else if (negativep(x) && positivep(y))
	res = mult(makeint(-1), plus(y, s_remainder(x, y, th), th), th);
    else
	res = s_remainder(x, y, th);
    return (res);
}

int f_expt(int x, int y, int th)
{
    double dx, dy, dz;

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (negativep(x) && !wide_integer_p(y))
	exception(EVALUATION_ERR, eval_context, y, th);
    if (floatp(x) && GET_FLT(x) >= DBL_MAX)
	exception(EVALUATION_ERR, eval_context, x, th);
    if (floatp(x) && (fabs(GET_FLT(x)) <= DBL_MIN && GET_FLT(x) != 0))
	exception(EVALUATION_ERR, eval_context, x, th);
    if (bignump(x) && (longnump(y) || bignump(y)))
	exception(RESOURCE_ERR, eval_context, y, th);

    if ((integerp(x) || longnump(x) || bignump(x)) && integerp(y)
	&& GET_INT(y) == 0)
	return (makeint(1));

    if ((integerp(x) || longnump(x) || bignump(x))
	&& (integerp(y) && GET_INT(y) > 0))
	return (expt(x, GET_INT(y), th));

    if ((integerp(x) || floatp(x)) && (integerp(y) || floatp(y))) {

	x = exact_to_inexact(x);
	y = exact_to_inexact(y);
	dx = GET_FLT(x);
	dy = GET_FLT(y);
	dz = pow(dx, dy);
	return (makeflt(dz));
    }
    if (integerp(x) && (integerp(y) || longnump(y) || bignump(y))) {
	if (GET_INT(x) == 1)
	    return (x);
	else if (GET_INT(x) == 0)
	    return (x);
	else if (GET_INT(x) == -1) {
	    if (zerop(s_remainder(y, makeint(2), th)))
		return (makeint(1));
	    else
		return (x);
	}
    }
    if (floatp(x) && (longnump(y) || bignump(y))) {
	if (GET_FLT(x) == 1.0)
	    return (x);
	else if (GET_FLT(x) == 0.0)
	    return (x);
	else if (GET_FLT(x) == -1.0) {
	    if (zerop(s_remainder(y, makeint(2), th)))
		return (makeflt(1.0));
	    else
		return (x);
	}
    }
    if (longnump(x) && integerp(y)) {
	if (GET_INT(y) == 1) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = dx;
	    return (makeflt(dy));
	} else if (GET_INT(y) == 2) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = dx * dx;
	    return (makeflt(dy));
	} else if (GET_INT(y) == -1) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = 1.0 / dx;
	    return (makeflt(dy));
	} else if (GET_INT(y) == -2) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = 1.0 / (dx * dx);
	    return (makeflt(dy));
	}
    }
    if (longnump(x) && floatp(y)) {
	if (GET_FLT(y) == 0.0) {
	    return (makeflt(1.0));
	} else if (GET_FLT(y) == 1.0) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = dx;
	    return (makeflt(dy));
	} else if (GET_FLT(y) == 2.0) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = dx * dx;
	    return (makeflt(dy));
	} else if (GET_FLT(y) == -1.0) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = 1.0 / dx;
	    return (makeflt(dy));
	} else if (GET_FLT(y) == -2.0) {
	    dx = GET_FLT(exact_to_inexact(x));
	    dy = 1.0 / (dx * dx);
	    return (makeflt(dy));
	}
    }
    return (UNDEF);
}

//x is cell address, y is integer of C
int expt(int x, int y, int th)
{
    int res, p;

    res = makeint(1);
    p = x;
    while (y > 0) {
	if ((y % 2) == 0) {
	    p = mult(p, p, th);
	    y = y / 2;
	} else {
	    res = mult(res, p, th);
	    y = y - 1;
	}
    }
    return (res);
}

int f_sqrt(int x, int th)
{
    double dx;

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (!numberp(x))
	exception(NOT_NUM, eval_context, x, th);


    dx = sqrt(GET_FLT(exact_to_inexact(x)));
    if (ceil(dx) == floor(dx) && dx < BIGNUM_BASE)
	return (makeint((int) dx));
    else
	return (makeflt(dx));
}

int f_round(int x, int y, int th)
{
    double dx;
    int n, i;

    if (wide_variable_p(x)) {
	exception(INSTANTATION_ERR, eval_context, x, th);
    }
    if (!numberp(x)) {
	exception(NOT_NUM, eval_context, x, th);
    }
    if (!integerp(y)) {
	exception(NOT_INT, eval_context, y, th);
    }

    if (floatp(x)) {
	dx = GET_FLT(x);
	n = GET_INT(y);

	for (i = 0; i < n; i++) {
	    dx = dx * 10;
	}
	dx = floor(dx);
	for (i = 0; i < n; i++) {
	    dx = dx / 10;
	}
	return (makeflt(dx));
    } else
	return (x);
}

int f_leftshift(int x, int y, int th)
{

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (!integerp(x))
	exception(NOT_INT, eval_context, x, th);
    if (!integerp(y))
	exception(NOT_INT, eval_context, y, th);

    x = GET_INT(x);
    y = GET_INT(y);
    return (makeint(x << y));
}

int f_rightshift(int x, int y, int th)
{

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (!integerp(x))
	exception(NOT_INT, eval_context, x, th);
    if (!integerp(y))
	exception(NOT_INT, eval_context, y, th);

    x = GET_INT(x);
    y = GET_INT(y);
    return (makeint(x >> y));
}

int f_logicaland(int x, int y, int th)
{

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (!integerp(x))
	exception(NOT_INT, eval_context, x, th);
    if (!integerp(y))
	exception(NOT_INT, eval_context, y, th);

    x = GET_INT(x);
    y = GET_INT(y);
    return (makeint(x & y));
}

int f_logicalor(int x, int y, int th)
{

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (wide_variable_p(y))
	exception(INSTANTATION_ERR, eval_context, y, th);
    if (!integerp(x))
	exception(NOT_INT, eval_context, x, th);
    if (!integerp(y))
	exception(NOT_INT, eval_context, y, th);

    x = GET_INT(x);
    y = GET_INT(y);
    return (makeint(x | y));
}

int f_complement(int x, int y, int th)
{

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, eval_context, x, th);
    if (!integerp(x))
	exception(NOT_INT, eval_context, x, th);

    x = GET_INT(x);
    return (makeint(~x));
}

/* The following function ensures that each argument is a number in eval when executed
* in the interpreter. However, the function is also called when tail recursion optimization 
* is applied by the compiler. In that case, eval is not involved, so the check must be
*  performed dynamically. This is why exception is included.
*/

int f_abs(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("abs", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("abs", 1, th), x, th);

    return (absolute(x, th));
}


int f_sin(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("sin", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("sin", 1, th), x, th);

    return (makeflt(sin(GET_FLT(exact_to_inexact(x)))));
}

int f_asin(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("asin", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("asin", 1, th), x, th);

    return (makeflt(asin(GET_FLT(exact_to_inexact(x)))));
}

int f_cos(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("cos", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("cos", 1, th), x, th);

    return (makeflt(cos(GET_FLT(exact_to_inexact(x)))));
}

int f_acos(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("asoc", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("acos", 1, th), x, th);

    return (makeflt(acos(GET_FLT(exact_to_inexact(x)))));
}

int f_tan(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("tan", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("tan", 1, th), x, th);

    return (makeflt(tan(GET_FLT(exact_to_inexact(x)))));
}

int f_atan(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("atan", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("atan", 1, th), x, th);

    return (makeflt(atan(GET_FLT(exact_to_inexact(x)))));
}

int f_exp(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("exp", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("exp", 1, th), x, th);

    return (makeflt(exp(GET_FLT(exact_to_inexact(x)))));
}

int f_ln(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("ln", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("ln", 1, th), x, th);
    if (zerop(x) || negativep(x))
	exception(FLOAT_OVERF, makeind("ln", 1, th), x, th);

    return (makeflt(log(GET_FLT(exact_to_inexact(x)))));
}


int f_log(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("log", 1, th), x, th);
    if (!numberp(x))
	exception(NOT_NUM, makeind("log", 1, th), x, th);
    if (zerop(x) || negativep(x))
	exception(FLOAT_OVERF, makeind("log", 1, th), x, th);

    return (makeflt(log10(GET_FLT(exact_to_inexact(x)))));
}


int f_integer(int x, int th)
{
    double flt;

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("integer", 1, th), x, th);
    if (!numberp(x)) {
	exception(NOT_NUM, makeind("integer", 1, th), x, th);
    }


    if (floatp(x)) {
	flt = GET_FLT(x);
	if (flt < 999999999 && flt > -999999999)
	    return (makeint((int) flt));
	else if (flt < 999999999999999999 && flt > -999999999999999999)
	    return (makelong((long) flt));
	else {
	    return (ERROBJ);
	}
    }

    return (x);
}

int f_float(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("float", 1, th), x, th);
    if (!numberp(x)) {
	exception(NOT_NUM, makeind("float", 1, th), x, th);
    }

    if (integerp(x))
	return (makeflt((double) GET_INT(x)));
    else
	return (x);
}


int f_randi(int x, int th)
{
    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makeind("randi", 1, th), x, th);
    if (!integerp(x))
	exception(NOT_INT, makeind("randi", 1, th), x, th);

    x = GET_INT(x);
    return (makeint(rand() & x));
}

int f_random(int x, int th)
{
    double d;

    if (!nullp(x))
	exception(WRONG_ARGS, makeind("random", 1, th), x, th);

    d = (double) rand() / RAND_MAX;
    return (makeflt(d));
}
