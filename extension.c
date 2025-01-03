#include <string.h>
#ifdef __arm__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "npl.h"

//-----------JUMP project(builtin for compiler)------------

int b_reconsult_predicate(int arglist, int rest, int th)
{
    int n, arg1, lis, save1;

    n = length(arglist);
    if (n == 1) {
	save1 = sp[th];
	arg1 = deref(car(arglist), th);
	if (!wide_variable_p(arg1))
	    error(NOT_VAR, "n_reconsult_predicate ", arg1,th);

	lis = reverse(reconsult_list);
	while (!nullp(lis)) {
	    unify(arg1, car(lis), th);
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);

	    lis = cdr(lis);
	    unbind(save1, th);
	}
	unbind(save1, th);
	return (NO);
    }
    return (NO);
}

int b_reconsult_abolish(int arglist, int rest, int th)
{
    int n, lis, pred;

    n = length(arglist);
    if (n == 0) {
	lis = reconsult_list;
	while (!nullp(lis)) {
	    pred = makepred(GET_NAME(car(lis)));
	    SET_CAR(pred, NIL);
	    listremove(car(lis), predicates);
	    lis = cdr(lis);
	}
	return (prove_all(rest, sp[th], th));
    }
    return (NO);
}

int b_filename(int arglist, int rest, int th)
{
    int n, arg1, arg2, pos, len;
    char str1[STRSIZE];

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist), th);
	arg2 = cadr(arglist);
	strcpy(str1, GET_NAME(arg1));
	len = strlen(GET_NAME(arg1));
	for (pos = 0; pos < len; pos++)
	    if (pos == 0 && str1[pos] == '.') {	// ./
		pos = pos + 2;
	    } else if (pos == 0 && str1[pos] == '.' && str1[pos + 1] == '.') {	// ../
		pos = pos + 3;
	    } else if (str1[pos] == '.') {
		str1[pos] = NUL;
		if (unify(arg2, makeconst(str1), th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    }
	if (unify(arg1, arg2, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

//convert atom for C language function name
int b_atom_convert(int arglist, int rest, int th)
{
    int n, arg1, arg2, pos1;
    char str1[ATOMSIZE], str2[ATOMSIZE], str3[ATOMSIZE], str4[ATOMSIZE];
    //   str1=input   str2=unicode-buffer str3=usc4-buffer str4 = output-string 
    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist), th);
	arg2 = deref(cadr(arglist), th);

	strcpy(str1, GET_NAME(arg1));
	pos1 = 0;
	memset(str4, NUL, ATOMSIZE);

	while (str1[pos1] != NUL) {
	    if (str1[pos1] == ':') {
		str2[0] = '_';
		str2[1] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '&') {
		str2[0] = 'a';
		str2[1] = 'n';
		str2[2] = 'd';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '?') {
		str2[0] = 'm';
		str2[1] = 'a';
		str2[2] = 'g';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '+') {
		str2[0] = 'p';
		str2[1] = 'l';
		str2[2] = 's';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '-') {
		str2[0] = 'm';
		str2[1] = 'n';
		str2[2] = 's';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '*') {
		str2[0] = 'a';
		str2[1] = 's';
		str2[2] = 't';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '/') {
		str2[0] = 'd';
		str2[1] = 'i';
		str2[2] = 'v';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '>') {
		str2[0] = 'r';
		str2[1] = 'i';
		str2[2] = 'g';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (str1[pos1] == '<') {
		str2[0] = 'l';
		str2[1] = 'e';
		str2[2] = 'f';
		str2[3] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (isUni1(str1[pos1])) {
		str2[0] = str1[pos1];
		str2[1] = NUL;
		strcat(str4, str2);
		pos1++;
	    } else if (isUni2(str1[pos1])) {
		str2[0] = str1[pos1++];
		str2[1] = str1[pos1++];
		str2[2] = NUL;
		sprintf(str3, "u%d", utf8_to_ucs4(str2));
		strcat(str4, str3);
	    } else if (isUni3(str1[pos1])) {
		str2[0] = str1[pos1++];
		str2[1] = str1[pos1++];
		str2[2] = str1[pos1++];
		str2[3] = NUL;
		sprintf(str3, "u%d", utf8_to_ucs4(str2));
		strcat(str4, str3);
	    } else if (isUni4(str1[pos1])) {
		str2[0] = str1[pos1++];
		str2[1] = str1[pos1++];
		str2[2] = str1[pos1++];
		str2[3] = str1[pos1++];
		str2[4] = NUL;
		sprintf(str3, "u%d", utf8_to_ucs4(str2));
		strcat(str4, str3);
	    } else if (isUni5(str1[pos1])) {
		str2[0] = str1[pos1++];
		str2[1] = str1[pos1++];
		str2[2] = str1[pos1++];
		str2[3] = str1[pos1++];
		str2[4] = str1[pos1++];
		str2[5] = NUL;
		sprintf(str3, "u%d", utf8_to_ucs4(str2));
		strcat(str4, str3);
	    } else if (isUni6(str1[pos1])) {
		str2[0] = str1[pos1++];
		str2[1] = str1[pos1++];
		str2[2] = str1[pos1++];
		str2[3] = str1[pos1++];
		str2[4] = str1[pos1++];
		str2[5] = str1[pos1++];
		str2[6] = NUL;
		sprintf(str3, "u%d", utf8_to_ucs4(str2));
		strcat(str4, str3);
	    }
	}
	unify(arg2, makeconst(str4), th);
	return (prove_all(rest, sp[th], th));
    }
    return (NO);
}

int b_arity_count(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist), th);
	arg2 = cadr(arglist);

	if (unify(arg2, listreverse(GET_ARITY(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}


int b_generate_all_variable(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist), th);
	arg2 = cadr(arglist);
	if (unify(arg2, generate_all_variable(GET_CAR(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int b_generate_variable(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist), th);
	arg2 = cadr(arglist);
	if (unify(arg2, generate_variable(arg1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int generate_all_variable(int x)
{
    int y, res;

    res = NIL;
    while (!nullp(x)) {
	y = variable_convert1(car(x));
	if (clausep(y))
	    res = generate_variable1(caddr(y),
				     generate_variable1(cadr(y), res));
	else
	    res = generate_variable1(y, res);

	x = cdr(x);
    }
    return (res);
}

int generate_variable(int x)
{
    if (clausep(x))
	return (generate_variable1(caddr(x),
				   generate_variable1(cadr(x), NIL)));
    else
	return (generate_variable1(x, NIL));
}

int generate_variable1(int x, int y)
{
    int temp;

    if (nullp(x))
	return (y);
    else if (numberp(x))
	return (y);
    else if (compiler_variable_p(x) && !memq(x, y)) {
	temp = cons(x, y);
	SET_AUX(temp, LIST);
	return (temp);
    } else if (singlep(x))
	return (y);
    else if (car(x) == AND)
	return (generate_variable1
		(cadr(x), generate_variable1(caddr(x), y)));
    else if (car(x) == OR)
	return (generate_variable1
		(cadr(x), generate_variable1(caddr(x), y)));
    else
	return (generate_variable1(car(x), generate_variable1(cdr(x), y)));
}

int b_compiler_anoymous(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist), th);
	if (compiler_anoymous_p(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int compiler_anoymous_p(int x)
{
    char str[256];

    if (numberp(x))
	return (0);
    if (!!structurep(x))
	return (0);
    strcpy(str, GET_NAME(x));
    str[4] = NUL;
    if (strcmp(str, "var_") == 0)
	return (1);
    else
	return (0);
}



int b_compiler_variable(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist), th);
	if (compiler_variable_p(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int compiler_variable_p(int x)
{
    char str[256];

    if (numberp(x))
	return (0);
    if (!!structurep(x))
	return (0);
    strcpy(str, GET_NAME(x));
    str[3] = NUL;
    if (strcmp(str, "var") == 0)
	return (1);
    else
	return (0);
}

int b_variable_convert(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist), th);
	arg2 = cadr(arglist);

	if (unify(arg2, variable_convert1(arg1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int variable_convert1(int x)
{
    int y;
    variable_convert4(NIL);	//initialize anoymous N
    y = variable_convert2(x);
    if (clausep(x)) {
	SET_AUX(y, CLAUSE);
	SET_OPT(y, GET_OPT(x));
    }
    return (y);
}

int variable_convert2(int x)
{
    int y, z;

    if (nullp(x))
	return (NIL);
    else if (anoymousp(x))
	return (variable_convert4(x));
    else if (variablep(x))
	return (variable_convert3(x));
    else if (!structurep(x))
	return (x);
    else {
	y = GET_AUX(x);
	z = cons(variable_convert2(car(x)), variable_convert2(cdr(x)));
	SET_AUX(z, y);
	return (z);
    }

}

//normal variable X -> varX
int variable_convert3(int x)
{
    int res;
    char str[STRSIZE];

    strcpy(str, "var");
    strcat(str, GET_NAME(x));
    res = makeconst(str);
    return (res);
}

//anoymous variable _ -> varN (N=1...)
int variable_convert4(int x)
{
    int res;
    static int n;
    char str1[STRSIZE], str2[STRSIZE];

    //initialize
    if (x == NIL) {
	n = 1;
	return (0);
    }

    strcpy(str1, "var_");
    sprintf(str2, "%d", n);
    strcat(str1, str2);
    res = makeconst(str1);
    n++;
    return (res);
}

int b_clause_with_arity(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, l, clause, clauses, res;

    n = length(arglist);
    if (n == 3) {
	arg1 = deref(car(arglist), th);
	arg2 = deref(cadr(arglist), th);
	arg3 = deref(caddr(arglist), th);
	if (!singlep(arg1))
	    error(NOT_ATOM, "n_clause_with_arity", arg1,th);
	if (!integerp(arg2))
	    error(NOT_INT, "n_clause_with_arity", arg2,th);

	clauses = GET_CAR(arg1);
	l = GET_INT(arg2);
	res = NIL;

	while (!nullp(clauses)) {
	    clause = car(clauses);
	    if (atomp(clause) && l == 0)
		res = cons(clause, res);
	    else if (predicatep(clause) && length(clause) == l + 1)
		res = cons(clause, res);
	    else if (user_operation_p(clause) && length(clause) == l + 1)
		res = cons(clause, res);
	    else if (clausep(clause) && atomp(cadr(clause)) && l == 0)
		res = cons(clause, res);
	    else if (clausep(clause) && length(cadr(clause)) == l + 1)
		res = cons(clause, res);

	    clauses = cdr(clauses);
	}
	res = listreverse(res);
	unify(res, arg3, th);
	return (prove_all(rest, sp[th], th));
    }
    return (NO);
}

int b_error(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	int ret1 = setjmp(buf1);


	if (ret1 == 0) {
	    check_flag = 1;
	    prove_all(arg1, sp[th], th);
	    check_flag = 0;
	    printf("Not error: ");
	    print(arg1);
	    return (NO);
	} else if (ret1 == 1) {
	    ret1 = 0;
	    check_flag = 0;
	    if (unify(arg2, makeint(error_code), th) == YES) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
		else
		    return (NO);
	    } else {
		printf("Wrong error code: %d ", error_code);
		print(arg1);
		return (NO);
	    }
	}
    }
    error(ARITY_ERR, "n_error ", arglist,th);
    return (NO);
}

int b_property(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (builtinp(arg1)) {
	    if (unify(arg2, makeconst("builtin"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (predicatep(arg1)) {
	    if (unify(arg2, makeconst("predicate"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (functionp(arg1)) {
	    if (unify(arg2, makeconst("function"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (compiledp(arg1)) {
	    if (unify(arg2, makeconst("compiled"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (operationp(arg1)) {
	    if (unify(arg2, makeconst("operation"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (operatorp(arg1)) {
	    if (unify(arg2, makeconst("operator"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (user_operator_p(arg1)) {
	    if (unify(arg2, makeconst("userop"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (user_operation_p(arg1)) {
	    if (unify(arg2, makeconst("userop"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (singlep(arg1) && findatom(arg1, USER) == 1) {
	    if (unify(arg2, makeconst("userop"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg1) && GET_AUX(arg1) != LIST &&
		   IS_INCELL(car(arg1)) && findatom(car(arg1), USER) == 1)
	{
	    if (unify(arg2, makeconst("userop"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);

    }
    return (NO);
}

int b_bignum(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (bignump(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int b_longnum(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (longnump(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int b_findatom(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, res;

    n = length(arglist);
    if (n == 3) {
	arg1 = deref(car(arglist), th);	//atom
	arg2 = deref(cadr(arglist), th);	//property
	arg3 = deref(caddr(arglist), th);	//address

	res = NIL;
	if (eqlp(arg2, makeconst("constant")))
	    res = findatom(arg1, SIMP);
	else if (eqlp(arg2, makeconst("predicate")))
	    res = findatom(arg1, PRED);
	else if (eqlp(arg2, makeconst("builtin")))
	    res = findatom(arg1, SYS);
	else if (eqlp(arg2, makeconst("compiled")))
	    res = findatom(arg1, COMP);
	else if (eqlp(arg2, makeconst("operator")))
	    res = findatom(arg1, OPE);
	else if (eqlp(arg2, makeconst("userop")))
	    res = findatom(arg1, USER);
	else
	    error(ILLEGAL_ARGS, "findatom ", arg2,th);

	if (unify(arg3, makeint(res), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int b_defined_predicate(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist), th);

	if (predicatep(arg1)) {
	    if (atomp(arg1) && GET_CAR(arg1) != NIL)
		return (prove_all(rest, sp[th], th));
	    else if (structurep(arg1) && GET_CAR(car(arg1)) != NIL)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    return (NO);
}

int b_defined_userop(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist), th);

	if (user_operation_p(arg1) || user_operator_p(arg1)) {
	    if (atomp(arg1) && GET_CAR(arg1) != NIL)
		return (prove_all(rest, sp[th], th));
	    else if (structurep(arg1) && GET_CAR(car(arg1)) != NIL)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    return (NO);
}

int b_get_execute(int arglist, int rest, int th)
{
    int n, arg1, pos, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	res = NIL;
	pos = execute_list;
	while (!nullp(pos)) {
	    res = listcons(car(pos), res);
	    pos = cdr(pos);
	}
	if (unify(arg1, res, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    return (NO);
}

int b_heapdump(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "heapd ", arg1,th);
	if (!integerp(arg2))
	    error(NOT_INT, "heapd ", arg2,th);
	if (greaterp(arg1, arg2))
	    error(WRONG_ARGS, "heapd ", wlist2(arg1, arg2, th), th);

	heapdump(get_int(arg1), get_int(arg2));
	return (prove_all(rest, sp[th], th));
    }
    return (NO);
}

int b_existerrors(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (arg1 != YES && arg1 != NO && !wide_variable_p(arg1))
	    error(ILLEGAL_ARGS, "existerrors ", arg1,th);
	if (arg2 != YES && arg2 != NO && !wide_variable_p(arg2))
	    error(ILLEGAL_ARGS, "existerrors ", arg1,th);

	res = unify(arg1, exist_flag, th);
	exist_flag = arg2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "existerrors ", arglist,th);
    return (NO);
}

int b_has_cut(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (has_cut_p(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "n_has_cut ", arglist, th);
    return (NO);
}

int b_before_cut(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (has_cut_p(arg1)) {
	    unify(arg2, before_cut(arg1), th);
	    return (prove_all(rest, sp[th], th));
	} else
	    return (NO);
    }
    error(ARITY_ERR, "n_before_cut ", arglist, th);
    return (NO);
}

int b_after_cut(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (has_cut_p(arg1)) {
	    unify(arg2, after_cut(arg1), th);
	    return (prove_all(rest, sp[th], th));
	} else
	    return (NO);
    }
    error(ARITY_ERR, "n_after_cut ", arglist, th);
    return (NO);
}

int exec_all(int goals, int bindings, int th)
{

    if (nullp(goals))
	return (YES);
    /* ,(;(D1;D2),Xs) */
    else if (listp(goals) && car(cadr(goals)) == OR) {
	if (exec_all(cadr(cadr(goals)), bindings, th) == YES)
	    return (exec_all(caddr(goals), bindings, th));
	else if (exec_all(caddr(cadr(goals)), bindings, th) == YES)
	    return (exec_all(caddr(goals), bindings, th));
	else
	    return (NO);
    } else if (car(goals) != AND)
	return (exec(goals, bindings, NIL, th));
    else {
	return (exec(cadr(goals), bindings, caddr(goals), th));
    }

    return (NO);
}

int exec(int goal, int bindings, int rest, int th)
{
    int res;

    proof[th]++;
    goal = deref(goal, th);

    if (nullp(goal)) {
	return (exec_all(rest, bindings, th));
    } else if (builtinp(goal)) {
	if (atomp(goal)) {
	    if ((res = (GET_SUBR(goal)) (NIL, rest, th)) == YES)
		return (YES);

	    return (res);
	} else {
	    if ((res = (GET_SUBR(car(goal))) (cdr(goal), rest, th)) == YES)
		return (YES);

	    return (res);
	}
    } else if (compiledp(goal)) {
	if (atomp(goal)) {
	    if ((GET_SUBR(goal)) (NIL, rest, th) == YES)
		return (YES);

	    return (NO);
	} else {
	    if ((GET_SUBR(car(goal))) (cdr(goal), rest, th) == YES)
		return (YES);

	    return (NO);
	}
    }
    return (NO);
}



//----------for Raspberry PI
#ifdef __arm__
int b_wiringpi_setup_gpio(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == th) {
	wiringPiSetupGpio();
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "wiringpi_setup_gpio ", arglist, th);
    return (NO);
}

int b_wiringpi_spi_setup_ch_speed(int arglist, int rest, int th)
{
    int n, arg1, arg2, x, y;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "wiringpi_spi_setup_ch_speed ", arg1, th);
	if (!integerp(arg2))
	    error(NOT_INT, "wiringpi_spi_setup_ch_speed ", arg2,th);


	x = GET_INT(arg1);
	y = GET_INT(arg2);
	wiringPiSPISetup(x, y);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "wiringpi_spi_setup_ch_speed ", arglist,th);
    return (NO);
}

int b_pwm_set_mode(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (arg1 == makeconst("pwm_mode_ms"))
	    pwmSetMode(PWM_MODE_MS);
	else if (arg1 == makeconst("pwm_mode_bal"))
	    pwmSetMode(PWM_MODE_BAL);
	else
	    error(WRONG_ARGS, "pwm_set_mode", arg1,th);

	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "pwm_set_mode ", arglist,th);
    return (NO);
}

int b_pwm_set_range(int arglist, int rest, int th)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pwm_set_range", arg1,th);

	x = GET_INT(arg1);
	pwmSetRange(x);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "pwm_set_range ", arglist,th);
    return (NO);
}

int b_pwm_set_clock(int arglist, int rest, int th)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pwm_set_clock", arg1,th);

	x = GET_INT(arg1);
	pwmSetClock(x);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "pwm_set_clock ", arglist,th);
    return (NO);
}

int b_pin_mode(int arglist, int rest, int th)
{
    int n, arg1, arg2, x;


    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pin_mode ", arg1,th);

	x = GET_INT(arg1);
	if (arg2 == makeconst("intput"))
	    pinMode(x, INPUT);
	else if (arg2 == makeconst("output"))
	    pinMode(x, OUTPUT);
	else if (arg2 == makeconst("pwm_output"))
	    pinMode(x, PWM_OUTPUT);
	else
	    error(WRONG_ARGS, "pin_mode", arg2,th);

	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "pin_mode ", arglist,th);
    return (NO);
}

int b_digital_write(int arglist, int rest, int th)
{
    int n, arg1, arg2, x, y;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "digital_write ", arg1,th);
	if (!integerp(arg2))
	    error(NOT_INT, "digital_write ", arg2,th);

	x = GET_INT(arg1);
	y = GET_INT(arg2);
	digitalWrite(x, y);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "digital_write ", arglist,th);
    return (NO);
}

int b_digital_write_byte(int arglist, int rest, int th)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "digital_write_byte ", arg1,th);

	x = GET_INT(arg1);
	digitalWriteByte(x);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "digital_write_byte ", arglist,th);
    return (NO);
}

int b_pull_up_dn_control(int arglist, int rest, int th)
{
    int n, arg1, arg2, x, y;


    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pull_up_dn_control ", arg1,th);
	if (!integerp(arg2))
	    error(NOT_INT, "pull_up_dn_control ", arg2,th);

	x = GET_INT(arg1);
	y = GET_INT(arg2);
	pullUpDnControl(x, y);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "pull_up_dn_control ", arglist,th);
    return (NO);
}

int b_digital_read(int arglist, int rest, int th)
{
    int n, arg1, arg2, x, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "digital_read", arg1,th);

	x = GET_INT(arg1);
	res = digitalRead(x);
	if (unify(arg2, makeint(res), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "digital_read ", arglist,th);
    return (NO);
}

int b_delay(int arglist, int rest, int th)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "delay", arg1,th);

	x = GET_INT(arg1);
	delay(x);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "delay ", arglist,th);
    return (NO);
}

int b_delay_microseconds(int arglist, int rest, int th)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "delay_microseconds ", arg1,th);

	x = GET_INT(arg1);
	delayMicroseconds(x);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "delay_microseconds ", arglist,th);
    return (NO);
}

int b_timer_microseconds(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (arg1 == TIMERON)
	    timer = getETime();
	else if (arg1 == TIMEROFF)
	    timer = getETime() - timer;
	else if (variablep(arg1))
	    unify(arg1, makeflt(timer), th);
	else
	    error(ILLEGAL_ARGS, "timer_microseconds ", arg1,th);

	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "timer_microseconds ", arglist,th);
    return (NO);
}


#endif


/* distributed parallel */
int pred_to_str(int x)
{
    int res;

    memset(bridge, '\0', sizeof(bridge));
    bridge_flag = 1;
    print(x);
    printstr(".\n");
    bridge_flag = 0;
    res = makestr((char *) bridge);
    return (res);
}

int str_to_pred(int x)
{
    int res;

    bridge_flag = 1;
    memset(bridge, '\0', sizeof(bridge));
    strcpy(bridge, GET_NAME(x));
    read_string_term(0);
    res = variable_to_call(readparse(0));
    memset(bridge, 0, sizeof(bridge));
    bridge_flag = 0;
    return (res);
}

// under construction V_1 -> v_1
int convert_to_variant(int x, int th)
{
    char *substr, *var;
    int i;

    if (nullp(x))
	return (NIL);
    else if (narrow_variable_p(x)) {
	var = GET_NAME(x);
	substr = &var[2];
	i = atoi(substr);
	i = i + CELLSIZE;
	return (i);
    }
    if (listp(x)) {
	return (x);
    } else if (!structurep(x)) {
	return (x);
    }
    return (wcons
	    (convert_to_variant(car(x), th),
	     convert_to_variant(cdr(x), th), th));
}

// under construction v_1 -> V_1
int convert_to_variable(int x, int th)
{
    char str[256];

    if (nullp(x))
	return (NIL);
    else if (IS_ALPHA(x)) {
	sprintf(str, "V_%d", x - CELLSIZE);
	return (makevar(str));
    } else if (listp(x)) {
	return (x);
    } else if (!structurep(x)) {
	return (x);
    } else
	return (wcons(convert_to_variable(car(x), th),
		      convert_to_variable(cdr(x), th), th));
}

void init_parent(void)
{

    // create socket
    parent_sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (parent_sockfd[0] < 0) {
	error(SYSTEM_ERROR, "init parent", NIL,0);
    }
    // initialize parent_addr
    memset((char *) &parent_addr, 0, sizeof(parent_addr));
    parent_addr.sin_family = AF_INET;
    parent_addr.sin_addr.s_addr = INADDR_ANY;
    parent_addr.sin_port = htons(PORT);

    // bind socket
    if (bind
	(parent_sockfd[0], (struct sockaddr *) &parent_addr,
	 sizeof(parent_addr)) < 0) {
	error(SYSTEM_ERROR, "init parent", NIL,0);
    }

}

void init_child(int n, int x)
{

    // create socket
    child_sockfd[n] = socket(AF_INET, SOCK_STREAM, 0);
    if (child_sockfd[n] < 0) {
	error(SYSTEM_ERROR, "dp_create", makeint(n),0);
    }
    // initialize child_addr
    memset((char *) &child_addr[n], 0, sizeof(child_addr[n]));
    child_addr[n].sin_family = AF_INET;
    child_addr[n].sin_port = htons(PORT);

    if (inet_pton(AF_INET, GET_NAME(x), &child_addr[n].sin_addr) < 0)
	error(SYSTEM_ERROR, "dp_create", x,0);


    if (connect
	(child_sockfd[n], (struct sockaddr *) &child_addr[n],
	 sizeof(child_addr[n])) < 0) {
	error(SYSTEM_ERROR, "dp_create", makeint(n),0);
    }

}


int receive_from_parent(void)
{
    int n;

    if (!connect_flag) {
	//wait conneting
	listen(parent_sockfd[0], 5);
	parent_len = sizeof(parent_addr);
	connect_flag = 1;

	// connection from parent
	parent_sockfd[1] =
	    accept(parent_sockfd[0], (struct sockaddr *) &parent_addr,
		   &parent_len);
	if (parent_sockfd[1] < 0) {
	    error(SYSTEM_ERROR, "receive from parent", NIL,0);
	}
    }
    // read message from parent
    memset(bridge, 0, sizeof(bridge));
    n = read(parent_sockfd[1], bridge, sizeof(bridge) - 1);
    if (n < 0) {
	error(SYSTEM_ERROR, "receive from parent", NIL,0);
    }
    return (makestr(bridge));
}

void send_to_parent(int x)
{
    int n;

    // send message to parent
    memset(bridge, 0, sizeof(bridge));
    strcpy(bridge, GET_NAME(x));
    n = write(parent_sockfd[1], bridge, strlen(bridge));
    memset(bridge, 0, sizeof(bridge));
    if (n < 0) {
	error(SYSTEM_ERROR, "send to parent", x,0);
    }
}

void send_to_parent_buffer(void)
{
    int n;

    n = write(parent_sockfd[1], bridge, strlen(bridge));
    if (n < 0) {
	error(SYSTEM_ERROR, "send to parent buffer ", NIL,0);
    }
    memset(bridge, 0, sizeof(bridge));
}

void send_to_child(int n, int x)
{
    int m;

    memset(bridge, 0, sizeof(bridge));
    strcpy(bridge, GET_NAME(x));
    m = write(child_sockfd[n], bridge, strlen(bridge));
    memset(bridge, 0, sizeof(bridge));
    if (m < 0) {
	error(SYSTEM_ERROR, "send to child", NIL,0);
    }
}

int receive_from_child(int n)
{
    int m, i, j;
    char sub_buffer[256], sub_buffer1[256 + 2];

    // receive from child
  reread:
    memset(bridge, 0, sizeof(bridge));
    m = read(child_sockfd[n], bridge, sizeof(bridge) - 1);
    if (m < 0) {
	error(SYSTEM_ERROR, "receive from child", makeint(n),0);
    }

  retry:
    if (bridge[0] == '\x02') {
	i = 0;
	while (bridge[i + 1] != '\x03') {
	    sub_buffer[i] = bridge[i + 1];
	    i++;
	}
	if (!(child_flag && parent_flag)) {
	    sub_buffer[i] = 0;
	    printf("%s", sub_buffer);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sprintf(sub_buffer1, "\x02%s\x03", sub_buffer);
	    send_to_parent(makestr(sub_buffer1));
	}
	j = 0;
	i = i + 2;
	while (bridge[j + i] != 0) {
	    bridge[j] = bridge[j + i];
	    j++;
	}
	bridge[j] = 0;
	if (bridge[0] == 0)
	    goto reread;
	else
	    goto retry;
    } else if (bridge[0] == '\x15') {
	if (!(child_flag && parent_flag)) {
	    error(SYSTEM_ERROR, "in child", makeint(n),0);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sub_buffer1[0] = '\x15';
	    send_to_parent(makestr(sub_buffer1));
	}
    } else {
	return (makestr(bridge));
    }

    return (0);
}




int receive_from_child_or(int n)
{
    int i, m, res;

    //initialize -1 (not received)
    for (i = 0; i < n; i++) {
	child_result[i] = -1;
    }
    res = receive_from_child_or1(n);

    // kill not received child
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1) {
	    // send child stop signal
	    memset(bridge, 0, sizeof(bridge));
	    bridge[0] = '\x11';
	    m = write(child_sockfd[i], bridge, strlen(bridge));
	    if (m < 0) {
		error(SYSTEM_ERROR, "receive from child", NIL,0);
	    }
	    // receive result and ignore
	    while ((m =
		    read(child_sockfd[i], bridge,
			 sizeof(bridge) - 1)) == 0) {
	    }
	}
    }

    return (res);
}


int receive_from_child_or1(int n)
{
    int m, i;

    // receive from child
    m = 0;
  retry:
    memset(bridge, 0, sizeof(bridge));
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1) {
	    m = read(child_sockfd[i], bridge, sizeof(bridge));
	}
	if (m < 0) {
	    error(SYSTEM_ERROR, "receive from child", makeint(i),0);
	} else if (m > 0) {
	    child_result[i] = receive_from_child_or2(i);
	}
    }

    //if find true return it.
    for (i = 0; i < n; i++) {
	if (child_result[i] != -1
	    && strcmp(GET_NAME(child_result[i]), "fail.") != 0)
	    return (child_result[i]);
    }


    //if exist not received result, goto retry
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1)
	    goto retry;
    }

    // if not exist YES, return fail.
    return (makeatom("fail", SYS));
}

int receive_from_child_or2(int n)
{
    char sub_buffer[256], sub_buffer1[256 + 2];
    int i, j;

  retry:
    if (bridge[0] == '\x02') {
	i = 0;
	while (bridge[i + 1] != '\x03') {
	    sub_buffer[i] = bridge[i + 1];
	    i++;
	}
	if (!(child_flag && parent_flag)) {
	    sub_buffer[i] = 0;
	    printf("%s", sub_buffer);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sprintf(sub_buffer1, "\x02%s\x03", sub_buffer);
	    send_to_parent(makestr(sub_buffer1));
	}
	j = 0;
	i = i + 2;
	while (bridge[j + i] != 0) {
	    bridge[j] = bridge[j + i];
	    j++;
	}
	bridge[j] = 0;
	if (bridge[0] == 0)
	    return (-1);
	else
	    goto retry;

    } else if (bridge[0] == '\x15') {
	if (!(child_flag && parent_flag)) {
	    error(SYSTEM_ERROR, "in child", makeint(n),0);
	} else {
	    memset(sub_buffer1, 0, sizeof(sub_buffer1));
	    sub_buffer1[0] = '\x15';
	    send_to_parent(makestr(sub_buffer1));
	}
    } else {
	return (makestr(bridge));
    }

    return (0);
}



// Thread for child lisp receiver
void *receiver(void *arg)
{
    int i;
    char sub_buffer[256];

    while (1) {
	if (receiver_exit_flag)
	    goto exit;

	if (child_busy_flag) {
	    receive_from_parent();
	  retry:
	    if (bridge[0] == '\x11') {
		// child stop 
		if (!(child_flag && parent_flag)) {
		    memset(sub_buffer, 0, sizeof(sub_buffer));
		    sub_buffer[0] = '\x11';
		    for (i = 0; i < child_num; i++)
			send_to_child(i, makestr(sub_buffer));
		}
		ctrl_c_flag = 1;
	    } else if (bridge[0] == '\x12') {
		// child pause 
		if (!(child_flag && parent_flag)) {
		    memset(sub_buffer, 0, sizeof(sub_buffer));
		    sub_buffer[0] = '\x12';
		    for (i = 0; i < child_num; i++)
			send_to_child(i, makestr(sub_buffer));
		}
		pause_flag = 1;
	    } else if (bridge[0] == '\x13') {
		// child resume 
		if (!(child_flag && parent_flag)) {
		    memset(sub_buffer, 0, sizeof(sub_buffer));
		    sub_buffer[0] = '\x11';
		    for (i = 0; i < child_num; i++)
			send_to_child(i, makestr(sub_buffer));
		}
		pause_flag = 0;
	    }

	    if (bridge[1] != 0) {
		int i;
		i = 0;
		while (bridge[i + 1] != 0) {
		    bridge[i] = bridge[i + 1];
		    i++;
		}
		bridge[i] = 0;
		goto retry;
	    }

	}

    }

  exit:
    pthread_exit(NULL);
}


void init_receiver(void)
{
    // create child receiver thread 
    pthread_create(&receiver_thread, NULL, receiver, NULL);

}


int b_dp_create(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);

    if (n == 1) {
	parent_flag = 1;
	child_num = 0;
	arg1 = car(arglist);
	while (!nullp(arg1)) {
	    if (!atomp(car(arg1)))
		error(NOT_ATOM, "dp_create", arg1,th);

	    init_child(child_num, car(arg1));
	    arg1 = cdr(arg1);
	    child_num++;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_create ", arglist,th);
    return (NO);
}

// close all distributed child 
int b_dp_close(int arglist, int rest, int th)
{
    int n, i, exp;

    n = length(arglist);
    if (n == 0) {

	if (parent_flag) {
	    exp = makestr("dp_close.");
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, exp);
	    }
	}

	if (parent_flag) {
	    for (i = 0; i < child_num; i++)
		close(child_sockfd[i]);
	}

	if (child_flag) {
	    printf("N-Prolog exit network mode.\n");
	    close(parent_sockfd[0]);
	    close(parent_sockfd[1]);
	    receiver_exit_flag = 1;
	    shutdown_flag = 1;
	    longjmp(buf, 2);
	}

	child_num = 0;
	parent_flag = 0;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_close ", arglist,0);
    return (NO);

}



int b_dp_prove(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (GET_INT(arg1) >= child_num || GET_INT(arg1) < 0)
	    error(WRONG_ARGS, "dp_prove", arg1,th);

	send_to_child(GET_INT(arg1), pred_to_str(arg2));
	res =
	    convert_to_variant(str_to_pred
			       (receive_from_child(GET_INT(arg1))), th);
	if (prove_all(res, sp[th], th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_prove ", arglist,th);
    return (NO);
}

// parent Prolog
int b_dp_transfer(int arglist, int rest, int th)
{
    int n, arg1, pred1, pred2, i, m;
    FILE *file;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1))
	    error(NOT_STR, "dp_transfer", arg1,th);

	file = fopen(GET_NAME(arg1), "r");
	if (!file) {
	    error(CANT_OPEN, "dp_transfer", arg1,th);
	}

	pred1 = list2(makeatom("dp_receive", SYS), arg1);

	for (i = 0; i < child_num; i++) {
	    send_to_child(i, pred_to_str(pred1));

	    int bytes_read;
	    while ((bytes_read =
		    fread(transfer, sizeof(char), sizeof(transfer),
			  file)) > 0) {
		m = write(child_sockfd[i], transfer, bytes_read);
		if (m < 0) {
		    error(SYSTEM_ERROR, "dp_transfer", NIL,th);
		}
	    }
	    memset(transfer, 0, sizeof(transfer));
	    transfer[0] = 0x15;
	    m = write(child_sockfd[i], transfer, 1);
	    if (m < 0) {
		error(SYSTEM_ERROR, "dp_transfer", NIL,th);
	    }
	    receive_from_child(i);
	    fseek(file, 0, SEEK_SET);
	}
	fclose(file);
	if (parent_flag) {
	    pred2 = list2(makeatom("dp_transfer", SYS), arg1);
	    for (i = 0; i < child_num; i++)
		send_to_child(i, pred_to_str(pred2));
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_transfer ", arglist,th);
    return (NO);
}

// child Prolog
int b_dp_receive(int arglist, int rest, int th)
{
    int n, arg1;
    FILE *file;

    n = length(arglist);
    if (n == 1) {
	child_busy_flag = 0;
	arg1 = car(arglist);


	file = fopen(GET_NAME(arg1), "w");
	if (!file) {
	    error(CANT_OPEN, "dp_receive", arg1,th);
	}

	int bytes_received;
	while ((bytes_received =
		read(parent_sockfd[1], transfer, sizeof(transfer))) > 0) {
	    if (transfer[bytes_received - 1] == 0x15) {
		transfer[bytes_received - 1] = 0;
		fwrite(transfer, sizeof(char), bytes_received - 1, file);
		break;
	    }
	    fwrite(transfer, sizeof(char), bytes_received, file);
	}
	child_busy_flag = 1;
	fclose(file);
	return (YES);
    }
    error(ARITY_ERR, "dp_receive ", arglist,th);
    return (NO);
}

int b_dp_consult(int arglist, int rest, int th)
{
    int arg1, pred1, pred2, i;

    arg1 = car(arglist);
    if (!atomp(arg1))
	error(NOT_STR, "dp_consult", arg1,th);

    pred1 = list2(makeatom("reconsult", SYS), arg1);
    prove_all(pred1, sp[th], th);

    if (parent_flag) {
	pred2 = list2(makeatom("dp_consult", SYS), arg1);
	for (i = 0; i < child_num; i++) {
	    send_to_child(i, pred_to_str(pred2));
	    receive_from_child(i);
	}
    }
    return (YES);
    error(ARITY_ERR, "dp_consult ", arglist,th);
    return (NO);
}

int b_dp_compile(int arglist, int rest, int th)
{
    int n, arg1, pred1, pred2, i;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1))
	    error(NOT_STR, "dp_compile", arg1,th);

	pred1 = list2(makeatom("compile_file", PRED), arg1);
	prove_all(pred1, sp[th], th);

	if (parent_flag) {
	    pred2 = list2(makeatom("dp_compile", SYS), arg1);
	    for (i = 0; i < child_num; i++) {
		send_to_child(i, pred_to_str(pred2));
		receive_from_child(i);
	    }
	}
	return (YES);
    }
    error(ARITY_ERR, "dp_compile ", arglist,th);
    return (NO);
}


int b_dp_report(int arglist, int rest, int th)
{
    int n, arg1;
    char sub_buffer[STRSIZE];

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!stringp(arg1))
	    error(NOT_STR, "dp_report", arg1,th);

	memset(sub_buffer, 0, sizeof(sub_buffer));
	sprintf(sub_buffer, "\x02%s\x03", GET_NAME(arg1));
	send_to_parent(makestr(sub_buffer));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_report ", arglist,th);
    return (NO);
}

int b_dp_and(int arglist, int rest, int th)
{
    int n, arg1, m, i, j, pred, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	m = length(arg1);
	if (m > child_num)
	    error(ILLEGAL_ARGS, "dp_and ", arg1,th);

	i = 0;
	while (!nullp(arg1)) {
	    pred = deref(car(arg1), th);
	    send_to_child(i, pred_to_str(pred));
	    arg1 = cdr(arg1);
	    i++;
	}
	for (i = 0; i < m; i++) {
	    res =
		convert_to_variant(str_to_pred(receive_from_child(i)), th);
	    if (prove_all(res, sp[th], th) == NO) {
		for (j = i; j < m; j++) {
		    res =
			convert_to_variant(str_to_pred
					   (receive_from_child(j)), th);
		}
		return (NO);
	    }
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_and ", arglist,th);
    return (NO);
}

int b_dp_or(int arglist, int rest, int th)
{
    int n, arg1, m, i, pred, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	m = length(arg1);
	if (m > child_num)
	    error(ILLEGAL_ARGS, "dp_or ", arg1,th);

	i = 0;
	while (!nullp(arg1)) {
	    pred = deref(car(arg1), th);
	    send_to_child(i, pred_to_str(pred));
	    arg1 = cdr(arg1);
	    i++;
	}
	res =
	    convert_to_variant(str_to_pred(receive_from_child_or(m)), th);
	if (prove_all(res, sp[th], th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_or ", arglist,th);
    return (NO);
}

int b_dp_countup(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	proof[th] = proof[th] + GET_INT(arg1);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_countup ", arglist,th);
    return (NO);
}

int b_dp_parent(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == th) {

	if (parent_flag)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "dp_parent ", arglist,th);
    return (NO);
}

int b_dp_child(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == th) {

	if (!parent_flag && child_flag)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "dp_parent ", arglist,th);
    return (NO);
}

int b_dp_wait(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "dp_wait ", arg1,th);
	if (negativep(arg1))
	    error(WRONG_ARGS, "dp_wait ", arg1,th);
	if (GET_INT(arg1) > 60)
	    error(WRONG_ARGS, "dp_wait ", arg1,th);

	sleep(GET_INT(arg1));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_wait ", arglist,th);
    return (NO);
}

int b_dp_pause(int arglist, int rest, int th)
{
    int n, arg1;
    char sub_buffer[256];

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "dp_pause ", arg1,th);
	if (negativep(arg1))
	    error(WRONG_ARGS, "dp_pause ", arg1,th);
	if (GET_INT(arg1) >= child_num)
	    error(WRONG_ARGS, "dp_pause ", arg1,th);


	memset(sub_buffer, 0, sizeof(sub_buffer));
	sub_buffer[0] = 0x11;
	send_to_child(GET_INT(arg1), makestr(sub_buffer));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_pause ", arglist,th);
    return (NO);
}

int b_dp_resume(int arglist, int rest, int th)
{
    int n, arg1;
    char sub_buffer[256];

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "dp_resume ", arg1,th);
	if (negativep(arg1))
	    error(WRONG_ARGS, "dp_resume ", arg1,th);
	if (GET_INT(arg1) >= child_num)
	    error(WRONG_ARGS, "dp_resume ", arg1,th);

	memset(sub_buffer, 0, sizeof(sub_buffer));
	sub_buffer[0] = 0x11;
	send_to_child(GET_INT(arg1), makestr(sub_buffer));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dp_resume ", arglist,th);
    return (NO);
}


// multi thread parallel functions 
void mt_enqueue(int n)
{
    pthread_mutex_lock(&mutex);
    mt_queue[mt_queue_pt] = n;
    mt_queue_pt++;
    pthread_cond_signal(&mt_cond_queue);
    pthread_mutex_unlock(&mutex);
}

int mt_dequeue(int arg)
{
    int num, i;

    if (mt_queue_pt == 0) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_queue, &mutex);
	pthread_mutex_unlock(&mutex);
    }

    num = mt_queue[0];
    mt_queue_pt--;
    for (i = 0; i < mt_queue_pt; i++) {
	mt_queue[i] = mt_queue[i + 1];
    }
    pthread_mutex_lock(&mutex);
    para_input[num] = copy_work(convert_to_variable(arg, num), num);
    para_output[num] = NIL;
    pthread_cond_signal(&mt_cond_para[num]);
    pthread_mutex_unlock(&mutex);

    return (num);
}

int eval_para(int arg)
{
    int num;

    num = mt_dequeue(arg);
    return (num);
}

int query_thread(int x, int th)
{
    variables[th] = listreverse(unique(varslist(x)));
    return (prove_all(addask(x,th), sp[th], th));
}

void *parallel(void *arg)
{
    int num = *(int *) arg;

    while (1) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_para[num], &mutex);
	pthread_mutex_unlock(&mutex);
	if (parallel_exit_flag)
	    goto exit;

	int ret = setjmp(buf3);
	if (ret == 0){
	para_output[num] = query_thread(para_input[num], num);
	}
	else if(ret == 1){
		para_output[num] = -1; // error
		ret = 0;
	}
	mt_enqueue(num);
	pthread_mutex_lock(&mutex);
	active_thread--;
	pthread_mutex_unlock(&mutex);
	if (active_thread == 0) {
	    pthread_mutex_lock(&mutex);
	    pthread_cond_signal(&mt_cond_main);
	    pthread_mutex_unlock(&mutex);
	}
    }
  exit:
    pthread_exit(NULL);
}

void init_para(void)
{
    int i;

    // mt_queue[1,2,3,4,...] worker thread number 
    // mt_para_thread[1] has worker-number 1
    // mt_para_thread[2] has worker-number 2 ... 
    //
    for (i = 0; i < mt_queue_num; i++) {
	mt_queue[i] = i + 1;
    }

    for (i = 0; i < mt_queue_num; i++) {
	pthread_create(&mt_para_thread[i + 1], NULL, parallel,
		       &mt_queue[i]);
    }

    mt_queue_pt = mt_queue_num;
}


void exit_para(void)
{
    int i;

    parallel_exit_flag = 1;
    for (i = 1; i <= mt_queue_num; i++) {
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&mt_cond_para[i]);
	pthread_mutex_unlock(&mutex);
    }

}


int b_mt_create(int arglist, int rest, int th)
{
    int n, arg1, i, m;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "mt-create", arg1,th);
	if (GET_INT(arg1) > THREADSIZE)
	    error(WRONG_ARGS, "mt-create", arg1,th);

	if (thread_flag)
	    return (YES);

	mt_queue_num = GET_INT(arg1);
	thread_num = mt_queue_num;
	thread_flag = 1;
	init_para();
	m = thread_num + 1;
	for (i = 0; i < m; i++) {
	    wp_min[i] = HEAPSIZE + 1 + (CELLSIZE - HEAPSIZE) / m * i;
	    wp_max[i] = wp_min[i] + (CELLSIZE - HEAPSIZE) / m;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "mt_create ", arglist,th);
    return (NO);
}

int b_mt_close(int arglist, int rest, int th)
{
    int n;
    n = length(arglist);
    if (n == 0) {

	exit_para();
	thread_flag = 0;
	mt_queue_num = 0;
	thread_num = 1;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "mt_close ", arglist,th);
    return (NO);
}


int b_mt_and(int arglist, int rest, int th)
{
    int n, arg1, i, j, pred;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (length(arg1) > mt_queue_num)
	    error(WRONG_ARGS, "mt_and", arg1,th);


	i = 0;
	while (!nullp(arg1)) {
	    pred = convert_to_variable(car(arg1), th);
	    eval_para(pred);
	    arg1 = cdr(arg1);
	    i++;
	}

	active_thread = i;
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_main, &mutex);
	pthread_mutex_unlock(&mutex);


	// receive result from each thread
	for (j = 1; j <= i; j++) {
	    if (para_output[j] == NO)
		return (NO);
		else if(para_output[j] == -1)
		longjmp(buf, 1);

	}

	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "mt_and ", arglist,th);
    return (NO);
}

int b_mt_or(int arglist, int rest, int th)
{
    int n, arg1, i, j;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (length(arg1) > mt_queue_num)
	    error(WRONG_ARGS, "mt_and", arg1,th);


	i = 0;
	while (!nullp(arg1)) {
	    eval_para(car(arg1));
	    arg1 = cdr(arg1);
	    i++;
	}
	active_thread = i;
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_main, &mutex);
	pthread_mutex_unlock(&mutex);

	// receive result from each thread
	for (j = 1; j <= i; j++) {
	    if (para_output[j] == YES)
		goto succ;
		else if(para_output[j] == -1)
		longjmp(buf, 1);

	}
	return (NO);

      succ:
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "mt_or ", arglist,th);
    return (NO);
}


int b_mt_prove(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	return (prove_all(arg2, sp[GET_INT(arg1)], GET_INT(arg1)));
    }
    error(ARITY_ERR, "mt_prove ", arglist,th);
    return (NO);
}
