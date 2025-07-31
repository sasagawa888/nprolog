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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include <curl/curl.h>
#include "npl.h"

//global vers
int proof[THREADSIZE];
int nest = 0;
cell heap[CELLSIZE];
int cell_hash_table[HASHTBSIZE];
int variant[VARIANTSIZE][THREADSIZE];
int bigcell[BIGSIZE];
int stack[STACKSIZE][THREADSIZE];
int record_hash_table[HASHTBSIZE][RECORDMAX];	// for hash record database 
int record_pt = 1;		// current index of record database
int counter[31];		// counter str_set,str_dec ... 
int catch_data[CTRLSTK][2][THREADSIZE];	//catch tag,sp,wp
char bridge[BUFSIZE];		// for string_term/2 and parallel buffer
char transfer[BUFSIZE];		// buffer for dp_transfer
token stok = { GO, OTHER };

jmp_buf catch_buf[CTRLSTK][THREADSIZE];	// catch jump buffer
jmp_buf buf;			// for REPL halt and error handling.
jmp_buf buf1;			// for n_error/2 error check.
jmp_buf buf2;			// for break/0 end_of_file/0 exit break
__thread jmp_buf buf3;		// for multi-threaded error handling.
int variables[THREADSIZE];
int variables_save[THREADSIZE];
int end_of_file_answer = NIL;
int end_of_file_rest = NIL;
int predicates = NIL;
int builtins = NIL;
int spy_list = NIL;
int reconsult_list = NIL;
int execute_list = NIL;
int dynamic_list = NIL;
int op_list = NIL;
int key_list = NIL;
int error_code = 0;
int eval_context;
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

//error_handler
int instantation_tag;
int uninstantation_tag;
int type_tag;
int domain_tag;
int exsistence_tag;
int permisson_tag;
int context_tag;
int syntax_tag;
int evaluation_tag;
int representation_tag;
int consistency_tag;
int resource_tag;
int system_tag;


//------pointer----
int hp;				//heap pointer
int sp[THREADSIZE];		//stack pointer
int fc;				//free counter
int ac[THREADSIZE];		//alpha conversion variable count
int wp[THREADSIZE];		//working pointer
int gc;				//invoked GC count
int wp_min[THREADSIZE];		// start wp point in each thread
int wp_max[THREADSIZE];		// end wp point in each thread
int cp[THREADSIZE];		// catch pointer
int unique_num = 0;		// for copy_term/2        

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
int bridge_flag = 0;		//for string_term/2 0=normal, 1=readparse from bridge
int ctrl_c_flag = 0;		//for ctrl_c  to stop prove
int init_flag = 1;		//for halt
int script_flag = 0;		// script mode, 0=not scriplt-mode, 1=script-mode.
int check_flag = 0;		// for n_error/2 error check
int break_flag = 0;		// for break/0 0=normal,1=break.
int parallel_exit_flag = 0;	/* To exit parallel threads */
int process_flag = 0;		/* when invoke as child process, flag is 1 */
int thread_flag = 0;		/* when invoke as multi thread, flag is 1 */
int child_flag = 0;		/* when invoke as network child, flag is 1 */
int connect_flag = 0;		/* when child listen, connect_flag is 1 */
int receiver_exit_flag = 0;	/* TO exit child TCP/IP receiver */
int child_busy_flag = 0;	/* while executing in child, child_busy_flag is 1 */
int parent_flag = 0;		/* while comunicating child, parent_flag = 1 */
int pause_flag = 0;		/* while pause in child, pause_flag = 1 */
int shutdown_flag = 0;		/* when receive dp_close, shutdown_flag = 1 */
int active_thread = 0;		/* for mt_and/1 mt_or/1 */
int dynamic_flag = 0;		/* for dynamic predicate. while assertz dynamic flag = 1 */
int string_flag = 0;		/* ARITY/PROLOG mode 0, ISO mode 1 */
int ifthenelse_false_flag = 0;	/* ifthenelse occures NFLASE set flag = 1 */
int compiled_flag = 0;		/* while execute compiled code falg = 1, else 0 */

//stream
int standard_input;
int standard_output;
int standard_error;
int input_stream;
int output_stream;
int error_stream;

/* -----distributed parallel & TCPIP------*/
int parent_sockfd[2];
int child_sockfd[PARASIZE];
socklen_t parent_len;
struct sockaddr_in parent_addr, child_addr[PARASIZE];
int child_num;
pthread_t receiver_thread;
int child_result[PARASIZE];

