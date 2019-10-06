/* O-Prolog
written by kenichi sasagawa 2016/8~
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <math.h>
#if __linux
#include <stdio_ext.h>
#endif
#include "opl.h"

//global vers
int proof = 0;
cell heap[CELLSIZE];
int variant[VARIANTSIZE][2];
int stack[STACKSIZE];
//0=arity-count 1=name-symbol 2-17=arity
//row=0 predicate for unify row>=1 trail predicate
int goal[ARITY];
int head[ARITY];
int trail[TRAILSIZE][ARITY];
int store[TRAILSIZE][ARITY];
int store1[100][ARITY][10]; //for repeat/0 for between/3
int store_pt = 0;
int numbervars[20][3]; // for numbervars  variable,numbervars and it's count
int numbervars_base_pt = 0; // for numbervars
int numbervars_top_pt  = 0; // for numbervars
token stok = {GO,OTHER};
jmp_buf buf;
jmp_buf catch_buf[CTRLSTKSIZE];
int catch_dt[CTRLSTKSIZE][5];
int catch_pt = 0;
int cell_hash_table[HASHTBSIZE];
int variables = NIL;
int predicates = NIL;
int spy_list = NIL;
int findall_list[10];
int findall_pt = 0;
int bagof_list = NIL;
int checked_var = NIL; //for bagof_help
int checking_var = NIL; //for bagof_help
int load_list = NIL;
int dynamic_list = NIL;
int reconsult_list = NIL;
int init_list = NIL;    //initialization/1
int contiguous_list = NIL;    //for contiguous check
int discontiguous_list = NIL; //discontiguous/1
int op_list = NIL; //current_op/3
int flag_list = NIL; //for current_prolog_flag, set_prolog_flag
int define_list = NIL;  //for c_define/2
int include_list = NIL; //for c_iinclude/1
int option_list = NIL;  //for c_option/1
int global_list = NIL;  //for c_global/1
int execute_list;     //for compiler. o_get_execution/1
int unread = NIL;     //for parse
int paren_nest = 0;   //for parse check ((()))
int line;
int column;
int trail_end;  //for comiler. get end of trail point
double micro_second;
p_cut1 cut_function[2]; // for compiled code o_cut !
                        // cut_function[0] <- cut_pt = 0
                        // cut_function[1] <- longjmp(cut_buf[cut_pt],1);
int module[10][2];
int module_pt = 0;
int module_name = NIL;
int export_list = NIL;
int meta_list = NIL;
int context = NIL;
int cleanup_dt = NIL;  //for setup_call_clean_up. when error invokde

//------pointer----
int hp; //heap pointer
int sp; //stack pointer
int fc; //free counter
int ac; //alpha conversion variable counter
int cp; //cut point
int tp; //trail stack pointer
int wp; //working pointer


//flag
int trace_flag = 0;
int trace_nest = 999999999; //max nest level of trace
int open_flag = 0;
int gbc_flag = 0;  // 0=not display massage 1=display message
int simp_flag = 1;
int assert_flag = 0; // 0=asserta, 1=assertz
int debug_flag = 0;  // 0=normal mode, 1=debug mode
int sexp_flag = 0;
int arguments_flag = 1; //1= 1,2,3 -> (1,2,3) 0= 1,2,3 -> 1,2,3
int undefined_flag = 1; //0=fail, 1=error, 2=warning
int double_flag = 1; //0=code, 1=char, 2=string for string
#if _WIN32
int mode_flag = 0;  // 0=SJIS, 1=Unicode
#elif __linux
int mode_flag = 1;  // 0=SJIS, 1=Unicod
#elif __OpenBSD__
int mode_flag = 1;  // 0=SJIS, 1=Unicod
#endif
int quoted_flag = 1; // 0=not print ' 1=print '
int ignore_flag = 0; // 0=infix notation 2+2 1=prefix notation +(2,2)
int numbervars_flag = 0; // 0=normal 1= A -> '_0001
int link_flag = 0;  // 0=not-link, 1=linked
int rounding_flag = 0; //0 = toward_zero, 1=down
int cut_flag = 0;  //for if then else 0=not exist cut, 1=exist cut
int listing_flag = 0;  //for print clause, 0=normal, 1=format print
int colon_sets_calling_context_flag = 1; //1=true, 0=false
int prefix_flag = 0;   //for parser 0=not prefix, 1=prefix
double time_flag = 0;   //for time/1 0=normal, not 0(start time)=print elapsed time


//operator token
char operator[OPERATOR_NUMBER][5] = {
{":-"},{"-->"},{","},{";"},{"?-"},{"."},
{"+"},{"-"},{"*"},{"/"},{"//"},{"<<"},{">>"},{"\\"},{"/\\"},{"\\/"},
{"mod"},{"rem"},{"^"},{"**"},{"xor"},{"iand"},
};

char function[FUNCTION_NUMBER][12] = {
{"abs"},{"sin"},{"cos"},{"tan"},{"asin"},{"acos"},{"atan"},
{"exp"},{"log"},{"floor"},{"ceiling"},{"truncate"},
{"sign"},{"sqrt"},{"round"},{"gcd"},{"lcm"},
{"random"},{"random_real"},
};


//builtin token
char builtin[BUILTIN_NUMBER][30] = {
{"->"},{"=.."},{"\\+"},{"@"},{":"},
{"=="},{"\\=="},{"@<"},{"@=<"},{"@>"},{"@>="},
{"=:="},{"=/="},{"=\\="},{"<"},{"=<"},{">"},
{">="},{"\\="},{"="},{"reverse"},
{"is"},{"edit"},{"set_editor"},{"open"},{"close"},{"system"},
{"op"},{"!"},{"assert"},{"asserta"},{"assertz"},{"retractall"},
{"abolish"},{"read"},{"write"},{"put"},{"get"},{"get0"},{"nl"},
{"tab"},{"fail"},{"not"},{"true"},{"halt"},{"abort"},
{"listing"},{"functor"},{"arg"},{"debug"},{"write_canonical"},
{"writeq"},{"write_term"},{"read_term"},{"bounded"},{"integer_rounding_function"},
{"char_conversion"},{"max_arity"},{"fail_if"},
{"atom_length"},{"findall"},{"consult"},{"reconsult"},
{"see"},{"seen"},{"tell"},{"told"},{"trace"},{"notrace"},{"spy"},
{"nospy"},{"atom"},{"integer"},{"real"},{"float"},{"number"},{"compound"},
{"var"},{"nonvar"},{"atomic"},{"list"},{"gbc"},{"time"},
{"char_set"},{"char_code"},{"atom_chars"},{"atom_codes"},{"name"},
{"number_chars"},{"number_codes"},{"debug"},{"bounded"},{"max_arity"},
{"undefined_predicate"},{"discontiguous"},
{"findall"},{"ensure_loaded"},{"dynamic"},
{"module"},{"export"},{"import"},{"end_module"},{"end_body"},{"body"},
{"reexprt"},{"meta"},{"calling_context"},
{"catch"},{"throw"},{"get_char"},{"get_code"},{"put_char"},{"put_code"},
{"current_input"},{"current_output"},{"unify_with_occurs_check"},
{"set_input"},{"set_output"},{"flush_output"},{"listreverse"},{"nano"},
{"numbervars"},{"retractall"},{"get_byte"},
{"string"},{"string_chars"},{"string_codes"},{"ground"},
{"put_byte"},{"predicate_property"},{"set_prolog_flag"},
{"succ"},{"term_variables"},{"use_module"},{"compare"},{"freeze"},
{"make_directory"},{"directory_exists"},{"current_directory"},
{"expand_path"},{"delete_file"},{"file_exists"},{"decompose_file_name"},
{"environment_variable"},{"file_modification_time"},
{"server_create"},{"server_accept"},{"client_connect"},{"socket_send"},
{"socket_recieve"},{"socket_close"},{"sort"},{"keysort"},
{"c_lang"},{"c_define"},{"c_include"},{"c_option"},{"c_global"},
{"o_include_cut"},{"o_has_cut"},{"o_c_define"},{"o_c_include"},
{"o_c_option"},{"o_c_global"},{"o_clause_with_arity"},
{"o_variable_convert"},{"o_filename"},{"o_arity_count"},
{"o_reconsult_predicate_list"},{"o_defined_predicate"},
{"o_is"},{"o_compiler_anoymous"},
{"o_compiler_variable"},{"o_generate_variable"},{"o_generate_all_variable"},
{"o_self_introduction"},{"o_dynamic_check"},{"o_get_dynamic"},
{"o_get_execute"},{"o_write_original_variable"},{"o_atom_convert"},
{"o_generate_before_cut"},{"o_generate_after_cut"},{"o_generated_module"},
{"o_argument_list"},{"o_decompose"},{"o_property"},
{"o_has_c_lang"},{"o_generate_before_c_lang"},{"o_generate_after_c_lang"},
};

//compiled predicate
char compiled[COMPILED_NUMBER][30] ={
{"append"},{"member"},{"repeat"},{"select"},{"maplist"},
{"retract"},{"clause"},{"current_predicate"},
{"current_prolog_flag"},{"current_op"},{"current_module"},
{"current_visible"},{"stream_property"},{"between"},
{"bagof"},{"setof"},{"sub_atom"},{"atom_concat"},{"length"},
{"call"},{"setup_call_cleanup"},{"o_reconsult_predicate"},
};

//extened predicate
char extended[EXTENDED_NUMBER][30] = {
{"wiringpi_setup_gpio"},{"wiringpi_spi_setup"},{"pwm_set_mode"},
{"pwm_set_clock"},{"pwm_set_range"},{"pin_mode"},{"digital_write"},
{"pwm_write"},{"pull_up_dn_control"},{"digital_read"},{"delay"},
{"compile_file"},
};


//stream
int standard_input;
int standard_output;
int standard_error;
int input_stream;
int output_stream;
int error_stream;

#if defined(__linux) || defined(__OpenBSD__)
//-----editor-----
int repl_flag = 1;  //for REPL read_line 1=on, 0=off
int buffer[256][10];
int ed_row;
int ed_col;
int ed_start;
int ed_end;
int ed_ins = 1;
int ed_tab = 4;
int ed_indent = 0;
int ed_name = NIL;
char ed_data[1000][80];
char ed_copy[500][80];
int ed_lparen_row;
int ed_lparen_col;
int ed_rparen_row;
int ed_rparen_col;
int ed_lbracket_row;
int ed_lbracket_col;
int ed_rbracket_row;
int ed_rbracket_col;
int ed_clip_start;
int ed_clip_end;
int ed_copy_end;
char ed_candidate[15][30];
int ed_candidate_pt;
int ed_operator_color = 3;   //default yellow
int ed_builtin_color = 6;  //default cyan
int ed_extended_color = 1; //default red
int ed_quote_color = 3;   //default yellow
int ed_comment_color = 4;  //default blue
int ed_function_color = 2; //default green
int ed_incomment = -1; /*...*/
#endif


