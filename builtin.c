#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "npl.h"

void initbuiltin(void){
    definfix(">",b_greater,700,XFX);
    definfix("<",b_smaller,700,XFX);
    definfix("=<",b_eqsmaller,700,XFX);
    definfix(">=",b_eqgreater,700,XFX);
    definfix("=:=",b_numeq,700,XFX);
    definfix("=\\=",b_notnumeq,700,XFX);
    definfix("=/=",b_notnumeq,700,XFX);
    definfix("@<",b_atsmaller,700,XFX);
    definfix("@=<",b_ateqsmaller,700,XFX);
    definfix("@>",b_atgreater,700,XFX);
    definfix("@>=",b_ateqgreater,700,XFX);
    definfix("is",b_is,700,XFX);
    definfix("=",b_unify,700,XFX);
    definfix("==",b_equalp,700,XFX);
    definfix("\\==",b_notequalp,700,XFX);
    definfix("\\=",b_notunify,700,XFX);
    definfix("=..",b_univ,700,XFX);
    definfix("@",o_ignore,100,XFX);
    definfix(":",b_colon,50,XFX);
    definfix("->",b_ifthen,1050,XFY);
    definfix("\\+",b_not,900,FY);

    defbuiltin("!",b_cut);
    defbuiltin("%ask",b_ask);
    defbuiltin("abolish",b_abolish);
    defbuiltin("abort",b_abort);
    defbuiltin("ansi_cup",b_ansi_cup);
    defbuiltin("ansi_cuu",b_ansi_cuu);
    defbuiltin("ansi_cud",b_ansi_cud);
    defbuiltin("ansi_cuf",b_ansi_cuf);
    defbuiltin("ansi_cub",b_ansi_cub);
    defbuiltin("ansi_sgr",b_ansi_sgr);
    defbuiltin("ansi_cpr",b_ansi_cpr);
    defbuiltin("ansi_scp",b_ansi_scp);
    defbuiltin("ansi_rcp",b_ansi_rcp);
    defbuiltin("ansi_ed",b_ansi_ed);
    defbuiltin("ansi_el",b_ansi_el);
    defbuiltin("arg",b_arg);
    defbuiltin("arg0",b_arg0);
    defbuiltin("assert",b_assert);
    defbuiltin("asserta",b_asserta);
    defbuiltin("assertz",b_assert);
    defbuiltin("atom_concat",b_atom_concat);
    defbuiltin("atom",b_atom);
    defbuiltin("atom_string",b_atom_string);
    defbuiltin("atomic",b_atomic);
    defbuiltin("break",b_break);
    defbuiltin("char_code",b_char_code);
    defbuiltin("chdir",b_chdir);
    defbuiltin("close",b_close);
    defbuiltin("compare",b_compare);
    defbuiltin("compound",b_compound);
    defbuiltin("concat",b_concat);
    defbuiltin("consult",b_consult);
    defbuiltin("create",b_create);
    defbuiltin("ctr_set",b_ctr_set);
    defbuiltin("ctr_dec",b_ctr_dec);
    defbuiltin("ctr_inc",b_ctr_inc);
    defbuiltin("ctr_is",b_ctr_is);
    defbuiltin("date",b_date);
    defbuiltin("date_day",b_date_day);
    defbuiltin("dec",b_dec);
    defbuiltin("delete",b_delete);
    defbuiltin("display",b_write_canonical);
    defbuiltin("debug",b_debug);
    defbuiltin("dup",b_dup);
    defbuiltin("edit",b_edit);
    defbuiltin("eq",b_eq);
    defbuiltin("errorcode",b_errorcode);
    defbuiltin("fail",b_fail);
    defbuiltin("flush",b_flush_output);
    defbuiltin("float",b_real);
    defbuiltin("float_text",b_float_text);
    defbuiltin("functor",b_functor);
    defbuiltin("gc",b_gbc);
    defbuiltin("get",b_get);
    defbuiltin("get0",b_get0);
    defbuiltin("get0_noecho",b_get0_noecho);
    defbuiltin("get_code",b_get_code);
    defbuiltin("get_byte",b_get_byte);
    defbuiltin("ground",b_ground);
    defbuiltin("halt",b_halt);
    defbuiltin("heapd",b_heapdump);
    defbuiltin("ifthen",b_ifthen);
    defbuiltin("ifthenelse",b_ifthenelse);
    defbuiltin("inc",b_inc);
    defbuiltin("instance",b_instance);
    defbuiltin("integer",b_integer);
    defbuiltin("int_text",b_int_text);
    defbuiltin("keysort",b_keysort);
    defbuiltin("leash",b_leash);
    defbuiltin("length",b_length);
    defbuiltin("listing",b_listing);
    defbuiltin("list",b_list);
    defbuiltin("list_text",b_list_text);
    defbuiltin("mkdir",b_mkdir);
    defbuiltin("measure",b_measure);
    defbuiltin("name",b_name);
    defbuiltin("nl",b_nl);
    defbuiltin("not",b_not);
    defbuiltin("nonvar",b_nonvar);
    defbuiltin("nospy",b_nospy);
    defbuiltin("notrace",b_notrace);
    defbuiltin("number",b_number);
    defbuiltin("op",b_op);
    defbuiltin("open",b_open);
    defbuiltin("predicate_property",b_predicate_property);
    defbuiltin("put",b_put);
    defbuiltin("reconsult",b_reconsult);
    defbuiltin("read",b_read);
    defbuiltin("read_line",b_read_line);
    defbuiltin("real",b_real);
    defbuiltin("recorda",b_recorda);
    defbuiltin("recordz",b_recordz);
    defbuiltin("recordh",b_recordh);
    defbuiltin("ref",b_ref);
    defbuiltin("removeallh",b_removeallh);
    defbuiltin("rename",b_rename);
    defbuiltin("reset_op",b_reset_op);
    defbuiltin("reverse",b_reverse);
    defbuiltin("rmdir",b_rmdir);
    defbuiltin("see",b_see);
    defbuiltin("seeing",b_seeing);
    defbuiltin("seen",b_seen);
    defbuiltin("shell",b_shell);
    defbuiltin("skip",b_skip);
    defbuiltin("sort",b_sort);
    defbuiltin("stdin",b_stdin);
    defbuiltin("stdinout",b_stdinout);
    defbuiltin("stdout",b_stdout);
    defbuiltin("string",b_string);
    defbuiltin("string_length",b_string_length);
    defbuiltin("string_term",b_string_term);
    defbuiltin("spy",b_spy);
    defbuiltin("substring",b_substring);
    defbuiltin("syntaxerrors",b_syntaxerrors);
    defbuiltin("system",b_system);
    defbuiltin("tab",b_tab);
    defbuiltin("tell",b_tell);
    defbuiltin("telling",b_telling);
    defbuiltin("time",b_time);
    defbuiltin("told",b_told);
    defbuiltin("trace",b_trace);
    defbuiltin("true",b_true);
    defbuiltin("var",b_var);
    defbuiltin("write",b_write);
    defbuiltin("writeq",b_writeq);
    
    defcompiled("call",b_call);
    defcompiled("repeat",b_repeat);
    defcompiled("append",b_append);
    defcompiled("member",b_member);
    defcompiled("retract",b_retract);
    defcompiled("clause",b_clause);
    defcompiled("current_predicate",b_current_predicate);
    defcompiled("current_op",b_current_op);
    defcompiled("between",b_between);
    defcompiled("retrieveh",b_retrieveh);
    defcompiled("removeh",b_removeh);
    defcompiled("directory",b_directory);

    //-----JUMP project---------
    defcompiled("n_reconsult_predicate",b_reconsult_predicate);
    defbuiltin("n_filename",b_filename);
    defbuiltin("n_atom_convert",b_atom_convert);
    defbuiltin("n_arity_count",b_arity_count);
    defbuiltin("n_compiler_anoymous",b_compiler_anoymous);
    defbuiltin("n_compiler_variable",b_compiler_variable);
    defbuiltin("n_variable_convert",b_variable_convert);
    defbuiltin("n_generate_all_variable",b_generate_all_variable);
    defbuiltin("n_generate_variable",b_generate_variable);
    defbuiltin("n_clause_with_arity",b_clause_with_arity);
    defbuiltin("n_property",b_property);
    defbuiltin("n_bignum",b_bignum);
    defbuiltin("n_longnum",b_longnum);
    defbuiltin("n_argument_list",b_argument_list);
    defbuiltin("n_findatom",b_findatom);
    defbuiltin("n_defined_predicate",b_defined_predicate);
    defbuiltin("n_defined_userop",b_defined_userop);
    defbuiltin("n_get_execute",b_get_execute);
    defbuiltin("n_strict",b_strict);

     #ifdef __arm__
    defbuiltin("wiringpi_setup_gpio",b_wiringpi_setup_gpio);
    defbuiltin("wiringpi_spi_setup_ch_speed",b_wiringpi_spi_setup_ch_speed);
    defbuiltin("pwm_set_mode",b_pwm_set_mode);
    defbuiltin("pwm_set_range",b_pwm_set_range);
    defbuiltin("pwm_set_clock",b_pwm_set_clock);
    defbuiltin("pin_mode",b_pin_mode);
    defbuiltin("digital_write",b_digital_write);
    defbuiltin("digital_write_byte",b_digital_write_byte);
    defbuiltin("pull_up_dn_control",b_pull_up_dn_control);
    defbuiltin("digital_read",b_digital_read);
    defbuiltin("delay",b_delay);
    defbuiltin("delay_microseconds",b_delay_microseconds);
    defbuiltin("out",b_digital_write);
    defbuiltin("in",b_digital_read);
    defbuiltin("timer_microseconds",b_timer_microseconds);
    #endif
    return;
}

int b_length(int arglist, int rest){
    int n,arg1,arg2,i,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(integerp(eval(arg2)) && GET_INT(eval(arg2)) < 0)
            error(NOT_LESS_THAN_ZERO,"length ",arg2);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"length ",arg2);

        if(listp(arg1))
            return(unify(arg2,makeint(length(arg1))));
        else if(integerp(arg2)){
            i = GET_INT(arg2);
            res = NIL;
            while(i > 0){
                res = wlistcons(makeatom("_",ANOY),res);
                i--;
            }
            return(unify(arg1,res));
        }
        return(NO);
    }
    return(NO);
}


//compiled predicate
int b_repeat(int arglist, int rest){
    int n,save1,save2,save3;

    save1 = wp;
    save2 = sp;
    save3 = ac;
    n = length(arglist);
    if(n == 0){
        loop:
        if(prove_all(rest,sp,0) == YES){
            return(YES);
        }
    wp = save1;
    unbind(save2);
    ac = save3;
    goto loop;
    }
    return(NO);
}


