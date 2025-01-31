#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#ifdef __linux
#include <stdio_ext.h>
#endif
#include "npl.h"

void init_handler()
{

    instantation_tag = list3(makepred("error"),
	                         makepred("instantiation_error"),
							 makevar("%Context"));
    uninstantation_tag = list2(makepred("uninstantiation_error"),makevar("%Term"));
    type_tag = list3(makepred("error"),
	                 list3(makepred("type_error"),makevar("%TypeName"),makevar("%Culprit")),
	                 makevar("%Context"));
    domain_tag = list3(makepred("error"),
	                 list3(makepred("domain_error"),makevar("%Domain"),makevar("%Culprit")),
					 makevar("%Context"));
    exsistence_tag = list3(makepred("error"),
	                      list3(makepred("existence_error"),makevar("%ObjectType"),makevar("%Culprit")),
						  makevar("%Context"));
    permisson_tag = list3(makepred("error"),
	                     list4(makepred("permission_error"),makevar("%Operation"),
                                                            makevar("%ObjectType"),
                                                            makevar("%Culprit")),
				          makevar("%Context"));
    context_tag = list2(makepred("context_error"),list2(makevar("%ContextType"),
                                                        makevar("%CommandType")));
    syntax_tag = list3(makepred("error"),list2(makepred("syntax_error"),makevar("%Message")),
	                                     makevar("%Context"));
    evaluation_tag = list2(makepred("evaluation_error"),list2(makevar("%ErrorType"),
                                                              makevar("%Culprit")));
    representation_tag =  list2(makepred("representation_error"),makevar("%ErrorType"));
    consistency_tag = list2(makepred("consistency_error"),list3(makevar("%Culprit1"),
                                                                makevar("%Culprit2"),
                                                                makevar("%Message")));
    resource_tag = list3(makepred("error"),
	                     list2(makepred("resource_error"),makevar("%ResourceType")),
						 makevar("%Context"));
    system_tag = list2(makepred("system_error"),makevar("%Message"));
    
}


//------error for compier-----
void errorcomp(int errnum, int name, int arg)
{
    error(GET_INT(errnum), GET_NAME(name), arg, 0);
}