int main(int argc, char *argv[]){
    int opt;

    printf("O-Prolog Ver 1.72\n");
    initcell();
    initbuiltin();
    initoperator();
    initstream();
    input_stream = standard_input;
    output_stream = standard_output;
    error_stream = standard_error;
    opt = 1;
    init_repl();

    FILE* fp = fopen("startup.pl","r");
    if(fp != NULL){
        fclose(fp);
        goal[2] = makeconst("startup.pl");
        b_consult(0,1);
        predicates = NIL;
    }
    while(opt < argc){
        if(strcmp(argv[opt],"-c") == 0){
            opt++;
            FILE* fp = fopen(argv[opt],"r");
            if(fp != NULL)
                fclose(fp);
            else{
                printf("Not exist %s\n", argv[opt]);
                break;
            }
            goal[2] = makeconst(argv[opt]);
            b_consult(0,1);
            opt++;
        }
        #if __linux
        else if(strcmp(argv[opt],"-r") == 0){
            repl_flag = 0;
            opt++;
        }
        #endif
        else{
            printf("Wrong option %s\n", argv[opt]);
            printf("-c consult prolog code\n");
            printf("-r off repl mode (only Linux)\n");
            return(0);
        }
    }
    int ret = setjmp(buf);
    repl:
    if(ret == 0)
        while(1){
            input_stream = standard_input;
            output_stream = standard_output;
            error_stream = standard_error;
            init_repl();
            printf("| "); fflush(stdout);
            execute(variable_to_call(readparse()));
            //sexp_flag = 1;print(variable_to_call(parser(NIL,NIL,NIL,NIL,0,0)));
            //printf("proof = %d\n", proof);
            fflush(stdout);
        }
    else
        if(ret == 1){
            ret = 0;
            goto repl;
        }
        else
            return 0;
}

