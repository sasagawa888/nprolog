/* N-Prolog
written by kenichi sasagawa 2016/8~
*/

#include <string.h>
#include <math.h>
#include <signal.h>
#ifndef __APPLE__
#include <stdio_ext.h>
#endif
#include <stdlib.h>
#include <getopt.h>
#include <float.h>
#include "npl.h"

//global vers
int proof = 0;
int nest = 0;
cell heap[CELLSIZE];
int cell_hash_table[HASHTBSIZE];
int variant[VARIANTSIZE];
int bigcell[BIGSIZE];
int stack[STACKSIZE];
int ustack[STACKSIZE];
int record_hash_table[HASHTBSIZE][RECORDMAX];	// for hash record database 
int record_pt = 1;		// current index of record database
int counter[31];		// counter str_set,str_dec ... 
int string_term_buffer[STRSIZE];	// for string_term/2
token stok = { GO, OTHER };

jmp_buf buf;			// for REPL halt and error handling.
jmp_buf buf1;			// for n_error/2 error check.
jmp_buf buf2;			// for break/0 end_of_file/0 exit break
int variables = NIL;
int variables_save = NIL;
int end_of_file_answer = NIL;
int end_of_file_rest = NIL;
int predicates = NIL;
int builtins = NIL;
int spy_list = NIL;
int reconsult_list = NIL;
int execute_list = NIL;
int op_list = NIL;
int key_list = NIL;
int error_code = 0;
int bag_list;
int nonfree_list;
int unread = NIL;		//for parse
int paren_nest = 0;		//for parse check ((()))
int left_margin = 4;		//for read_line 
int break_nest = 0;		//for debugger b command
int leap_point = NIL;		//for debugger l command
int port;			//for debugger
int line;			//for error, display line of error point
int column;			//for error, display column of error point
int cursor_color;		//for ansi_sgr
int cursor_style;		//for ansi_sgr
int cursor_row_store = -1;	//for ansi_sgr -1=undefined,0~=defined
int cursor_col_store = -1;	//for ansi_sgr
int cursor_color_store = -1;	//for ansi_sgr
int cursor_style_store = -1;	//for ansi_sgr
double timer;			// for timer_microseconds/1



//------pointer----
int hp;				//heap pointer
int sp;				//stack pointer
int fc;				//free counter
int ac;				//alpha conversion variable count
int wp;				//working pointer
int up;				//unify stack pointer
int gc;				//invoked GC count

// bignum pointer
int big_pt0 = 0;		// pointer of temporaly bignum
int big_pt1 = BIGNUM_PARMA;	// pointer of parmanent bignum

//flag
int repl_flag = 1;		//for editable REPL read_line 1=on, 0=off
int trace_flag = FULL;		//for debugger
int open_flag = 0;		//for error 0=not int reading file, 1=in reading file 
int gbc_flag = 0;		// 0=not display massage 1=display message
int simp_flag = 1;		//for bignum 1=if bignum become more simple, simplify, 0=not
int assert_flag = 0;		// 0=asserta, 1=assertz
int debug_flag = OFF;		// 0=normal mode, 1=debug mode
int fskip_flag = OFF;		// for debugger f command
int qskip_flag = OFF;		// for debugger q command
int sskip_flag = OFF;		// for debugger s command 
int xskip_flag = OFF;		// for debugger x command
int semiskip_flag = OFF;	//for debugger ; command
int sexp_flag = 0;		// for debug 0=normal, 1=print data as S expression like LISP
int arguments_flag = 1;		//1= 1,2,3 -> (1,2,3) 0= 1,2,3 -> 1,2,3
int quoted_flag = 1;		// 0=not print ' 1=print '
int ignore_flag = 0;		// 0=infix notation 2+2 1=prefix notation +(2,2)
int link_flag = 0;		// 0=not-link, 1=linked
int listing_flag = 0;		//for print clause, 0=normal, 1=format print
int colon_sets_calling_context_flag = 1;	//1=true, 0=false
int prefix_flag = 0;		//for parser 0=not prefix, 1=prefix
int syntax_flag = YES;		//syntaxerrors/2 YES=normal. NO=ignore syntax-errors
int fileerr_flag = YES;		//fileerrors/2 YES=normal. NO=ignore file-errors
int exist_flag = YES;		//existerrors/2 YES=normal, NO=ignore existance_errors
int string_term_flag = 0;	//for string_term/2 0=normal, 1=readparse from string_term_buffer
int ctrl_c_flag = 0;		//for ctrl_c  to stop prove
int init_flag = 1;		//for halt
int script_flag = 0;		// script mode, 0=not scriplt-mode, 1=script-mode.
int check_flag = 0;		// for n_error/2 error check
int break_flag = 0;		// for break/0 0=normal,1=break.

//stream
int standard_input;
int standard_output;
int standard_error;
int input_stream;
int output_stream;
int error_stream;


//-----editor-----
char buffer[BUFSIZE][10];
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
char ed_candidate[30][30];
int ed_candidate_pt;
int ed_operator_color = 5;	//default magenta
int ed_builtin_color = 6;	//default cyan
int ed_extended_color = 1;	//default red
int ed_quote_color = 3;		//default yellow
int ed_comment_color = 4;	//default blue
int ed_function_color = 2;	//default green
int ed_incomment = -1;		/*... */
int ed_hight;
int ed_width;
result rtok;			// token type and length for editable REPL

void usage()
{
    printf("List of options:\n");
    printf("-c filename -- NPL starts after reading the file.\n");
    printf("-h          -- display help.\n");
    printf("-r          -- NPL does not use editable REPL.\n");
    printf("-s filename -- NPL run file with script mode.\n");
    printf("-v          -- dislplay version number.\n");
}

