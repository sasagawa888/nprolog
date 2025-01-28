/*
*     superset builtin predicates 
*/
#include <string.h>
#include <stdlib.h>
#include "npl.h"

int b_atom_concat(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, atom;
    char str1[STRSIZE];

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "atom_concat ", arg1, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    error(NOT_ATOM, "atom_concat ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "atom_concat ", arg3, th);
	if (strlen(GET_NAME(arg1)) + strlen(GET_NAME(arg2)) > STRSIZE)
	    error(RESOURCE_ERR, "atom_concat ", arglist, th);

	strcpy(str1, GET_NAME(arg1));
	strcat(str1, GET_NAME(arg2));
	atom = makeconst(str1);

	if (unify(arg3, atom, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);

    }
    error(ARITY_ERR, "atom_concat ", arglist, th);
    return (NO);
}


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
	return(NO);
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

	if (prove_all(arg1, sp[th], th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "once ", arglist, th);
    return (NO);
}


int b_compound(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (compoundp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "compound ", arglist, th);
    return (NO);
}

int b_ground(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (groundp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "ground ", arglist, th);
    return (NO);
}

int b_member(int arglist, int rest, int th)
{
    int n, arg1, arg2, x, y, l, save1, save2, body, res;

    save2 = sp[th];
    res = NIL;
    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);


	if (nullp(arg2))
	    return (NO);

	save1 = wp[th];
	x = makevariant(th);
	l = makevariant(th);
	if (unify(arg1, x, th) == YES
	    && unify(arg2, wlistcons(x, l, th), th) == YES) {
	    if ((res = prove(NIL, sp[th], rest, th)) == YES)
		return (YES);
	}

	wp[th] = save1;
	unbind(save2, th);
	if (res == NFALSE)
	    return (res);

	save1 = wp[th];
	x = makevariant(th);
	y = makevariant(th);
	l = makevariant(th);
	if (unify(arg1, x, th) == YES
	    && unify(arg2, wlistcons(y, l, th), th) == YES) {
	    body = wlist3(makeatom("member", SYS), x, l, th);
	    if ((res = prove(body, sp[th], rest, th)) == YES)
		return (YES);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (res);
    }
    error(ARITY_ERR, "member ", arglist, th);
    return (NO);
}

//---------extention--------

int b_append(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, x, ls, ys, zs, save1, save2, body;

    save2 = sp[th];
    body = NIL;
    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!listp(arg1) && !nullp(arg1) && !wide_variable_p(arg1))
	    error(NOT_LIST, "append ", arg1, th);
	if (!listp(arg2) && !nullp(arg2) && !wide_variable_p(arg2))
	    error(NOT_LIST, "append ", arg2, th);
	if (!listp(arg3) && !nullp(arg3) && !wide_variable_p(arg3))
	    error(NOT_LIST, "append ", arg3, th);

	save1 = wp[th];
	if (unify(arg1, NIL, th) == YES && unify(arg2, arg3, th) == YES) {
	    if (prove(NIL, sp[th], rest, th) == YES)
		return (YES);
	}
	wp[th] = save1;
	unbind(save2, th);

	save1 = wp[th];
	x = makevariant(th);
	ls = makevariant(th);
	ys = makevariant(th);
	zs = makevariant(th);
	if (unify(arg1, wlistcons(x, ls, th), th) == YES &&
	    unify(arg2, ys, th) == YES
	    && unify(arg3, wlistcons(x, zs, th), th) == YES) {
	    body = wlist4(makeatom("append", SYS), ls, ys, zs, th);
	    if (prove(body, sp[th], rest, th) == YES)
		return (YES);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "append ", arglist, th);
    return (NO);
}