/* multi thread */
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
int mt_queue[PARASIZE];
int mt_queue_pt;
int mt_queue_num;
int thread_num = 0;
int para_input[PARASIZE];
int para_output[PARASIZE];
pthread_t mt_para_thread[PARASIZE];
pthread_cond_t mt_cond_para[PARASIZE];
pthread_cond_t mt_cond_main;
pthread_cond_t mt_cond_queue;
pthread_attr_t mt_para_attr[PARASIZE];
size_t mt_para_size[PARASIZE];

/* module */
int module_name;		// module name
int export_data[256][2];	// export name,arity
int module_flag;		// inner module 1, else 0
int export_pt;			// export data pointer

/* -----TCPIP for server----------------*/
socklen_t server_len;
struct sockaddr_in server_addr, client_addr;

/* -----CLPFD-------------------------- */
int fd_sets = NIL;
int fd_domain[256];
int fd_var_max;
int fd_var_idx;
int fd_min[256];
int fd_max[256];
int fd_len[256];
int fd_unique[256];
int fd_analyze_sw;
int fd_selected[256];
int fd_sel_idx;
int fd_var_free;
int fd_vars = NIL;
int fd_removed[256][256];
int fd_rem_idx[256];
int fd_rem_sw;
int fd_queue[2048];
int fd_deque_idx;
int fd_enque_idx;
int fd_trace;

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
    printf("-n          -- NPL run with network mode.\n");
    printf("-r          -- NPL does not use editable REPL.\n");
    printf("-s filename -- NPL run file with script mode.\n");
    printf("-v          -- dislplay version number.\n");
}

int main(int argc, char *argv[])
{
    int ch, input;
    char *path;
    struct winsize w;
    FILE *fp;

    signal(SIGINT, reset);
    init_cell();
    init_builtin();
    init_operator();
    init_stream();
    init_handler();
    ioctl(0, TIOCGWINSZ, &w);
    ed_hight = w.ws_row;
    ed_width = w.ws_col;
    input_stream = standard_input;
    output_stream = standard_output;
    error_stream = standard_error;
    wp[0] = HEAPSIZE + 1;
    wp_min[0] = HEAPSIZE + 1;
    wp_max[0] = CELLSIZE;
    init_repl();
    int ret = setjmp(buf);
    if (!init_flag) {
	goto repl;
    }

    path = prolog_file_name("library/startup.pl");
    if (path)
	b_consult(list1(makeconst("library/startup.pl")), NIL, 0);

    while ((ch = getopt(argc, argv, "c:s:rhvn")) != -1) {
	switch (ch) {
	case 'c':
	    b_consult(list1(makeconst(optarg)), NIL, 0);
	    break;
	case 's':
	    b_consult(list1(makeconst(optarg)), NIL, 0);
	    exit(EXIT_SUCCESS);
	    break;
	case 'r':
	    repl_flag = 0;
	    break;
	case 'v':
	    printf("N-Prolog Ver %1.2f\n", VERSION);
	    exit(EXIT_SUCCESS);
	case 'h':
	    usage();
	    exit(EXIT_SUCCESS);
	case 'n':
	    printf("N-Prolog runs with network mode.\n");
	    fp = fopen("network.pl", "r");
	    if (fp != NULL) {
		fclose(fp);
		b_consult(list1(makeconst("network.pl")), NIL, 0);
	    }
	    child_flag = 1;
	    init_parent();
	    init_receiver();
	    break;
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
	    if (!child_flag) {
		input_stream = standard_input;
		output_stream = standard_output;
		error_stream = standard_error;
		init_repl();
		printf("?- ");
		fflush(stdout);
		input = variable_to_call(readparse(0));
		if (!repl_flag)
		    clear_input_buffer();
		query(input, 0);
		//sexp_flag = 1;print(input);
		//printf("proof = %d\n", proof);
		fflush(stdout);
	    } else if (child_flag) {
		input_stream = standard_input;
		output_stream = standard_output;
		error_stream = standard_error;
		init_repl();
		input =
		    variable_to_call(convert_to_variable
				     (str_to_pred(receive_from_parent()),
				      0));
		printf("Receive from parent ");
		sprint(input);
		printf("\n");
		fflush(stdout);
		child_busy_flag = 1;
		query(input, 0);
		child_busy_flag = 0;
		printf("Send to parent ");
		printf("\n");
		fflush(stdout);
	    }
    } else if (ret == 1) {
	ret = 0;
	goto repl;
    } else {
	if (shutdown_flag) {
	    printf("Shutting down the system...\n");
	    int ret = system("sudo shutdown now");
	    if (ret == -1)
		exception(SYSTEM_ERR, makestr("dp_close shatdown"), NIL,
			  0);
	}
	return 0;
    }
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
    int i, j;

    stok.flag = GO;
    nest = 0;
    for (i = 0; i < THREADSIZE; i++) {
	sp[i] = 0;
	proof[i] = 0;
	ac[i] = CELLSIZE + 1;
	cp[i] = 0;
    }
    for (i = 0; i <= thread_num; i++) {
	wp[i] = wp_min[i];
    }
    ctrl_c_flag = 0;
    compiled_flag = 0;
    fskip_flag = OFF;
    sskip_flag = OFF;
    xskip_flag = OFF;
    semiskip_flag = OFF;
    leap_point = NIL;
    left_margin = 4;
    big_pt0 = 0;
    //initialize variant variable
    for (i = 0; i < VARIANTSIZE; i++) {
	for (j = 0; j < THREADSIZE; j++) {
	    variant[i][j] = UNBIND;
	}
    }
    for (j = 0; j < THREADSIZE; j++) {
	i = variables[j];
	while (!nullp(i)) {
	    SET_CAR(car(i), UNBIND);
	    SET_CDR(car(i), UNBIND);
	    i = cdr(i);
	}
    }
    //initialize spy-point trace-level
    i = spy_list;
    while (!nullp(i)) {
	SET_TR(cadar(i), 0);
	i = cdr(i);
    }
    // CLPFD
    fd_sets = NIL;
    fd_var_max = 0;
    fd_var_idx = 0;
    fd_sel_idx = 0;
    fd_var_free = 0;
    fd_deque_idx = 0;
    fd_enque_idx = 0;
    for (i = 0; i < 256; i++) {
	fd_domain[i] = -1;
	fd_unique[i] = 0;
	fd_rem_idx[i] = 0;
    }
    while (!nullp(fd_vars)) {
	SET_ARITY(car(fd_vars), 0);
	SET_VAR(car(fd_vars), 0);
	fd_vars = cdr(fd_vars);
    }
}

void query(int x, int th)
{
    int res;

    // DCG syntax e.g. a-->b.
    if (dcgp(x)) {
	operate(x, th);
	return;
    }
    //[file1,file2] -> consult(file1),consult(file2).
    if (listp(x))
	x = list_to_ope(x, th);

    if (atomp(x) && !builtinp(x) && !compiledp(x))
	x = makepred(GET_NAME(x));

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makestr("?-"), x, th);

    if (!callablep(x))
	exception(NOT_CALLABLE, makestr("?-"), x, th);

    variables[th] = listreverse(unique(varslist(x)));
    res = prove_all(addask(x, th), sp[th], th);
    if (!child_flag) {
	ESCRST;
	print(res);
	printf("\n");
    } else {
	bridge_flag = 1;
	if (res == YES) {
	    printstr("dp_countup(");
	    printint(proof[th]);
	    printstr("),");
	    printstr("true.\n");
	} else {
	    printstr("dp_countup(");
	    printint(proof[th]);
	    printstr("),");
	    printstr("fail.\n");
	}
	bridge_flag = 0;
	send_to_parent_buffer();
    }
    return;
}