int b_op(int arglist, int rest){
    int n,arg1,arg2,arg3,weight,type;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);   //priority
        arg2 = cadr(arglist);  //specifier
        arg3 = caddr(arglist); //operator

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"op ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"op ",arg2);
        if(listp(arg3) && length(arg3) == -1)
            error(INSTANTATION_ERR,"op ",arg3);
        if(!integerp(arg1))
            error(NOT_INT,"op ",arg1);
        if(!atomp(arg2))
            error(NOT_ATOM,"op ",arg2);
        if(!atomp(arg3) && !listp(arg3))
            error(NOT_ATOM,"op ",arg3);
        weight = GET_INT(arg1);
        if(!(weight >= 0 && weight <= 1200))
            error(OPE_PRIORITY_ERR,"op ",arg1);
        if(arg3 == DOTOBJ)
            error(MODIFY_OPE_ERR,"op ",arg3);
        if(arg3 == AND)
            error(MODIFY_OPE_ERR,"op ",arg3);
        if(arg3 == makeatom("op",OPE))
            error(MODIFY_OPE_ERR,"op ",arg3);

        type = NIL;
        if(arg2 == makeconst("xfx")){
            type = XFX;

        }
        else if(arg2 == makeconst("yfx")){
            if(GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
                error(OPE_SPEC_ERR,"op",arg2);
            type = YFX;
        }
        else if(arg2 == makeconst("xfy")){
            if(GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
                error(OPE_SPEC_ERR,"op",arg2);
            type = XFY;
        }
        else if(arg2 == makeconst("fx"))
            type = FX;
        else if(arg2 == makeconst("fy"))
            type = FY;
        else if(arg2 == makeconst("xf")){
            if(GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
               GET_OPT(arg3) == XFY)
                error(OPE_SPEC_ERR,"op",arg2);
            type = XF;
        }
        else if(arg2 == makeconst("yf")){
            if(GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
               GET_OPT(arg3) == XFY)
                error(OPE_SPEC_ERR,"op",arg2);
            type = YF;
        }
        else
            error(OPE_SPEC_ERR,"op",arg2);

        if(singlep(arg3)){
            if(operatorp(arg3))
                defoperator(GET_NAME(arg3),NIL,weight,type,0);
            else if(builtinp(arg3))
                defoperator(GET_NAME(arg3),NIL,weight,type,1);
            else
                defoperator(GET_NAME(arg3),NIL,weight,type,2);
        }
        else{
            while(!nullp(arg3)){
                if(wide_variable_p(car(arg3)))
                    error(INSTANTATION_ERR,"ope ",car(arg3));
                else if(!atomp(car(arg3)))
                    error(NOT_ATOM,"ope ",car(arg3));
                else if(operatorp(car(arg3)))
                    defoperator(GET_NAME(arg3),NIL,weight,type,0);
                else
                    defoperator(GET_NAME(car(arg3)),NIL,weight,type,1);

                arg3 = cdr(arg3);
            }
        }
        return(YES);
    }
    return(NO);
}


int o_cons(int x, int y){
    if(operationp(y))
        y = operate(y);
    return(cons(x,y));
}

int b_ask(int arglist, int rest){
    int n,x1,x2;
    char c;

    n = length(arglist);
    if(n == 0){
        x1 = variables;
        if(nullp(x1) || has_no_value_p(x1)){
            return(YES);
        }
        // ignore singleton e.g. X=X
        x2 = NIL;
        while(!nullp(x1)){
            if(variablep(car(x1)) && deref(car(x1)) != car(x1))
                x2 = cons(car(x1),x2);
            x1 = cdr(x1);
        }
        x2 = reverse(x2);
        while(!nullp(x2)){
            print(car(x2));
            printf(" = ");
            printanswer(deref(car(x2)));
            if(!nullp(cdr(x2)))
                printf("\n");
            x2 = cdr(x2);
        }

        putchar(' ');

        fflush(stdout);
        fflush(stdin);

        loop:	
        c = getch();
        
        if(c == '.' || c == EOL){
            fputs(".\n", stdout);           	
            return(YES);
        }
        else if(c == ';' || c == ' '){
            fputs(";\n", stdout);	    
            return(NO);
        }
        else
            goto loop;
    }
    return(NO);
}


int b_unify(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(operationp(arg1) && car(arg1) == DOTOBJ)
            arg1 = operate(arg1);
        if(operationp(arg2) && car(arg2) == DOTOBJ)
            arg2 = operate(arg2);
        res = unify(arg1,arg2);
        return(res);
    }
    return(NO);
}

int b_notunify(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(operationp(arg1))
            arg1 = operate(arg1);
        if(operationp(arg2))
            arg2 = operate(arg2);
        res = unify(arg1,arg2);
        if(res == NO)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}




//input and output
int b_write(int arglist, int rest){
    int n,arg1,arg2,save;

    n = length(arglist);
    if(n == 1){
        arg1 = output_stream;
        arg2 = car(arglist);
        goto write;

    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        write:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"write ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"write ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 0;
        print(arg2);
        fflush(GET_PORT(output_stream));
        quoted_flag = 1;
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_write_canonical(int arglist, int rest){
    int n,arg1,arg2,save;

    n = length(arglist);
    if(n == 1){
        arg1 = output_stream;
        arg2 = car(arglist);
        goto write_canonical;

    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        write_canonical:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"write_canonical ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"write_canonical ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 1;
        ignore_flag = 1;
        print(arg2);
        quoted_flag = 0;
        ignore_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_writeq(int arglist, int rest){
    int n,arg1,arg2,save;

    n = length(arglist);
    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(car(arglist));
        goto writeq;

    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        writeq:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"writeq ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"writeq ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 1;
        print(arg2);
        quoted_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}


int b_nl(int arglist, int rest){
    int n,arg1,save;

    n = length(arglist);
    if(n == 0){
        fprintf(GET_PORT(output_stream),"\n");
        fflush(GET_PORT(output_stream));
        return(YES);
    }
    else if(n == 1){
        arg1 = car(arglist);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        fprintf(GET_PORT(output_stream),"\n");
        fflush(GET_PORT(output_stream));
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_put(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(!integerp(arg1))
            error(NOT_INT,"put",arg1);
        fprintf(GET_PORT(output_stream), "%c", (char)GET_INT(arg1));
        return(YES);
    }
    return(NO);
}

int b_get0(int arglist, int rest){
    int n,c,arg1,i,res;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        c = getc(GET_PORT(input_stream));
        if(c == EOL){
            c = getc(GET_PORT(input_stream));
        }
        i = makeint((int)c);
        res = unify(arg1,i);
        return(res);
    }
    return(NO);
}

int b_get(int arglist, int rest){
    int n,c,arg1,i,res;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        loop:
        c = getc(GET_PORT(input_stream));
        if(c == EOL)
            c = getc(GET_PORT(input_stream));
        i = (int)c;
        if(c == EOL)
            goto exit;
        if(i < 32)
            goto loop;

        exit:
        res = unify(arg1,makeint(i));
        return(res);
    }
    return(NO);
}


int b_get0_noecho(int arglist, int rest){
    int n,c,arg1,i,res;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        c = getchar();
        i = makeint((int)c);
        res = unify(arg1,i);
        return(res);
    }
    return(NO);
}




int b_get_code(int arglist, int rest){
    int n,arg1,arg2,c,i,res;
    char str[10];

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = car(arglist);
        goto get_code;
    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        get_code:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_code ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"get_code ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_code ",arg1);

        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        c = getc(GET_PORT(arg1));

        if(mode_flag == 0 && iskanji(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = NUL;
            i = sjis_to_code(str);
        }
        else if(mode_flag == 1 && isUni2(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni3(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni4(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = getc(GET_PORT(arg1));
            str[4] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni5(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = getc(GET_PORT(arg1));
            str[4] = getc(GET_PORT(arg1));
            str[5] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni6(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = getc(GET_PORT(arg1));
            str[4] = getc(GET_PORT(arg1));
            str[5] = getc(GET_PORT(arg1));
            str[6] = NUL;
            i = utf8_to_ucs4(str);
        }
        else{
            i = c;
        }

        res = NIL;
        
        res = unify(arg2,makeint(i));
        return(res);
    }
    return(NO);
}

int b_get_byte(int arglist, int rest){
    int n,arg1,arg2,c,res;

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = car(arglist);
        goto get_byte;
    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        get_byte:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_byte ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"get_byte ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_byte ",arg1);

        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        c = fgetc(GET_PORT(arg1));

        res = unify(arg2,makeint(c));
        return(res);
    }
    return(NO);
}


int b_tab(int arglist, int rest){
    int n,arg1,count;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(integerp(eval(arg1)) && GET_INT(eval(arg1)) < 0)
            error(NOT_LESS_THAN_ZERO,"tab",arg1);
        if(!integerp(arg1))
            error(NOT_INT,"tab",arg1);

        count = GET_INT(arg1);
        while(count > 0){
            fprintf(GET_PORT(output_stream)," ");
            count--;
        }
        return(YES);
    }
    return(NO);
}


//option for read_term [variable_names(X)]
int variable_name_p(int x){

    if(eqlp(car(x),makeconst("variable_names")) &&
       (wide_variable_p(cadr(x)) || listp(cadr(x))) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}

//option for read_term [singletons(X)]
int singletonp(int x){

    if(eqlp(car(x),makeconst("singletons")) &&
       wide_variable_p(cadr(x)) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}



int b_read(int arglist, int rest){
    int n,arg1,arg2,save1,save2,temp,res;

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = car(arglist);
        goto read;

    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        read:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"read ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"read",arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"read ", arg1);
        
        save1 = input_stream;
        save2 = repl_flag;   
        input_stream = arg1;
        repl_flag = 0;
        
        temp = variable_to_call(readparse());
        res = unify(arg2,temp);
        input_stream = save1;
        repl_flag = save2;
        return(res);
    }
    return(NO);
}

int b_read_line(int arglist, int rest){
    int n,arg1,arg2,save1,save2,res,pos;
    char str[STRSIZE],c;

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = car(arglist);
        goto read_line;
    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        read_line:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"read_line ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"read_line ",arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"read_line ", arg1);
        
        save1 = input_stream;
        save2 = repl_flag;   
        input_stream = arg1;
        repl_flag = 0;

        c = readc();
        pos = 0;
        while(c != EOL && c != EOF){
            str[pos] = c;
            pos++;
            c = readc();
        }
        str[pos] = NUL;
        res = unify(arg2,makeconst(str));
        input_stream = save1;
        repl_flag = save2;
        return(res);
    }
    return(NO);
}


int b_skip(int arglist, int rest){
    int n,arg1,arg2,save;
    char c,str[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = standard_input;
        arg2 = car(arglist);
        goto skip;
    }
    else if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        skip:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"skip ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"skip",arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"skip ", arg1);
        
        save = input_stream;   
        input_stream = arg1;

        do{
            c = readc();
            str[0] = c;
            str[1] = 0;
        }while(strcmp(str,GET_NAME(arg2)) != 0 && c != EOF);

        input_stream = save;
        return(YES);
    }
    return(NO);
}


int b_stdin(int arglist, int rest){
    int n,arg1,arg2,save1,save2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!streamp(arg1))
            error(NOT_STREAM,"stdin ",arg1);
        if(!callablep(arg2))
            error(NOT_CALLABLE,"stdin ",arg2);
        
        save1 = input_stream;
        save2 = sp;
        if(prove_all(arg2,sp,0) == YES){
            input_stream = save1;
            return(YES);
        }
        unbind(save2);
        input_stream = save1; 
        return(NO);
    }
    return(NO);
}

int b_stdout(int arglist, int rest){
    int n,arg1,arg2,save1,save2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!streamp(arg1))
            error(NOT_STREAM,"stdout ",arg1);
        if(!callablep(arg2))
            error(NOT_CALLABLE,"stdout ",arg2);
        
        save1 = output_stream;
        save2 = sp;
        if(prove_all(arg2,sp,0) == YES){
            output_stream = save1;
            return(YES);
        }
        unbind(save2);
        output_stream = save1; 
        return(NO);
    }
    return(NO);
}

int b_stdinout(int arglist, int rest){
    int n,arg1,arg2,arg3,save1,save2,save3;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        if(!streamp(arg1))
            error(NOT_STREAM,"stdinout ",arg1);
        if(!streamp(arg1))
            error(NOT_STREAM,"stdinout ",arg2);
        if(!callablep(arg3))
            error(NOT_CALLABLE,"stdinout ",arg3);
        
        save1 = input_stream;
        save2 = output_stream;
        save3 = sp;
        if(prove_all(arg3,sp,0) == YES){
            input_stream = save1;
            output_stream = save2;
            return(YES);
        }
        unbind(save3);
        input_stream = save1;
        output_stream = save2; 
        return(NO);
    }
    return(NO);
}


