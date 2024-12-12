/* N-Prolog
written by kenichi sasagawa 2016/9~
*/
#include <setjmp.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
memory map
address 
0          -  5,000,000  heap area
 5,000,001 - 30,000,000  working area 
30,000,001 - 50,000,000  variant area
*/
#define VERSION     3.61
#define CELLSIZE    30000000  // if raspberry PI set smaller size.
#define HEAPSIZE     5000000
#define FREESIZE         500
#define STACKSIZE    1000000
#define VARIANTSIZE 20000000
#define VARIANTMAX  CELLSIZE + VARIANTSIZE
#define BIGSIZE 20000000
#define NTTBASE 1000
#define RECORDMAX 12
#define ATOMSIZE 1024
#define BUFSIZE 1024
#define STRSIZE 1024
#define PARASIZE 100
#define THREADSIZE 6
#define PROCSIZE 10
#define OPERATOR_NUMBER 24
#define FUNCTION_NUMBER 22
#define BUILTIN_NUMBER 200
#define COMPILED_NUMBER 23
#define EXTENDED_NUMBER 30
#define NIL         0
#define YES         2
#define NO          4
#define FEND        6
#define UNDEF       8
#define CUT         10
#define AND         12
#define OR          14
#define LEFTPAREN   16
#define RIGHTPAREN  18
#define CALL        20
#define QUEST	    22
#define ANOYVAR     24
#define DEFINE      26
#define ATMARK      28
#define COLON       30
#define NTRUE       32
#define NFALSE      34
#define CURL        36
#define IFTHEN      38
#define IFTHENELSE  40
#define UNDERBAR    42
#define DOTOBJ      44
#define DCG         46
#define TIMERON     48
#define TIMEROFF    50
#define SLASH       52
#define ERROBJ      54
#define HASHTBSIZE 107
#define BIGNUM_BASE 1000000000
#define SMALL_INT_MAX       1000000000
#define SMALL_INT_MIN       -1000000000
#define UNBIND              -1000000001
#define INT_FLAG    1073741824 //#b1000000000000000000000000000000
#define INT_MASK    1073741823 //#b0111111111111111111111111111111
#define PI      3.141592653589793
#define LESS    0
#define NOTLESS 1
//following are for unicode<=>UTF-8 transform
#define UNI2ADD1    192        //#b11000000
#define UNI3ADD1    224        //#b11100000
#define UNI4ADD1    240        //#b11110000
#define UNIOADDO    128        //#b10000000
#define UNI2MSK1    1984       //#b0000011111000000
#define UNI2MSK2    63         //#b0000000000111111
#define UNI3MSK1    61440      //#b1111000000000000
#define UNI3MSK2    4032       //#b0000111111000000
#define UNI3MSK3    63         //#b0000000000111111
#define UNI4MSK1    1835008    //#b00000000000111000000000000000000
#define UNI4MSK2    258048     //#b00000000000000111111000000000000
#define UNI4MSK3    4032       //#b00000000000000000000111111000000
#define UNI4MSK4    63         //#b00000000000000000000000000111111
#define UTF2MSK1    63         //#b00111111
#define UTF3MSK1    31         //#b00011111
#define UTF4MSK1    15         //#b00001111
#define UTFOMSKO    127        //#b01111111


typedef enum tag {EMP,INTN,FLTN,LONGN,BIGX,STRUCT,SINGLE,STREAM,STR} tag;
typedef enum flag {FRE,USE} flag;

typedef struct __packed{
    union{
        double fltnum;
        long long int lngnum;
        struct{
            union{
                int intnum;
                int     ( *subr) (int, int);
                FILE    *port;
            } car;
            union{
                int intnum;
            } cdr;
        };
    } val;
    int     aux;
    int     var;
    int     arity;
    char    tag;
    flag    flag;
    char    *name;
    unsigned char option;
    char    trace;
    int     record;
} cell;


typedef enum toktype {LPAREN,RPAREN,LBRACKET,RBRACKET,VERTICAL,LCURL,RCURL,SHARP,
                      STRING,INTEGER,FLOATN,CHARCODE,ATOMOBJ,BUILTIN,FUNCTION,
                      COMPILED,OPERATOR,VARIABLE,ANOYMOUS,VARIANT,QUOTE,DOT,BACKQUOTE,DBLQUOTE,
                      COMMA,SEMICOLON,BIGNUM,BINNUM,OCTNUM,HEXNUM,
                      PERIOD,FILEEND,OTHER} toktype;
typedef enum backtrack {GO,BACK} backtrack;
typedef enum spaceskip {SKIP,NOTSKIP} spaceskip;

typedef struct token {
    char ch;
    char ahead;
    backtrack flag;
    spaceskip space;
    toktype type;
    char buf[BUFSIZE];
} token;

// for editable REPL
typedef struct result {
    int type;
    int length;
} result;

// for ansi_*
typedef struct cursor {
    int row;
    int col;
} cursor;


enum { CHECKGBC_IDX, GBC_IDX, FRESHCELL_IDX, 
       DEBUG_IDX, 
       NUM_FN0S
};

enum { CAR_IDX, CDR_IDX, CADR_IDX, CADDR_IDX, CAAR_IDX, CADAR_IDX, PRINT_IDX, MAKEINT_IDX,
       LENGTH_IDX,  GET_INT_IDX,
       SIN_IDX, ASIN_IDX, COS_IDX, ACOS_IDX, TAN_IDX, ATAN_IDX, EXP_IDX, LOG_IDX,
       LN_IDX, LIST1_IDX, RANDOM_IDX, RANDI_IDX,  WLIST1_IDX, OPERATE_IDX,
       LISTP_IDX,  STRUCTUREP_IDX, VARIABLEP_IDX, GET_SP_IDX, GET_WP_IDX, INC_PROOF_IDX,
       MAKEVARIANT_IDX, 
       NUM_FN1S
};

enum { CONS_IDX, PLUS_IDX, MINUS_IDX, MULT_IDX, DIVIDE_IDX, REMAINDER_IDX,
       QUOTIENT_IDX, EQP_IDX, EQUALP_IDX, NUMEQP_IDX, SMALLERP_IDX, EQSMALLERP_IDX,
       GREATERP_IDX, EQGREATERP_IDX, MOD_IDX, EXPT_IDX, SQRT_IDX,
       LEFTSHIFT_IDX, RIGHTSHIFT_IDX, LOGICALAND_IDX, LOGICALOR_IDX, LISTCONS_IDX,
       LIST2_IDX, SET_CAR_IDX, SET_CDR_IDX, COMPLEMENT_IDX, SET_AUX_IDX,
       NOT_NUMEQP_IDX, DIV_IDX, SET_VAR_IDX, WCONS_IDX, WLIST2_IDX, 
       ADDTAIL_BODY_IDX, NTH_IDX, 
       ROUND_IDX, UNBIND_IDX, SET_SP_IDX, SET_WP_IDX,DEREF_IDX,
       NUM_FN2S
};

