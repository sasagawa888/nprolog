#include <string.h>
#ifdef __arm__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#include "npl.h"

//-----------JUMP project(builtin for compiler)------------

int b_reconsult_predicate(int arglist, int rest)
{
    int n, arg1, lis, save1;

    n = length(arglist);
    if (n == 1) {
	save1 = sp;
	arg1 = deref(car(arglist));
	if (!wide_variable_p(arg1))
	    error(NOT_VAR, "n_reconsult_predicate ", arg1);

	lis = reverse(reconsult_list);
	while (!nullp(lis)) {
	    unify(arg1, car(lis));
	    if (prove_all(rest, sp) == YES)
		return (YES);

	    lis = cdr(lis);
	    unbind(save1);
	}
	unbind(save1);
	return (NO);
    }
    return (NO);
}

int b_reconsult_abolish(int arglist, int rest)
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
	return (prove_all(rest, sp));
    }
    return (NO);
}

int b_filename(int arglist, int rest)
{
    int n, arg1, arg2, pos, len;
    char str1[STRSIZE];

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist));
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
		if (unify(arg2, makeconst(str1)) == YES)
		    return (prove_all(rest, sp));
		else
		    return (NO);
	    }
	if (unify(arg1, arg2) == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}

//convert atom for C language function name
int b_atom_convert(int arglist, int rest)
{
    int n, arg1, arg2, pos1;
    char str1[ATOMSIZE], str2[ATOMSIZE], str3[ATOMSIZE], str4[ATOMSIZE];
    //   str1=input   str2=unicode-buffer str3=usc4-buffer str4 = output-string 
    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist));
	arg2 = deref(cadr(arglist));

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
	unify(arg2, makeconst(str4));
	return (prove_all(rest, sp));
    }
    return (NO);
}

int b_arity_count(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist));
	arg2 = cadr(arglist);

	if (unify(arg2, listreverse(GET_ARITY(arg1))) == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}


int b_generate_all_variable(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist));
	arg2 = cadr(arglist);
	if (unify(arg2, generate_all_variable(GET_CAR(arg1))) == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}

int b_generate_variable(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist));
	arg2 = cadr(arglist);
	if (unify(arg2, generate_variable(arg1)) == YES)
	    return (prove_all(rest, sp));
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

int b_compiler_anoymous(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist));
	if (compiler_anoymous_p(arg1))
	    return (prove_all(rest, sp));
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



int b_compiler_variable(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist));
	if (compiler_variable_p(arg1))
	    return (prove_all(rest, sp));
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