void init_repl(void){
    int i;

    stok.flag = GO;
    proof = 0;
    ac = CELLSIZE+1;
    wp = HEAPSIZE+1;
    unbind(0);
    sp = 0;
    tp = 0;
    trail_end = 0;
    cut_flag = 0;
    store_pt = 0;
    findall_pt = 0;  //findall/3
    checked_var = NIL; //bagof/3
    checking_var = NIL; //bagof/3
    catch_pt = 0;
    cleanup_dt = NIL;
    numbervars_top_pt = 0;
    numbervars_base_pt = 0;
    //initialize variant variable
    for(i=0; i<VARIANTSIZE; i++){
        variant[i][0] = UNBIND;
        variant[i][1] = UNBIND;
    }
    i = variables;
    while(!nullp(i)){
        SET_CAR(car(i),UNBIND);
        SET_CDR(car(i),UNBIND);
        i = cdr(i);
    }

}

void execute(int x){
    int atom;

    if((builtinp(x) || compiledp(x)) &&
       !(structurep(x) && car(x) == COLON))
        error(BUILTIN_EXIST,"assertz",x);

    if(atomp(x)){
        SET_AUX(x,PRED);
        if(module_name != NIL)
            x = add_prefix(x);
        add_data(x,x);
        return;
    }
    if(predicatep(x)){
        if(module_name != NIL)
            x = add_prefix(x);
        if(atomp(x))
            atom = x;
        else
            atom = car(x);
        memoize_arity(x,atom);
        SET_VAR(x,unique(varslist(x)));
        set_length(x);
        add_data(car(x),x);
        return;
    }
    if(user_operation_p(x)){
        if(module_name != NIL)
            x = add_prefix(x);
        if(atomp(cadr(x)))
            atom = cadr(x);
        else
            atom = car(cadr(x));
        SET_VAR(x,unique(varslist(x)));
        set_length(x);
        add_data(car(x),x);
        return;
    }
    else if(operationp(x)){
        operate(x);
        return;
    }
    else if(colonp(x)){
        // (: atom pred(t1)) -> atom_pred(t1)
        if(atomp(caddr(x)))
            x = cons(concat_atom(cadr(x),caddr(x)),cdr(caddr(x)));
        else
            x = cons(concat_atom(cadr(x),car(caddr(x))),cdr(caddr(x)));
        if(atomp(x))
            atom = x;
        else
            atom = car(x);
        memoize_arity(x,atom);
        SET_VAR(x,unique(varslist(x)));
        set_length(x);
        add_data(car(x),x);
        return;
    }
    error(SYNTAX_ERR,"execute ",x);
}

int resolve_all(int end, int bindings, int n){
    trail_end = end;
    if(tp <= end)
        return(YES);
    else
        return(resolve(end,bindings,tp-1,n+1));
}