enum { LIST3_IDX, CALLSUBR_IDX, WLIST3_IDX, ERRORCOMP_IDX, WLISTCONS_IDX,UNIFY_IDX, 
       UNIFY_VAR_IDX, UNIFY_CONST_IDX, UNIFY_NIL_IDX, EXEC_ALL_IDX,
       NUM_FN3S,
};

enum { MAKECONST_IDX, MAKEPRED_IDX, MAKEVAR_IDX, MAKESTRFLT_IDX, MAKECOMP_IDX,
       MAKESYS_IDX, MAKEOPE_IDX, MAKEUSER_IDX, MAKESTRLONG_IDX, MAKEBIGX_IDX,
       MAKESTR_IDX, MAKEFUNC_IDX,
       NUM_FN4S
};



extern cell heap[CELLSIZE];
extern int variant[VARIANTSIZE];
extern int bigcell[BIGSIZE];
extern int stack[STACKSIZE];
extern int ustack[STACKSIZE];
extern token stok;
extern jmp_buf buf;
extern jmp_buf buf1;
extern jmp_buf buf2;
extern int cell_hash_table[HASHTBSIZE];
extern int record_hash_table[HASHTBSIZE][RECORDMAX]; 
extern int record_pt;       
extern int counter[31]; 
extern char bridge[BUFSIZE];
extern char transfer[BUFSIZE];
extern int variables;
extern int variables_save;
extern int end_of_file_answer;
extern int end_of_file_rest;
extern int predicates;
extern int builtins;
extern int spy_list;
extern int reconsult_list;
extern int execute_list;
extern int op_list;
extern int key_list;
extern int error_code;
extern int bag_list;
extern int nonfree_list;
extern int proof[THREADSIZE];
extern int parse_mode;
extern int left_margin;
extern int break_nest;
extern int leap_point;
extern int port;
extern int line;
extern int column;
extern int cursor_color;
extern int cursor_style;
extern int cursor_row_store;
extern int cursor_col_store;
extern int cursor_color_store;
extern int cursor_style_store;
extern int unread;
extern int paren_nest;
extern char operator[OPERATOR_NUMBER][5];
extern char function[FUNCTION_NUMBER][12];
extern char builtin[BUILTIN_NUMBER][30];
extern char compiled[COMPILED_NUMBER][30];
extern char extended[EXTENDED_NUMBER][30];
extern double timer;

// bignum pointer
extern int big_pt0;
extern int big_pt1;

//stream
extern int standard_input;
extern int standard_output;
extern int standard_error;
extern int input_stream;
extern int output_stream;
extern int error_stream;

//stream type
#define OPL_OPEN    21
#define OPL_INPUT   22
#define OPL_OUTPUT  23
#define OPL_TEXT    24
#define OPL_BINARY  25

//trace mode
#define OFF     0
#define FULL    1
#define TIGHT   2
#define HALF    3
#define LOOSE   4 
#define DBCALL  5
#define DBEXIT  6
#define DBREDO  7
#define DBFAIL  8
#define DBCUTFAIL   9

//debugger
#define OFF     0
#define ON      1
    
/* distributed parallel */
#define PORT 5000 
extern int parent_sockfd[2];
extern int child_sockfd[PARASIZE];
extern socklen_t parent_len;
extern struct sockaddr_in parent_addr, child_addr[PARASIZE];
extern int child_num;
extern pthread_t receiver_thread;
extern int child_result[PARASIZE];

/* multi-thread */
extern int thread_num;

#ifdef __APPLE__
#define FLUSH               fpurge(stdin);
#else
#define FLUSH               __fpurge(stdin); 
#endif
#define DEBUG               printf("debug\n"); longjmp(buf,2);
#define GET_FLT(addr)       heap[addr].val.fltnum
#define GET_CAR(addr)       heap[addr].val.car.intnum
#define GET_CDR(addr)       heap[addr].val.cdr.intnum
#define GET_AUX(addr)       heap[addr].aux
#define GET_VAR(addr)       heap[addr].var
#define GET_ATTR(addr)      heap[addr].attr
#define GET_ARITY(addr)     heap[addr].arity
#define GET_SUBR(addr)      heap[addr].val.car.subr
#define GET_PORT(addr)      heap[addr].val.car.port
#define GET_INT(addr)       get_int(addr)
#define GET_NUMBER(addr)    heap[addr].val.car.intnum
#define GET_FLT(addr)       heap[addr].val.fltnum
#define GET_LONG(addr)      heap[addr].val.lngnum
#define GET_NAME(addr)      heap[addr].name
#define GET_NAME_ELT(addr,n)    heap[addr].name[n]
#define GET_CHAR(addr)      heap[addr].name[0]
#define GET_TAG(addr)       get_tag(addr)
#define GET_CAR(addr)       heap[addr].val.car.intnum
#define GET_OPT(addr)       heap[addr].option
#define GET_TR(addr)        heap[addr].trace
#define GET_FLAG(addr)      heap[addr].flag
#define GET_RECORD(addr)    heap[addr].record
#define SET_TAG(addr,x)     heap[addr].tag = x
#define SET_CAR(addr,x)     heap[addr].val.car.intnum = x
#define SET_CDR(addr,x)     heap[addr].val.cdr.intnum = x
#define SET_AUX(addr,x)     heap[addr].aux = x
#define SET_VAR(addr,x)     heap[addr].var = x
#define SET_ARITY(addr,x)   heap[addr].arity = x
#define SET_INT(addr,x)     heap[addr].val.car.intnum = x
#define SET_FLT(addr,x)     heap[addr].val.fltnum = x
#define SET_LONG(addr,x)    heap[addr].val.lngnum = x
#define SET_SUBR(addr,x)    heap[addr].val.car.subr = x
#define SET_PORT(addr,x)    heap[addr].val.car.port = x
#define SET_OPT(addr,x)     heap[addr].option = x
#define SET_TR(addr,x)      heap[addr].trace = x
#define SET_CHAR(addr,x)    heap[addr].name[0] = x
#define SET(addr,x)         heap[addr] = heap[x]
#define SET_RECORD(addr,x)  heap[addr].record = x
#define IS_INCELL(addr)     (addr >= 0 && addr < CELLSIZE)
#define IS_OUTCELL(addr)    (addr < 0 || addr >= CELLSIZE)
#define IS_ALPHA(addr)      (addr < VARIANTMAX && addr > CELLSIZE)
#define IS_SINGLE(addr)     heap[addr].tag == SINGLE
#define IS_BIGXNUM(addr)    heap[addr].tag == BIGX
#define IS_LONGNUM(addr)    heap[addr].tag == LONGN
#define IS_FLOAT(addr)      heap[addr].tag == FLTN
#define IS_STRING(addr)     heap[addr].tag == STR
#define IS_STRUCT(addr)     heap[addr].tag == STRUCT
#define IS_NIL(addr)        (addr == 0)
#define IS_T(addr)          (addr == 2)
#define IS_EMPTY(addr)      heap[addr].tag  == EMP
#define IS_STREAM(addr)     heap[addr].tag == STREAM
#define HAS_NAME(addr,x)    strcmp(heap[addr].name,x) == 0
#define SAME_NAME(addr1,addr2) strcmp(heap[addr1].name, heap[addr2].name) == 0
#define GREATER_NAME(addr1,addr2) strcmp(heap[addr1].name, heap[addr2].name) > 0
#define SMALLER_NAME(addr1,addr2) strcmp(heap[addr1].name, heap[addr2].name) < 0
#define EQUAL_STR(x,y)      strcmp(x,y) == 0
#define EQUAL_STR(x,y)      strcmp(x,y) == 0
#define STRING_REF(addr,k)   heap[addr].name[k]
#define STRING_SET(addr,k,c) heap[addr].name[k] = c
#define MARK_CELL(addr)     heap[addr].flag = USE
#define NOMARK_CELL(addr)   heap[addr].flag = FRE
#define USED_CELL(addr)     heap[addr].flag == USE
#define FREE_CELL(addr)     heap[addr].flag == FRE

