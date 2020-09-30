/* N-Prolog
written by kenichi sasagawa 2016/8~
*/

#include <string.h>
#include <math.h>
#include <signal.h>
#ifdef __linux
  #include <stdio_ext.h>
#endif
#include "npl.h"

//global vers
int proof = 0;
cell heap[CELLSIZE];
int cell_hash_table[HASHTBSIZE];
int variant[VARIANTSIZE];
int stack[STACKSIZE];
int record_hash_table[HASHTBSIZE][RECORDMAX];  //for hash record database 
int record_pt = 1;                             // current index of record database
token stok = {GO,OTHER};
jmp_buf buf;
int variables = NIL;
int predicates = NIL;
int spy_list = NIL;
int reconsult_list = NIL;
int execute_list = NIL;
int op_list = NIL;
int record_list = NIL;
int unread = NIL;     //for parse
int paren_nest = 0;   //for parse check ((()))
int line;
int column;
int cursor_row = 0;
int cursor_col = 0;
int cursor_prop = 0;
int cursor_row_store = 0;
int cursor_col_store = 0;
int cursor_prop_store = 0;



//------pointer----
int hp; //heap pointer
int sp; //stack pointer
int fc; //free counter
int ac; //alpha conversion variable count
int wp; //working pointer


//flag
int trace_flag = FULL;
int trace_nest = 999999999; //max nest level of trace
int open_flag = 0;
int gbc_flag = 0;  // 0=not display massage 1=display message
int simp_flag = 1;
int assert_flag = 0; // 0=asserta, 1=assertz
int debug_flag = OFF;  // 0=normal mode, 1=debug mode
int sexp_flag = 0;
int cut_flag = 0;
int arguments_flag = 1; //1= 1,2,3 -> (1,2,3) 0= 1,2,3 -> 1,2,3
int mode_flag = 1;  // 0=SJIS, 1=Unicod
int quoted_flag = 1; // 0=not print ' 1=print '
int ignore_flag = 0; // 0=infix notation 2+2 1=prefix notation +(2,2)
int error_flag = 0;  // flag in syntax error
int link_flag = 0;  // 0=not-link, 1=linked
int listing_flag = 0;  //for print clause, 0=normal, 1=format print
int colon_sets_calling_context_flag = 1; //1=true, 0=false
int prefix_flag = 0;   //for parser 0=not prefix, 1=prefix


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
{"is"},{"edit"},{"open"},{"close"},{"system"},{"create"},
{"delete"},{"rename"},
{"op"},{"!"},{"assert"},{"asserta"},{"assertz"},
{"abolish"},{"read"},{"write"},{"put"},{"get"},{"get0"},{"get0_noecho"},{"nl"},
{"tab"},{"fail"},{"not"},{"true"},{"halt"},{"abort"},
{"listing"},{"functor"},{"arg"},
{"writeq"},{"display"},
{"atom_concat"},{"consult"},{"reconsult"},
{"see"},{"seeing"},{"seen"},{"tell"},{"telling"},{"told"},{"trace"},{"notrace"},{"spy"},
{"nospy"},{"leash"},{"atom"},{"integer"},{"real"},{"float"},{"number"},
{"var"},{"nonvar"},{"atomic"},{"list"},{"gc"},{"time"},{"name"},{"bounded"},
{"flush"},{"date"},{"date_day"},
{"string"},{"string_chars"},{"string_codes"},{"ground"},
{"concat"},{"substring"},
{"inc"},{"dec"},{"compare"},
{"mkdir"},{"rmdir"},{"chdir"},{"string_length"},
{"sort"},{"keysort"},{"length"},{"shell"},{"measure"},
{"ansi_cuu"},{"ansi_cud"},{"ansi_cuf"},{"ansi_cub"},
{"ansi_cup"},{"ansi_cpr"},{"ansi_scp"},{"ansi_rcp"},
{"ansi_ed"},{"ansi_el"},
{"recordh"},{"recorda"},{"recordz"},{"instance"}
};