int b_create(int arglist, int rest){
    int n,arg1,arg2,stream;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"create ",arg2);
        if(!atomp(arg2))
            error(NOT_ATOM,"create ",arg2);

        if(eqp(arg1,makeconst("user"))){
            output_stream = standard_output;
            return(YES);
        }
        else{
            stream = makestream(fopen(GET_NAME(arg2),"w"),OPL_OUTPUT,OPL_TEXT,NIL,arg2);
            
            if(GET_PORT(stream) == NULL)
                error(CANT_OPEN, "create ", arg2);
            unify(arg1,stream);
            return(YES);
        }
    }
    return(NO);
}




int b_open(int arglist, int rest){
    int n,arg1,arg2,arg3,stream;
    FILE* fp;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"open ",arg2);
        if(!atomp(arg2))
            error(NOT_ATOM,"open ",arg2);

        if(eqp(arg1,makeconst("user"))){
            output_stream = standard_output;
            return(YES);
        }
        else{
            fp = fopen(GET_NAME(arg2),"r");
            if(fp == NULL){
                fclose(fp);
                error(FILE_EXIST,"open ",arg2);
            }

            if(arg3 == makeconst("w")){
                stream = makestream(fopen(GET_NAME(arg2),"w"),OPL_OUTPUT,OPL_TEXT,NIL,arg2);
            
                if(GET_PORT(stream) == NULL)
                    error(CANT_OPEN, "open ", arg2);
                unify(arg1,stream);
                return(YES);
            }
            else if(arg3 == makeconst("r")){
                stream = makestream(fopen(GET_NAME(arg2),"r"),OPL_INPUT,OPL_TEXT,NIL,arg2);
            
                if(GET_PORT(stream) == NULL)
                    error(CANT_OPEN, "open ", arg2);
                unify(arg1,stream);
                return(YES);
            }
            else if(arg3 == makeconst("rw")){
                stream = makestream(fopen(GET_NAME(arg2),"r+"),OPL_INPUT,OPL_TEXT,NIL,arg2);
            
                if(GET_PORT(stream) == NULL)
                    error(CANT_OPEN, "open ", arg2);
                unify(arg1,stream);
                return(YES);
            }
            else if(arg3 == makeconst("a") || arg3 == makeconst("ra")){
                stream = makestream(fopen(GET_NAME(arg2),"a+"),OPL_INPUT,OPL_TEXT,NIL,arg2);
            
                if(GET_PORT(stream) == NULL)
                    error(CANT_OPEN, "open ", arg2);
                unify(arg1,stream);
                return(YES);
            }
            error(NOT_OPEN_OPTION,"open ", arg3);
        }
    }
    return(NO);
}

int b_dup(int arglist, int rest){
    int n,arg1,arg2,addr;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!streamp(arg1))
            error(NOT_STREAM,"dup ", arg1);
        
        addr = freshcell();
        SET_TAG(addr,STREAM);
        SET_PORT(addr,GET_PORT(arg1));
        SET_CDR(addr,GET_CDR(arg1));
        SET_OPT(addr,GET_OPT(arg1)); //input/output/inout
        SET_VAR(addr,GET_VAR(arg1)); //text/binary
        SET_AUX(addr,GET_AUX(arg1)); //for eof_action
        return(unify(arg2,addr));
    }
    return(NO);
}


int b_close(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        fclose(GET_PORT(arg1));
        return(YES);
    }
    return(NO);
}


int b_see(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"see ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"see ",arg1);

        if(eqp(arg1,makeconst("user"))){
            input_stream = standard_input;
            return(YES);
        }
        else{
            input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

            if(GET_PORT(input_stream) == NULL)
                error(CANT_OPEN, "see", arg1);
            return(YES);
        }
    }
    return(NO);
}

int b_seeing(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        return(unify(arg1,GET_CDR(input_stream)));
    }
    return(NO);
}


int b_seen(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        if(input_stream != standard_input){
            fclose(GET_PORT(input_stream));
            input_stream = standard_input;
        }
        return(YES);
    }
    return(NO);
}

int b_tell(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"tell ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"tell ",arg1);

        if(eqp(arg1,makeconst("user"))){
            output_stream = standard_output;
            return(YES);
        }
        else{
            output_stream = makestream(fopen(GET_NAME(arg1),"w"),OPL_OUTPUT,OPL_TEXT,NIL,arg1);
            
            if(GET_PORT(input_stream) == NULL)
                error(CANT_OPEN, "tell", arg1);
            return(YES);
        }
    }
    return(NO);
}

int b_telling(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        return(unify(arg1,GET_CDR(output_stream)));
    }
    return(NO);
}

int b_told(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        if(output_stream != standard_output){
            fclose(GET_PORT(output_stream));
            output_stream = standard_output;
        }
        return(YES);
    }
    return(NO);
}


int b_flush_output(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 0){
        fflush(stdout);
        return(YES);
    }
    else if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"flush_output ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"flush_output ",arg1);
        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        if(GET_OPT(arg1) == OPL_INPUT)
            error(NOT_OUTPUT_STREAM,"flush_output ",arg1);

        fflush(GET_PORT(arg1));
        return(YES);
    }
    return(NO);
}


int b_consult(int arglist, int rest){
    int n,arg1,clause,save;
    char str[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"consult ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM, "consult ",arg1);

        save = input_stream;
        input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

        if(GET_PORT(input_stream) == NULL)
            error(CANT_OPEN, "consult", arg1);

        //object file ex "foo.o"
        n = strlen(GET_NAME(arg1));
        strcpy(str,GET_NAME(arg1));
        if(str[n-1] == 'o' && str[n-2] == '.'){
            dynamic_link(arg1);
            input_stream = save;
            goto exit;
        }

        open_flag = 1;
        line = 1;
        column = 0;
        reconsult_list = NIL;
        execute_list = NIL;
        while(1){
            skip:
            clause = parser(NIL,NIL,NIL,NIL,0,0);
            if(clause == FEND)
                break;

            //e.g. :- op(...)
            if(operationp(clause) && car(clause) == DEFINE && length(clause) == 2){
                clause = cadr(clause);
                prove_all(clause,sp,0);
                goto skip;
            }
            // DCG syntax e.g. a-->b.
            if(dcgp(clause)){
                operate(clause);
                goto skip;
            }

            //assert
            b_assert(list1(clause),NIL);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;

        exit:
        return(YES);
    }
    return(NO);
}


int b_reconsult(int arglist, int rest){
    int n,arg1,clause,head,atom,save;
    char str[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"reconsult ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM, "reconsult ", arg1);

        save = input_stream;
        input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

        if(GET_PORT(input_stream) == NULL)
            error(CANT_OPEN, "reconsult", arg1);

        //object file ex "foo.o"
        n = strlen(GET_NAME(arg1));
        strcpy(str,GET_NAME(arg1));
        if(str[n-1] == 'o' && str[n-2] == '.'){
            dynamic_link(arg1);
            input_stream = save;
            goto exit;
        }

        open_flag = 1;
        line = 1;
        column = 0;
        reconsult_list = NIL;
        execute_list = NIL;
        while(1){
            skip:
            clause = parser(NIL,NIL,NIL,NIL,0,0);
            if(clause == FEND)
                break;
            
            //e.g. :- op(...)
            if(operationp(clause) && car(clause) == DEFINE && length(clause) == 2){
                clause = cadr(clause);
                prove_all(clause,sp,0);
                while(structurep(clause) && car(clause) == AND){
                    execute_list = cons(cadr(clause),execute_list);
                    clause = caddr(clause);
                }
                execute_list = cons(clause,execute_list);
                goto skip;
            }
            // DCG syntax e.g. a-->b.
            if(dcgp(clause)){
                operate(clause);
                goto skip;
            }

            //delete old definition
            if(predicatep(clause)){
                if(atomp(clause))
                    atom  = clause;
                else
                    atom = car(clause);
            }
            else{
                head = cadr(clause);
                if(atomp(head))
                    atom = head;
                else
                    atom = car(head);
            }
            if(!memberp(atom,reconsult_list)){
                reconsult_list = cons(atom,reconsult_list);
                SET_CAR(atom,NIL);
            }

            //assert
            b_assert(list1(clause),NIL);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;

        exit:
        return(YES);
    }
    return(NO);
}

/*
X)->foo, foo(X) :- bar(X)->foo
 set CDR part of atom the arity. e.g. cdr(atom) = #[2,3]
*/
void memoize_arity(int clause, int atom){
    if(predicatep(clause)){
        if(atomp(clause) && !memq(makeint(0),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(0),GET_ARITY(atom)));
        }
        else if(!atomp(clause) && !memq(makeint(length(cdr(clause))),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(length(cdr(clause))),GET_ARITY(atom)));
        }
    }
    else{
        if(atomp(cadr(clause)) &&
           !memq(makeint(0),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(0),GET_ARITY(atom)));
        }
        else if(!atomp(cadr(clause)) &&
                !memq(makeint(length(cdr(cadr(clause)))),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(length(cdr(cadr(clause)))),GET_ARITY(atom)));
        }
    }
}


int b_directory(int arglist, int rest){
    int n,arg1,arg2,arg3,arg4,arg5,arg6,save,mode,date,time;
    DIR *dir;
    struct dirent *dp;
    struct stat stat_buf;
    struct tm *t_st;

    n = length(arglist);
    if(n == 6){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        arg4 = cadddr(arglist);
        arg5 = caddddr(arglist);
        arg6 = cadddddr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"directory ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"directory ",arg1);
        if(!wide_variable_p(arg2))
            error(NOT_VAR,"directory ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"directory ",arg3);
        if(!wide_variable_p(arg4))
            error(NOT_VAR,"directory ",arg4);    
        if(!wide_variable_p(arg5))
            error(NOT_VAR,"directory ",arg5);    
        if(!wide_variable_p(arg6))
            error(NOT_VAR,"directory ",arg6);    

        save = sp;
        dir = opendir(GET_NAME(arg1));
        if(dir == NULL)
            error(SYSTEM_ERROR,"directory ",NIL);

        dp = readdir(dir);
        while (dp != NULL) {
            if(stat(dp->d_name,&stat_buf) == 0){
                if(S_ISREG(stat_buf.st_mode))
                    mode = makeconst("file");
                else if(S_ISDIR(stat_buf.st_mode))
                    mode = makeconst("directory");
                else
                    mode = makeconst("unknown"); 

                t_st = localtime(&stat_buf.st_mtime);
                date = NIL;
                time = NIL;
                time = cons(makeint(t_st->tm_sec),time);
                time = cons(makeint(t_st->tm_min),time);
                time = cons(makeint(t_st->tm_hour),time);
                time = cons(makeconst("time"),time);
                SET_AUX(car(time),PRED);
                date = cons(makeint(t_st->tm_mday),date);
                date = cons(makeint(t_st->tm_mon+1),date);
                date = cons(makeint(t_st->tm_year+1900),date);
                date = cons(makeconst("date"),date);
                SET_AUX(car(date),PRED);
                unify(arg2,makeconst(dp->d_name));
                unify(arg3,mode);
                unify(arg4,time);
                unify(arg5,date);
                unify(arg6,makeint(stat_buf.st_size));
                if(prove_all(rest,sp,0) == YES)
                    return(YES);
            }
            else
                error(SYSTEM_ERROR,"directory ",NIL);

            unbind(save);
            dp = readdir(dir);
        }
        if(dir != NULL)
            closedir(dir);
        
        unbind(save);
        return(NO);
    }
    return(NO);
}
        

//arithmetic operation

int b_is(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"is ", arg2);

        arg2 = eval(arg2);
        res = unify(arg1,arg2);
        return(res);
    }
    return(NO);
}


