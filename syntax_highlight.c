
#include <string.h>
#include <stdbool.h>
#include "term.h"
#include "npl.h"

#define NELEM(X) (sizeof(X) / sizeof((X)[0]))

// dummy
char special[1][1] = { };

//operator token
char operator[OPERATOR_NUMBER][5] = {
    { ":-" }, { "-->" }, { "," }, { ";" }, { "?-" }, { "." },
    { "+" }, { "-" }, { "*" }, { "/" }, { "//" }, { "<<" }, { ">>" },
    { "\\" }, { "/\\" }, { "\\/" }, { "mod" }, { "^" }, { "**" },
};

char function[FUNCTION_NUMBER][12] = {
    { "abs" }, { "sin" }, { "cos" }, { "tan" }, { "asin" }, { "acos" },
    { "atan" }, { "exp" }, { "ln" }, { "log" }, { "sqrt" }, { "round" },
    { "random" }, { "randi" }, { "pi" }
};


//builtin token
char builtin[BUILTIN_NUMBER][30] = {
    { "->" }, { "=.." }, { "==" }, { "\\==" }, { "@<" },
    { "@=<" }, { "@>" }, { "@>=" }, { "=:=" }, { "=/=" }, { "=\\=" },
    { "<" }, { "=<" }, { ">" }, { ">=" }, { "\\=" }, { "=" }, { "\\+" },
    { "is" }, { "edit" }, { "open" }, { "close" }, { "create" }, { "dup" },
    { "delete" }, { "rename" }, { "op" }, { "!" }, { "assert" },
    { "asserta" }, { "assertz" }, { "abolish" }, { "read" }, { "write" },
    { "display" }, { "put" }, { "get" }, { "get0" }, { "ifthen" },
    { "ifthenelse" }, { "get0_noecho" }, { "nl" }, { "read_string" },
    { "read_line" }, { "reset_op" }, { "skip" }, { "predicate_property" },
    { "tab" }, { "fail" }, { "not" }, { "true" }, { "halt" }, { "abort" },
    { "listing" }, { "functor" }, { "arg" }, { "writeq" }, { "display" },
    { "ref" }, { "key" }, { "atom_string" }, { "write_canonical" },
    { "consult" }, { "reconsult" }, { "see" }, { "seeing" }, { "seen" },
    { "tell" }, { "telling" }, { "save" }, { "told" }, { "trace" },
    { "notrace" }, { "spy" }, { "nospy" }, { "leash" }, { "atom" },
    { "integer" }, { "real" }, { "float" }, { "number" },
    { "var" }, { "nonvar" }, { "atomic" }, { "list" }, { "gc" },
    { "time" }, { "name" }, { "nth_char" }, { "bounded" },
    { "flush" }, { "date" }, { "date_day" },
    { "string" }, { "string_chars" }, { "string_codes" },
    { "concat" }, { "substring" }, { "string_term" }, { "float_text" },
    { "inc" }, { "dec" }, { "compare" }, { "in" }, { "out" },
    { "mkdir" }, { "rmdir" }, { "chdir" }, { "string_length" },
    { "atom_length" },
    { "sort" }, { "keysort" }, { "length" }, { "shell" }, { "measure" },
    { "syntaxerrors" }, { "fileerrors" }, { "statistics" }, { "eq" },
    { "ansi_cuu" }, { "ansi_cud" }, { "ansi_cuf" }, { "ansi_cub" },
    { "ansi_cup" }, { "ansi_cpr" }, { "ansi_scp" }, { "ansi_rcp" },
    { "ansi_ed" }, { "ansi_el" }, { "errcode" },
    { "recordh" }, { "recorda" }, { "recordz" }, { "recorded" },
    { "record_after" }, { "break" }, { "end_of_file" },
    { "instance" }, { "removeallh" }, { "erase" },
    { "eraseall" }, { "stdin" }, { "stdout" }, { "stdinout" },
    { "ctr_set" }, { "ctr_dec" }, { "ctr_inc" }, { "ctr_is" },
    { "heapd" }, { "list_text" }, { "nref" }, { "pref" }, { "nth_ref" },
    { "replace" }, { "member" }, { "append" }, { "repeat" }, { "system" },
    { "retract" }, { "clause" }, { "call" }, { "directory" }, { "select" },
    { "maplist" }, { "ground" }, { "compound" }, { "once" },
    { "atom_codes" }, { "char_code" },
    { "between" }, { "bagof" }, { "setof" }, { "findall" }, { "succ" },
    { "atom_chars" }, { "atom_concat" },
    { "current_predicate" }, { "current_op" }, { "retrieveh" },
    { "removeh" }, { "unify_with_occurs_check" },
    { "get_code" }, { "get_char" }, { "get_byte" }, { "put_char" },
    { "flush_output" }, { "put_code" }, { "put_byte" },
    { "number_codes" }, { "number_chars" }, { "catch" }, { "throw" },
    { "set_input" }, { "set_output" }, { "use_module" }, { "module" },
    { "copy_term" },
    { "current_input" }, { "current_output" }, { "at_end_of_stream" },
    { "peek_code" }, { "peek_char" }, { "peek_byte" },
    { "stream_property" }, { "dynamic" },
    { "create_client_socket" }, { "create_server_socket" },
    { "b_send_socket" },
    { "recv_socket" }, { "close_socket" },
};