int resolve(int end, int bindings, int choice, int n){
    int clause,clauses,varlis,save1,save2,save3,save4,save5,temp;

    proof++;
    checkgbc();
    #if _WIN32
    if(n > 250000)
        error(RESOURCE_ERR,"resolve ",NIL);

    #elif __linux
    if(n > 150000)
        error(RESOURCE_ERR,"resolve ",NIL);
    #endif
    store_goal(n);
    trail_end = end;
    if((trace_flag == FULL && n < trace_nest) ||
       (trace_flag == SPY && aritycheck(goal[1],goal[0]))){
        if(goal[1] != OR){ //normal predicate
            printf("(%d) CALL: ", n); print_goal();
        }
        else{ // or disjunction
            printf("(%d) CALL: ;(",n);
            sprint(goal[2]);
            printf(",");
            sprint(goal[3]);
            printf(")");
        }
        debugger(end,bindings,choice,n);
    }
    //builtin
    if(GET_AUX(goal[1]) == SYS){
        save1 = tp;
        save2 = trail_end;
        if((GET_SUBR(goal[1]))(0,goal[0] - 1) == YES)
            if(resolve_all(end,sp,n+1) == YES)
                return(YES);

        tp = save1;
        trail_end = save2;
        retract_goal(n);
        unbind(bindings);
        return(NO);
    }
    //compiled
    else if(GET_AUX(goal[1]) == COMP){
        if((GET_SUBR(goal[1]))(n, goal[0]-1) == YES)
            return(YES);

        retract_goal(n);
        return(NO);
    }
    //compiled user operation
    else if(GET_AUX(goal[1]) == USER &&
            getatom(GET_NAME(goal[1]),COMP,hash(GET_NAME(goal[1]))) != 0){

        if((GET_SUBR(makecomp(GET_NAME(goal[1]))))(n, goal[0]-1) == YES)
            return(YES);

        retract_goal(n);
        return(NO);
    }
    //predicate
    else if(GET_AUX(goal[1]) == PRED ||
            GET_AUX(goal[1]) == USER){
        clauses = GET_CAR(goal[1]);
        // when not defined clause or not match arity
        // invoke error or return NO or warning according to flag
        if(clauses == NIL ||
           !memq(makeint(goal[0]-1),GET_ARITY(goal[1]))){
            if(undefined_flag == 0)
    			      return(NO);
            else if(GET_OPT1(goal[1]) == NO)
                return(NO);
    		    else if(undefined_flag == 1)
    			      error(UNDEF_PRED,"resolve",NIL);
    		else if(undefined_flag == 2){
    		    printf("Warning: undefined predicate ");
        		print_goal();
            printf("\n");
        		return(NO);
    		    }
        }
        while(!nullp(clauses)){
            save5 = wp;
            clause = car(clauses);
            clauses = cdr(clauses);
            varlis = GET_VAR(clause);
            if(predicatep(clause)){
                assign_variant(varlis);
                set_head(clause);
                release_variant(varlis);
                if(unify_head() == YES){
                    if(trace_flag == FULL && !nullp(clauses) &&
                       n < trace_nest){
                        printf("(%d) EXIT: ",n); print_goal();
                        debugger(end,bindings,choice,n);
                    }
                    if((temp=resolve_all(end,sp,n+1)) == YES)
                        return(YES);
                    else if(temp == CUT)
                        goto cut;
                }
            }
            else{
                assign_variant(varlis);
                set_head(cadr(clause));
                if(unify_head() == YES){
                    if(GET_OPT(clause) != HASCUT){
                        push_trail_body(caddr(clause));
                        release_variant(varlis);
                        if(resolve_all(end,sp,n+1) == YES){
                            if(trace_flag == FULL && n < trace_nest){
                                printf("(%d) EXIT: ",n); print_goal();
                                debugger(end,bindings,choice,n);
                            }
                            return(YES);
                        }
                        else if(cut_flag == 1 && GET_OPT1(clause) == HASIFTHEN){
                            cut_flag = 0;
                            tp = choice;
                            retract_goal(n);
                            unbind(bindings);
                            goto cut;
                        }
                        else if(cut_flag == 1){
                            tp = choice;
                            retract_goal(n);
                            unbind(bindings);
                            goto cut;
                        }
                    }
                    //clause has a cut
                    else{
                        save1 = tp;
                        save2 = memory_variant(varlis);
                        push_trail_body(before_cut(caddr(clause)));
                        release_variant(varlis);
                        if(resolve_all(save1,sp,n+1) == YES){
                            recall_variant(save2);
                            push_trail_body(after_cut(caddr(clause)));
                            release_variant(varlis);
                            if(resolve_all(end,sp,n+1) == YES){
                                if(trace_flag == FULL && n < trace_nest){
                                    printf("(%d) EXIT: ",n); print_goal();
                                    debugger(end,bindings,choice,n);
                                }
                                return(YES);
                            }
                            else if(cut_flag == 1 && GET_OPT1(clause) == HASIFTHEN){
                                cut_flag = 0;
                                tp = choice;
                                retract_goal(n);
                                unbind(bindings);
                                goto cut;
                            }
                            else if(cut_flag == 1){
                                tp = choice;
                                retract_goal(n);
                                unbind(bindings);
                                goto cut;
                            }
                            else{
                                tp = choice;
                                trail_end = end;
                                retract_goal(n);
                                unbind(bindings);
                                goto cut;
                            }
                        }
                    }
                }
            }
            if(trace_flag == FULL && !nullp(clauses) && n < trace_nest){
                printf("(%d) REDO: ",n); sprint(car(clauses));
                debugger(end,bindings,choice,n);
            }
            tp = choice;
            retract_goal(n);
            unbind(bindings);
            wp = save5;
        }// end of while loop
        cut:
        if(trace_flag == FULL && n < trace_nest){
            printf("(%d) FAIL: ",n); print_goal();
            printf("cut_flag %d" ,cut_flag);
            debugger(end,bindings,choice,n);
        }
        if(cut_flag == 0)
            return(NO);
        else
            return(CUT);
    }
    //disjunction
    else if(goal[1] == OR){
        save1 = tp;
        save2 = trail_end;
        save3 = goal[2];
        save4 = goal[3];
        if(!has_cut_p(save3)){
            if(!ifthenp(save3)){
                if(!callablep(save3))
                    error(NOT_CALLABLE, "; ", save3);
                push_trail_body1(save3);
                trail_end = save2;
                if(resolve_all(end,sp,n+2) == YES)
                    return(YES);
                else{
                    tp = choice;
                    unbind(bindings);
                    trail_end = end;
                    retract_goal(n);
                }
            }
            else{// case of if_then(->)
                push_trail_body1(save3);
                if(resolve_all(save1,sp,n+1) == YES){
                    trail_end = save2;
                    retract_goal(n);
                    if(resolve_all(end,sp,n+2) == YES)
                        return(YES);
                    else{
                        tp = choice;
                        unbind(bindings);
                        trail_end = end;
                        retract_goal(n);
                        if(cut_flag == 0)
                            return(NO); //not back track when if_then
                        else
                            return(CUT);
                    }
                }
                /*
                else{
                    if(cut_flag == 1){
                        cut_flag = 0;
                        tp = choice;
                        unbind(bindings);
                        trail_end = end;
                        retract_goal(n);
                        return(NO); //not back track when if_then
                    }
                }
                */
            }
        }
        else{
            push_trail_body1(before_cut(save3));
            if(resolve_all(save1,sp,n+1) == YES){
                trail_end = save2;
                push_trail_body1(after_cut(save3));
                trail_end = save2;
                if(resolve_all(save1,sp,n+2) == YES){
                    trail_end = save2;
                    retract_goal(n);
                    if(resolve_all(end,sp,n+3) == YES)
                        return(YES);
                    else{
                        tp = choice;
                        unbind(bindings);
                        trail_end = end;
                        retract_goal(n);
                        return(NO);
                    }
                }
                else{
                    tp = choice;
                    trail_end = end;
                    retract_goal(n);
                    unbind(bindings);
                    goto cut;
                }
            }
        }
        unbind(bindings);
        tp = save1;
        if(!has_cut_p(save4)){
            if(!callablep(save4))
                    error(NOT_CALLABLE, "; ", save4);
            push_trail_body1(save4);
            trail_end = save2;
            if(resolve_all(end,sp,n+2) == YES)
                return(YES);
        }
        else{
            cut_flag = 1;
            push_trail_body1(before_cut(save4));
            if(resolve_all(save1,sp,n+1) == YES){
                trail_end = save2;
                push_trail_body1(after_cut(save4));
                trail_end = save2;
                if(resolve_all(save1,sp,n+2) == YES){
                    trail_end = save2;
                    if(resolve_all(end,sp,n+3) == YES)
                        return(YES);
                }
                else{
                    tp = choice;
                    trail_end = end;
                    retract_goal(n);
                    unbind(bindings);
                    goto cut;
                }
            }
        }
        tp = save1;
        trail_end = save2;
        retract_goal(n);
        unbind(bindings);
        if(trace_flag == FULL && n < trace_nest){
            printf("(%d) FAIL: ",n);sprint(save3), sprint(save4);
            debugger(end,bindings,choice,n);
        }
        return(NO);
    }
    return(NO);
}

int before_cut(int x){
    return(before_cut1(x,NIL));
}