int b_variable_convert(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = deref(car(arglist));
	arg2 = cadr(arglist);

	if (unify(arg2, variable_convert1(arg1)) == YES)
	    return (prove_all(rest, sp));
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

int b_clause_with_arity(int arglist, int rest)
{
    int n, arg1, arg2, arg3, l, clause, clauses, res;

    n = length(arglist);
    if (n == 3) {
	arg1 = deref(car(arglist));
	arg2 = deref(cadr(arglist));
	arg3 = deref(caddr(arglist));
	if (!singlep(arg1))
	    error(NOT_ATOM, "n_clause_with_arity", arg1);
	if (!integerp(arg2))
	    error(NOT_INT, "n_clause_with_arity", arg2);

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
	unify(res, arg3);
	return (prove_all(rest, sp));
    }
    return (NO);
}

int b_error(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	int ret1 = setjmp(buf1);


	if (ret1 == 0) {
	    check_flag = 1;
	    prove_all(arg1, sp);
	    check_flag = 0;
	    printf("Not error: ");
	    print(arg1);
	    return (NO);
	} else if (ret1 == 1) {
	    ret1 = 0;
	    check_flag = 0;
	    if (unify(arg2, makeint(error_code)) == YES) {
		if (prove_all(rest, sp) == YES)
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
    error(ARITY_ERR, "n_error ", arglist);
    return (NO);
}

int b_property(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (builtinp(arg1)) {
	    if (unify(arg2, makeconst("builtin")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (predicatep(arg1)) {
	    if (unify(arg2, makeconst("predicate")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (functionp(arg1)) {
	    if (unify(arg2, makeconst("function")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (compiledp(arg1)) {
	    if (unify(arg2, makeconst("compiled")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (operationp(arg1)) {
	    if (unify(arg2, makeconst("operation")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (operatorp(arg1)) {
	    if (unify(arg2, makeconst("operator")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (user_operator_p(arg1)) {
	    if (unify(arg2, makeconst("userop")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (user_operation_p(arg1)) {
	    if (unify(arg2, makeconst("userop")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (singlep(arg1) && findatom(arg1, USER) == 1) {
	    if (unify(arg2, makeconst("userop")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else if (structurep(arg1) && GET_AUX(arg1) != LIST &&
		   IS_INCELL(car(arg1)) && findatom(car(arg1), USER) == 1)
	{
	    if (unify(arg2, makeconst("userop")) == YES)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else
	    return (NO);

    }
    return (NO);
}

int b_bignum(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (bignump(arg1))
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}

int b_longnum(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (longnump(arg1))
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}

int b_findatom(int arglist, int rest)
{
    int n, arg1, arg2, arg3, res;

    n = length(arglist);
    if (n == 3) {
	arg1 = deref(car(arglist));	//atom
	arg2 = deref(cadr(arglist));	//property
	arg3 = deref(caddr(arglist));	//address

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
	    error(ILLEGAL_ARGS, "findatom ", arg2);

	if (unify(arg3, makeint(res)) == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}

int b_defined_predicate(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist));

	if (predicatep(arg1)) {
	    if (atomp(arg1) && GET_CAR(arg1) != NIL)
		return (prove_all(rest, sp));
	    else if (structurep(arg1) && GET_CAR(car(arg1)) != NIL)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else
	    return (NO);
    }
    return (NO);
}

int b_defined_userop(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = deref(car(arglist));

	if (user_operation_p(arg1) || user_operator_p(arg1)) {
	    if (atomp(arg1) && GET_CAR(arg1) != NIL)
		return (prove_all(rest, sp));
	    else if (structurep(arg1) && GET_CAR(car(arg1)) != NIL)
		return (prove_all(rest, sp));
	    else
		return (NO);
	} else
	    return (NO);
    }
    return (NO);
}

int b_get_execute(int arglist, int rest)
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
	if (unify(arg1, res) == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    return (NO);
}

int b_heapdump(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "heapd ", arg1);
	if (!integerp(arg2))
	    error(NOT_INT, "heapd ", arg2);
	if (greaterp(arg1, arg2))
	    error(WRONG_ARGS, "heapd ", wlist2(arg1, arg2));

	heapdump(get_int(arg1), get_int(arg2));
	return (prove_all(rest, sp));
    }
    return (NO);
}

int b_existerrors(int arglist, int rest)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (arg1 != YES && arg1 != NO && !wide_variable_p(arg1))
	    error(ILLEGAL_ARGS, "existerrors ", arg1);
	if (arg2 != YES && arg2 != NO && !wide_variable_p(arg2))
	    error(ILLEGAL_ARGS, "existerrors ", arg1);

	res = unify(arg1, exist_flag);
	exist_flag = arg2;
	if (res == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    error(ARITY_ERR, "existerrors ", arglist);
    return (NO);
}

int b_has_cut(int arglist, int rest)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (has_cut_p(arg1))
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    error(ARITY_ERR, "n_has_cut ", arglist);
    return (NO);
}

int b_before_cut(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (has_cut_p(arg1)) {
	    unify(arg2, before_cut(arg1));
	    return (prove_all(rest, sp));
	} else
	    return (NO);
    }
    error(ARITY_ERR, "n_before_cut ", arglist);
    return (NO);
}

int b_after_cut(int arglist, int rest)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (has_cut_p(arg1)) {
	    unify(arg2, after_cut(arg1));
	    return (prove_all(rest, sp));
	} else
	    return (NO);
    }
    error(ARITY_ERR, "n_after_cut ", arglist);
    return (NO);
}

int exec_all(int goals, int bindings)
{

    if (nullp(goals))
	return (YES);
    /* ,(;(D1;D2),Xs) */
    else if (listp(goals) && car(cadr(goals)) == OR) {
	if (exec_all(cadr(cadr(goals)), bindings) == YES)
	    return (exec_all(caddr(goals), bindings));
	else if (exec_all(caddr(cadr(goals)), bindings) == YES)
	    return (exec_all(caddr(goals), bindings));
	else
	    return (NO);
    } else if (car(goals) != AND)
	return (exec(goals, bindings, NIL));
    else {
	return (exec(cadr(goals), bindings, caddr(goals)));
    }

    return (NO);
}

int exec(int goal, int bindings, int rest)
{
    int res;

    proof++;
    goal = deref(goal);

    if (nullp(goal)) {
	return (exec_all(rest, bindings));
    } else if (builtinp(goal)) {
	if (atomp(goal)) {
	    if ((res = (GET_SUBR(goal)) (NIL, rest)) == YES)
		return (YES);

	    return (res);
	} else {
	    if ((res = (GET_SUBR(car(goal))) (cdr(goal), rest)) == YES)
		return (YES);

	    return (res);
	}
    } else if (compiledp(goal)) {
	if (atomp(goal)) {
	    if ((GET_SUBR(goal)) (NIL, rest) == YES)
		return (YES);

	    return (NO);
	} else {
	    if ((GET_SUBR(car(goal))) (cdr(goal), rest) == YES)
		return (YES);

	    return (NO);
	}
    }
    return (NO);
}



//----------for Raspberry PI
#ifdef __arm__
int b_wiringpi_setup_gpio(int arglist, int rest)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	wiringPiSetupGpio();
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "wiringpi_setup_gpio ", arglist);
    return (NO);
}

int b_wiringpi_spi_setup_ch_speed(int arglist, int rest)
{
    int n, arg1, arg2, x, y;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "wiringpi_spi_setup_ch_speed ", arg1);
	if (!integerp(arg2))
	    error(NOT_INT, "wiringpi_spi_setup_ch_speed ", arg2);


	x = GET_INT(arg1);
	y = GET_INT(arg2);
	wiringPiSPISetup(x, y);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "wiringpi_spi_setup_ch_speed ", arglist);
    return (NO);
}

int b_pwm_set_mode(int arglist, int rest)
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
	    error(WRONG_ARGS, "pwm_set_mode", arg1);

	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "pwm_set_mode ", arglist);
    return (NO);
}

int b_pwm_set_range(int arglist, int rest)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pwm_set_range", arg1);

	x = GET_INT(arg1);
	pwmSetRange(x);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "pwm_set_range ", arglist);
    return (NO);
}

int b_pwm_set_clock(int arglist, int rest)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pwm_set_clock", arg1);

	x = GET_INT(arg1);
	pwmSetClock(x);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "pwm_set_clock ", arglist);
    return (NO);
}

int b_pin_mode(int arglist, int rest)
{
    int n, arg1, arg2, x;


    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pin_mode ", arg1);

	x = GET_INT(arg1);
	if (arg2 == makeconst("intput"))
	    pinMode(x, INPUT);
	else if (arg2 == makeconst("output"))
	    pinMode(x, OUTPUT);
	else if (arg2 == makeconst("pwm_output"))
	    pinMode(x, PWM_OUTPUT);
	else
	    error(WRONG_ARGS, "pin_mode", arg2);

	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "pin_mode ", arglist);
    return (NO);
}

int b_digital_write(int arglist, int rest)
{
    int n, arg1, arg2, x, y;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "digital_write ", arg1);
	if (!integerp(arg2))
	    error(NOT_INT, "digital_write ", arg2);

	x = GET_INT(arg1);
	y = GET_INT(arg2);
	digitalWrite(x, y);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "digital_write ", arglist);
    return (NO);
}

int b_digital_write_byte(int arglist, int rest)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "digital_write_byte ", arg1);

	x = GET_INT(arg1);
	digitalWriteByte(x);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "digital_write_byte ", arglist);
    return (NO);
}

int b_pull_up_dn_control(int arglist, int rest)
{
    int n, arg1, arg2, x, y;


    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "pull_up_dn_control ", arg1);
	if (!integerp(arg2))
	    error(NOT_INT, "pull_up_dn_control ", arg2);

	x = GET_INT(arg1);
	y = GET_INT(arg2);
	pullUpDnControl(x, y);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "pull_up_dn_control ", arglist);
    return (NO);
}

int b_digital_read(int arglist, int rest)
{
    int n, arg1, arg2, x, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "digital_read", arg1);

	x = GET_INT(arg1);
	res = digitalRead(x);
	if (unify(arg2, makeint(res)) == YES)
	    return (prove_all(rest, sp));
	else
	    return (NO);
    }
    error(ARITY_ERR, "digital_read ", arglist);
    return (NO);
}

int b_delay(int arglist, int rest)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "delay", arg1);

	x = GET_INT(arg1);
	delay(x);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "delay ", arglist);
    return (NO);
}

