
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
    { "\\" }, { "/\\" },
    { "\\/" },
    { "mod" }, { "^" }, { "**" },
};

char function[FUNCTION_NUMBER][12] = {
    { "abs" }, { "sin" }, { "cos" }, { "tan" }, { "asin" }, { "acos" },
    { "atan" },
    { "exp" }, { "ln" }, { "log" }, { "sqrt" }, { "round" },
    { "random" }, { "randi" }, { "pi" }
};


//builtin token
char builtin[BUILTIN_NUMBER][30] = {
    { "->" }, { "=.." }, { "\\+" },
    { "==" }, { "\\==" }, { "@<" }, { "@=<" }, { "@>" }, { "@>=" },
    { "=:=" }, { "=/=" }, { "=\\=" }, { "<" }, { "=<" }, { ">" },
    { ">=" }, { "\\=" }, { "=" },
    { "is" }, { "edit" }, { "open" }, { "close" }, { "create" }, { "dup" },
    { "delete" }, { "rename" },
    { "op" }, { "!" }, { "assert" }, { "asserta" }, { "assertz" },
    { "abolish" }, { "read" }, { "write" }, { "put" }, { "get" },
    { "get0" }, { "ifthen" }, { "ifthenelse" },
    { "get0_noecho" }, { "nl" }, { "read_string" },
    { "read_line" }, { "reset_op" }, { "skip" }, { "predicate_property" },
    { "tab" }, { "fail" }, { "not" }, { "true" }, { "halt" }, { "abort" },
    { "listing" }, { "functor" }, { "arg" },
    { "writeq" }, { "display" }, { "ref" }, { "key" },
    { "atom_concat" }, { "atom_string" }, { "consult" }, { "reconsult" },
    { "see" }, { "seeing" }, { "seen" }, { "tell" }, { "telling" },
    { "save" },
    { "told" }, { "trace" },
    { "notrace" }, { "spy" },
    { "nospy" }, { "leash" }, { "atom" }, { "integer" }, { "real" },
    { "float" },
    { "number" },
    { "var" }, { "nonvar" }, { "atomic" }, { "list" }, { "gc" },
    { "time" }, { "name" }, { "nth_char" },
    { "bounded" },
    { "flush" }, { "date" }, { "date_day" }, { "char_code" },
    { "string" }, { "string_chars" }, { "string_codes" }, { "ground" },
    { "concat" }, { "substring" }, { "string_term" }, { "float_text" },
    { "inc" }, { "dec" }, { "compare" }, { "in" }, { "out" },
    { "mkdir" }, { "rmdir" }, { "chdir" }, { "string_length" },
    { "sort" }, { "keysort" }, { "length" }, { "shell" }, { "measure" },
    { "syntaxerrors" },
    { "ansi_cuu" }, { "ansi_cud" }, { "ansi_cuf" }, { "ansi_cub" },
    { "ansi_cup" }, { "ansi_cpr" }, { "ansi_scp" }, { "ansi_rcp" },
    { "ansi_ed" }, { "ansi_el" }, { "errorcode" },
    { "recordh" }, { "recorda" }, { "recordz" }, { "recorded" },
	{ "record_after" },
    { "instance" }, { "reverse" },
    { "removeallh" }, { "erase" }, { "eraseall" },
    { "stdin" }, { "stdout" }, { "stdinout" },
    { "ctr_set" }, { "ctr_dec" }, { "ctr_inc" }, { "ctr_is" },
    { "heapd" }, { "list_text" }, { "nref" }, { "pref" }, { "nth_ref" }, { "replace" },
    { "member" }, { "append" }, { "repeat" }, { "system" },
    { "retract" }, { "clause" }, { "call" }, { "directory" },
    { "between" }, { "bagof" }, { "setof" }, { "findall" },
    { "current_predicate" }, { "current_op" }, { "retrieveh" }, { "removeh" }
};

//compiled predicate
char compiled[COMPILED_NUMBER][30] = {
};

//extened predicate
char extended[EXTENDED_NUMBER][30] = {
    { "wiringpi_setup_gpio" }, { "wiringpi_spi_setup" },
    { "pwm_set_mode" },
    { "pwm_set_clock" }, { "pwm_set_range" }, { "pin_mode" },
    { "digital_write" },
    { "pwm_write" }, { "pull_up_dn_control" }, { "digital_read" },
    { "delay" },
    { "delay_microseconds" },
    { "compile_file" }, { "timer_microseconds" }, { "with" },
    { "existerrors" },
};


static bool in_syntax_table(const char *str)
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
    if (in_syntax_table(str)) {
	return HIGHLIGHT_SYNTAX;
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
