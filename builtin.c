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

void init_builtin(void)
{
    definfix(">", b_n_greater, 700, XFX);
    definfix("<", b_n_smaller, 700, XFX);
    definfix("=<", b_n_eqsmaller, 700, XFX);
    definfix(">=", b_n_eqgreater, 700, XFX);
    definfix("=:=", b_n_numeq, 700, XFX);
    definfix("=\\=", b_n_notnumeq, 700, XFX);
    definfix("=/=", b_n_notnumeq, 700, XFX);
    definfix("@<", b_n_atsmaller, 700, XFX);
    definfix("@=<", b_n_ateqsmaller, 700, XFX);
    definfix("@>", b_n_atgreater, 700, XFX);
    definfix("@>=", b_n_ateqgreater, 700, XFX);
    definfix("is", b_is, 700, XFX);
    definfix("=", b_n_unify, 700, XFX);
    definfix("==", b_n_equalp, 700, XFX);
    definfix("\\==", b_n_notequalp, 700, XFX);
    definfix("\\=", b_n_notunify, 700, XFX);
    definfix("=..", b_n_univ, 700, XFX);
    definfix("->", b_ifthen, 1050, XFY);
    definfix("not", b_not, 900, FY);

    defbuiltin("!", b_n_cut, 0);
    defbuiltin("%ask", b_n_ask, -1);
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
    defbuiltin("atom", b_atom, 1);
    defbuiltin("atom_string", b_atom_string, 2);
    defbuiltin("atomic", b_atomic, 1);
    defbuiltin("bagof", b_bagof, 3);
    defbuiltin("%bagofhelper", b_bagofhelper, -1);
    defbuiltin("break", b_break, 0);
    defbuiltin("call", b_call, 1);
    defbuiltin("chdir", b_chdir, 1);
    defbuiltin("close", b_close, 1);
    defbuiltin("clause", b_clause, 2);
    defbuiltin("compare", b_compare, 2);
    defbuiltin("concat", b_concat, 3);
    defbuiltin("consult", b_consult, list2(1,2));
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
    defbuiltin("flush", b_flush_output, list2(0, 1));
    defbuiltin("float", b_real, 1);
    defbuiltin("float_text", b_float_text, 3);
    defbuiltin("functor", b_functor, 3);
    defbuiltin("gc", b_gbc, 0);
    defbuiltin("get", b_get, list2(1, 2));
    defbuiltin("get0", b_get0, list2(1, 2));
    defbuiltin("get0_noecho", b_get0_noecho, 1);
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
    defbuiltin("length", b_length, 2);
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
    defbuiltin("reconsult", b_reconsult, list2(1,2));
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

    defbuiltin("repeat", b_repeat, 0);
    defbuiltin("append", b_append, 3);
    defbuiltin("member", b_member, 2);
    defbuiltin("between", b_between, 3);
    defbuiltin("select", b_select, 3);
    defbuiltin("succ", b_succ, 2);
    defbuiltin("maplist", b_maplist, 2);
    defbuiltin("compound", b_compound, 1);
    defbuiltin("ground", b_ground, 1);
    defbuiltin("once", b_once, 1);
    defbuiltin("atom_codes", b_atom_codes, 2);
    defbuiltin("atom_chars", b_atom_chars, 2);
    defbuiltin("char_code", b_char_code, 2);
    defbuiltin("number_codes", b_number_codes, 2);
    defbuiltin("number_chars", b_number_chars, 2);
    defbuiltin("write_canonical", b_display, list2(1, 2));
    defbuiltin("atom_length", b_atom_length, 2);
    defbuiltin("atom_concat", b_atom_concat, 3);
    defbuiltin("get_code", b_get_code, list2(1, 2));
    defbuiltin("get_char", b_get_char, list2(1, 2));
    defbuiltin("get_byte", b_get_byte, list2(1, 2));
    defbuiltin("put_char", b_put_char, list2(1, 2));
    defbuiltin("put_code", b_put_code, list2(1, 2));
    defbuiltin("put_byte", b_put_byte, list2(1, 2));
    defbuiltin("peek_code", b_peek_code, list2(1, 2));
    defbuiltin("peek_char", b_peek_char, list2(1, 2));
    defbuiltin("peek_byte", b_peek_byte, list2(1, 2));
    defbuiltin("flush_output", b_flush_output, list2(0, 1));
    defbuiltin("catch", b_catch, 3);
    defbuiltin("throw", b_throw, 1);
    defbuiltin("unify_with_occurs_check", b_unify_with_occurs_check, 2);
    defbuiltin("current_input", b_current_input, 1);
    defbuiltin("current_output", b_current_output, 1);
    defbuiltin("set_input", b_set_input, 1);
    defbuiltin("set_output", b_set_output, 1);
    defbuiltin("use_module", b_use_module, 1);
    defbuiltin("module", b_module, 2);
    defbuiltin("copy_term", b_copy_term, 2);
    defbuiltin("at_end_of_stream", b_at_end_of_stream, 1);
    defbuiltin("stream_property", b_stream_property, 2);
    defbuiltin("create_client_socket", b_create_client_socket, 3);
    defbuiltin("create_server_socket", b_create_server_socket, 2);
    defbuiltin("send_socket", b_send_socket, 2);
    defbuiltin("recv_socket", b_recv_socket, 2);
    defbuiltin("close_socket", b_close_socket, 1);
    defbuiltin("dynamic", b_dynamic, 1);
    defbuiltin("existerrors", b_existerrors, 2);
    defbuiltin("set_prolog_flag", b_set_prolog_flag, 2);
    defbuiltin("cinline", b_cinline, 1);
    defbuiltin("format", b_format, 3);
    defbuiltin("create_client_curl", b_create_client_curl, 2);
    defbuiltin("send_curl", b_send_curl, 2);
    defbuiltin("recv_curl", b_recv_curl, 2);
    defbuiltin("close_curl", b_close_curl, 1);
    defbuiltin("set_curl_option", b_set_curl_option, 2);
    defbuiltin("add_curl_header", b_add_curl_header, 2);
    defbuiltin("string_atom", b_string_atom, 2);
    defbuiltin("initialization", b_initialization, 1);
    definfix("\\+", b_not, 900, FY);

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

   
    //------CLPFD--------------------------
    defbuiltin("n_add_constraint", b_add_constraint, -1);
    defbuiltin("n_constraint_set", b_constraint_set, -1);
    defbuiltin("n_constraint_var", b_constraint_var, -1);
    defbuiltin("n_constraint_vars", b_constraint_vars, -1);
    defbuiltin("label", b_label, 1);
    defbuiltin("all_different", b_all_different, 1);


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
    defbuiltin("digital_read", b_digital_read, 2);
    defbuiltin("delay", b_delay, 1);
    defbuiltin("delay_microseconds", b_delay_microseconds, 1);
    defbuiltin("timer_microseconds", b_timer_microseconds, 1);
#endif
	
	
	//-----JUMP project---------
    defbuiltin("n_reconsult_predicate", b_n_reconsult_predicate, 1);
    defbuiltin("n_reconsult_abolish", b_n_reconsult_abolish, 0);
    defbuiltin("n_dynamic_predicate", b_n_dynamic_predicate, 1);
    defbuiltin("n_filename", b_n_filename, 2);
    defbuiltin("n_atom_convert", b_n_atom_convert, 2);
    defbuiltin("n_arity_count", b_n_arity_count, 2);
    defbuiltin("n_compiler_anonymous", b_n_compiler_anonymous, 1);
    defbuiltin("n_compiler_variable", b_n_compiler_variable, 1);
    defbuiltin("n_variable_convert", b_n_variable_convert, 2);
    defbuiltin("n_generate_all_variable", b_n_generate_all_variable, 2);
    defbuiltin("n_generate_variable", b_n_generate_variable, 2);
    defbuiltin("n_clause_with_arity", b_n_clause_with_arity, 3);
    defbuiltin("n_property", b_n_property, 2);
    defbuiltin("n_bignum", b_n_bignum, 1);
    defbuiltin("n_longnum", b_n_longnum, 1);
    defbuiltin("n_findatom", b_n_findatom, 3);
    defbuiltin("n_defined_predicate", b_n_defined_predicate, 1);
    defbuiltin("n_defined_userop", b_n_defined_userop, 1);
    defbuiltin("n_get_execute", b_n_get_execute, 1);
    defbuiltin("n_get_dynamic", b_n_get_dynamic, 1);
    defbuiltin("n_error", b_n_error, 2);
    defbuiltin("n_has_cut", b_n_has_cut, 1);
    defbuiltin("n_before_cut", b_n_before_cut, 2);
    defbuiltin("n_after_cut", b_n_after_cut, 2);
    defbuiltin("n_pair_list", b_n_pair_list, 1);
    defbuiltin("n_exec_is", b_n_exec_is, 2);
	defbuiltin("n_exec_smaller", b_n_exec_smaller, 2);
	defbuiltin("n_exec_greater", b_n_exec_greater, 2);
	defbuiltin("n_exec_eqsmaller", b_n_exec_eqsmaller, 2);
	defbuiltin("n_exec_eqgreater", b_n_exec_eqgreater, 2);

	
	builtins = reverse(builtins);

    return;
}

