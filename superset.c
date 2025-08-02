/*
*     superset builtin predicates 
*/
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <curl/curl.h>
#include "npl.h"

int b_atom_concat(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, atom;
    char str1[STRSIZE];

    n = length(arglist);
    ind = makeind("atom_concat", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);
	if (!wide_variable_p(arg3))
	    exception(NOT_VAR, ind, arg3, th);
	if (strlen(GET_NAME(arg1)) + strlen(GET_NAME(arg2)) > STRSIZE)
	    exception(RESOURCE_ERR, ind, makestr("strsize"), th);

	strcpy(str1, GET_NAME(arg1));
	strcat(str1, GET_NAME(arg2));
	atom = makeconst(str1);

	if (unify(arg3, atom, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_select(int arglist, int rest, int th)
{
    int arg1, arg2, arg3, varYs, varY, varZs, varX, varXs, n, ind, body,
	save1, save2;
    save2 = sp[th];
    n = length(arglist);
    ind = makeind("select", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	varX = makevariant(th);
	varXs = makevariant(th);
	save1 = get_wp(th);
	if (unify_var(arg1, varX, th) == YES
	    && unify(wlistcons(varX, varXs, th), arg2, th) == YES
	    && unify_var(arg3, varXs, th) == YES)
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);
	unbind(save2, th);
	wp[th] = save1;
	varX = makevariant(th);
	varYs = makevariant(th);
	varY = makevariant(th);
	varZs = makevariant(th);
	save1 = wp[th];
	if (unify_var(arg1, varX, th) == YES
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_succ(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("succ", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arglist, th);
	if (!wide_integer_p(arg1) && !wide_variable_p(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_integer_p(arg2) && !wide_variable_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (negativep(arg2))
	    exception(LESS_THAN_ZERO, ind, arg2, th);

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
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_maplist(int arglist, int rest, int th)
{
    int arg1, arg2, varE, varEs, varP, n, ind, pred, arg, body, save1,
	save2;
    save2 = sp[th];
    pred = NIL;
    n = length(arglist);
    ind = makeind("maplist", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!callablep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);
	if (!listp(arg2) && !nullp(arg2))
	    exception(NOT_LIST, ind, arg2, th);
	if (listp(arg2) && length(arg2) == -1)
	    exception(WRONG_ARGS, ind, arg2, th);

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
	if (!callablep(pred))
	    exception(NOT_CALLABLE, ind, pred, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_once(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("once", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!callablep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (atom_constant_p(arg1))
	    arg1 = makeatom(GET_NAME(arg1), PRED);

	if (prove_all(arg1, sp[th], th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_compound(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("compound", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (compoundp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ground(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("ground", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (groundp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_member(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, x, y, l, save1, save2, body, res;

    save2 = sp[th];
    res = NIL;
    n = length(arglist);
    ind = makeind("member", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

//---------extention--------

/*
	append([],X,X).
	append([X|Ls],Ys,[X|Zs]):-
        	append(Ls,Ys,Zs).
*/
int b_append(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, x, ls, ys, zs, save1, save2, body;

    save2 = sp[th];
    body = NIL;
    n = length(arglist);
    ind = makeind("append", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!listp(arg1) && !nullp(arg1) && !wide_variable_p(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (!listp(arg2) && !nullp(arg2) && !wide_variable_p(arg2))
	    exception(NOT_LIST, ind, arg2, th);
	if (!listp(arg3) && !nullp(arg3) && !wide_variable_p(arg3))
	    exception(NOT_LIST, ind, arg3, th);

	save1 = wp[th];
	if (unify_nil(arg1, th) == YES && unify(arg2, arg3, th) == YES) {
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);
	}
	wp[th] = save1;
	unbind(save2, th);

	save1 = wp[th];
	x = makevariant(th);
	ls = makevariant(th);
	ys = makevariant(th);
	zs = makevariant(th);
	if (unify_pair(arg1, wlistcons(x, ls, th), th) == YES &&
	    unify_var(arg2, ys, th) == YES
	    && unify(arg3, wlistcons(x, zs, th), th) == YES) {
	    body = wlist4(makeatom("append", SYS), ls, ys, zs, th);
	    return (prove_all(addtail_body(rest, body, th), sp[th], th));
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_between(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, save2, save3, low, high,
	betweenval;

    n = length(arglist);
    ind = makeind("between", n, th);
    if (n == 3) {
	arg1 = car(arglist);	//low
	arg2 = cadr(arglist);	//high
	arg3 = caddr(arglist);	//variable
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg1) && !integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!wide_variable_p(arg3) && !integerp(arg3))
	    exception(NOT_INT, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_bagof(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, save2, free, vars, nonfree, goal,
	lis;

    n = length(arglist);
    ind = makeind("bagof", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_setof(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, save2, free, vars, nonfree, goal,
	lis;

    n = length(arglist);
    ind = makeind("setof", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_findall(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, save2, goal;

    n = length(arglist);
    ind = makeind("findall", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
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
	putinbag(key, copy_heap(deref(arg1, th)));
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
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("atom_length", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

	if (unify(arg2, makeint(atom_length(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_get_code(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, c, i, res;
    char str[10];

    n = length(arglist);
    ind = makeind("get_code", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get_code;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get_code:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
	if (c == EOF)
	    res = unify(arg2, makeconst("end_of_file"), th);
	else
	    res = unify(arg2, makeint(i), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_get_char(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, c, res;
    char str[10];

    n = length(arglist);
    ind = makeind("get_char", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get_char;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get_char:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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

	if (c == EOF)
	    res = unify(arg2, makeconst("end_of_file"), th);
	else
	    res = unify(arg2, makeconst(str), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_get_byte(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, c, res;

    n = length(arglist);
    ind = makeind("get_byte", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get_byte;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get_byte:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = fgetc(GET_PORT(arg1));

	if (c == EOF)
	    res = unify(arg2, makeconst("end_of_file"), th);
	else
	    res = unify(arg2, makeint(c), th);

	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_put_char(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("put_char", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto put;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      put:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg1) && !characterp(arg2))
	    exception(NOT_CHAR, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	fprintf(GET_PORT(arg1), "%s", GET_NAME(arg2));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_put_code(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("put_code", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto put;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      put:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg1) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	fprintf(GET_PORT(arg1), "%d", GET_INT(arg2));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_put_byte(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("put_byte", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto put;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      put:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg1) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	fprintf(GET_PORT(arg1), "%d", GET_INT(arg2));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_peek_code(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, c, i, res;
    char str[10];

    n = length(arglist);
    ind = makeind("peek_code", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto peek_code;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      peek_code:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = getc(GET_PORT(arg1));
	ungetc(c, GET_PORT(arg1));

	if (isUni2(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni3(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni4(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    ungetc(str[3], GET_PORT(arg1));
	    str[4] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni5(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    ungetc(str[3], GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    ungetc(str[4], GET_PORT(arg1));
	    str[5] = NUL;
	    i = utf8_to_ucs4(str);
	} else if (isUni6(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    ungetc(str[3], GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    ungetc(str[4], GET_PORT(arg1));
	    str[5] = getc(GET_PORT(arg1));
	    ungetc(str[5], GET_PORT(arg1));
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_peek_char(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, c, res;
    char str[10];

    n = length(arglist);
    ind = makeind("peek_char", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto peek_char;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      peek_char:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);

	c = getc(GET_PORT(arg1));
	str[0] = c;
	ungetc(c, GET_PORT(arg1));

	if (isUni2(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = NUL;
	} else if (isUni3(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = NUL;
	} else if (isUni4(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    ungetc(str[3], GET_PORT(arg1));
	    str[4] = NUL;
	} else if (isUni5(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    ungetc(str[3], GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    ungetc(str[4], GET_PORT(arg1));
	    str[5] = NUL;
	} else if (isUni6(c)) {
	    str[0] = c;
	    str[1] = getc(GET_PORT(arg1));
	    ungetc(str[1], GET_PORT(arg1));
	    str[2] = getc(GET_PORT(arg1));
	    ungetc(str[2], GET_PORT(arg1));
	    str[3] = getc(GET_PORT(arg1));
	    ungetc(str[3], GET_PORT(arg1));
	    str[4] = getc(GET_PORT(arg1));
	    ungetc(str[4], GET_PORT(arg1));
	    str[5] = getc(GET_PORT(arg1));
	    ungetc(str[5], GET_PORT(arg1));
	    str[6] = NUL;
	}
	res = NIL;

	res = unify(arg2, makeconst(str), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_peek_byte(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, c, res;

    n = length(arglist);
    ind = makeind("peek_byte", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto peek_byte;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      peek_byte:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	c = fgetc(GET_PORT(arg1));
	ungetc(c, GET_PORT(arg1));

	res = unify(arg2, makeint(c), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_flush_output(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("flush_output", n, th);
    if (n == 0) {
	fflush(stdout);
	return (prove_all(rest, sp[th], th));
    } else if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);

	fflush(GET_PORT(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_atom_codes(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, ls, atom, pos, code, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("atom_codes", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    exception(NOT_LIST, ind, arg2, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_atom_chars(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, ls, atom, pos, c, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("atom_chars", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    exception(NOT_LIST, ind, arg2, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_number_codes(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, ls, num, pos, code, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("number_codes", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!wide_variable_p(arg1) && !numberp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    exception(NOT_LIST, ind, arg2, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_number_chars(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, ls, num, pos, c, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("number_chars", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!wide_variable_p(arg1) && !numberp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    exception(NOT_LIST, ind, arg2, th);


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
		    exception(ILLEGAL_ARGS, ind, arg2, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_catch(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, pt, res;

    n = length(arglist);
    ind = makeind("catch", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!callablep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);

	catch_data[cp[th]][0][th] = arg2;	//tag
	catch_data[cp[th]][1][th] = sp[th];	//sp for restore catch
	int ret = setjmp(catch_buf[cp[th]][th]);
	pt = cp[th];

	if (cp[th] > CTRLSTK) {
	    exception(RESOURCE_ERR, ind, makestr("ctrlstk"), th);
	}

	if (ret == 0) {
	    cp[th]++;
	    if (prove_all(arg1, sp[th], th) == YES) {
		res = prove_all(rest, sp[th], th);
		cp[th]--;
		return (res);
	    } else
		return (NO);
	} else if (ret == 1) {
	    sp[th] = catch_data[pt][1][th];
	    if (prove_all(arg3, sp[th], th) == YES) {
		res = prove_all(rest, sp[th], th);
		cp[th]--;
		return (res);
	    } else
		return (NO);
	}
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

void throw(int tag, int th)
{
    int i;

    for (i = cp[th] - 1; i >= 0; i--) {
	if (unify(catch_data[i][0][th], tag, th) == YES)
	    longjmp(catch_buf[i][th], 1);
    }
}

int b_throw(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("throw", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	throw(arg1, th);
	//if not exist unified tag, execute rest
	return (prove_all(rest, sp[th], th));

    }
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("unify_with_occurs_check", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_current_input(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("current_input", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!wide_variable_p(arg1) && !streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	if (unify(arg1, input_stream, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_current_output(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("current_output", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!wide_variable_p(arg1) && !streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	if (unify(arg1, output_stream, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_set_input(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("set_input", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	input_stream = arg1;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_set_output(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("set_output", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	output_stream = arg1;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_use_module(int arglist, int rest, int th)
{
    int n, ind, arg1;
    char str[STRSIZE];
    FILE *fp;

    n = length(arglist);
    ind = makeind("use_module", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	strcpy(str, "library/");
	strcat(str, GET_NAME(arg1));
	strcat(str, ".o");
	fp = fopen(prolog_file_name(str), "r");
	if (fp != NULL) {
	    fclose(fp);
	    b_reconsult(list1(makeconst(str)), NIL, 0);
	    return (prove_all(rest, sp[th], th));
	}
	strcpy(str, "library/");
	strcat(str, GET_NAME(arg1));
	strcat(str, ".pl");
	fp = fopen(prolog_file_name(str), "r");
	if (fp != NULL) {
	    fclose(fp);
	    b_reconsult(list1(makeconst(str)), NIL, 0);
	    return (prove_all(rest, sp[th], th));
	}

	exception(CANT_OPEN, ind, arglist, th);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_module(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("module", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!listp(arg2) && !nullp(arg2))
	    exception(NOT_LIST, ind, arg2, th);

	module_flag = 1;
	module_name = arg1;
	export_pt = 0;
	while (!nullp(arg2)) {
	    export_data[export_pt][0] = cadr(car(arg2));
	    export_data[export_pt][1] = GET_INT(caddr(car(arg2)));
	    arg2 = cdr(arg2);
	    export_pt++;
	    if (export_pt >= 256)
		exception(RESOURCE_ERR, NIL, ind, th);
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_copy_term(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("copy_term", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	unique_num++;
	if (unify(arg2, copy_term(arg1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_at_end_of_stream(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("at_end_of_stream", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arglist, th);

	if (arg1 == standard_input || arg1 == standard_output)
	    return (NO);
	else if (feof(GET_PORT(arg1)))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_stream_property(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, prop;

    n = length(arglist);
    ind = makeind("stream_property", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arglist, th);

	if (GET_OPT(arg1) == NPL_INPUT)
	    prop = list2(makepred("mode"), makeconst("input"));
	else if (GET_OPT(arg1) == NPL_OUTPUT)
	    prop = list2(makepred("mode"), makeconst("output"));
	else if (GET_OPT(arg1) == NPL_INPUT)
	    prop = list2(makepred("mode"), makeconst("output"));
	else
	    prop = NIL;

	if (unify(arg2, prop, th) == YES) {
	    return (prove_all(rest, sp[th], th));
	}

	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



//-----------TCP/IP--------------------

int b_create_client_socket(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, res, sock;

    n = length(arglist);
    ind = makeind("create_client_socket", n, th);
    if (n == 3) {
	arg1 = car(arglist);	//socket
	arg2 = cadr(arglist);	//port number
	arg3 = caddr(arglist);	//IP address

	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!atomp(arg3))
	    exception(NOT_ATOM, ind, arg3, th);
	if (!wide_variable_p(arg1) && !socketp(arg1))
	    exception(NOT_SOCKET, ind, arg1, th);


	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
	    exception(SYSTEM_ERR, ind, NIL, th);
	}

	memset((char *) &client_addr, 0, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(GET_INT(arg2));

	if (inet_pton(AF_INET, GET_NAME(arg3), &client_addr.sin_addr) < 0)
	    exception(SYSTEM_ERR, ind, NIL, 0);


	if (connect
	    (sock, (struct sockaddr *) &client_addr,
	     sizeof(client_addr)) < 0) {
	    exception(SYSTEM_ERR, ind, NIL, 0);
	}

	res = makesocket(sock, NPL_SOCKET, "client", NIL);
	if (unify(arg1, res, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_create_server_socket(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, sock0, sock1, res;

    n = length(arglist);
    ind = makeind("create_server_socket", n, th);
    if (n == 2) {
	arg1 = car(arglist);	// socket
	arg2 = cadr(arglist);	// port number

	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!wide_variable_p(arg1) && !socketp(arg1))
	    exception(NOT_SOCKET, ind, arg1, th);

	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 < 0) {
	    exception(SYSTEM_ERR, ind, NIL, th);
	}

	memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(GET_INT(arg2));

	if (bind
	    (sock0, (struct sockaddr *) &server_addr,
	     sizeof(server_addr)) < 0) {
	    exception(SYSTEM_ERR, ind, NIL, th);
	}

	listen(sock0, 5);
	parent_len = sizeof(server_addr);
	sock1 =
	    accept(sock0, (struct sockaddr *) &server_addr, &parent_len);
	if (sock1 < 0) {
	    exception(SYSTEM_ERR, ind, NIL, th);
	}

	res = makesocket(sock1, NPL_SOCKET, "server", sock0);
	if (unify(arg1, res, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_send_socket(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, m;
    char buf[256];

    n = length(arglist);
    ind = makeind("send_socket", n, th);
    if (n == 2) {
	arg1 = car(arglist);	//socket
	arg2 = cadr(arglist);	//message atom

	if (!socketp(arg1))
	    exception(NOT_SOCKET, ind, arg1, th);
	if (!atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);

	strcpy(buf, GET_NAME(arg2));
	m = write(GET_SOCKET(arg1), buf, 256);
	if (m < 0)
	    exception(SYSTEM_ERR, ind, NIL, th);

	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_recv_socket(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, sock, m;
    char buf[STRSIZE];

    n = length(arglist);
    ind = makeind("recv_socket", n, th);
    if (n == 2) {
	arg1 = car(arglist);	//socket
	arg2 = cadr(arglist);	//receive var

	if (!socketp(arg1))
	    exception(NOT_SOCKET, ind, arg1, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_ATOM, ind, arg1, th);

	sock = GET_SOCKET(arg1);
	memset(buf, 0, sizeof(buf));
	m = read(sock, buf, sizeof(buf) - 1);
	if (m < 0) {
	    exception(SYSTEM_ERR, ind, NIL, 0);
	}
	if (unify(arg2, makeconst(buf), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_close_socket(int arglist, int rest, int th)
{
    int n, ind, arg1, sock0, sock1;

    n = length(arglist);
    ind = makeind("close_socket", n, th);
    if (n == 1) {
	arg1 = car(arglist);	//socket
	if (!socketp(arg1))
	    exception(NOT_SOCKET, ind, arg1, th);

	sock0 = GET_SOCKET(arg1);
	sock1 = GET_CDR(arg1);
	close(sock0);
	if (!nullp(sock1)) {
	    close(sock1);
	}

	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dynamic(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("dynamic", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!indicatorp(arg1))
	    exception(NOT_INDICATOR, ind, arg1, th);

	dynamic_list = cons(cadr(arg1), dynamic_list);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_cinline(int arglist, int rest, int th)
{
    int n, arg1, ind;

    n = length(arglist);
    ind = makeind("cinline", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!stringp(arg1))
	    exception(NOT_STR, ind, arg1, th);

	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_set_prolog_flag(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind;

    n = length(arglist);
    ind = makeind("set_prolog_flag", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (eqlp(arg1, makeconst("string"))
	    && eqlp(arg2, makeconst("arity"))) {
	    string_flag = 0;
	    return (prove_all(rest, sp[th], th));
	} else if (eqlp(arg1, makeconst("string"))
		   && eqlp(arg2, makeconst("iso"))) {
	    string_flag = 1;
	    return (prove_all(rest, sp[th], th));
	} else if (eqlp(arg1, makeconst("expression"))
		   && eqlp(arg2, makeconst("canonical"))) {
	    sexp_flag = 0;
	    return (prove_all(rest, sp[th], th));
	} else if (eqlp(arg1, makeconst("expression"))
		   && eqlp(arg2, makeconst("sexp"))) {
	    sexp_flag = 1;
	    return (prove_all(rest, sp[th], th));
	}


	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int format_obj(int x, int ind, int th)
{
    char obj[STRSIZE];

    if (integerp(x)) {
	sprintf(obj, "%d", GET_INT(x));
    } else if (floatp(x)) {
	sprintf(obj, "%g", GET_FLT(x));
    } else if (atomp(x)) {
	sprintf(obj, "%s", GET_NAME(x));
    } else if (stringp(x)) {
	sprintf(obj, "%s", GET_NAME(x));
    } else {
	exception(NOT_ATOMIC, ind, x, th);
    }

    return (makestr(obj));
}

int b_format(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, ind, i, j, k, save;
    char c, format[STRSIZE], output[STRSIZE], substr[STRSIZE];

    n = length(arglist);
    ind = makeind("format", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (!wide_variable_p(arg1) && !streamp(arg1) && !aliasp(arg1))
	    exception(NOT_VAR, ind, arg1, th);
	if (!stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);
	if (!listp(arg3))
	    exception(NOT_LIST, ind, arg3, th);

	memset(output, 0, sizeof(output));
	memset(format, 0, sizeof(format));
	strcpy(format, GET_NAME(arg2));
	i = 0;
	j = 0;
	c = format[i++];
	while (c != 0) {
	    if (c == '~') {
		c = format[i++];
		if (c == 'O') {
		    memset(substr, 0, sizeof(substr));
		    strcpy(substr,
			   GET_NAME(format_obj(car(arg3), ind, th)));
		    arg3 = cdr(arg3);
		    k = 0;
		    c = substr[k++];
		    while (c != 0) {
			output[j++] = c;
			c = substr[k++];
		    }
		} else if (c == 'A') {
		    if (!atomp(car(arg3)))
			exception(NOT_ATOM, ind, arg3, th);
		    memset(substr, 0, sizeof(substr));
		    strcpy(substr, GET_NAME(car(arg3)));
		    arg3 = cdr(arg3);
		    k = 0;
		    c = substr[k++];
		    while (c != 0) {
			output[j++] = c;
			c = substr[k++];
		    }
		}
		if (c == 'S') {
		    if (!stringp(car(arg3)))
			exception(NOT_STR, ind, arg3, th);
		    memset(substr, 0, sizeof(substr));
		    strcpy(substr, GET_NAME(car(arg3)));
		    arg3 = cdr(arg3);
		    k = 0;
		    c = substr[k++];
		    while (c != 0) {
			output[j++] = c;
			c = substr[k++];
		    }
		} else if (c == 'D') {
		    if (!integerp(car(arg3)))
			exception(NOT_INT, ind, arg3, th);
		    memset(substr, 0, sizeof(substr));
		    sprintf(substr, "%d", GET_INT(car(arg3)));
		    arg3 = cdr(arg3);
		    k = 0;
		    c = substr[k++];
		    while (c != 0) {
			output[j++] = c;
			c = substr[k++];
		    }
		} else if (c == 'F') {
		    memset(substr, 0, sizeof(substr));
		    sprintf(substr, "%g", GET_FLT(car(arg3)));
		    arg3 = cdr(arg3);
		    k = 0;
		    c = substr[k++];
		    while (c != 0) {
			output[j++] = c;
			c = substr[k++];
		    }
		}
	    } else {
		output[j++] = c;
	    }
	    c = format[i++];
	}
	if (wide_variable_p(arg1)) {
	    if (unify(arg1, makestr(output), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else {
	    save = output_stream;
	    if (aliasp(arg1))
		output_stream = GET_CAR(arg1);
	    else
		output_stream = arg1;
	    quoted_flag = 0;
	    print(makestr(output));
	    quoted_flag = 1;
	    output_stream = save;
	    return (prove_all(rest, sp[th], th));
	}
    }

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

//------------------https curl----------------


size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    strncat((char *) userdata, (char *) ptr, size * nmemb);	// store recieved data
    return size * nmemb;
}

int b_create_client_curl(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind;
    CURL *curl;

    n = length(arglist);
    ind = makeind("create_client_curl", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!wide_variable_p(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

	curl = curl_easy_init();
	if (!curl) {
	    exception(SYSTEM_ERR, ind, NIL, th);
	}

	curl_easy_setopt(curl, CURLOPT_URL, GET_NAME(arg2));
	if (unify(arg1, makecurl(curl, NPL_CURL, GET_NAME(arg2)), th) ==
	    YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_send_curl(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind;
    CURL *curl;

    n = length(arglist);
    ind = makeind("send_curl", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

	curl = GET_CURL(arg1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, GET_NAME(arg2));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_recv_curl(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind;
    char response_data[STRSIZE] = { 0 };
    CURL *curl;

    n = length(arglist);
    ind = makeind("recv_curl", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

	curl = GET_CURL(arg1);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_data);
	curl_easy_perform(curl);
	if (unify(arg2, makestr(response_data), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_close_curl(int arglist, int rest, int th)
{
    int n, arg1, ind;

    n = length(arglist);
    ind = makeind("close_curl", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	curl_easy_cleanup(GET_CURL(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_set_curl_option(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind, header, post, get, timeout, var;
    CURL *curl;

    n = length(arglist);
    ind = makeind("set_curl_option", n, th);

    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

	curl = GET_CURL(arg1);
	var = makevariant(th);
	header = list2(makepred("header"), var);
	post = list2(makepred("method"), makeconst("post"));
	get = list2(makepred("get"), makeconst("get"));
	timeout = list2(makepred("timeout"), var);
	if (unify(arg2, header, th) == YES) {
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, GET_NAME(var));
	} else if (unify(arg2, post, th) == YES) {
	    curl_easy_setopt(curl, CURLOPT_POST, 1L);
	} else if (unify(arg2, get, th) == YES) {
	    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	} else if (unify(arg2, timeout, th) == YES) {
	    long timeout = GET_INT(var);
	    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
	} else {
	    exception(SYSTEM_ERR, ind, NIL, th);
	    return (NO);
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_add_curl_header(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind;
    CURL *curl;
    struct curl_slist *headers = NULL;

    n = length(arglist);
    ind = makeind("add_curl_header", n, th);

    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

	curl = GET_CURL(arg1);
	headers = curl_slist_append(headers, GET_NAME(arg2));
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_string_atom(int arglist, int rest, int th)
{
    int n, arg1, arg2, ind;

    n = length(arglist);
    ind = makeind("string_atom", n, th);

    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!(stringp(arg1) || wide_variable_p(arg1)))
	    exception(NOT_STR, ind, arg1, th);
	if (!(atomp(arg2) || wide_variable_p(arg2)))
	    exception(NOT_ATOM, ind, arg1, th);

	if (stringp(arg1)) {
	    if (unify(arg2, makeconst(GET_NAME(arg1)), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (atomp(arg2)) {
	    if (unify(arg1, makestr(GET_NAME(arg2)), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_initialization(int arglist, int rest, int th)
{
    int n, arg1, ind;

    n = length(arglist);
    ind = makeind("initialization", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	execute_list = listcons(copy_heap(arg1), execute_list);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
