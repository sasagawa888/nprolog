#ifndef __APPLE__
#include <stdio_ext.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "npl.h"

void initbuiltin(void)
{
    definfix(">", b_greater, 700, XFX);
    definfix("<", b_smaller, 700, XFX);
    definfix("=<", b_eqsmaller, 700, XFX);
    definfix(">=", b_eqgreater, 700, XFX);
    definfix("=:=", b_numeq, 700, XFX);
    definfix("=\\=", b_notnumeq, 700, XFX);
    definfix("=/=", b_notnumeq, 700, XFX);
    definfix("@<", b_atsmaller, 700, XFX);
    definfix("@=<", b_ateqsmaller, 700, XFX);
    definfix("@>", b_atgreater, 700, XFX);
    definfix("@>=", b_ateqgreater, 700, XFX);
    definfix("is", b_is, 700, XFX);
    definfix("=", b_unify, 700, XFX);
    definfix("==", b_equalp, 700, XFX);
    definfix("\\==", b_notequalp, 700, XFX);
    definfix("\\=", b_notunify, 700, XFX);
    definfix("=..", b_univ, 700, XFX);
    definfix("->", b_ifthen, 1050, XFY);
    //definfix("\\+", b_not, 900, FY);
    definfix("not", b_not, 900, FY);

    defbuiltin("!", b_cut, 0);
    defbuiltin("%ask", b_ask, -1);
    defbuiltin("abolish", b_abolish, 1);
    defbuiltin("abort", b_abort, 0);
    defbuiltin("ansi_cup", b_ansi_cup, 2);
    defbuiltin("ansi_cuu", b_ansi_cuu, 1);
    defbuiltin("ansi_cud", b_ansi_cud, 1);
    defbuiltin("ansi_cuf", b_ansi_cuf, 1);
    defbuiltin("ansi_cub", b_ansi_cub, 1);
    defbuiltin("ansi_sgr", b_ansi_sgr, 1);
    defbuiltin("ansi_cpr", b_ansi_cpr, 2);
    defbuiltin("ansi_scp", b_ansi_scp, 0);
    defbuiltin("ansi_rcp", b_ansi_rcp, 0);
    defbuiltin("ansi_ed", b_ansi_ed, 0);
    defbuiltin("ansi_el", b_ansi_el, 0);
    defbuiltin("arg", b_arg, 3);
    defbuiltin("arg0", b_arg0, 3);
    defbuiltin("assert", b_assert, 1);
    defbuiltin("asserta", b_asserta, 1);
    defbuiltin("assertz", b_assert, 1);
    defbuiltin("atom_concat", b_atom_concat, 3);
    defbuiltin("atom", b_atom, 1);
    defbuiltin("atom_string", b_atom_string, 2);
    defbuiltin("atomic", b_atomic, 1);
    defbuiltin("bagof", b_bagof, 3);
    defbuiltin("%bagofhelper", b_bagofhelper, -1);
    defbuiltin("break", b_break, 0);
    //defbuiltin("char_code", b_char_code, 2);
    defbuiltin("chdir", b_chdir, 1);
    defbuiltin("close", b_close, 1);
    defbuiltin("clause", b_clause, 2);
    defbuiltin("compare", b_compare, 2);
    //defbuiltin("compound", b_compound, 1);
    defbuiltin("concat", b_concat, 3);
    defbuiltin("consult", b_consult, 1);
    defbuiltin("create", b_create, 2);
    defbuiltin("ctr_set", b_ctr_set, 2);
    defbuiltin("ctr_dec", b_ctr_dec, 2);
    defbuiltin("ctr_inc", b_ctr_inc, 2);
    defbuiltin("ctr_is", b_ctr_is, 2);
    defbuiltin("current_op", b_current_op, 3);
    defbuiltin("current_predicate", b_current_predicate, 1);
    defbuiltin("date", b_date, 1);
    defbuiltin("date_day", b_date_day, 1);
    defbuiltin("dec", b_dec, 2);
    defbuiltin("delete", b_delete, 1);
    defbuiltin("display", b_display, 1);
    defbuiltin("directory", b_directory, 6);
    defbuiltin("debug", b_debug, 0);
    defbuiltin("dup", b_dup, 2);
    defbuiltin("edit", b_edit, 1);
    defbuiltin("end_of_file", b_end_of_file, 0);
    defbuiltin("eq", b_eq, 2);
    defbuiltin("errcode", b_errcode, 1);
    defbuiltin("erase", b_erase, 1);
    defbuiltin("eraseall", b_eraseall, 1);
    defbuiltin("fail", b_fail, 0);
    defbuiltin("fileerrors", b_fileerrors, 2);
    defbuiltin("findall", b_findall, 3);
    defbuiltin("flush", b_flush_output, 0);
    defbuiltin("float", b_real, 1);
    defbuiltin("float_text", b_float_text, 3);
    defbuiltin("functor", b_functor, 3);
    defbuiltin("gc", b_gbc, 0);
    defbuiltin("get", b_get, list2(1, 2));
    defbuiltin("get0", b_get0, list2(1, 2));
    defbuiltin("get0_noecho", b_get0_noecho, 1);
    defbuiltin("get_code", b_get_code, 1);
    defbuiltin("get_byte", b_get_byte, 1);
    //defbuiltin("ground", b_ground, 1);
    defbuiltin("halt", b_halt, 0);
    defbuiltin("heapd", b_heapdump, 2);
    defbuiltin("ifthen", b_ifthen, 2);
    defbuiltin("ifthenelse", b_ifthenelse, 3);
    defbuiltin("inc", b_inc, 2);
    defbuiltin("instance", b_instance, 2);
    defbuiltin("integer", b_integer, 1);
    defbuiltin("int_text", b_int_text, 3);
    defbuiltin("key", b_key, list2(1, 2));
    defbuiltin("keysort", b_keysort, 2);
    defbuiltin("leash", b_leash, 1);
    defbuiltin("length", b_length, 1);
    defbuiltin("listing", b_listing, list3(0, 1, 2));
    defbuiltin("list", b_list, 1);
    defbuiltin("list_text", b_list_text, 2);
    defbuiltin("mkdir", b_mkdir, 1);
    defbuiltin("measure", b_measure, 1);
    defbuiltin("name", b_name, 2);
    defbuiltin("nl", b_nl, list2(0, 1));
    defbuiltin("nonvar", b_nonvar, 1);
    defbuiltin("nospy", b_nospy, 1);
    defbuiltin("notrace", b_notrace, 0);
    defbuiltin("nref", b_nref, 2);
    defbuiltin("nth_ref", b_nth_ref, 3);
    defbuiltin("number", b_number, 1);
    defbuiltin("nth_char", b_nth_char, 3);
    defbuiltin("op", b_op, 3);
    defbuiltin("open", b_open, 3);
    defbuiltin("predicate_property", b_predicate_property, 2);
    defbuiltin("pref", b_pref, 2);
    defbuiltin("put", b_put, 1);
    defbuiltin("reconsult", b_reconsult, 1);
    defbuiltin("read", b_read, list2(1, 2));
    defbuiltin("read_line", b_read_line, 2);
    defbuiltin("read_string", b_read_string, list2(2, 3));
    defbuiltin("real", b_real, 1);
    defbuiltin("record_after", b_record_after, 3);
    defbuiltin("recorda", b_recorda, 3);
    defbuiltin("recordz", b_recordz, 3);
    defbuiltin("recorded", b_recorded, 3);
    defbuiltin("recordh", b_recordh, 4);
    defbuiltin("ref", b_ref, 1);
    defbuiltin("retract", b_retract, 1);
    defbuiltin("retrieveh", b_retrieveh, 3);
    defbuiltin("removeh", b_removeh, 3);
    defbuiltin("removeallh", b_removeallh, 2);
    defbuiltin("rename", b_rename, 2);
    defbuiltin("replace", b_replace, 2);
    defbuiltin("reset_op", b_reset_op, 0);
    defbuiltin("reverse", b_reverse, 2);
    defbuiltin("rmdir", b_rmdir, 1);
    defbuiltin("save", b_save, list2(0, 1));
    defbuiltin("see", b_see, 1);
    defbuiltin("seeing", b_seeing, 1);
    defbuiltin("seen", b_seen, 0);
    defbuiltin("setof", b_setof, 3);
    defbuiltin("shell", b_shell, 1);
    defbuiltin("skip", b_skip, 1);
    defbuiltin("sort", b_sort, 2);
    defbuiltin("statistics", b_statistics, 2);
    defbuiltin("stdin", b_stdin, 2);
    defbuiltin("stdinout", b_stdinout, 3);
    defbuiltin("stdout", b_stdout, 2);
    defbuiltin("string", b_string, 1);
    defbuiltin("string_length", b_string_length, 2);
    defbuiltin("string_term", b_string_term, 2);
    defbuiltin("spy", b_spy, 1);
    defbuiltin("substring", b_substring, 3);
    defbuiltin("syntaxerrors", b_syntaxerrors, 2);
    defbuiltin("system", b_system, 1);
    defbuiltin("tab", b_tab, list2(1, 2));
    defbuiltin("tell", b_tell, 1);
    defbuiltin("telling", b_telling, 1);
    defbuiltin("time", b_time, 1);
    defbuiltin("told", b_told, 0);
    defbuiltin("trace", b_trace, 0);
    defbuiltin("true", b_true, 0);
    defbuiltin("var", b_var, 1);
    defbuiltin("write", b_write, list2(1, 2));
    defbuiltin("writeq", b_writeq, list2(1, 2));

    defbuiltin("call", b_call, 1);
    defbuiltin("repeat", b_repeat, 0);
    defbuiltin("append", b_append, 3);
    defbuiltin("member", b_member, 2);
    defbuiltin("between", b_between, 3);
	defbuiltin("select", b_select, 3);
    defbuiltin("existerrors", b_existerrors, 2);

    //-----Distributed parallel
    defbuiltin("dp_create", b_dp_create, 1);
    defbuiltin("dp_close", b_dp_close, 0);
    defbuiltin("dp_prove", b_dp_prove, 1);
    defbuiltin("dp_and", b_dp_and, 1);
    defbuiltin("dp_or", b_dp_or, 1);
    defbuiltin("dp_transfer", b_dp_transfer, 1);
    defbuiltin("dp_receive", b_dp_receive, -1);
    defbuiltin("dp_compile", b_dp_compile, 1);
    defbuiltin("dp_consult", b_dp_consult, 1);
    defbuiltin("dp_report", b_dp_report, 1);
    defbuiltin("dp_countup", b_dp_countup, -1);
    defbuiltin("dp_parent", b_dp_parent, 0);
    defbuiltin("dp_child", b_dp_child, 0);
    defbuiltin("dp_wait", b_dp_wait, 1);
    defbuiltin("dp_pause", b_dp_pause, 1);
    defbuiltin("dp_resume", b_dp_resume, 1);

    //------multi thread--------------------
    defbuiltin("mt_create", b_mt_create, 1);
    defbuiltin("mt_close", b_mt_close, 1);
    defbuiltin("mt_and", b_mt_and, 1);
    defbuiltin("mt_or", b_mt_or, 1);
    defbuiltin("mt_prove", b_mt_prove, 2);

    //-----JUMP project---------
    defbuiltin("n_reconsult_predicate", b_reconsult_predicate, -1);
    defbuiltin("n_reconsult_abolish", b_reconsult_abolish, -1);
    defbuiltin("n_filename", b_filename, -1);
    defbuiltin("n_atom_convert", b_atom_convert, -1);
    defbuiltin("n_arity_count", b_arity_count, -1);
    defbuiltin("n_compiler_anoymous", b_compiler_anoymous, -1);
    defbuiltin("n_compiler_variable", b_compiler_variable, -1);
    defbuiltin("n_variable_convert", b_variable_convert, -1);
    defbuiltin("n_generate_all_variable", b_generate_all_variable, -1);
    defbuiltin("n_generate_variable", b_generate_variable, -1);
    defbuiltin("n_clause_with_arity", b_clause_with_arity, -1);
    defbuiltin("n_property", b_property, -1);
    defbuiltin("n_bignum", b_bignum, -1);
    defbuiltin("n_longnum", b_longnum, -1);
    defbuiltin("n_findatom", b_findatom, -1);
    defbuiltin("n_defined_predicate", b_defined_predicate, -1);
    defbuiltin("n_defined_userop", b_defined_userop, -1);
    defbuiltin("n_get_execute", b_get_execute, -1);
    defbuiltin("n_error", b_error, -1);
    defbuiltin("n_has_cut", b_has_cut, -1);
    defbuiltin("n_before_cut", b_before_cut, -1);
    defbuiltin("n_after_cut", b_after_cut, -1);


#ifdef __arm__
    defbuiltin("wiringpi_setup_gpio", b_wiringpi_setup_gpio, 2);
    defbuiltin("wiringpi_spi_setup_ch_speed",
	       b_wiringpi_spi_setup_ch_speed, 1);
    defbuiltin("pwm_set_mode", b_pwm_set_mode, 1);
    defbuiltin("pwm_set_range", b_pwm_set_range, 1);
    defbuiltin("pwm_set_clock", b_pwm_set_clock, 1);
    defbuiltin("pin_mode", b_pin_mode, 2);
    defbuiltin("digital_write", b_digital_write, 2);
    defbuiltin("digital_write_byte", b_digital_write_byte, 1);
    defbuiltin("pull_up_dn_control", b_pull_up_dn_control, 2);
    defbuiltin("digital_read", b_digital_read, 1);
    defbuiltin("delay", b_delay, 1);
    defbuiltin("delay_microseconds", b_delay_microseconds, 1);
    defbuiltin("out", b_digital_write, 2);
    defbuiltin("in", b_digital_read, 2);
    defbuiltin("timer_microseconds", b_timer_microseconds, 1);
#endif
    return;
}