int b_delay_microseconds(int arglist, int rest)
{
    int n, arg1, x;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "delay_microseconds ", arg1);

	x = GET_INT(arg1);
	delayMicroseconds(x);
	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "delay_microseconds ", arglist);
    return (NO);
}

int b_timer_microseconds(int arglist, int rest)
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
	    unify(arg1, makeflt(timer));
	else
	    error(ILLEGAL_ARGS, "timer_microseconds ", arg1);

	return (prove_all(rest, sp));
    }
    error(ARITY_ERR, "timer_microseconds ", arglist);
    return (NO);
}


#endif


/* distributed parallel */
void init_parent(void)
{
	
    // create socket
    sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd[0] < 0) {
	error(SYSTEM_ERROR, "init parent", NIL);
    }
	
    // initialize parent_addr
    memset((char *) &parent_addr, 0, sizeof(parent_addr));
    parent_addr.sin_family = AF_INET;
    parent_addr.sin_addr.s_addr = INADDR_ANY;
    parent_addr.sin_port = htons(PORT);

    // bind socket
    if (bind
	(sockfd[0], (struct sockaddr *) &parent_addr,
	 sizeof(parent_addr)) < 0) {
	error(SYSTEM_ERROR, "init parent", NIL);
    }
	
}

void init_child(int n, int x)
{	

    // create socket
    sockfd[n] = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd[n] < 0) {
	error(SYSTEM_ERROR, "dp_create", makeint(n));
    }

    // initialize child_addr
    memset((char *) &child_addr[n], 0, sizeof(child_addr[n]));
    child_addr[n].sin_family = AF_INET;
    child_addr[n].sin_port = htons(PORT);

    if (inet_pton(AF_INET, GET_NAME(x), &child_addr[n].sin_addr) < 0)
	error(SYSTEM_ERROR, "dp_create", x);


    if (connect
	(sockfd[n], (struct sockaddr *) &child_addr[n],
	 sizeof(child_addr[n])) < 0) {
	error(SYSTEM_ERROR, "dp_create", makeint(n));
    }
	
}