int main(int argc, char *argv[])
{
    int ch, input;
    char *home, str[STRSIZE];
    struct winsize w;
    FILE *fp;

    signal(SIGINT, reset);
    initcell();
    initbuiltin();
    initoperator();
    initstream();
    ioctl(0, TIOCGWINSZ, &w);
    ed_hight = w.ws_row;
    ed_width = w.ws_col;
    input_stream = standard_input;
    output_stream = standard_output;
    error_stream = standard_error;
    init_repl();
    int ret = setjmp(buf);
    if (!init_flag)
	goto repl;

    home = getenv("HOME");
    strcpy(str, home);
    strcat(str, "/nprolog/library/dcg.pl");
    fp = fopen(str, "r");
    if (fp != NULL) {
	fclose(fp);
	b_consult(list1(makeconst(str)), NIL);
	predicates = NIL;
    }
    strcpy(str, home);
    strcat(str, "/nprolog/library/compiler.pl");
    fp = fopen(str, "r");
    if (fp != NULL) {
	fclose(fp);
	b_consult(list1(makeconst(str)), NIL);
	predicates = NIL;
    }
    strcpy(str, home);
    strcat(str, "/nprolog/library/multiplex.pl");
    fp = fopen(str, "r");
    if (fp != NULL) {
	fclose(fp);
	b_consult(list1(makeconst(str)), NIL);
	predicates = NIL;
    }
    strcpy(str, home);
    strcat(str, "/nprolog/library/startup.pl");
    fp = fopen(str, "r");
    if (fp != NULL) {
	fclose(fp);
	b_consult(list1(makeconst(str)), NIL);
    }

    while ((ch = getopt(argc, argv, "c:s:rhv")) != -1) {
	switch (ch) {
	case 'c':
	    fp = fopen(optarg, "r");
	    if (fp != NULL)
		fclose(fp);
	    else {
		printf("Not exist %s\n", optarg);
		exit(EXIT_FAILURE);
	    }
	    b_consult(list1(makeconst(optarg)), NIL);
	    break;
	case 's':
	    fp = fopen(optarg, "r");
	    if (fp != NULL)
		fclose(fp);
	    else {
		printf("Not exist %s\n", optarg);
		exit(EXIT_FAILURE);
	    }
	    script_flag = 1;
	    b_consult(list1(makeconst(optarg)), NIL);
	    exit(EXIT_SUCCESS);
	case 'r':
	    repl_flag = 0;
	    break;
	case 'v':
	    printf("N-Prolog Ver %1.2f\n", VERSION);
	    exit(EXIT_SUCCESS);
	case 'h':
	    usage();
	    exit(EXIT_SUCCESS);
	default:
	    usage();
	    exit(EXIT_FAILURE);
	}
    }


    if (init_flag) {
	printf("N-Prolog Ver %1.2f\n", VERSION);
	init_flag = 0;
    }

  repl:
    if (ret == 0)
	while (1) {
	    input_stream = standard_input;
	    output_stream = standard_output;
	    error_stream = standard_error;
	    init_repl();
	    printf("?- ");
	    fflush(stdout);
	    input = variable_to_call(readparse());
	    if (!repl_flag)
		clear_input_buffer();
	    query(input);
	    //sexp_flag = 1;print(variable_to_call(parser(NIL,NIL,NIL,NIL,0,0)));
	    //printf("proof = %d\n", proof);
	    fflush(stdout);
    } else if (ret == 1) {
	ret = 0;
	goto repl;
    } else
	return 0;
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void reset(int i)
{
    ctrl_c_flag = 1;
}

void init_repl(void)
{
    int i;

    stok.flag = GO;
    proof = 0;
    nest = 0;
    ac = CELLSIZE + 1;
    wp = HEAPSIZE + 1;
    unbind(0);
    sp = 0;
    up = 0;
    ctrl_c_flag = 0;
    fskip_flag = OFF;
    sskip_flag = OFF;
    xskip_flag = OFF;
    semiskip_flag = OFF;
    leap_point = NIL;
    left_margin = 4;
    big_pt0 = 0;
    //initialize variant variable
    for (i = 0; i < VARIANTSIZE; i++) {
	variant[i] = UNBIND;
    }
    i = variables;
    while (!nullp(i)) {
	SET_CAR(car(i), UNBIND);
	SET_CDR(car(i), UNBIND);
	i = cdr(i);
    }
    //initialize spy-point trace-level
    i = spy_list;
    while (!nullp(i)) {
	SET_TR(cadar(i), 0);
	i = cdr(i);
    }

}

void query(int x)
{
    int res;

    // DCG syntax e.g. a-->b.
    if (dcgp(x)) {
	operate(x);
	return;
    }
    //[file1,file2] -> consult(file1),consult(file2).
    if (listp(x))
	x = list_to_ope(x);

    if (atomp(x) && !builtinp(x) && !compiledp(x))
	x = makepred(GET_NAME(x));

    if (wide_variable_p(x))
	error(INSTANTATION_ERR, "?- ", x);

    if (!callablep(x))
	error(NOT_CALLABLE, "?- ", x);

    variables = listreverse(unique(varslist(x)));
    res = prove_all(addask(x), sp);
    ESCRST;
    print(res);
    printf("\n");
    return;
}

void query_break(int x)
{
    int res;

    // DCG syntax e.g. a-->b.
    if (dcgp(x)) {
	operate(x);
	return;
    }
    //[file1,file2] -> consult(file1),consult(file2).
    if (listp(x))
	x = list_to_ope(x);

    if (atomp(x) && !builtinp(x) && !compiledp(x))
	x = makepred(GET_NAME(x));

    if (wide_variable_p(x))
	error(INSTANTATION_ERR, "?= ", x);

    if (!callablep(x)) {
	error(NOT_CALLABLE, "?= ", x);
    }

    variables_save = variables;
    variables = listreverse(unique(varslist(x)));
    res = prove_all(addask(x), sp);
    variables = variables_save;
    ESCRST;
    print(res);
    printf("\n");
    return;
}


int list_to_ope(int x)
{
    if (nullp(x))
	error(SYNTAX_ERR, "?-", x);
    else if (nullp(cdr(x))) {
	if (atomp(car(x)))
	    return (list2(makeatom("consult", SYS), car(x)));
	else if (caar(x) == makeatom("-", OPE))
	    return (list2(makeatom("reconsult", SYS), cadr(car(x))));
    } else {
	if (atomp(car(x)))
	    return (list3(makeatom(",", OPE),
			  list2(makeatom("consult", SYS), car(x)),
			  list_to_ope(cdr(x))));
	else if (caar(x) == makeatom("-", OPE))
	    return (list3(makeatom(",", OPE),
			  list2(makeatom("reconsult", SYS), cadr(car(x))),
			  list_to_ope(cdr(x))));
    }
    return (NIL);
}

int addask(int x)
{
    return (addtail_body(makeatom("%ask", SYS), x));
}


int addtail_body(int x, int y)
{
    if (nullp(y))
	return (x);
    else if (!conjunctionp(y))
	return (wlist3(AND, y, x));
    else
	return (wlist3(car(y), cadr(y), addtail_body(x, caddr(y))));
}


int prove_all(int goals, int bindings)
{
    int res;

    if (nullp(goals))
	return (YES);
    else if (car(goals) != AND)
	return (prove(goals, bindings, NIL));
    else {
	if (!has_cut_p(goals)) {
	    return (prove(cadr(goals), bindings, caddr(goals)));
	} else {
	    if (prove_all(before_cut(goals), bindings) == YES) {
		res = prove_all(after_cut(goals), sp);
		if (res == YES)
		    return (YES);
		else if (res == NO)
		    return (NPLFALSE);
	    } else
		return (NO);
	}
    }

    return (NO);
}

int prove(int goal, int bindings, int rest)
{
    int clause, clauses, clause1, varlis, save1, save2, res;

    proof++;
    if (ctrl_c_flag == 1) {
	printf("ctrl+C\n\n");
	longjmp(buf, 1);
    }
    if (nest > 50000)
	error(RESOURCE_ERR, "prove recursion over max", NIL);

    goal = deref(goal);

    if (nullp(goal)) {
	return (prove_all(rest, bindings));
    } else if (builtinp(goal)) {
	if (atomp(goal)) {
	    if ((res = (GET_SUBR(goal)) (NIL, rest)) == YES)
		return (YES);

	    return (res);
	} else {
	    if ((res = (GET_SUBR(car(goal))) (cdr(goal), rest)) == YES)
		return (YES);

	    return (res);
	}
    } else if (compiledp(goal)) {
	if (atomp(goal)) {
	    if ((GET_SUBR(goal)) (NIL, rest) == YES)
		return (YES);

	    return (NO);
	} else {
	    if ((GET_SUBR(car(goal))) (cdr(goal), rest) == YES)
		return (YES);

	    return (NO);
	}
    } else if (predicatep(goal) || user_operation_p(goal)) {
	//trace
	if (debug_flag == ON)
	    prove_trace(DBCALL, goal, bindings, rest);

	if (atomp(goal))
	    clauses = GET_CAR(goal);
	else
	    clauses = GET_CAR(car(goal));

	if (clauses == NIL) {
	    if (exist_flag == YES)
		error(EXISTENCE_ERR, "", goal);
	    else if (exist_flag == NO)
		return (NO);

	}
	while (!nullp(clauses)) {
	    save1 = wp;
	    save2 = ac;
	    clause = car(clauses);
	    clauses = cdr(clauses);
	    varlis = GET_VAR(clause);
	    assign_variant(varlis);
	    clause1 = walpha_conversion(clause);
	    release_variant(varlis);

	    // case of predicate
	    if (predicatep(clause1) || user_operation_p(clause1)) {
		if (unify(goal, clause1) == YES) {
		    if (prove_all(rest, sp) == YES) {
			//trace
			if (debug_flag == ON)
			    prove_trace(DBEXIT, goal, bindings, rest);

			return (YES);
		    } else {
			//trace
			if (debug_flag == ON)
			    prove_trace(DBFAIL, goal, bindings, rest);
		    }
		}
	    }
	    // case of clause
	    else {
		if (unify(goal, (cadr(clause1))) == YES) {
		    clause1 = addtail_body(rest, caddr(clause1));
		    nest++;
		    if ((res = prove_all(clause1, sp)) == YES) {
			nest--;
			//trace
			if (debug_flag == ON)
			    prove_trace(DBEXIT, goal, bindings, rest);

			return (YES);
		    } else {
			nest--;
			if (res == NPLFALSE) {	// when after cut occurs NO
			    //trace
			    if (debug_flag == ON)
				prove_trace(DBCUTFAIL, goal, bindings,
					    rest);
			    wp = save1;
			    ac = save2;
			    unbind(bindings);
			    return (NO);
			}
		    }
		}
	    }
	    //trace
	    if (debug_flag == ON && !nullp(clauses))
		prove_trace(DBREDO, goal, bindings, rest);

	    wp = save1;
	    ac = save2;
	    unbind(bindings);
	}
	//trace
	if (debug_flag == ON)
	    prove_trace(DBFAIL, goal, bindings, rest);

    } else if (disjunctionp(goal)) {
	if (ifthenp(cadr(goal))) {
	    goal =
		wcons(IFTHENELSE,
		      wcons(cadr(cadr(goal)),
			    wcons(caddr(cadr(goal)),
				  wcons(caddr(goal), NIL))));
	    // redefine goal = ifthenelse(if,then,else)
	    return (prove(goal, bindings, rest));
	} else
	    if ((res = prove_all(addtail_body(rest, cadr(goal)), bindings))
		== YES)
	    return (YES);
	else {
	    if (res == NPLFALSE) {
		unbind(bindings);
		return (NO);
	    }
	    unbind(bindings);
	    if (prove_all(addtail_body(rest, caddr(goal)), bindings) ==
		YES)
		return (YES);
	    else {
		unbind(bindings);
		return (NO);
	    }
	}
	unbind(bindings);
	return (NO);
    }
    return (NO);
}


int before_cut(int x)
{

    if (x == CUT)
	return (NIL);
    else if (!conjunctionp(x))
	return (x);
    else if (cadr(x) == CUT)
	return (NIL);
    else if (conjunctionp(caddr(x)) && cadr(caddr(x)) == CUT)
	return (cadr(x));
    else
	return (wlist3(AND, cadr(x), before_cut(caddr(x))));

}


int after_cut(int x)
{

    if (x == CUT)
	return (NIL);
    else if (!conjunctionp(x))
	return (x);
    else if (cadr(x) == CUT)
	return (caddr(x));
    else
	return (after_cut(caddr(x)));

}

void prove_trace(int port, int goal, int bindings, int rest)
{
    int spy, leap;

    if (port == DBCALL) {
	if (trace_flag != OFF) {
	    spy = spypointp(goal);
	    leap = leappointp(goal);
	    if (spy && !leap && xskip_flag == OFF)
		printf("** ");
	    else if (spy && !leap && xskip_flag == ON)
		printf("*> ");
	    else if (!spy && xskip_flag == OFF)
		return;
	    else if (fskip_flag == ON)
		return;
	    else if (qskip_flag == ON)
		return;
	    else if (sskip_flag == ON)
		return;
	    else if (xskip_flag == ON) {
		if (!spy)
		    printf(">  ");
		sskip_flag = OFF;
	    } else if (semiskip_flag == ON)
		return;

	    if (leap)
		return;
	    else
		leap_point = NIL;

	    inctrace(goal);
	    printf("(%d) CALL: ", gettrace(goal));
	    print(goal);
	    port = DBCALL;
	    debugger(goal, bindings, rest);
	}
    } else if (port == DBREDO) {
	if (trace_flag == FULL || trace_flag == TIGHT
	    || trace_flag == HALF) {
	    spy = spypointp(goal);
	    leap = leappointp(goal);

	    if (spy && !leap && semiskip_flag == OFF)
		printf("** ");
	    else if (spy && !leap && semiskip_flag == ON)
		printf("*> ");
	    else if (!spy && semiskip_flag == OFF)
		return;
	    else if (fskip_flag == ON)
		return;
	    else if (qskip_flag == ON)
		return;
	    else if (sskip_flag == ON)
		return;
	    else if (xskip_flag == ON)
		return;
	    else if (semiskip_flag == ON) {
		if (spy) {
		    printf(">  ");
		    semiskip_flag = OFF;
		}
	    }

	    if (leap)
		return;
	    else
		leap_point = NIL;

	    printf("(%d) REDO: ", gettrace(goal));
	    print(goal);
	    port = DBREDO;
	    debugger(goal, bindings, rest);
	}
    } else if (port == DBFAIL) {
	if (trace_flag == FULL || trace_flag == TIGHT) {
	    spy = spypointp(goal);
	    leap = leappointp(goal);
	    if (spy && !leap && fskip_flag == OFF && qskip_flag == OFF
		&& sskip_flag == OFF)
		printf("** ");
	    else if (spy && !leap
		     && (fskip_flag == ON || qskip_flag == ON
			 || qskip_flag == ON))
		printf("*> ");
	    else if (!spy && fskip_flag == OFF && qskip_flag == OFF
		     && sskip_flag == OFF)
		return;
	    else if (fskip_flag == ON) {
		printf(">  ");
		fskip_flag = OFF;
	    } else if (qskip_flag == ON) {
		printf(">  ");
		qskip_flag = OFF;
	    } else if (sskip_flag == ON) {
		printf(">  ");
		sskip_flag = OFF;
	    } else if (xskip_flag == ON)
		return;
	    else if (semiskip_flag == ON)
		return;

	    if (leap)
		return;
	    else
		leap_point = NIL;

	    printf("(%d) FAIL: ", gettrace(goal));
	    print(goal);
	    dectrace(goal);
	    port = DBFAIL;
	    debugger(goal, bindings, rest);
	}
    } else if (port == DBCUTFAIL) {
	if (trace_flag == FULL || trace_flag == TIGHT) {
	    spy = spypointp(goal);
	    leap = leappointp(goal);
	    if (spy && !leap && fskip_flag == OFF && qskip_flag == OFF
		&& sskip_flag == OFF)
		printf("** ");
	    else if (spy && !leap
		     && (fskip_flag == ON || qskip_flag == ON
			 || qskip_flag == ON))
		printf("*> ");
	    else if (!spy && fskip_flag == OFF && qskip_flag == OFF
		     && sskip_flag == OFF)
		return;
	    else if (fskip_flag == ON) {
		printf(">  ");
		fskip_flag = OFF;
	    } else if (qskip_flag == ON) {
		printf(">  ");
		qskip_flag = OFF;
	    } else if (sskip_flag == ON) {
		printf(">  ");
		sskip_flag = OFF;
	    } else if (xskip_flag == ON)
		return;
	    else if (semiskip_flag == ON)
		return;

	    if (leap)
		return;
	    else
		leap_point = NIL;

	    printf("(%d) CUTFAIL: ", gettrace(goal));
	    print(goal);
	    clrtrace(goal);
	    port = DBFAIL;
	    debugger(goal, bindings, rest);
	}
    } else if (port == DBEXIT) {
	if (trace_flag == FULL) {
	    spy = spypointp(goal);
	    leap = leappointp(goal);

	    if (spy && !leap && qskip_flag == OFF && sskip_flag == OFF
		&& xskip_flag == OFF)
		printf("** ");
	    else if (spy && !leap
		     && (qskip_flag == ON || sskip_flag == ON
			 || xskip_flag == ON))
		printf("*> ");
	    else if (!spy && qskip_flag == OFF && sskip_flag == OFF
		     && xskip_flag == OFF)
		return;
	    else if (fskip_flag == ON)
		return;
	    else if (qskip_flag == ON) {
		printf(">  ");
		qskip_flag = OFF;
	    } else if (sskip_flag == ON) {
		printf(">  ");
		sskip_flag = OFF;
	    } else if (xskip_flag == ON) {
		printf("-> ");
		qskip_flag = OFF;
	    } else if (semiskip_flag == ON)
		return;

	    if (leap)
		return;
	    else
		leap_point = NIL;


	    printf("(%d) EXIT: ", gettrace(goal));
	    print(goal);
	    dectrace(goal);
	    port = DBEXIT;
	    debugger(goal, bindings, rest);
	}
    }
}

void inctrace(int goal)
{
    if (atomp(goal))
	SET_TR(goal, GET_TR(goal) + 1);
    else
	SET_TR(car(goal), GET_TR(car(goal)) + 1);
}

void dectrace(int goal)
{
    if (atomp(goal))
	SET_TR(goal, GET_TR(goal) - 1);
    else
	SET_TR(car(goal), GET_TR(car(goal)) - 1);
}

void clrtrace(int goal)
{
    if (atomp(goal))
	SET_TR(goal, 0);
    else
	SET_TR(car(goal), 0);
}

int gettrace(int goal)
{
    if (atomp(goal))
	return (GET_TR(goal));
    else
	return (GET_TR(car(goal)));
}

void debugger(int goal, int bindings, int rest)
{
    int c, save, i, read;

  loop:
    printf("?> ");
    fflush(stdout);
    c = getchar();
    FLUSH switch (c) {
    case 'a':
	FLUSH longjmp(buf, 1);
    case 'b':
	break_nest++;
	left_margin++;
      break_loop:
	for (i = 0; i <= break_nest; i++)
	    printf("?");

	printf("- ");
	fflush(stdout);
	read = variable_to_call(readparse());
	if (read == FEND)
	    goto break_exit;
	query(read);
	fflush(stdout);
	goto break_loop;
      break_exit:
	break_nest--;
	left_margin--;
	break;
    case EOL:
    case 'c':
	trace_flag = FULL;
	FLUSH break;
    case 'd':
	save = ignore_flag;
	ignore_flag = 1;
	print(goal);
	printf("\n");
	ignore_flag = save;
	goto loop;
    case 'e':
	longjmp(buf, 2);
    case 'f':
	fskip_flag = ON;
	break;
    case '?':
    case 'h':
	printf("return key: creep\n");
	printf("escape key: sskip\n");
	printf("a: abort to REPL\n");
	printf("b: break to REPL\n");
	printf("c: creep\n");
	printf("d: display goal\n");
	printf("e: end of intepreter\n");
	printf("f: skip to next FAIL port\n");
	printf("?: help\n");
	printf("h: help\n");
	printf("n: notrace\n");
	printf("q: skip to next EXIT or FAIL port\n");
	printf
	    ("s: skip to next EXIT or FAIL port (only in CALL or REDO port\n");
	printf
	    ("x: skip to next CALL or EXIT port (only in FAIL or REDO port\n");
	printf("w: write goal\n");
	printf("@: invoke REPL once\n");
	printf(";: skip to next REDO port (only in EXIT port)\n");
	fflush(stdin);
	goto loop;
    case 'l':
	leap_point = list3(SLASH, car(goal), makeint(length(goal) - 1));
	break;
    case 'n':
	debug_flag = OFF;
	break;
    case 'q':
	qskip_flag = ON;
	break;
    case ESC:			//escape
    case 's':
	if (port != DBCALL && port != DBREDO)
	    goto loop;
	sskip_flag = ON;
	break;
    case 'w':
	save = ignore_flag;
	ignore_flag = 0;
	print(goal);
	printf("\n");
	ignore_flag = save;
	goto loop;
    case 'x':
	if (port != DBFAIL && port != DBREDO)
	    goto loop;
	xskip_flag = ON;
	break;
    case '@':
	printf("?- ");
	fflush(stdout);
	read = variable_to_call(readparse());
	query(read);
	fflush(stdout);
	break;
    case ';':
	if (port != DBEXIT)
	    goto loop;
	semiskip_flag = ON;
	break;
    }
}


int varslist(int addr)
{
    if (nullp(addr))
	return (NIL);
    else if (variablep(addr))
	return (cons(addr, NIL));
    else if (!structurep(addr))
	return (NIL);
    else if (variablep(car(addr)))
	return (cons(car(addr), varslist(cdr(addr))));
    else if (structurep(addr) && car(addr) == AND)
	return (append(varslist(cadr(addr)), varslist(caddr(addr))));
    else if (structurep(addr) && car(addr) == OR)
	return (append(varslist(cadr(addr)), varslist(caddr(addr))));
    else if (!structurep(car(addr)))
	return (varslist(cdr(addr)));
    else
	return (append(varslist(car(addr)), varslist(cdr(addr))));
}

int valslist(int x)
{
    if (nullp(x))
	return (NIL);
    else
	return (cons(cons(car(x), deref1(car(x))), valslist(cdr(x))));
}

int operate(int x)
{
    int operator, operand1, operand2;

    operator = car(x);
    operand1 = cadr(x);
    operand2 = caddr(x);
    return ((GET_SUBR(operator)) (operand1, operand2));
}

int walpha_conversion(int x)
{
    int temp;

    if (nullp(x))
	return (NIL);
    else if (alpha_variable_p(x))
	return (x);
    else if (anoymousp(x))
	return (makevariant());
    else if (variablep(x))
	return (GET_CDR(x));
    else if (!structurep(x))
	return (x);
    else if (operationp(x) && nullp(caddr(x))) {	// e.g. :- foo(x)
	temp = wlist2(car(x), walpha_conversion(cadr(x)));
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else if (operationp(x)) {
	temp = wlist3(car(x),
		      walpha_conversion(cadr(x)),
		      walpha_conversion(caddr(x)));
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else if (listp(x)) {
	temp = wcons(walpha_conversion(car(x)), walpha_conversion(cdr(x)));
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else if (predicatep(x)) {
	temp = wcons(car(x), walpha_conversion(cdr(x)));
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else {			//buiiltin
	temp = wcons(walpha_conversion(car(x)), walpha_conversion(cdr(x)));
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    }
}

//-----print------------------
//output to standard output
void sprint(int addr)
{
    int save;

    save = output_stream;
    output_stream = standard_output;
    print(addr);
    output_stream = save;
}

//for answer unified variable
void printanswer(int addr)
{
    if (operatorp(addr) || eqlp(addr, DOTOBJ)) {
	printc('(');
	print(addr);
	printc(')');
    } else if (atom_quote_p(addr)) {
	print_quoted(addr);
    } else if (argumentsp(addr) && !ignore_flag && arguments_flag) {
	fprintf(GET_PORT(output_stream), "(");
	printarguments(addr);
    } else if (operationp(addr) && heavy999p(car(addr))) {	// e.g (a :- b)
	fprintf(GET_PORT(output_stream), "(");
	print(addr);
	fprintf(GET_PORT(output_stream), ")");
    } else
	print(addr);
}

//output to output_stream
void print(int addr)
{
    double x;

    if (IS_ALPHA(addr)) {
	fprintf(GET_PORT(output_stream), "v_%d", addr - CELLSIZE);
	return;
    }
    switch (GET_TAG(addr)) {
    case INTN:
	fprintf(GET_PORT(output_stream), "%d", GET_INT(addr));
	break;
    case FLTN:
	x = GET_FLT(addr);
	if (x - (int) x != 0.0)
	    fprintf(GET_PORT(output_stream), "%g", x);
	else
	    fprintf(GET_PORT(output_stream), "%0.1f", x);
	break;
    case LONGN:
	printlong(addr);
	break;
    case BIGX:
	print_bigx(addr);
	break;
    case SINGLE:
	if (addr == NIL)
	    fprintf(GET_PORT(output_stream), "[]");
	else if (variablep(addr))
	    fprintf(GET_PORT(output_stream), "%s", GET_NAME(addr));
	else if (quoted_flag && atom_quote_p(addr))
	    print_quoted(addr);
	else
	    print_not_quoted(addr);
	break;
    case STRUCT:
	if (sexp_flag) {
	    fprintf(GET_PORT(output_stream), "(");
	    printsexp(addr);
	} else if (postfixp(addr)) {
	    if (!ignore_flag)
		printpostfix(addr);
	    else {
		print(car(addr));
		fprintf(GET_PORT(output_stream), "(");
		print(cadr(addr));
		fprintf(GET_PORT(output_stream), ")");
	    }
	} else if (clausep(addr))
	    printclause(addr);
	else if (listp(addr)) {
	    if (!ignore_flag) {
		fprintf(GET_PORT(output_stream), "[");
		printlist(addr);
	    } else
		printlist_canonical(addr);
	} else if (eqlp(car(addr), CURL)) {
	    fprintf(GET_PORT(output_stream), "{");
	    printcurl(cdr(addr));
	} else if (mixturep(car(addr))) {
	    if (length(addr) == 2)
		goto prefix;
	    else
		goto infix;
	} else if (infixp(addr)) {
	  infix:
	    if (!ignore_flag)
		printinfix(addr);
	    else {
		if (car(addr) == DOTOBJ || car(addr) == AND || car(addr) == OR) {	// '.' ',' ';'
		    fprintf(GET_PORT(output_stream), "'");
		    print(car(addr));
		    fprintf(GET_PORT(output_stream), "'");
		} else		//other functor
		    print(car(addr));
		if (!nullp(cdr(addr))) {
		    fprintf(GET_PORT(output_stream), "(");
		    printtuple(cdr(addr));
		}
	    }
	} else if (prefixp(addr)) {
	  prefix:
	    if (!ignore_flag)
		printprefix(addr);
	    else {
		print(car(addr));
		fprintf(GET_PORT(output_stream), "(");
		print(cadr(addr));
		fprintf(GET_PORT(output_stream), ")");
	    }
	} else if (operationp(addr) ||
		   predicatep(addr) ||
		   builtinp(addr) || compiledp(addr) || functionp(addr)) {
	    print(car(addr));
	    if (!nullp(cdr(addr))) {
		fprintf(GET_PORT(output_stream), "(");
		printtuple(cdr(addr));
	    }
	} else {
	    fprintf(GET_PORT(output_stream), "#[");
	    printlist(addr);
	}
	break;
    case STREAM:
	if (addr == standard_input)
	    fprintf(GET_PORT(output_stream), "<stdin>");
	else if (addr == standard_output)
	    fprintf(GET_PORT(output_stream), "<stdout>");
	else if (addr == standard_error)
	    fprintf(GET_PORT(output_stream), "<stderr>");
	else
	    fprintf(GET_PORT(output_stream), "<stream%d>", addr);
	break;
    case STR:
	if (quoted_flag)
	    fprintf(GET_PORT(output_stream), "$%s$", GET_NAME(addr));
	else
	    fprintf(GET_PORT(output_stream), "%s", GET_NAME(addr));
	break;
    default:
	fprintf(GET_PORT(output_stream), "<undef>");
	break;
    }
}

void print_quoted(int addr)
{
    char str[ATOMSIZE], c;
    int pos;

    strcpy(str, GET_NAME(addr));
    pos = 0;
    c = str[pos];
    fprintf(GET_PORT(output_stream), "%c", '\'');
    while (c != NUL) {
	if (c == '\\') {
	    pos++;
	    c = str[pos];
	    if (c == NUL) {
		fprintf(GET_PORT(output_stream), "%c", '\\');
		goto exit;
	    } else if (c == '"') {
		fprintf(GET_PORT(output_stream), "%c", c);
		pos++;
	    } else {
		fprintf(GET_PORT(output_stream), "%c", '\\');
		fprintf(GET_PORT(output_stream), "%c", c);
		pos++;
	    }
	} else if (c == '\'') {
	    fprintf(GET_PORT(output_stream), "%c", '\'');
	    fprintf(GET_PORT(output_stream), "%c", c);
	    pos++;
	} else if (c <= 31) {
	    fprintf(GET_PORT(output_stream), "%c", '\\');
	    fprintf(GET_PORT(output_stream), "%o", c);
	    fprintf(GET_PORT(output_stream), "%c", '\\');
	    pos++;
	} else if (isUni2(c)) {
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	} else if (isUni3(c)) {
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	} else if (isUni4(str[0])) {
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	} else if (isUni5(str[0])) {
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	} else if (isUni6(str[0])) {
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);
	} else
	    fprintf(GET_PORT(output_stream), "%c", str[pos++]);


	c = str[pos];
    }
  exit:
    fprintf(GET_PORT(output_stream), "%c", '\'');
}

void print_not_quoted(int addr)
{
    char str[ATOMSIZE], c;
    int pos;


    strcpy(str, GET_NAME(addr));
    pos = 0;
    c = str[pos];
    while (c != NUL) {
	if (c == '\\') {
	    pos++;
	    c = str[pos];
	    if (c == 'n')
		fprintf(GET_PORT(output_stream), "%c", EOL);
	    else if (c == 't')
		fprintf(GET_PORT(output_stream), "%c", TAB);
	    else if (c == 'f')
		fprintf(GET_PORT(output_stream), "%c", FF);
	    else if (c == 'r')
		fprintf(GET_PORT(output_stream), "%c", CR);
	    else if (c == 'v')
		fprintf(GET_PORT(output_stream), "%c", VT);
	    else if (c == 'a')
#if _WIN32
		MessageBeep(-1);
#else
		printf("\a");
#endif
	    else if (c == 'b')
		fprintf(GET_PORT(output_stream), "%c", BS);
	    else if (c == NUL)
		return;
	    else {
		fprintf(GET_PORT(output_stream), "%c", str[pos - 1]);
		fprintf(GET_PORT(output_stream), "%c", c);
	    }
	} else
	    fprintf(GET_PORT(output_stream), "%c", c);
	pos++;
	c = str[pos];
    }
}

void printc(char c)
{
    fprintf(GET_PORT(output_stream), "%c", c);
}

void printlong(int addr)
{
    fprintf(GET_PORT(output_stream), "%lld", GET_LONG(addr));
}

/*
print infix notation 
get_2nd_weight means weight of infix operater
check the weight of argument and if it needs ( ) print paren. 
*/
void printinfix(int addr)
{
    if (length(addr) == 2) {
	print(car(addr));
	print(cadr(addr));
    } else if (alphabeticalp(car(addr))) {
	print(cadr(addr));
	printc(' ');
	print(car(addr));
	printc(' ');
	print(caddr(addr));
    } else {
	if (infix_operator_p(cadr(addr))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(cadr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else if (infixp(cadr(addr)) &&
		   get_2nd_weight(car(cadr(addr))) >
		   get_2nd_weight(car(addr))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(cadr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else
	    print(cadr(addr));

	print(car(addr));

	if (infix_operator_p(caddr(addr))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(caddr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else if (infixp(caddr(addr)) &&
		   get_2nd_weight(car(caddr(addr))) >
		   get_2nd_weight(car(addr))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(caddr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else if (infixp(cadr(addr)) && infixp(caddr(addr)) &&
		   get_2nd_weight(car(cadr(addr))) <
		   get_2nd_weight(car(caddr(addr)))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(caddr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else if (single_operation_p(caddr(addr))) {
	    fprintf(GET_PORT(output_stream), " ");
	    print(caddr(addr));
	} else
	    print(caddr(addr));
    }
}



void printprefix(int addr)
{
    if (alphabeticalp(car(addr))) {
	print(car(addr));
	printc(' ');
	print(cadr(addr));
    } else {
	print(car(addr));
	print(cadr(addr));
    }
}

void printpostfix(int addr)
{
    if (alphabeticalp(car(addr))) {
	print(cadr(addr));
	printc(' ');
	print(car(addr));
    } else {
	print(cadr(addr));
	print(car(addr));
    }
}



void printsexp(int addr)
{
    if (nullp(addr))
	fprintf(GET_PORT(output_stream), ")");
    else if ((!(structurep(cdr(addr)))) && (!(nullp(cdr(addr))))) {
	print(car(addr));
	fprintf(GET_PORT(output_stream), " . ");
	print(cdr(addr));
	fprintf(GET_PORT(output_stream), ")");
    } else {
	print(car(addr));
	if (!nullp(cdr(addr)))
	    fprintf(GET_PORT(output_stream), " ");
	printsexp(cdr(addr));
    }
}

void printarguments(int addr)
{
    if (!structurep(caddr(addr))) {
	print(cadr(addr));
	fprintf(GET_PORT(output_stream), ",");
	print(caddr(addr));
	fprintf(GET_PORT(output_stream), ")");
    } else {
	print(cadr(addr));
	fprintf(GET_PORT(output_stream), ",");
	printarguments(caddr(addr));
    }
}

void printlist(int addr)
{
    if (nullp(addr))
	fprintf(GET_PORT(output_stream), "]");
    else if ((!(structurep(cdr(addr)))) && (!(nullp(cdr(addr))))) {
	if (operationp(car(addr)) &&
	    !argumentsp(car(addr)) && heavy999p(car(car(addr)))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(car(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else if (car(addr) == AND) {
	    fprintf(GET_PORT(output_stream), "','");
	} else if (car(addr) == DOTOBJ) {
	    fprintf(GET_PORT(output_stream), "'.'");
	} else
	    print(car(addr));

	fprintf(GET_PORT(output_stream), "|");

	if (operationp(cdr(addr)) &&
	    !argumentsp(cdr(addr)) && heavy999p(car(cdr(addr)))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(cdr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else
	    print(cdr(addr));
	fprintf(GET_PORT(output_stream), "]");
    } else {
	if (operationp(car(addr)) &&
	    !argumentsp(car(addr)) && heavy999p(car(car(addr)))) {
	    fprintf(GET_PORT(output_stream), "(");
	    print(car(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else if (car(addr) == AND) {
	    fprintf(GET_PORT(output_stream), "','");
	} else if (car(addr) == DOTOBJ) {
	    fprintf(GET_PORT(output_stream), "'.'");
	} else
	    print(car(addr));
	if (!nullp(cdr(addr)))
	    fprintf(GET_PORT(output_stream), ",");
	printlist(cdr(addr));
    }
}

void printlist_canonical(int addr)
{
    if (nullp(addr))
	print(NIL);
    else if (!listp(cdr(addr))) {
	fprintf(GET_PORT(output_stream), "'.'(");
	print(car(addr));
	fprintf(GET_PORT(output_stream), ",");
	print(cdr(addr));
	fprintf(GET_PORT(output_stream), ")");
    } else {
	fprintf(GET_PORT(output_stream), "'.'(");
	print(car(addr));
	fprintf(GET_PORT(output_stream), ",");
	printlist_canonical(cdr(addr));
	fprintf(GET_PORT(output_stream), ")");
    }
}

void printcurl(int addr)
{
    arguments_flag = 0;		//(1,2,3) -> 1,2,3
    if (nullp(addr)) {
	fprintf(GET_PORT(output_stream), "}");
	arguments_flag = 1;
    } else {
	print(car(addr));
	if (!nullp(cdr(addr)))
	    fprintf(GET_PORT(output_stream), ",");
	printcurl(cdr(addr));
    }
}

void printtuple(int addr)
{
    if (nullp(addr))
	fprintf(GET_PORT(output_stream), ")");
    else {
	print(car(addr));
	if (!nullp(cdr(addr)))
	    fprintf(GET_PORT(output_stream), ",");
	printtuple(cdr(addr));
    }
}

void printclause(int addr)
{

    if (listing_flag) {
	if (nullp(caddr(addr))) {	// e.g. :- foo(x).
	    fprintf(GET_PORT(output_stream), "(:- ");
	    print(cadr(addr));
	    fprintf(GET_PORT(output_stream), ")");
	} else {		// e.g. foo(x) :- boo(x).
	    print(cadr(addr));
	    fprintf(GET_PORT(output_stream), " :-\n    ");
	    printbody(caddr(addr));
	}
    } else {
	if (!ignore_flag) {
	    if (nullp(caddr(addr))) {	// e.g :- foo(x).
		fprintf(GET_PORT(output_stream), ":- ");
		print(cadr(addr));
	    } else {		//normal case  foo(X) :- bar(X).
		print(cadr(addr));
		fprintf(GET_PORT(output_stream), ":-");
		print(caddr(addr));
	    }
	} else {
	    if (nullp(caddr(addr))) {	// e.g :- foo(x).
		fprintf(GET_PORT(output_stream), ":-(");
		print(cadr(addr));
		fprintf(GET_PORT(output_stream), ")");
	    } else {		// normal case foo(X) :- bar(X).
		fprintf(GET_PORT(output_stream), ":-(");
		print(cadr(addr));
		fprintf(GET_PORT(output_stream), ",");
		print(caddr(addr));
		fprintf(GET_PORT(output_stream), ")");
	    }
	}
    }
}

void printbody(int addr)
{

    if (operationp(addr) && car(addr) == AND) {
	printbody(cadr(addr));
	print(car(addr));
	fprintf(GET_PORT(output_stream), "\n    ");
	printbody(caddr(addr));
    } else if (operationp(addr) && car(addr) == OR) {
	fprintf(GET_PORT(output_stream), "(");
	printbody1(cadr(addr));
	print(car(addr));
	printbody1(caddr(addr));
	fprintf(GET_PORT(output_stream), ")");
    } else {
	print(addr);
    }
}

void printbody1(int addr)
{
    if (operationp(addr)) {
	print(cadr(addr));
	print(car(addr));
	printbody1(caddr(addr));
    } else
	print(addr);
}


int laststr(char buf[])
{
    int i;

    i = 0;
    while (buf[i] != NUL)
	i++;
    return (i - 1);
}