//listreverse/2
int b_reverse(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1) && !listp(arg1) && !nullp(arg1))
	    error(NOT_LIST, "reverse ", arg1, th);
	if (listp(arg1) && length(arg1) == -1)
	    error(WRONG_ARGS, "reverse ", arg1, th);
	if (!wide_variable_p(arg2) && !listp(arg2) && !nullp(arg2))
	    error(NOT_LIST, "reverse ", arg2, th);
	if (listp(arg2) && length(arg2) == -1)
	    error(WRONG_ARGS, "reverse ", arg2, th);

	if (!variablep(arg1)) {
	    if (unify(listreverse(arg1), arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (!variablep(arg2)) {
	    if (unify(arg1, listreverse(arg2), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "reverse ", arglist, th);
    return (NO);
}


int b_between(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, save3, low, high, betweenval;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);	//low
	arg2 = cadr(arglist);	//high
	arg3 = caddr(arglist);	//variable
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "between ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "between ", arg2, th);
	if (!wide_variable_p(arg1) && !integerp(arg1))
	    error(NOT_INT, "between ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "between ", arg2, th);
	if (!wide_variable_p(arg3) && !integerp(arg3))
	    error(NOT_INT, "between ", arg3, th);

	save1 = wp[th];
	save2 = sp[th];
	save3 = ac[th];
	low = get_int(arg1);
	high = get_int(arg2);

	if (groundp(arg3)) {
	    betweenval = get_int(arg3);
	    if (betweenval >= low && betweenval <= high) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
	    }
	    return (NO);
	}

	while (low <= high) {
	    //printf("%d",low);
	    unify(arg3, makeint(low), th);
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);

	    low++;
	    wp[th] = save1;
	    unbind(save2, th);
	    ac[th] = save3;
	}
	wp[th] = save1;
	unify(arg3, arg2, th);
	ac[th] = save3;
	return (NO);
    }
    error(ARITY_ERR, "between ", arglist, th);
    return (NO);
}


int b_bagof(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, free, vars, nonfree, goal, lis;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	save1 = wp[th];
	save2 = sp[th];
	vars = listreverse(unique(varslist(arg2)));
	free = get_free(arg2);
	nonfree = get_nonfree(vars, free, arg1);
	goal = get_goal(arg2);
	goal =
	    addtail_body(list2(makesys("%bagofhelper"), arg1), goal, th);
	bag_list = NIL;
	nonfree_list = nonfree;
	prove_all(goal, sp[th], th);

	lis = reverse(bag_list);
	while (!nullp(lis)) {
	    apply_unify(caar(lis));
	    unify(arg3, listreverse(cdar(lis)), th);
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);

	    wp[th] = save1;
	    unbind(save2, th);
	    lis = cdr(lis);
	}
	return (NO);
    }
    error(ARITY_ERR, "bagof ", arglist, th);
    return (NO);
}


int b_setof(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, free, vars, nonfree, goal, lis;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	save1 = wp[th];
	save2 = sp[th];
	vars = listreverse(unique(varslist(arg2)));
	free = get_free(arg2);
	nonfree = get_nonfree(vars, free, arg1);
	goal = get_goal(arg2);
	goal =
	    addtail_body(list2(makesys("%bagofhelper"), arg1), goal, th);
	bag_list = NIL;
	nonfree_list = nonfree;
	prove_all(goal, sp[th], th);

	lis = reverse(bag_list);
	while (!nullp(lis)) {
	    apply_unify(caar(lis));
	    unify(arg3, sort(remove_duplicate(cdar(lis))), th);
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);

	    wp[th] = save1;
	    unbind(save2, th);
	    lis = cdr(lis);
	}
	return (NO);
    }
    error(ARITY_ERR, "setof ", arglist, th);
    return (NO);
}

int b_findall(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, goal;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	save1 = wp[th];
	save2 = sp[th];
	goal = get_goal(arg2);
	goal =
	    addtail_body(list2(makesys("%bagofhelper"), arg1), goal, th);
	bag_list = NIL;
	nonfree_list = NIL;
	prove_all(goal, sp[th], th);

	unify(arg3, listreverse(cdar(bag_list)), th);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);

	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "findall ", arglist, th);
    return (NO);
}


/*
X^Y^foo(Z) == ^(X,^(Y,foo(Z)))  -> [X,Y]
*/
int get_free(int x)
{
    if (car(x) == makeope("^"))
	return (listcons(cadr(x), get_free(caddr(x))));
    else
	return (NIL);
}