void close_socket(void)
{
	/*
    int i;

    if (child_num > 0) {
	for (i = 0; i < child_num; i++)
	    close(sockfd[i]);
    } else if (network_flag) {
	puts("EISL exit network mode.\n");
	close(sockfd[0]);
	close(sockfd[1]);
    }

    receiver_exit_flag = true;
	*/
}

/*
int receive_from_parent(void)
{
    int n;

    if (!connect_flag) {
	//wait conneting
	listen(sockfd[0], 5);
	parent_len = sizeof(parent_addr);
	connect_flag = true;

	// connection from parent
	sockfd[1] =
	    accept(sockfd[0], (struct sockaddr *) &parent_addr,
		   &parent_len);
	if (sockfd[1] < 0) {
	    error(SYSTEM_ERR, "receive from parent", NIL, 0);
	}
    }

    // read message from parent
    memset(buffer3, 0, sizeof(buffer3));
    n = read(sockfd[1], buffer3, sizeof(buffer3) - 1);
    if (n < 0) {
	error(SYSTEM_ERR, "receive from parent", NIL, 0);
    }


    return (make_str(buffer3));

}

void send_to_parent(int x)
{
    int n;

    // send message to parent
    memset(buffer3, 0, sizeof(buffer3));
    strcpy(buffer3, GET_NAME(x));
    n = write(sockfd[1], buffer3, strlen(buffer3));
    if (n < 0) {
	error(SYSTEM_ERR, "send to parent", x, 0);
    }

}

int send_to_child(int n, int x)
{
    int m;

    // send message to child
    memset(buffer3, 0, sizeof(buffer3));
    strcpy(buffer3, GET_NAME(x));
    strcat(buffer3, "\n");
    m = write(sockfd[n], buffer3, strlen(buffer3));
    if (m < 0) {
	error(SYSTEM_ERR, "send to child", NIL, 0);
    }
    return (0);
}

int receive_from_child(int n)
{
    int m, i, j;
    char sub_buffer[256];

    // receive from child
  reread:
    memset(buffer3, 0, sizeof(buffer3));
    m = read(sockfd[n], buffer3, sizeof(buffer3) - 1);
    if (m < 0) {
	error(SYSTEM_ERR, "receive from child", make_int(n), 0);
    }

  retry:
    if (buffer3[0] == '\x02') {
	i = 0;
	while (buffer3[i + 1] != '\x03') {
	    sub_buffer[i] = buffer3[i + 1];
	    i++;
	}
	sub_buffer[i] = 0;
	printf("%s", sub_buffer);
	j = 0;
	i = i + 2;
	while (buffer3[j + i] != 0) {
	    buffer3[j] = buffer3[j + i];
	    j++;
	}
	buffer3[j] = 0;
	if (buffer3[0] == 0)
	    goto reread;
	else
	    goto retry;
    } else if (buffer3[0] == '\x15') {
	error(SYSTEM_ERR, "in child", make_int(n), 0);
    } else {
	return (make_str(buffer3));
    }

    return (0);
}

// opt == 0 find NIL, opt == 1 find non NIL 
int receive_from_child_part(int n, int opt)
{
    int i, m, res;

    //initialize -1 (not received)
    for (i = 0; i < n; i++) {
	child_result[i] = -1;
    }
    res = receive_from_child_part1(n, opt);

    // kill not received child
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1) {
	    // send child stop signal
	    memset(buffer3, 0, sizeof(buffer3));
	    buffer3[0] = '\x11';
	    m = write(sockfd[i], buffer3, strlen(buffer3));
	    if (m < 0) {
		error(SYSTEM_ERR, "receive from child", NIL, 0);
	    }
	    // receive result and ignore
	    while ((m =
		    read(sockfd[i], buffer3, sizeof(buffer3) - 1)) == 0) {
	    }
	}
    }

    return (res);
}


int receive_from_child_part1(int n, int opt)
{
    int m, i;

    // receive from child
  retry:
    memset(buffer3, 0, sizeof(buffer3));
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1) {
	    m = read(sockfd[i], buffer3, sizeof(buffer3));
	}
	if (m < 0) {
	    error(SYSTEM_ERR, "receive from child", make_int(i), 0);
	} else if (m > 0) {
	    child_result[i] = receive_from_child_part2(i);
	}
    }

    //if find non nil, return it, else retry reading.
    for (i = 0; i < n; i++) {
	if (opt == 1 && child_result[i] > NIL)
	    return (child_result[i]);
	else if (opt == 0 && child_result[i] == NIL)
	    return (child_result[i]);
    }


    //if exist not received result, goto retry
    for (i = 0; i < n; i++) {
	if (child_result[i] == -1)
	    goto retry;
    }

    //if opt==1 and all results are nil, return nil
    //if opt==0 and all returls are non nil,return T
    if (opt == 1)
	return (NIL);
    else if (opt == 0)
	return (T);

    return (0);
}

int receive_from_child_part2(int n)
{
    char sub_buffer[256];
    int i, j;

  retry:
    if (buffer3[0] == '\x02') {
	i = 0;
	while (buffer3[i + 1] != '\x03') {
	    sub_buffer[i] = buffer3[i + 1];
	    i++;
	}
	sub_buffer[i] = 0;
	printf("%s", sub_buffer);
	j = 0;
	i = i + 2;
	while (buffer3[j + i] != 0) {
	    buffer3[j] = buffer3[j + i];
	    j++;
	}
	buffer3[j] = 0;
	if (buffer3[0] == 0)
	    return (-1);
	else
	    goto retry;

    } else if (buffer3[0] == '\x15') {
	error(SYSTEM_ERR, "in child", make_int(n), 0);
    } else {
	return (str_to_sexp(make_str(buffer3)));
    }

    return (0);
}



// Thread for child lisp receiver
void *receiver(void *arg __unused)
{
    int res;

    while (1) {
	if (receiver_exit_flag)
	    goto exit;

	if (child_busy_flag) {
	    res = receive_from_parent();
	    memset(buffer3, 0, sizeof(buffer3));
	    strcpy(buffer3, GET_NAME(res));
	  retry:
	    if (buffer3[0] == '\x11') {
		// child stop 
		exit_flag = 1;
	    } else if (buffer3[0] == '\x12') {
		// child pause 

	    } else if (buffer3[0] == '\x13') {
		// chidl resume 

	    }

	    if (buffer3[1] != 0) {
		int i;
		i = 0;
		while (buffer3[i + 1] != 0) {
		    buffer3[i] = buffer3[i + 1];
		    i++;
		}
		buffer3[i] = 0;
		goto retry;
	    }

	}

    }

  exit:
    pthread_exit(NULL);
}

*/
void init_receiver(void)
{
    // create child receiver thread 
    /*
	pthread_create(&receiver_thread, NULL, receiver, NULL);
	*/
}
/*
int f_dp_eval(int arglist, int th __unused)
{
    int arg1, arg2, res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (GET_INT(arg1) >= child_num || GET_INT(arg1) < 0)
	error(WRONG_ARGS, "dp-eval", arg1, 0);

    send_to_child(GET_INT(arg1), sexp_to_str(arg2));
    res = str_to_sexp(receive_from_child(GET_INT(arg1)));
    return (res);
}

// parent lisp 
int f_dp_transfer(int arglist, int th)
{
    int arg1, exp, i, m;
    FILE *file;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-transfer", arg1, th);

    file = fopen(GET_NAME(arg1), "r");
    if (!file) {
	error(CANT_OPEN, "dp-transfer", arg1, th);
    }

    exp = list2(make_sym("dp-receive"), arg1);

    for (i = 0; i < child_num; i++) {
	send_to_child(i, sexp_to_str(exp));

	int bytes_read;
	while ((bytes_read =
		fread(buffer3, sizeof(char), sizeof(buffer3), file)) > 0) {
	    m = write(sockfd[i], buffer3, bytes_read);
	    if (m < 0) {
		error(SYSTEM_ERR, "dp-transfer", NIL, 0);
	    }
	}
	memset(buffer3, 0, sizeof(buffer3));
	buffer3[0] = EOF;
	m = write(sockfd[i], buffer3, 1);
	if (m < 0) {
	    error(SYSTEM_ERR, "dp-transfer", NIL, 0);
	}
	receive_from_child(i);
	fseek(file, 0, SEEK_SET);
    }

    fclose(file);

    return (T);
}

// child lisp 
int f_dp_receive(int arglist, int th)
{
    int arg1;
    FILE *file;

    child_busy_flag = false;
    arg1 = car(arglist);

    file = fopen(GET_NAME(arg1), "w");
    if (!file) {
	error(CANT_OPEN, "dp-receive", arg1, th);
    }

    int bytes_received;
    while ((bytes_received =
	    read(sockfd[1], buffer3, sizeof(buffer3))) > 0) {
	if (buffer3[bytes_received - 1] == EOF) {
	    buffer3[bytes_received - 1] = 0;
	    fwrite(buffer3, sizeof(char), bytes_received - 1, file);
	    break;
	}
	fwrite(buffer3, sizeof(char), bytes_received, file);
    }
    fclose(file);

    return (T);
}


int f_dp_load(int arglist, int th)
{
    int arg1, exp, i;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-load", arg1, th);

    exp = list2(make_sym("LOAD"), arg1);

    for (i = 0; i < child_num; i++) {
	send_to_child(i, sexp_to_str(exp));
	receive_from_child(i);
    }

    eval(exp, 0);

    return (T);
}


int f_dp_compile(int arglist, int th)
{
    int arg1, exp, i;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-compile", arg1, th);

    exp = list2(make_sym("COMPILE-FILE"), arg1);

    for (i = 0; i < child_num; i++) {
	send_to_child(i, sexp_to_str(exp));
	receive_from_child(i);
    }

    eval(exp, 0);

    return (T);
}

// fsubr (dp-call fun arg1 arg2 ... argn)
int f_dp_call(int arglist, int th)
{
    int arg1, arg2, temp, res, n, i, args, exp;

    arg1 = car(arglist);	//fun
    arg2 = cdr(arglist);	//args
    n = length(arg2);
    if (n > child_num)
	error(ILLEGAL_ARGS, "dp-call", arg2, th);
    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "dp-call", arglist, th);
	temp = cdr(temp);
    }

    i = 0;
    while (!nullp(arg2)) {
	exp = eval_args(car(arg2));
	send_to_child(i, sexp_to_str(exp));
	arg2 = cdr(arg2);
	i++;
    }

    args = NIL;
    for (i = 0; i < n; i++) {
	args = cons(str_to_sexp(receive_from_child(i)), args);
    }
    args = reverse(args);

    res = apply(eval(arg1, th), args, th);
    return (res);
}


int f_dp_exec(int arglist, int th)
{
    int temp, res, n, i, exp;

    n = length(arglist);
    if (n > child_num)
	error(ILLEGAL_ARGS, "dp-exec", arglist, th);
    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "dp-exec", arglist, th);
	temp = cdr(temp);
    }

    i = 0;
    temp = arglist;
    while (!nullp(temp)) {
	exp = eval_args(car(temp));
	send_to_child(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }

    for (i = 0; i < n; i++) {
	res = str_to_sexp(receive_from_child(i));
    }

    return (res);

}

int f_dp_report(int arglist, int th __unused)
{
    int arg1;
    char sub_buffer[STRSIZE];

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-report", arg1, 0);

    memset(sub_buffer, 0, sizeof(sub_buffer));
    sprintf(sub_buffer, "\x02%s\x03", GET_NAME(arg1));
    send_to_parent(make_str(sub_buffer));
    return (T);
}


int f_dp_part(int arglist, int th)
{
    int temp, res, n, i, exp, opt;

    opt = car(arglist);
    n = length(cdr(arglist));
    if (opt != T && opt != NIL)
	error(ILLEGAL_ARGS, "dp-part", opt, th);
    if (n > child_num)
	error(ILLEGAL_ARGS, "dp-part", cdr(arglist), th);
    temp = cdr(arglist);
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "dp-part", arglist, th);
	temp = cdr(temp);
    }
    i = 0;
    temp = cdr(arglist);
    while (!nullp(temp)) {
	exp = eval_args(car(temp));
	send_to_child(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }
    if (opt == NIL) {
	res = str_to_sexp(receive_from_child_part(n, 0));
    } else if (opt == T) {
	res = str_to_sexp(receive_from_child_part(n, 1));
    }
    return (res);

}

*/