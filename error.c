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
    uninstantation_tag =
	list2(makepred("uninstantiation_error"), makevar("%Term"));
    type_tag =
	list3(makepred("error"),
	      list3(makepred("type_error"), makevar("%TypeName"),
		    makevar("%Culprit")), makevar("%Context"));
    domain_tag =
	list3(makepred("error"),
	      list3(makepred("domain_error"), makevar("%Domain"),
		    makevar("%Culprit")), makevar("%Context"));
    exsistence_tag =
	list3(makepred("error"),
	      list3(makepred("existence_error"), makevar("%ObjectType"),
		    makevar("%Culprit")), makevar("%Context"));
    permisson_tag =
	list3(makepred("error"),
	      list4(makepred("permission_error"), makevar("%Operation"),
		    makevar("%ObjectType"), makevar("%Culprit")),
	      makevar("%Context"));
    context_tag =
	list2(makepred("context_error"),
	      list2(makevar("%ContextType"), makevar("%CommandType")));
    syntax_tag =
	list3(makepred("error"),
	      list2(makepred("syntax_error"), makevar("%Message")),
	      makevar("%Context"));
    evaluation_tag =
	list3(makepred("error"),
	      list3(makepred("evaluation_error"), makevar("%ErrorType"),
		    makevar("%Culprit")), makevar("%Context"));
    representation_tag =
	list2(makepred("representation_error"), makevar("%ErrorType"));
    consistency_tag =
	list2(makepred("consistency_error"),
	      list3(makevar("%Culprit1"), makevar("%Culprit2"),
		    makevar("%Message")));
    resource_tag =
	list3(makepred("error"),
	      list2(makepred("resource_error"), makevar("%ResourceType")),
	      makevar("%Context"));
    system_tag =
	list3(makepred("error"),
	      list2(makepred("SYSTEM_ERR"), makevar("%Message")),
	      makevar("%Context"));

}