//-------error------
void exception(int errnum, int ind, int arg, int th)
{

    error_code = errnum;
    if (check_flag) {
	longjmp(buf1, 1);
    }

    switch (errnum) {

    case SYNTAX_ERR:
	bindsym(makevar("%Message"),ind,th);
	bindsym(makevar("%Context"),arg,th);
	throw(type_tag,th);
	ESCFRED;
	if (syntax_flag == YES) {
	    printf("Syntax error %s ", GET_NAME(ind));
	    if (arg != NIL)
		print(arg);
	}
	break;
	/*
    case BUILTIN_EXIST:
	ESCFRED;
	printf("Permission error %s ", fun);
	print(arg);
	break;

    case ALIAS_EXIST:
	ESCFRED;
	printf("Permission error %s ", fun);
	print(arg);
	break;

    case STATIC_PROCEDURE:
	ESCFRED;
	printf("Static procedure %s ", fun);
	print(arg);
	break;

    case ILLEGAL_ARGS:
	ESCFRED;
	printf("Illegal argument %s ", fun);
	print(arg);
	break;

    case CANT_READ:
	ESCFRED;
	printf("Can't read of %s ", fun);
	break;

    case NOT_NUM:
	ESCFRED;
	printf("Not a number %s ", fun);
	print(arg);
	break;

    case NOT_COMPUTABLE:
	ESCFRED;
	printf("Not computable %s ", fun);
	print(arg);
	break;

    case DIV_ZERO:
	ESCFRED;
	printf("Divide by zero %s ", fun);
	break;
	*/
    case NOT_INT:
	bindsym(makevar("%TypeName"),makeconst("integer"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not an integer ");
	print(ind);
	printf(" ");
	print(arg);
	break;

	
    case NOT_FLT:
	bindsym(makevar("%TypeName"),makeconst("float"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not a float number ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_STR:
	bindsym(makevar("%TypeName"),makeconst("string"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not a string ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	
    case NOT_ATOM:
	bindsym(makevar("%TypeName"),makeconst("atom"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not an atom ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	
    case NOT_ATOMIC:
	bindsym(makevar("%TypeName"),makeconst("atomic"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not an atomic ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_COMPOUND:
	bindsym(makevar("%TypeName"),makeconst("compound"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not a compound ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case WRONG_ARGS:
	ESCFRED;
	printf("Wrong arguments %s ", fun);
	print(arg);
	break;

    case PRED_INDICATOR:
	ESCFRED;
	printf("Not predicate indicator %s ", fun);
	print(arg);
	break;


	*/
    case NOT_LIST:
	bindsym(makevar("%TypeName"),makeconst("list"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not a list ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case NOT_VAR:
	ESCFRED;
	printf("Not a variable %s ", fun);
	print(arg);
	break;

    case CANT_OPEN:
	ESCFRED;
	if (fileerr_flag == YES) {
	    printf("Can't open file %s ", fun);
	    if (arg != NIL)
		print(arg);
	}
	break;

    case FILE_EXIST:
	ESCFRED;
	if (fileerr_flag == YES) {
	    printf("File not exist %s ", fun);
	    if (arg != NIL)
		print(arg);
	}
	break;

    case STACK_OVERF:
	ESCFRED;
	printf("Stack over flow ");
	break;

    case VARIANT_OVERF:
	ESCFRED;
	printf("Variant over flow ");
	break;

    case SYSTEM_ERROR:
	ESCFRED;
	printf("System error at %s ", fun);
	break;

    case OUT_OF_RANGE:
	ESCFRED;
	printf("Out of range %s ", fun);
	print(arg);
	break;

    case UNDEF_PRED:
	ESCFRED;
	printf("Undefined predicate %s ", fun);
	break;


    case EOF_ERROR:
	ESCFRED;
	printf("End of file error %s ", fun);
	break;
	*/
    case INSTANTATION_ERR:
	bindsym(makevar("%Context"),ind,th);
	throw(instantation_tag,th);
	ESCFRED;
	printf("Instantation error ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case EXPONENT_ERR:
	ESCFRED;
	printf("Exponentiation of a too big integer %s ", fun);
	break;
	*/
    case RESOURCE_ERR:
	bindsym(makevar("%ResourceType"),arg,th);
	throw(resource_tag,th);
	ESCFRED;
	printf("Resource error ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case NOT_CHAR:
	ESCFRED;
	printf("Not character %s ", fun);
	print(arg);
	break;

    case NOT_CALLABLE:
	ESCFRED;
	printf("Not callable %s ", fun);
	print(arg);
	break;
    case EXISTENCE_ERR:
	ESCFRED;
	printf("Existence error %s ", fun);
	print(arg);
	break;
	*/
    case ARITY_ERR:
	bindsym(makevar("%ObjectType"),makeconst("predicate"),th);
	bindsym(makevar("%Culprit"),ind,th);
	bindsym(makevar("%Context"),ind,th);
	throw(exsistence_tag,th);
	ESCFRED;
	printf("Arity error ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case NOT_SOURCE:
	ESCFRED;
	printf("Not source-sink %s ", fun);
	print(arg);
	break;
	*/
    case NOT_STREAM:
	bindsym(makevar("%Domain"),makeconst("stream_or_alias"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(domain_tag,th);
	ESCFRED;
	printf("Not stream or alias ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case NOT_CLOSE_OPTION:
	ESCFRED;
	printf("Not close option %s ", fun);
	print(arg);
	break;
    case NOT_IO_MODE:
	ESCFRED;
	printf("Not I/O mode %s ", fun);
	print(arg);
	break;
	*/
    case LESS_THAN_ZERO:
	bindsym(makevar("%Domain"),makeconst("not_less_than_zero"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),ind,th);
	throw(domain_tag,th);
	ESCFRED;
	printf("Less than zero ");
	print(ind);
	printf(" ");
	print(arg);
	break;
	/*
    case NON_EMPTY_LIST:
	ESCFRED;
	printf("Not empty list %s ", fun);
	print(arg);
	break;

    case NOT_STREAM_OPTION:
	ESCFRED;
	printf("Not stream option %s ", fun);
	print(arg);
	break;

    case OPE_PRIORITY_ERR:
	ESCFRED;
	printf("Operator priority error %s ", fun);
	print(arg);
	break;

    case OPE_SPEC_ERR:
	ESCFRED;
	printf("Operator specifier error %s ", fun);
	print(arg);
	break;

    case NOT_ORDER:
	ESCFRED;
	printf("Not compare order %s ", fun);
	print(arg);
	break;

    case NOT_INPUT_STREAM:
	ESCFRED;
	printf("Not input stream %s ", fun);
	print(arg);
	break;

    case NOT_OUTPUT_STREAM:
	ESCFRED;
	printf("Not output stream %s ", fun);
	print(arg);
	break;

    case PAST_EOF_INPUT:
	ESCFRED;
	printf("Past EOF %s ", fun);
	print(arg);
	break;

    case MODIFY_OPE_ERR:
	ESCFRED;
	printf("Modify operator error %s ", fun);
	print(arg);
	break;

    case EVALUATION_ERR:
	ESCFRED;
	printf("Evaluation error %s ", fun);
	print(arg);
	break;
    case NOT_CHAR_CODE:
	ESCFRED;
	printf("Not charactor code %s ", fun);
	print(arg);
	break;

    case NOT_OPEN_OPTION:
	ESCFRED;
	printf("Not open option %s ", fun);
	print(arg);
	break;

    case NOT_TERM:
	ESCFRED;
	printf("Not term %s ", fun);
	print(arg);
	break;

    case RECORD_OVERF:
	ESCFRED;
	printf("recordh tables max over %s ", fun);
	break;

    case NOT_RECORD:
	ESCFRED;
	printf("recordh tables has no record %s ", fun);
	print(arg);
	break;
	*/
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

    if (child_flag) {
	memset(bridge, 0, sizeof(bridge));
	bridge[0] = 0x15;
	send_to_parent_buffer();
	child_busy_flag = 0;
    }

    if (init_flag) {
	init_flag = 0;
	longjmp(buf, 2);
    } else if (break_flag) {
	longjmp(buf2, 2);
    } else if (thread_flag && th != 0) {
	longjmp(buf3, 1);
    } else
	longjmp(buf, 1);
}


void error(int errnum, char *fun, int arg, int th)
{

    error_code = errnum;
    if (check_flag) {
	longjmp(buf1, 1);
    }

    switch (errnum) {
    case SYNTAX_ERR:
	ESCFRED;
	if (syntax_flag == YES) {
	    printf("Syntax error %s ", fun);
	    if (arg != NIL)
		print(arg);

	}
	break;

    case BUILTIN_EXIST:
	ESCFRED;
	printf("Permission error %s ", fun);
	print(arg);
	break;

    case ALIAS_EXIST:
	ESCFRED;
	printf("Permission error %s ", fun);
	print(arg);
	break;

    case STATIC_PROCEDURE:
	ESCFRED;
	printf("Static procedure %s ", fun);
	print(arg);
	break;

    case ILLEGAL_ARGS:
	ESCFRED;
	printf("Illegal argument %s ", fun);
	print(arg);
	break;

    case CANT_READ:
	ESCFRED;
	printf("Can't read of %s ", fun);
	break;

    case NOT_NUM:
	ESCFRED;
	printf("Not a number %s ", fun);
	print(arg);
	break;

    case NOT_COMPUTABLE:
	ESCFRED;
	printf("Not computable %s ", fun);
	print(arg);
	break;

    case DIV_ZERO:
	ESCFRED;
	printf("Divide by zero %s ", fun);
	break;

    case NOT_INT:
	bindsym(makevar("%TypeName"),makeconst("integer"),th);
	bindsym(makevar("%Culprit"),arg,th);
	bindsym(makevar("%Context"),makeconst(fun),th);
	throw(type_tag,th);
	ESCFRED;
	printf("Not a small integer %s ", fun);
	print(arg);
	break;

    case NOT_FLT:
	ESCFRED;
	printf("Not a float number %s ", fun);
	print(arg);
	break;

    case NOT_STR:
	ESCFRED;
	printf("Not a string %s ", fun);
	print(arg);
	break;

    case NOT_ATOM:
	ESCFRED;
	printf("Not an atom %s ", fun);
	print(arg);
	break;

    case NOT_ATOMIC:
	ESCFRED;
	printf("Not an atomic %s ", fun);
	print(arg);
	break;

    case NOT_COMPOUND:
	ESCFRED;
	printf("Not a compound %s ", fun);
	print(arg);
	break;

    case WRONG_ARGS:
	ESCFRED;
	printf("Wrong arguments %s ", fun);
	print(arg);
	break;

    case PRED_INDICATOR:
	ESCFRED;
	printf("Not predicate indicator %s ", fun);
	print(arg);
	break;


    case UNCAUGHT_EXCEPTION:
	ESCFRED;
	printf("Uncaught exception %s ", fun);
	print(arg);
	break;

    case NOT_LIST:
	ESCFRED;
	printf("Not a list %s ", fun);
	print(arg);
	break;

    case NOT_VAR:
	ESCFRED;
	printf("Not a variable %s ", fun);
	print(arg);
	break;

    case CANT_OPEN:
	ESCFRED;
	if (fileerr_flag == YES) {
	    printf("Can't open file %s ", fun);
	    if (arg != NIL)
		print(arg);
	}
	break;

    case FILE_EXIST:
	ESCFRED;
	if (fileerr_flag == YES) {
	    printf("File not exist %s ", fun);
	    if (arg != NIL)
		print(arg);
	}
	break;

    case STACK_OVERF:
	ESCFRED;
	printf("Stack over flow ");
	break;

    case VARIANT_OVERF:
	ESCFRED;
	printf("Variant over flow ");
	break;

    case SYSTEM_ERROR:
	ESCFRED;
	printf("System error at %s ", fun);
	break;

    case OUT_OF_RANGE:
	ESCFRED;
	printf("Out of range %s ", fun);
	print(arg);
	break;

    case UNDEF_PRED:
	ESCFRED;
	printf("Undefined predicate %s ", fun);
	break;


    case EOF_ERROR:
	ESCFRED;
	printf("End of file error %s ", fun);
	break;

    case INSTANTATION_ERR:
	ESCFRED;
	printf("Instantation error %s ", fun);
	print(arg);
	break;
    case EXPONENT_ERR:
	ESCFRED;
	printf("Exponentiation of a too big integer %s ", fun);
	break;

    case RESOURCE_ERR:
	ESCFRED;
	printf("Resource error %s ", fun);
	break;

    case NOT_CHAR:
	ESCFRED;
	printf("Not character %s ", fun);
	print(arg);
	break;

    case NOT_CALLABLE:
	ESCFRED;
	printf("Not callable %s ", fun);
	print(arg);
	break;
    case EXISTENCE_ERR:
	ESCFRED;
	printf("Existence error %s ", fun);
	print(arg);
	break;
    case ARITY_ERR:
	ESCFRED;
	printf("Arity error %s ", fun);
	print(arg);
	break;
    case NOT_SOURCE:
	ESCFRED;
	printf("Not source-sink %s ", fun);
	print(arg);
	break;
    case NOT_STREAM:
	ESCFRED;
	printf("Not stream or alias %s ", fun);
	print(arg);
	break;
    case NOT_CLOSE_OPTION:
	ESCFRED;
	printf("Not close option %s ", fun);
	print(arg);
	break;
    case NOT_IO_MODE:
	ESCFRED;
	printf("Not I/O mode %s ", fun);
	print(arg);
	break;
    case LESS_THAN_ZERO:
	ESCFRED;
	printf("Less than zero %s ", fun);
	print(arg);
	break;

    case NON_EMPTY_LIST:
	ESCFRED;
	printf("Not empty list %s ", fun);
	print(arg);
	break;

    case NOT_STREAM_OPTION:
	ESCFRED;
	printf("Not stream option %s ", fun);
	print(arg);
	break;

    case OPE_PRIORITY_ERR:
	ESCFRED;
	printf("Operator priority error %s ", fun);
	print(arg);
	break;

    case OPE_SPEC_ERR:
	ESCFRED;
	printf("Operator specifier error %s ", fun);
	print(arg);
	break;

    case NOT_ORDER:
	ESCFRED;
	printf("Not compare order %s ", fun);
	print(arg);
	break;

    case NOT_INPUT_STREAM:
	ESCFRED;
	printf("Not input stream %s ", fun);
	print(arg);
	break;

    case NOT_OUTPUT_STREAM:
	ESCFRED;
	printf("Not output stream %s ", fun);
	print(arg);
	break;

    case PAST_EOF_INPUT:
	ESCFRED;
	printf("Past EOF %s ", fun);
	print(arg);
	break;

    case MODIFY_OPE_ERR:
	ESCFRED;
	printf("Modify operator error %s ", fun);
	print(arg);
	break;

    case EVALUATION_ERR:
	ESCFRED;
	printf("Evaluation error %s ", fun);
	print(arg);
	break;
    case NOT_CHAR_CODE:
	ESCFRED;
	printf("Not charactor code %s ", fun);
	print(arg);
	break;

    case NOT_OPEN_OPTION:
	ESCFRED;
	printf("Not open option %s ", fun);
	print(arg);
	break;

    case NOT_TERM:
	ESCFRED;
	printf("Not term %s ", fun);
	print(arg);
	break;

    case RECORD_OVERF:
	ESCFRED;
	printf("recordh tables max over %s ", fun);
	break;

    case NOT_RECORD:
	ESCFRED;
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

    if (child_flag) {
	memset(bridge, 0, sizeof(bridge));
	bridge[0] = 0x15;
	send_to_parent_buffer();
	child_busy_flag = 0;
    }


    if (init_flag) {
	init_flag = 0;
	longjmp(buf, 2);
    } else if (break_flag) {
	longjmp(buf2, 2);
    } else if (thread_flag && th != 0) {
	longjmp(buf3, 1);
    } else
	longjmp(buf, 1);
}