#define isUni1(c)   ((unsigned char)(c) <= 0x7f)

#define isUni2(c)   (((unsigned char)(c) >= 0xc2) && \
                     ((unsigned char)(c) <= 0xdf))

#define isUni3(c)   (((unsigned char)(c) >= 0xe0) && \
                     ((unsigned char)(c) <= 0xef))

#define isUni4(c)   (((unsigned char)(c) >= 0xf0) && \
                     ((unsigned char)(c) <= 0xf7))

#define isUni5(c)   (((unsigned char)(c) >= 0xf8) && \
                     ((unsigned char)(c) <= 0xfb))

#define isUni6(c)   (((unsigned char)(c) >= 0xfc) && \
                     ((unsigned char)(c) <= 0xfd))



//operator
#define FX  1   //0b0000001
#define FY  2   //0b0000010
#define XFX 4   //0b0000100
#define XFY 8   //0b0001000
#define YFX 16  //0b0010000
#define XF  32  //0b0100000
#define YF  64  //0b1000000
#define FX_XFX  5 //0b0000101
#define FY_XFX  6 //0b0000110
#define FX_XFY  9 //0b0001001
#define FY_XFY 10 //0b0001010
#define FX_YFX 17 //0b0010001
#define FY_YFX 18 //0b0010010
#define FX_XF  33 //0b0100001
#define FX_YF  65 //0b1000001
#define FY_XF  34 //0b0100010
#define FY_YF  66 //0b1000010

//clause option
#define HASCUT  100 //the clause has cut operator
#define CUTING  101 //the clause that has cut is now on executing.
#define HASLOOP 102 //the clause has simple loop
#define HASIFTHEN 103 // the clause has ih_then ->

//atom type
#define SIMP    1 //simple atom(constant)
#define VAR     2 //variable
#define ANOY    3 //anoimouse
#define USER    4 //user defined operator
#define OPE     5 //operator
#define PRED    6 //user defined predicate
#define SYS     7 //system predicate
#define CLAUSE  8 //clause
#define COMP    9 //compiled predicate
#define LIST    10 //list
#define FUNC    11 //function


//stream type
#define NORMAL  0
#define STDIO   1 //user_input user_output error

//------flag---
extern int trace_flag;
extern int open_flag;
extern int gbc_flag;
extern int simp_flag;
extern int assert_flag;
extern int debug_flag;
extern int fskip_flag;
extern int qskip_flag;
extern int sskip_flag;
extern int xskip_flag;
extern int semiskip_flag;
extern int sexp_flag;
extern int quoted_flag;
extern int ignore_flag;
extern int link_flag;
extern int listing_flag;
extern int prefix_flag;
extern int syntax_flag;
extern int fileerr_flag;
extern int exist_flag;
extern int bridge_flag;
extern int ctrl_c_flag;
extern int init_flag;
extern int script_flag;
extern int check_flag;
extern int break_flag;
extern int network_mode;
extern int parallel_flag;
extern int parallel_exit_flag;
extern int process_flag;
extern int thread_flag;
extern int child_flag;
extern int connect_flag;
extern int receiver_exit_flag;
extern int child_busy_flag;
extern int parent_flag;
extern int pause_flag;
extern int shutdown_flag;

//------pointer----
extern int hp; //heap pointer
extern int sp[THREADSIZE]; //stack pointer
extern int fc; //free counter
extern int ac[THREADSIZE]; //alpha conversion variable counter
extern int wp[THREADSIZE]; //working pointer
extern int up; //unify stack pointer
extern int gc; //invokded GC count

//-----editor-----
extern int repl_flag;
extern char buffer[BUFSIZE][10];
extern int ed_row;
extern int ed_col;
extern int ed_start;
extern int ed_end;
extern int ed_ins;
extern int ed_tab;
extern int ed_indent;
extern int ed_name;
extern int ed_lparen_row;
extern int ed_lparen_col;
extern int ed_rparen_row;
extern int ed_rparen_col;
extern int ed_lbracket_row;
extern int ed_lbracket_col;
extern int ed_rbracket_row;
extern int ed_rbracket_col;
extern char ed_candidate[30][30];
extern int ed_candidate_pt;
extern int ed_operator_color;
extern int ed_builtin_color;
extern int ed_extended_color;
extern int ed_quote_color;
extern int ed_comment_color;
extern int ed_function_color;
extern int ed_incomment;
extern int ed_hight;
extern int ed_width;
extern result rtok;

static const int BIGNUM_WORK = BIGSIZE * 5 / 10; // from 50% to 90% of bigcell area is working area.
static const int BIGNUM_PARMA = BIGSIZE * 9 / 10; //from 90% to 100% of bigcell area is parmanent area