int b_greater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"> ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"> ",arg2);


        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,"> ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"> ",arg2);

        if(greaterp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_smaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"< ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"< ",arg2);


        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,"< ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"< ",arg2);
        if(smallerp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_eqsmaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"=< ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"=< ",arg2);

        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,"=< ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"=< ",arg2);
        if(eqsmallerp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_eqgreater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,">= ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,">= ",arg2);

        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,">= ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,">= ",arg2);
        if(eqgreaterp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_numeq(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = eval(car(arglist));
        arg2 = eval(cadr(arglist));
        if(!numberp(arg1))
            error(NOT_NUM,"=:= ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"=:= ",arg2);

        if(numeqp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_notnumeq(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = eval(car(arglist));
        arg2 = eval(cadr(arglist));
        if(!numberp(arg1))
            error(NOT_NUM,"=:= ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"=:= ",arg2);

        if(!numeqp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_equalp(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(anoymousp(arg1) && anoymousp(arg2))
            return(NO);
        else if(equalp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_notequalp(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(anoymousp(arg1) && anoymousp(arg2))
            return(YES);
        else if(!equalp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_eq(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(arg1 == arg2)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}



int b_compare(int arglist, int rest){
    int n,arg1,arg2,arg3;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"compare ",arg1);
        if(!wide_variable_p(arg1) &&
          !(eqp(arg1,makeatom("<",SYS)) ||
            eqp(arg1,makeatom("=",SYS)) ||
            eqp(arg1,makeatom(">",SYS))))
            error(NOT_ORDER,"compare ",arg1);

        if(equalp(arg2,arg3))
            return(unify(arg1,makeatom("=",SYS)));
        else if(atsmaller(arg2,arg3))
            return(unify(arg1,makeatom("<",SYS)));
        else if(atsmaller(arg3,arg2))
            return(unify(arg1,makeatom(">",SYS)));

    }
    return(NO);
}

int b_atsmaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(atsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@< ", makeint(n));
    return(NO);
}

int atsmaller(int x, int y){

    if(nullp(x))
        return(0);
    else if(variablep(x) || variablep(y))
        return(1);
    else if(numberp(x) && numberp(y)){
        if(smallerp(x,y))
            return(1);
        else
            return(0);
    }
    else if(atomp(x) && atomp(y)){
        if(strcmp(GET_NAME(x),GET_NAME(y)) < 0)
            return(1);
        else
            return(0);
    }
    else if(structurep(x) && structurep(y)){
        if(length(x) < length(y))
            return(1);
        else if(length(x) > length(y))
            return(0);
        else if(atsmaller(car(x),car(y)))
            return(1);
        else if(equalp(car(x),car(y)))
            return(atsmaller(cdr(x),cdr(y)));
        else
            return(0);
    }
    else if(floatp(x))
       return(1);
    else if(wide_integer_p(x) && atomp(y))
        return(1);
    else if(wide_integer_p(x) && structurep(y))
        return(1);
    else if(atomp(x) && structurep(y))
        return(1);
    else
        return(0);
}

int ateqsmaller(int x, int y){

    if(nullp(x))
        return(0);
    else if(variablep(x) || variablep(y))
        return(1);
    else if(numberp(x) && numberp(y)){
        if(eqsmallerp(x,y))
            return(1);
        else
            return(0);
    }
    else if(atomp(x) && atomp(y)){
        if(strcmp(GET_NAME(x),GET_NAME(y)) <= 0)
            return(1);
        else
            return(0);
    }
    else if(structurep(x) && structurep(y)){
        if(length(x) < length(y))
            return(1);
        else if(length(x) > length(y))
            return(0);
        else if(ateqsmaller(car(x),car(y)))
            return(1);
        else if(equalp(car(x),car(y)))
            return(ateqsmaller(cdr(x),cdr(y)));
        else
            return(0);
    }
    else if(floatp(x))
       return(1);
    else if(wide_integer_p(x) && atomp(y))
        return(1);
    else if(wide_integer_p(x) && structurep(y))
        return(1);
    else if(atomp(x) && structurep(y))
        return(1);
    else
        return(0);
}


int b_ateqsmaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(ateqsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@=< ", makeint(n));
    return(NO);
}



int b_atgreater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!ateqsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@> ", makeint(n));
    return(NO);
}


int b_ateqgreater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!atsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@>= ", makeint(n));
    return(NO);
}

//timer
int b_ctr_set(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!integerp(arg1))
            error(NOT_INT,"ctr_set ",arg1);
        if(GET_INT(arg1) > 30)
            error(ILLEGAL_ARGS,"str_set ",arg1);
        if(!integerp(arg2))
            error(NOT_INT,"ctr_set ",arg2);
        
        counter[GET_INT(arg1)] = GET_INT(arg2);
        return(YES);

    }
    return(NO);
}

int b_ctr_dec(int arglist, int rest){
    int n,arg1,arg2,i;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!integerp(arg1))
            error(NOT_INT,"ctr_dec ",arg1);
        if(GET_INT(arg1) > 30)
            error(ILLEGAL_ARGS,"str_set ",arg1);
        if(!wide_variable_p(arg2))
            error(NOT_VAR,"ctr_dec ",arg2);
        
        i = counter[GET_INT(arg1)];
        counter[GET_INT(arg1)] = i-1;
        return(unify(arg2,makeint(i)));

    }
    return(NO);
}

int b_ctr_inc(int arglist, int rest){
    int n,arg1,arg2,i;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!integerp(arg1))
            error(NOT_INT,"ctr_dec ",arg1);
        if(GET_INT(arg1) > 30)
            error(ILLEGAL_ARGS,"str_set ",arg1);
        if(!wide_variable_p(arg2))
            error(NOT_VAR,"ctr_dec ",arg2);
        
        i = counter[GET_INT(arg1)];
        counter[GET_INT(arg1)] = i+1;
        return(unify(arg2,makeint(i)));

    }
    return(NO);
}

int b_ctr_is(int arglist, int rest){
    int n,arg1,arg2,i;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!integerp(arg1))
            error(NOT_INT,"ctr_dec ",arg1);
        if(GET_INT(arg1) > 30)
            error(ILLEGAL_ARGS,"str_set ",arg1);
        if(!wide_variable_p(arg2))
            error(NOT_VAR,"ctr_dec ",arg2);
        
        i = counter[GET_INT(arg1)];
        return(unify(arg2,makeint(i)));

    }
    return(NO);
}

//true fail
int b_fail(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        return(NO);
    }
    return(NO);
}

int b_call(int arglist, int rest){
    int n,arg1,res;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"call ",arg1);

        if(!callablep(arg1))
            error(NOT_CALLABLE,"call ",arg1);
        
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"call ",arg1);

        res = prove_all(addtail_body(rest,arg1),sp,n);
        return(res);
    }
    
    return(NO);
}

int b_not(int arglist, int rest){
    int n,arg1,res;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"not ",arg1);
        if(!callablep(arg1))
            error(NOT_CALLABLE,"not ", arg1);

        res = prove(arg1,sp,NIL,0);
        if(res == YES)
            return(NO);
        else
            return(YES);
    }
    return(NO);
}

int b_true(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        return(YES);
    }
    return(NO);
}


//database operation
int b_assert(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"assertz ",arg1);
        if(singlep(arg1)){
            if(GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
                SET_AUX(arg1,PRED);
        }
        if(builtinp(arg1))
            error(BUILTIN_EXIST,"assertz ",arg1);
        

        arg1 = variable_to_call(arg1); //P -> call(P)
        arg1 = copy_heap(arg1); //copy arg1 to heap area
        if(predicatep(arg1)){
            SET_VAR(arg1,unique(varslist(arg1)));
            if(atomp(arg1))
                add_data(arg1,arg1);
            else
                add_data(car(arg1),arg1);
            checkgbc();
            return(YES);
        }
        else if(operationp(arg1)){
            if(!callablep(caddr(arg1)))
                error(NOT_CALLABLE,"assertz ",arg1);
            if(operationp(cadr(arg1)))
                error(BUILTIN_EXIST,"assertz ",arg1);
            
            SET_VAR(arg1,unique(varslist(arg1)));
            operate(arg1);
            checkgbc();
            return(YES);
        }
        error(NOT_CALLABLE,"assertz ",arg1);
    }
    return(NO);
}

int b_asserta(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"asserta ",arg1);
        if(singlep(arg1)){
            if(GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
                SET_AUX(arg1,PRED);
        }
        if(builtinp(arg1))
            error(BUILTIN_EXIST,"asserta ",arg1);
        

        arg1 = variable_to_call(arg1); //P -> call(P)
        arg1 = copy_heap(arg1); //copy arg1 to heap area
        if(predicatep(arg1)){
            SET_VAR(arg1,unique(varslist(arg1)));
            if(atomp(arg1))
                insert_data(arg1,arg1);
            else
                insert_data(car(arg1),arg1);
            checkgbc();
            return(YES);
        }
        else if(operationp(arg1)){
            if(!callablep(caddr(arg1)))
                error(NOT_CALLABLE,"asserta ",arg1);
            if(operationp(cadr(arg1)))
                error(BUILTIN_EXIST,"asserta ",arg1);

            SET_VAR(arg1,unique(varslist(arg1)));
            operate(arg1);
            assert_flag = 0;
            checkgbc();
            return(YES);
        }
        error(NOT_CALLABLE,"asserta ",arg1);
    }
    return(NO);
}

int b_retract(int arglist, int rest){
    int n,arg1,clause,head,clauses,new_clauses,save1,save2;

    save2 = sp;
    clause = clauses = head = NIL;
    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"retract ",arg1);
        if(operationp(arg1) && !predicatep(cadr(arg1)))
            error(NOT_CALLABLE,"retract ",arg1);
        if(!operationp(arg1) && !predicatep(arg1))
            error(NOT_CALLABLE,"retract ",arg1);
        if(operationp(arg1) && builtinp(cadr(arg1)))
            error(BUILTIN_EXIST,"retract ",arg1);
        if(!operationp(arg1) && builtinp(arg1))
            error(BUILTIN_EXIST,"retract ",arg1);

        if(singlep(arg1)){
            arg1 = list1(arg1);
        }
        if(atom_predicate_p(arg1))
            clauses = GET_CAR(arg1);
        else if(predicatep(arg1))
            clauses = GET_CAR(car(arg1));
        else if(clausep(arg1) && atom_predicate_p(cadr(arg1)))
            clauses = GET_CAR(cadr(arg1));
        else if(clausep(arg1))
            clauses = GET_CAR(car(cadr(arg1)));

        new_clauses = NIL;
        save1 = wp;
        while(!nullp(clauses)){
            clause = car(clauses);
            clauses = cdr(clauses);

            if(unify(arg1,clause) == YES){
                if(atom_predicate_p(arg1))
                    SET_CAR(clause,append(listreverse(new_clauses),clauses));
                else if(predicatep(arg1))
                    SET_CAR(car(arg1),append(listreverse(new_clauses),clauses));
                else if(clausep(arg1) && atom_predicate_p(cadr(arg1)))
                    SET_CAR(cadr(arg1),append(listreverse(new_clauses),clauses));
                else if(clausep(arg1))
                    SET_CAR(car(cadr(arg1)),append(listreverse(new_clauses),clauses));

                if(prove_all(rest,sp,0) == YES)
                    return(YES);
                else
                    goto next;
            }
            new_clauses = cons(clause,new_clauses);
            next:
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        sp = save2;
        return(NO);
    }
    return(NO);
}