void query_break(int x, int th)
{
    int res;

    // DCG syntax e.g. a-->b.
    if (dcgp(x)) {
	operate(x, th);
	return;
    }
    //[file1,file2] -> consult(file1),consult(file2).
    if (listp(x))
	x = list_to_ope(x, th);

    if (atomp(x) && !builtinp(x) && !compiledp(x))
	x = makepred(GET_NAME(x));

    if (wide_variable_p(x))
	exception(INSTANTATION_ERR, makestr("?="), x, th);

    if (!callablep(x)) {
	exception(NOT_CALLABLE, makestr("?="), x, th);
    }

    variables_save[th] = variables[th];
    variables[th] = listreverse(unique(varslist(x)));
    res = prove_all(addask(x, th), sp[th], th);
    variables[th] = variables_save[th];
    ESCRST;
    print(res);
    printf("\n");
    return;
}


int list_to_ope(int x, int th)
{
    if (nullp(x))
	exception(SYNTAX_ERR, makestr("?-"), x, 0);
    else if (nullp(cdr(x))) {
	if (atomp(car(x)))
	    return (list2(makeatom("consult", SYS), car(x)));
	else if (caar(x) == makeatom("-", OPE))
	    return (list2(makeatom("reconsult", SYS), cadr(car(x))));
    } else {
	if (atomp(car(x)))
	    return (list3(makeatom(",", OPE),
			  list2(makeatom("consult", SYS), car(x)),
			  list_to_ope(cdr(x), th)));
	else if (caar(x) == makeatom("-", OPE))
	    return (list3(makeatom(",", OPE),
			  list2(makeatom("reconsult", SYS), cadr(car(x))),
			  list_to_ope(cdr(x), th)));
    }
    return (NIL);
}