int before_cut1(int x, int y){
    int temp1,temp2;

    if(nullp(x))
        return(NO);
    else if(x == CUT)
        return(y);
    else if(car(x) == AND && cadr(x) == CUT)
        return(y);
    else if(car(x) == AND && caddr(x) == CUT)
        return(addtail_operation(cadr(x),y));
    else if(predicatep(x) || builtinp(x) || compiledp(x))
        return(NO);
    else if(operationp(cadr(x))){
        temp1 = before_cut1(cadr(x),y);
        if(temp1 == NO)
            return(before_cut1(caddr(x),addtail_operation(cadr(x),y)));
        else{
            temp2 = before_cut1(caddr(x),temp1);
            if(temp2 == NO)
                return(temp1);
            else
                return(temp2);
        }
    }
    else
        return(before_cut1(caddr(x),addtail_operation(cadr(x),y)));
    return(x);
}

int addtail_operation(int x, int y){
    if(nullp(y))
        return(x);
    else if(!operationp(y))
        return(list3(AND,y,x));
    else
        return(list3(car(y),cadr(y),addtail_operation(x,caddr(y))));
}

int after_cut(int x){
    int temp1,temp2;

    if(x == CUT)
        return(NIL);
    else if(predicatep(x) || builtinp(x) || compiledp(x))
        return(NO);
    else if(car(x) == AND && cadr(x) == CUT){
        temp1 = after_cut(caddr(x));
        if(temp1 == NO)
            return(caddr(x));
        else
            return(temp1);
    }
    else if(operationp(cadr(x))){
        temp1 = after_cut(cadr(x));

        if(temp1 == NO)
            return(after_cut(caddr(x)));
        else{
            temp2 = after_cut(caddr(x));
            if(temp2 == NO)
                return(addtail_operation(caddr(x),temp1));
            else
                return(temp2);
        }
    }
    else if(car(x) == AND)
        return(after_cut(caddr(x)));
    else if(car(car(x)) == OR)
        return(x);
    return(x);
}

#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif __OpenBSD__
#define FLUSH fpurge(stdin);
#else
#define FLUSH __fpurge(stdin);
#endif
void debugger(int end, int bindings, int choice, int n){
    int c;

    loop:
    printf("?>");
    fflush(stdout);
    c = getchar();
    FLUSH
    switch(c){
        case EOL:   trace_flag = FULL;
                    break;
        case 'a':   FLUSH
                    longjmp(buf,1);
        case 'c':   trace_flag = FULL;
                    FLUSH
                    break;
        case 'd':   print_goal();
                    FLUSH
                    goto loop;
        case 'e':   longjmp(buf,2);
        case '?':
        case 'h':   printf("return key: creep\n");
                    printf("a: abort to REPL\n");
                    printf("c: creep\n");
                    printf("d: display goal\n");
                    printf("e: end of intepreter\n");
                    printf("?: help\n");
                    printf("h: help\n");
                    printf("l: display local stack\n");
                    printf("n: notrace\n");
                    printf("s: skip to next spy point\n");
                    printf("r: dislay room information\n");
                    printf("t: display trail stack\n");
                    printf("1~9: set trace nest level\n");
                    printf("0: release trace nest level\n");
                    fflush(stdin);
                    goto loop;
        case 'n':   trace_flag = OFF;
                    break;
        case 'r':   printf("end      %d\n",end);
                    printf("bindings %d\n", bindings);
                    printf("choice   %d\n", choice);
                    printf("nest     %d\n", n);
                    printf("tp       %d\n", tp);
                    printf("sp       %d\n", sp);
                    printf("wp       %d\n", wp);
                    goto loop;
        case 's':   trace_flag = SPY;
                    FLUSH
                    break;
        case 't':   print_trail_block(tp);
                    goto loop;
        case 'l':   print_stack();
                    goto loop;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':   trace_nest = c - '0';
                    goto loop;
        case '0':   trace_nest = 999999999;
    }
}


int varslist(int addr){
    if(nullp(addr))
        return(NIL);
    else if(variablep(addr))
        return(cons(addr,NIL));
    else if(!structurep(addr))
        return(NIL);
    else if(variablep(car(addr)))
        return(cons(car(addr),varslist(cdr(addr))));
    else if(structurep(addr) && car(addr) == AND)
        return(append(varslist(cadr(addr)),
                      varslist(caddr(addr))));
    else if(structurep(addr) && car(addr) == OR)
        return(append(varslist(cadr(addr)),
                      varslist(caddr(addr))));
    else if(!structurep(car(addr)))
        return(varslist(cdr(addr)));
    else
        return(append(varslist(car(addr)),
                      varslist(cdr(addr))));
}

int valslist(int x){
    if(nullp(x))
        return(NIL);
    else
        return(cons(cons(car(x),deref1(car(x))),valslist(cdr(x))));
}


int operate(int x){
    int operator,operand1,operand2;

    operator = car(x);
    operand1 = cadr(x);
    operand2 = caddr(x);
    return((GET_SUBR(operator))(operand1, operand2));
}

int walpha_conversion(int x){
    int temp;

    if(nullp(x))
        return(NIL);
    else if(alpha_variable_p(x))
    	return(x);
    else if(anoymousp(x))
        return(makevariant());
    else if(variablep(x))
        return(GET_CDR(x));
    else if(!structurep(x))
        return(x);
    else if(operationp(x) && nullp(caddr(x))){ // e.g. :- foo(x)
        temp = wlist2(car(x),walpha_conversion(cadr(x)));
        SET_AUX(temp,GET_AUX(x));
    	return(temp);
    }
    else if(operationp(x)){
        temp = wlist3(car(x),
                     walpha_conversion(cadr(x)),
                     walpha_conversion(caddr(x)));
        SET_AUX(temp,GET_AUX(x));
    	return(temp);
    }
    else if(listp(x)){
        temp = wcons(walpha_conversion(car(x)),
                     walpha_conversion(cdr(x)));
        SET_AUX(temp,GET_AUX(x));
    	return(temp);
    }
    else if(predicatep(x)){
        temp = wcons(car(x),
                     walpha_conversion(cdr(x)));
        SET_AUX(temp,GET_AUX(x));
        return(temp);
    }
    else{ //buiiltin
        temp = wcons(walpha_conversion(car(x)),
                     walpha_conversion(cdr(x)));
        SET_AUX(temp,GET_AUX(x));
        return(temp);
    }
}