int b_abolish(int arglist, int rest){
    int n,arg1,pred,clause,arity,clauses,new_clauses;

    clause = clauses = NIL;
    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"abolish ",arg1);
        if(structurep(arg1) &&
           (wide_variable_p(cadr(arg1)) ||
            wide_variable_p(caddr(arg1))))
            error(INSTANTATION_ERR,"abolish ",arg1);
        if(car(arg1) != makeatom("/",OPE))
            error(PRED_INDICATOR,"abolish ",arg1);
        if(builtinp(cadr(arg1)))
            error(STATIC_PROCEDURE,"abolish ",arg1);
        if(!atomp(cadr(arg1)))
            error(NOT_ATOM,"abolish ",arg1);
        if(integerp(eval(caddr(arg1))) && GET_INT(eval(caddr(arg1))) < 0)
            error(NOT_LESS_THAN_ZERO,"abolish ",arg1);
        if(!integerp(caddr(arg1)))
            error(NOT_INT,"abolish ",arg1);

        pred = makepred(GET_NAME(cadr(arg1)));
        clauses = GET_CAR(pred);
        arity = GET_INT(caddr(arg1));

        new_clauses = NIL;
        while(!nullp(clauses)){
            clause = car(clauses);

            if(atom_predicate_p(clause) && arity == 0)
                goto abolish;
            else if(predicatep(clause) && length(clause)-1 == arity)
                goto abolish;
            else if(clausep(clause) && atom_predicate_p(cadr(clause)) &&
                    arity == 0)
                goto abolish;
            else if(clausep(clause) && length(cadr(clause))-1 == arity)
                goto abolish;

            new_clauses = cons(clause,new_clauses);

            abolish:
            clauses = cdr(clauses);
        }
        SET_CAR(pred,listreverse(new_clauses));
        if(nullp(new_clauses))
            listremove(cadr(arg1),predicates);
        return(YES);
    }
    return(NO);
}

int b_clause(int arglist, int rest){
    int n,arg1,arg2,clause,clauses,save1,save2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist); //head
        arg2 = cadr(arglist); //body

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"clause ",arg1);
        if(!atom_predicate_p(arg1) && !predicatep(arg1))
            error(NOT_CALLABLE,"clause ",arg1);
        if(builtinp(arg1) || compiledp(arg1))
            error(BUILTIN_EXIST,"clause ",arg1);
        if(!wide_variable_p(arg2) && !callablep(arg2))
            error(NOT_CALLABLE,"clause ",arg2);

        
        if(atom_predicate_p(arg1))
            clauses = GET_CAR(arg1);
        else
            clauses = GET_CAR(car(arg1));

        save1 = wp;
        save2 = sp;
        while(!nullp(clauses)){
            clause = car(clauses);
            clauses = cdr(clauses);
            if(clausep(clause) && unify(arg1,cadr(clause)) == YES &&
                unify(arg2,caddr(clause)) == YES){
                if(prove_all(rest,sp,0) == YES)
                    return(YES);
            }
            else if(predicatep(clause) && unify(arg1,clause) == YES &&
                    unify(arg2,NPLTRUE) == YES){
                if(prove_all(rest,sp,0) == YES)
                    return(YES);
            }
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}


//transform
int b_name(int arglist, int rest){
    int n,arg1,arg2,ls,atom,pos,code,res;
    char str1[STRSIZE],str2[10];

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
            error(INSTANTATION_ERR,"name ",arg1);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"name ",arg1);
        if(wide_variable_p(arg1) && !listp(arg2))
            error(NOT_LIST,"name ",arg2);
        if(wide_variable_p(arg1) && !atom_codes_list_p(arg2))
            error(NOT_CHAR_CODE,"name ",arg2);


        if(singlep(arg1) && !variablep(arg1)){
            strcpy(str1,GET_NAME(arg1));
            ls = NIL;
            pos = 0;
            while(str1[pos] != NUL){
                if(str1[pos] == '\\'){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                }
                else if(mode_flag == 0 && iskanji(str1[pos])){ //SJIS
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = NUL;
                }
                else if(mode_flag == 1 && isUni2(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = NUL;
                }
                else if(mode_flag == 1 && isUni3(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = NUL;
                }
                else if(mode_flag == 1 && isUni4(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = NUL;
                }
                else if(mode_flag == 1 && isUni5(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = str1[pos++];
                    str2[5] = NUL;
                }
                else if(mode_flag == 1 && isUni6(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = str1[pos++];
                    str2[5] = str1[pos++];
                    str2[6] = NUL;
                }
                else{//ascii code
                    str2[0] = str1[pos++];
                    str2[1] = NUL;
                }
                if(str2[0] == '\\')
                    code = ctrl_to_number(str2[1]);
                else if(mode_flag == 0) //SJIS
                    code = makeint(sjis_to_code(str2));
                else //unicode
                    code = makeint(utf8_to_ucs4(str2));
                ls = cons(code,ls);
            }
            ls = listreverse(ls);
            res = unify(arg2,ls);
            return(res);
        }
        else if(structurep(arg2)){
            ls = arg2;
            str1[0] = NUL;
            while(!nullp(ls)){
                if(GET_INT(car(ls)) < ' ')
                    sprintf(str2,"\\x%x\\",GET_INT(car(ls)));
                else if(mode_flag == 0)
                    sjis_to_char(GET_INT(car(ls)),str2);
                else
                    ucs4_to_utf8(GET_INT(car(ls)),str2);
                strcat(str1,str2);
                ls = cdr(ls);
            }
            atom = makeconst(str1);
            res = unify(arg1,atom);
            return(res);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_list_text(int arglist, int rest){
    int n,arg1,arg2,ls,atom,pos,code,index,res;
    char str1[STRSIZE],str2[10];

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);  //list
        arg2 = cadr(arglist); //atomstring
        if(listp(arg1) && length(arg1) == -1 && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"list_text ",arg2);
        if(!wide_variable_p(arg1) && !listp(arg1))
            error(NOT_LIST,"list_text ",arg1);
        if(wide_variable_p(arg1) && !atomp(arg2) && !stringp(arg2))
            error(NOT_ATOM,"list_text ",arg2);
        

        if(atomp(arg2) || stringp(arg2)){
            strcpy(str1,GET_NAME(arg2));
            ls = NIL;
            pos = 0;
            while(str1[pos] != NUL){
                if(str1[pos] == '\\'){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                }
                else if(mode_flag == 0 && iskanji(str1[pos])){ //SJIS
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = NUL;
                }
                else if(mode_flag == 1 && isUni2(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = NUL;
                }
                else if(mode_flag == 1 && isUni3(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = NUL;
                }
                else if(mode_flag == 1 && isUni4(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = NUL;
                }
                else if(mode_flag == 1 && isUni5(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = str1[pos++];
                    str2[5] = NUL;
                }
                else if(mode_flag == 1 && isUni6(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = str1[pos++];
                    str2[5] = str1[pos++];
                    str2[6] = NUL;
                }
                else{//ascii code
                    str2[0] = str1[pos++];
                    str2[1] = NUL;
                }
                if(str2[0] == '\\')
                    code = ctrl_to_number(str2[1]);
                else if(mode_flag == 0) //SJIS
                    code = makeint(sjis_to_code(str2));
                else //unicode
                    code = makeint(utf8_to_ucs4(str2));
                ls = cons(code,ls);
            }
            ls = listreverse(ls);
            res = unify(arg1,ls);
            return(res);
        }
        else if(structurep(arg1)){
            ls = arg1;
            str1[0] = NUL;
            while(!nullp(ls)){
                if(GET_INT(car(ls)) < ' ')
                    sprintf(str2,"\\x%x\\",GET_INT(car(ls)));
                else if(mode_flag == 0)
                    sjis_to_char(GET_INT(car(ls)),str2);
                else
                    ucs4_to_utf8(GET_INT(car(ls)),str2);
                strcat(str1,str2);
                ls = cdr(ls);
            }

            index = hash(str1);
            if((res=getatom(str1,SIMP,index)) != 0)
                atom = res;
            else if((res=getatom(str1,PRED,index)) != 0)
                atom = res;
            else if((res=getatom(str1,SYS,index)) != 0)
                atom = res;
            else if((res=getatom(str1,COMP,index)) != 0)
                atom = res;
            else if((res=getatom(str1,OPE,index)) != 0)
                atom = res;
            else if((res=getatom(str1,USER,index)) != 0)
                atom = res;
            else
                atom = makestr(str1);
            
            return(unify(arg2,atom));
        }
        else
            return(NO);
    }
    return(NO);
}


int b_atom_concat(int arglist, int rest){
    int n,arg1,arg2,arg3,atom;
    char str1[STRSIZE];

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"atom_concat ",arg1);
        if(!wide_variable_p(arg2) && !atomp(arg2))
            error(NOT_ATOM,"atom_concat ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"atom_concat ", arg3);
    
        strcpy(str1,GET_NAME(arg1));
        strcat(str1,GET_NAME(arg2));
        atom = makeconst(str1);

        unify(arg3,atom);
        return(YES);

    }
    return(NO);
}

int b_atom_string(int arglist, int rest){
    int n,arg1,arg2,temp;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist); //atom
        arg2 = cadr(arglist);//string

        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"atom_string ",arg1);
        if(!wide_variable_p(arg2) && !stringp(arg2))
            error(NOT_STR,"atom_string ",arg2);

        if(atomp(arg1)){
            temp = makestr(GET_NAME(arg1));
            return(unify(arg2,temp));
        }
        else if(stringp(arg2)){
            temp = makeconst(GET_NAME(arg2));
            return(unify(arg1,temp));
        }
    }
    return(NO);
}

int b_char_code(int arglist, int rest){
    int n,arg1,arg2,code,res;
    char str[2];

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"char_code ",list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !characterp(arg1))
            error(NOT_CHAR,"char_code ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"char_code ",arg2);


        if(atomp(arg1) && !variablep(arg1)){
            strcpy(str,GET_NAME(arg1));
            if(str[0] == '\\'){
                if(str[1] == 'n')
                    return(unify(arg2,makeint(EOL)));
                else if(str[1] == 't')
                    return(unify(arg2,makeint(TAB)));
                else if(str[1] == 'f')
                    return(unify(arg2,makeint(FF)));
                else if(str[1] == 'r')
                    return(unify(arg2,makeint(CR)));
                else if(str[1] == 'v')
                    return(unify(arg2,makeint(VT)));
                else if(str[1] == 'a')
                    return(unify(arg2,makeint(BEL)));
                else if(str[1] == 'b')
                    return(unify(arg2,makeint(BS)));
                else
                    error(SYNTAX_ERR,"char_code ",NIL);
            }
            //unicode
            code = makeint(utf8_to_ucs4(GET_NAME(arg1)));
            res = unify(arg2,code);
            return(res);
        }
        else if(integerp(arg2)){
            //unicode
            ucs4_to_utf8(GET_INT(arg2),str);
            res = unify(arg1,makeconst(str));
            return(res);
        }
        else
            return(NO);
    }
    return(NO);
}



//----------string transform-------------------

int b_concat(int arglist, int rest){
    int n,arg1,arg2,arg3,str;
    char str1[STRSIZE];

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        
        if(!wide_variable_p(arg1) && !(atomp(arg1) || stringp(arg1)))
            error(NOT_STR,"concat ",arg1);
        if(!wide_variable_p(arg2) && !(atomp(arg2) || stringp(arg2)))
            error(NOT_STR,"concat ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"concat ", arg3);
    
        strcpy(str1,GET_NAME(arg1));
        strcat(str1,GET_NAME(arg2));
        str = makestr(str1);

        unify(arg3,str);
        return(YES);

    }
    return(NO);
}

int b_string_length(int arglist, int rest){
    int n,arg1,arg2,val;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"string_length ",arg1);
        if(!stringp(arg1))
            error(NOT_STR,"string_length ",arg1);
        if(integerp(eval(arg2)) && GET_INT(eval(arg2)) < 0)
            error(NOT_LESS_THAN_ZERO,"string_length ",arg2);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"string_length ", arg2);

        val = makeint(string_length(arg1));
        return(unify(arg2,val));
    }
    return(NO);
}

int b_string_term(int arglist, int rest){
    int n,arg1,arg2,l,i,res;
    char str[STRSIZE];

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"string_term ",arg1);
        if(!stringp(arg1))
            error(NOT_STR,"string_term ",arg1);

        l = strlen(GET_NAME(arg1));
        memset(str,'\0',STRSIZE);
        strcpy(str,GET_NAME(arg1));
        for(i=0;i<l;i++)
            string_term_buffer[i] = str[i];
        
        string_term_buffer[l] = '.';
        string_term_buffer[l+1] = 0;
        read_string_term(0); //initilize 
        string_term_flag = 1;
        res = readparse();
        string_term_flag = 0;
        return(unify(arg2,res));
    }
    return(NO);
}