int addask(int x, int th)
{
    return (addtail_body(makeatom("%ask", SYS), x, th));
}


int addtail_body(int x, int y, int th)
{
    if (nullp(y))
	return (x);
    else if (!conjunctionp(y))
	return (wlist3(AND, y, x, th));
    else
	return (wlist3
		(car(y), cadr(y), addtail_body(x, caddr(y), th), th));
}


int prove_all(int goals, int bindings, int th)
{
    int res;

    if (compiled_flag)
	return (exec_all(goals, bindings, th));


    if (nullp(goals))
	return (YES);
    else if (car(goals) != AND)
	return (prove(goals, bindings, NIL, th));
    else {
	if (structurep(cadr(goals)) && car(cadr(goals)) == AND &&
	    structurep(caddr(goals)) && car(caddr(goals)) == AND) {
	    if (prove_all(cadr(goals), bindings, th) == YES)
		if (prove_all(caddr(goals), bindings, th) == YES)
		    return (YES);
		else
		    return (NO);
	    else
		return (NO);
	} else if (!has_cut_p(goals)) {
	    return (prove(cadr(goals), bindings, caddr(goals), th));
	} else {
	    if (prove_all(before_cut(goals), bindings, th) == YES) {
		res = prove_all(after_cut(goals), sp[th], th);
		if (res == YES)
		    return (YES);
		else if (res == NO)
		    return (NFALSE);
	    } else
		return (NO);
	}
    }

    return (NO);
}