int b_length(int arglist, int rest, int th)
{
    int n, arg1, arg2, i, ls, res, save1, save2;
    save2 = sp[th];
    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1) && !nullp(arg1) && !wide_variable_p(arg1))
	    error(NOT_LIST, "length ", arglist, th);
	if (listp(arg1) && length(arg1) == -1
	    && !wide_variable_p(improper_last(arg1)))
	    error(WRONG_ARGS, "length ", arg1, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    error(LESS_THAN_ZERO, "length ", arg2, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "length ", arg2, th);
	if (variablep(arg1) && variablep(arg2) && eqp(arg1, arg2))
	    error(WRONG_ARGS, "length ", arg1, th);

	save1 = wp[th];
	if ((listp(arg1) && length(arg1) != -1) || nullp(arg1)) {
	    if (unify(arg2, makeint(length(arg1)), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (listp(arg1) && length(arg1) == -1
		   && wide_variable_p(improper_last(arg1))) {
	    if (unify(improper_last(arg1), NIL, th) == YES
		&& unify(arg2, makeint(length(improper_butlast(arg1))),
			 th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (integerp(arg2)) {
	    i = GET_INT(arg2);
	    res = NIL;
	    while (i > 0) {
		res = wlistcons(makevariant(th), res, th);
		i--;
	    }
	    if (unify(arg1, res, th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (wide_variable_p(arg1) && wide_variable_p(arg2)) {
	    ls = NIL;
	    i = 0;
	    while (1) {
		unify(arg1, ls, th);
		unify(arg2, makeint(i), th);
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);

		unbind(save2, th);
		i++;
		ls = wlistcons(makevariant(th), ls, th);
	    }
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "length ", arglist, th);
    return (NO);
}


//compiled predicate
int b_repeat(int arglist, int rest, int th)
{
    int n, save1, save2, save3;

    save1 = wp[th];
    save2 = sp[th];
    save3 = ac[th];
    n = length(arglist);
    if (n == 0) {
      loop:
	if (prove_all(rest, sp[th], th) == YES) {
	    return (YES);
	}
	wp[th] = save1;
	unbind(save2, th);
	ac[th] = save3;
	goto loop;
    }

    error(ARITY_ERR, "repeat ", arglist, th);
    return (NO);
}


int b_op(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, weight, type;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);	//priority
	arg2 = cadr(arglist);	//specifier
	arg3 = caddr(arglist);	//operator

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "op ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "op ", arg2, th);
	if (listp(arg3) && length(arg3) == -1)
	    error(INSTANTATION_ERR, "op ", arg3, th);
	if (!integerp(arg1))
	    error(NOT_INT, "op ", arg1, th);
	if (!atomp(arg2))
	    error(NOT_ATOM, "op ", arg2, th);
	if (!atomp(arg3) && !listp(arg3))
	    error(NOT_ATOM, "op ", arg3, th);
	weight = GET_INT(arg1);
	if (!(weight > 0 && weight <= 1200))
	    error(OPE_PRIORITY_ERR, "op ", arg1, th);
	if (arg3 == DOTOBJ)
	    error(MODIFY_OPE_ERR, "op ", arg3, th);
	if (arg3 == AND)
	    error(MODIFY_OPE_ERR, "op ", arg3, th);
	if (arg3 == makeatom("op", OPE))
	    error(MODIFY_OPE_ERR, "op ", arg3, th);

	type = NIL;
	if (arg2 == makeconst("xfx")) {
	    type = XFX;

	} else if (arg2 == makeconst("yfx")) {
	    if (GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
		error(OPE_SPEC_ERR, "op", arg2, th);
	    type = YFX;
	} else if (arg2 == makeconst("xfy")) {
	    if (GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
		error(OPE_SPEC_ERR, "op", arg2, th);
	    type = XFY;
	} else if (arg2 == makeconst("fx"))
	    type = FX;
	else if (arg2 == makeconst("fy"))
	    type = FY;
	else if (arg2 == makeconst("xf")) {
	    if (GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
		GET_OPT(arg3) == XFY)
		error(OPE_SPEC_ERR, "op", arg2, th);
	    type = XF;
	} else if (arg2 == makeconst("yf")) {
	    if (GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
		GET_OPT(arg3) == XFY)
		error(OPE_SPEC_ERR, "op", arg2, th);
	    type = YF;
	} else
	    error(OPE_SPEC_ERR, "op", arg2, th);

	if (singlep(arg3)) {
	    if (operatorp(arg3))
		defoperator(GET_NAME(arg3), NIL, weight, type, 0);
	    else if (builtinp(arg3))
		defoperator(GET_NAME(arg3), NIL, weight, type, 1);
	    else
		defoperator(GET_NAME(arg3), NIL, weight, type, 2);
	} else {
	    while (!nullp(arg3)) {
		if (wide_variable_p(car(arg3)))
		    error(INSTANTATION_ERR, "ope ", car(arg3), th);
		else if (!atomp(car(arg3)) && !operatorp(car(arg3)))
		    error(NOT_ATOM, "ope ", car(arg3), th);
		else if (operatorp(car(arg3)))
		    defoperator(GET_NAME(arg3), NIL, weight, type, 0);
		else
		    defoperator(GET_NAME(car(arg3)), NIL, weight, type, 2);

		arg3 = cdr(arg3);
	    }
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "op ", arglist, th);
    return (NO);
}


int o_cons(int x, int y, int th)
{
    if (operationp(y))
	y = operate(y, th);
    return (listcons(x, y));
}

int b_ask(int arglist, int rest, int th)
{
    int n, x1, x2, x3;
    char c;

    n = length(arglist);
    if (n == 0) {
	x1 = variables[th];
	if (child_flag)
	    memset(bridge, 0, sizeof(bridge));
	if (nullp(x1) || has_no_value_p(x1, th)) {
	    if (thread_flag)
		proof[0] = proof[0] + proof[th];
	    return (prove_all(rest, sp[th], th));
	    // ignore singleton e.g. X=X
	}
	x2 = NIL;
	while (!nullp(x1)) {
	    if (variablep(car(x1)) && car(x1) != deref(car(x1), th))
		x2 = cons(car(x1), x2);
	    x1 = cdr(x1);
	}
	x2 = reverse(x2);

	// if multi-thread mode unify variables and return YES.
	if (thread_flag && th != 0) {
	    while (!nullp(x2)) {
		x3 = convert_to_variant(car(x2), th);
		unify(x3, copy_work(deref(car(x2), th), 0), 0);
		x2 = cdr(x2);
	    }
	    proof[0] = proof[0] + proof[th];
	    return (YES);
	}

	if (child_flag) {
	    bridge_flag = 1;
	}
	/* if network-mode write to buffer e.g. X = 1,Y = 2,
	 * normal-mode write to termial 
	 * X = 1
	 * Y = 2
	 */
	while (!nullp(x2)) {
	    print(car(x2));
	    printstr(" = ");
	    printanswer(deref(car(x2), th));
	    if (child_flag)
		printc(',');
	    if (!nullp(cdr(x2)))
		printf("\n");
	    x2 = cdr(x2);
	}
	if (child_flag) {
	    bridge_flag = 0;
	    return (YES);
	}

	putchar(' ');

	fflush(stdout);
	fflush(stdin);

      loop:
	c = n_getch();

	if (c == '.' || c == EOL) {
	    fputs(".\n", stdout);
	    return (prove_all(rest, sp[th], th));
	} else if (c == ';' || c == ' ') {
	    fputs(";\n", stdout);
	    return (NO);
	} else
	    goto loop;
	return (NO);
    }
    error(ARITY_ERR, "ask ", arglist, th);
    return (NO);
}


int b_unify(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	res = unify(arg1, arg2, th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "= ", arglist, th);
    return (NO);
}

int b_notunify(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (operationp(arg1))
	    arg1 = operate(arg1, th);
	if (operationp(arg2))
	    arg2 = operate(arg2, th);
	res = unify(arg1, arg2, th);
	if (res == NO)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "\\= ", arglist, th);
    return (NO);
}




//input and output
int b_write(int arglist, int rest, int th)
{
    int n, arg1, arg2, save;

    n = length(arglist);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto write;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      write:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "write ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "write ", arg1, th);

	save = output_stream;
	if (aliasp(arg1))
	    output_stream = GET_CAR(arg1);
	else
	    output_stream = arg1;
	quoted_flag = 0;
	print(arg2);
	fflush(GET_PORT(output_stream));
	quoted_flag = 1;
	output_stream = save;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "write ", arglist, th);
    return (NO);
}


int b_display(int arglist, int rest, int th)
{
    int n, arg1, arg2, save;

    n = length(arglist);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto display;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      display:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "display ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "display ", arg1, th);

	save = output_stream;
	if (aliasp(arg1))
	    output_stream = GET_CAR(arg1);
	else
	    output_stream = arg1;
	quoted_flag = 1;
	ignore_flag = 1;
	print(arg2);
	quoted_flag = 0;
	ignore_flag = 0;
	output_stream = save;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "display ", arglist, th);
    return (NO);
}


int b_writeq(int arglist, int rest, int th)
{
    int n, arg1, arg2, save;

    n = length(arglist);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto writeq;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      writeq:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "writeq ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "writeq ", arg1, th);

	save = output_stream;
	if (aliasp(arg1))
	    output_stream = GET_CAR(arg1);
	else
	    output_stream = arg1;
	quoted_flag = 1;
	print(arg2);
	quoted_flag = 0;
	output_stream = save;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "writeq ", arglist, th);
    return (NO);
}


int b_nl(int arglist, int rest, int th)
{
    int n, arg1, save;

    n = length(arglist);
    if (n == 0) {
	fprintf(GET_PORT(output_stream), "\n");
	fflush(GET_PORT(output_stream));
	return (prove_all(rest, sp[th], th));
    } else if (n == 1) {
	arg1 = car(arglist);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "nl ", arg1, th);

	save = output_stream;
	if (aliasp(arg1))
	    output_stream = GET_CAR(arg1);
	else
	    output_stream = arg1;
	fprintf(GET_PORT(output_stream), "\n");
	fflush(GET_PORT(output_stream));
	output_stream = save;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "nl ", arglist, th);
    return (NO);
}

int b_put(int arglist, int rest, int th)
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
	if (!integerp(arg2))
	    error(NOT_INT, "put ", arg1, th);

	fprintf(GET_PORT(arg1), "%c", (char) GET_INT(arg2));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "put ", arglist, th);
    return (NO);
}


int b_get0(int arglist, int rest, int th)
{
    int n, c, arg1, arg2, i, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get0;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);


      get0:
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "get0 ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_VAR, "get0 ", arg2, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);

	if (n == 1)
	    c = n_getch();
	else
	    c = getc(GET_PORT(arg1));

	if (c == EOF)
	    return (NO);

	i = makeint((int) c);
	res = unify(arg2, i, th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "get0 ", arglist, th);
    return (NO);
}


int b_get(int arglist, int rest, int th)
{
    int n, c, arg1, arg2, i, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);

	goto get;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get:
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "get ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_VAR, "get ", arg2, th);
	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
      loop:
	if (n == 1)
	    c = n_getch();
	else
	    c = getc(GET_PORT(arg1));


	if (c == EOF)
	    return (NO);

	i = (int) c;
	if (c == EOL)
	    goto exit;
	if (i < 33)
	    goto loop;

      exit:
	res = unify(arg2, makeint(i), th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "get ", arglist, th);
    return (NO);
}


int b_get0_noecho(int arglist, int rest, int th)
{
    int n, c, arg1, i, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	c = n_getch();
	i = makeint((int) c);
	res = unify(arg1, i, th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "get0_noecho ", arglist, th);
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


int b_tab(int arglist, int rest, int th)
{
    int n, arg1, arg2, count;

    n = length(arglist);
    if (n == 1) {
	arg1 = standard_output;
	arg2 = car(arglist);
	goto tab;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      tab:
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "tab ", arg1, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    error(LESS_THAN_ZERO, "tab", arg2, th);
	if (!integerp(arg2))
	    error(NOT_INT, "tab", arg2, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	count = GET_INT(arg2);
	while (count > 0) {
	    fprintf(GET_PORT(arg1), " ");
	    count--;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "tab ", arglist, th);
    return (NO);
}


//option for read_term [variable_names(X)]
int variable_name_p(int x)
{

    if (eqlp(car(x), makeconst("variable_names")) &&
	(wide_variable_p(cadr(x)) || listp(cadr(x))) && nullp(cddr(x)))
	return (1);
    else
	return (0);
}

//option for read_term [singletons(X)]
int singletonp(int x)
{

    if (eqlp(car(x), makeconst("singletons")) &&
	wide_variable_p(cadr(x)) && nullp(cddr(x)))
	return (1);
    else
	return (0);
}



int b_read(int arglist, int rest, int th)
{
    int n, arg1, arg2, save1, save2, temp, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto read;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      read:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "read ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "read", arg1, th);
	if (streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
	    error(NOT_INPUT_STREAM, "read ", arg1, th);

	save1 = input_stream;
	save2 = repl_flag;
	input_stream = arg1;
	if (aliasp(arg1))
	    input_stream = GET_CAR(arg1);
	repl_flag = 0;

	temp = variable_to_call(readparse(th));
	res = unify(arg2, temp, th);
	input_stream = save1;
	repl_flag = save2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "read ", arglist, th);
    return (NO);
}

int b_read_line(int arglist, int rest, int th)
{
    int n, arg1, arg2, save1, save2, res, pos;
    char str[STRSIZE], c;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (arg1 == makeint(0))
	    arg1 = standard_input;

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "read_line ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "read_line ", arg1, th);
	if (streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
	    error(NOT_INPUT_STREAM, "read_line ", arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    error(NOT_VAR, "read_line ", arg2, th);

	save1 = input_stream;
	save2 = repl_flag;
	input_stream = arg1;
	if (aliasp(arg1))
	    input_stream = GET_CAR(arg1);

	repl_flag = 0;

	c = readc();
	pos = 0;
	while (c != EOL && c != EOF) {
	    str[pos] = c;
	    pos++;
	    if (pos > STRSIZE - 1)
		error(RESOURCE_ERR, "read_line ", NIL, th);
	    c = readc();
	}
	str[pos] = NUL;
	res = unify(arg2, makestr(str), th);
	input_stream = save1;
	repl_flag = save2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "read_line ", arglist, th);
    return (NO);
}


int b_read_string(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, res, pos, maxlen;
    char str[STRSIZE], c;

    n = length(arglist);
    if (n == 2) {
	arg1 = input_stream;
	arg2 = car(arglist);	// maxlen
	arg3 = cadr(arglist);	// string
	goto read_string;
    } else if (n == 3) {
	arg1 = car(arglist);	// stream
	arg2 = cadr(arglist);	// maxlen
	arg3 = caddr(arglist);	// string
      read_string:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "read_string ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "read_string ", arg1, th);
	if (streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
	    error(NOT_INPUT_STREAM, "read_string ", arg1, th);
	if (!integerp(arg2))
	    error(NOT_INT, "read_string ", arg2, th);
	if (get_int(arg2) < 0 || get_int(arg2) > STRSIZE)
	    error(WRONG_ARGS, "read_string ", arg2, th);
	if (!wide_variable_p(arg3) && !stringp(arg3))
	    error(NOT_VAR, "read_string ", arg3, th);

	save1 = input_stream;
	save2 = repl_flag;
	input_stream = arg1;
	if (aliasp(arg1))
	    input_stream = GET_CAR(arg1);
	maxlen = GET_INT(arg2);
	repl_flag = 0;

	c = readc();
	pos = 0;
	while (c != EOL && c != EOF && pos < maxlen) {
	    str[pos] = c;
	    pos++;
	    if (pos > STRSIZE - 1)
		error(RESOURCE_ERR, "read_string ", NIL, th);
	    c = readc();
	}
	str[pos] = NUL;
	res = unify(arg3, makestr(str), th);
	input_stream = save1;
	repl_flag = save2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "read_string ", arglist, th);
    return (NO);
}



int b_skip(int arglist, int rest, int th)
{
    int n, arg1, arg2, save;
    char c, str[STRSIZE];

    n = length(arglist);
    if (n == 1) {
	arg1 = standard_input;
	arg2 = car(arglist);
	goto skip;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      skip:
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "skip ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "skip", arg1, th);
	if (streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
	    error(NOT_INPUT_STREAM, "skip ", arg1, th);

	save = input_stream;
	input_stream = arg1;

	do {
	    c = readc();
	    str[0] = c;
	    str[1] = 0;
	}
	while (strcmp(str, GET_NAME(arg2)) != 0 && c != EOF);

	input_stream = save;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "skip ", arglist, th);
    return (NO);
}


int b_stdin(int arglist, int rest, int th)
{
    int n, arg1, arg2, save1, save2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "stdin ", arg1, th);
	if (!callablep(arg2))
	    error(NOT_CALLABLE, "stdin ", arg2, th);

	save1 = input_stream;
	save2 = sp[th];
	if (prove_all(arg2, sp[th], th) == YES) {
	    input_stream = save1;
	    return (prove_all(rest, sp[th], th));
	}
	unbind(save2, th);
	input_stream = save1;
	return (NO);
    }
    error(ARITY_ERR, "stdin ", arglist, th);
    return (NO);
}

int b_stdout(int arglist, int rest, int th)
{
    int n, arg1, arg2, save1, save2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "stdout ", arg1, th);
	if (!callablep(arg2))
	    error(NOT_CALLABLE, "stdout ", arg2, th);

	save1 = output_stream;
	save2 = sp[th];
	if (prove_all(arg2, sp[th], th) == YES) {
	    output_stream = save1;
	    return (prove_all(rest, sp[th], th));
	}
	unbind(save2, th);
	output_stream = save1;
	return (NO);
    }
    error(ARITY_ERR, "stdin ", arglist, th);
    return (NO);
}

int b_stdinout(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, save3;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!streamp(arg1) && !aliasp(arg1))
	    error(NOT_STREAM, "stdinout ", arg1, th);
	if (!streamp(arg1) && !aliasp(arg2))
	    error(NOT_STREAM, "stdinout ", arg2, th);
	if (!callablep(arg3))
	    error(NOT_CALLABLE, "stdinout ", arg3, th);

	save1 = input_stream;
	save2 = output_stream;
	save3 = sp[th];
	if (prove_all(arg3, sp[th], th) == YES) {
	    input_stream = save1;
	    output_stream = save2;
	    return (prove_all(rest, sp[th], th));
	}
	unbind(save3, th);
	input_stream = save1;
	output_stream = save2;
	return (NO);
    }
    error(ARITY_ERR, "stdinout ", arglist, th);
    return (NO);
}