int read_string_term(int flag){
    static int pos=0;

    if(flag == 0){
       pos = 0;
       return(0);
    }
    else if(flag == -1){
        pos--;
        return(-1);
    }


    return(string_term_buffer[pos++]);
}

int b_substring(int arglist, int rest){
    int n,arg1,arg2,arg3,arg4,i,j,k,start,len,str;
    char str1[STRSIZE],str2[STRSIZE];

    n = length(arglist);
    if(n == 4){
        arg1 = car(arglist);   //instring
        arg2 = cadr(arglist);  //start
        arg3 = caddr(arglist); //length
        arg4 = cadddr(arglist);//outstring

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"substring ",arg1);
        if(!stringp(arg1))
            error(NOT_STR,"substring ",arg1);
        if(!wide_variable_p(arg4) && !stringp(arg4))
            error(NOT_STR,"substring ",arg4);
        if(integerp(arg2) && GET_INT(arg2) < 0)
            error(NOT_LESS_THAN_ZERO,"substring ",arg2);
        if(integerp(arg3) && GET_INT(arg3) < 0)
            error(NOT_LESS_THAN_ZERO,"substring ",arg3);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"substring ",arg2);
        if(!wide_variable_p(arg3) && !wide_integer_p(arg3))
            error(NOT_INT,"substring ",arg3);
        


        strcpy(str1,GET_NAME(arg1));
        start = GET_INT(arg2);
        len   = GET_INT(arg3);
        if(string_length(arg1) < start+len-1)
            error(OUT_OF_RANGE,"substring ", list2(arg2,arg3));
        i= 0;
        j = start - 1;
        k = start + len - 1;
        memset(str2, '\0' ,STRSIZE);
         while(j < k){
            str2[i] = str1[j];
            i++;
            j++;
        }
        str = makestr(str2);
        return(unify(arg4,str));
    }
    return(NO);
}


int b_float_text(int arglist, int rest){
    int n,arg1,arg2,arg3;
    char str[STRSIZE];
    double flt;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        if(!wide_variable_p(arg1) && !floatp(arg1))
            error(NOT_FLT,"float_text ",arg1);
        if(!wide_variable_p(arg2) && !stringp(arg2))
            error(NOT_STR,"float_text ",arg2);
        if(!wide_variable_p(arg3) && !stringp(arg3))
            error(NOT_STR,"float_text ",arg3);

        if(floatp(arg1)){
            sprintf(str,"%g",GET_FLT(arg1));
            return(unify(arg2,makestr(str)));
        }
        else if(stringp(arg2)){
            flt = atof(GET_NAME(arg2));
            return(unify(arg1,makeflt(flt)));
        }
        return(NO);
    }
    return(NO);
}

int b_int_text(int arglist, int rest){
    int n,arg1,arg2,i;
    char str[STRSIZE];

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!wide_variable_p(arg1) && !integerp(arg1))
            error(NOT_FLT,"int_text ",arg1);
        if(!wide_variable_p(arg2) && !stringp(arg2))
            error(NOT_STR,"int_text ",arg2);

        if(integerp(arg1)){
            sprintf(str,"%d",get_int(arg1));
            return(unify(arg2,makestr(str)));
        }
        else if(stringp(arg2)){
            i = atoi(GET_NAME(arg2));
            return(unify(arg1,makeint(i)));
        }
        return(NO);
    }
    return(NO);
}


//controle
int b_cut(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        return(YES);
    }
    return(NO);
}

int b_ifthen(int arglist, int rest){
    int n,arg1,arg2,save1;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        save1 = sp;
        if(variablep(arg1))
            error(INSTANTATION_ERR,"ifthen ",arg1);
        if(variablep(arg2))
            error(INSTANTATION_ERR,"ifthen ",arg2);

        if(prove_all(arg1,sp,0) == YES){
            return(prove_all(arg2,sp,0));
        }
        else{
            unbind(save1);
            return(NO);
        }
            
        unbind(save1);
        return(NO);
    }
    return(NO);
}

int b_ifthenelse(int arglist, int rest){
    int n,arg1,arg2,arg3,save;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        
        if(variablep(arg1))
            error(INSTANTATION_ERR,"ifthenelse ",arg1);
        if(variablep(arg2))
            error(INSTANTATION_ERR,"ifthenelse ",arg2);
        if(variablep(arg3))
            error(INSTANTATION_ERR,"ifthenelse ",arg3);    

        save = sp;
        if(prove_all(arg1,sp,0) == YES){
            return(prove_all(arg2,sp,0));
        }
        else{
            unbind(save);
            return(prove_all(arg3,sp,0));
        }
    }
    return(NO);
}



int b_colon(int nest, int n){
    return(YES);
}



double getETime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec*1e-6;
}

int b_measure(int arglist, int rest){
    int n,arg1,res;
    double start_time,end_time,time,lips;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        proof = 0;
        start_time = getETime(); //time_flag on and it store start time
        res = prove_all(arg1,sp,0);
        end_time = getETime();
        time = end_time - start_time;
        lips = (double)proof / time; 
        ESCFGREEN;
        printf("Elapsed Time=%.6f (second)  %.0f(LIPS)\n", time,lips);
        ESCFORG;
        return(res);
    }
    return(NO);
}


int b_trace(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        debug_flag = ON;
        return(YES);
    }
    return(NO);
}

int b_notrace(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        debug_flag = OFF;
        return(YES);
    }
    return(NO);
}

int b_spy(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 0){
        print(spy_list);
        return(YES);
    }
    else if(n == 1){
        arg1 = car(arglist);
        arg1 = copy_heap(arg1);
    
        if(!memberp(arg1,spy_list))
            spy_list = cons(arg1,spy_list);
        return(YES);
    }
    return(NO);
}

int b_nospy(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 0){
        while(!nullp(spy_list)){
            spy_list = cdr(spy_list);
        }
        return(YES);
    }
    else if(n == 1){
        arg1 = car(arglist);
        arg1 = copy_heap(arg1);
        spy_list = listremove(arg1,spy_list);
        return(YES);
    }
    return(NO);
}

int b_leash(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(arg1 == makeatom("full",SIMP)){
            trace_flag = FULL;
            return(YES);
        }
        else if(arg1 == makeatom("tight",SIMP)){
            trace_flag = TIGHT;
            return(YES);
        }
        else if(arg1 == makeatom("half",SIMP)){
            trace_flag = HALF;
            return(YES);
        }
        else if(arg1 == makeatom("off",SIMP)){
            trace_flag = OFF;
            return(YES);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_debug(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        printf("debug_flag=%d\n", debug_flag);
        printf("trace_flag=%d\n", trace_flag);
        printf("spy_list=");
        print(spy_list);
        printf("\n");
        return(YES);
    }
    return(NO);
}

int b_break(int arglist, int rest){
    int n,input;

    n = length(arglist);
    if(n == 0){
        while(1){
            printf("?- ");
            input = readitem();
            if(input == FEND)
                return(YES);
            
        }
    }
    return(NO);
}

int b_halt(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        printf("- good bye -\n");
        longjmp(buf,2);
    }
    return(NO);
}

int b_abort(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        longjmp(buf,1);
    }
    return(NO);
}


