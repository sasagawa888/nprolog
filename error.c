#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#ifdef __linux
#include <stdio_ext.h>
#endif
#include "npl.h"

//------error for compier-----
void errorcomp(int errnum, int name, int arg)
{
    error(GET_INT(errnum), GET_NAME(name), arg);
}


//-------error------
void error(int errnum, char *fun, int arg)
{

    error_code = errnum;
    if (check_flag) {
	longjmp(buf1, 1);
    }

    ESCFRED;
    switch (errnum) {
    case SYNTAX_ERR:
	if (syntax_flag == YES) {
	    printf("Syntax error %s ", fun);
	    if (arg != NIL)
		print(arg);

	}
	break;

    case BUILTIN_EXIST:
	printf("Permission error %s ", fun);
	print(arg);
	break;

    case ALIAS_EXIST:
	printf("Permission error %s ", fun);
	print(arg);
	break;

    case STATIC_PROCEDURE:
	printf("Static procedure %s ", fun);
	print(arg);
	break;

    case ILLEGAL_ARGS:
	printf("Illegal argument %s ", fun);
	print(arg);
	break;

    case CANT_READ:
	printf("Can't read of %s ", fun);
	break;

    case NOT_NUM:
	printf("Not a number %s ", fun);
	print(arg);
	break;

    case NOT_COMPUTABLE:
	printf("Not computable %s ", fun);
	print(arg);
	break;

    case DIV_ZERO:
	printf("Divide by zero %s ", fun);
	break;

    case NOT_INT:
	printf("Not an integer %s ", fun);
	print(arg);
	break;

    case NOT_FLT:
	printf("Not a float number %s ", fun);
	print(arg);
	break;

    case NOT_STR:
	printf("Not a string %s ", fun);
	print(arg);
	break;

    case NOT_ATOM:
	printf("Not an atom %s ", fun);
	print(arg);
	break;

    case NOT_ATOMIC:
	printf("Not an atomic %s ", fun);
	print(arg);
	break;

    case NOT_COMPOUND:
	printf("Not a compound %s ", fun);
	print(arg);
	break;

    case WRONG_ARGS:
	printf("Wrong arguments %s ", fun);
	print(arg);
	break;

    case PRED_INDICATOR:
	printf("Not predicate indicator %s ", fun);
	print(arg);
	break;


    case UNCAUGHT_EXCEPTION:
	printf("Uncaught exception %s ", fun);
	print(arg);
	break;

    case NOT_LIST:
	printf("Not a list %s ", fun);
	print(arg);
	break;

    case NOT_VAR:
	printf("Not a variable %s ", fun);
	print(arg);
	break;

    case CANT_OPEN:
	if (fileerr_flag == YES) {
	    printf("Can't open file %s ", fun);
	    if (arg != NIL)
		print(arg);
	}
	break;

    case FILE_EXIST:
	if (fileerr_flag == YES) {
	    printf("File not exist %s ", fun);
	    if (arg != NIL)
		print(arg);
	}
	break;

    case STACK_OVERF:
	printf("Stack over flow ");
	break;

    case VARIANT_OVERF:
	printf("Variant over flow ");
	break;

    case SYSTEM_ERROR:
	printf("System error at %s ", fun);
	break;

    case OUT_OF_RANGE:
	printf("Out of range %s ", fun);
	print(arg);
	break;

    case UNDEF_PRED:
	printf("Undefined predicate %s ", fun);
	break;


    case EOF_ERROR:
	printf("End of file error %s ", fun);
	break;

    case INSTANTATION_ERR:
	printf("Instantation error %s ", fun);
	print(arg);
	break;
    case EXPONENT_ERR:
	printf("Exponentiation of a too big integer %s ", fun);
	break;

    case RESOURCE_ERR:
	printf("Resource error %s ", fun);
	break;

    case NOT_CHAR:
	printf("Not character %s ", fun);
	print(arg);
	break;

    case NOT_CALLABLE:
	printf("Not callable %s ", fun);
	print(arg);
	break;
    case EXISTENCE_ERR:
	printf("Existence error %s ", fun);
	print(arg);
	break;
    case ARITY_ERR:
	printf("Arity error %s ", fun);
	print(arg);
	break;
    case NOT_SOURCE:
	printf("Not source-sink %s ", fun);
	print(arg);
	break;
    case NOT_STREAM:
	printf("Not stream or alias %s ", fun);
	print(arg);
	break;
    case NOT_CLOSE_OPTION:
	printf("Not close option %s ", fun);
	print(arg);
	break;
    case NOT_IO_MODE:
	printf("Not I/O mode %s ", fun);
	print(arg);
	break;
    case LESS_THAN_ZERO:
	printf("Less than zero %s ", fun);
	print(arg);
	break;

    case NON_EMPTY_LIST:
	printf("Not empty list %s ", fun);
	print(arg);
	break;

    case NOT_STREAM_OPTION:
	printf("Not stream option %s ", fun);
	print(arg);
	break;

    case OPE_PRIORITY_ERR:
	printf("Operator priority error %s ", fun);
	print(arg);
	break;

    case OPE_SPEC_ERR:
	printf("Operator specifier error %s ", fun);
	print(arg);
	break;

    case NOT_ORDER:
	printf("Not compare order %s ", fun);
	print(arg);
	break;

    case NOT_INPUT_STREAM:
	printf("Not input stream %s ", fun);
	print(arg);
	break;

    case NOT_OUTPUT_STREAM:
	printf("Not output stream %s ", fun);
	print(arg);
	break;

    case PAST_EOF_INPUT:
	printf("Past EOF %s ", fun);
	print(arg);
	break;

    case MODIFY_OPE_ERR:
	printf("Modify operator error %s ", fun);
	print(arg);
	break;

    case EVALUATION_ERR:
	printf("Evaluation error %s ", fun);
	print(arg);
	break;
    case NOT_CHAR_CODE:
	printf("Not charactor code %s ", fun);
	print(arg);
	break;

    case NOT_OPEN_OPTION:
	printf("Not open option %s ", fun);
	print(arg);
	break;

    case NOT_TERM:
	printf("Not term %s ", fun);
	print(arg);
	break;

    case RECORD_OVERF:
	printf("recordh tables max over %s ", fun);
	break;

    case NOT_RECORD:
	printf("recordh tables has no record %s ", fun);
	print(arg);
	break;

    }
    printf("\n");
    stok.ch = NUL;
    stok.flag = GO;
    stok.type = NUL;
    stok.ahead = NUL;
    memset(stok.buf, NUL, BUFSIZE);
    FLUSH if (open_flag) {
	open_flag = 0;
	printf("around here line=%d column=%d\n", line, column);
	fflush(stdout);
	fclose(GET_PORT(input_stream));
    }
    ESCFORG;
    if (script_flag) {
	exit(EXIT_FAILURE);
    }

    read_line(-2);		// clear buffer

    if (init_flag) {
	init_flag = 0;
	longjmp(buf, 2);
    } else if (break_flag) {
	longjmp(buf2, 2);
    } else
	longjmp(buf, 1);
}