/* for compiled code runtime routin exec_all, exec*/
int exec_all(int goals, int bindings, int th)
{
    compiled_flag = 1;


    if (IS_NIL(goals))
	return (YES);
    // ,(;(D1;D2),Xs) 
    else if (structurep(goals) && car(cadr(goals)) == OR) {
	if (exec_all(cadr(cadr(goals)), bindings, th) == YES)
	    return (exec_all(caddr(goals), bindings, th));
	else if (exec_all(caddr(cadr(goals)), bindings, th) == YES)
	    return (exec_all(caddr(goals), bindings, th));
	else
	    return (NO);
    }
    // ((D1,D2),Xs) 
    else if (structurep(goals) && car(goals) == AND
	     && car(cadr(goals)) == AND) {
	if (exec_all(cadr(goals), bindings, th) == YES)
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

    if (IS_NIL(goal)) {
	return (exec_all(rest, bindings, th));
    } else if (builtinp(goal) || compiledp(goal)) {
	if (atomp(goal)) {
	    if ((res = (GET_SUBR(goal)) (NIL, rest, th)) == YES)
		return (YES);

	    return (res);
	} else {
	    if ((res = (GET_SUBR(car(goal))) (cdr(goal), rest, th)) == YES)
		return (YES);

	    return (res);
	}
    } else if (predicatep(goal)) {
	compiled_flag = 0;
	res = prove(goal, sp[th], NIL, th);
	compiled_flag = 1;
	if (res == YES)
	    return (exec_all(rest, sp[th], th));
	else
	    return (res);
    }

    return (NO);
}


int b_length(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, i, ls, res, save1, save2;
    int list_length, properp, improper_last_not_var, improper_last_var;
    save2 = sp[th];
    n = length(arglist);
    ind = makeind("length", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	// pre check
	properp = 0;
	improper_last_not_var = 0;
	improper_last_var = 0;
	if (listp(arg1)) {
	    list_length = length(arg1);
	    if (list_length != -1 && list_length != -2)
		properp = 1;
	    else if (list_length == -1)
		improper_last_not_var = 1;
	    else if (list_length == -2)
		improper_last_var = 1;
	}

	if (!listp(arg1) && !wide_variable_p(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (listp(arg1) && improper_last_not_var)
	    exception(NOT_LIST, ind, arg1, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    exception(LESS_THAN_ZERO, ind, arg2, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (variablep(arg1) && variablep(arg2) && eqp(arg1, arg2))
	    exception(INSTANTATION_ERR, ind, arglist, th);

	save1 = wp[th];
	if (listp(arg1) && properp) {
	    if (unify(arg2, makeint(length(arg1)), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (listp(arg1) && improper_last_var) {
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//compiled predicate
int b_repeat(int arglist, int rest, int th)
{
    int n, ind, save1, save2, save3;

    save1 = wp[th];
    save2 = sp[th];
    save3 = ac[th];
    n = length(arglist);
    ind = makeind("repeat", n, th);
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

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_op(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, weight, type;

    n = length(arglist);
    ind = makeind("op", n, th);
    if (n == 3) {
	arg1 = car(arglist);	//priority
	arg2 = cadr(arglist);	//specifier
	arg3 = caddr(arglist);	//operator

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (listp(arg3) && length(arg3) == -1)
	    exception(INSTANTATION_ERR, ind, arg3, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);
	if (!atomp(arg3) && !listp(arg3))
	    exception(NOT_ATOM, ind, arg3, th);
	weight = GET_INT(arg1);
	if (!(weight > 0 && weight <= 1200))
	    exception(OPE_PRIORITY_ERR, ind, arg1, th);
	if (arg3 == DOTOBJ)
	    exception(MODIFY_OPE_ERR, ind, arg3, th);
	if (arg3 == AND)
	    exception(MODIFY_OPE_ERR, ind, arg3, th);
	if (arg3 == makeatom("op", OPE))
	    exception(MODIFY_OPE_ERR, ind, arg3, th);

	type = NIL;
	if (arg2 == makeconst("xfx")) {
	    type = XFX;

	} else if (arg2 == makeconst("yfx")) {
	    if (GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
		exception(OPE_SPEC_ERR, ind, arg2, th);
	    type = YFX;
	} else if (arg2 == makeconst("xfy")) {
	    if (GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
		exception(OPE_SPEC_ERR, ind, arg2, th);
	    type = XFY;
	} else if (arg2 == makeconst("fx"))
	    type = FX;
	else if (arg2 == makeconst("fy"))
	    type = FY;
	else if (arg2 == makeconst("xf")) {
	    if (GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
		GET_OPT(arg3) == XFY)
		exception(OPE_SPEC_ERR, ind, arg2, th);
	    type = XF;
	} else if (arg2 == makeconst("yf")) {
	    if (GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
		GET_OPT(arg3) == XFY)
		exception(OPE_SPEC_ERR, ind, arg2, th);
	    type = YF;
	} else
	    exception(OPE_SPEC_ERR, ind, arg2, th);

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
		    exception(INSTANTATION_ERR, ind, car(arg3), th);
		else if (!atomp(car(arg3)) && !operatorp(car(arg3)))
		    exception(NOT_ATOM, ind, car(arg3), th);
		else if (operatorp(car(arg3)))
		    defoperator(GET_NAME(arg3), NIL, weight, type, 0);
		else
		    defoperator(GET_NAME(car(arg3)), NIL, weight, type, 2);

		arg3 = cdr(arg3);
	    }
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int o_cons(int x, int y, int th)
{
    if (operationp(y))
	y = operate(y, th);
    return (listcons(x, y));
}

int b_n_ask(int arglist, int rest, int th)
{
    int n, ind, x1, x2, x3;
    char c;

    n = length(arglist);
    ind = makeind("ask", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_unify(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("=", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	res = unify(arg1, arg2, th);
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_n_notunify(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("\\=", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}




//input and output
int b_write(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save;

    n = length(arglist);
    ind = makeind("write", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto write;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      write:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_display(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save;

    n = length(arglist);
    ind = makeind("display", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto display;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      display:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_writeq(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save;

    n = length(arglist);
    ind = makeind("writeq", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto writeq;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      writeq:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_nl(int arglist, int rest, int th)
{
    int n, ind, arg1, save;

    n = length(arglist);
    ind = makeind("nl", n, th);
    if (n == 0) {
	fprintf(GET_PORT(output_stream), "\n");
	fflush(GET_PORT(output_stream));
	return (prove_all(rest, sp[th], th));
    } else if (n == 1) {
	arg1 = car(arglist);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_put(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("put", n, th);
    if (n == 1) {
	arg1 = output_stream;
	arg2 = car(arglist);
	goto put;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      put:

	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

	fprintf(GET_PORT(arg1), "%c", (char) GET_INT(arg2));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_get0(int arglist, int rest, int th)
{
    int n, ind, c, arg1, arg2, i, res;

    n = length(arglist);
    ind = makeind("get0", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto get0;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);


      get0:
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_get(int arglist, int rest, int th)
{
    int n, ind, c, arg1, arg2, i, res;

    n = length(arglist);
    ind = makeind("get", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);

	goto get;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      get:
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_get0_noecho(int arglist, int rest, int th)
{
    int n, ind, c, arg1, i, res;

    n = length(arglist);
    ind = makeind("get0_noecho", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_tab(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, count;

    n = length(arglist);
    ind = makeind("tab", n, th);
    if (n == 1) {
	arg1 = standard_output;
	arg2 = car(arglist);
	goto tab;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      tab:
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    exception(LESS_THAN_ZERO, ind, arg2, th);
	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

	if (aliasp(arg1))
	    arg1 = GET_CAR(arg1);
	count = GET_INT(arg2);
	while (count > 0) {
	    fprintf(GET_PORT(arg1), " ");
	    count--;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1, arg2, save1, save2, temp, res;

    n = length(arglist);
    ind = makeind("read", n, th);
    if (n == 1) {
	arg1 = input_stream;
	arg2 = car(arglist);
	goto read;

    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      read:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_read_line(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save1, save2, res, pos;
    char str[STRSIZE], c;

    n = length(arglist);
    ind = makeind("read_line", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (arg1 == makeint(0))
	    arg1 = standard_input;

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

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
		exception(RESOURCE_ERR, ind, makestr("strsize"), th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_read_string(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, save2, res, pos, maxlen;
    char str[STRSIZE], c;

    n = length(arglist);
    ind = makeind("read_string", n, th);
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
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (get_int(arg2) < 0 || get_int(arg2) > STRSIZE)
	    exception(RESOURCE_ERR, ind, makestr("strsize"), th);
	if (!wide_variable_p(arg3) && !stringp(arg3))
	    exception(NOT_STR, ind, arg3, th);

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
		exception(RESOURCE_ERR, ind, makestr("strsize"), th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_skip(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save;
    char c, str[STRSIZE];

    n = length(arglist);
    ind = makeind("skip", n, th);
    if (n == 1) {
	arg1 = standard_input;
	arg2 = car(arglist);
	goto skip;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
      skip:
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_stdin(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save1, save2;

    n = length(arglist);
    ind = makeind("stdin", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!callablep(arg2))
	    exception(NOT_CALLABLE, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_stdout(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save1, save2;

    n = length(arglist);
    ind = makeind("stdout", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!callablep(arg2))
	    exception(NOT_CALLABLE, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_stdinout(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, save2, save3;

    n = length(arglist);
    ind = makeind("stdinout", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!streamp(arg1) && !aliasp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);
	if (!streamp(arg1) && !aliasp(arg2))
	    exception(NOT_STREAM, ind, arg2, th);
	if (!callablep(arg3))
	    exception(NOT_CALLABLE, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_create(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, stream;

    n = length(arglist);
    ind = makeind("create", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);

	if (eqp(arg1, makeconst("user"))) {
	    output_stream = standard_output;
	    return (prove_all(rest, sp[th], th));
	} else {
	    stream =
		makestream(fopen(GET_NAME(arg2), "w"), NPL_OUTPUT,
			   NPL_TEXT, NIL, arg2);

	    if (GET_PORT(stream) == NULL)
		exception(CANT_OPEN, ind, arg2, th);
	    unify(arg1, stream, th);
	    return (prove_all(rest, sp[th], th));
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}




int b_open(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, stream;

    n = length(arglist);
    ind = makeind("open", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);

	if (eqp(arg1, makeconst("user"))) {
	    output_stream = standard_output;
	    return (prove_all(rest, sp[th], th));
	} else {
	    if (arg3 == makeconst("w")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "w"), NPL_OUTPUT,
			       NPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    exception(CANT_OPEN, ind, arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("wb")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "wb"), NPL_OUTPUT,
			       NPL_BINARY, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    exception(CANT_OPEN, ind, arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("r")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "r"), NPL_INPUT,
			       NPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    exception(CANT_OPEN, ind, arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("rb")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "rb"), NPL_INPUT,
			       NPL_BINARY, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    exception(CANT_OPEN, ind, arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("rw")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "r+"), NPL_INOUT,
			       NPL_TEXT, NIL, arg2);

		if (GET_PORT(stream) == NULL)
		    exception(CANT_OPEN, ind, arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    } else if (arg3 == makeconst("a") || arg3 == makeconst("ra")) {
		stream =
		    makestream(fopen(GET_NAME(arg2), "a+"), NPL_INPUT,
			       NPL_TEXT, NIL, arg2);


		if (GET_PORT(stream) == NULL)
		    exception(CANT_OPEN, ind, arg2, th);
		unify(arg1, stream, th);
		return (prove_all(rest, sp[th], th));
	    }
	    exception(ILLEGAL_ARGS, ind, arg3, th);
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dup(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, addr;

    n = length(arglist);
    ind = makeind("dup", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!streamp(arg1))
	    exception(NOT_STREAM, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_close(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("clsoe", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	fclose(GET_PORT(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_see(int arglist, int rest, int th)
{
    int n, ind, arg1, save;

    n = length(arglist);
    ind = makeind("see", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	if (eqp(arg1, makeconst("user"))) {
	    input_stream = standard_input;
	    return (prove_all(rest, sp[th], th));
	} else {
	    save = input_stream;
	    input_stream =
		makestream(fopen(GET_NAME(arg1), "r"), NPL_INPUT, NPL_TEXT,
			   NIL, arg1);

	    if (GET_PORT(input_stream) == NULL) {
		input_stream = save;
		exception(CANT_OPEN, ind, arg1, th);
	    }
	    return (prove_all(rest, sp[th], th));
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_seeing(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("seeing", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!wide_variable_p(arg1))
	    exception(NOT_VAR, ind, arg1, th);
	if (unify(arg1, GET_CDR(input_stream), th) == YES) {
	    return (prove_all(rest, sp[th], th));
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_seen(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("seen", n, th);
    if (n == 0) {
	if (input_stream != standard_input) {
	    fclose(GET_PORT(input_stream));
	    input_stream = standard_input;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_tell(int arglist, int rest, int th)
{
    int n, ind, arg1, save;

    n = length(arglist);
    ind = makeind("tell", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	if (eqp(arg1, makeconst("user"))) {
	    output_stream = standard_output;
	    return (prove_all(rest, sp[th], th));
	} else {
	    save = output_stream;
	    output_stream =
		makestream(fopen(GET_NAME(arg1), "w"), NPL_OUTPUT,
			   NPL_TEXT, NIL, arg1);

	    if (GET_PORT(input_stream) == NULL) {
		output_stream = save;
		exception(CANT_OPEN, ind, arg1, th);
	    }
	    return (prove_all(rest, sp[th], th));
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_telling(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("telling", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (unify(arg1, GET_CDR(output_stream), th) == YES)
	    return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_told(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("told", n, th);
    if (n == 0) {
	if (output_stream != standard_output) {
	    fclose(GET_PORT(output_stream));
	    output_stream = standard_output;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_flush(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("flush", n, th);
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


int b_consult(int arglist, int rest, int th)
{
    int n, ind, arg1, clause, save;
    char str[STRSIZE];

    n = length(arglist);
    ind = makeind("consult", n, th);
    execute_list = NIL;
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	save = input_stream;
	input_stream =
	    makestream(fopen(GET_NAME(arg1), "r"), NPL_INPUT, NPL_TEXT,
		       NIL, arg1);

	if (GET_PORT(input_stream) == NULL)
	    exception(CANT_OPEN, ind, arg1, th);

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
	dynamic_list = NIL;
	while (1) {
	  skip:
	    clause = readparse(th);
	    if (clause == FEND)
		break;

	    //e.g. :- op(...)
	    if (operationp(clause) && car(clause) == NECK
		&& length(clause) == 2) {
		clause = cadr(clause);
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
	if (execute_list != NIL) {
	    execute_list = reverse(execute_list);
	    while (!nullp(execute_list)) {
		prove_all(car(execute_list), sp[th], th);
		execute_list = cdr(execute_list);
	    }
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_reconsult(int arglist, int rest, int th)
{
    int n, ind, arg1, clause, clause1, head, atom, save, compiler;
    char str[STRSIZE];

    n = length(arglist);
    ind = makeind("reconsult", n, th);
    execute_list = NIL;
    compiler = 0;
    if (n == 1) {
      reconsult:
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	save = input_stream;
	input_stream =
	    makestream(fopen(GET_NAME(arg1), "r"), NPL_INPUT, NPL_TEXT,
		       NIL, arg1);

	if (GET_PORT(input_stream) == NULL)
	    exception(CANT_OPEN, ind, arg1, th);

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
	dynamic_list = NIL;
	while (1) {
	  skip:
	    clause = readparse(th);
	    if (clause == FEND)
		break;

	    //e.g. :- op(...)
	    if (operationp(clause) && car(clause) == NECK
		&& length(clause) == 2) {
		clause = cadr(clause);
		prove_all(clause, sp[th], th);
		goto skip;
	    }
	    // DCG syntax e.g. a-->b.
	    if (dcgp(clause)) {
		operate(clause, th);
		goto skip;
	    }
	    //delete old definition and consult
	    if (predicatep(clause) || user_operation_p(clause)) {
		clause1 = copy_heap(clause);
		if (atomp(clause1))
		    atom = clause1;
		else
		    atom = car(clause1);
	    } else {
		clause1 = copy_heap(clause);
		head = cadr(clause1);
		if (atomp(head))
		    atom = head;
		else
		    atom = car(head);
	    }
	    if (!memberp(atom, reconsult_list)) {
		reconsult_list = cons(atom, reconsult_list);
		SET_CAR(atom, NIL);
		SET_ARITY(atom, NIL);
	    }
	    //assert
	    b_assert(list1(clause), NIL, th);
	}
	open_flag = 0;
	fclose(GET_PORT(input_stream));
	input_stream = save;
	module_flag = 0;

      exit:
	if (compiler != 1 && execute_list != NIL) {
	    execute_list = reverse(execute_list);
	    while (!nullp(execute_list)) {
		prove_all(car(execute_list), sp[th], th);
		execute_list = cdr(execute_list);
	    }
	}
	return (prove_all(rest, sp[th], th));
    } else if (n == 2) {
	arg1 = car(arglist);
	compiler = 1;
	goto reconsult;
    }
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1;
    static char str[STREAM];
    char str1[STRSIZE];

    n = length(arglist);
    ind = makeind("save", n, th);
	str = NULL;
    if (n == 0) {
	arg1 = NIL;
	strcpy(str1, "library/startup.pl");
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	output_stream =
	    makestream(fopen(GET_NAME(arg1), "w"), NPL_OUTPUT, NPL_TEXT,
		       NIL, arg1);
	goto save;
    } else if (n == 1) {
	arg1 = car(arglist);
	arg1 = makeatom(prolog_file_name(GET_NAME(arg1)), SIMP);
	strcpy(str, GET_NAME(arg1));
	output_stream =
	    makestream(fopen(GET_NAME(arg1), "w"), NPL_OUTPUT,
		       NPL_TEXT, NIL, arg1);

      save:
	if (GET_PORT(output_stream) == NULL) {
	    exception(CANT_OPEN, ind, arg1, th);
	}
	b_listing(NIL, NIL, th);
	fclose(GET_PORT(output_stream));
	output_stream = standard_output;
	return (prove_all(rest, sp[th], th));

    } else if (n == 0) {
	if (str == NULL) {
	    exception(ILLEGAL_ARGS, ind, NIL, th);
	}

	output_stream =
	    makestream(fopen(str, "w"), NPL_OUTPUT,
		       NPL_TEXT, NIL, makeatom(str, SIMP));
	b_listing(NIL, NIL, th);
	fclose(GET_PORT(output_stream));
	output_stream = standard_output;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_directory(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, arg4, arg5, arg6, save, mode, date, time;
    DIR *dir;
    struct dirent *dp;
    struct stat stat_buf;
    struct tm *t_st;

    n = length(arglist);
    ind = makeind("directory", n, th);
    if (n == 6) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	arg4 = cadddr(arglist);
	arg5 = caddddr(arglist);
	arg6 = cadddddr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);
	if (!wide_variable_p(arg3) && !atomp(arg3))
	    exception(NOT_ATOM, ind, arg3, th);
	if (!wide_variable_p(arg4))
	    exception(NOT_VAR, ind, arg4, th);
	if (!wide_variable_p(arg5))
	    exception(NOT_VAR, ind, arg5, th);
	if (!wide_variable_p(arg6))
	    exception(NOT_VAR, ind, arg6, th);

	save = sp[th];
	dir = opendir(GET_NAME(arg1));
	if (dir == NULL)
	    exception(SYSTEM_ERR, ind, makestr("opendir"), th);

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
		exception(SYSTEM_ERR, ind, makestr("readdir"), th);

	    unbind(save, th);
	    dp = readdir(dir);
	}
	if (dir != NULL)
	    closedir(dir);

	unbind(save, th);
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//arithmetic operation

int b_is(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("is", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	eval_context = ind;
	arg2 = eval(arg2, th);
	res = unify(arg1, arg2, th);

	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_exec_is(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("is", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	res = unify(arg1, arg2, th);

	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_n_greater(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind(">", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	eval_context = ind;
	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);

	if (greaterp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_exec_greater(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind(">", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	if (greaterp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_smaller(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("<", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	eval_context = ind;
	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);

	if (smallerp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_exec_smaller(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("<", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	
	if (smallerp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_eqsmaller(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("=<", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	eval_context = ind;
	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);

	if (eqsmallerp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_exec_eqsmaller(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("=<", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	if (eqsmallerp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_eqgreater(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind(">=", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	eval_context = ind;
	arg1 = eval(arg1, th);
	arg2 = eval(arg2, th);

	if (eqgreaterp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_exec_eqgreater(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind(">=", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	if (eqgreaterp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_numeq(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("=:=", n, th);
    if (n == 2) {
	eval_context = ind;
	arg1 = eval(car(arglist), th);
	arg2 = eval(cadr(arglist), th);

	if (numeqp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_n_notnumeq(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("=\\=", n, th);
    if (n == 2) {
	eval_context = ind;
	arg1 = eval(car(arglist), th);
	arg2 = eval(cadr(arglist), th);

	if (!numeqp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_n_equalp(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("==", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (anonymousp(arg1) && anonymousp(arg2))
	    return (NO);
	else if (equalp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_n_notequalp(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("\\==", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (anonymousp(arg1) && anonymousp(arg2))
	    return (prove_all(rest, sp[th], th));
	else if (!equalp(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_eq(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("eq", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (arg1 == arg2)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_compare(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3;

    n = length(arglist);
    ind = makeind("compare", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!wide_variable_p(arg1) &&
	    !(eqlp(arg1, makeconst("<")) ||
	      eqlp(arg1, makeconst("=")) || eqlp(arg1, makeconst(">"))))
	    exception(NOT_ORDER, ind, arg1, th);

	if (equalp(arg2, arg3)) {
	    if (unify(arg1, makeconst("="), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (atsmaller(arg2, arg3)) {
	    if (unify(arg1, makeconst("<"), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (atsmaller(arg3, arg2)) {
	    if (unify(arg1, makeconst(">"), th) == YES)
		return (prove_all(rest, sp[th], th));
	}

	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_n_atsmaller(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("@<", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (atsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
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


int b_n_ateqsmaller(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("@=<", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (ateqsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_n_atgreater(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("@>", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!ateqsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_n_ateqgreater(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("@>=", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!atsmaller(arg1, arg2))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

//timer
int b_ctr_set(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("ctr_set", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    exception(RESOURCE_ERR, ind, makestr("max_timer"), th);
	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

	counter[GET_INT(arg1)] = GET_INT(arg2);
	return (prove_all(rest, sp[th], th));

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ctr_dec(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, i;

    n = length(arglist);
    ind = makeind("ctr_dec", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    exception(RESOURCE_ERR, ind, makestr("max_timer"), th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

	i = counter[GET_INT(arg1)];
	counter[GET_INT(arg1)] = i - 1;
	if (unify(arg2, makeint(i), th) == YES)
	    return (prove_all(rest, sp[th], th));

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ctr_inc(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, i;

    n = length(arglist);
    ind = makeind("ctr_inc", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    exception(RESOURCE_ERR, ind, makestr("max_timer"), th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

	i = counter[GET_INT(arg1)];
	counter[GET_INT(arg1)] = i + 1;
	if (unify(arg2, makeint(i), th) == YES)
	    return (prove_all(rest, sp[th], th));

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ctr_is(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, i;

    n = length(arglist);
    ind = makeind("ctr_is", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (GET_INT(arg1) > 30 || GET_INT(arg1) < 0)
	    exception(RESOURCE_ERR, ind, makestr("max_timer"), th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

	i = counter[GET_INT(arg1)];
	if (unify(arg2, makeint(i), th) == YES)
	    return (prove_all(rest, sp[th], th));

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

//true fail
int b_fail(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("fail", n, th);
    if (n == 0) {
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_call(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("call", n, th);
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

	return (prove_all(addtail_body(rest, arg1, th), sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_not(int arglist, int rest, int th)
{
    int n, ind, arg1, res;

    n = length(arglist);
    ind = makeind("not", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!callablep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);

	res = prove_all(arg1, sp[th], th);
	if (res == YES)
	    return (NO);
	else
	    return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_true(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("true", n, th);
    if (n == 0) {
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//database operation
int b_assert(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("assertz", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (singlep(arg1)) {
	    if (GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
		SET_AUX(arg1, PRED);
	}
	if (builtinp(arg1))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (functionp(arg1)) {
	    arg1 = cons(makeatom(GET_NAME(car(arg1)), PRED), cdr(arg1));
	}


	arg1 = variable_to_call(arg1);	//P -> call(P)
	if (!callablep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);
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
		exception(NOT_CALLABLE, ind, arg1, th);
	    if (operationp(cadr(arg1)))
		exception(BUILTIN_EXIST, ind, arg1, th);



	    SET_VAR(arg1, unique(varslist(arg1)));
	    operate(arg1, th);
	    checkgbc();
	    return (prove_all(rest, sp[th], th));
	}
	exception(NOT_CALLABLE, ind, arg1, th);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_asserta(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("asserta", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (singlep(arg1)) {
	    if (GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
		SET_AUX(arg1, PRED);
	}
	if (builtinp(arg1))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (functionp(arg1)) {
	    arg1 = cons(makeatom(GET_NAME(car(arg1)), PRED), cdr(arg1));
	}

	arg1 = variable_to_call(arg1);	//P -> call(P)
	if (!callablep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);
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
		exception(NOT_CALLABLE, ind, arg1, th);
	    if (operationp(cadr(arg1)))
		exception(BUILTIN_EXIST, ind, arg1, th);

	    SET_VAR(arg1, unique(varslist(arg1)));
	    assert_flag = 1;
	    operate(arg1, th);
	    assert_flag = 0;
	    checkgbc();
	    return (prove_all(rest, sp[th], th));
	}
	exception(NOT_CALLABLE, ind, arg1, th);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_retract(int arglist, int rest, int th)
{
    int n, ind, arg1, clause, head, clauses, new_clauses, save1, save2;

    save2 = sp[th];
    clause = clauses = head = NIL;
    n = length(arglist);
    ind = makeind("retract", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (operationp(arg1) && !predicatep(cadr(arg1)))
	    exception(NOT_CALLABLE, ind, arg1, th);
	if (!operationp(arg1) && !predicatep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);
	if (operationp(arg1) && builtinp(cadr(arg1)))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (!operationp(arg1) && builtinp(arg1))
	    exception(BUILTIN_EXIST, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_abolish(int arglist, int rest, int th)
{
    int n, ind, arg1, pred, clause, arity, clauses, new_clauses;

    clause = clauses = NIL;
    n = length(arglist);
    ind = makeind("abolish", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (structurep(arg1) &&
	    (wide_variable_p(cadr(arg1)) || wide_variable_p(caddr(arg1))))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!indicatorp(arg1))
	    exception(NOT_INDICATOR, ind, arg1, th);
	if (builtinp(cadr(arg1)))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (!atomp(cadr(arg1)))
	    exception(NOT_ATOM, ind, arg1, th);
	if (integerp(eval(caddr(arg1), th))
	    && GET_INT(eval(caddr(arg1), th)) < 0)
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (!integerp(caddr(arg1)))
	    exception(NOT_INT, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_clause(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, clause, clauses, save1, save2;

    n = length(arglist);
    ind = makeind("clause", n, th);
    if (n == 2) {
	arg1 = car(arglist);	//head
	arg2 = cadr(arglist);	//body

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atom_predicate_p(arg1) && !predicatep(arg1))
	    exception(NOT_CALLABLE, ind, arg1, th);
	if (builtinp(arg1) || compiledp(arg1))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (!wide_variable_p(arg2) && !callablep(arg2))
	    exception(NOT_CALLABLE, ind, arg2, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_nth_char(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, pos, code;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("nth_char", n, th);
    if (n == 3) {
	arg1 = car(arglist);	// Nth
	arg2 = cadr(arglist);	//string
	arg3 = caddr(arglist);	//Char
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);
	if (!wide_variable_p(arg3))
	    exception(NOT_VAR, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//transform
int b_name(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, ls, atom, pos, code, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("name", n, th);
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

int b_list_text(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, ls, atom, pos, code, index, res;
    char str1[STRSIZE], str2[10];

    n = length(arglist);
    ind = makeind("list_text", n, th);
    if (n == 2) {
	arg1 = car(arglist);	//list
	arg2 = cadr(arglist);	//atomstring
	if (listp(arg1) && length(arg1) == -1 && wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg1) && !listp(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (wide_variable_p(arg1) && !atomp(arg2) && !stringp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_atom_string(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, temp;

    n = length(arglist);
    ind = makeind("atom_string", n, th);
    if (n == 2) {
	arg1 = car(arglist);	//atom
	arg2 = cadr(arglist);	//string

	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_char_code(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, code, res;
    char str[16];

    n = length(arglist);
    ind = makeind("char_code", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, list2(arg1, arg2), th);
	if (!wide_variable_p(arg1) && !characterp(arg1))
	    exception(NOT_CHAR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);


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
		    exception(ILLEGAL_ARGS, ind, arg1, th);
	    }
	    //unicode
	    code = makeint(utf8_to_ucs4(str));
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



//----------string transform-------------------

int b_concat(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, str;
    char str1[STRSIZE];

    n = length(arglist);
    ind = makeind("concat", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);
	if (!stringp(car(arg1)))
	    exception(NOT_STR, ind, car(arg1), th);

	strcpy(str1, GET_NAME(car(arg1)));
	arg1 = cdr(arg1);
	while (!nullp(arg1)) {
	    if (!stringp(car(arg1)) && !atomp(car(arg1)))
		exception(NOT_STR, ind, car(arg1), th);
	    if (strlen(str1) + strlen(GET_NAME(car(arg1))) > STRSIZE)
		exception(RESOURCE_ERR, ind, makestr("strsize"), th);

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
	    exception(NOT_STR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !(atomp(arg2) || stringp(arg2)))
	    exception(NOT_STR, ind, arg2, th);
	if (!wide_variable_p(arg3) && !stringp(arg3))
	    exception(NOT_VAR, ind, arg3, th);
	if (strlen(GET_NAME(arg1)) + strlen(GET_NAME(arg2)) > STRSIZE)
	    exception(RESOURCE_ERR, ind, makestr("strsize"), th);

	strcpy(str1, GET_NAME(arg1));
	strcat(str1, GET_NAME(arg2));
	str = makestr(str1);

	if (unify(arg3, str, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_string_length(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, val;

    n = length(arglist);
    ind = makeind("string_length", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!stringp(arg1))
	    exception(NOT_STR, ind, arg1, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    exception(LESS_THAN_ZERO, ind, arg2, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

	val = makeint(string_length(arg1));
	if (unify(arg2, val, th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_string_term(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, l, i, res;
    char str[STRSIZE];

    n = length(arglist);
    ind = makeind("string_term", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1) && !stringp(arg1))
	    exception(NOT_STR, ind, arg1, th);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    exception(ILLEGAL_ARGS, ind, arglist, th);

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
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1, arg2, arg3, arg4, i, j, k, start, len, str;
    char str1[STRSIZE], str2[STRSIZE];

    n = length(arglist);
    ind = makeind("substring", n, th);
    if (n == 4) {
	arg1 = car(arglist);	//instring
	arg2 = cadr(arglist);	//start
	arg3 = caddr(arglist);	//length
	arg4 = cadddr(arglist);	//outstring

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!stringp(arg1))
	    exception(NOT_STR, ind, arg1, th);
	if (!wide_variable_p(arg4) && !stringp(arg4))
	    exception(NOT_STR, ind, arg4, th);
	if (integerp(arg2) && GET_INT(arg2) < 0)
	    exception(LESS_THAN_ZERO, ind, arg2, th);
	if (integerp(arg3) && GET_INT(arg3) < 0)
	    exception(LESS_THAN_ZERO, ind, arg3, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!wide_variable_p(arg3) && !wide_integer_p(arg3))
	    exception(NOT_INT, ind, arg3, th);



	strcpy(str1, GET_NAME(arg1));
	start = GET_INT(arg2);
	len = GET_INT(arg3);
	if (string_length(arg1) < start + len - 1)
	    exception(RESOURCE_ERR, ind, makestr("strsize"), th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_float_text(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3;
    char str[STRSIZE], format[STRSIZE];
    double flt;

    n = length(arglist);
    ind = makeind("float_text", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !floatp(arg1))
	    exception(NOT_FLT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_int_text(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, i;
    char str[STRSIZE];

    n = length(arglist);
    ind = makeind("int_text", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1) && !integerp(arg1))
	    exception(NOT_FLT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !stringp(arg2))
	    exception(NOT_STR, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//controle
int b_n_cut(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("!", n, th);
    if (n == 0) {
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ifthen(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save1;

    n = length(arglist);
    ind = makeind("ifthen", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	save1 = sp[th];
	if (variablep(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (variablep(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	if (prove_all(arg1, sp[th], th) == YES) {
	    return (prove_all(addtail_body(rest, arg2, th), sp[th], th));
	} else {
	    unbind(save1, th);
	    return (NO);
	}

	unbind(save1, th);
	return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ifthenelse(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, body, res;

    n = length(arglist);
    ind = makeind("ifthenelse", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	save1 = sp[th];

	if (variablep(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (variablep(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (variablep(arg3))
	    exception(INSTANTATION_ERR, ind, arg3, th);

	body = addtail_body(arg2, arg1, th);
	body = list3(OR, body, arg3);
	/* body = (arg1,arg2);arg3 */
	if ((res = prove_all(body, sp[th], th)) == YES) {
	    return (prove_all(rest, sp[th], th));
	} else {
	    unbind(save1, th);
	    return (res);
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1;
    double start_time, end_time, time, lips;

    n = length(arglist);
    ind = makeind("measure", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_trace(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("trace", n, th);
    if (n == 0) {
	debug_flag = ON;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_notrace(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("notrace", n, th);
    if (n == 0) {
	debug_flag = OFF;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_spy(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("spy", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_nospy(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("nospy", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_leash(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("leash", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_debug(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("debug", n, th);
    if (n == 0) {
	printf("debug_flag=%d\n", debug_flag);
	printf("trace_flag=%d\n", trace_flag);
	printf("spy_list=");
	print(spy_list);
	printf("\n");
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_break(int arglist, int rest, int th)
{
    int n, ind, ret, save1, save2;

    n = length(arglist);
    ind = makeind("break", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_end_of_file(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("end_of_file", n, th);
    if (n == 0) {
	if (break_flag) {
	    variables[th] = variables_save[th];
	    break_flag = 0;
	    longjmp(buf2, 1);
	} else
	    return (YES);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_halt(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("halt", n, th);
    if (n == 0) {
	if (parent_flag)
	    exception(SYSTEM_ERR, ind,
		      makestr("Execute dp_close before halting."), th);

	printf("- good bye -\n");
	longjmp(buf, 2);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_abort(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("abort", n, th);
    if (n == 0) {
	longjmp(buf, 1);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//check data type
int b_atom(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("atom", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (atomp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_integer(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("integer", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (integerp(arg1) || longnump(arg1) || bignump(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_real(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("real", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (floatp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_number(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("number", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (numberp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_system(int arglist, int rest, int th)
{
    int n, ind, arg1, save1, save2, syslist, pred;

    n = length(arglist);
    ind = makeind("system", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!wide_variable_p(arg1) && !structurep(arg1))
	    exception(NOT_COMPOUND, ind, arg1, th);

	syslist = builtins;
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

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_var(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("var", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (variablep(arg1))
	    return (prove_all(rest, sp[th], th));
	else if (anonymousp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_nonvar(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("nonvar", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (variablep(arg1))
	    return (NO);
	else if (anonymousp(arg1))
	    return (NO);
	else
	    return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_atomic(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("atomic", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (atomicp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_list(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("list", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (listp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_string(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("string", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (stringp(arg1))
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



//-----structure------
int b_functor(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, res, i;

    n = length(arglist);
    ind = makeind("functor", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, list2(arg1, arg2), th);
	if (wide_variable_p(arg1) && wide_variable_p(arg3))
	    exception(INSTANTATION_ERR, ind, list2(arg1, arg3), th);
	if (wide_variable_p(arg1) && !atomicp(arg2)) {
	    exception(NOT_ATOMIC, ind, arg2, th);
	}
	if (wide_variable_p(arg1) && !integerp(arg3))
	    exception(NOT_INT, ind, arg3, th);
	if (wide_variable_p(arg1) && integerp(arg3) && GET_INT(arg3) < 0)
	    exception(LESS_THAN_ZERO, ind, arg3, th);
	if (wide_variable_p(arg1) && atomicp(arg2) &&
	    !atomp(arg2) && integerp(arg3) && GET_INT(arg3) > 0)
	    exception(NOT_ATOM, ind, arg2, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_arg(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, elt, i;

    n = length(arglist);
    ind = makeind("arg", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!compoundp(arg2))
	    exception(NOT_COMPOUND, ind, arg2, th);
	if (integerp(eval(arg1, th)) && GET_INT(eval(arg1, th)) < 0)
	    exception(LESS_THAN_ZERO, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_arg0(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, elt, i;

    n = length(arglist);
    ind = makeind("arg0", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!compoundp(arg2))
	    exception(NOT_COMPOUND, ind, arg2, th);
	if (integerp(eval(arg1, th)) && GET_INT(eval(arg1, th)) < 0)
	    exception(LESS_THAN_ZERO, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//-----other----
int b_listing(int arglist, int rest, int th)
{
    int n, ind, arg1, clauses, pred, list, temp;

    n = length(arglist);
    ind = makeind("listing", n, th);
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
	} else if (structurep(arg1) && eqlp(car(arg1), makeope("/")) &&
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
	    exception(NOT_INDICATOR, ind, arglist, th);
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


//transform bwtween predicate and data
int b_n_univ(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("=..", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (variablep(arg1) && variablep(arg2))
	    exception(INSTANTATION_ERR, ind, list2(arg1, arg2), th);
	if (listp(arg2) && compoundp(car(arg2)))
	    exception(NOT_ATOMIC, ind, arg2, th);
	if (variablep(arg1) && nullp(arg2))
	    exception(NON_EMPTY_LIST, ind, arg2, th);



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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_current_predicate(int arglist, int rest, int th)
{
    int n, ind, arg1, save1, save2, predlist, pred, aritylist, arity;

    n = length(arglist);
    ind = makeind("current_predicate", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!indicatorp(arg1))
	    exception(NOT_INDICATOR, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1, arg2, arg3, save1, save2, lis, weight, spec, op, w,
	s, o;

    n = length(arglist);
    ind = makeind("current_op", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!wide_variable_p(arg1) && !integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (integerp(arg1) && (GET_INT(arg1) < 0 || GET_INT(arg1) > 1200))
	    exception(OPE_PRIORITY_ERR, ind, arg1, th);
	if (!wide_variable_p(arg2) && !specp(arg2))
	    exception(OPE_SPEC_ERR, ind, arg2, th);
	if (!wide_variable_p(arg3) && !atomp(arg3))
	    exception(NOT_ATOM, ind, arg3, th);


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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_predicate_property(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("predicate_property", n, th);
    if (n == 2) {
	arg1 = car(arglist);	//term
	arg2 = cadr(arglist);	//prop

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);

}


int b_reset_op(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("reset_op", n, th);
    if (n == 0) {
	init_operator();
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int o_define(int x, int y, int th)
{
    int clause, ind;

    ind = makeind("assertz", 1, th);
    if (!nullp(y)) {
	if (builtinp(x))
	    exception(BUILTIN_EXIST, ind, x, th);
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
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("gc", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (arg1 == makeconst("full")) {
	    markcell(rest);
	    gbc();
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeconst("on")) {
	    gbc_flag = 1;
	    return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeconst("off")) {
	    gbc_flag = 0;
	    return (prove_all(rest, sp[th], th));
	} else {
	    exception(ILLEGAL_ARGS, ind, arglist, th);
	}
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int o_ignore(int nest, int n, int th)
{
    return (YES);
}


//-----------file system-------------------
int b_mkdir(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("mkdir", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	mkdir(GET_NAME(arg1), 0777);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_rmdir(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("rmdir", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	rmdir(GET_NAME(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_chdir(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("chdir", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	if (chdir(GET_NAME(arg1)) != -1)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_delete(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("delete", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	remove(GET_NAME(arg1));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_rename(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("rename", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);


	rename(GET_NAME(arg1), GET_NAME(arg2));
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

char *prolog_file_name(char *name)
{
    int n, i;
    static char str[STRSIZE];

    const char *env_home = getenv("NPROLOG_HOME");
    const char *home = getenv("HOME");

    /* 0 relative path */
    strcpy(str, name);
    n = strlen(str);
    if ((str[0] == '.' && str[1] == '/') ||
	(str[0] == '.' && str[1] == '.' && str[2] == '/')) {
	for (i = 2; i < n; i++) {
	    if (str[i] == '.')
		goto exit0;
	}
	strcat(str, ".pl");
      exit0:
	return (str);
    }

    /* 1. exist $NPROLOG_HOME */
    if (env_home) {
	strcpy(str, env_home);
	strcat(str, "/");
	strcat(str, name);
	n = strlen(str);
	for (i = 0; i < n; i++) {
	    if (str[i] == '.')
		goto exit1;
	}
	strcat(str, ".pl");
      exit1:
	return (str);
    }

    /* 2. exist $HOME */
    if (home) {
	strcpy(str, home);
	strcat(str, "/nprolog/");
	strcat(str, name);
	n = strlen(str);
	for (i = 0; i < n; i++) {
	    if (str[i] == '.')
		goto exit2;
	}
	strcat(str, ".pl");
      exit2:
	return (str);
    }

    /* absuolute path */
    strcpy(str, name);
    n = strlen(str);

    for (i = 0; i < n; i++) {
	if (str[i] == '.')
	    goto exit3;
    }
    strcat(str, ".pl");
  exit3:
    return (str);

}

int b_edit(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;
    char str[STRSIZE];
    char *editor;

    n = length(arglist);
    ind = makeind("edit", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg2 = makeatom("r", SIMP);
	goto edit;
    } else if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

      edit:
	if (!singlep(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (arg2 != makeatom("r", SIMP) && arg2 != makeatom("c", SIMP))
	    exception(ILLEGAL_ARGS, ind, arg2, th);


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
	    exception(SYSTEM_ERR, ind, arg1, th);

	if (arg2 == makeatom("r", SIMP))
	    b_reconsult(list1(arg1), NIL, th);
	else if (arg2 == makeatom("c", SIMP))
	    b_consult(list1(arg1), NIL, th);


	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_shell(int arglist, int rest, int th)
{
    int n, ind, arg1, res;
    char str1[STRSIZE];

    n = length(arglist);
    ind = makeind("shell", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!singlep(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	strcpy(str1, GET_NAME(arg1));
	res = system(str1);
	if (res == -1)
	    exception(SYSTEM_ERR, ind, arg1, th);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_syntaxerrors(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("syntaxerrors", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (arg1 != YES && arg1 != NO && !wide_variable_p(arg1))
	    exception(ILLEGAL_ARGS, ind, arg1, th);
	if (arg2 != YES && arg2 != NO && !wide_variable_p(arg2))
	    exception(ILLEGAL_ARGS, ind, arg1, th);

	res = unify(arg1, syntax_flag, th);
	syntax_flag = arg2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_fileerrors(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, res;

    n = length(arglist);
    ind = makeind("fileerrors", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (arg1 != YES && arg1 != NO && !wide_variable_p(arg1))
	    exception(ILLEGAL_ARGS, ind, arg1, th);
	if (arg2 != YES && arg2 != NO && !wide_variable_p(arg2))
	    exception(ILLEGAL_ARGS, ind, arg1, th);

	res = unify(arg1, syntax_flag, th);
	fileerr_flag = arg2;
	if (res == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_statistics(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("statistics", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (arg1 == makeatom("free", SIMP)) {
	    if (unify(arg2, makeint(fc), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("wp", SIMP)) {
	    if (unify(arg2, makeint(wp[th]), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("sp", SIMP)) {
	    if (unify(arg2, makeint(sp[th]), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else if (arg1 == makeatom("gc", SYS)) {
	    if (unify(arg2, makeint(gc), th) == YES)
		return (prove_all(rest, sp[th], th));
	} else {
	    return (NO);
	}

    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_sort(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("sort", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (!wide_variable_p(arg2) && !listp(arg2))
	    exception(NOT_LIST, ind, arg2, th);

	if (unify(arg2, sort(remove_duplicate(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_keysort(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("keysort", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!listp(arg1))
	    exception(NOT_LIST, ind, arg1, th);
	if (!wide_variable_p(arg2) && !listp(arg2))
	    exception(NOT_LIST, ind, arg2, th);

	if (unify(arg2, keysort(arg1), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_inc(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("inc", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, list2(arg1, arg2), th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (wide_integer_p(arg1) && negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (wide_integer_p(arg2) && negativep(arg2))
	    exception(LESS_THAN_ZERO, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_dec(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("dec", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1) && wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, list2(arg1, arg2), th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (wide_integer_p(arg1) && negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (wide_integer_p(arg2) && negativep(arg2))
	    exception(LESS_THAN_ZERO, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_cup(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, r, c;

    n = length(arglist);
    ind = makeind("ansi_cup", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg1) && !wide_integer_p(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (wide_integer_p(arg1) && negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg2) && !wide_integer_p(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (wide_integer_p(arg2) && negativep(arg2))
	    exception(LESS_THAN_ZERO, ind, arg2, th);

	r = get_int(arg1);
	c = get_int(arg2);
	ESCMOVE(r, c);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
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
	exception(SYSTEM_ERR, NIL, makestr("get_cursol"), 0);
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
    int n, ind, arg1, arg2, r, c, res1, res2;
    cursor position;

    n = length(arglist);
    ind = makeind("ansi_cpr", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!wide_variable_p(arg1))
	    exception(NOT_VAR, ind, arg1, th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_scp(int arglist, int rest, int th)
{
    int n, ind;
    cursor position;

    n = length(arglist);
    ind = makeind("ansi_scp", n, th);
    if (n == 0) {
	position = get_cursor();

	cursor_row_store = position.row;
	cursor_col_store = position.col;
	cursor_color_store = cursor_color;
	cursor_style_store = cursor_style;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_rcp(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("ansi_rcp", n, th);
    if (n == 0) {
	ESCMOVE(cursor_row_store, cursor_col_store);
	ESCCOLOR(cursor_color_store);
	ESCCOLOR(cursor_style_store);
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_ed(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("ansi_ed", n, th);
    if (n == 0) {
	ESCCLS;
	ESCTOP;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_el(int arglist, int rest, int th)
{
    int n, ind;

    n = length(arglist);
    ind = makeind("ansi_el", n, th);
    if (n == 0) {
	ESCCLSL1;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_ansi_cuu(int arglist, int rest, int th)
{
    int n, ind, arg1, m;

    n = length(arglist);
    ind = makeind("ansi_cuu", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVU;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_cud(int arglist, int rest, int th)
{
    int n, ind, arg1, m;

    n = length(arglist);
    ind = makeind("ansi_cud", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVD;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_cuf(int arglist, int rest, int th)
{
    int n, ind, arg1, m;

    n = length(arglist);
    ind = makeind("ansi_cuf", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVR;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_cub(int arglist, int rest, int th)
{
    int n, ind, arg1, m;

    n = length(arglist);
    ind = makeind("ansi_cub", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	m = get_int(arg1);
	while (m > 0) {
	    ESCMVL;
	    m--;
	}
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ansi_sgr(int arglist, int rest, int th)
{
    int n, ind, arg1, m;

    n = length(arglist);
    ind = makeind("ansi_sgr", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (negativep(arg1))
	    exception(LESS_THAN_ZERO, ind, arg1, th);
	if (get_int(arg1) > 47)
	    exception(RESOURCE_ERR, ind, makestr("over 47"), th);

	m = get_int(arg1);
	ESCCOLOR(m);
	if (m < 10)
	    cursor_style = m;
	else
	    cursor_color = m;
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_date(int arglist, int rest, int th)
{
    int n, ind, arg1, res;
    struct tm *jst;
    time_t t;

    n = length(arglist);
    ind = makeind("data", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (!wide_variable_p(arg1))
	    exception(NOT_VAR, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_date_day(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, y, m, d, w;

    n = length(arglist);
    ind = makeind("data_day", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!(structurep(arg1) && length(arg1) == 4))
	    exception(NOT_COMPOUND, ind, arg1, th);
	if (!wide_variable_p(arg2) && !integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_time(int arglist, int rest, int th)
{
    int n, ind, arg1, res;
    struct tm *jst;
    time_t t;

    n = length(arglist);
    ind = makeind("time", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_errcode(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("errcode", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	if (unify(arg1, makeint(error_code), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
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
    int n, ind, arg1, arg2, arg3, data, record_id, index;

    n = length(arglist);
    ind = makeind("recordh", n, th);
    if (n == 3) {
	arg1 = car(arglist);	//table_name
	arg2 = cadr(arglist);	//sort_key
	arg3 = caddr(arglist);	//term instance address
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);


	arg3 = deref(arg3, th);
	if (!integerp(arg3))
	    exception(NOT_INT, ind, arg3, th);

	if (record_pt >= RECORDMAX)
	    exception(RESOURCE_ERR, ind, makestr("recordmax"), th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_retrieveh(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, record_id, index, lis, term;

    n = length(arglist);
    ind = makeind("retrieveh", n, th);
    if (n == 3) {
	arg1 = car(arglist);	//table name
	arg2 = cadr(arglist);	//sort key
	arg3 = caddr(arglist);	//term instance address
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);


	save1 = sp[th];
	record_id = GET_ARITY(arg1) - 1;	//id starts from 1
	if (record_id < 0)
	    exception(NOT_RECORD, ind, arg1, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_instance(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2;

    n = length(arglist);
    ind = makeind("instance", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

	if (unify(arg2, car(get_int(arg1)), th) == YES)
	    return (prove_all(rest, sp[th], th));
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_recordz(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, temp, chain, next;

    n = length(arglist);
    ind = makeind("recordz", n, th);
    if (n == 3) {
	arg1 = car(arglist);	//key
	arg2 = cadr(arglist);	//term
	arg3 = caddr(arglist);	//ref 

	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (builtinp(arg1))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg3))
	    exception(NOT_VAR, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_record_after(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, chain, chain1;

    n = length(arglist);
    ind = makeind("record_after", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg3))
	    exception(NOT_VAR, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_recorda(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, chain;

    n = length(arglist);
    ind = makeind("recorda", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (builtinp(arg1))
	    exception(BUILTIN_EXIST, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg3))
	    exception(NOT_VAR, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_recorded(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, chain, save1, save2;

    n = length(arglist);
    ind = makeind("recorded", n, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_nref(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, chain;

    n = length(arglist);
    ind = makeind("nref", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg1) && !integerp(arg1))
	    exception(NOT_INT, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_pref(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, chain;

    n = length(arglist);
    ind = makeind("pref", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (!wide_variable_p(arg1) && !integerp(arg1))
	    exception(NOT_INT, ind, arg2, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_nth_ref(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, chain, i;

    n = length(arglist);
    ind = makeind("nth_ref", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (!integerp(arg2))
	    exception(NOT_INT, ind, arg2, th);
	if (!wide_variable_p(arg3))
	    exception(NOT_VAR, ind, arg3, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_replace(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, chain;

    n = length(arglist);
    ind = makeind("replace", n, th);
    if (n == 2) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);

	chain = get_int(arg1);
	arg2 = copy_heap(arg2);
	SET_CAR(chain, arg2);
	if (prove(NIL, sp[th], rest, th) == YES)
	    return (YES);
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_erase(int arglist, int rest, int th)
{
    int n, ind, arg1, addr;

    n = length(arglist);
    ind = makeind("erase", th, n);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = deref(arg1, th);
	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);

	addr = get_int(arg1);
	SET_CAR(addr, NIL);
	return (YES);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_eraseall(int arglist, int rest, int th)
{
    int n, ind, arg1;

    n = length(arglist);
    ind = makeind("eraseall", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	arg1 = deref(arg1, th);
	if (!atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);

	arg1 = makeatom(GET_NAME(arg1), SIMP);
	SET_RECORD(arg1, NIL);
	if (prove_all(rest, sp[th], th) == YES)
	    return (YES);
	else
	    return (NO);
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}



int b_removeh(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, arg3, save1, record_id, index, lis, prev, term;

    n = length(arglist);
    ind = makeind("removeh", n, th);
    if (n == 3) {
	arg1 = car(arglist);
	arg2 = cadr(arglist);
	arg3 = caddr(arglist);
	if (wide_variable_p(arg1))
	    exception(INSTANTATION_ERR, ind, arg1, th);
	if (!wide_variable_p(arg1) && !atomp(arg1))
	    exception(NOT_ATOM, ind, arg1, th);
	if (wide_variable_p(arg2))
	    exception(INSTANTATION_ERR, ind, arg2, th);
	if (!wide_variable_p(arg2) && !atomp(arg2))
	    exception(NOT_ATOM, ind, arg2, th);


	save1 = sp[th];
	record_id = GET_ARITY(arg1) - 1;	//id starts from 1
	if (record_id < 0)
	    exception(NOT_RECORD, ind, arg1, th);
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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_removeallh(int arglist, int rest, int th)
{
    int n, ind, arg1, record_id, i;

    n = length(arglist);
    ind = makeind("removeallh", n, th);
    if (n == 1) {
	arg1 = car(arglist);
	record_id = GET_ARITY(arg1) - 1;
	SET_ARITY(arg1, NIL);
	for (i = 0; i < HASHTBSIZE; i++)
	    record_hash_table[i][record_id] = NIL;
	//as a result, removed term will be retrieve by GC
	return (prove_all(rest, sp[th], th));
    }
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}

int b_ref(int arglist, int rest, int th)
{
    int n, ind, arg1, list, key, num, chain;

    n = length(arglist);
    ind = makeind("ref", n, th);
    if (n == 1) {
	arg1 = car(arglist);

	if (!integerp(arg1))
	    exception(NOT_INT, ind, arg1, th);

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
    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}


int b_key(int arglist, int rest, int th)
{
    int n, ind, arg1, arg2, save1, save2, list, key, chain, arity,
	keyarity;

    n = length(arglist);
    ind = makeind("key", n, th);
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
	    exception(NOT_ATOM, ind, arg1, th);
	if (!wide_variable_p(arg2))
	    exception(NOT_VAR, ind, arg2, th);

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

    exception(ARITY_ERR, ind, arglist, th);
    return (NO);
}