int anoymous_conversion(int x){
    int temp;

    if(nullp(x))
        return(NIL);
    else if(alpha_variable_p(x))
    	return(x);
    else if(anoymousp(x))
        return(makevariant());
    else if(variablep(x))
        return(x);
    else if(!structurep(x))
        return(x);
    else if(operationp(x) && nullp(cdr(x)))
        return(x);
    else if(operationp(x) && nullp(caddr(x))){ // e.g. :- foo(x)
        temp = list2(car(x),anoymous_conversion(cadr(x)));
        SET_AUX(temp,GET_AUX(x));
    	return(temp);
    }
    else if(operationp(x)){
        temp = list3(car(x),
                     anoymous_conversion(cadr(x)),
                     anoymous_conversion(caddr(x)));
        SET_AUX(temp,GET_AUX(x));
    	return(temp);
    }
    else if(listp(x)){
        temp = cons(anoymous_conversion(car(x)),
                    anoymous_conversion(cdr(x)));
        SET_AUX(temp,GET_AUX(x));
    	return(temp);
    }
    else if(predicatep(x)){
        temp = cons(car(x),
                    anoymous_conversion(cdr(x)));
        SET_AUX(temp,GET_AUX(x));
        return(temp);
    }
    else{ //buiiltin
        temp = cons(anoymous_conversion(car(x)),
                    anoymous_conversion(cdr(x)));
        SET_AUX(temp,GET_AUX(x));
        return(temp);
    }
}

//-----print------------------
//output to standard output
void sprint(int addr){
    int save;

    save = output_stream;
    output_stream = standard_output;
    print(addr);
    output_stream = save;
}

//for answer unified variable
void printanswer(int addr){
    if(operatorp(addr)){
        printc('(');
        print(addr);
        printc(')');
    }
    else if(atom_quote_p(addr)){
        print_quoted(addr);
    }
    else if(argumentsp(addr) && !ignore_flag && arguments_flag){
        fprintf(GET_PORT(output_stream),"(");
        printarguments(addr);
    }
    else if(operationp(addr) &&
            heavy999p(car(addr))){ // e.g (a :- b)
        fprintf(GET_PORT(output_stream),"(");
        print(addr);
        fprintf(GET_PORT(output_stream),")");
    }
    else if(builtinp(addr)){
        fprintf(GET_PORT(output_stream),"(");
        print(addr);
        fprintf(GET_PORT(output_stream),")");
    }
    else
        print(addr);
}

//output to output_stream
void print(int addr){
    double x;
    int i;

    if(IS_ALPHA(addr)){
        fprintf(GET_PORT(output_stream),"v_%d", addr-CELLSIZE);
        return;
    }
    switch(GET_TAG(addr)){
        case INTN:  fprintf(GET_PORT(output_stream),"%d", GET_INT(addr)); break;
        case FLTN:  x = GET_FLT(addr);
                    if(x - trunc(x) != 0.0)
                        fprintf(GET_PORT(output_stream),"%0.16g", x);
                    else
                        fprintf(GET_PORT(output_stream),"%0.1f", x);
                    break;
        case LONGN: printlong(addr); break;
        case BIGX:  print_bigx(addr); break;
        case SINGLE:
                    if(addr == NIL)
                        fprintf(GET_PORT(output_stream),"[]");
                    else if(variablep(addr)){
                        if(!numbervars_flag)
                            fprintf(GET_PORT(output_stream),"%s", GET_NAME(addr));
                        else{
                            for(i=0;i<numbervars_top_pt;i++)
                                if(numbervars[i][0] == i){
                                    fprintf(GET_PORT(output_stream),"_%04d", i+1);
                                    break;
                                }

                            numbervars[numbervars_top_pt][0] = addr;
                            numbervars_top_pt++;
                            fprintf(GET_PORT(output_stream),"_%04d", i+1);
                        }
                    }
                    else if(quoted_flag && atom_quote_p(addr))
                        print_quoted(addr);
                    else
                        print_not_quoted(addr);
                    break;
        case STRUCT:
                    if(sexp_flag){
                        fprintf(GET_PORT(output_stream),"(");
                        printsexp(addr);
                    }
                    else if(postfixp(addr)){
                        if(!ignore_flag)
                            printpostfix(addr);
                        else{
                            print(car(addr));
                            fprintf(GET_PORT(output_stream),"(");
                            print(cadr(addr));
                            fprintf(GET_PORT(output_stream),")");
                        }
                    }
                    else if(numbervarp(addr) && numbervars_flag)
                        print_numbervars(addr);
                    else if(clausep(addr))
                            printclause(addr);
                    else if(listp(addr)){
                        if(!ignore_flag){
                            fprintf(GET_PORT(output_stream),"[");
                            printlist(addr);
                        }
                        else
                            printlist_canonical(addr);
                    }
                    else if(eqlp(car(addr),CURL)){
                            fprintf(GET_PORT(output_stream),"{");
                            printcurl(cdr(addr));
                    }
                    else if(mixturep(car(addr))){
                        if(length(addr) == 2)
                            goto prefix;
                        else
                            goto infix;
                    }
                    else if(infixp(addr)){
                        infix:
                        if(!ignore_flag)
                            printinfix(addr);
                        else{
                            if(car(addr) == DOTOBJ ||
                               car(addr) == AND ||
                               car(addr) == OR){// '.' ',' ';'
                                fprintf(GET_PORT(output_stream),"'");
                                print(car(addr));
                                fprintf(GET_PORT(output_stream),"'");
                            }
                            else   //other functor
                                print(car(addr));
                            if(!nullp(cdr(addr))){
                                fprintf(GET_PORT(output_stream),"(");
                                printtuple(cdr(addr));
                            }
                        }
                    }
                    else if(prefixp(addr)){
                        prefix:
                        if(!ignore_flag)
                            printprefix(addr);
                        else{
                            print(car(addr));
                            fprintf(GET_PORT(output_stream),"(");
                            print(cadr(addr));
                            fprintf(GET_PORT(output_stream),")");
                        }
                    }
                    else if(operationp(addr) ||
                            predicatep(addr) ||
                            builtinp(addr) ||
                            compiledp(addr)){
                                print(car(addr));
                                if(!nullp(cdr(addr))){
                                    fprintf(GET_PORT(output_stream),"(");
                                    printtuple(cdr(addr));
                                }
                    }
                    else{
                        fprintf(GET_PORT(output_stream),"#[");
                        printlist(addr);
                    }
                    break;
        case STREAM:if(addr == standard_input)
                        fprintf(GET_PORT(output_stream),"<stdin>");
                    else if(addr == standard_output)
                        fprintf(GET_PORT(output_stream),"<stdout>");
                    else if(addr == standard_error)
                        fprintf(GET_PORT(output_stream),"<stderr>");
                    else
                        fprintf(GET_PORT(output_stream),"<stream%d>",addr);
                    break;
        case STR:   fprintf(GET_PORT(output_stream),"\"%s\"", GET_NAME(addr));
                    break;
        default:    fprintf(GET_PORT(output_stream),"<undef>"); break;
    }
}

