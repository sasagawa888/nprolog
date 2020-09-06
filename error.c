#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#ifdef __linux
#include <stdio_ext.h>
#endif
#include "npl.h"

//-------error------
void error(int errnum, char *fun, int arg){
	int type,info,i;

    //for setup_call_cleanup
    if(cleanup_dt != NIL){
        if(wide_variable_p(cleanup_dt))
            error(INSTANTATION_ERR,"set_call_cleanup ",cleanup_dt);
        set_length(cleanup_dt);
        push_trail_body1(cleanup_dt);
        cleanup_dt = NIL;
        resolve_all(0,sp,0);
    }

    switch(errnum){
        case SYNTAX_ERR:    type = list2(makeconst("syntax_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = NIL;
                            throw_error(type,info);
        										printf("Syntax error %s ", fun);
														if(!debug_flag && arg > 24)
																print(arg);
                  					if(debug_flag)
                  							printf("errNO=%d\n",arg);
                  					break;

        case BUILTIN_EXIST: if(atomp(arg))
                                arg = list3(makeatom("/",OPE),arg,makeint(0));
                            else
                                arg = list3(makeatom("/",OPE),car(arg),makeint(length(cdr(arg))));
                            type = list4(makeconst("permission_error"),
                                         makeconst("modify"),
                                         makeconst("static_procedure"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Permission error %s ", fun);
                            print(arg);
                            break;

        case ALIAS_EXIST:   type = list4(makeconst("permission_error"),
                                         makeconst("open"),
                                         makeconst("source_link"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Permission error %s ", fun);
                            print(arg);
                            break;

        case STATIC_PROCEDURE:
                            type = list4(makeconst("permission_error"),
                                         makeconst("modify"),
                                         makeconst("static_procedure"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Static procedure %s ", fun);
                            print(arg);
                            break;

        case ILLEGAL_ARGS:  type = list2(makeconst("system_error"),NIL);
        										SET_AUX(type,PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Illegal argument %s ", fun);
                            print(arg);
                            break;

        case CANT_READ:     type = list2(makeconst("syntax_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = NIL;
                            throw_error(type,info);
                            printf("Can't read of %s ", fun);
                            break;

        case NOT_NUM:       type = list3(makeconst("type_error"),
                                         makeconst("number"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not a number %s ", fun);
                            print(arg);
                            break;

        case NOT_COMPUTABLE:
                            type = list2(makeconst("calculation_error"),
                                         makeconst("not_computable"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not computable %s ", fun);
                            print(arg);
                            break;

        case DIV_ZERO:			type = list2(makeconst("evaluation_error"),
                                         makeconst("zero_divisor"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Divide by zero %s ",fun);
        										break;

        case NOT_INT:       type = list3(makeconst("type_error"),
                                         makeconst("integer"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not an integer %s ", fun);
                            print(arg);
                            break;

        case NOT_FLT:       type = list3(makeconst("type_error"),
                                         makeconst("float"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not a float number %s ", fun);
                            print(arg);
                            break;

        case NOT_STR:       type = list3(makeconst("type_error"),
                                         makeconst("string"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not a string %s ", fun);
                            print(arg);
                            break;

        case NOT_ATOM:      type = list3(makeconst("type_error"),
                                         makeconst("atom"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not an atom %s ", fun);
                            print(arg);
                            break;

        case NOT_ATOMIC:    type = list3(makeconst("type_error"),
                                         makeconst("atomic"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not an atomic %s ", fun);
                            print(arg);
                            break;

        case NOT_COMPOUND:  type = list3(makeconst("type_error"),
                                         makeconst("compound"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not a compound %s ", fun);
                            print(arg);
                            break;
        case PRED_INDICATOR:
                            type = list3(makeconst("type_error"),
                                         makeconst("predicate_indicator"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not predicate indicator %s ", fun);
                            print(arg);
                            break;


        case UNCAUGHT_EXCEPTION:
                            type = list2(makeconst("system_error"),arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Uncaught exception %s ", fun);
                            print(arg);
                            if(debug_flag){
                                printf("\n");
                                for(i=0;i<10;i++){
                                    printf("%d ", i);
                                    print(deref(catch_dt[i][0]));
                                    printf("\n");
                                }
                                printf("catch_pt = %d\n", catch_pt);
                            }
                            break;

        case NOT_LIST:			type = list3(makeconst("type_error"),
                                         makeconst("list"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not a list %s ", fun);
                            print(arg);
                            break;

        case NOT_VAR:       type = list2(makeconst("uninstantation_error"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not a variable %s ", fun);
                            print(arg);
                            break;

        case CANT_OPEN:     type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = goal[1];
                            throw_error(type,info);
                            printf("Can't open file %s ", fun);
                            print(arg);
                            break;

        case STACK_OVERF:   type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = NIL;
                            throw_error(type,info);
                            printf("Stack over flow ");
                            break;

        case TRAIL_OVERF:   type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = NIL;
                            throw_error(type,info);
                            printf("Trail over flow ");
                            break;


        case SYSTEM_ERROR:  type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = NIL;
                            throw_error(type,info);
                            printf("System error at %s ", fun);
                            break;

        case TCPIP:         type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("TCP/IP error %s ", fun);
                            print(arg);
                            break;

        case OUT_OF_RANGE:  type = list2(makeconst("domain_error"),
                                         makeconst("out_of_range"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Out of range %s ", fun);
                            print(arg);
                            break;

        case UNDEF_PRED:	type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Undefined predicate %s ", fun);
        										print_goal();
                            break;

        case DISCONTIGUOUS:	type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Discontiguous assertion ");
        										print(arg);
                            break;

        case NOT_EXIST_MODULE:
                        		type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not exist module %s ", fun);
        										print_goal();
                            break;

        case EOF_ERROR:     type = list2(makeconst("system_error"),NIL);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("End of file error %s ", fun);
        										print_goal();
                            break;

        case INSTANTATION_ERR:
                            type = list2(makeconst("instantation_error"),arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Instantation error %s ", fun);
        										print(arg);
                            break;
        case EXPONENT_ERR:
                            type = list2(makeconst("resource_error"),
                                         makeconst("exponentiation"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Exponentiation of a too big integer %s ", fun);
        										print_goal();
                            break;

        case RESOURCE_ERR:
                            type = list2(makeconst("resource_error"),
                                         makeconst("length"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Resource error ");
        										print_goal();
                            break;

        case NOT_CHAR:      type = list3(makeconst("type_error"),
                                         makeconst("character"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not character %s ", fun);
        										print(arg);
                            break;

        case NOT_CALLABLE:  type = list3(makeconst("type_error"),
                                         makeconst("callable"),
                                         arg);
					        					SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not callable %s ", fun);
        										print(arg);
                            break;
        case EXISTENCE_ERR: type = list3(makeconst("existence_error"),
                                         makeconst("source_sink"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Existence error %s ", fun);
                            print(arg);
                            break;
        case NOT_SOURCE:    type = list3(makeconst("domain_error"),
                                         makeconst("source_sink"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not source-sink %s ", fun);
                            print(arg);
                            break;
        case NOT_STREAM:    type = list3(makeconst("domain_error"),
                                         makeconst("stream_or_alias"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not stream or alias %s ", fun);
                            print(arg);
                            break;
        case NOT_CLOSE_OPTION:
                            type = list3(makeconst("domain_error"),
                                         makeconst("close_option"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not close option %s ", fun);
                            print(arg);
                            break;
        case NOT_IO_MODE:   type = list3(makeconst("domain_error"),
                                         makeconst("io_mode"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not I/O mode %s ", fun);
                            print(arg);
                            break;
        case NOT_LESS_THAN_ZERO:
                            type = list3(makeconst("domain_error"),
                                         makeconst("not_less_than_zero"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not less than zero %s ", fun);
                            print(arg);
                            break;

        case NON_EMPTY_LIST:
                            type = list3(makeconst("domain_error"),
                                         makeconst("not_empty_list"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not empty list %s ", fun);
                            print(arg);
                            break;

        case NOT_STREAM_OPTION:
                            type = list3(makeconst("domain_error"),
                                         makeconst("stream_option"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not stream option %s ", fun);
                            print(arg);
                            break;

        case OPE_PRIORITY_ERR:
                            type = list4(makeconst("domain_error"),
                                         makeconst("operator_priority"),
                                         makeconst("priority"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Operator priority error %s ", fun);
                            print(arg);
                            break;

        case OPE_SPEC_ERR:
                            type = list3(makeconst("domain_error"),
                                         makeconst("operator_specifier"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Operator specifier error %s ", fun);
                            print(arg);
                            break;

        case NOT_WRITE_OPTION:
                            type = list3(makeconst("domain_error"),
                                         makeconst("write_option"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not write option %s ", fun);
                            print(arg);
                            break;

        case NOT_READ_OPTION:
                            type = list3(makeconst("domain_error"),
                                         makeconst("read_option"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not read option %s ", fun);
                            print(arg);
                            break;

        case NOT_ORDER:     type = list3(makeconst("domain_error"),
                                         makeconst("order"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not compare order %s ", fun);
                            print(arg);
                            break;

        case NOT_INPUT_STREAM:
                            type = list4(makeconst("permission_error"),
                                         makeconst("input"),
                                         makeconst("stream"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not input stream %s ", fun);
                            print(arg);
                            break;

        case NOT_OUTPUT_STREAM:
                            type = list4(makeconst("permission_error"),
                                         makeconst("output"),
                                         makeconst("stream"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not output stream %s ", fun);
                            print(arg);
                            break;

        case PAST_EOF_INPUT:
                            type = list4(makeconst("permission_error"),
                                         makeconst("input"),
                                         makeconst("past_end_of_stream"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Past EOF %s ", fun);
                            print(arg);
                            break;

        case MODIFY_OPE_ERR:
                            type = list4(makeconst("permission_error"),
                                         makeconst("modify"),
                                         makeconst("operator"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Modify operator error %s ", fun);
                            print(arg);
                            break;

        case EVALUATION_ERR:
                            type = list2(makeconst("evaluation_error"),
                                         makeconst("undefined"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Evaluation error %s ", fun);
                            print(arg);
                            break;
        case NOT_CHAR_CODE:
                            type = list2(makeconst("representation_error"),
                                         makeconst("character_code"));
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not charactor code %s ", fun);
                            print(arg);
                            break;

        case NOT_FLAG_SPEC:
                            type = list3(makeconst("domain_error"),
                                         makeconst("flag"),
                                         arg);
        										SET_AUX(car(type),PRED);
                            info = list3(makeatom("/",OPE),goal[1],makeint(goal[0]-1));
                            throw_error(type,info);
                            printf("Not flag specifier %s ", fun);
                            print(arg);
                            break;
  }
    printf("\n");
    stok.ch = NUL;
    stok.flag = GO;
		stok.type = NUL;
		stok.ahead = NUL;
    memset(stok.buf,NUL,BUFSIZE);
    #if _WIN32
    fflush(stdin);
    #elif __linux
    __fpurge(stdin);
    #endif
    if(open_flag){
        open_flag = 0;
        printf("around here line=%d column=%d\n", line, column);
        fflush(stdout);
        fclose(GET_PORT(input_stream));
    }
    longjmp(buf,1);
}

void throw_error(int type, int info){
	int i,error_tag,tag;

    error_tag = list3(makeconst("error"),type,info);
	for(i=catch_pt;i>0;i--){
    	tag = catch_dt[i][0];
    	tp = catch_dt[i][2];
    	sp = catch_dt[i][3];
    	if(unify(error_tag,tag) == YES)
    		longjmp(catch_buf[i],1);
    }
    return;
}