int b_create(int arglist, int rest, int th)
{
    int n, arg1, arg2, stream;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "create ", arg2, th);
	if (!atomp(arg2))
	    error(NOT_ATOM, "create ", arg2, th);

	if (eqp(arg1, makeconst("user"))) {
	    output_stream = standard_output;
	    return (prove_all(rest, sp[th], th));
	} else {
	    stream =
		makestream(fopen(GET_NAME(arg2), "w"), OPL_OUTPUT,
			   OPL_TEXT, NIL, arg2);

	    if (GET_PORT(stream) == NULL)
		error(CANT_OPEN, "create ", arg2, th);
	    unify(arg1, stream, th);
	    return (prove_all(rest, sp[th], th));
	}
    }
    error(ARITY_ERR, "create ", arglist, th);
    return (NO);
}




int b_open(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, stream;
    FILE *fp;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "open ", arg2, th);
	if (!atomp(arg2))
	    error(NOT_ATOM, "open ", arg2, th);

	if (eqp(arg1, makeconst("user"))) {
	    output_stream = standard_output;
	    return (prove_all(rest, sp[th], th));
	} else {
	    fp = fopen(GET_NAME(arg2), "r");
	    if (fp == NULL) {
		fclose(fp);
		error(FILE_EXIST, "open ", arg2, th);
	    }

	    if (arg3 == makeconst("w")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "w"), OPL_OUTPUT,
			       OPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    error(CANT_OPEN, "open ", arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("r")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "r"), OPL_INPUT,
			       OPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    error(CANT_OPEN, "open ", arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("rw")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "r+"), OPL_INPUT,
			       OPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    error(CANT_OPEN, "open ", arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("a") || arg3 == makeconst("ra")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "a+"), OPL_INPUT,
			       OPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    error(CANT_OPEN, "open ", arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    }
	    error(NOT_OPEN_OPTION, "open ", arg3, th);
	}
    }
    error(ARITY_ERR, "open ", arglist, th);
    return (NO);
}

int b_dup(int arglist, int rest, int th)
{
    int n, arg1, arg2, addr;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1))
	    error(NOT_STREAM, "dup ", arg1, th);

	addr = freshcell();
	SET_TAG(addr, STREAM);
	SET_PORT(addr, GET_PORT(arg1));
	SET_CDR(addr, GET_CDR(arg1));
	SET_OPT(addr, GET_OPT(arg1));	//input/output/inout
	SET_VAR(addr, GET_VAR(arg1));	//text/binary
	SET_AUX(addr, GET_AUX(arg1));	//for eof_action
	if (unify(arg2, addr, th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "dup ", arglist, th);
    return (NO);
}


int b_close(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	fclose(GET_PORT(arg1));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "close ", arglist, th);
    return (NO);
}


int b_see(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "see ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "see ", arg1, th);

	if (eqp(arg1, makeconst("user"))) {
	    input_stream = standard_input;
	    return (prove_all(rest, sp[th], th));
	} else {
	    input_stream =
		makestream(fopen(GET_NAME(arg1), "r"), OPL_INPUT, OPL_TEXT,
			   NIL, arg1);

	    if (GET_PORT(input_stream) == NULL)
		error(CANT_OPEN, "see", arg1, th);
	    return (prove_all(rest, sp[th], th));
	}
    }
    error(ARITY_ERR, "see ", arglist, th);
    return (NO);
}

int b_seeing(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!wide_variable_p(arg1))
	    error(NOT_VAR, "seeing ", arg1, th);
	if (unify(arg1, GET_CDR(input_stream), th) == YES) {
	    return (prove_all(rest, sp[th], th));
	}
    }
    error(ARITY_ERR, "seeing ", arglist, th);
    return (NO);
}


int b_seen(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	if (input_stream != standard_input) {
	    fclose(GET_PORT(input_stream));
	    input_stream = standard_input;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "seen ", arglist, th);
    return (NO);
}

int b_tell(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "tell ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "tell ", arg1, th);

	if (eqp(arg1, makeconst("user"))) {
	    output_stream = standard_output;
	    return (prove_all(rest, sp[th], th));
	} else {
	    output_stream =
		makestream(fopen(GET_NAME(arg1), "w"), OPL_OUTPUT,
			   OPL_TEXT, NIL, arg1);

	    if (GET_PORT(input_stream) == NULL)
		error(CANT_OPEN, "tell ", arg1, th);
	    return (prove_all(rest, sp[th], th));
	}
    }
    error(ARITY_ERR, "tell ", arglist, th);
    return (NO);
}

int b_telling(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (unify(arg1, GET_CDR(output_stream), th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "telling ", arglist, th);
    return (NO);
}

int b_told(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	if (output_stream != standard_output) {
	    fclose(GET_PORT(output_stream));
	    output_stream = standard_output;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "told ", arglist, th);
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


int b_consult(int arglist, int rest, int th)
{
    int n, arg1, clause, save;
    char str[STRSIZE];

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "consult ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "consult ", arg1, th);

	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	save = input_stream;
	input_stream =
	    makestream(fopen(GET_NAME(arg1), "r"), OPL_INPUT, OPL_TEXT,
		       NIL, arg1);

	if (GET_PORT(input_stream) == NULL)
	    error(CANT_OPEN, "consult", arg1, th);

	//object file ex "foo.o"
	n = strlen(GET_NAME(arg1));
	strcpy(str, GET_NAME(arg1));
	if (str[n - 1] == 'o' && str[n - 2] == '.') {
	    dynamic_link(arg1);
	    input_stream = save;
	    goto exit;
	}

	open_flag = 1;
	line = 1;
	column = 0;
	reconsult_list = NIL;
	execute_list = NIL;
	while (1) {
	  skip:
	    clause = readparse(th);
	    if (clause == FEND)
		break;

	    //e.g. :- op(...)
	    if (operationp(clause) && car(clause) == NECK
		&& length(clause) == 2) {
		clause = cadr(clause);
		//if(!builtinp(clause) && !user_operation_p(clause)){
		//  error(SYNTAX_ERR,"consult",clause);
		//}
		prove_all(clause, sp[th], th);
		goto skip;
	    }
	    // DCG syntax e.g. a-->b.
	    if (dcgp(clause)) {
		operate(clause, th);
		goto skip;
	    }
	    //assert
	    b_assert(list1(clause), NIL, th);
	}
	open_flag = 0;
	fclose(GET_PORT(input_stream));
	input_stream = save;

      exit:
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "consult ", arglist, th);
    return (NO);
}


int b_reconsult(int arglist, int rest, int th)
{
    int n, arg1, arg2, clause, head, atom, save;
    char str[STRSIZE];

    n = length(arglist);
    arg2 = NIL;
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "reconsult ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "reconsult ", arg1, th);

	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	save = input_stream;
	input_stream =
	    makestream(fopen(GET_NAME(arg1), "r"), OPL_INPUT, OPL_TEXT,
		       NIL, arg1);

	if (GET_PORT(input_stream) == NULL)
	    error(CANT_OPEN, "reconsult", arg1, th);

	//object file ex "foo.o"
	n = strlen(GET_NAME(arg1));
	strcpy(str, GET_NAME(arg1));
	if (str[n - 1] == 'o' && str[n - 2] == '.') {
	    dynamic_link(arg1);
	    input_stream = save;
	    goto exit;
	}

	open_flag = 1;
	line = 1;
	column = 0;
	reconsult_list = NIL;
	execute_list = NIL;
	while (1) {
	  skip:
	    clause = readparse(th);
	    if (clause == FEND)
		break;

	    //e.g. :- op(...)
	    if (operationp(clause) && car(clause) == NECK
		&& length(clause) == 2) {
		clause = cadr(clause);
		if (arg2 == NIL)
		    prove_all(clause, sp[th], th);
		else if (arg2 != NIL && !predicatep(cadr(clause)))
		    prove_all(clause, sp[th], th);
		execute_list = listcons(clause, execute_list);
		goto skip;
	    }
	    // DCG syntax e.g. a-->b.
	    if (dcgp(clause)) {
		operate(clause, th);
		goto skip;
	    }
	    //delete old definition
	    if (predicatep(clause) || user_operation_p(clause)) {
		if (atomp(clause))
		    atom = clause;
		else
		    atom = car(clause);
	    } else {
		head = cadr(clause);
		if (atomp(head))
		    atom = head;
		else
		    atom = car(head);
	    }
	    if (!memberp(atom, reconsult_list)) {
		reconsult_list = cons(atom, reconsult_list);
		SET_CAR(atom, NIL);
	    }
	    //assert
	    b_assert(list1(clause), NIL, th);
	}
	open_flag = 0;
	fclose(GET_PORT(input_stream));
	input_stream = save;

      exit:
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "reconsult ", arglist, th);
    return (NO);
}

/*
X)->foo, foo(X) :- bar(X)->foo
 set CDR part of atom the arity. e.g. cdr(atom) = #[2,3]
*/
void memoize_arity(int clause, int atom)
{
    if (predicatep(clause) || user_operation_p(clause)) {
	if (atomp(clause) && !memq(makeint(0), GET_ARITY(atom))) {
	    SET_ARITY(atom, cons(makeint(0), GET_ARITY(atom)));
	} else if (!atomp(clause)
		   && !memq(makeint(length(cdr(clause))), GET_ARITY(atom))) {
	    SET_ARITY(atom,
		      cons(makeint(length(cdr(clause))), GET_ARITY(atom)));
	}
    } else {
	if (atomp(cadr(clause)) && !memq(makeint(0), GET_ARITY(atom))) {
	    SET_ARITY(atom, cons(makeint(0), GET_ARITY(atom)));
	} else if (!atomp(cadr(clause)) &&
		   !memq(makeint(length(cdr(cadr(clause)))),
			 GET_ARITY(atom))) {
	    SET_ARITY(atom,
		      cons(makeint(length(cdr(cadr(clause)))),
			   GET_ARITY(atom)));
	}
    }
}

int b_save(int arglist, int rest, int th)
{
    int n, arg1;
    static char str[STREAM];
    char *home, str1[STRSIZE];

    n = length(arglist);
    if (n == 0) {
	arg1 = NIL;
	home = getenv("HOME");
	strcpy(str1, home);
	strcat(str1, "/nprolog/library/startup.pl");
	output_stream =
	    makestream(fopen(str1, "w"), OPL_OUTPUT, OPL_TEXT, NIL, arg1);
	goto save;
    } else if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	strcpy(str, GET_NAME(arg1));
	output_stream =
	    makestream(fopen(GET_NAME(arg1), "w"), OPL_OUTPUT,
		       OPL_TEXT, NIL, arg1);

      save:
	if (GET_PORT(output_stream) == NULL) {
	    error(CANT_OPEN, "save ", arg1, th);
	}
	b_listing(NIL, NIL, th);
	fclose(GET_PORT(output_stream));
	output_stream = standard_output;
	return (prove_all(rest, sp[th], th));

    } else if (n == 0) {
	if (str == NULL) {
	    error(ILLEGAL_ARGS, "save ", NIL, th);
	}

	output_stream =
	    makestream(fopen(str, "w"), OPL_OUTPUT,
		       OPL_TEXT, NIL, makeatom(str, SIMP));
	b_listing(NIL, NIL, th);
	fclose(GET_PORT(output_stream));
	output_stream = standard_output;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "save ", arglist, th);
    return (NO);
}


int b_directory(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, arg4, arg5, arg6, save, mode, date, time;
    DIR *dir;
    struct dirent *dp;
    struct stat stat_buf;
    struct tm *t_st;

    n = length(arglist);
    if (n == 6) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	arg4 = cadddr(arglist);
	arg5 = caddddr(arglist);
	arg6 = cadddddr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "directory ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "directory ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "directory ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "directory ", arg3, th);
	if (!wide_variable_p(arg4))
	    error(NOT_VAR, "directory ", arg4, th);
	if (!wide_variable_p(arg5))
	    error(NOT_VAR, "directory ", arg5, th);
	if (!wide_variable_p(arg6))
	    error(NOT_VAR, "directory ", arg6, th);

	save = sp[th];
	dir = opendir(GET_NAME(arg1));
	if (dir == NULL)
	    error(SYSTEM_ERROR, "directory ", NIL, th);

	dp = readdir(dir);
	while (dp != NULL) {
	    if (stat(dp->d_name, &stat_buf) == 0) {
		if (S_ISREG(stat_buf.st_mode))
		    mode = makeconst("file");
		else if (S_ISDIR(stat_buf.st_mode))
		    mode = makeconst("directory");
		else
		    mode = makeconst("unknown");

		t_st = localtime(&stat_buf.st_mtime);
		date = NIL;
		time = NIL;
		time = cons(makeint(t_st->tm_sec), time);
		time = cons(makeint(t_st->tm_min), time);
		time = cons(makeint(t_st->tm_hour), time);
		time = cons(makeconst("time"), time);
		SET_AUX(car(time), PRED);
		date = cons(makeint(t_st->tm_mday), date);
		date = cons(makeint(t_st->tm_mon + 1), date);
		date = cons(makeint(t_st->tm_year + 1900), date);
		date = cons(makeconst("date"), date);
		SET_AUX(car(date), PRED);
		unify(arg2, makeconst(dp->d_name), th);
		unify(arg3, mode, th);
		unify(arg4, time, th);
		unify(arg5, date, th);
		unify(arg6, makeint(stat_buf.st_size), th);
		return (prove_all(rest, sp[th], th));
	    } else
		error(SYSTEM_ERROR, "directory ", NIL, th);

	    unbind(save, th);
	    dp = readdir(dir);
	}
	if (dir != NULL)
	    closedir(dir);

	unbind(save, th);
	return (NO);
    }
    error(ARITY_ERR, "directory ", arglist, th);
    return (NO);
}


//arithmetic operation

int b_is(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "is ", arg2, th);

	arg2 = eval(arg2, th);
	res = unify(arg1, arg2, th);

	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "is ", arglist, th);
    return (NO);
}


int b_greater(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "> ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "> ", arg2, th);


	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);
	if (!numberp(arg1))
	    error(NOT_NUM, "> ", arg1, th);
	if (!numberp(arg2))
	    error(NOT_NUM, "> ", arg2, th);

	if (greaterp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "> ", arglist, th);
    return (NO);
}