void print_quoted(int addr){
    char str[ATOMSIZE],c;
    int pos;

    strcpy(str,GET_NAME(addr));
    pos = 0;
    c = str[pos];
    fprintf(GET_PORT(output_stream),"%c",'\'');
    while(c != NUL){
        if(c == '\\'){
            pos++;
            c = str[pos];
            if(c == NUL){
                fprintf(GET_PORT(output_stream),"%c",'\\');
                goto exit;
            }
            else if(c == '"'){
                fprintf(GET_PORT(output_stream),"%c",c);
                pos++;
            }
            else{
                fprintf(GET_PORT(output_stream),"%c",c);
                pos++;
            }
        }
        else if(c <= 31){
            fprintf(GET_PORT(output_stream),"%c",'\\');
            fprintf(GET_PORT(output_stream),"%o",c);
            fprintf(GET_PORT(output_stream),"%c",'\\');
            pos++;
        }
        else if(mode_flag == 0 && iskanji(c)){
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
        }
        else if(mode_flag == 1 && isUni2(c)){
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
        }
        else if(mode_flag == 1 && isUni3(c)){
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
        }
        else if(mode_flag == 1 && isUni4(str[0])){
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
        }
        else if(mode_flag == 1 && isUni5(str[0])){
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
        }
        else if(mode_flag == 1 && isUni6(str[0])){
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);
        }
        else
            fprintf(GET_PORT(output_stream),"%c",str[pos++]);


        c = str[pos];
    }
    exit:
    fprintf(GET_PORT(output_stream),"%c",'\'');
}

void print_numbervars(int addr){
    int n,alpha,num;

    if(integerp(cadr(addr))){
        n = GET_INT(cadr(addr));
        alpha = n % 26 + 65;
        num = n / 26;
        if(num != 0)
            fprintf(GET_PORT(output_stream),"%c%d",alpha,num);
        else
            fprintf(GET_PORT(output_stream),"%c",alpha);
    }
    else{
        print(car(addr));
        fprintf(GET_PORT(output_stream),"(");
        print(cadr(addr));
        fprintf(GET_PORT(output_stream),")");
    }
}

void print_not_quoted(int addr){
    char str[ATOMSIZE],c;
    int pos;


    strcpy(str,GET_NAME(addr));
    pos = 0;
    c = str[pos];
    while(c != NUL){
        if(c == '\\'){
            pos++;
            c = str[pos];
            if(c == 'n')
                fprintf(GET_PORT(output_stream),"%c",EOL);
            else if(c == 't')
                fprintf(GET_PORT(output_stream),"%c",TAB);
            else if(c == 'f')
                fprintf(GET_PORT(output_stream),"%c",FF);
            else if(c == 'r')
                fprintf(GET_PORT(output_stream),"%c",CR);
            else if(c == 'v')
                fprintf(GET_PORT(output_stream),"%c",VT);
            else if(c == 'a')
                #if _WIN32
                MessageBeep(-1);
                #elif __linux
                printf("\a");
                #elif __OpenBSD__
                printf("\a");
                #endif
            else if(c == 'b')
                fprintf(GET_PORT(output_stream),"%c",BS);
            else if(c == NUL)
                return;
            else{
                fprintf(GET_PORT(output_stream),"%c",str[pos-1]);
                fprintf(GET_PORT(output_stream),"%c",c);
            }
        }
        else
            fprintf(GET_PORT(output_stream),"%c",c);
        pos++;
        c = str[pos];
    }
}

void printc(char c){
    fprintf(GET_PORT(output_stream),"%c", c);
}

void printlong(int addr){
    #if (defined __MINGW32__) || (defined __MINGW64)
        fprintf(GET_PORT(output_stream),"%I64d", GET_LONG(addr));
    #else
        fprintf(GET_PORT(output_stream),"%lld", GET_LONG(addr));
    #endif
}


void printinfix(int addr){
    if(length(addr) == 2){
        print(car(addr));
        print(cadr(addr));
    }
    else if(alphabeticalp(car(addr))){
        print(cadr(addr));
        printc(' ');
        print(car(addr));
        printc(' ');
        print(caddr(addr));
    }
    else{
        if(infix_operator_p(cadr(addr))){
            fprintf(GET_PORT(output_stream),"(" );
            print(cadr(addr));
            fprintf(GET_PORT(output_stream),")" );
        }
        else if(infixp(cadr(addr)) &&
            get_2nd_weight(car(cadr(addr))) > get_2nd_weight(car(addr))){
            fprintf(GET_PORT(output_stream),"(" );
            print(cadr(addr));
            fprintf(GET_PORT(output_stream),")" );
        }
        else
            print(cadr(addr));

        print(car(addr));

        if(infix_operator_p(caddr(addr))){
            fprintf(GET_PORT(output_stream),"(" );
            print(caddr(addr));
            fprintf(GET_PORT(output_stream),")" );
        }
        else if(infixp(caddr(addr)) &&
                get_2nd_weight(car(caddr(addr))) > get_2nd_weight(car(addr))){
            fprintf(GET_PORT(output_stream),"(" );
            print(caddr(addr));
            fprintf(GET_PORT(output_stream),")" );
        }
        else if(infixp(cadr(addr)) && infixp(caddr(addr)) &&
            get_2nd_weight(car(cadr(addr))) <= get_2nd_weight(car(caddr(addr)))){
            fprintf(GET_PORT(output_stream),"(" );
            print(caddr(addr));
            fprintf(GET_PORT(output_stream),")" );
        }
        else if(single_operation_p(caddr(addr))){
            fprintf(GET_PORT(output_stream)," " );
            print(caddr(addr));
        }
        else
            print(caddr(addr));
    }
}



void printprefix(int addr){
    if(alphabeticalp(car(addr))){
        print(car(addr));
        printc(' ');
        print(cadr(addr));
    }
    else{
        print(car(addr));
        print(cadr(addr));
    }
}

