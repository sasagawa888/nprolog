#include "npl.h"

//operator token
char operator[OPERATOR_NUMBER][5] = {
    { ":-" }, { "-->" }, { "," }, { ";" }, { "?-" }, { "." },
    { "+" }, { "-" }, { "*" }, { "/" }, { "//" }, { "<<" }, { ">>" },
	{ "\\" }, { "/\\" },
    { "\\/" },
    { "mod" }, { "rem" }, { "^" }, { "**" }, { "xor" }, { "iand" },
};

char function[FUNCTION_NUMBER][12] = {
    { "abs" }, { "sin" }, { "cos" }, { "tan" }, { "asin" }, { "acos" },
	{ "atan" },
    { "exp" }, { "log" }, { "floor" }, { "ceiling" }, { "truncate" },
    { "sign" }, { "sqrt" }, { "round" }, { "gcd" }, { "lcm" }, { "max" },
	{ "min" },
    { "random" }, { "randi" }, { "pi" }
};


//builtin token
char builtin[BUILTIN_NUMBER][30] = {
    { "->" }, { "=.." }, { "\\+" }, 
    { "==" }, { "\\==" }, { "@<" }, { "@=<" }, { "@>" }, { "@>=" },
    { "=:=" }, { "=/=" }, { "=\\=" }, { "<" }, { "=<" }, { ">" },
    { ">=" }, { "\\=" }, { "=" }, { "reverse" },
    { "is" }, { "edit" }, { "open" }, { "close" }, { "create" }, { "dup" },
    { "delete" }, { "rename" },
    { "op" }, { "!" }, { "assert" }, { "asserta" }, { "assertz" },
    { "abolish" }, { "read" }, { "write" }, { "put" }, { "get" },
	{ "get0" },
    { "get0_noecho" }, { "nl" },
    { "read_line" }, { "reset_op" }, { "skip" }, { "predicate_property" },
    { "tab" }, { "fail" }, { "not" }, { "true" }, { "halt" }, { "abort" },
    { "listing" }, { "functor" }, { "arg" },
    { "writeq" }, { "display" }, { "ref" },
    { "atom_concat" }, { "atom_string" }, { "consult" }, { "reconsult" },
    { "see" }, { "seeing" }, { "seen" }, { "tell" }, { "telling" },
	{ "told" }, { "trace" },
    { "notrace" }, { "spy" },
    { "nospy" }, { "leash" }, { "atom" }, { "integer" }, { "real" },
	{ "float" },
    { "number" },
    { "var" }, { "nonvar" }, { "atomic" }, { "list" }, { "gc" },
	{ "time" }, { "name" },
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
    { "recordh" }, { "recorda" }, { "recordz" }, { "instance" },
	{ "removeallh" },
    { "stdin" }, { "stdout" }, { "stdinout" },
    { "ctr_set" }, { "ctr_dec" }, { "ctr_inc" }, { "ctr_is" },
    { "heapd" }, { "list_text" },
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
    { "compile_file" }, { "timer_microseconds" }, { "with" }
};