int b_smaller(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "< ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "< ", arg2, th);


	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);
	if (!numberp(arg1))
	    error(NOT_NUM, "< ", arg1, th);
	if (!numberp(arg2))
	    error(NOT_NUM, "< ", arg2, th);
	if (smallerp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "< ", arglist, th);
    return (NO);
}

int b_eqsmaller(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "=< ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "=< ", arg2, th);

	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);
	if (!numberp(arg1))
	    error(NOT_NUM, "=< ", arg1, th);
	if (!numberp(arg2))
	    error(NOT_NUM, "=< ", arg2, th);
	if (eqsmallerp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "=< ", arglist, th);
    return (NO);
}

int b_eqgreater(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, ">= ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, ">= ", arg2, th);

	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);
	if (!numberp(arg1))
	    error(NOT_NUM, ">= ", arg1, th);
	if (!numberp(arg2))
	    error(NOT_NUM, ">= ", arg2, th);
	if (eqgreaterp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, ">= ", arglist, th);
    return (NO);
}

int b_numeq(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = eval(car(arglist), th);
	arg2 = eval(cadr(arglist), th);
	if (!numberp(arg1))
	    error(NOT_NUM, "=:= ", arg1, th);
	if (!numberp(arg2))
	    error(NOT_NUM, "=:= ", arg2, th);

	if (numeqp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "=:= ", arglist, th);
    return (NO);
}

int b_notnumeq(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = eval(car(arglist), th);
	arg2 = eval(cadr(arglist), th);
	if (!numberp(arg1))
	    error(NOT_NUM, "=\\= ", arg1, th);
	if (!numberp(arg2))
	    error(NOT_NUM, "=\\= ", arg2, th);

	if (!numeqp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "=\\= ", arglist, th);
    return (NO);
}

int b_equalp(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (anoymousp(arg1) && anoymousp(arg2))
	    return (NO);
	else if (equalp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "== ", arglist, th);
    return (NO);
}

int b_notequalp(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (anoymousp(arg1) && anoymousp(arg2))
	    return (prove_all(rest, sp[th], th));
	else if (!equalp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "\\== ", arglist, th);
    return (NO);
}

int b_eq(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (arg1 == arg2)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "eq ", arglist, th);
    return (NO);
}



int b_compare(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "compare ", arg1, th);
	if (!wide_variable_p(arg1) &&
	    !(eqp(arg1, makeatom("<", SYS)) ||
	      eqp(arg1, makeatom("=", SYS)) ||
	      eqp(arg1, makeatom(">", SYS))))
	    error(NOT_ORDER, "compare ", arg1, th);

	if (equalp(arg2, arg3)) {
	    if (unify(arg1, makeatom("=", SYS), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (atsmaller(arg2, arg3)) {
	    if (unify(arg1, makeatom("<", SYS), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (atsmaller(arg3, arg2)) {
	    if (unify(arg1, makeatom(">", SYS), th) == YES)
		return (prove_all(rest, sp[th], th));
	}

    }
    error(ARITY_ERR, "compare ", arglist, th);
    return (NO);
}

int b_atsmaller(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (atsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "@< ", arglist, th);
    return (NO);
}

int atsmaller(int x, int y)
{

    if (nullp(x))
	return (0);
    else if (variablep(x) || variablep(y))
	return (1);
    else if (numberp(x) && numberp(y)) {
	if (smallerp(x, y))
	    return (1);
	else
	    return (0);
    } else if (atomp(x) && atomp(y)) {
	if (strcmp(GET_NAME(x), GET_NAME(y)) < 0)
	    return (1);
	else
	    return (0);
    } else if (structurep(x) && structurep(y)) {
	if (length(x) < length(y))
	    return (1);
	else if (length(x) > length(y))
	    return (0);
	else if (atsmaller(car(x), car(y)))
	    return (1);
	else if (equalp(car(x), car(y)))
	    return (atsmaller(cdr(x), cdr(y)));
	else
	    return (0);
    } else if (floatp(x))
	return (1);
    else if (wide_integer_p(x) && atomp(y))
	return (1);
    else if (wide_integer_p(x) && structurep(y))
	return (1);
    else if (atomp(x) && structurep(y))
	return (1);
    else
	return (0);
}

int ateqsmaller(int x, int y)
{

    if (nullp(x))
	return (0);
    else if (variablep(x) || variablep(y))
	return (1);
    else if (numberp(x) && numberp(y)) {
	if (eqsmallerp(x, y))
	    return (1);
	else
	    return (0);
    } else if (atomp(x) && atomp(y)) {
	if (strcmp(GET_NAME(x), GET_NAME(y)) <= 0)
	    return (1);
	else
	    return (0);
    } else if (structurep(x) && structurep(y)) {
	if (length(x) < length(y))
	    return (1);
	else if (length(x) > length(y))
	    return (0);
	else if (ateqsmaller(car(x), car(y)))
	    return (1);
	else if (equalp(car(x), car(y)))
	    return (ateqsmaller(cdr(x), cdr(y)));
	else
	    return (0);
    } else if (floatp(x))
	return (1);
    else if (wide_integer_p(x) && atomp(y))
	return (1);
    else if (wide_integer_p(x) && structurep(y))
	return (1);
    else if (atomp(x) && structurep(y))
	return (1);
    else
	return (0);
}


int b_ateqsmaller(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (ateqsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "@=< ", arglist, th);
    return (NO);
}



int b_atgreater(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!ateqsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "@> ", arglist, th);
    return (NO);
}


int b_ateqgreater(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!atsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "@>= ", arglist, th);
    return (NO);
}

//timer
int b_ctr_set(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "ctr_set ", arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    error(WRONG_ARGS, "ctr_set ", arg1, th);
	if (!integerp(arg2))
	    error(NOT_INT, "ctr_set ", arg2, th);

	counter[GET_INT(arg1)] = GET_INT(arg2);
	return (prove_all(rest, sp[th], th));

    }
    error(ARITY_ERR, "ctr_set ", arglist, th);
    return (NO);
}

int b_ctr_dec(int arglist, int rest, int th)
{
    int n, arg1, arg2, i;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "ctr_dec ", arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    error(WRONG_ARGS, "ctr_dec ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "ctr_dec ", arg2, th);

	i = counter[GET_INT(arg1)];
	counter[GET_INT(arg1)] = i - 1;
	if (unify(arg2, makeint(i), th) == YES)
	    return (prove_all(rest, sp[th], th));

    }
    error(ARITY_ERR, "ctr_dec ", arglist, th);
    return (NO);
}

int b_ctr_inc(int arglist, int rest, int th)
{
    int n, arg1, arg2, i;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "ctr_inc ", arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    error(WRONG_ARGS, "ctr_inc ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "ctr_inc ", arg2, th);

	i = counter[GET_INT(arg1)];
	counter[GET_INT(arg1)] = i + 1;
	if (unify(arg2, makeint(i), th) == YES)
	    return (prove_all(rest, sp[th], th));

    }
    error(ARITY_ERR, "ctr_inc ", arglist, th);
    return (NO);
}

int b_ctr_is(int arglist, int rest, int th)
{
    int n, arg1, arg2, i;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "ctr_is ", arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    error(WRONG_ARGS, "str_is ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "ctr_is ", arg2, th);

	i = counter[GET_INT(arg1)];
	if (unify(arg2, makeint(i), th) == YES)
	    return (prove_all(rest, sp[th], th));

    }
    error(ARITY_ERR, "str_is ", arglist, th);
    return (NO);
}

//true fail
int b_fail(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	return (NO);
    }
    return (NO);
}

int b_call(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "call ", arg1, th);

	if (!callablep(arg1))
	    error(NOT_CALLABLE, "call ", arg1, th);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "call ", arg1, th);

	if (atom_constant_p(arg1))
	    arg1 = makeatom(GET_NAME(arg1), PRED);

	return (prove_all(addtail_body(rest, arg1, th), sp[th], th));
    }
    error(ARITY_ERR, "call ", arglist, th);
    return (NO);
}

int b_not(int arglist, int rest, int th)
{
    int n, arg1, res;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "not ", arg1, th);
	if (!callablep(arg1))
	    error(NOT_CALLABLE, "not ", arg1, th);

	res = prove_all(arg1, sp[th], th);
	if (res == YES)
	    return (NO);
	else
	    return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "not ", arglist, th);
    return (NO);
}

int b_true(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	return (prove_all(rest, sp[th], th));
    }
    return (NO);
}


//database operation
int b_assert(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "assertz ", arg1, th);
	if (singlep(arg1)) {
	    if (GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
		SET_AUX(arg1, PRED);
	}
	if (builtinp(arg1))
	    error(BUILTIN_EXIST, "assertz ", arg1, th);
	if (functionp(arg1)) {
	    arg1 = cons(makeatom(GET_NAME(car(arg1)), PRED), cdr(arg1));
	}


	arg1 = variable_to_call(arg1);	//P -> call(P)
	arg1 = copy_heap(arg1);	//copy arg1 to heap area
	if (predicatep(arg1) || user_operation_p(arg1)) {
	    SET_VAR(arg1, unique(varslist(arg1)));
	    if (atomp(arg1))
		add_data(arg1, arg1);
	    else
		add_data(car(arg1), arg1);
	    checkgbc();
	    return (prove_all(rest, sp[th], th));
	} else if (clausep(arg1)) {
	    if (!callablep(cadr(arg1)))
		error(NOT_CALLABLE, "assertz ", arg1, th);
	    if (operationp(cadr(arg1)))
		error(BUILTIN_EXIST, "assertz ", arg1, th);



	    SET_VAR(arg1, unique(varslist(arg1)));
	    operate(arg1, th);
	    checkgbc();
	    return (prove_all(rest, sp[th], th));
	}
	error(NOT_CALLABLE, "assertz ", arg1, th);
    }
    error(ARITY_ERR, "assertz ", arglist, th);
    return (NO);
}

int b_asserta(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "asserta ", arg1, th);
	if (singlep(arg1)) {
	    if (GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
		SET_AUX(arg1, PRED);
	}
	if (builtinp(arg1))
	    error(BUILTIN_EXIST, "asserta ", arg1, th);
	if (functionp(arg1)) {
	    arg1 = cons(makeatom(GET_NAME(car(arg1)), PRED), cdr(arg1));
	}

	arg1 = variable_to_call(arg1);	//P -> call(P)
	arg1 = copy_heap(arg1);	//copy arg1 to heap area
	if (predicatep(arg1) || user_operation_p(arg1)) {
	    SET_VAR(arg1, unique(varslist(arg1)));
	    if (atomp(arg1))
		insert_data(arg1, arg1);
	    else
		insert_data(car(arg1), arg1);
	    checkgbc();
	    return (prove_all(rest, sp[th], th));
	} else if (clausep(arg1)) {
	    if (!callablep(cadr(arg1)))
		error(NOT_CALLABLE, "asserta ", arg1, th);
	    if (operationp(cadr(arg1)))
		error(BUILTIN_EXIST, "asserta ", arg1, th);

	    SET_VAR(arg1, unique(varslist(arg1)));
	    operate(arg1, th);
	    assert_flag = 0;
	    checkgbc();
	    return (prove_all(rest, sp[th], th));
	}
	error(NOT_CALLABLE, "asserta ", arg1, th);
    }
    error(ARITY_ERR, "asserta ", arglist, th);
    return (NO);
}

int b_retract(int arglist, int rest, int th)
{
    int n, arg1, clause, head, clauses, new_clauses, save1, save2;

    save2 = sp[th];
    clause = clauses = head = NIL;
    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "retract ", arg1, th);
	if (operationp(arg1) && !predicatep(cadr(arg1)))
	    error(NOT_CALLABLE, "retract ", arg1, th);
	if (!operationp(arg1) && !predicatep(arg1))
	    error(NOT_CALLABLE, "retract ", arg1, th);
	if (operationp(arg1) && builtinp(cadr(arg1)))
	    error(BUILTIN_EXIST, "retract ", arg1, th);
	if (!operationp(arg1) && builtinp(arg1))
	    error(BUILTIN_EXIST, "retract ", arg1, th);

	if (singlep(arg1)) {
	    arg1 = list1(arg1);
	}
	if (atom_predicate_p(arg1))
	    clauses = GET_CAR(arg1);
	else if (predicatep(arg1))
	    clauses = GET_CAR(car(arg1));
	else if (clausep(arg1) && atom_predicate_p(cadr(arg1)))
	    clauses = GET_CAR(cadr(arg1));
	else if (clausep(arg1))
	    clauses = GET_CAR(car(cadr(arg1)));

	new_clauses = NIL;
	save1 = wp[th];
	while (!nullp(clauses)) {
	    clause = car(clauses);
	    clauses = cdr(clauses);

	    if (unify(arg1, clause, th) == YES) {
		if (atom_predicate_p(arg1))
		    SET_CAR(clause,
			    append(listreverse(new_clauses), clauses));
		else if (predicatep(arg1))
		    SET_CAR(car(arg1),
			    append(listreverse(new_clauses), clauses));
		else if (clausep(arg1) && atom_predicate_p(cadr(arg1)))
		    SET_CAR(cadr(arg1),
			    append(listreverse(new_clauses), clauses));
		else if (clausep(arg1))
		    SET_CAR(car(cadr(arg1)),
			    append(listreverse(new_clauses), clauses));

		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
		else
		    goto next;
	    }
	    new_clauses = cons(clause, new_clauses);
	  next:
	    wp[th] = save1;
	    unbind(save2, th);
	}
	wp[th] = save1;
	sp[th] = save2;
	return (NO);
    }
    error(ARITY_ERR, "retract ", arglist, th);
    return (NO);
}


int b_abolish(int arglist, int rest, int th)
{
    int n, arg1, pred, clause, arity, clauses, new_clauses;

    clause = clauses = NIL;
    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "abolish ", arg1, th);
	if (structurep(arg1) &&
	    (wide_variable_p(cadr(arg1)) || wide_variable_p(caddr(arg1))))
	    error(INSTANTATION_ERR, "abolish ", arg1, th);
	if (car(arg1) != makeatom("/", OPE))
	    error(PRED_INDICATOR, "abolish ", arg1, th);
	if (builtinp(cadr(arg1)))
	    error(STATIC_PROCEDURE, "abolish ", arg1, th);
	if (!atomp(cadr(arg1)))
	    error(NOT_ATOM, "abolish ", arg1, th);
	if (integerp(eval(caddr(arg1), th))
	    && GET_INT(eval(caddr(arg1), th)) < 0)
	    error(LESS_THAN_ZERO, "abolish ", arg1, th);
	if (!integerp(caddr(arg1)))
	    error(NOT_INT, "abolish ", arg1, th);

	pred = makepred(GET_NAME(cadr(arg1)));
	clauses = GET_CAR(pred);
	arity = GET_INT(caddr(arg1));

	new_clauses = NIL;
	while (!nullp(clauses)) {
	    clause = car(clauses);

	    if (atom_predicate_p(clause) && arity == 0)
		goto abolish;
	    else if (predicatep(clause) && length(clause) - 1 == arity)
		goto abolish;
	    else if (clausep(clause) && atom_predicate_p(cadr(clause)) &&
		     arity == 0)
		goto abolish;
	    else if (clausep(clause) && length(cadr(clause)) - 1 == arity)
		goto abolish;

	    new_clauses = cons(clause, new_clauses);

	  abolish:
	    clauses = cdr(clauses);
	}
	SET_CAR(pred, listreverse(new_clauses));
	if (nullp(new_clauses))
	    listremove(cadr(arg1), predicates);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "abolish ", arglist, th);
    return (NO);
}