#define ESCHOME printf("\33[1;1H")
#define ESCTOP  printf("\33[2;1H")
#define ESCCLS  printf("\33[2J")          //clear screen
#define ESCCLS1 printf("\33[0J")
#define ESCCLSL printf("\33[0K")
#define ESCCLSL1 printf("\033[K")         //clear line from cursor
#define ESCMVLEFT(x) printf("\33[%dG", x)
#define ESCMVR  printf("\33[1C")
#define ESCMVL  printf("\33[1D")
#define ESCMVU  printf("\33[1A")
#define ESCMVD  printf("\33[1B")
#define ESCSCR  printf("\33[S")
#define ESCMOVE(x,y)    printf("\33[%d;%df", x,y)
#define ESCCOLOR(x)     printf("\33[%dm",x)
#define ESCFBLACK printf("\33[30m")
#define ESCFRED  printf("\33[31m")
#define ESCFGREEN printf("\33[32m")
#define ESCFYELLOW printf("\33[33m")
#define ESCFBLUE printf("\33[34m")
#define ESCFMAGENTA printf("\33[35m")
#define ESCFCYAN printf("\33[36m")
#define ESCFWHITE printf("\33[37m")
#define ESCFORG  printf("\33[39m")
#define ESCBCYAN printf("\33[46m")
#define ESCBORG  printf("\33[49m")
#define ESCREV  printf("\33[7m")
#define ESCRST  printf("\33[0m")
#define ESCBOLD printf("\33[1m")


//-------read--------
#define EOL     '\n'
#define RET     '\r'
#define TAB     '\t'
#define SPACE   ' '
#define ESCAPE  033
#define NUL     '\0'
#define ESC     27
#define NUL     '\0'
#define BEL     '\a'
#define BS      '\b'
#define DEL     127
#define FF      12
#define CR      13
#define VT      11


#define LEFT    'D'
#define UP      'A'
#define RIGHT   'C'
#define DOWN    'B'
#define INSERT  '2'
#define DELETE  '3'
#define PAGEUP  '5'
#define PAGEDN  '6'
#define HOME    'H'
#define END     'F'


//-------error code---
#define SYNTAX_ERR      1
#define BUILTIN_EXIST   2
#define CANT_READ       3
#define NOT_COMPUTABLE  4
#define OUT_OF_RANGE    5
#define MALLOC_OVERF    6
#define WRONG_ARGS      7
#define NOT_NUM         8
#define NOT_STR         9
#define NOT_LIST        10
#define NOT_ATOM         11
#define ILLEGAL_OPL_INPUT   12
#define UNCAUGHT_EXCEPTION       13
#define CANT_OPEN       14
#define FILE_EXIST      15
#define ILLEGAL_ARGS    16
#define NOT_CONS        17
#define CANT_MODIFY     18
#define NOT_INT         19
#define NOT_STREAM      20
#define NOT_OUT_STREAM  21
#define NOT_IN_STREAM   22
#define NOT_CHAR        23
#define NOT_FLT         24
#define CTRL_OVERF      25
#define END_STREAM      26
#define DIV_ZERO        27
#define CANT_PARSE      28
#define NOT_ARITHMETIC  29
#define FLT_OVERF       30
#define FLT_UNDERF      31
#define STACK_OVERF     32
#define SYSTEM_ERROR    33
#define UNDEF_PRED		34
#define EOF_ERROR       35
#define INSTANTATION_ERR    36
#define EXPONENT_ERR    37
#define OPE_SPEC_ERR    38
#define NOT_CALLABLE    39
#define NOT_VAR         40
#define EXISTENCE_ERR   41
#define NOT_SOURCE      42
#define ALIAS_EXIST     43
#define NOT_IO_MODE     44
#define NOT_CLOSE_OPTION    45   
#define NOT_STREAM_OPTION   46
#define NOT_OUTPUT_STREAM   47
#define NOT_ATOMIC          48
#define LESS_THAN_ZERO      49
#define NOT_COMPOUND        50
#define NON_EMPTY_LIST      51
#define NOT_INPUT_STREAM    52
#define PAST_EOF_INPUT      53
#define EVALUATION_ERR      54
#define STATIC_PROCEDURE    55
#define PRED_INDICATOR      56
#define NOT_OPEN_OPTION     57
#define OPE_PRIORITY_ERR    58
#define MODIFY_OPE_ERR      59
#define NOT_CHAR_CODE       60
#define RESOURCE_ERR        61
#define NOT_ORDER           62
#define NOT_TERM            63
#define RECORD_OVERF        64
#define NOT_RECORD          65
#define VARIANT_OVERF       66
#define ARITY_ERR           67


double getETime(void);
int readc(void);