int prove(int goal, int bindings, int rest, int th)
{
    int clause, clauses, clause1, varlis, save1, save2, res;


    proof[th]++;
    if (ctrl_c_flag) {
	printf("ctrl+C\n");
	longjmp(buf, 1);
    }

    if (pause_flag) {
	printf("pause\n");
	while (1) {
	    sleep(1);
	    if (!pause_flag)
		break;
	}
	printf("resume\n");
    }


    if (nest > 40000)
	exception(RESOURCE_ERR, NIL, makestr("prove recursion over max"),
		  th);

    goal = deref(goal, th);

    if (nullp(goal)) {
	return (prove_all(rest, bindings, th));
    } else if (builtinp(goal)) {
	if (atomp(goal)) {
	    if ((res = (GET_SUBR(goal)) (NIL, rest, th)) == YES)
		return (YES);

	    return (res);
	} else {
	    if ((res = (GET_SUBR(car(goal))) (cdr(goal), rest, th)) == YES)
		return (YES);

	    return (res);
	}
    } else if (compiledp(goal)) {
	if (atomp(goal)) {
	    if ((GET_SUBR(goal)) (NIL, rest, th) == YES)
		return (YES);

	    return (NO);
	} else {
	    if ((GET_SUBR(car(goal))) (cdr(goal), rest, th) == YES)
		return (YES);

	    return (NO);
	}
    } else if (predicatep(goal) || user_operation_p(goal)) {
	//trace
	if (debug_flag == ON)
	    prove_trace(DBCALL, goal, bindings, rest, th);

	if (atomp(goal)) {
	    clauses = GET_CAR(goal);
	    if (clauses != NIL && !memberp(makeint(0), GET_ARITY(goal)))
		exception(ARITY_ERR, makestr("prove"), goal, th);
	} else {
	    clauses = GET_CAR(car(goal));
	    if (clauses != NIL
		&& !memberp(makeint(length(cdr(goal))),
			    GET_ARITY(car(goal))))
		exception(ARITY_ERR, makestr("prove"), goal, th);
	}

	if (clauses == NIL) {
	    if (exist_flag == YES)
		exception(EXISTENCE_ERR, NIL, goal, th);
	    else if (exist_flag == NO)
		return (NO);

	}
	while (!nullp(clauses)) {
	    save1 = wp[th];
	    save2 = ac[th];
	    clause = car(clauses);
	    clauses = cdr(clauses);
	    varlis = GET_VAR(clause);
	    pthread_mutex_lock(&mutex1);
	    assign_variant(varlis, th);
	    clause1 = walpha_conversion(clause, th);
	    release_variant(varlis);
	    pthread_mutex_unlock(&mutex1);

	    // case of predicate
	    if (predicatep(clause1) || user_operation_p(clause1)) {
		if (unify(goal, clause1, th) == YES) {
		    if (prove_all(rest, sp[th], th) == YES) {
			//trace
			if (debug_flag == ON)
			    prove_trace(DBEXIT, goal, bindings, rest, th);

			return (YES);
		    } else {
			//trace
			if (debug_flag == ON)
			    prove_trace(DBFAIL, goal, bindings, rest, th);
		    }
		}
	    }
	    // case of clause
	    else {
		if (unify(goal, (cadr(clause1)), th) == YES) {
		    clause1 = addtail_body(rest, caddr(clause1), th);
		    nest++;
		    if ((res = prove_all(clause1, sp[th], th)) == YES) {
			nest--;
			//trace
			if (debug_flag == ON)
			    prove_trace(DBEXIT, goal, bindings, rest, th);

			return (YES);
		    } else {
			nest--;
			if (res == NFALSE) {	// when after cut occurs cut off backtracking and return NO
			    //trace
			    if (debug_flag == ON)
				prove_trace(DBCUTFAIL, goal, bindings,
					    rest, th);
			    wp[th] = save1;
			    ac[th] = save2;
			    unbind(bindings, th);
			    /* When a cut plus fail results in NFALSE within ifthenelse/3,
			     * the flag is turned off and NFALSE is returned to the caller.
			     */
			    if (ifthenelse_false_flag) {
				ifthenelse_false_flag = 0;
				return (NFALSE);
			    }
			    return (NO);
			}
		    }
		}
	    }
	    //trace
	    if (debug_flag == ON && !nullp(clauses))
		prove_trace(DBREDO, goal, bindings, rest, th);

	    wp[th] = save1;
	    ac[th] = save2;
	    unbind(bindings, th);
	}
	//trace
	if (debug_flag == ON)
	    prove_trace(DBFAIL, goal, bindings, rest, th);

    } else if (disjunctionp(goal)) {
	if (ifthenp(cadr(goal))) {
	    goal =
		wcons(IFTHENELSE,
		      wcons(cadr(cadr(goal)),
			    wcons(caddr(cadr(goal)),
				  wcons(caddr(goal), NIL, th), th), th),
		      th);
	    // redefine goal = ifthenelse(if,then,else)
	    return (prove(goal, bindings, rest, th));
	} else
	    if ((res =
		 prove_all(addtail_body(rest, cadr(goal), th), bindings,
			   th))
		== YES)
	    return (YES);
	else {
	    if (res == NFALSE) {
		unbind(bindings, th);
		return (NO);
	    }
	    unbind(bindings, th);
	    if (prove_all
		(addtail_body(rest, caddr(goal), th), bindings, th) == YES)
		return (YES);
	    else {
		unbind(bindings, th);
		return (NO);
	    }
	}
	unbind(bindings, th);
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
    else if (conjunctionp(x) && caddr(x) == CUT)
	return (cadr(x));
    else if (cadr(x) == CUT)
	return (NIL);
    else if (conjunctionp(caddr(x)) && cadr(caddr(x)) == CUT)
	return (cadr(x));
    else
	return (wlist3(AND, cadr(x), before_cut(caddr(x)), 0));

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

void prove_trace(int port, int goal, int bindings, int rest, int th)
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
	read = variable_to_call(readparse(0));
	if (read == FEND)
	    goto break_exit;
	query(read, 0);
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
	read = variable_to_call(readparse(0));
	query(read, 0);
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
	return (cons(cons(car(x), deref1(car(x), 0)), valslist(cdr(x))));
}

int operate(int x, int th)
{
    int operator, operand1, operand2;

    operator = car(x);
    operand1 = cadr(x);
    operand2 = caddr(x);
    return ((GET_SUBR(operator)) (operand1, operand2, th));
}

int walpha_conversion(int x, int th)
{
    int temp;

    if (nullp(x))
	return (NIL);
    else if (alpha_variable_p(x))
	return (x);
    else if (anonymousp(x))
	return (makevariant(th));
    else if (variablep(x))
	return (GET_CDR(x));
    else if (!structurep(x))
	return (x);
    else if (operationp(x) && nullp(caddr(x))) {	// e.g. :- foo(x)
	temp = wlist2(car(x), walpha_conversion(cadr(x), th), th);
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else if (operationp(x)) {
	temp = wlist3(car(x),
		      walpha_conversion(cadr(x), th),
		      walpha_conversion(caddr(x), th), th);
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else if (listp(x)) {
	temp =
	    wcons(walpha_conversion(car(x), th),
		  walpha_conversion(cdr(x), th), th);
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else if (predicatep(x)) {
	temp = wcons(car(x), walpha_conversion(cdr(x), th), th);
	SET_AUX(temp, GET_AUX(x));
	return (temp);
    } else {			//buiiltin
	temp =
	    wcons(walpha_conversion(car(x), th),
		  walpha_conversion(cdr(x), th), th);
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
	printc('(');
	printarguments(addr);
    } else if (operationp(addr) && heavy999p(car(addr))) {	// e.g (a :- b)
	printc('(');
	print(addr);
	printc(')');
    } else
	print(addr);
}


void print(int addr)
{
    double x;
    char str1[STRSIZE];

    if (IS_ALPHA(addr)) {
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "v_%d", addr - CELLSIZE);
	else {
	    sprintf(str1, "v_%d", addr - CELLSIZE);
	    strcat(bridge, str1);
	}
	return;
    }
    switch (GET_TAG(addr)) {
    case INTN:
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "%d", GET_INT(addr));
	else {
	    sprintf(str1, "%d", GET_INT(addr));
	    strcat(bridge, str1);
	}
	break;
    case FLTN:
	x = GET_FLT(addr);
	if (x - (int) x != 0.0) {
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), "%g", x);
	    else {
		sprintf(str1, "%g", x);
		strcat(bridge, str1);
	    }
	} else {
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), "%0.1f", x);
	    else {
		sprintf(str1, "%0.1f", x);
		strcat(bridge, str1);
	    }
	}
	break;
    case LONGN:
	printlong(addr);
	break;
    case BIGX:
	print_bigx(addr);
	break;
    case SINGLE:
	if (addr == NIL) {
	    printstr("[]");
	} else if (variablep(addr)) {
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), "%s", GET_NAME(addr));
	    else {
		sprintf(str1, "%s", GET_NAME(addr));
		strcat(bridge, str1);
	    }
	} else if (quoted_flag && atom_quote_p(addr))
	    print_quoted(addr);
	else
	    print_not_quoted(addr);
	break;
    case STRUCT:
	if (sexp_flag) {
	    printc('(');
	    printsexp(addr);
	} else if (postfixp(addr)) {
	    if (!ignore_flag)
		printpostfix(addr);
	    else {
		print(car(addr));
		printc('(');
		print(cadr(addr));
		printc(')');
	    }
	} else if (clausep(addr))
	    printclause(addr);
	else if (listp(addr)) {
	    if (!ignore_flag) {
		printc('[');
		printlist(addr);
	    } else
		printlist_canonical(addr);
	} else if (eqlp(car(addr), NCURL)) {
	    printc('{');
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
		    printc('\'');
		    print(car(addr));
		    printc('\'');
		} else		//other functor
		    print(car(addr));
		if (!nullp(cdr(addr))) {
		    printc('(');
		    printtuple(cdr(addr));
		}
	    }
	} else if (prefixp(addr)) {
	  prefix:
	    if (!ignore_flag)
		printprefix(addr);
	    else {
		print(car(addr));
		printc('(');
		print(cadr(addr));
		printc(')');
	    }
	} else if (operationp(addr) ||
		   predicatep(addr) ||
		   builtinp(addr) || compiledp(addr) || functionp(addr)) {
	    print(car(addr));
	    if (!nullp(cdr(addr))) {
		printc('(');
		printtuple(cdr(addr));
	    }
	} else {
	    printstr("#[");
	    printlist(addr);
	}
	break;
    case STREAM:
	if (addr == standard_input) {
	    printstr("<stdin>");
	} else if (addr == standard_output) {
	    printstr("<stdout>");
	} else if (addr == standard_error) {
	    printstr("<stderr>");
	} else {
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), "<stream%d>", addr);
	    else {
		sprintf(str1, "<stream%d>", addr);
		strcat(bridge, str1);
	    }
	}
	break;
    case SOCKET:
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "<socket%d>", addr);
	else {
	    sprintf(str1, "<socket%d>", addr);
	    strcat(bridge, str1);
	}
	break;
    case STR:
	if (quoted_flag) {
	    if (!bridge_flag) {
		if (!string_flag)
		    fprintf(GET_PORT(output_stream), "$%s$",
			    GET_NAME(addr));
		else
		    fprintf(GET_PORT(output_stream), "\"%s\"",
			    GET_NAME(addr));
	    } else {
		if (!string_flag)
		    sprintf(str1, "$%s$", GET_NAME(addr));
		else
		    sprintf(str1, "\"%s\"", GET_NAME(addr));
		strcat(bridge, str1);
	    }
	} else {
	    printstr(GET_NAME(addr));
	}
	break;
    default:
	printstr("<undef>");
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
    printc('\'');
    while (c != NUL) {
	if (c == '\\') {
	    pos++;
	    c = str[pos];
	    if (c == NUL) {
		printc('\\');
		goto exit;
	    } else if (c == '"') {
		printc(c);
		pos++;
	    } else {
		printc('\\');
		printc(c);
		pos++;
	    }
	} else if (c == '\'') {
	    printc('\'');
	    printc(c);
	    pos++;
	} else if (isUni2(c)) {
	    printc(str[pos++]);
	    printc(str[pos++]);
	} else if (isUni3(c)) {
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	} else if (isUni4(str[0])) {
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	} else if (isUni5(str[0])) {
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	} else if (isUni6(str[0])) {
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	    printc(str[pos++]);
	} else if (c <= 31) {
	    printc('\\');
	    printc(c);
	    printc('\\');
	    pos++;
	} else
	    printc(str[pos++]);


	c = str[pos];
    }
  exit:
    printc('\'');
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
		printc(EOL);
	    else if (c == 't')
		printc(TAB);
	    else if (c == 'f')
		printc(FF);
	    else if (c == 'r')
		printc(CR);
	    else if (c == 'v')
		printc(VT);
	    else if (c == 'a')
		printf("\a");

	    else if (c == 'b')
		printc(BS);
	    else if (c == NUL)
		return;
	    else {
		printc(str[pos - 1]);
		printc(c);
	    }
	} else
	    printc(c);
	pos++;
	c = str[pos];
    }
}