//check data type
int b_atom(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(atomp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_integer(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(integerp(arg1) || longnump(arg1) || bignump(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_real(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(floatp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_number(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(numberp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}


int b_compound(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(compoundp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_ground(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(groundp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_system(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(builtinp(arg1))
            return(YES);
        else
            return(NO);   
    }
    return(NO);
}

int b_var(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(variablep(arg1))
            return(YES);
        else if(anoymousp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_nonvar(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(variablep(arg1))
            return(NO);
        else if(anoymousp(arg1))
            return(NO);
        else
            return(YES);
    }
    return(NO);
}

int b_atomic(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(atomicp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_list(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(listp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_string(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(stringp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}



//-----structure------
int b_functor(int arglist, int rest){
    int n,arg1,arg2,arg3,res,i;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        // to avoid compier bug {}
        if(structurep(arg2) && car(arg2) == CURL && length(arg2) == 1)
            arg2 = CURL;

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"functor ", list2(arg1,arg2));
        if(wide_variable_p(arg1) && wide_variable_p(arg3))
            error(INSTANTATION_ERR,"functor ", list2(arg1,arg3));
        if(wide_variable_p(arg1) && !atomicp(arg2)){
            error(NOT_ATOMIC,"functor ", arg2);}
        if(wide_variable_p(arg1) && integerp(eval(arg3)) && GET_INT(eval(arg3)) < 0)
            error(NOT_LESS_THAN_ZERO,"functor ", arg3);
        if(wide_variable_p(arg1) && !integerp(arg3))
            error(NOT_INT, "functor ", arg3);
        if(wide_variable_p(arg1) && atomicp(arg2) &&
           !atomp(arg2) && integerp(arg3) && GET_INT(arg3) > 0)
            error(NOT_ATOM,"functor ", arg2);


        if(listp(arg1) &&
                 constantp(arg2) && integerp(arg3)){
            i = GET_INT(arg3);
            if(i == 0)
                return(unify(arg1,arg2));
            else{
                res = NIL;
                while(i > 0){
                    res = cons(makevariant(),res);
                    i--;
                }
                res = listreverse(res);
                SET_AUX(arg2,PRED);
                res = cons(arg2,res);
                if(arg2 == DOTOBJ && GET_INT(arg3)==2)
                    res = operate(res);
                return(unify(arg1,res));
            }
        }
        else if(listp(arg1) &&
                wide_variable_p(arg2) &&
                wide_variable_p(arg3)){
            unify(arg2,makeatom(".",SYS));
            unify(arg3,makeint(2));
            return(YES);
        }
        else if(structurep(arg1)){
            if(unify(car(arg1),arg2) == YES &&
               unify(makeint(length(cdr(arg1))),arg3) == YES)
                return(YES);
            else
                return(NO);
        }
        else if(variablep(arg1) && constantp(arg2) && integerp(arg3)){
            i = GET_INT(arg3);
            if(i == 0)
                return(unify(arg1,arg2));
            else{
                res = NIL;
                while(i > 0){
                    res = cons(makevariant(),res);
                    i--;
                }
                res = reverse(res);
                if(GET_AUX(arg2) == SIMP)
                    SET_AUX(arg2,PRED);
                res = cons(arg2,res);
                if(arg2 == DOTOBJ && GET_INT(arg3)==2)
                    res = operate(res);
                return(unify(arg1,res));
            }
        }
        else if(atomicp(arg1)){
            if(unify(arg1,arg2) == YES &&
               unify(makeint(0),arg3) == YES)
                return(YES);
            else
                return(NO);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_arg(int arglist, int rest){
    int n,arg1,arg2,arg3,elt,i;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"arg ", arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"arg ", arg2);
        if(!integerp(arg1))
            error(NOT_INT,"arg ", arg1);
        if(!compoundp(arg2))
            error(NOT_COMPOUND,"arg ", arg2);
        if(integerp(eval(arg1)) && GET_INT(eval(arg1)) < 0)
            error(NOT_LESS_THAN_ZERO,"arg ", arg1);

        if(integerp(arg1) && structurep(arg2)){
            i = GET_INT(arg1);
            if(i < 1 || i >= length(arg2))
                return(NO);
            elt = nth(cdr(arg2),i);
            return(unify(arg3,elt));
        }
    }
    return(NO);
}

int b_arg0(int arglist, int rest){
    int n,arg1,arg2,arg3,elt,i;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"arg ", arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"arg ", arg2);
        if(!integerp(arg1))
            error(NOT_INT,"arg ", arg1);
        if(!compoundp(arg2))
            error(NOT_COMPOUND,"arg ", arg2);
        if(integerp(eval(arg1)) && GET_INT(eval(arg1)) < 0)
            error(NOT_LESS_THAN_ZERO,"arg ", arg1);

        if(integerp(arg1) && structurep(arg2)){
            i = GET_INT(arg1)+1;
            if(i < 1 || i >= length(arg2))
                return(NO);
            elt = nth(cdr(arg2),i);
            return(unify(arg3,elt));
        }
    }
    return(NO);
}


//-----other----
int b_listing(int arglist, int rest){
    int n,arg1,clauses,pred,list,temp;

    n = length(arglist);
    if(n == 0){
        list = listreverse(predicates);
        listing_flag = 1;
        while(!nullp(list)){
            pred = car(list);
            list = cdr(list);
            clauses = GET_CAR(pred);
            while(!nullp(clauses)){
                print(car(clauses));
                printf(".\n");
                clauses = cdr(clauses);
            }
        }
        listing_flag = 0;
        return(YES);
    }
    if(n == 1){
        arg1 = car(arglist);
        if(atomp(arg1)){
            clauses = GET_CAR(arg1);
            listing_flag = 1;
            while(!nullp(clauses)){
                print(car(clauses));
                printf(".\n");
                clauses = cdr(clauses);
            }
            listing_flag = 0;
            return(YES);
        }
        else if(eqlp(car(arg1),makeope("/")) &&
                atomp(cadr(arg1)) && integerp(caddr(arg1))){
            clauses = GET_CAR(cadr(arg1));
            listing_flag = 1;
            while(!nullp(clauses)){
                temp = car(clauses);
                if(predicatep(temp) && length(cdr(temp)) == GET_INT(caddr(arg1))){
                    print(temp);
                    printf(".\n");
                }
                else if(clausep(temp) && length(cdr(cadr(arg1))) == GET_INT(caddr(arg1))){
                    print(temp);
                    printf(".\n");
                }
                clauses = cdr(clauses);
            }
            listing_flag = 0;
            return(YES);
        }
    }
    return(NO);
}


//transform bwtween predicate and data
int b_univ(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(variablep(arg1) && variablep(arg2))
            error(INSTANTATION_ERR,"=.. ",list2(arg1,arg2));
        if(listp(arg2) && compoundp(car(arg2)))
            error(NOT_ATOMIC,"=.. ", arg2);
        if(variablep(arg1) && nullp(arg2))
            error(NON_EMPTY_LIST,"=.. ", arg2);



        if(!wide_variable_p(arg1) && atomicp(arg1)){
            res = list1(arg1);
            SET_AUX(res,LIST);
            return(unify(res,arg2));
        }
        else if(predicatep(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(builtinp(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(compiledp(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(operationp(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(variablep(arg1) && listp(arg2)){
            if(GET_AUX(car(arg2)) != SYS &&
               GET_AUX(car(arg2)) != COMP &&
               GET_AUX(car(arg2)) != OPE)
                SET_AUX(car(arg2),PRED);
            if(car(arg2) == DOTOBJ)
                arg2 = operate(arg2);
            SET_AUX(arg2,0);
            return(unify(arg1,arg2));
        }
        else if(listp(arg1)){
            arg1 = list3(DOTOBJ,car(arg1),cdr(arg1));
            SET_AUX(arg1,LIST);
            return(unify(arg1,arg2));
        }
        else if(alpha_variable_p(arg2)){//for bug of OPL compiler
            return(unify(arg1,arg2));
        }
        else{
            return(unify(arg1,arg2));
        }
    }
    return(NO);
}

int b_current_predicate(int arglist, int rest){
    int n,arg1,save1,save2,predlist,pred,aritylist,arity;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        predlist = reverse(predicates);
        save1 = wp;
        save2 = sp;
        while(!nullp(predlist)){
            pred = car(predlist);
            predlist = cdr(predlist);
            aritylist = GET_ARITY(pred);
            while(!nullp(aritylist)){
                arity = car(aritylist);
                aritylist = cdr(aritylist);   
                if(unify(arg1,list3(makeatom("/",OPE),pred,arity)) == YES)
                    if(prove(NIL,sp,rest,0) == YES)
                        return(YES);
                
                wp = save1;
                unbind(save2);
            }
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_current_op(int arglist, int rest){
    int n,arg1,arg2,arg3,save1,save2,
        lis,weight,spec,op,w,s,o;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        /*
        e.g. ',' ':-'  aux of operator is SIMP
        beclause of parsing. so change to OPE from SIMP
        */
        if(getatom(GET_NAME(arg3),OPE,hash(GET_NAME(arg3))))
            arg3 = makeatom(GET_NAME(arg3),OPE);

        lis = op_list;
        spec = NIL;
        save1 = wp;
        save2 = sp;
        while(!nullp(lis)){
            weight = car(car(lis));
            spec = cadr(car(lis));
            op = caddr(car(lis));

            w= unify(arg1,weight);
            s = unify(arg2,spec);
            o = unify(arg3,op);
            if(w == YES && s == YES && o == YES)
                if(prove(NIL,sp,rest,0) == YES)
                    return(YES);
            lis = cdr(lis);
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_predicate_property(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist); //term
        arg2 = cadr(arglist);//prop

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"predicate_property ",arg1);

        if(atomp(arg1) && GET_AUX(arg1) == SYS)
            return(unify(arg2,makeconst("built_in")));
        else if(structurep(arg1) && GET_AUX(car(arg1)) == SYS)
            return(unify(arg2,makeconst("built_in")));
        else if(atomp(arg1) && GET_AUX(arg1) == PRED &&
                GET_CAR(arg1) != NIL)
            return(unify(arg2,makeconst("dynamic")));
        else if(structurep(arg1) && GET_AUX(car(arg1)) == PRED &&
                GET_CAR(car(arg1)) != NIL)
            return(unify(arg2,makeconst("dynamic")));
        else if(atomp(arg1) && GET_AUX(arg1) == COMP)
            return(unify(arg2,makeconst("static")));
        else if(structurep(arg1) && GET_AUX(car(arg1)) == COMP)
            return(unify(arg2,makeconst("static")));
        else
            return(NO);
    }
    return(NO);

}


int b_reset_op(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        initoperator();
        return(YES);
    }
    return(NO);
}

int o_define(int x, int y){
    int clause;

    if(!nullp(y)){
        if(builtinp(x) || compiledp(x))
            error(BUILTIN_EXIST,"assertz",x);
        if(atomp(x))
            SET_AUX(x,PRED);
        clause = list3(DEFINE,x,y);
        SET_AUX(clause,CLAUSE);
        SET_VAR(clause,reverse(unique(varslist(clause))));
    
        if(assert_flag){
            if(atomp(x))
                insert_data(cadr(clause),clause);
            else
        	    insert_data(car(cadr(clause)),clause);
        }
        else{
            if(atomp(x))
        	     add_data(cadr(clause),clause);
            else
                add_data(car(cadr(clause)),clause);
        }

        return(YES);
    }
    // :- predicate.
    else{
        return(prove_all(x,sp,0));
    }
    return(NO);
}

int o_dcg(int x, int y){
    int clause,res;

    clause = list2(makepred("dcg_expand"),
                list3(makeatom("-->",OPE),x,y));

    res = prove_all(clause,sp,0);
    return(res);
}



int b_gbc(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(arg1 == makeconst("full"))
            gbc();
        return(YES);
    }
    
    return(NO);
}



int o_ignore(int nest, int n){
    return(YES);
}


//-----------file system-------------------
int b_mkdir(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"mkdir ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"mkdir ", arg1);

        mkdir(GET_NAME(arg1),0777);
        return(YES);
    }
    return(NO);
}


int b_rmdir(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"rmdir ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"rmdir ", arg1);

        rmdir(GET_NAME(arg1));
        return(YES);
    }
    return(NO);
}


int b_chdir(int arglist , int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"chdir ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"chdir ", arg1);

        if(chdir(GET_NAME(arg1)) != -1)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_delete(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"delete ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"delete ", arg1);

        remove(GET_NAME(arg1));
        return(YES);
    }
    return(NO);
}


int b_rename(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"rename ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"rename ", arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"rename ",arg2);
        if(!atomp(arg2))
            error(NOT_ATOM,"rename ", arg2);
        

        rename(GET_NAME(arg1),GET_NAME(arg2));
        return(YES);
    }
    return(NO);
}


int b_edit(int arglist, int rest){
    int n,arg1,res;
    char str[STRSIZE];
    char *editor;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(!singlep(arg1))
            error(NOT_ATOM,"edit ",arg1);

        editor = getenv("EDITOR");
        if(editor == NULL){
            strcpy(str,"nano ");
            strcat(str,GET_NAME(arg1));
        }
        else{
            strcpy(str,editor);
            strcat(str," ");
            strcat(str,GET_NAME(arg1));
        }
        res = system(str);
        if(res == -1)
            error(SYSTEM_ERROR,"edit ",arg1);
        b_reconsult(list1(arg1),NIL);
        return(YES);
    }
    return(NO);
}


int b_shell(int arglist, int rest){
    int n,arg1,res;
    char str1[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(!singlep(arg1))
            error(NOT_ATOM,"shell",arg1);

        strcpy(str1,GET_NAME(arg1));
        res = system(str1);
        if(res == -1)
            error(SYSTEM_ERROR,"shell",arg1);
        return(YES);
    }
    return(NO);
}


int b_syntaxerrors(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        res = unify(arg1,syntax_flag); 
        syntax_flag = arg2;
        return(res);
    }
    return(NO);
}


int b_sort(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        return(unify(arg2,sort(arg1)));
    }
    return(NO);
}

int b_keysort(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        return(unify(arg2,keysort(arg1)));
    }
    return(NO);
}

int b_member(int arglist, int rest){
    int n,arg1,arg2,x,y,l,save1,save2,body;

    save2 = sp;
    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);


        save1 = wp;
        x = makevariant();
        l = makevariant();
        if(unify(arg1,x) == YES && unify(arg2,wlistcons(x,l)) == YES){
            if(prove(NIL,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);

        save1 = wp;
        x = makevariant();
        y = makevariant();
        l = makevariant();
        if(unify(arg1,x) == YES &&
           unify(arg2,wlistcons(y,l)) == YES){
            body = wlist3(makeatom("member",COMP),x,l);
            if(prove(body,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

//---------extention--------

int b_append(int arglist, int rest){
    int n,arg1,arg2,arg3,x,ls,ys,zs,save1,save2,body;

    save2 = sp;
    body = NIL;
    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);

        save1 = wp;
        if(unify(arg1,NIL) == YES && unify(arg2,arg3) == YES){
            if(prove(NIL,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);

        save1 = wp;
        x = makevariant();
        ls = makevariant();
        ys = makevariant();
        zs = makevariant();
        if(unify(arg1,wlistcons(x,ls)) == YES &&
           unify(arg2,ys) == YES &&
           unify(arg3,wlistcons(x,zs)) == YES){
            body = wlist4(makeatom("append",COMP),ls,ys,zs);
            if(prove(body,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

//listreverse/2
int b_reverse(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(!variablep(arg1) && variablep(arg2))
            return(unify(listreverse(arg1),arg2));
        else if(variablep(arg1) && !variablep(arg2))
            return(unify(arg1,listreverse(arg2)));
        else
            return(NO);
    }
    return(NO);
}


int b_between(int arglist, int rest){
    int n,arg1,arg2,arg3,save1,save2,save3,low,high;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);   //low
        arg2 = cadr(arglist);  //high
        arg3 = caddr(arglist); //variable
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"between ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"between ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"between ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"between ",arg2);
        if(!wide_variable_p(arg3) && !wide_integer_p(arg3))
            error(NOT_INT,"between ",arg3);

        save1 = wp;
        save2 = sp;
        save3 = ac;
        low = get_int(arg1);
        high = get_int(arg2);
        while(low <= high){
            //printf("%d",low);
            unify(arg3,makeint(low));
            if(prove_all(rest,sp,0) == YES)
                return(YES);
            
            low++;
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        unify(arg3,arg2);
        ac = save3;
        return(NO);
    }
    return(NO);
}


//------------------------------------------------

int b_inc(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"inc ", list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"inc ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"inc ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"inc ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"inc ",arg2);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"inc ",arg1);
        if(wide_integer_p(arg2) && negativep(arg2))
            error(NOT_LESS_THAN_ZERO,"inc ",arg2);

        if(wide_variable_p(arg1))
            return(unify(arg1,minus(arg2,makeint(1))));
        else if(wide_variable_p(arg2))
            return(unify(arg2,plus(arg1,makeint(1))));
        else
            return(unify(arg2,plus(arg1,makeint(1))));

    }
    return(NO);
}

int b_dec(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"dec ", list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"dec ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"dec ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"dec ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"dec ",arg2);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"dec ",arg1);
        if(wide_integer_p(arg2) && negativep(arg2))
            error(NOT_LESS_THAN_ZERO,"dec ",arg2);

        if(wide_variable_p(arg1))
            return(unify(arg1,plus(arg2,makeint(1))));
        else if(wide_variable_p(arg2))
            return(unify(arg2,minus(arg1,makeint(1))));
        else
            return(unify(arg2,minus(arg1,makeint(1))));

    }
    return(NO);
}

int b_ansi_cup(int arglist, int rest){
    int n,arg1,arg2,r,c;

    n=length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cup ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"ansi_cup ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cup ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"ansi_cup ", arg2);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"ansi_cup ",arg2);
        if(wide_integer_p(arg2) && negativep(arg2))
            error(NOT_LESS_THAN_ZERO,"ansi_cup ",arg2);
        
        r = get_int(arg1);
        c = get_int(arg2);
        ESCMOVE(r,c);
        cursor_row = r;
        cursor_col = c;
        return(YES);
    }
    return(NO);
}

int b_ansi_cpr(int arglist, int rest){
    int n,arg1,arg2,r,c,res1,res2;

    n=length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
 
        r = makeint(cursor_row);
        c = makeint(cursor_col);
        res1 = unify(arg1,r);
        res2 = unify(arg2,c);
        if(res1 == YES && res2 == YES)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_ansi_scp(int arglist, int rest){
    int n;

    n=length(arglist);
    if(n == 0){
        cursor_row_store = cursor_row;
        cursor_col_store = cursor_col;
        cursor_prop_store = cursor_prop;
        return(YES);
    }
    return(NO);
}

int b_ansi_rcp(int arglist, int rest){
    int n;

    n=length(arglist);
    if(n == 0){
        cursor_row = cursor_row_store;
        cursor_col = cursor_col_store;
        cursor_prop = cursor_prop_store;
        return(YES);
    }
    return(NO);
}

int b_ansi_ed(int arglist, int rest){
    int n;

    n=length(arglist);
    if(n == 0){
        ESCCLS;
        ESCTOP;
        return(YES);
    }
    return(NO);
}

int b_ansi_el(int arglist, int rest){
    int n;

    n=length(arglist);
    if(n == 0){
        ESCCLSL;
        ESCMVLEFT(0);
        return(YES);
    }
    return(NO);
}


int b_ansi_cuu(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cuu ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"ansi_cuu ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cuu ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVU;
            cursor_row--;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_cud(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cud ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_cud ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cud ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVD;
            cursor_row++;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_cuf(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cuf ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_cuf ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cuf ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVR;
            cursor_col--;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_cub(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cub ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_cub ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cub ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVL;
            cursor_col++;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_sgr(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_sgr ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_sgr ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_sgr ",arg1);
        m = get_int(arg1);
        ESCCOLOR(m);
        cursor_prop = m;
        return(YES);
    }
    return(NO);
}



int b_date(int arglist, int rest){
    int n,arg1,res;
    struct tm* jst;
    time_t t;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        t = time( NULL );
        jst = localtime( &t );
        res = list4(makepred("date"),makeint(jst->tm_year+1900),makeint(jst->tm_mon+1),makeint(jst->tm_mday));
        return(unify(arg1,res));
    }
    return(NO);
}

int b_date_day(int arglist, int rest){
    int n,arg1,arg2,y,m,d,w;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        y = get_int(cadr(arg1));
        m = get_int(caddr(arg1));
        d = get_int(cadddr(arg1));
        if (m < 3){
            y--;
            m += 12;
        }
        w = (y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7;
        return(unify(arg2,makeint(w)));
    }
    return(NO);
}

int b_time(int arglist, int rest){
    int n,arg1,res;
    struct tm* jst;
    time_t t;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
    
        t = time( NULL );
        jst = localtime( &t );
        res = list4(makepred("time"),makeint(jst->tm_hour),makeint(jst->tm_min),makeint(jst->tm_sec));
        return(unify(arg1,res));
    }
    return(NO);
}

int b_errorcode(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        return(unify(arg1,makeint(error_code)));
    }
    return(NO);
}


//-----------record data type-----------------------------
/*
                          CAR,CDR,...,ARITY
atom of record name    foo[NIL,......,record_id,...]

record_hash_table 
 ID0   ID1  ID2
0[7272,1232,9992,...]
1[3232,9231,2312,...]
...
HASHTBLSIZE[]

cell_list
e.g. hash == 1 ID==1 (ID starts from 1)
addr 1232 -> [pred1,pred2,...] 

*/

int b_recordh(int arglist, int rest){
    int n,arg1,arg2,arg3,record_id,index;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);    //table_name
        arg2 = cadr(arglist);   //sort_key
        arg3 = caddr(arglist);  //term
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"recordh ", arg1);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"recordh ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"recordh ", arg2);
        if(!wide_variable_p(arg2) && !atomp(arg2))
            error(NOT_ATOM,"recordh ",arg2);
        if(wide_variable_p(arg3))
            error(INSTANTATION_ERR,"recordh ", arg3);
        if(!termp(arg3) && !integerp(arg3))
            error(NOT_TERM,"record ",arg3);

        if(integerp(arg3))
            arg3 = get_int(arg3);   //reffernce number -> term
        else 
            arg3 = copy_heap(arg3); //copy arg1 to heap area

        SET_ARITY(arg3,arg2);     //set sort key atom
        if(record_pt >= RECORDMAX)
            error(RECORD_OVERF,"recordh ",NIL);
        if(GET_ARITY(arg1) == NIL){
            SET_ARITY(arg1,record_pt);
            record_pt++;
        }
        record_id = GET_ARITY(arg1)-1; //id starts from 1
        index = hash(GET_NAME(arg2));
        add_hash_pred(arg3,record_id,index);
        checkgbc();
        return(YES);
    }
    return(NO);
}

int b_retrieveh(int arglist, int rest){
    int n,arg1,arg2,arg3,save1,record_id,index,lis,term;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"retrieveh ", arg1);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"retrieveh ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"retrieveh ", arg2);
        if(!wide_variable_p(arg2) && !atomp(arg2))
            error(NOT_ATOM,"retrieveh ",arg2);
    
        
        save1 = sp;
        record_id = GET_ARITY(arg1)-1; //id starts from 1
        if(record_id < 0)
            error(NOT_RECORD,"retrieveh ",arg1);
        index = hash(GET_NAME(arg2));
        lis = record_hash_table[index][record_id];
        while(lis != NIL){
            term = car(lis);
            if(GET_ARITY(term) != arg2)
                goto skip;

            unify(arg3,term);
            if(prove_all(rest,sp,0) == YES)
                return(YES);
            
            unbind(save1);
            skip:
            lis = cdr(lis);
        }
        return(NO);
    }
    return(NO);
}


int b_instance(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"instance ", arg1);
        if(!wide_variable_p(arg1) && !integerp(arg1))
            error(NOT_INT,"instance ",arg1);

        return(unify(arg2,get_int(arg1)));
    }
    return(NO);
}


int b_recordz(int arglist, int rest){
    int n,arg1,arg2,arg3,temp;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);   //key
        arg2 = cadr(arglist);  //term
        arg3 = caddr(arglist); //ref 

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"recordz ",arg1);
        if(builtinp(arg1))
            error(BUILTIN_EXIST,"recordz ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"recordz ",arg2);
        if(!termp(arg2))
            error(NOT_TERM,"recordz ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"recordz ",arg3);

        arg2 = cons(car(arg2),cons(arg1,cdr(arg2))); //insert key to term
        arg2 = copy_heap(arg2); //copy arg1 to heap area
        temp = record_list;
        if(temp == NIL)
            temp = cons(arg2,NIL);
        else{
            while(cdr(temp) != NIL){
                temp = cdr(temp);
            }
            SET_CDR(temp,cons(arg2,NIL));
        }
        checkgbc();
        return(unify(arg3,makeint(arg2)));
    }
    return(NO);
}

int b_recorda(int arglist, int rest){
    int n,arg1,arg2,arg3;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"recorda ",arg1);
        if(builtinp(arg1))
            error(BUILTIN_EXIST,"recorda ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"recorda ",arg2);
        if(!termp(arg2))
            error(NOT_TERM,"recorda ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"recorda ",arg3);

        arg2 = cons(car(arg2),cons(arg1,cdr(arg2))); //insert key to term
        arg2 = copy_heap(arg2); //copy arg1 to heap area
        record_list = cons(arg2,record_list);
        checkgbc();
        return(unify(arg3,makeint(arg2)));
        
    }
    return(NO);
}


int b_removeh(int arglist, int rest){
    int n,arg1,arg2,arg3,save1,record_id,index,lis,prev,term;

    n = length(arglist);
    if(n == 3){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        arg3 = caddr(arglist);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"remove ", arg1);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"remove ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"remove ", arg2);
        if(!wide_variable_p(arg2) && !atomp(arg2))
            error(NOT_ATOM,"remove ",arg2);
    
        
        save1 = sp;
        record_id = GET_ARITY(arg1)-1; //id starts from 1
        if(record_id < 0)
            error(NOT_RECORD,"remove ",arg1);
        index = hash(GET_NAME(arg2));
        repeat:
        lis = record_hash_table[index][record_id];
        prev = NIL;
        while(lis != NIL){
            term = car(lis);
            if(GET_ARITY(term) != arg2)
                goto skip;

            if(unify(arg3,term)){
                if(prev != NIL)
                    SET_CDR(prev,cdr(lis)); // delete unified term
                else
                    record_hash_table[index][record_id] = cdr(lis); 
                    // if term is first one of list, set hashtable cdr of lis
                if(prove_all(rest,sp,0) == YES)
                    return(YES);
            }
            unbind(save1);
            if(prev == NIL)
                goto repeat;
            skip:
            lis = cdr(lis);
            prev = lis;
        }
        return(NO);
    }
    return(NO);
}

int b_removeallh(int arglist, int rest){
    int n,arg1,record_id,i;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        record_id = GET_ARITY(arg1)-1;
        SET_ARITY(arg1,NIL);
        for(i=0;i<HASHTBSIZE;i++)
            record_hash_table[i][record_id] = NIL;
        //as a result, removed term will be retrieve by GC
        return(YES);
    }
    return(NO);
}

int b_ref(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);

        if(!integerp(arg1))
            error(NOT_INT,"resf ",arg1);
        
        if(predicatep(GET_INT(arg1)))
            return(YES);
        else 
            return(NO);
    }
    return(NO);
}