int absolute(int x);
int addask(int x);
int addatom(char *name, int property, int index);
int addtail(int x, int y);
int addtail_body(int x, int y);
int addtail_operation(int x, int y);
int after_cut(int x);
int after_c_lang(int x);
int alias_option_p(int x);
int aliasp(int addr);
int alpha_variable_p(int addr);
int alpha_to_variable(int x);
int alphabeticalp(int addr);
int already_checked_p(int x);
int angle(int y, int x);
int anoymousp(int x);
int anoymous_conversion(int x);
int append(int x, int y);
int append1(int x, int y);
int argumentsp(int addr);
int assq(int sym, int lis);
int assq1(int sym, int lis);
int atmarkp(int addr);
int atom_chars_list_p(int addr);
int atom_codes_list_p(int addr);
int atom_constant_p(int addr);
int atom_predicate_p(int addr);
int atom_quote_p(int addr);
int atom_variable_p(int addr);
int atomp(int addr);
int atomicp(int addr);
int atsmaller(int x, int y);
int ateqsmaller(int x, int y);
int bcons(int car, int cdr);
int b_abolish(int arglist, int rest);
int b_abort(int arglist, int rest);
int b_after_cut(int arglist, int rest);
int b_ansi_cup(int arglist, int rest);
int b_ansi_cuu(int arglist, int rest);
int b_ansi_cud(int arglist, int rest);
int b_ansi_cuf(int arglist, int rest);
int b_ansi_cub(int arglist, int rest);
int b_ansi_sgr(int arglist, int rest);
int b_ansi_cpr(int arglist, int rest);
int b_ansi_scp(int arglist, int rest);
int b_ansi_rcp(int arglist, int rest);
int b_ansi_ed(int arglist, int rest);
int b_ansi_el(int arglist, int rest);
int b_append(int arglist, int rest);
int b_arg(int arglist, int rest);
int b_arg0(int arglist, int rest);
int b_arity_count(int arglist, int rest);
int b_ask(int arglist, int rest);
int b_assert(int arglist, int rest);
int b_asserta(int arglist, int rest);
int b_assertz(int arglist, int rest);
int b_ateqsmaller(int arglist, int rest);
int b_atsmaller(int arglist, int rest);
int b_atgreater(int arglist, int rest);
int b_ateqgreater(int arglist, int rest);
int b_atmark(int arglist, int rest);
int b_atom(int arglist, int rest);
int b_atom_string(int arglist, int rest);
int b_atom_concat(int arglist, int rest);
int b_atomic(int arglist, int rest);
int b_atom_convert(int arglist, int rest);
int b_atsmaller(int arglist, int rest);
int b_before_cut(int arglist, int rest);
int b_bagof(int arglist, int rest);
int b_bagofhelper(int arglist, int rest);
int b_between(int arglist, int rest);
int b_bignum(int arglist, int rest);
int b_break(int arglist, int rest);
int b_call(int arglist, int rest);
int b_chdir(int arglist , int rest);
int b_char_code(int arglist, int rest);
int b_char_conversion(int arglist, int rest);
int b_char_set(int arglist, int rest);
int b_clause(int arglist, int rest);
int b_clause_with_arity(int arglist, int rest);
int b_close(int arglist, int rest);
int b_colon(int arglist, int rest);
int b_compare(int arglist, int rest);
int b_compiler_anoymous(int arglist, int rest);
int b_compiler_variable(int arglist, int rest);
int b_compound(int arglist, int rest);
int b_concat(int arglist, int rest);
int b_consult(int arglist, int rest);
int b_constant(int arglist, int rest);
int b_copy_term(int arglist, int rest);
int b_create(int arglist, int rest);
int b_ctr_set(int arglist, int rest);
int b_ctr_dec(int arglist, int rest);
int b_ctr_inc(int arglist, int rest);
int b_ctr_is(int artlist, int rest);
int b_current_directory(int arglist , int rest);
int b_current_input(int arglist, int rest);
int b_current_output(int arglist, int rest);
int b_current_op(int arglist, int rest);
int b_current_predicate(int arglist, int rest);
int b_cut(int arglist, int rest);
int b_date_day(int arglist, int rest);
int b_date(int arglist, int rest);
int b_dec(int arglist, int rest);
int b_debug(int arglist, int rest);
int b_defined_predicate(int arglist, int rest);
int b_defined_userop(int arglist, int rest);
int b_delete(int arglist, int rest);
int b_directory(int arglist, int rest);
int b_display(int arglist, int rest);
int b_dp_countup(int arglist, int rest);
int b_dp_create(int arglist, int rest);
int b_dp_close(int arglist, int rest);
int b_dp_prove(int arglist ,int rest);
int b_dp_and(int arglist, int rest);
int b_dp_or(int arglist, int rest);
int b_dp_transfer(int arglist, int rest);
int b_dp_receive(int arglist ,int rest);
int b_dp_compile(int arglist, int rest);
int b_dp_consult(int arglist, int rest);
int b_dp_report(int arglist, int rest);
int b_dp_parent(int arglist, int rest);
int b_dp_child(int arglist, int rest);
int b_dp_wait(int arglist, int rest);
int b_dp_pause(int arglist, int rest);
int b_dp_resume(int arglist, int rest);
int b_dup(int arglist, int rest);
int b_edit(int arglist, int rest);
int b_end_of_file(int arglist, int rest);
int b_eq(int arglist, int rest);
int b_eqgreater(int arglist, int rest);
int b_eqsmaller(int arglist, int rest);
int b_equalp(int arglist, int rest);
int b_erase(int arglist, int rest);
int b_eraseall(int arglist, int rest);
int b_errcode(int arglist, int rest);
int b_error(int arglist, int rest);
int b_existerrors(int arglist, int rest);
int b_fail(int arglist, int rest);
int b_findall(int arglist, int rest);
int b_findatom(int arglist, int rest);
int b_fileerrors(int arglist, int rest);
int b_filename(int arglist, int rest);
int b_float_text(int arglist, int rest);
int b_flush_output(int arglist, int rest);
int b_functor(int arglist, int rest);
int b_gbc(int arglist, int rest);
int b_generate_all_variable(int arglist, int rest);
int b_generate_variable(int arglist, int rest);
int b_get(int arglist, int rest);
int b_get0(int arglist, int rest);
int b_get0_noecho(int arglist, int rest);
int b_get_byte(int arglist, int rest);
int b_get_char(int arglist, int rest);
int b_get_code(int arglist, int rest);
int b_greater(int arglist, int rest);
int b_ground(int arglist, int rest);
int b_halt(int arglist, int rest);
int b_has_cut(int arglist, int rest);
int b_heapdump(int arglist, int rest);
int b_inc(int arglist, int rest);
int b_ifthen(int arglist, int rest);
int b_ifthenelse(int arglist, int rest);
int b_instance(int arglist, int rest);
int b_integer(int arglist, int rest);
int b_int_text(int arglist, int rest);
int b_is(int arglist, int rest);
int b_key(int arglist, int rest);
int b_keysort(int arglist, int rest);
int b_leash(int arglist, int rest);
int b_length(int arglist, int rest);
int b_list(int arglist, int rest);
int b_listing(int arglist, int rest);
int b_list_text(int arglist, int rest);
int b_longnum(int arglist, int rest);
int b_mkdir(int arglist, int rest);
int b_member(int arglist, int rest);
int b_measure(int arglist, int rest);
int b_nl(int arglist, int rest);
int b_nonvar(int arglist, int rest);
int b_nospy(int arglist, int rest);
int b_not(int arglist, int rest);
int b_notequalp(int arglist, int rest);
int b_notnumeq(int arglist, int rest);
int b_notrace(int arglist, int rest);
int b_notunify(int arglist, int rest);
int b_name(int arglist, int rest);
int b_number(int arglist, int rest);
int b_number_chars(int arglist, int rest);
int b_number_codes(int arglist, int rest);
int b_numbervars(int arglist, int rest);
int b_numeq(int arglist, int rest);
int b_nth_char(int arglist, int rest);
int b_nref(int arglist, int rest);
int b_nth_ref(int arglist, int rest);
int b_op(int arglist, int rest);
int b_open(int arglist, int rest);
int b_peek_byte(int arglist, int rest);
int b_predicate_property(int arglist, int rest);
int b_pref(int arglist, int rest);
int b_property(int arglist, int rest);
int b_put(int arglist, int rest);
int b_put_char(int arglist, int rest);
int b_put_code(int arglist, int rest);
int b_put_byte(int arglist, int rest);
int b_read(int arglist, int rest);
int b_read_line(int arglist, int rest);
int b_read_string(int arglist, int rest);
int b_real(int arglist, int rest);
int b_record_after(int arglist, int rest);
int b_recorda(int arglist, int rest);
int b_recordz(int arglist, int rest);
int b_recorded(int arglist, int rest);
int b_recordh(int arglist, int rest);
int b_reconsult(int arglist, int rest);
int b_ref(int arglist, int rest);
int b_rename(int arglist, int rest);
int b_repeat(int arglist, int rest);
int b_reset_op(int arglist, int rest);
int b_retract(int arglist, int rest);
int b_retrieveh(int arglist, int rest);
int b_reverse(int arglist, int rest);
int b_reconsult_predicate(int arglist, int rest);
int b_reconsult_abolish(int arglist, int rest);
int b_rmdir(int arglist, int rest);
int b_removeh(int arglist, int rest);
int b_removeallh(int arglist, int rest);
int b_replace(int arglist, int rest);
int b_save(int arglist, int rest);
int b_see(int arglist, int rest);
int b_seeing(int arglist, int rest);
int b_seen(int arglist, int rest);
int b_setof(int arglist, int rest);
int b_set_input(int arglist, int rest);
int b_set_output(int arglist, int rest);
int b_shell(int arglist, int rest);
int b_skip(int arglist, int rest);
int b_smaller(int arglist, int rest);
int b_sort(int arglist, int rest);
int b_spy(int arglist, int rest);
int b_statistics(int arglist, int rest);
int b_stdin(int arglist, int rest);
int b_stdout(int arglist, int rest);
int b_stdinout(int arglist, int rest);
int b_string(int arglist, int rest);
int b_string_length(int arglist, int rest);
int b_string_term(int arglist, int rest);
int b_substring(int arglist, int rest);
int b_syntaxerrors(int arglist, int rest);
int b_tab(int arglist, int rest);
int b_tell(int arglist, int rest);
int b_telling(int arglist, int rest);
int b_term_variables(int arglist, int rest);
int b_time(int arglist, int rest);
int b_told(int arglist, int rest);
int b_trace(int arglist, int rest);
int b_true(int arglist, int rest);
int b_unify(int arglist, int rest);
int b_univ(int arglist, int rest);
int b_var(int arglist, int rest);
int b_variable_convert(int arglist, int rest);
int b_write(int arglist, int rest);
int b_writeln(int arglist, int rest);
int b_writeq(int arglist, int rest);
int before_cut(int x);
int before_cut1(int x, int y);
int before_c_lang(int x);
int bignump(int x);
int bigx_abs(int x);
int bigx_abs_smallerp(int arg1, int arg2);
int bigx_big_to_flt(int x);
int bigx_div (int arg1, int arg2);
int bigx_div1 (int arg1, int arg2);
int bigx_div_i (int x, int y);
int bigx_eqp(int x, int y);
int bigx_greaterp(int arg1, int arg2);
int bigx_int_to_big(int x);
int bigx_length(int x);
int bigx_long_to_big(int x);
int bigx_minus(int arg1, int arg2);
int bigx_minus1(int arg1, int arg2);
int bigx_mult(int arg1, int arg2);
int bigx_mult_i(int x, int y);
int bigx_mult1(int arg1, int arg2);
int bigx_negativep(int x);
int bigx_ntt_mult(int arg1, int arg2);
int bigx_plus(int arg1, int arg2);
int bigx_plus1(int arg1, int arg2);
int bigx_positivep(int x);
int bigx_quotient(int arg1, int arg2);
int bigx_quotient_i(int x, int y);
int bigx_quotient1(int arg1, int arg2);
int bigx_remainder_i(int x, int y);
int bigx_shift(int x, int rest);
int bigx_simplify(int x);
int bigx_smallerp(int arg1, int arg2);
int bigx_to_parmanent(int x);
int builtin_zero_p(int addr);
int builtinp(int addr);
int butlast(int addr);
int callsubr(int x,int restest,int rest);
int caar(int addr);
int cadar(int addr);
int caddr(int addr);
int cadddr(int addr);
int caddddr(int addr);
int cadddddr(int addr);
int cadr(int addr);
int car(int addr);
int callablep(int addr);
int cdar(int addr);
int cddr(int addr);
int cdr(int addr);
int characterp(int addr);
int clausep(int addr);
int colonp(int addr);
int compiler_anoymous_p(int x);
int compiler_variable_p(int x);
int compiled_zero_p(int addr);
int compiledp(int addr);
int compoundp(int addr);
int concat_atom(int x, int y);
int conjunctionp(int addr);
int cons(int car, int cdr);
int cons_next(int x, int y);
int cons_prev(int x, int y);
int constantp(int addr);
int convert_to_variant(int x);
int convert_to_variable(int x);
int copy_heap(int x);
int copy_term(int x);
int copy_variable(int x);
int ctrl_to_number(char c);
int c_lang_p(int x);
int dcgp(int x);
int deref(int x, int th);
int deref1(int x, int th);
int disjunctionp(int addr);
int divide(int arg1, int arg2);
int eqgreaterp(int x1, int x2);
int eqlp(int addr1, int addr2);
int eqp(int addr1, int addr2);
int eqsmallerp(int x1, int x2);
int equalp(int addr1, int addr2);
int eval(int x);
int exec(int goal, int bindings, int rest, int th);
int exec_all(int goals, int bindings, int th);
void evalterm(int x, int [3]);
int exact_to_inexact(int x);
int exist_unbind_var_p(int x);
int export_check(int pred);
int expt(int x, int y);
int f_abs(int x);
int f_div(int x, int y);
int f_divide(int x, int y);
int f_expt(int x, int y);
int f_float(int x);
int f_integer(int x);
int f_leftshift(int x, int y);
int f_logicaland(int x, int y);
int f_logicalor(int x, int y);
int f_complement(int x, int y);
int f_minus(int x, int y);
int f_mod(int x, int y);
int f_mult(int x, int y);
int f_plus(int x, int y);
int f_rightshift(int x, int y);
int f_round(int x, int y);
int f_sqrt(int x);
int f_sin(int x);
int f_asin(int x);
int f_cos(int x);
int f_acos(int x);
int f_tan(int x);
int f_atan(int x);
int f_exp(int x);
int f_ln(int x);
int f_log(int x);
int f_randi(int x);
int f_random(int x);
int findatom(int x, int property);
int findvar(int sym);
int floatp(int x);
int formulap(int addr);
int formula1p(int addr);
int forcefalsep(int x);
int forcetruep(int x);
int freshcell(void);
int functionp(int addr);
int gcd(int x, int y);
int generate_all_variable(int x);
int generate_variable(int x);
int generate_variable1(int x, int y);
int gen_big(void);
int gen_n(int n);
int get_1st_weight(int addr);
int get_2nd_weight(int addr);
int get_msb(int x);
int get_nth(int x, int n);
int get_sign(int x);
int get_sp(int th);
int get_wp(int);
int get_up(void);
int get_goal(int n);
int get_cut_jmp(void);
int get_free(int x);
int get_goal(int x);
int get_nonfree(int x, int y, int z);
int get_predicate(int x);
int getatom(char *name, int property, int index);
int getsym(char *name, int index);
int gettrace(int goal);
int greaterp(int x1, int x2);
int groundp(int addr);
int has_cut_p(int addr);
int has_loop_p(int x, int y);
int has_no_value_p(int x);
int has_value_p(int addr);
int has_variable_p(int addr);
int hash(char *name);
int heavy999p(int addr);
int last(int x);
int ifthenp(int addr);
int ignore_optin_p(int x);
int inc_proof(int th);
int infixp(int addr);
int infix_operator_p(int addr);
int insert(int x, int y);
int int_gcd(int x, int y);
int int_lcm(int m, int n);
int integerp(int addr);
int isatomch(char c);
int isoctch(char c);
int isbinch(char c);
int ishexch(char c);
int isnumlis(int arg);
int isqrt(int x);
int isqrt1(int s, int s2, int x);
int keysort(int x);
int keyinsert(int x, int y);
int last_predicate(int x);
int laststr(char buf[]);
int lcm(int x, int y);
int length(int addr);
int leappointp(int x);
int list(int addr);
int list_to_ope(int x);
int list_to_structure(int x);
int list1(int x);
int list2(int x, int y);
int list3(int x1, int x2, int x3);
int list4(int x1, int x2, int x3, int x4);
int list5(int x1, int x2, int x3, int x4, int x5);
int list6(int x1, int x2, int x3, int x4, int x5, int x6);
int list7(int x1, int x2, int x3, int x4, int x5, int x6, int x7);
int list8(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
int list9(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9);
int list10(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9, int x10);
int listp(int addr);
int listremove(int x, int y);
int listremove3(int x1, int x2, int x3, int ls);
int listreverse(int x);
int aritycheck(int x, int y);
int long_int_quotient(int x, int y);
int long_int_remainder(int x, int y);
int long_long_quotient(int x, int y);
int long_long_remainder(int x, int y);
int longnump(int x);
int makealias(char *name, int stream, int type);
int makeatom(char *name, int property);
int makeatom1(char *name, int property);
int makeconst(char *name);
int makebigx(char *bignum);
int makehexbigx(char *bignum);
int makeoctbigx(char *bignum);
int makeope(char *name);
int makebinbigx(char *bignum);
int makecomp(char *name);
int makecopy(int x);
int makeexspec(int old_spec, int spec);
int makeflt(double floatn);
int makeint(int num);
int makelong(long long int lngnum);
int makepred(char *name);
int makefunc(char *name);
int makespec(int spec);
int makestr(char *name);
int makesys(char *name);
int makestream(FILE *port, int i_o, int type, int action ,int fname);
int makeuser(char *name);
int makevariant(int th);
int makevar(char *name);
int memory_variant(int x);
int memq(int x, int y);
int memberp(int x, int y);
int meta_check(int pred, int arity);
int minus(int arg1, int arg2);
int mixturep(int addr);
int mult(int arg1, int arg2);
int mode_option_p(int x);
int narrow_variable_p(int addr);
int negative_zerop(int x);
int negativep(int x);
int next(int x);
int nfindvar(int x);
int notated_builtinp(int addr);
int not_numeqp(int x, int y);
int now_checking_var_p(int x);
int nth(int addr, int n);
int nullp(int addr);
int numberp(int addr);
int numbertoken(char buf[]);
int numbervars_option_p(int x);
int numeqp(int x, int y);
int o_cons(int x, int y);
int o_dcg(int x, int y);
int o_define(int x, int y);
int o_ignore(int nest, int n);
int op_connect(int x, int y, int th);
int operate(int x);
int operationp(int addr);
int operatorp(int addr);
int parser(int operand, int operator, int weight, int spec, int terminal, int parsemode);
int parse(int operand, int operator);
int parse1(int operand, int operator ,int weight, int spec);
int plus(int arg1, int arg2);
int pop_stack(int th);
int pop_ustack(void);
int position_option_p(int x);
int positive_zerop(int x);
int positivep(int x);
int postfixp(int addr);
int predicatep(int addr);
int pred_to_str(int x);
int prefixp(int addr);
int prev(int x);
int prove(int goal, int bindings, int rest, int th);
int prove_all(int goals, int bindings, int th);
int quoted_option_p(int x);
int quotient(int x, int y);
int readparse(void);
int readitem(void);
int readitem1(void);
int readcurl(void);
int readlist(void);
int readparen(void);
int readdouble(void);
int read_string_term(int flag);
int receive_from_parent(void);
int receive_from_child(int n);
int receive_from_child_or(int n);
int receive_from_child_or1(int n);
int receive_from_child_or2(int n);
int remove_cut(int x);
int remove_duplicate(int x);
int replace(int x, int lis);
int reposition_option_p(int x);
int resolve_all(int end, int bindings, int n);
int resolve(int end, int bindings, int trail, int n);
int reverse(int x);
int set_sp(int x, int th);
int set_wp(int x, int th);
int set_up(int x);
int set_aux(int x, int y);
int set_var(int x, int y);
int s_remainder(int x, int y);
int see_trail(void);
int singletonp(int x);
int singleton_list(void);
int single_operation_p(int x);
int smallerp(int x1, int x2);
int sort(int x);
int sortsmaller(int x, int y);
int sorteqlp(int x, int y);
int spypointp(int x);
int structure_to_list(int x);
int structurep(int addr);
int streamp(int addr);
int stringp(int addr);
int string_length(int addr);
int singlep(int addr);
int streqp(int x, int y);
int str_to_pred(int x);
int symboltoken(char buf[]);
int takeoutbug(int key);
int termp(int addr);
int term_variables(int x, int y);
int type_option_p(int x);
int thunkp(int addr);
int unicodep(char c);
int unify(int x, int y, int th);
int unify_const(int x, int y, int th);
int unify_var(int x, int y, int th);
int unify_nil(int x, int y, int th);
int unique(int x);
int user_operation_p(int addr);
int user_operator_p(int addr);
int utf8_to_ucs4(char *p);
int valslist(int x);
int variablep(int addr);
int variantp(int addr);
int variable_convert1(int x);
int variable_convert2(int x);
int variable_convert3(int x);
int variable_convert4(int x);
int variable_name_list(void);
int variable_name_p(int x);
int variable_to_call(int x);
int varslist(int x);
int walpha_conversion(int x);
int wcons(int car, int cdr, int th);
int wide_integer_p(int addr);
int wide_variable_p(int addr);
int wlistcons(int x, int y, int th);
int wlist1(int x, int th);
int wlist2(int x, int y, int th);
int wlist3(int x1, int x2, int x3, int th);
int wlist4(int x1, int x2, int x3, int x4, int th);
int wlist5(int x1, int x2, int x3, int x4, int x5, int th);
int wlist6(int x1, int x2, int x3, int x4, int x5, int x6, int th);
int wlist7(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int th);
int wlist8(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int th);
int wlist9(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9, int th);
int wlist10(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9, int x10, int th);
int zerop(int x);
void add_hash_table(int x, int record_id, int index);
void add_data(int pred, int data);
void addtail_body1(int x, int y);
void apply_unify(int x);
void assign_variant(int x);
void bigx_gbc(int x);
void bigx_minus2(int arg, int c, int msb);
void bigx_plus2(int arg, int c, int msb);
void bindsym(int x, int val, int th);
void cellprint(int addr);
void checkarg(int test, char *fun, int arg);
void checkgbc(void);
void clear_input_buffer(void);
void clrcell(int addr);
void clrtrace(int goal);
void cut_zero(int x);
void debugger(int end, int bindings, int choice);
void dectrace(int goal);
void defbuiltin(char *name, int(*func)(int, int), int arity);
void defcompiled(char *name, int(*func)(int, int), int arity);
void definfix(char *name, int(*func)(int, int), int weight, int spec);
void defoperator(char *name, int(*func)(int, int), int weight, int spec, int opt);
void defuserfunction(char *name, int weight, int spec);
void definfixcomp(char *name, int(*func)(int, int), int weight, int spec);
void discard_trail(void);
void discard_trail_n(int n);
void dynamic_link(int x);
void error(int errnum, char *fun, int arg);
void errorcomp(int errnum, int name, int arg);
void execute(int x);
void gbc(void);
void gbcmark(void);
void gbcsweep(void);
void gettoken(void);
void heapdump(int start, int end);
void inctrace(int goal);
void init_parent(void);
void init_receiver(void);
void init_repl(void);
void initbuiltin(void);
void initcell(void);
void initoperator(void);
void initstream(void);
void insert_data(int pred, int data);
void markcell(int addr);
void markoblist(void);
void memoize_arity(int clause, int atom);
void print(int addr);
void printanswer(int addr);
void print_bigx(int x);
void printbody(int addr);
void printbody1(int addr);
void printc(char c);
void printstr(char* s);
void printint(int n);
void printlong(int addr);
void printclause(int addr);
void printenv(void);
void print_quoted(int addr);
void print_numbervars(int addr);
void print_not_quoted(int addr);
void print_goal(void);
void print_head(void);
void print_stack(void);
void printarguments(int addr);
void printcurl(int addr);
void printinfix(int addr);
void printlist(int addr);
void printlist_canonical(int addr);
void printlong(int addr);
void printpostfix(int addr);
void printprefix(int addr);
void printsexp(int addr);
void printtuple(int addr);
void push_stack(int x, int th);
void putinbag(int key, int data);
void query(int x, int th);
void query_break(int x, int th);
void recall_variant(int x);
void release_variant(int x);
void reset(int i);
void send_to_parent(int x);
void send_to_parent_buffer(void);
void sned_to_child(int n, int x);
void set_sign(int x, int y);
void sprint(int addr);
void prove_trace(int port, int goal, int bindings, int rest);
void ucs4_to_utf8(int n, char *p);
void unbind(int x, int th);
void unreadc(char c);
char *prolog_file_name(char *name);

//JUMP project
int b_system(int arglist, int n);
int b_date(int arglist, int n);
int b_dynamic_check(int arglist, int n);
int b_get_dynamic(int arglist, int n);
int b_get_execute(int arglist, int n);
int b_write_original_variable(int arglist, int n);
int dynamic_check1(int x);
int get_tag(int addr);
int get_int(int addr);
int listcons(int x, int y);
int set_car(int x, int y);
int set_cdr(int x, int y);
int makestrflt(char *str);
int makestrlong(char *str);
void debug(void);

// wiringPI
#ifdef __arm__
int b_wiringpi_setup_gpio(int arglist, int rest);
int b_wiringpi_spi_setup_ch_speed(int arglist, int rest);
int b_pwm_set_mode(int arglist, int rest);
int b_pwm_set_range(int arglist, int rest);
int b_pwm_set_clock(int arglist, int rest);
int b_pin_mode(int arglist, int rest);
int b_digital_write(int arglist, int rest);
int b_digital_write_byte(int arglist, int rest);
int b_pwm_write(int arglist, int rest);
int b_pull_up_dn_control(int arglist, int rest);
int b_digital_read(int arglist, int rest);
int b_delay(int arglist, int rest);
int b_delay_microseconds(int arglist, int rest);
int b_timer_microseconds(int arglist, int rest);
#endif

// edit 
struct position{
    int row;
    int col;
};

int b_edit(int arglist, int n);
void edit_screen(int x);
void display_command(int arg);
void display_screen();
void display_line(int line);
void setcolor(int n);
void backspace();
void insertcol();
void insertrow();
int n_getch();
void deleterow();
int findeol(int row);
struct position findlparen(int bias);
struct position findrparen(int bias);
struct position findlbracket(int bias);
struct position findrbracket(int bias);
void restore_paren();
void restore_bracket();
void emphasis_lparen();
void emphasis_rparen();
void emphasis_lbracket();
void emphasis_rbracket();
void softtabs(int n);
void save_data(int arg1);
int findnext(int row, int col);
void remove_headspace(int row);
void copy_selection();
void paste_selection();
void delete_selection();
int check_token(int row, int col);
char* get_fragment();
void find_candidate();
void replace_fragment(char* newstr);
void display_buffer(void);
void check_token_buffer(int col);
int findlparen_buffer(int col);
int findrparen_buffer(int col);
int findlbracket_buffer(int col);
int findrbracket_buffer(int col);
void emphasis_lparen_buffer(int col);
void emphasis_rparen_buffer(int col);
void emphasis_lbracket_buffer(int col);
void emphasis_rbracket_buffer(int col);
void reset_paren_bracket_buffer();
void restore_paren_buffer(int col);
void restore_bracket_buffer(int col);
char *get_fragment_buffer(int col);
void find_candidate_buffer(int col);
int replace_fragment_buffer(char* newstr, int col);
void insertcol_buffer(int col);
void backspace_buffer(int col);
int read_line(int flag);
int count_col(int x);
int count_col_buffer(int x);