void printpostfix(int addr){
    if(alphabeticalp(car(addr))){
        print(cadr(addr));
        printc(' ');
        print(car(addr));
    }
    else{
        print(cadr(addr));
        print(car(addr));
    }
}



void printsexp(int addr){
    if(nullp(addr))
        fprintf(GET_PORT(output_stream),")");
    else
    if((!(structurep(cdr(addr)))) && (! (nullp(cdr(addr))))){
        print(car(addr));
        fprintf(GET_PORT(output_stream)," . ");
        print(cdr(addr));
        fprintf(GET_PORT(output_stream),")");
    }
    else {
        print(car(addr));
        if(!nullp(cdr(addr)))
            fprintf(GET_PORT(output_stream)," ");
        printsexp(cdr(addr));
    }
}

void printarguments(int addr){
    if(!structurep(caddr(addr))){
        print(cadr(addr));
        fprintf(GET_PORT(output_stream),",");
        print(caddr(addr));
        fprintf(GET_PORT(output_stream),")");
    }
    else{
        print(cadr(addr));
        fprintf(GET_PORT(output_stream),",");
        printarguments(caddr(addr));
    }
}

void printlist(int addr){
    if(nullp(addr))
        fprintf(GET_PORT(output_stream),"]");
    else if((!(structurep(cdr(addr)))) && (! (nullp(cdr(addr))))){
        if(operationp(car(addr)) &&
           !argumentsp(car(addr)) &&
           heavy999p(car(car(addr)))){
            fprintf(GET_PORT(output_stream),"(");
            print(car(addr));
            fprintf(GET_PORT(output_stream),")");
        }
        else if(car(addr) == AND){
            fprintf(GET_PORT(output_stream),"','");
        }
        else if(car(addr) == DOTOBJ){
            fprintf(GET_PORT(output_stream),"'.'");
        }
        else
            print(car(addr));

        fprintf(GET_PORT(output_stream),"|");

        if(operationp(cdr(addr)) &&
           !argumentsp(cdr(addr)) &&
           heavy999p(car(cdr(addr)))){
            fprintf(GET_PORT(output_stream),"(");
            print(cdr(addr));
            fprintf(GET_PORT(output_stream),")");
        }
        else
            print(cdr(addr));
        fprintf(GET_PORT(output_stream),"]");
    }
    else {
        if(operationp(car(addr)) &&
           !argumentsp(car(addr)) &&
           heavy999p(car(car(addr)))){
            fprintf(GET_PORT(output_stream),"(");
            print(car(addr));
            fprintf(GET_PORT(output_stream),")");
        }
        else if(car(addr) == AND){
            fprintf(GET_PORT(output_stream),"','");
        }
        else if(car(addr) == DOTOBJ){
            fprintf(GET_PORT(output_stream),"'.'");
        }
        else
            print(car(addr));
        if(!nullp(cdr(addr)))
            fprintf(GET_PORT(output_stream),",");
        printlist(cdr(addr));
    }
}

void printlist_canonical(int addr){
    if(nullp(addr))
        print(NIL);
    else if(!listp(cdr(addr))){
        fprintf(GET_PORT(output_stream),"'.'(");
        print(car(addr));
        fprintf(GET_PORT(output_stream),",");
        print(cdr(addr));
        fprintf(GET_PORT(output_stream),")");
    }
    else{
        fprintf(GET_PORT(output_stream),"'.'(");
        print(car(addr));
        fprintf(GET_PORT(output_stream),",");
        printlist_canonical(cdr(addr));
        fprintf(GET_PORT(output_stream),")");
    }
}

void printcurl(int addr){
    arguments_flag = 0; //(1,2,3) -> 1,2,3
    if(nullp(addr)){
        fprintf(GET_PORT(output_stream),"}");
        arguments_flag = 1;
    }
    else {
        print(car(addr));
        if(!nullp(cdr(addr)))
            fprintf(GET_PORT(output_stream),",");
        printcurl(cdr(addr));
    }
}

void printtuple(int addr){
    if(nullp(addr))
        fprintf(GET_PORT(output_stream),")");
    else {
        print(car(addr));
        if(!nullp(cdr(addr)))
            fprintf(GET_PORT(output_stream),",");
        printtuple(cdr(addr));
    }
}

void printclause(int addr){

    if(listing_flag){
        if(nullp(caddr(addr))){// e.g. :- foo(x).
            fprintf(GET_PORT(output_stream),"(:- ");
            print(cadr(addr));
            fprintf(GET_PORT(output_stream),")");
        }
        else{// e.g. foo(x) :- boo(x).
            print(cadr(addr));
            fprintf(GET_PORT(output_stream)," :-\n    ");
            printbody(caddr(addr));
        }
    }
    else{
        if(!ignore_flag){
            if(nullp(caddr(addr))){ // e.g :- foo(x).
                fprintf(GET_PORT(output_stream),":- ");
                print(cadr(addr));
            }
            else{ //normal case  foo(X) :- bar(X).
                print(cadr(addr));
                fprintf(GET_PORT(output_stream),":-");
                print(caddr(addr));
            }
        }
        else{
            if(nullp(caddr(addr))){ // e.g :- foo(x).
                fprintf(GET_PORT(output_stream),":-(");
                print(cadr(addr));
                fprintf(GET_PORT(output_stream),")");
            }
            else{ // normal case foo(X) :- bar(X).
                fprintf(GET_PORT(output_stream),":-(");
                print(cadr(addr));
                fprintf(GET_PORT(output_stream),",");
                print(caddr(addr));
                fprintf(GET_PORT(output_stream),")");
            }
        }
    }
}

void printbody(int addr){

    if(operationp(addr) && car(addr) == AND){
        printbody(cadr(addr));
        print(car(addr));
        fprintf(GET_PORT(output_stream),"\n    ");
        printbody(caddr(addr));
    }
    else if(operationp(addr) && car(addr) == OR){
        fprintf(GET_PORT(output_stream),"(");
        printbody1(cadr(addr));
        print(car(addr));
        printbody1(caddr(addr));
        fprintf(GET_PORT(output_stream),")");
    }
    else{
        print(addr);
    }
}

void printbody1(int addr){
    if(operationp(addr)){
        print(cadr(addr));
        print(car(addr));
        printbody1(caddr(addr));
    }
    else
        print(addr);
}


int laststr(char buf[]){
    int i;

    i = 0;
    while(buf[i] != NUL)
        i++;
    return(i-1);
}