int b_clause(int arglist, int rest, int th)
{
    int n, arg1, arg2, clause, clauses, save1, save2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);	//head
	arg2 = cadr(arglist);	//body

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "clause ", arg1, th);
	if (!atom_predicate_p(arg1) && !predicatep(arg1))
	    error(NOT_CALLABLE, "clause ", arg1, th);
	if (builtinp(arg1) || compiledp(arg1))
	    error(BUILTIN_EXIST, "clause ", arg1, th);
	if (!wide_variable_p(arg2) && !callablep(arg2))
	    error(NOT_CALLABLE, "clause ", arg2, th);


	if (atom_predicate_p(arg1))
	    clauses = GET_CAR(arg1);
	else
	    clauses = GET_CAR(car(arg1));

	save1 = wp[th];
	save2 = sp[th];
	while (!nullp(clauses)) {
	    clause = car(clauses);
	    clauses = cdr(clauses);
	    if (clausep(clause) && unify(arg1, cadr(clause), th) == YES &&
		unify(arg2, caddr(clause), th) == YES) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
	    } else if (predicatep(clause) && unify(arg1, clause, th) == YES
		       && unify(arg2, NTRUE, th) == YES) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
	    }
	    wp[th] = save1;
	    unbind(save2, th);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "clause ", arglist, th);
    return (NO);
}

int b_nth_char(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, pos, code;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);	// Nth
	arg2 = cadr(arglist);	//string
	arg3 = caddr(arglist);	//Char
	if (!integerp(arg1))
	    error(NOT_INT, "nth_char ", arg1, th);
	if (!stringp(arg2))
	    error(NOT_STR, "nth_char ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "nth_char ", arg3, th);

	pos = GET_INT(arg1);
	strcpy(str1, GET_NAME(arg2));

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
	} else {		//ascii code
	    str2[0] = str1[pos++];
	    str2[1] = NUL;
	}

	if (str2[0] == '\\')
	    code = ctrl_to_number(str2[1]);
	else			//unicode
	    code = makeint(utf8_to_ucs4(str2));

	unify(arg3, makeint(code), th);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "nth_char ", arglist, th);
    return (NO);
}


//transform
int b_name(int arglist, int rest, int th)
{
    int n, arg1, arg2, ls, atom, pos, code, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
	    error(INSTANTATION_ERR, "name ", arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "name ", arg1, th);
	if (wide_variable_p(arg1) && !listp(arg2))
	    error(NOT_LIST, "name ", arg2, th);
	if (wide_variable_p(arg1) && !atom_codes_list_p(arg2))
	    error(NOT_CHAR_CODE, "name ", arg2, th);


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
    error(ARITY_ERR, "name ", arglist, th);
    return (NO);
}