//------error for compier-----
void errorcomp(int errnum, int name, int arg)
{
    exception(GET_INT(errnum), name, arg, 0);
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
	bindsym(makevar("%Message"), ind, th);
	bindsym(makevar("%Context"), arg, th);
	throw(type_tag, th);
	ESCFRED;
	if (syntax_flag == YES) {
	    printf("Syntax error %s ", GET_NAME(ind));
	    if (arg != NIL)
		print(arg);
	}
	break;

    case BUILTIN_EXIST:
	bindsym(makevar("%Operation"), makeconst("modify"), th);
	bindsym(makevar("%ObjectType"), makeconst("static_procedure"), th);
	bindsym(makevar("%Culprit"), arg, th);
	throw(permisson_tag, th);
	ESCFRED;
	printf("Can't modify builtin ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case ILLEGAL_ARGS:
	bindsym(makevar("%Domain"), makeconst("expected"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Illegal argument ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case DIV_ZERO:
	bindsym(makevar("%ErrorType"), makeconst("evalution_error"), th);
	bindsym(makevar("%Culprit"), makeconst("zero_divisor"), th),
	    bindsym(makevar("%Context"), ind, th);
	throw(evaluation_tag, th);
	ESCFRED;
	printf("Divide by zero ");
	print(ind);
	break;

    case NOT_NUM:
	bindsym(makevar("%TypeName"), makeconst("number"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not a number ");
	print(ind);
	printf(" ");
	print(arg);
	break;


    case NOT_INT:
	bindsym(makevar("%TypeName"), makeconst("integer"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not an integer ");
	print(ind);
	printf(" ");
	print(arg);
	break;


    case NOT_FLT:
	bindsym(makevar("%TypeName"), makeconst("float"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not a float number ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_STR:
	bindsym(makevar("%TypeName"), makeconst("string"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not a string ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_ATOM:
	bindsym(makevar("%TypeName"), makeconst("atom"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not an atom ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_ATOMIC:
	bindsym(makevar("%TypeName"), makeconst("atomic"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not an atomic ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_COMPOUND:
	bindsym(makevar("%TypeName"), makeconst("compound"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not a compound ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_INDICATOR:
	bindsym(makevar("%TypeName"), makeconst("predicate_indicator"),
		th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not predicate indicator ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_LIST:
	bindsym(makevar("%TypeName"), makeconst("list"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not a list ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_VAR:
	bindsym(makevar("%TypeName"), makeconst("variable"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not a variable ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case CANT_OPEN:
	bindsym(makevar("%ObjectType"), makeconst("source_sink"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(exsistence_tag, th);
	ESCFRED;
	if (fileerr_flag == YES) {
	    printf("Can't open file ");
	    print(ind);
	    printf(" ");
	    if (arg != NIL)
		print(arg);
	}
	break;

    case SYSTEM_ERR:
	bindsym(makevar("%Message"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(system_tag, th);
	ESCFRED;
	printf("System error at ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case INSTANTATION_ERR:
	bindsym(makevar("%Context"), ind, th);
	throw(instantation_tag, th);
	ESCFRED;
	printf("Instantation error ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case RESOURCE_ERR:
	bindsym(makevar("%ResourceType"), arg, th);
	throw(resource_tag, th);
	ESCFRED;
	printf("Resource error ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_CALLABLE:
	bindsym(makevar("%TypeName"), makeconst("callable"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(type_tag, th);
	ESCFRED;
	printf("Not callable ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case EXISTENCE_ERR:
	bindsym(makevar("%ObjectType"), makeconst("procedure"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), makestr("top_level"), th);
	throw(exsistence_tag, th);
	ESCFRED;
	printf("Existence error ");
	print(arg);
	break;

    case ARITY_ERR:
	bindsym(makevar("%ObjectType"), makeconst("predicate"), th);
	bindsym(makevar("%Culprit"), ind, th);
	bindsym(makevar("%Context"), ind, th);
	throw(exsistence_tag, th);
	ESCFRED;
	printf("Arity error ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_STREAM:
	bindsym(makevar("%Domain"), makeconst("stream_or_alias"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Not stream or alias ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_SOCKET:
	bindsym(makevar("%Domain"), makeconst("socket"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Not socket ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_FUNCTION:
	bindsym(makevar("%Domain"), makeconst("evaluable"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Not function ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case LESS_THAN_ZERO:
	bindsym(makevar("%Domain"), makeconst("not_less_than_zero"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Less than zero ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NON_EMPTY_LIST:
	bindsym(makevar("%Domain"), makeconst("empty_list"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Not empty list ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case OPE_PRIORITY_ERR:
	bindsym(makevar("%Domain"), makeconst("operator_priority"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Operator priority error ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case MODIFY_OPE_ERR:
	bindsym(makevar("%Domain"), makeconst("operator_specifier"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Modify operator error ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case OPE_SPEC_ERR:
	bindsym(makevar("%Domain"), makeconst("operator_specifier"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Operator specifier error ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case FLOAT_OVERF:
	bindsym(makevar("%ErrorType"), makeconst("float_overflow"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(evaluation_tag, th);
	ESCFRED;
	printf("Float overflow ");
	print(ind);
	printf(" ");
	print(arg);
	break;


    case NOT_RECORD:
	bindsym(makevar("%Domain"), makeconst("record"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("recordh tables has no record ");
	print(ind);
	printf(" ");
	print(arg);
	break;

    case NOT_ORDER:
	bindsym(makevar("%Domain"), makeconst("order"), th);
	bindsym(makevar("%Culprit"), arg, th);
	bindsym(makevar("%Context"), ind, th);
	throw(domain_tag, th);
	ESCFRED;
	printf("Not order ");
	print(ind);
	printf(" ");
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
	printf("send to parent dp_senderr/1\n");
	fflush(stdout);
	int pred;
	pred = list2(makeatom("dp_senderr", SYS), makeint(child_id));
	send_to_parent(pred_to_str(pred));
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