void printc(char c)
{
    char str1[STRSIZE];

    if (!bridge_flag)
	fprintf(GET_PORT(output_stream), "%c", c);
    else {
	sprintf(str1, "%c", c);
	strcat(bridge, str1);
    }
}

void printstr(char *s)
{
    char str1[STRSIZE];

    if (!bridge_flag)
	fprintf(GET_PORT(output_stream), "%s", s);
    else {
	sprintf(str1, "%s", s);
	strcat(bridge, str1);
    }
}

void printint(int n)
{
    char str1[STRSIZE];

    if (!bridge_flag)
	fprintf(GET_PORT(output_stream), "%d", n);
    else {
	sprintf(str1, "%d", n);
	strcat(bridge, str1);
    }
}


void printlong(int addr)
{
    char str1[STRSIZE];

    if (!bridge_flag)
	fprintf(GET_PORT(output_stream), "%lld", GET_LONG(addr));
    else {
	sprintf(str1, "%lld", GET_LONG(addr));
	strcat(bridge, str1);
    }
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
	    printc('(');
	    print(cadr(addr));
	    printc(')');
	} else if (infixp(cadr(addr)) &&
		   get_2nd_weight(car(cadr(addr))) >
		   get_2nd_weight(car(addr))) {
	    printc('(');
	    print(cadr(addr));
	    printc(')');
	} else {
	    if (structurep(cadr(addr)) && car(cadr(addr)) == AND) {
		printc('(');
		print(cadr(addr));
		printc(')');
	    } else
		print(cadr(addr));
	}

	print(car(addr));

	if (infix_operator_p(caddr(addr))) {
	    printc('(');
	    print(caddr(addr));
	    printc(')');
	} else if (infixp(caddr(addr)) &&
		   get_2nd_weight(car(caddr(addr))) >
		   get_2nd_weight(car(addr))) {
	    printc('(');
	    print(caddr(addr));
	    printc(')');
	} else if (infixp(cadr(addr)) && infixp(caddr(addr)) &&
		   get_2nd_weight(car(cadr(addr))) <
		   get_2nd_weight(car(caddr(addr)))) {
	    printc('(');
	    print(caddr(addr));
	    printc(')');
	} else if (single_operation_p(caddr(addr))) {
	    printc(' ');
	    print(caddr(addr));
	} else {
	    print(caddr(addr));
	}
    }
}