int b_list_text(int arglist, int rest, int th)
{
    int n, arg1, arg2, ls, atom, pos, code, index, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);	//list
	arg2 = cadr(arglist);	//atomstring
	if (listp(arg1) && length(arg1) == -1 && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "list_text ", arg2, th);
	if (!wide_variable_p(arg1) && !listp(arg1) && !nullp(arg1))
	    error(NOT_LIST, "list_text ", arg1, th);
	if (wide_variable_p(arg1) && !atomp(arg2) && !stringp(arg2))
	    error(NOT_ATOM, "list_text ", arg2, th);


	if (atomp(arg2) || stringp(arg2)) {
	    strcpy(str1, GET_NAME(arg2));
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
	    res = unify(arg1, ls, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);

	} else if (structurep(arg1)) {
	    ls = arg1;
	    str1[th] = NUL;
	    while (!nullp(ls)) {
		if (GET_INT(car(ls)) < ' ')
		    sprintf(str2, "\\x%x\\", GET_INT(car(ls)));
		else
		    ucs4_to_utf8(GET_INT(car(ls)), str2);
		strcat(str1, str2);
		ls = cdr(ls);
	    }

	    index = hash(str1);
	    if ((res = getatom(str1, SIMP, index)) != 0)
		atom = res;
	    else if ((res = getatom(str1, PRED, index)) != 0)
		atom = res;
	    else if ((res = getatom(str1, SYS, index)) != 0)
		atom = res;
	    else if ((res = getatom(str1, COMP, index)) != 0)
		atom = res;
	    else if ((res = getatom(str1, OPE, index)) != 0)
		atom = res;
	    else if ((res = getatom(str1, USER, index)) != 0)
		atom = res;
	    else
		atom = makestr(str1);

	    if (unify(arg2, atom, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "list_text ", arglist, th);
    return (NO);
}


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

int b_atom_string(int arglist, int rest, int th)
{
    int n, arg1, arg2, temp;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);	//atom
	arg2 = cadr(arglist);	//string

	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "atom_string ", arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    error(NOT_STR, "atom_string ", arg2, th);

	if (atomp(arg1)) {
	    temp = makestr(GET_NAME(arg1));
	    if (unify(arg2, temp, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (stringp(arg2)) {
	    temp = makeconst(GET_NAME(arg2));
	    if (unify(arg1, temp, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}
    }
    error(ARITY_ERR, "atom_string ", arglist, th);
    return (NO);
}

int b_char_code(int arglist, int rest, int th)
{
    int n, arg1, arg2, code, res;
    char str[2];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "char_code ", list2(arg1, arg2), th);
	if (!wide_variable_p(arg1) && !characterp(arg1))
	    error(NOT_CHAR, "char_code ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "char_code ", arg2, th);


	if (atomp(arg1) && !variablep(arg1)) {
	    strcpy(str, GET_NAME(arg1));
	    if (str[0] == '\\') {
		if (str[1] == 'n')
		    return (unify(arg2, makeint(EOL), th));
		else if (str[1] == 't')
		    return (unify(arg2, makeint(TAB), th));
		else if (str[1] == 'f')
		    return (unify(arg2, makeint(FF), th));
		else if (str[1] == 'r')
		    return (unify(arg2, makeint(CR), th));
		else if (str[1] == 'v')
		    return (unify(arg2, makeint(VT), th));
		else if (str[1] == 'a')
		    return (unify(arg2, makeint(BEL), th));
		else if (str[1] == 'b')
		    return (unify(arg2, makeint(BS), th));
		else
		    error(SYNTAX_ERR, "char_code ", NIL, th);
	    }
	    //unicode
	    code = makeint(utf8_to_ucs4(GET_NAME(arg1)));
	    res = unify(arg2, code, th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);

	} else if (integerp(arg2)) {
	    //unicode
	    ucs4_to_utf8(GET_INT(arg2), str);
	    res = unify(arg1, makeconst(str), th);
	    if (res == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "char_code ", arglist, th);
    return (NO);
}



//----------string transform-------------------

int b_concat(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, str;
    char str1[STRSIZE];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1))
	    error(NOT_LIST, "concat ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "concat ", arg2, th);
	if (!stringp(car(arg1)))
	    error(NOT_STR, "concat ", car(arg1), th);

	strcpy(str1, GET_NAME(car(arg1)));
	arg1 = cdr(arg1);
	while (!nullp(arg1)) {
	    if (!stringp(car(arg1)) && !atomp(car(arg1)))
		error(NOT_STR, "concat ", car(arg1), th);
	    if (strlen(str1) + strlen(GET_NAME(car(arg1))) > STRSIZE)
		error(RESOURCE_ERR, "concat ", car(arg1), th);

	    strcat(str1, GET_NAME(car(arg1)));
	    arg1 = cdr(arg1);
	}
	str = makestr(str1);

	if (unify(arg2, str, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    } else if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !(atomp(arg1) || stringp(arg1)))
	    error(NOT_STR, "concat ", arg1, th);
	if (!wide_variable_p(arg2) && !(atomp(arg2) || stringp(arg2)))
	    error(NOT_STR, "concat ", arg2, th);
	if (!wide_variable_p(arg3) && !stringp(arg3))
	    error(NOT_VAR, "concat ", arg3, th);
	if (strlen(GET_NAME(arg1)) + strlen(GET_NAME(arg2)) > STRSIZE)
	    error(RESOURCE_ERR, "concat", arglist, th);

	strcpy(str1, GET_NAME(arg1));
	strcat(str1, GET_NAME(arg2));
	str = makestr(str1);

	if (unify(arg3, str, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);

    }
    error(ARITY_ERR, "concat ", arglist, th);
    return (NO);
}

int b_string_length(int arglist, int rest, int th)
{
    int n, arg1, arg2, val;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "string_length ", arg1, th);
	if (!stringp(arg1))
	    error(NOT_STR, "string_length ", arg1, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    error(LESS_THAN_ZERO, "string_length ", arg2, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_INT, "string_length ", arg2, th);

	val = makeint(string_length(arg1));
	if (unify(arg2, val, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "string_length ", arglist, th);
    return (NO);
}

int b_string_term(int arglist, int rest, int th)
{
    int n, arg1, arg2, l, i, res;
    char str[STRSIZE];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1) && !stringp(arg1))
	    error(NOT_STR, "string_term ", arg1, th);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(WRONG_ARGS, "string_term ", arglist, th);

	if (wide_variable_p(arg2)) {
	    l = strlen(GET_NAME(arg1));
	    memset(str, '\0', STRSIZE);
	    strcpy(str, GET_NAME(arg1));
	    for (i = 0; i < l; i++)
		bridge[i] = str[i];

	    bridge[l] = '.';
	    bridge[l + 1] = 0;
	    read_string_term(0);	//initilize 
	    bridge_flag = 1;
	    res = readparse(th);
	    bridge_flag = 0;
	    if (unify(arg2, res, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (wide_variable_p(arg1)) {
	    memset(bridge, '\0', sizeof(bridge));
	    bridge_flag = 1;
	    print(arg2);
	    bridge_flag = 0;
	    res = makestr(bridge);
	    if (unify(arg1, res, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "string_term ", arglist, th);
    return (NO);
}

int read_string_term(int flag)
{
    static int pos = 0;

    if (flag == 0) {
	pos = 0;
	return (0);
    } else if (flag == -1) {
	pos--;
	return (-1);
    }


    return (bridge[pos++]);
}

int b_substring(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, arg4, i, j, k, start, len, str;
    char str1[STRSIZE], str2[STRSIZE];

    n = length(arglist);
    if (n == 4) {
	arg1 = car(arglist);	//instring
	arg2 = cadr(arglist);	//start
	arg3 = caddr(arglist);	//length
	arg4 = cadddr(arglist);	//outstring

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "substring ", arg1, th);
	if (!stringp(arg1))
	    error(NOT_STR, "substring ", arg1, th);
	if (!wide_variable_p(arg4) && !stringp(arg4))
	    error(NOT_STR, "substring ", arg4, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    error(LESS_THAN_ZERO, "substring ", arg2, th);
	if (integerp(arg3) && GET_INT(arg3) < 0)
	    error(LESS_THAN_ZERO, "substring ", arg3, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    error(NOT_INT, "substring ", arg2, th);
	if (!wide_variable_p(arg3) && !wide_integer_p(arg3))
	    error(NOT_INT, "substring ", arg3, th);



	strcpy(str1, GET_NAME(arg1));
	start = GET_INT(arg2);
	len = GET_INT(arg3);
	if (string_length(arg1) < start + len - 1)
	    error(OUT_OF_RANGE, "substring ", list2(arg2, arg3), th);
	i = 0;
	j = start - 1;
	k = start + len - 1;
	memset(str2, '\0', STRSIZE);
	while (j < k) {
	    str2[i] = str1[j];
	    i++;
	    j++;
	}
	str = makestr(str2);
	if (unify(arg4, str, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "substring ", arglist, th);
    return (NO);
}


int b_float_text(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3;
    char str[STRSIZE], format[STRSIZE];
    double flt;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !floatp(arg1))
	    error(NOT_FLT, "float_text ", arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    error(NOT_STR, "float_text ", arg2, th);

	if (floatp(arg1)) {
	    int n, d;
	    n = makevariant(th);
	    if (unify(arg3, makeconst("general"), th) == YES) {
		sprintf(str, "%g", GET_FLT(arg1));
		if (unify(arg2, makestr(str), th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    } else
		if (unify
		    (arg3, wcons(makepred("fixed"), wcons(n, NIL, th), th),
		     th) == YES) {
		d = GET_INT(deref(n, th));
		if (d > 15)
		    d = 15;
		else if (d < 0)
		    d = 0;
		sprintf(format, "%%-%d.%df", d, d);
		sprintf(str, format, GET_FLT(arg1));
		if (unify(arg2, makestr(str), th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    } else
		if (unify
		    (arg3,
		     wcons(makepred("scientific"), wcons(n, NIL, th), th),
		     th)
		    == YES) {
		d = GET_INT(deref(n, th));
		if (d > 15)
		    d = 15;
		else if (d < 0)
		    d = 0;
		sprintf(format, "%%-.%de", d);
		sprintf(str, format, GET_FLT(arg1));
		if (unify(arg2, makestr(str), th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    } else
		return (NO);

	} else if (stringp(arg2)) {
	    flt = atof(GET_NAME(arg2));
	    if (unify(arg1, makeflt(flt), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}
	return (NO);
    }
    error(ARITY_ERR, "float_text ", arglist, th);
    return (NO);
}

int b_int_text(int arglist, int rest, int th)
{
    int n, arg1, arg2, i;
    char str[STRSIZE];

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1) && !integerp(arg1))
	    error(NOT_FLT, "int_text ", arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    error(NOT_STR, "int_text ", arg2, th);

	if (integerp(arg1)) {
	    sprintf(str, "%d", get_int(arg1));
	    if (unify(arg2, makestr(str), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (stringp(arg2)) {
	    i = atoi(GET_NAME(arg2));
	    if (unify(arg1, makeint(i), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}
	return (NO);
    }
    error(ARITY_ERR, "int_text ", arglist, th);
    return (NO);
}


//controle
int b_cut(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "! ", arglist, th);
    return (NO);
}

int b_ifthen(int arglist, int rest, int th)
{
    int n, arg1, arg2, save1;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	save1 = sp[th];
	if (variablep(arg1))
	    error(INSTANTATION_ERR, "ifthen ", arg1, th);
	if (variablep(arg2))
	    error(INSTANTATION_ERR, "ifthen ", arg2, th);

	if (prove_all(arg1, sp[th], th) == YES) {
	    return (prove_all(addtail_body(rest, arg2, th), sp[th], th));
	} else {
	    unbind(save1, th);
	    return (NO);
	}

	unbind(save1, th);
	return (NO);
    }
    error(ARITY_ERR, "ifthen ", arglist, th);
    return (NO);
}

int b_ifthenelse(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (variablep(arg1))
	    error(INSTANTATION_ERR, "ifthenelse ", arg1, th);
	if (variablep(arg2))
	    error(INSTANTATION_ERR, "ifthenelse ", arg2, th);
	if (variablep(arg3))
	    error(INSTANTATION_ERR, "ifthenelse ", arg3, th);

	save = sp[th];
	if (prove_all(arg1, sp[th], th) == YES) {
	    return (prove_all(addtail_body(rest, arg2, th), sp[th], th));
	} else {
	    unbind(save, th);
	    return (prove_all(addtail_body(rest, arg3, th), sp[th], th));
	}
    }
    error(ARITY_ERR, "ifthenelse ", arglist, th);
    return (NO);
}



double getETime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double) tv.tv_usec * 1e-6;
}

int b_measure(int arglist, int rest, int th)
{
    int n, arg1;
    double start_time, end_time, time, lips;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	proof[th] = 0;
	start_time = getETime();	//time_flag on and it store start time
	prove_all(arg1, sp[th], th);
	end_time = getETime();
	time = end_time - start_time;
	lips = (double) proof[th] / time;
	ESCFGREEN;
	printf("Elapsed Time=%.6f (second)  %.0f(LIPS)\n", time, lips);
	ESCFORG;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "measure ", arglist, th);
    return (NO);
}


int b_trace(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	debug_flag = ON;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "trace ", arglist, th);
    return (NO);
}

int b_notrace(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	debug_flag = OFF;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "notrace ", arglist, th);
    return (NO);
}

int b_spy(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 0) {
	print(spy_list);
	return (prove_all(rest, sp[th], th));
    } else if (n == 1) {
	arg1 = car(arglist);
	arg1 = copy_heap(arg1);

	if (!memberp(arg1, spy_list))
	    spy_list = cons(arg1, spy_list);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "spy ", arglist, th);
    return (NO);
}

int b_nospy(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 0) {
	while (!nullp(spy_list)) {
	    spy_list = cdr(spy_list);
	}
	return (prove_all(rest, sp[th], th));
    } else if (n == 1) {
	arg1 = car(arglist);
	arg1 = copy_heap(arg1);
	spy_list = listremove(arg1, spy_list);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "nospy ", arglist, th);
    return (NO);
}

int b_leash(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (arg1 == makeatom("full", SIMP)) {
	    trace_flag = FULL;
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("tight", SIMP)) {
	    trace_flag = TIGHT;
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("half", SIMP)) {
	    trace_flag = HALF;
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("off", SIMP)) {
	    trace_flag = OFF;
	    return (prove_all(rest, sp[th], th));
	} else
	    return (NO);
    }
    error(ARITY_ERR, "leash ", arglist, th);
    return (NO);
}

int b_debug(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	printf("debug_flag=%d\n", debug_flag);
	printf("trace_flag=%d\n", trace_flag);
	printf("spy_list=");
	print(spy_list);
	printf("\n");
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "debug ", arglist, th);
    return (NO);
}

int b_break(int arglist, int rest, int th)
{
    int n, ret, save1, save2;

    n = length(arglist);
    if (n == 0) {
	break_flag = 1;
	save1 = wp[th];
	save2 = sp[th];
      repl:
	ret = setjmp(buf2);
	if (ret == 0) {
	    while (1) {
		printf("?= ");
		fflush(stdout);
		query_break(variable_to_call(readparse(th)), th);
		fflush(stdout);
	    }
	} else if (ret == 1) {
	    ret = 0;
	    wp[th] = save1;
	    sp[th] = save2;
	    return (prove_all(rest, sp[th], th));
	} else {
	    goto repl;
	}
    }
    error(ARITY_ERR, "break ", arglist, th);
    return (NO);
}

int b_end_of_file(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	if (break_flag) {
	    variables[th] = variables_save[th];
	    break_flag = 0;
	    longjmp(buf2, 1);
	} else
	    return (YES);
    }
    error(ARITY_ERR, "end_of_file ", arglist, th);
    return (NO);
}

int b_halt(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	if (parent_flag)
	    error(SYSTEM_ERROR, "Execute dp_close before halting. ", NIL,
		  th);

	printf("- good bye -\n");
	longjmp(buf, 2);
    }
    error(ARITY_ERR, "halt ", arglist, th);
    return (NO);
}

int b_abort(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	longjmp(buf, 1);
    }
    error(ARITY_ERR, "abort ", arglist, th);
    return (NO);
}


//check data type
int b_atom(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (atomp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "atom ", arglist, th);
    return (NO);
}

int b_integer(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (integerp(arg1) || longnump(arg1) || bignump(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "integer ", arglist, th);
    return (NO);
}

int b_real(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (floatp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "real ", arglist, th);
    return (NO);
}

int b_number(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (numberp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "number ", arglist, th);
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

int b_system(int arglist, int rest, int th)
{
    int n, arg1, save1, save2, syslist, pred;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!wide_variable_p(arg1) && !structurep(arg1))
	    error(WRONG_ARGS, "system", arg1, th);

	syslist = reverse(builtins);
	save1 = wp[th];
	save2 = sp[th];
	while (!nullp(syslist)) {
	    pred = car(syslist);
	    syslist = cdr(syslist);
	    if (unify(arg1, pred, th) == YES)
		if (prove(NIL, sp[th], rest, th) == YES)
		    return (YES);

	    wp[th] = save1;
	    unbind(save2, th);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }

    error(ARITY_ERR, "system ", arglist, th);
    return (NO);
}

int b_var(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (variablep(arg1))
	    return (prove_all(rest, sp[th], th));
	else if (anoymousp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "var ", arglist, th);
    return (NO);
}

int b_nonvar(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (variablep(arg1))
	    return (NO);
	else if (anoymousp(arg1))
	    return (NO);
	else
	    return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "nonvar ", arglist, th);
    return (NO);
}

int b_atomic(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (atomicp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "atomic ", arglist, th);
    return (NO);
}

int b_list(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (listp(arg1) || nullp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "list ", arglist, th);
    return (NO);
}

int b_string(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (stringp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "string ", arglist, th);
    return (NO);
}



//-----structure------
int b_functor(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, res, i;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	// to avoid compier bug {}
	if (structurep(arg2) && car(arg2) == CURL && length(arg2) == 1)
	    arg2 = CURL;

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "functor ", list2(arg1, arg2), th);
	if (wide_variable_p(arg1) && wide_variable_p(arg3))
	    error(INSTANTATION_ERR, "functor ", list2(arg1, arg3), th);
	if (wide_variable_p(arg1) && !atomicp(arg2)) {
	    error(NOT_ATOMIC, "functor ", arg2, th);
	}
	if (wide_variable_p(arg1) && integerp(arg3) && GET_INT(arg3) < 0)
	    error(LESS_THAN_ZERO, "functor ", arg3, th);
	if (wide_variable_p(arg1) && !integerp(arg3))
	    error(NOT_INT, "functor ", arg3, th);
	if (wide_variable_p(arg1) && atomicp(arg2) &&
	    !atomp(arg2) && integerp(arg3) && GET_INT(arg3) > 0)
	    error(NOT_ATOM, "functor ", arg2, th);


	if (listp(arg1) && atomp(arg2) && integerp(arg3)) {
	    i = GET_INT(arg3);
	    if (i == 0) {
		if (unify(arg1, arg2, th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    } else {

		if (eqlp(arg2, DOTOBJ) && GET_INT(arg3) == 2)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    }
	} else if (listp(arg1) &&
		   wide_variable_p(arg2) && wide_variable_p(arg3)) {
	    unify(arg2, makeatom(".", SYS), th);
	    unify(arg3, makeint(2), th);
	    return (prove_all(rest, sp[th], th));
	} else if (structurep(arg1)) {
	    if (unify(car(arg1), arg2, th) == YES &&
		unify(makeint(length(cdr(arg1))), arg3, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (variablep(arg1) && constantp(arg2) && integerp(arg3)) {
	    i = GET_INT(arg3);
	    if (i == 0) {
		if (unify(arg1, arg2, th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    } else {
		res = NIL;
		while (i > 0) {
		    res = cons(makevariant(th), res);
		    i--;
		}
		res = reverse(res);
		if (GET_AUX(arg2) == SIMP)
		    SET_AUX(arg2, PRED);
		res = cons(arg2, res);
		if (arg2 == DOTOBJ && GET_INT(arg3) == 2)
		    res = operate(res, th);
		if (unify(arg1, res, th) == YES)
		    return (prove_all(rest, sp[th], th));
		else
		    return (NO);
	    }
	} else if (atomicp(arg1)) {
	    if (unify(arg1, arg2, th) == YES
		&& unify(makeint(th), arg3, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "functor ", arglist, th);
    return (NO);
}

int b_arg(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, elt, i;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "arg ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "arg ", arg2, th);
	if (!integerp(arg1))
	    error(NOT_INT, "arg ", arg1, th);
	if (!compoundp(arg2))
	    error(NOT_COMPOUND, "arg ", arg2, th);
	if (integerp(eval(arg1, th)) && GET_INT(eval(arg1, th)) < 0)
	    error(LESS_THAN_ZERO, "arg ", arg1, th);

	if (integerp(arg1) && structurep(arg2)) {
	    i = GET_INT(arg1);
	    if (i < 1 || i >= length(arg2))
		return (NO);
	    elt = nth(cdr(arg2), i);
	    if (unify(arg3, elt, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}
    }
    error(ARITY_ERR, "arg ", arglist, th);
    return (NO);
}

int b_arg0(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, elt, i;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "arg0 ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "arg0 ", arg2, th);
	if (!integerp(arg1))
	    error(NOT_INT, "arg0 ", arg1, th);
	if (!compoundp(arg2))
	    error(NOT_COMPOUND, "arg0 ", arg2, th);
	if (integerp(eval(arg1, th)) && GET_INT(eval(arg1, th)) < 0)
	    error(LESS_THAN_ZERO, "arg0 ", arg1, th);

	if (integerp(arg1) && structurep(arg2)) {
	    i = GET_INT(arg1) + 1;
	    if (i < 1 || i >= length(arg2))
		return (NO);
	    elt = nth(cdr(arg2), i);
	    if (unify(arg3, elt, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}
    }
    error(ARITY_ERR, "arg0 ", arglist, th);
    return (NO);
}


//-----other----
int b_listing(int arglist, int rest, int th)
{
    int n, arg1, clauses, pred, list, temp;

    n = length(arglist);
    if (n == 0) {
	list = listreverse(predicates);
	listing_flag = 1;
	while (!nullp(list)) {
	    pred = car(list);
	    list = cdr(list);
	    clauses = GET_CAR(pred);
	    while (!nullp(clauses)) {
		print(car(clauses));
		fprintf(GET_PORT(output_stream), ".\n");
		clauses = cdr(clauses);
	    }
	}
	listing_flag = 0;
	return (prove_all(rest, sp[th], th));
    }
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1) && !structurep(arg1))
	    error(WRONG_ARGS, "listing ", arglist, th);
	if (atomp(arg1)) {
	    clauses = GET_CAR(arg1);
	    listing_flag = 1;
	    while (!nullp(clauses)) {
		print(car(clauses));
		fprintf(GET_PORT(output_stream), ".\n");
		clauses = cdr(clauses);
	    }
	    listing_flag = 0;
	    return (prove_all(rest, sp[th], th));
	} else if (eqlp(car(arg1), makeope("/")) &&
		   atomp(cadr(arg1)) && integerp(caddr(arg1))) {
	    clauses = GET_CAR(cadr(arg1));
	    listing_flag = 1;
	    while (!nullp(clauses)) {
		temp = car(clauses);
		if (predicatep(temp)
		    && length(cdr(temp)) == GET_INT(caddr(arg1))) {
		    print(temp);
		    fprintf(GET_PORT(output_stream), ".\n");
		} else if (clausep(temp)
			   && length(cdr(cadr(temp))) ==
			   GET_INT(caddr(arg1))) {
		    print(temp);
		    fprintf(GET_PORT(output_stream), ".\n");
		}
		clauses = cdr(clauses);
	    }
	    listing_flag = 0;
	    return (prove_all(rest, sp[th], th));
	} else {
	    error(WRONG_ARGS, "listing ", arglist, th);
	}
    }
    error(ARITY_ERR, "listing ", arglist, th);
    return (NO);
}


//transform bwtween predicate and data
int b_univ(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (variablep(arg1) && variablep(arg2))
	    error(INSTANTATION_ERR, "=.. ", list2(arg1, arg2), th);
	if (listp(arg2) && compoundp(car(arg2)))
	    error(NOT_ATOMIC, "=.. ", arg2, th);
	if (variablep(arg1) && nullp(arg2))
	    error(NON_EMPTY_LIST, "=.. ", arg2, th);



	if (!wide_variable_p(arg1) && atomicp(arg1)) {
	    res = list1(arg1);
	    SET_AUX(res, LIST);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (predicatep(arg1)) {
	    res = structure_to_list(arg1);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (builtinp(arg1)) {
	    res = structure_to_list(arg1);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (compiledp(arg1)) {
	    res = structure_to_list(arg1);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (operationp(arg1)) {
	    res = structure_to_list(arg1);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (user_operation_p(arg1)) {
	    res = structure_to_list(arg1);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (functionp(arg1)) {
	    res = structure_to_list(arg1);
	    if (unify(res, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (variablep(arg1) && listp(arg2)) {
	    if (car(arg2) == DOTOBJ) {
		arg2 = operate(arg2, th);
		SET_AUX(arg2, 0);
	    } else if (numberp(car(arg2))) {
		return (NO);
	    } else if (GET_AUX(car(arg2)) != SYS &&
		       GET_AUX(car(arg2)) != COMP &&
		       GET_AUX(car(arg2)) != OPE) {
		arg2 = list_to_structure(arg2);
		SET_AUX(car(arg2), PRED);
	    } else {
		arg2 = list_to_structure(arg2);
	    }
	    if (unify(arg1, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (listp(arg1)) {
	    arg1 = list3(DOTOBJ, car(arg1), cdr(arg1));
	    SET_AUX(arg1, LIST);
	    if (unify(arg1, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else {
	    if (unify(arg1, arg2, th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}
    }
    error(ARITY_ERR, "=.. ", arglist, th);
    return (NO);
}

int b_current_predicate(int arglist, int rest, int th)
{
    int n, arg1, save1, save2, predlist, pred, aritylist, arity;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!atomp(arg1) && !wide_variable_p(arg1) && !structurep(arg1))
	    error(WRONG_ARGS, "current_predicate ", arg1, th);

	predlist = reverse(predicates);
	save1 = wp[th];
	save2 = sp[th];
	while (!nullp(predlist)) {
	    pred = car(predlist);
	    predlist = cdr(predlist);
	    aritylist = GET_ARITY(pred);
	    while (!nullp(aritylist)) {
		arity = car(aritylist);
		aritylist = cdr(aritylist);
		if (unify(arg1, list3(makeatom("/", OPE), pred, arity), th)
		    == YES)
		    if (prove(NIL, sp[th], rest, th) == YES)
			return (YES);

		wp[th] = save1;
		unbind(save2, th);
	    }
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "current_predicate ", arglist, th);
    return (NO);
}


int specp(int x)
{
    if (x == makeatom("xfx", SIMP))
	return (1);
    else if (x == makeatom("yfx", SIMP))
	return (1);
    else if (x == makeatom("xfy", SIMP))
	return (1);
    else if (x == makeatom("fx", SIMP))
	return (1);
    else if (x == makeatom("fy", SIMP))
	return (1);
    else if (x == makeatom("xf", SIMP))
	return (1);
    else if (x == makeatom("yf", SIMP))
	return (1);
    else
	return (0);
}

int b_current_op(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, save2, lis, weight, spec, op, w, s, o;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !integerp(arg1))
	    error(NOT_INT, "current_op ", arg1, th);
	if (integerp(arg1) && (GET_INT(arg1) < 0 || GET_INT(arg1) > 1200))
	    error(OPE_PRIORITY_ERR, "current_op ", arg1, th);
	if (!wide_variable_p(arg2) && !specp(arg2))
	    error(OPE_SPEC_ERR, "current_op ", arg2, th);
	if (!wide_variable_p(arg3) && !atomp(arg3))
	    error(NOT_ATOM, "current_op ", arg3, th);


	/*
	   e.g. ',' ':-'  aux of operator is SIMP
	   beclause of parsing. so change to OPE from SIMP
	 */
	if (getatom(GET_NAME(arg3), OPE, hash(GET_NAME(arg3))))
	    arg3 = makeatom(GET_NAME(arg3), OPE);

	lis = op_list;
	spec = NIL;
	save1 = wp[th];
	save2 = sp[th];
	while (!nullp(lis)) {
	    weight = car(car(lis));
	    spec = cadr(car(lis));
	    op = caddr(car(lis));

	    w = unify(arg1, weight, th);
	    s = unify(arg2, spec, th);
	    o = unify(arg3, op, th);
	    if (w == YES && s == YES && o == YES)
		if (prove(NIL, sp[th], rest, th) == YES)
		    return (YES);
	    lis = cdr(lis);
	    wp[th] = save1;
	    unbind(save2, th);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "current_op ", arglist, th);
    return (NO);
}

int b_predicate_property(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);	//term
	arg2 = cadr(arglist);	//prop

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "predicate_property ", arg1, th);

	if (atomp(arg1) && GET_AUX(arg1) == SYS) {
	    if (unify(arg2, makeconst("built_in"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg1) && GET_AUX(car(arg1)) == SYS) {
	    if (unify(arg2, makeconst("built_in"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (atomp(arg1) && GET_AUX(arg1) == PRED &&
		   GET_CAR(arg1) != NIL) {
	    if (unify(arg2, makeconst("dynamic"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg1) && GET_AUX(car(arg1)) == PRED &&
		   GET_CAR(car(arg1)) != NIL) {
	    if (unify(arg2, makeconst("dynamic"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (atomp(arg1) && GET_AUX(arg1) == COMP) {
	    if (unify(arg2, makeconst("static"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (structurep(arg1) && GET_AUX(car(arg1)) == COMP) {
	    if (unify(arg2, makeconst("static"), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "predicate_property ", arglist, th);
    return (NO);

}


int b_reset_op(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	initoperator();
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "reset_op ", arglist, th);
    return (NO);
}

int o_define(int x, int y, int th)
{
    int clause;

    if (!nullp(y)) {
	if (builtinp(x))
	    error(BUILTIN_EXIST, "assertz", x, th);
	if (atomp(x))
	    SET_AUX(x, PRED);
	clause = list3(NECK, x, y);
	SET_AUX(clause, CLAUSE);
	SET_VAR(clause, reverse(unique(varslist(clause))));

	if (assert_flag) {
	    if (atomp(x))
		insert_data(cadr(clause), clause);
	    else
		insert_data(car(cadr(clause)), clause);
	} else {
	    if (atomp(x))
		add_data(cadr(clause), clause);
	    else
		add_data(car(cadr(clause)), clause);
	}

	return (YES);
    }
    // :- predicate.
    else {
	return (prove_all(x, sp[th], th));
    }
    return (NO);
}

int o_dcg(int x, int y, int th)
{
    int clause, res;

    clause = list2(makepred("dcg_expand"),
		   list3(makeatom("-->", OPE), x, y));

    res = prove_all(clause, sp[th], th);
    return (res);
}



int b_gbc(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (arg1 == makeconst("full")) {
	    gbc();
	    return (prove_all(rest, sp[th], th));
	} else {
	    error(WRONG_ARGS, "gc ", arglist, th);
	}
    }
    error(ARITY_ERR, "gc ", arglist, th);
    return (NO);
}



int o_ignore(int nest, int n, int th)
{
    return (YES);
}


//-----------file system-------------------
int b_mkdir(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "mkdir ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "mkdir ", arg1, th);

	mkdir(GET_NAME(arg1), 0777);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "mkdir ", arglist, th);
    return (NO);
}


int b_rmdir(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "rmdir ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "rmdir ", arg1, th);

	rmdir(GET_NAME(arg1));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "rmdir ", arglist, th);
    return (NO);
}


int b_chdir(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "chdir ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "chdir ", arg1, th);

	if (chdir(GET_NAME(arg1)) != -1)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "chdir ", arglist, th);
    return (NO);
}

int b_delete(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "delete ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "delete ", arg1, th);

	remove(GET_NAME(arg1));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "delete ", arglist, th);
    return (NO);
}


int b_rename(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "rename ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "rename ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "rename ", arg2, th);
	if (!atomp(arg2))
	    error(NOT_ATOM, "rename ", arg2, th);


	rename(GET_NAME(arg1), GET_NAME(arg2));
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "rename ", arglist, th);
    return (NO);
}

char *prolog_file_name(char *name)
{
    int n, i;
    static char str[STRSIZE];

    strcpy(str, name);
    n = strlen(name);

    for (i = 0; i < n; i++) {
	if (str[i] == '.')
	    return (name);
    }

    strcat(str, ".pl");
    return (str);
}

int b_edit(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;
    char str[STRSIZE];
    char *editor;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	arg2 = makeatom("r", SIMP);
	goto edit;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      edit:
	if (!singlep(arg1))
	    error(NOT_ATOM, "edit ", arg1, th);
	if (arg2 != makeatom("r", SIMP) && arg2 != makeatom("c", SIMP))
	    error(WRONG_ARGS, "edit ", arg2, th);


	editor = getenv("EDITOR");
	if (editor == NULL) {
	    strcpy(str, "edlog ");
	    strcat(str, prolog_file_name(GET_NAME(arg1)));
	} else {
	    strcpy(str, editor);
	    strcat(str, " ");
	    strcat(str, prolog_file_name(GET_NAME(arg1)));
	}
	res = system(str);
	if (res == -1)
	    error(SYSTEM_ERROR, "edit ", arg1, th);

	if (arg2 == makeatom("r", SIMP))
	    b_reconsult(list1(arg1), NIL, th);
	else if (arg2 == makeatom("c", SIMP))
	    b_consult(list1(arg1), NIL, th);


	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "edit ", arglist, th);
    return (NO);
}


int b_shell(int arglist, int rest, int th)
{
    int n, arg1, res;
    char str1[STRSIZE];

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!singlep(arg1))
	    error(NOT_ATOM, "shell", arg1, th);

	strcpy(str1, GET_NAME(arg1));
	res = system(str1);
	if (res == -1)
	    error(SYSTEM_ERROR, "shell", arg1, th);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "shell ", arglist, th);
    return (NO);
}


int b_syntaxerrors(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (arg1 != YES && arg1 != NO && !wide_variable_p(arg1))
	    error(ILLEGAL_ARGS, "syntaxerrors ", arg1, th);
	if (arg2 != YES && arg2 != NO && !wide_variable_p(arg2))
	    error(ILLEGAL_ARGS, "syntaxerrors ", arg1, th);

	res = unify(arg1, syntax_flag, th);
	syntax_flag = arg2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "syntaxerrors ", arglist, th);
    return (NO);
}

int b_fileerrors(int arglist, int rest, int th)
{
    int n, arg1, arg2, res;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (arg1 != YES && arg1 != NO && !wide_variable_p(arg1))
	    error(ILLEGAL_ARGS, "fileerrors ", arg1, th);
	if (arg2 != YES && arg2 != NO && !wide_variable_p(arg2))
	    error(ILLEGAL_ARGS, "fileerrors ", arg1, th);

	res = unify(arg1, syntax_flag, th);
	fileerr_flag = arg2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "fileerrors ", arglist, th);
    return (NO);
}

int b_statistics(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (arg1 == makeatom("free", SIMP)) {
	    if (unify(arg2, makeint(fc), th) == YES);
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("wp", SIMP)) {
	    if (unify(arg2, makeint(wp[th]), th) == YES);
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("sp", SIMP)) {
	    if (unify(arg2, makeint(sp[th]), th) == YES);
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("gc", SYS)) {
	    if (unify(arg2, makeint(gc), th) == YES);
	    return (prove_all(rest, sp[th], th));
	} else {
	    return (NO);
	}

    }
    error(ARITY_ERR, "statistics ", arglist, th);
    return (NO);
}



int b_sort(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1) && !nullp(arg1))
	    error(NOT_LIST, "sort ", arg1, th);
	if (!wide_variable_p(arg2) && !listp(arg2) && !nullp(arg2))
	    error(NOT_VAR, "sort ", arg2, th);

	if (unify(arg2, sort(arg1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "sort ", arglist, th);
    return (NO);
}

int b_keysort(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1) && !nullp(arg1))
	    error(NOT_LIST, "key_sort ", arg1, th);
	if (!wide_variable_p(arg2) && !listp(arg2) && !nullp(arg2))
	    error(NOT_VAR, "key_sort ", arg2, th);

	if (unify(arg2, keysort(arg1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "keysort ", arglist, th);
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

//------------------------------------------------

int b_inc(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "inc ", list2(arg1, arg2), th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    error(NOT_INT, "inc ", arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    error(NOT_INT, "inc ", arg2, th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    error(NOT_INT, "inc ", arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    error(NOT_INT, "inc ", arg2, th);
	if (wide_integer_p(arg1) && negativep(arg1))
	    error(LESS_THAN_ZERO, "inc ", arg1, th);
	if (wide_integer_p(arg2) && negativep(arg2))
	    error(LESS_THAN_ZERO, "inc ", arg2, th);

	if (wide_variable_p(arg1)) {
	    if (unify(arg1, minus(arg2, makeint(1), th), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (wide_variable_p(arg2)) {
	    if (unify(arg2, plus(arg1, makeint(1), th), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else {
	    if (unify(arg2, plus(arg1, makeint(1), th), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}

    }
    error(ARITY_ERR, "inc ", arglist, th);
    return (NO);
}

int b_dec(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "dec ", list2(arg1, arg2), th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    error(NOT_INT, "dec ", arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    error(NOT_INT, "dec ", arg2, th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    error(NOT_INT, "dec ", arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    error(NOT_INT, "dec ", arg2, th);
	if (wide_integer_p(arg1) && negativep(arg1))
	    error(LESS_THAN_ZERO, "dec ", arg1, th);
	if (wide_integer_p(arg2) && negativep(arg2))
	    error(LESS_THAN_ZERO, "dec ", arg2, th);

	if (wide_variable_p(arg1)) {
	    if (unify(arg1, plus(arg2, makeint(1), th), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else if (wide_variable_p(arg2)) {
	    if (unify(arg2, minus(arg1, makeint(1), th), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	} else {
	    if (unify(arg2, minus(arg1, makeint(1), th), th) == YES)
		return (prove_all(rest, sp[th], th));
	    else
		return (NO);
	}

    }
    error(ARITY_ERR, "dec ", arglist, th);
    return (NO);
}

int b_ansi_cup(int arglist, int rest, int th)
{
    int n, arg1, arg2, r, c;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "ansi_cup ", arg1, th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    error(NOT_INT, "ansi_cup ", arg1, th);
	if (wide_integer_p(arg1) && negativep(arg1))
	    error(LESS_THAN_ZERO, "ansi_cup ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "ansi_cup ", arg2, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    error(NOT_INT, "ansi_cup ", arg2, th);
	if (wide_integer_p(arg2) && negativep(arg2))
	    error(LESS_THAN_ZERO, "ansi_cup ", arg2, th);

	r = get_int(arg1);
	c = get_int(arg2);
	ESCMOVE(r, c);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_cup ", arglist, th);
    return (NO);
}

// set stdin non canonical mode
void set_input_mode(struct termios *original)
{
    struct termios new_mode;
    tcgetattr(STDIN_FILENO, original);	// save original setting
    new_mode = *original;
    new_mode.c_lflag &= ~(ICANON | ECHO);	// set non canonical and echooff 
    tcsetattr(STDIN_FILENO, TCSANOW, &new_mode);	// apply new setting
}

// restore original setting.
void reset_input_mode(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}

// get cursor position on terminal
cursor get_cursor(void)
{
    char buf[32];
    int row, col;
    int i = 0;
    struct termios original;

    set_input_mode(&original);

    printf("\033[6n");
    fflush(stdout);

    // read from stdin to buffer (e.g. \033[12;40R)
    while (i < sizeof(buf) - 1) {
	if (read(STDIN_FILENO, buf + i, 1) != 1) {
	    break;
	}
	if (buf[i] == 'R') {
	    break;
	}
	i++;
    }
    buf[i] = '\0';

    if (sscanf(buf, "\033[%d;%dR", &row, &col) != 2) {
	error(SYSTEM_ERROR, "ansi_cpr ", NIL, 0);
    }
    // restore original setting
    reset_input_mode(&original);

    cursor position;
    position.row = row;
    position.col = col;

    return position;
}


int b_ansi_cpr(int arglist, int rest, int th)
{
    int n, arg1, arg2, r, c, res1, res2;
    cursor position;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1))
	    error(NOT_VAR, "ansi_cpr ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "ansi_cpr ", arg2, th);

	position = get_cursor();
	r = makeint(position.row);
	c = makeint(position.col);
	res1 = unify(arg1, r, 0);
	res2 = unify(arg2, c, 0);
	if (res1 == YES && res2 == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "ansi_cpr ", arglist, th);
    return (NO);
}

int b_ansi_scp(int arglist, int rest, int th)
{
    int n;
    cursor position;

    n = length(arglist);
    if (n == 0) {
	position = get_cursor();

	cursor_row_store = position.row;
	cursor_col_store = position.col;
	cursor_color_store = cursor_color;
	cursor_style_store = cursor_style;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_scp ", arglist, th);
    return (NO);
}

int b_ansi_rcp(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	ESCMOVE(cursor_row_store, cursor_col_store);
	ESCCOLOR(cursor_color_store);
	ESCCOLOR(cursor_style_store);
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_rcp ", arglist, th);
    return (NO);
}

int b_ansi_ed(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	ESCCLS;
	ESCTOP;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_ed ", arglist, th);
    return (NO);
}

int b_ansi_el(int arglist, int rest, int th)
{
    int n;

    n = length(arglist);
    if (n == 0) {
	ESCCLSL1;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_el ", arglist, th);
    return (NO);
}


int b_ansi_cuu(int arglist, int rest, int th)
{
    int n, arg1, m;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "ansi_cuu ", arg1, th);
	if (!integerp(arg1))
	    error(NOT_INT, "ansi_cuu ", arg1, th);
	if (negativep(arg1))
	    error(LESS_THAN_ZERO, "ansi_cuu ", arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVU;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_cuu ", arglist, th);
    return (NO);
}

int b_ansi_cud(int arglist, int rest, int th)
{
    int n, arg1, m;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "ansi_cud ", arg1, th);
	if (!integerp(arg1))
	    error(NOT_INT, "and_cud ", arg1, th);
	if (negativep(arg1))
	    error(LESS_THAN_ZERO, "ansi_cud ", arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVD;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_cud ", arglist, th);
    return (NO);
}

int b_ansi_cuf(int arglist, int rest, int th)
{
    int n, arg1, m;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "ansi_cuf ", arg1, th);
	if (!integerp(arg1))
	    error(NOT_INT, "and_cuf ", arg1, th);
	if (negativep(arg1))
	    error(LESS_THAN_ZERO, "ansi_cuf ", arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVR;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_cuf ", arglist, th);
    return (NO);
}

int b_ansi_cub(int arglist, int rest, int th)
{
    int n, arg1, m;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "ansi_cub ", arg1, th);
	if (!integerp(arg1))
	    error(NOT_INT, "and_cub ", arg1, th);
	if (negativep(arg1))
	    error(LESS_THAN_ZERO, "ansi_cub ", arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVL;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_cub ", arglist, th);
    return (NO);
}

int b_ansi_sgr(int arglist, int rest, int th)
{
    int n, arg1, m;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "ansi_sgr ", arg1, th);
	if (!integerp(arg1))
	    error(NOT_INT, "and_sgr ", arg1, th);
	if (negativep(arg1))
	    error(LESS_THAN_ZERO, "ansi_sgr ", arg1, th);
	if (get_int(arg1) > 47)
	    error(WRONG_ARGS, "ansi_sgr ", arg1, th);

	m = get_int(arg1);
	ESCCOLOR(m);
	if (m < 10)
	    cursor_style = m;
	else
	    cursor_color = m;
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "ansi_sgr ", arglist, th);
    return (NO);
}



int b_date(int arglist, int rest, int th)
{
    int n, arg1, res;
    struct tm *jst;
    time_t t;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (!wide_variable_p(arg1))
	    error(NOT_VAR, "date ", arg1, th);

	t = time(NULL);
	jst = localtime(&t);
	res =
	    list4(makepred("date"), makeint(jst->tm_year + 1900),
		  makeint(jst->tm_mon + 1), makeint(jst->tm_mday));
	if (unify(arg1, res, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "date ", arglist, th);
    return (NO);
}

int b_date_day(int arglist, int rest, int th)
{
    int n, arg1, arg2, y, m, d, w;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!(structurep(arg1) && length(arg1) == 4))
	    error(WRONG_ARGS, "date_day ", arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    error(NOT_VAR, "date_day", arg2, th);

	y = get_int(cadr(arg1));
	m = get_int(caddr(arg1));
	d = get_int(cadddr(arg1));
	if (m < 3) {
	    y--;
	    m += 12;
	}
	w = (y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7;
	if (unify(arg2, makeint(w), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "date_day ", arglist, th);
    return (NO);
}

int b_time(int arglist, int rest, int th)
{
    int n, arg1, res;
    struct tm *jst;
    time_t t;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	t = time(NULL);
	jst = localtime(&t);
	res =
	    list4(makepred("time"), makeint(jst->tm_hour),
		  makeint(jst->tm_min), makeint(jst->tm_sec));
	if (unify(arg1, res, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "time ", arglist, th);
    return (NO);
}

int b_errcode(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	if (unify(arg1, makeint(error_code), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "errorcode ", arglist, th);
    return (NO);
}


//-----------record and hash-----------------------------
/*
<record>
key name. set record area top address of list.
list [term1,term2,...]
Refnum is address of each term.

<hash table>
atom of hashtable name. set arity area hash_pt.
record_hash_table [HASHTBSIZE][ID]
ID=1... (ID starts from 1)
record_hash_table
 0,  1,  2,
[pt0,pt1,pt2,....]
 |    |
 |    |- list of hash==1
 |- list of hash==0

*/

int b_recordh(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, data, record_id, index;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);	//table_name
	arg2 = cadr(arglist);	//sort_key
	arg3 = caddr(arglist);	//term instance address
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "recordh ", arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "recordh ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "recordh ", arg2, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    error(NOT_ATOM, "recordh ", arg2, th);


	arg3 = deref(arg3, th);
	if (!integerp(arg3))
	    error(NOT_INT, "recordh ", arg3, th);

	if (record_pt >= RECORDMAX)
	    error(RECORD_OVERF, "recordh ", NIL, th);
	if (GET_ARITY(arg1) == NIL) {
	    SET_ARITY(arg1, record_pt);
	    record_pt++;
	}
	record_id = GET_ARITY(arg1) - 1;	//id starts from 1
	index = hash(GET_NAME(arg2));
	data = cons(arg2, arg3);
	add_hash_table(data, record_id, index);
	checkgbc();
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "recordh ", arglist, th);
    return (NO);
}

int b_retrieveh(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, record_id, index, lis, term;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);	//table name
	arg2 = cadr(arglist);	//sort key
	arg3 = caddr(arglist);	//term instance address
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "retrieveh ", arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "retrieveh ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "retrieveh ", arg2, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    error(NOT_ATOM, "retrieveh ", arg2, th);


	save1 = sp[th];
	record_id = GET_ARITY(arg1) - 1;	//id starts from 1
	if (record_id < 0)
	    error(NOT_RECORD, "retrieveh ", arg1, th);
	index = hash(GET_NAME(arg2));
	lis = record_hash_table[index][record_id];
	while (lis != NIL) {
	    term = car(lis);
	    if (car(term) != arg2)
		goto skip;

	    unify(arg3, cdr(term), th);
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);

	    unbind(save1, th);
	  skip:
	    lis = cdr(lis);
	}
	return (NO);
    }
    error(ARITY_ERR, "retrieveh ", arglist, th);
    return (NO);
}


int b_instance(int arglist, int rest, int th)
{
    int n, arg1, arg2;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "instance ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "instance ", arg2, th);

	if (unify(arg2, car(get_int(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "instance ", arglist, th);
    return (NO);
}


int b_recordz(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, temp, chain, next;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);	//key
	arg2 = cadr(arglist);	//term
	arg3 = caddr(arglist);	//ref 

	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "recordz ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "recordz ", arg1, th);
	if (builtinp(arg1))
	    error(BUILTIN_EXIST, "recordz ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "recordz ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "recordz ", arg3, th);

	arg1 = makeatom(GET_NAME(arg1), SIMP);
	temp = GET_RECORD(arg1);
	arg2 = copy_heap(arg2);	//copy arg2 to heap area
	if (temp == NIL) {
	    SET_RECORD(arg1, bcons(arg2, NIL));
	    key_list = cons(arg1, key_list);
	} else {
	    while (cdr(temp) != NIL) {
		temp = cdr(temp);
	    }
	    next = bcons(arg2, NIL);
	    SET_CDR(temp, next);
	    SET_AUX(next, temp);	// bidirectional data
	}
	checkgbc();
	if (temp == NIL)
	    chain = GET_RECORD(arg1);
	else
	    chain = cdr(temp);


	if (unify(arg3, makeint(chain), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "recordz ", arglist, th);
    return (NO);
}

int b_record_after(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, chain, chain1;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "record_after ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "record_after ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "record_after ", arg3, th);

	chain = get_int(arg1);
	if (car(chain) == NIL)
	    return (NO);

	arg2 = copy_heap(arg2);
	chain1 = bcons(arg2, cdr(chain));
	SET_CDR(chain, chain1);	// make bidirectional list
	SET_AUX(chain1, chain);	// 

	if (unify(arg3, makeint(chain1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    error(ARITY_ERR, "record_after ", arglist, th);
    return (NO);
}


int b_recorda(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, chain;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "recorda ", arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "recorda ", arg1, th);
	if (builtinp(arg1))
	    error(BUILTIN_EXIST, "recorda ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "recorda ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "recorda ", arg3, th);

	arg1 = makeatom(GET_NAME(arg1), SIMP);
	chain = GET_RECORD(arg1);
	arg2 = copy_heap(arg2);	//copy arg1 to heap area
	if (chain == NIL) {
	    key_list = cons(arg1, key_list);
	}

	SET_RECORD(arg1, bcons(arg2, chain));
	checkgbc();
	if (unify(arg3, makeint(GET_RECORD(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);

    }
    error(ARITY_ERR, "recorda ", arglist, th);
    return (NO);
}

int b_recorded(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, chain, save1, save2;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	arg1 = makeatom(GET_NAME(arg1), SIMP);
	chain = GET_RECORD(arg1);
	save1 = wp[th];
	save2 = sp[th];
	while (!nullp(chain)) {
	    if (unify(arg2, car(chain), th) == YES
		&& unify(arg3, makeint(chain), th) == YES) {
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
	    }
	    chain = cdr(chain);
	    wp[th] = save1;
	    unbind(save2, th);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }
    error(ARITY_ERR, "recorded ", arglist, th);
    return (NO);
}

int b_nref(int arglist, int rest, int th)
{
    int n, arg1, arg2, chain;

    n = length(arglist);

    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "nref ", arg1, th);
	if (!wide_variable_p(arg1) && !integerp(arg1))
	    error(NOT_VAR, "nref ", arg2, th);

	chain = cdr(get_int(arg1));
	if (chain == NIL)
	    return (NO);
	if (unify(arg2, makeint(chain), th) == YES) {
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);
	    else
		return (NO);
	}
    }
    error(ARITY_ERR, "nref ", arglist, th);
    return (NO);
}

int b_pref(int arglist, int rest, int th)
{
    int n, arg1, arg2, chain;

    n = length(arglist);

    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	error(NOT_INT, "pref ", arg1, th);
	if (!wide_variable_p(arg1) && !integerp(arg1))
	    error(NOT_VAR, "pref ", arg2, th);

	chain = GET_AUX(get_int(arg1));
	if (chain == NIL)
	    return (NO);
	if (unify(arg2, makeint(chain), th) == YES) {
	    if (prove_all(rest, sp[th], th) == YES)
		return (YES);
	    else
		return (NO);
	}
    }
    error(ARITY_ERR, "pref ", arglist, th);
    return (NO);
}

int b_nth_ref(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, chain, i;

    n = length(arglist);

    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (!atomp(arg1))
	    error(NOT_ATOM, "nth_ref ", arg1, th);
	if (!integerp(arg2))
	    error(NOT_INT, "nth_ref ", arg2, th);
	if (!wide_variable_p(arg3))
	    error(NOT_VAR, "nth_ref ", arg3, th);

	chain = GET_RECORD(arg1);
	i = get_int(arg2);
	if (chain == NIL)
	    return (NO);

	while (!nullp(chain)) {
	    if (i == 1)
		goto find;
	    chain = cdr(chain);
	}
	return (NO);

      find:
	if (unify(arg2, makeint(chain), th) == YES) {
	    if (prove(NIL, sp[th], rest, th) == YES)
		return (YES);
	}
    }
    error(ARITY_ERR, "nth_ref ", arglist, th);
    return (NO);
}

int b_replace(int arglist, int rest, int th)
{
    int n, arg1, arg2, chain;

    n = length(arglist);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    error(NOT_INT, "replace ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "replace ", arg2, th);

	chain = get_int(arg1);
	arg2 = copy_heap(arg2);
	SET_CAR(chain, arg2);
	if (prove(NIL, sp[th], rest, th) == YES)
	    return (YES);
	else
	    return (NO);
    }
    error(ARITY_ERR, "replace ", arglist, th);
    return (NO);
}


int b_erase(int arglist, int rest, int th)
{
    int n, arg1, addr;

    n = length(arglist);

    if (n == 1) {
	arg1 = car(arglist);
	arg1 = deref(arg1, th);
	if (!integerp(arg1))
	    error(NOT_INT, "erase ", arg1, th);

	addr = get_int(arg1);
	SET_CAR(addr, NIL);
	return (YES);
    }
    error(ARITY_ERR, "erase ", arglist, th);
    return (NO);
}

int b_eraseall(int arglist, int rest, int th)
{
    int n, arg1;

    n = length(arglist);

    if (n == 1) {
	arg1 = car(arglist);
	arg1 = deref(arg1, th);
	if (!atomp(arg1))
	    error(NOT_ATOM, "erase ", arg1, th);

	arg1 = makeatom(GET_NAME(arg1), SIMP);
	SET_RECORD(arg1, NIL);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);
	else
	    return (NO);
    }
    error(ARITY_ERR, "eraseall ", arglist, th);
    return (NO);
}



int b_removeh(int arglist, int rest, int th)
{
    int n, arg1, arg2, arg3, save1, record_id, index, lis, prev, term;

    n = length(arglist);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (wide_variable_p(arg1))
	    error(INSTANTATION_ERR, "removeh ", arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    error(NOT_ATOM, "removeh ", arg1, th);
	if (wide_variable_p(arg2))
	    error(INSTANTATION_ERR, "removeh ", arg2, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    error(NOT_ATOM, "removeh ", arg2, th);


	save1 = sp[th];
	record_id = GET_ARITY(arg1) - 1;	//id starts from 1
	if (record_id < 0)
	    error(NOT_RECORD, "removeh ", arg1, th);
	index = hash(GET_NAME(arg2));
      repeat:
	lis = record_hash_table[index][record_id];
	prev = NIL;
	while (lis != NIL) {
	    term = car(lis);
	    if (car(term) != arg2)
		goto skip;

	    if (unify(arg3, cdr(term), th)) {
		if (prev != NIL)
		    SET_CDR(prev, cdr(lis));	// delete unified term
		else
		    record_hash_table[index][record_id] = cdr(lis);
		// if term is first one of list, set hashtable cdr of lis
		if (prove_all(rest, sp[th], th) == YES)
		    return (YES);
	    }
	    unbind(save1, th);
	    if (prev == NIL)
		goto repeat;
	  skip:
	    lis = cdr(lis);
	    prev = lis;
	}
	return (NO);
    }
    error(ARITY_ERR, "removeh ", arglist, th);
    return (NO);
}

int b_removeallh(int arglist, int rest, int th)
{
    int n, arg1, record_id, i;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);
	record_id = GET_ARITY(arg1) - 1;
	SET_ARITY(arg1, NIL);
	for (i = 0; i < HASHTBSIZE; i++)
	    record_hash_table[i][record_id] = NIL;
	//as a result, removed term will be retrieve by GC
	return (prove_all(rest, sp[th], th));
    }
    error(ARITY_ERR, "removeallh ", arglist, th);
    return (NO);
}

int b_ref(int arglist, int rest, int th)
{
    int n, arg1, list, key, num, chain;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	if (!integerp(arg1))
	    error(NOT_INT, "ref ", arg1, th);

	num = get_int(arg1);
	list = key_list;
	while (!nullp(list)) {
	    key = car(list);
	    list = cdr(list);
	    chain = GET_RECORD(key);
	    while (!nullp(chain)) {
		if (num == chain)
		    goto find;
		chain = cdr(chain);
	    }
	}
	return (NO);		//not find

      find:
	if (prove_all(rest, sp[th], th) == YES) {
	    return (YES);
	} else
	    return (NO);
    }
    error(ARITY_ERR, "ref ", arglist, th);
    return (NO);
}


int b_key(int arglist, int rest, int th)
{
    int n, arg1, arg2, save1, save2, list, key, chain, arity, keyarity;

    n = length(arglist);
    if (n == 1) {
	arg1 = car(arglist);

	list = reverse(key_list);
	save1 = wp[th];
	save2 = sp[th];
	while (!nullp(list)) {
	    key = car(list);
	    list = cdr(list);
	    chain = GET_RECORD(key);
	    if (chain != NIL) {

		if (structurep(car(chain)))
		    arity = length(car(chain)) - 1;
		else
		    arity = 0;

		keyarity = list3(SLASH, key, makeint(arity));
		if (unify(arg1, keyarity, th) == YES) {
		    if (prove(NIL, sp[th], rest, th) == YES)
			return (YES);
		}
		wp[th] = save1;
		unbind(save2, th);
	    }
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!atomp(arg1))
	    error(NOT_ATOM, "key ", arg1, th);
	if (!wide_variable_p(arg2))
	    error(NOT_VAR, "key ", arg2, th);

	save1 = wp[th];
	save2 = sp[th];
	arg1 = makeatom(GET_NAME(arg1), SIMP);
	chain = GET_RECORD(arg1);
	if (unify(arg2, makeint(chain), th) == YES) {
	    if (prove(NIL, sp[th], rest, th) == YES)
		return (YES);
	}
	wp[th] = save1;
	unbind(save2, th);
	return (NO);
    }

    error(ARITY_ERR, "key ", arglist, th);
    return (NO);
}