//compiled predicate
char compiled[COMPILED_NUMBER][30] = {
};

//extened predicate
char extended[EXTENDED_NUMBER][30] = {
    { "wiringpi_setup_gpio" }, { "wiringpi_spi_setup" },
    { "pwm_set_mode" }, { "pwm_set_clock" }, { "pwm_set_range" },
    { "pin_mode" }, { "digital_write" },
    { "pwm_write" }, { "pull_up_dn_control" }, { "digital_read" },
    { "delay" }, { "delay_microseconds" },
    { "compile_file" }, { "timer_microseconds" }, { "with" },
    { "existerrors" }, { "dp_create" }, { "dp_consult" },
    { "dp_transfer" }, { "dp_and" }, { "dp_or" },
    { "dp_compile" }, { "dp_prove" }, { "dp_close" }, { "dp_parent" },
    { "dp_child" }, { "dp_wait" }, { "dp_pause" }, { "dp_resume" },
    { "mt_create" }, { "mt_close" }, { "mt_and" }, { "mt_or" },
    { "mt_prove" }, { "cinline"},
};


static bool in_operator_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(operator); i++) {
	if (strcmp(operator[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

static bool in_builtin_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(builtin); i++) {
	if (strcmp(builtin[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

static bool in_extended_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(extended); i++) {
	if (strcmp(extended[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

bool in_special_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(special); i++) {
	if (strcmp(special[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

bool in_function_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(function); i++) {
	if (strcmp(function[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

enum HighlightToken maybe_match(const char *str)
{
    if (in_operator_table(str)) {
	return HIGHLIGHT_OPERATOR;
    }
    if (in_builtin_table(str)) {
	return HIGHLIGHT_BUILTIN;
    }
    if (in_extended_table(str)) {
	return HIGHLIGHT_EXTENDED;
    }
    if (in_function_table(str)) {
	return HIGHLIGHT_FUNCTION;
    }
    return HIGHLIGHT_NONE;
}

void
gather_fuzzy_matches(const char *str, const char *candidates[],
		     int *candidate_pt)
{
    int i;

    for (i = 0; i < (int) NELEM(operator); i++) {
	if (strstr(operator[i], str) != NULL && operator[i][0] == str[0]) {
	    candidates[*candidate_pt] = operator[i];
	    *candidate_pt = (*candidate_pt) + 1;
	}
    }
    for (i = 0; i < (int) NELEM(builtin); i++) {
	if (strstr(builtin[i], str) != NULL && builtin[i][0] == str[0]) {
	    candidates[*candidate_pt] = builtin[i];
	    *candidate_pt = (*candidate_pt) + 1;
	}
    }
    for (i = 0; i < (int) NELEM(extended); i++) {
	if (strstr(extended[i], str) != NULL && extended[i][0] == str[0]) {
	    candidates[*candidate_pt] = extended[i];
	    *candidate_pt = (*candidate_pt) + 1;
	}
    }
}