void printpostfix(int addr)
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

void printprefix(int addr)
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
    if (nullp(addr)) {
	printc(')');
    } else if ((!(structurep(cdr(addr)))) && (!(nullp(cdr(addr))))) {
	print(car(addr));
	printstr(" . ");
	print(cdr(addr));
	printc(')');
    } else {
	print(car(addr));
	if (!nullp(cdr(addr))) {
	    printc(' ');
	}
	printsexp(cdr(addr));
    }
}

void printarguments(int addr)
{
    if (!structurep(caddr(addr))) {
	print(cadr(addr));
	printc(',');
	print(caddr(addr));
	printc(')');
    } else {
	print(cadr(addr));
	printc(',');
	printarguments(caddr(addr));
    }
}

void printlist(int addr)
{
    if (nullp(addr)) {
	printc(']');
    } else if ((!(structurep(cdr(addr)))) && (!(nullp(cdr(addr))))) {
	if (operationp(car(addr)) &&
	    !argumentsp(car(addr)) && heavy999p(car(car(addr)))) {
	    printc('(');
	    print(car(addr));
	    printc(')');
	} else if (car(addr) == AND) {
	    printstr("','");
	} else if (car(addr) == DOTOBJ) {
	    printstr("'.'");
	} else {
	    print(car(addr));
	}
	printc('|');

	if (operationp(cdr(addr)) &&
	    !argumentsp(cdr(addr)) && heavy999p(car(cdr(addr)))) {
	    printc('(');
	    print(cdr(addr));
	    printc(')');
	} else {
	    print(cdr(addr));
	}
	printc(']');
    } else {
	if (operationp(car(addr)) &&
	    !argumentsp(car(addr)) && heavy999p(car(car(addr)))) {
	    printc('(');
	    print(car(addr));
	    printc(')');
	} else if (car(addr) == AND) {
	    printstr("','");
	} else if (car(addr) == DOTOBJ) {
	    printstr("'.'");
	} else
	    print(car(addr));
	if (!nullp(cdr(addr))) {
	    printc(',');
	}
	printlist(cdr(addr));
    }
}