/*
X^Y^foo(Z) == ^(X,^(Y,foo(Z)))  -> foo(Z)
*/
int get_goal(int x)
{
    if (car(x) == makeope("^"))
	return (get_goal(caddr(x)));
    else
	return (x);
}

/*
x = [A,B,C]  y = [C] -> [A,B]
*/
int get_nonfree(int x, int y, int z)
{
    if (nullp(x))
	return (NIL);
    else if (eqlp(car(x), z))
	return (get_nonfree(cdr(x), y, z));
    else if (memq(car(x), y))
	return (get_nonfree(cdr(x), y, z));
    else
	return (listcons(car(x), get_nonfree(cdr(x), y, z)));
}

/*
key = ((A.1)(B.2)) -> unify(A,1) unify(B,2)
*/
void apply_unify(int x)
{
    int lis;

    lis = x;
    while (!nullp(lis)) {
	unify(caar(lis), cdar(lis), 0);
	lis = cdr(lis);
    }
}

int b_bagofhelper(int arglist, int rest, int th)
{
    int n, arg1, nonfree, key;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);	//target var    

	nonfree = nonfree_list;
	key = NIL;
	while (!nullp(nonfree)) {
	    key = cons(cons(car(nonfree), deref(car(nonfree), th)), key);
	    nonfree = cdr(nonfree);
	}
	putinbag(key, deref(arg1, th));
	return (NO);
    }
    return (NO);
}


/*
bag data structure
((key1 . data1)(key2 . data2)...)
key = ((var1 . val1)(var2 . val2)...)
data = [a,b,a,d...]
*/
void putinbag(int key, int data)
{
    int lis;

    lis = bag_list;
    while (!nullp(lis)) {
	if (equalp(key, caar(lis))) {
	    SET_CDR(car(lis), listcons(data, cdar(lis)));
	    return;
	}
	lis = cdr(lis);
    }
    bag_list = cons(cons(key, listcons(data, NIL)), bag_list);
}

int takeoutbug(int key)
{
    int lis;

    lis = bag_list;
    while (!nullp(lis)) {
	if (equalp(key, caar(lis))) {
	    return (cdar(lis));
	}
	lis = cdr(lis);
    }
    return (NIL);
}