//compiled predicate
char compiled[COMPILED_NUMBER][30] ={
{"append"},{"member"},{"repeat"},
{"retract"},{"clause"},{"call"},
{"current_visible"},{"stream_property"},{"between"},
{"current_predicate"},{"current_op"},{"retrieveh"}
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


//-----editor-----
int repl_flag = 1;  //for REPL read_line 1=on, 0=off
int buffer[256][10];
int ed_tab = 4;
int ed_indent = 0;
int ed_lparen_row;
int ed_lparen_col;
int ed_rparen_row;
int ed_rparen_col;
int ed_lbracket_row;
int ed_lbracket_col;
int ed_rbracket_row;
int ed_rbracket_col;
char ed_candidate[15][30];
int ed_candidate_pt;
int ed_operator_color = 3;   //default yellow
int ed_builtin_color = 6;  //default cyan
int ed_extended_color = 1; //default red
int ed_quote_color = 3;   //default yellow
int ed_comment_color = 4;  //default blue
int ed_function_color = 2; //default green
int ed_incomment = -1; /*...*/



int main(int argc, char *argv[]){
    int opt;

    printf("N-Prolog Ver 0.09\n");
    signal(SIGINT,reset);
    initcell();
    initbuiltin();
    initoperator();
    initstream();
    input_stream = standard_input;
    output_stream = standard_output;
    error_stream = standard_error;
    opt = 1;
    init_repl();

    FILE* fp = fopen("library/dcg.pl","r");
    if(fp != NULL){
        fclose(fp);
        b_consult(list1(makeconst("library/dcg.pl")),NIL);
        predicates = NIL;
    }
    fp = fopen("library/compiler.pl","r");
    if(fp != NULL){
        fclose(fp);
        b_consult(list1(makeconst("library/compiler.pl")),NIL);
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
            b_consult(list1(makeconst(argv[opt])),NIL);
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
            printf("?- "); fflush(stdout);
            query(variable_to_call(readparse()));
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

void reset(int i){
    printf("ctrl+C\n");
    longjmp(buf,1);
}

void init_repl(void){
    int i;

    stok.flag = GO;
    proof = 0;
    ac = CELLSIZE+1;
    wp = HEAPSIZE+1;
    unbind(0);
    sp = 0;
    cut_flag = 0;
    //initialize variant variable
    for(i=0; i<VARIANTSIZE; i++){
        variant[i] = UNBIND;
    }
    i = variables;
    while(!nullp(i)){
        SET_CAR(car(i),UNBIND);
        SET_CDR(car(i),UNBIND);
        i = cdr(i);
    }

}

void query(int x){
    int res;

    // DCG syntax e.g. a-->b.
    if(dcgp(x)){
        operate(x);
        return;
    }

    //[file1,file2] -> consult(file1),consult(file2).
    if(listp(x))
        x = list_to_ope(x);

    if(atomp(x) && !builtinp(x) && !compiledp(x))
        x = makepred(GET_NAME(x));

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"?- ", x);

    if(!callablep(x))
        error(NOT_CALLABLE,"?- ", x);

    variables = listreverse(unique(varslist(x)));
    res = prove_all(addask(x),sp,1);
    print(res);printf("\n");
    return;
}

int list_to_ope(int x){
    if(nullp(x))
        error(SYNTAX_ERR,"?-", x);
    else if(nullp(cdr(x))){
        if(atomp(car(x)))
            return(list2(makeatom("consult",SYS),car(x)));
        else if(caar(x) == makeatom("-",OPE))
            return(list2(makeatom("reconsult",SYS),cadr(car(x))));
    }
    else{
        if(atomp(car(x)))
            return(list3(makeatom(",",OPE),
                     list2(makeatom("consult",SYS),car(x)),
                     list_to_ope(cdr(x))));
        else if(caar(x) == makeatom("-",OPE))
            return(list3(makeatom(",",OPE),
                     list2(makeatom("reconsult",SYS),cadr(car(x))),
                     list_to_ope(cdr(x))));
    }
    return(NIL);
}

int addask(int x){
    return(addtail_body(makeatom("%ask",SYS),x));
}


int addtail_body(int x, int y){
    if(nullp(y))
        return(x);
    else if(!conjunctionp(y))
        return(wlist3(AND,y,x));
    else
        return(wlist3(car(y),cadr(y),addtail_body(x,caddr(y))));
}

/*
int addtail_body(int x, int y){
    if(!conjunctionp(y))
        return(wlist3(AND,y,x));
    else{
        addtail_body1(x,y);
        return(y);
    }
}


//concat y and x by side eeffect.
//set address directly

void addtail_body1(int x, int y){
    if(!conjunctionp(y))
        y = wlist3(AND,y,x);
    else
        addtail_body1(x,caddr(y));
}
*/

int prove_all(int goals, int bindings, int n){

    if(nullp(goals))
        return(YES);
    else if(car(goals) != AND)
        return(prove(goals,bindings,NIL,n));
    else{
        if(!has_cut_p(goals)){
            return(prove(cadr(goals),bindings,caddr(goals),n));
        }
        else{
            if(conjunctionp(goals) && cadr(goals) == CUT)
                cut_flag = 1;
        
            if(prove_all(before_cut(goals),bindings,n) == YES)
                return(prove_all(after_cut(goals),sp,n));
            else
                return(NO);
        }
    }

    return(NO);
}

int prove(int goal, int bindings, int rest, int n){
    int clause,clauses,clause1,varlis,save;

    proof++;
    if(n > 18000)
        error(RESOURCE_ERR,"",NIL);

    goal = deref(goal);
    
    if(nullp(goal)){
        return(prove_all(rest,bindings,n));
    }
    else if(builtinp(goal)){
        if(atomp(goal)){
            if((GET_SUBR(goal))(NIL,rest) == YES)
                return(prove_all(rest,sp,n));

            unbind(bindings);
            return(NO);
        }
        else{
            if((GET_SUBR(car(goal)))(cdr(goal),rest) == YES)
                return(prove_all(rest,sp,n));

            unbind(bindings);
            return(NO);
        }
    }
    else if(compiledp(goal)){
        if(atomp(goal)){
            if((GET_SUBR(goal))(NIL,rest) == YES)
                return(YES);

            return(NO);
        }
        else{
            if((GET_SUBR(car(goal)))(cdr(goal),rest) == YES)
                return(YES);

            return(NO);
        }
    }
    else if(predicatep(goal)){
        //trace
        if(debug_flag == ON && trace_flag != OFF && spypointp(goal)){
            printf("(%d) CALL: ", n); print(goal);
            debugger(goal,bindings,rest,n);
        }

        if(atomp(goal))
            clauses = GET_CAR(goal);
        else
            clauses = GET_CAR(car(goal));
        
        if(clauses == NIL)
            error(EXISTENCE_ERR,"", goal);

        while(!nullp(clauses)){
            save = wp;
            clause = car(clauses);
            clauses = cdr(clauses);
            varlis = GET_VAR(clause);
            assign_variant(varlis);
            clause1 = walpha_conversion(clause);
            release_variant(varlis);
            
            // case of predicate
            if(predicatep(clause1) && unify(goal,clause1) == YES){
                if(prove_all(rest,sp,n+1) == YES){
                    //trace
                    if(debug_flag == ON && trace_flag != OFF && spypointp(goal)){
                        printf("(%d) EXIT: ", n); print(goal);
                        debugger(goal,bindings,rest,n);
                    }
                    return(YES);
                }
                else{
                    //trace
                    if(debug_flag == ON && (trace_flag == FULL || trace_flag == TIGHT) && 
                        spypointp(goal)){
                        printf("(%d) FAIL: ", n); print(goal);
                        debugger(goal,bindings,rest,n);
                    }
                }
            }
            // case of clause
            else{
                if(unify(goal,(cadr(clause1))) == YES){
                    clause1 = addtail_body(rest,caddr(clause1));
                    if(prove_all(clause1,sp,n+1) == YES){
                        //trace
                        if(debug_flag == ON && trace_flag == FULL && spypointp(goal)){
                            printf("(%d) EXIT: ", n); print(goal);
                            debugger(goal,bindings,rest,n);
                        }
                        return(YES);
                    }
                }
            }
            //trace
            if(debug_flag == ON && (trace_flag == FULL || trace_flag == TIGHT || trace_flag == HALF) &&
                spypointp(goal)){
                printf("(%d) REDO: ", n); print(goal);
                debugger(goal,bindings,rest,n);
            }
            wp = save;
            unbind(bindings);
        }
        //trace
        if(debug_flag == ON && (trace_flag == FULL || trace_flag == TIGHT || trace_flag == HALF) &&
            spypointp(goal)){
            printf("(%d) FAIL: ", n); print(goal);
            debugger(goal,bindings,rest,n);
        }
    }
    else if(disjunctionp(goal)){
        if(prove_all(addtail_body(rest,cadr(goal)),bindings,n) == YES)
            return(YES);
        else{
            if(cut_flag == 1 || car(cadr(goal)) == IFTHEN){
                cut_flag = 0;
                unbind(bindings);
                return(NO);
            }
            unbind(bindings);
            if(prove_all(addtail_body(rest,caddr(goal)),bindings,n) == YES)
                return(YES)
;            else{
                unbind(bindings);
                return(NO);
            }
        }
        unbind(bindings);
        return(NO);
    }
    return(NO);
}


int before_cut(int x){

    if(x == CUT)
        return(NIL);
    else if(!conjunctionp(x))
        return(x);
    else if(cadr(x) == CUT)
        return(NIL);
    else if(conjunctionp(caddr(x)) && cadr(caddr(x)) == CUT)
        return(cadr(x));
    else
        return(wlist3(AND,cadr(x),before_cut(caddr(x))));

}


int after_cut(int x){

    if(x == CUT)
        return(NIL);
    else if(!conjunctionp(x))
        return(x);
    else if(cadr(x) == CUT)
        return(caddr(x));
    else
        return(after_cut(caddr(x)));
    
}

void debugger(int goal, int bindings, int rest, int n){
    int c,save;

    loop:
    printf("?> ");
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
        case 'd':   save = ignore_flag;
                    ignore_flag = 1;
                    print(goal);
                    printf("\n");
                    ignore_flag = save;
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
                    printf("n: notrace\n");
                    printf("s: skip to next spy point\n");
                    printf("w: write goal\n");
                    fflush(stdin);
                    goto loop;
        case 'n':   debug_flag = OFF;
                    break;
        case 's':   debug_flag = ON;
                    FLUSH
                    break;
         case 'w':  save = ignore_flag;
                    ignore_flag = 0;
                    print(goal);
                    printf("\n");
                    ignore_flag = save;
                    goto loop;
    
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
                    else if(variablep(addr))
                        fprintf(GET_PORT(output_stream),"%s", GET_NAME(addr));
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
        case STR:   if(quoted_flag)
                        fprintf(GET_PORT(output_stream),"$%s$", GET_NAME(addr));
                    else
                        fprintf(GET_PORT(output_stream),"%s", GET_NAME(addr));
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
    fprintf(GET_PORT(output_stream),"%lld", GET_LONG(addr));
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