void printlist_canonical(int addr)
{
    if (nullp(addr))
	print(NIL);
    else if (!listp(cdr(addr))) {
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "'.'(");
	else
	    strcat(bridge, "'.'(");
	print(car(addr));
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), ",");
	else
	    strcat(bridge, ",");
	print(cdr(addr));
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), ")");
	else
	    strcat(bridge, ")");
    } else {
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "'.'(");
	else
	    strcat(bridge, "'.'(");
	print(car(addr));
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), ",");
	else
	    strcat(bridge, ",");
	printlist_canonical(cdr(addr));
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), ")");
	else
	    strcat(bridge, ")");
    }
}

void printcurl(int addr)
{
    arguments_flag = 0;		//(1,2,3) -> 1,2,3
    if (nullp(addr)) {
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "}");
	else
	    strcat(bridge, "}");
	arguments_flag = 1;
    } else {
	print(car(addr));
	if (!nullp(cdr(addr))) {
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), ",");
	    else
		strcat(bridge, ",");
	}
	printcurl(cdr(addr));
    }
}

void printtuple(int addr)
{
    if (nullp(addr)) {
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), ")");
	else
	    strcat(bridge, ")");
    } else {
	print(car(addr));
	if (!nullp(cdr(addr))) {
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), ",");
	    strcat(bridge, ",");
	}
	printtuple(cdr(addr));
    }
}

void printclause(int addr)
{

    if (listing_flag) {
	if (nullp(caddr(addr))) {	// e.g. :- foo(x).
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), "(:- ");
	    else
		strcat(bridge, "(:- ");
	    print(cadr(addr));
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), ")");
	    else
		strcat(bridge, ")");
	} else {		// e.g. foo(x) :- boo(x).
	    print(cadr(addr));
	    if (!bridge_flag)
		fprintf(GET_PORT(output_stream), " :-\n    ");
	    else
		strcat(bridge, " :-\n    ");
	    printbody(caddr(addr));
	}
    } else {
	if (!ignore_flag) {
	    if (nullp(caddr(addr))) {	// e.g :- foo(x).
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ":- ");
		else
		    strcat(bridge, ":- ");
		print(cadr(addr));
	    } else {		//normal case  foo(X) :- bar(X).
		print(cadr(addr));
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ":-");
		else
		    strcat(bridge, ":-");
		print(caddr(addr));
	    }
	} else {
	    if (nullp(caddr(addr))) {	// e.g :- foo(x).
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ":-(");
		else
		    strcat(bridge, ":-(");
		print(cadr(addr));
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ")");
		else
		    strcat(bridge, ")");
	    } else {		// normal case foo(X) :- bar(X).
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ":-(");
		else
		    strcat(bridge, ":-(");
		print(cadr(addr));
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ",");
		else
		    strcat(bridge, ",");
		print(caddr(addr));
		if (!bridge_flag)
		    fprintf(GET_PORT(output_stream), ")");
		else
		    strcat(bridge, ")");
	    }
	}
    }
}

void printbody(int addr)
{

    if (operationp(addr) && car(addr) == AND) {
	printbody(cadr(addr));
	print(car(addr));
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "\n    ");
	strcat(bridge, "\n    ");
	printbody(caddr(addr));
    } else if (operationp(addr) && car(addr) == OR) {
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), "(");
	else
	    strcat(bridge, "(");
	printbody1(cadr(addr));
	print(car(addr));
	printbody1(caddr(addr));
	if (!bridge_flag)
	    fprintf(GET_PORT(output_stream), ")");
	else
	    strcat(bridge, ")");
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