int b_atom_length(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);

    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!atomp(arg1))
	    error(NOT_ATOM, "atom_length ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "atom_length ", arg2, th);

	if (unify(arg2, makeint(atom_length(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "atom_length ", arglist, th);
    return (NO);
}


int b_get_code(int arglist, int rest, int th)
{
    int n, arg1, arg2, c, i, res;
    char str[10];

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get_code;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get_code:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "get_code ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "get_code ", arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "get_code ", arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = getc(GET_PORT(arg1));

	if (isUni2(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni3(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni4(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    str[4] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni5(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    str[5] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni6(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    str[5] = getc(GET_PORT(arg1));
	    str[6] = NUL;
	    i = utf8_to_ucs4(str);
	} else {
	    i = c;
	}

	res = NIL;

	res = unify(arg2, makeint(i), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "get_code ", arglist, th);
    return (NO);
}

int b_get_char(int arglist, int rest, int th)
{
    int n, arg1, arg2, c, res;
    char str[10];

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get_char;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get_char:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "get_char ", arg1, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    error(NOT_INT, "get_char ", arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "get_char ", arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = getc(GET_PORT(arg1));
	str[0] = c;

	if (isUni2(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = NUL;
	} else if (isUni3(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = NUL;
	} else if (isUni4(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    str[4] = NUL;
	} else if (isUni5(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    str[5] = NUL;
	} else if (isUni6(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    str[5] = getc(GET_PORT(arg1));
	    str[6] = NUL;
	} else {
		str[1] = NUL;
	}
	res = NIL;

	res = unify(arg2, makeconst(str), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "get_char ", arglist, th);
    return (NO);
}



int b_get_byte(int arglist, int rest, int th)
{
    int n, arg1, arg2, c, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get_byte;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get_byte:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "get_byte ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "get_byte ", arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "get_byte ", arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = fgetc(GET_PORT(arg1));

	res = unify(arg2, makeint(c), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "get_byte ", arglist, th);
    return (NO);
}

int b_put_char(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto put;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      put:
	if(wide_variable_p(arg1))
	error(INSTANTATION_ERR,"put_char ",arg1,th);
	if(wide_variable_p(arg2))
	error(INSTANTATION_ERR,"put_char ",arg2,th);
	if (!wide_variable_p(arg1) && !characterp(arg2))
	    error(NOT_CHAR, "put_char ", arg2, th);
	if(!streamp(arg1))
	error(NOT_STREAM,"put_char ", arg1,th);

	fprintf(GET_PORT(arg1), "%s", GET_NAME(arg2));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "put_char ", arglist, th);
    return (NO);
}

int b_peek_code(int arglist, int rest, int th)
{
    int n, arg1, arg2, c, i, res;
    char str[10];

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto peek_code;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      peek_code:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "peek_code ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "peek_code ", arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "peek_code ", arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = getc(GET_PORT(arg1));
	ungetc(c,GET_PORT(arg1));

	if (isUni2(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni3(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni4(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
		ungetc(str[3],GET_PORT(arg1));
	    str[4] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni5(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
		ungetc(str[3],GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
		ungetc(str[4],GET_PORT(arg1));
	    str[5] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni6(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
		ungetc(str[3],GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
		ungetc(str[4],GET_PORT(arg1));
	    str[5] = getc(GET_PORT(arg1));
		ungetc(str[5],GET_PORT(arg1));
	    str[6] = NUL;
	    i = utf8_to_ucs4(str);
	} else {
	    i = c;
	}

	res = NIL;

	res = unify(arg2, makeint(i), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "peek_code ", arglist, th);
    return (NO);
}

int b_peek_char(int arglist, int rest, int th)
{
    int n, arg1, arg2, c, res;
    char str[10];

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto peek_char;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      peek_char:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "peek_char ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "peek_char ", arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "peek_char ", arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);

	c = getc(GET_PORT(arg1));
	str[0] = c;
	ungetc(c,GET_PORT(arg1));

	if (isUni2(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = NUL;
	} else if (isUni3(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = NUL;
	} else if (isUni4(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
		ungetc(str[3],GET_PORT(arg1));
	    str[4] = NUL;
	} else if (isUni5(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
		ungetc(str[3],GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
		ungetc(str[4],GET_PORT(arg1));
	    str[5] = NUL;
	} else if (isUni6(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
		ungetc(str[1],GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
		ungetc(str[2],GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
		ungetc(str[3],GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
		ungetc(str[4],GET_PORT(arg1));
	    str[5] = getc(GET_PORT(arg1));
		ungetc(str[5],GET_PORT(arg1));
	    str[6] = NUL;
	} 
	res = NIL;

	res = unify(arg2, makeconst(str), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "peek_char ", arglist, th);
    return (NO);
}


int b_peek_byte(int arglist, int rest, int th)
{
    int n, arg1, arg2, c, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto peek_byte;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      peek_byte:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "peek_byte ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "peek_byte ", arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "peek_byte ", arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = fgetc(GET_PORT(arg1));
	ungetc(c,GET_PORT(arg1));

	res = unify(arg2, makeint(c), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "peek_byte ", arglist, th);
    return (NO);
}



int b_flush_output(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 0) {
	fflush(stdout);
	return (prove_all(rest, sp[th], th));
    } else if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "flush_output ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "flush_output ", arg1, th);
	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	if (GET_OPT(arg1) == OPL_INPUT)
	    error(NOT_OUTPUT_STREAM, "flush_output ", arg1, th);

	fflush(GET_PORT(arg1));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "flush_output ", arglist, th);
    return (NO);
}

int b_atom_codes(int arglist, int rest, int th)
{
    int n, arg1, arg2, ls, atom, pos, code, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
	    error(INSTANTATION_ERR, "atom_codes ", arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "atom_codes ", arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    error(NOT_LIST, "atom_codes ", arg2, th);


	if (singlep(arg1) && !variablep(arg1)) {
	    strcpy(str1, GET_NAME(arg1));
	    ls = NIL;
	    pos = 0;
	    while (str1[pos] != NUL) {
		if (str1[pos] == '\\') {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		} else if (isUni2(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = NUL;
		} else if (isUni3(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = NUL;
		} else if (isUni4(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = str1[pos++];
		    str2[4] = NUL;
		} else if (isUni5(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = str1[pos++];
		    str2[4] = str1[pos++];
		    str2[5] = NUL;
		} else if (isUni6(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = str1[pos++];
		    str2[4] = str1[pos++];
		    str2[5] = str1[pos++];
		    str2[6] = NUL;
		} else {	//ascii code
		    str2[0] = str1[pos++];
		    str2[1] = NUL;
		}
		if (str2[0] == '\\')
		    code = ctrl_to_number(str2[1]);
		else		//unicode
		    code = makeint(utf8_to_ucs4(str2));
		ls = cons(code, ls);
	    }
	    ls = listreverse(ls);
	    res = unify(arg2, ls, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg2)) {
	    ls = arg2;
	    str1[th] = NUL;
	    while (!nullp(ls)) {
		if (GET_INT(car(ls)) < ' ')
		    sprintf(str2, "\\x%x\\", GET_INT(car(ls)));
		else
		    ucs4_to_utf8(GET_INT(car(ls)), str2);
		strcat(str1, str2);
		ls = cdr(ls);
	    }
	    atom = makeconst(str1);
	    res = unify(arg1, atom, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "atom_codes ", arglist, th);
    return (NO);
}

int b_atom_chars(int arglist, int rest, int th)
{
    int n, arg1, arg2, ls, atom, pos, c, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
	    error(INSTANTATION_ERR, "atom_chars ", arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "atom_chars ", arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    error(NOT_LIST, "atom_chars ", arg2, th);


	if (singlep(arg1) && !variablep(arg1)) {
	    strcpy(str1, GET_NAME(arg1));
	    ls = NIL;
	    pos = 0;
	    while (str1[pos] != NUL) {
		if (str1[pos] == '\\') {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		} else if (isUni2(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = NUL;
		} else if (isUni3(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = NUL;
		} else if (isUni4(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = str1[pos++];
		    str2[4] = NUL;
		} else if (isUni5(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = str1[pos++];
		    str2[4] = str1[pos++];
		    str2[5] = NUL;
		} else if (isUni6(str1[pos])) {
		    str2[0] = str1[pos++];
		    str2[1] = str1[pos++];
		    str2[2] = str1[pos++];
		    str2[3] = str1[pos++];
		    str2[4] = str1[pos++];
		    str2[5] = str1[pos++];
		    str2[6] = NUL;
		} else {	//ascii code
		    str2[0] = str1[pos++];
		    str2[1] = NUL;
		}
		if (str2[0] == '\\')
		    c = ctrl_to_number(str2[1]);
		else		//unicode
		    c = makeconst(str2);
		ls = cons(c, ls);
	    }
	    ls = listreverse(ls);
	    res = unify(arg2, ls, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg2)) {
	    ls = arg2;
	    str1[th] = NUL;
	    while (!nullp(ls)) {
		strcat(str1, GET_NAME(car(ls)));
		ls = cdr(ls);
	    }
	    atom = makeconst(str1);
	    res = unify(arg1, atom, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "atom_chars ", arglist, th);
    return (NO);
}


int b_number_codes(int arglist, int rest, int th)
{
    int n, arg1, arg2, ls, num, pos, code, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!wide_variable_p(arg1) && !numberp(arg1))
	    error(NOT_ATOM, "atom_codes ", arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    error(NOT_LIST, "atom_codes ", arg2, th);
	

	if (!variablep(arg1)) {
	    if (integerp(arg1))
		sprintf(str1, "%d", GET_INT(arg1));
	    else if (longnump(arg1))
		sprintf(str1, "%lld", GET_LONG(arg1));
	    else if (floatp(arg1))
		sprintf(str1, "%g", GET_FLT(arg1));
	    ls = NIL;
	    pos = 0;
	    while (str1[pos] != NUL) {
		str2[0] = str1[pos++];
		str2[1] = NUL;
		code = makeint(utf8_to_ucs4(str2));
		ls = cons(code, ls);
	    }
	    ls = listreverse(ls);
	    res = unify(arg2, ls, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg2)) {
	    ls = arg2;
	    str1[th] = NUL;
	    while (!nullp(ls)) {
		if (GET_INT(car(ls)) < ' ')
		    sprintf(str2, "\\x%c\\", GET_INT(car(ls)));
		else
		    sprintf(str2, "%c", GET_INT(car(ls)));
		strcat(str1, str2);
		ls = cdr(ls);
	    }
	    strcat(str1, ".");
	    strcpy(bridge, str1);
	    read_string_term(0);	//initilize 
	    bridge_flag = 1;
	    num = readparse(th);
	    bridge_flag = 0;
	    res = unify(arg1, num, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "number_codes ", arglist, th);
    return (NO);
}

int b_number_chars(int arglist, int rest, int th)
{
    int n, arg1, arg2, ls, num, pos, c, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!wide_variable_p(arg1) && !numberp(arg1))
	    error(NOT_ATOM, "number_chars ", arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    error(NOT_LIST, "number_chars ", arg2, th);


	if (!variablep(arg1)) {
	    if (integerp(arg1))
		sprintf(str1, "%d", GET_INT(arg1));
	    else if (longnump(arg1))
		sprintf(str1, "%lld", GET_LONG(arg1));
	    else if (floatp(arg1))
		sprintf(str1, "%g", GET_FLT(arg1));
	    ls = NIL;
	    pos = 0;
	    while (str1[pos] != NUL) {
		str2[0] = str1[pos++];
		str2[1] = NUL;
		c = makeconst(str2);
		ls = cons(c, ls);
	    }
	    ls = listreverse(ls);
	    res = unify(arg2, ls, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg2)) {
	    ls = arg2;
	    str1[th] = NUL;
	    while (!nullp(ls)) {
		sprintf(str2, "%s", GET_NAME(car(ls)));
		if (!(str2[0] >= 43 && str2[0] <= 57))
		    error(WRONG_ARGS, "number_chars ", arg2, th);
		strcat(str1, str2);
		ls = cdr(ls);
	    }
	    strcat(str1, ".");
	    strcpy(bridge, str1);
	    read_string_term(0);	//initilize 
	    bridge_flag = 1;
	    num = readparse(th);
	    bridge_flag = 0;
	    res = unify(arg1, num, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "number_chars ", arglist, th);
    return (NO);
}


int b_catch(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, pt;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);


	catch_data[cp[th]][0][th] = arg2;
	catch_data[cp[th]][1][th] = sp[th];
	int ret = setjmp(catch_buf[cp[th]][th]);
	pt = cp[th];
	cp[th]++;
	if (cp[th] > THREADSIZE)
	    error(RESOURCE_ERR, "catch ", NIL, th);

	if (ret == 0) {
	    if (prove_all(arg1, sp[th], th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (ret == 1) {
	    sp[th] = catch_data[pt][1][th];
	    return (prove_all(arg3, sp[th], th));
	}
	return (NO);
    }
    error(ARITY_ERR, "catch ", arglist, th);
    return (NO);
}


int b_throw(int arglist, int rest, int th)
{
    int n, arg1, i;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	for (i = cp[th] - 1; i >= 0; i--) {
	    if (eqlp(catch_data[i][0][th], arg1))
		longjmp(catch_buf[i][th], 1);
	}
	error(WRONG_ARGS, "throw ", arg1, th);

    }
    error(ARITY_ERR, "throw ", arglist, th);
    return (NO);
}



int occursp(int x, int y)
{
    if (nullp(y))
	return (0);
    else if (variablep(x) && variablep(y) && eqlp(x, y))
	return (1);
    else if (atomicp(x))
	return (0);
    else if (structurep(y)) {
	if (occursp(x, car(y)) || occursp(x, cdr(y)))
	    return (1);
	else
	    return (0);
    } else
	return (0);
}

int b_unify_with_occurs_check(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (occursp(arg1, arg2))
	    return (NO);

	if (unify(arg1, arg2, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "unify_with_occurs_check ", arglist, th);
    return (NO);
}

int b_current_input(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!wide_variable_p(arg1) && !streamp(arg1))
	    error(NOT_STREAM, "current_input", arg1, th);

	if(unify(arg1,input_stream,th) == YES)
		return (prove_all(rest, sp[th], th));
	else 
		return(NO);
    }
    error(ARITY_ERR, "current_input ", arglist, th);
    return (NO);
}

int b_current_output(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!wide_variable_p(arg1) && !streamp(arg1))
	    error(NOT_STREAM, "current_output", arg1, th);

	if(unify(arg1,output_stream,th) == YES)
		return (prove_all(rest, sp[th], th));
	else 
		return(NO);
    }
    error(ARITY_ERR, "current_output ", arglist, th);
    return (NO);
}


int b_set_input(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!streamp(arg1))
	    error(NOT_STREAM, "set_input", arg1, th);

	input_stream = arg1;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "set_input ", arglist, th);
    return (NO);
}


int b_set_output(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!streamp(arg1))
	    error(NOT_STREAM, "set_output", arg1, th);

	output_stream = arg1;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "set_output ", arglist, th);
    return (NO);
}

int b_use_module(int arglist, int rest, int th)
{
    int n, arg1;
    char *home, str[STRSIZE];
    FILE *fp;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1))
	    error(NOT_ATOM, "use_module ", arg1, th);

	home = getenv("HOME");
	strcpy(str, home);
	strcat(str, "/nprolog/library/");
	strcat(str, GET_NAME(arg1));
	strcat(str, ".pl");
	fp = fopen(str, "r");
	if (fp != NULL) {
	    fclose(fp);
	    b_reconsult(list1(makeconst(str)), NIL, 0);
		return(prove_all(rest,sp[th],th));
	}
	error(CANT_OPEN, "use_module ", arglist, th);
    }
    error(ARITY_ERR, "use_module ", arglist, th);
    return (NO);
}

int b_module(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!atomp(arg1))
	    error(NOT_ATOM, "module ", arg1, th);
	if (!listp(arg2) && !nullp(arg2))
	    error(NOT_LIST, "module ", arg2, th);

	module_flag = 1;
	module_name = arg1;
	export_pt = 0;
	while (!nullp(arg2)) {
	    export_data[export_pt][0] = cadr(car(arg2));
	    export_data[export_pt][1] = GET_INT(caddr(car(arg2)));
	    arg2 = cdr(arg2);
	    export_pt++;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "module ", arglist, th);
    return (NO);
}

int b_copy_term(int arglist, int rest, int th)
{
	int n,arg1,arg2;

	n=length(arglist);
	if(n==2){
		arg1 = car(arglist);
		arg2 = cadr(arglist);

		if(unify(arg2,copy_term(arg1),th) == YES)
			return(prove_all(rest,sp[th],th));
		else
			return(NO);

	}
	error(ARITY_ERR,"copy_term ",arglist,th);
	return(NO);
}

int b_at_end_of_stream(int arglist, int rest, int th)
{
	int n,arg1;

	n=length(arglist);
	if(n==1){
		arg1 = car(arglist);

		if(!streamp(arg1))
		error(NOT_STREAM,"at_end_of_stream ",arglist,th);

		if(arg1 == standard_input || arg1 == standard_output)
			return(NO);
		else if(feof(GET_PORT(arg1)))
			return(prove_all(rest,sp[th],th));
		else 
			return(NO);
	}
	error(ARITY_ERR,"at_end_ofstream ",arglist,th);
	return(NO);
}