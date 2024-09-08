#include <setjmp.h>
#include <stdio.h>
#include "npl.h"

/*
#define NIL     0
#define YES     2
#define NO      4
#define FEND    6
#define UNDEF   8
#define CUT     10
#define AND     12
#define OR      14
#define LEFTPAREN  	16
#define RIGHTPAREN	18
#define CALL    20
#define OCUT	22
#define ANOYVAR 24
#define DEFINE  26
#define ATMARK  28
#define COLON   30
#define NPLTRUE 32
#define NPLFALSE    34
#define CURL    36
#define IFTHEN  38
#define NUMVAR  40
#define UNDERBAR    42
#define DOTOBJ  44


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


//-------error code---
#define SYNTAX_ERR      1
#define BUILTIN_EXIST   2
#define CANT_READ       3
#define NOT_COMPUTABLE  9
#define OUT_OF_RANGE    10
#define MALLOC_OVERF    11
#define WRONG_ARGS      12
#define NOT_NUM         13
#define NOT_STR         14
#define NOT_LIST        15
#define NOT_ATOM         16
#define ILLEGAL_OPL_INPUT   17
#define UNCAUGHT_EXCEPTION       19
#define CANT_OPEN       20
#define FILE_EXIST      21
#define ILLEGAL_ARGS    22
#define NOT_CONS        23
#define CANT_MODIFY     24
#define NOT_INT         25
#define NOT_STREAM      26
#define NOT_OUT_STREAM  27
#define NOT_IN_STREAM   28
#define NOT_CHAR        29
#define NOT_FLT         30
#define CTRL_OVERF      31
#define END_STREAM      32
#define DIV_ZERO        33
#define CANT_PARSE      34
#define NOT_ARITHMETIC  35
#define FLT_OVERF       36
#define FLT_UNDERF      37
#define STACK_OVERF     38
#define SYSTEM_ERROR    39
#define UNDEF_PRED		40
#define EOF_ERROR       41
#define INSTANTATION_ERR    42
#define EXPONENT_ERR    43
#define OPE_SPEC_ERR    44
#define NOT_CALLABLE    45
#define NOT_VAR         46
#define EXISTENCE_ERR   47
#define NOT_SOURCE      48
#define ALIAS_EXIST     49
#define NOT_IO_MODE     50
#define NOT_CLOSE_OPTION    51   
#define NOT_STREAM_OPTION   52
#define NOT_OUTPUT_STREAM   53
#define NOT_ATOMIC          54
#define NOT_LESS_THAN_ZERO  55
#define NOT_COMPOUND        56
#define NON_EMPTY_LIST      57
#define NOT_INPUT_STREAM    58
#define PAST_EOF_INPUT      59
#define EVALUATION_ERR      60
#define STATIC_PROCEDURE    61
#define PRED_INDICATOR      62
#define NOT_OPEN_OPTION     63
#define OPE_PRIORITY_ERR    64
#define MODIFY_OPE_ERR      65
#define NOT_CHAR_CODE       66
#define RESOURCE_ERR        67
#define NOT_ORDER           68
#define NOT_TERM            69
#define RECORD_OVERF        70
#define NOT_RECORD          71
#define VARIANT_OVERF       72
#define ARITY_ERR           73
*/


typedef int (*fn0)();
typedef int (*fn1)(int);
typedef int (*fn2)(int , int);
typedef int (*fn3)(int , int , int);
typedef int (*fn4)(char*);
typedef void (*tpred)(char*, int(*pred)(int , int));
typedef void (*tuser)(char*, int(*user)(int , int), int weight, int spec);

fn0 f0[50];
fn1 f1[50];
fn2 f2[50];
fn3 f3[50];
fn4 f4[50];
tpred deftpred;
tuser deftinfix;
tpred deftsys;

void init0(int n, tpred x){
    f0[n] = (fn0)x;
}

void init1(int n, tpred x){
    f1[n] = (fn1)x;
}

void init2(int n, tpred x){
    f2[n] = (fn2)x;
}

void init3(int n, tpred x){
    f3[n] = (fn3)x;
}

void init4(int n, tpred x){
    f4[n] = (fn4)x;
}

//for define compiled builtin predicate
void init_deftpred(tpred x){
    deftpred = (tpred)x;
}

//for define infix compiled builtin predicate
void init_deftinfix(tuser x){
    deftinfix = (tuser)x;
}


#define Jcheckgbc()  (f0[CHECKGBC_IDX])()
#define Jgbc()	     (f0[GBC_IDX])()
#define Jfreshcell() (f0[FRESHCELL_IDX])()
#define Jmakevariant() (f0[MAKEVARIANT_IDX])()
#define Jget_sp()    (f0[GET_SP_IDX])()
#define Jget_wp()    (f0[GET_WP_IDX])()
#define Jdebug()     (f0[DEBUG_IDX])()
#define Jinc_proof() (f0[INC_PROOF_IDX])()
#define Jpop_ustack() (f0[POP_USTACK_IDX])()
#define Jget_up()    (f0[GET_UP_IDX])()

#define Jcar(x)      (f1[CAR_IDX])(x)
#define Jcdr(x)      (f1[CDR_IDX])(x)
#define Jcadr(x)     (f1[CADR_IDX])(x)
#define Jcaddr(x)    (f1[CADDR_IDX])(x)
#define Jcaar(x)     (f1[CAAR_IDX])(x)
#define Jcadar(x)    (f1[CADAR_IDX])(x)
#define Jprint(x)    (f1[PRINT_IDX])(x)
#define Jmakeint(x)  (f1[MAKEINT_IDX])(x)
#define Junbind(x)   (f1[UNBIND_IDX])(x)
#define Jlength(x)   (f1[LENGTH_IDX])(x)
#define Jset_sp(x)   (f1[SET_UP_IDX])(x)
#define Jderef(x)    (f1[DEREF_IDX])(x)
#define Jpush_ustack(x) (f1[PUSH_USTACK_IDX])(x)
#define Jget_int(x)  (f1[GET_INT_IDX])(x)
#define Jsin(x)      (f1[SIN_IDX])(x)
#define Jasin(x)     (f1[ASIN_IDX])(x)
#define Jcos(x)      (f1[COS_IDX])(x)
#define Jacos(x)     (f1[ACOS_IDX])(x)
#define Jtan(x)      (f1[TAN_IDX])(x)
#define Jatan(x)     (f1[ATAN_IDX])(x)
#define Jexp(x)      (f1[EXP_IDX])(x)
#define Jlog(x)      (f1[LOG_IDX])(x)
#define Jln(x)       (f1[LN_IDX])(x)
#define Jround(x)    (f1[ROUND_IDX])(x)
#define Jlist1(x)    (f1[LIST1_IDX])(x)
#define Jrandom(x)   (f1[RANDOM_IDX])(x)
#define Jset_wp(x)   (f1[SET_UP_IDX])(x)
#define Jwlist1(x)   (f1[WLIST1_IDX])(x)
#define Jexecute(x)  (f1[EXECUTE_IDX])(x)
#define Jlistp(x)    (f1[LISTP_IDX])(x)
#define Jstructurep(x) (f1[STRUCTUREP_IDX])(x)
#define Jset_up(x)   (f1[SET_UP_IDX])(x)
#define Jvariablep(x) (f1[VARIABLEP_IDX])(x)

#define Jcons(x,y)   (f2[CONS_IDX])(x,y)
#define Jplus(x,y)   (f2[PLUS_IDX])(x,y)
#define Jminus(x,y)  (f2[MINUS_IDX])(x,y)
#define Jmult(x,y)   (f2[MULT_IDX])(x,y)
#define Jdivide(x,y) (f2[DIVIDE_IDX])(x,y)
#define Jremainder(x,y) (f2[REMAINDER_IDX])(x,y)
#define Jquotient(x,y) (f2[QUOTIENT_IDX])(x,y)
#define Jeqp(x,y)    (f2[EQP_IDX])(x,y)
#define Jnumeqp(x,y) (f2[NUMEQP_IDX])(x,y)
#define Jsmallerp(x,y) (f2[SMALLERP_IDX])(x,y)
#define Jeqsmallerp(x,y) (f2[EQSMALLERP_IDX])(x,y)
#define Jgreaterp(x,y) (f2[GREATERP_IDX])(x,y)
#define Jeqgreaterp(x,y) (f2[EQGREATERP_IDX])(x,y)
#define Junify(x,y)      (f2[UNIFY_IDX])(x,y)
#define Jmod(x,y)		 (f2[MOD_IDX])(x,y)
#define Jexpt(x,y)       (f2[EXPT_IDX])(x,y)
#define Jsqrt(x,y)       (f2[SQRT_IDX])(x,y)
#define Jleftshift(x,y)  (f2[LEFTSHIFT_IDX])(x,y)
#define Jrightshift(x,y) (f2[RIGHTSHIFT_IDX])(x,y)
#define Jlogicaland(x,y) (f2[LOGICALAND_IDX])(x,y)
#define Jlogicalor(x,y)  (f2[LOGICALOR_IDX])(x,y)
#define Jlistcons(x,y)   (f2[LISTCONS_IDX])(x,y)
#define Jlist2(x,y)      (f2[LIST2_IDX])(x,y)
#define Jset_car(x,y)    (f2[SET_CAR_IDX])(x,y)
#define Jset_cdr(x,y)    (f2[SET_CDR_IDX])(x,y)
#define Jcomplement(x)   (f2[COMPLEMENT_IDX])(x,y)
#define Jset_aux(x,y)    (f2[SET_AUX_IDX])(x,y)
#define Jnot_numeqp(x,y) (f2[NOT_NUMEQP_IDX])(x,y)
#define Jdiv(x,y)        (f2[DIV_IDX])(x,y)
#define Jset_var(x,y)    (f2[SET_VAR_IDX])(x,y)
#define Jwcons(x,y)        (f2[WCONS_IDX])(x,y)
#define Jwlist2(x,y)       (f2[WLIST2_IDX])(x,y)
#define Jwlistcons(x,y)    (f2[WLISTCONS_IDX])(x,y)
#define Jaddtail_body(x,y)      (f2[ADDTAIL_BODY_IDX])(x,y)
#define Jnth(x,y)          (f2[NTH_IDX])(x,y)
#define Junify_const(x,y)  (f2[UNIFY_CONST_IDX])(x,y)
#define Junify_var(x,y)    (f2[UNIFY_VAR_IDX])(x,y)
#define Junify_nil(x,y)    (f2[UNIFY_NIL_IDX])(x,y)
#define Jprove_all(x,y)    (f2[PROVE_ALL_IDX])(x,y)

#define Jlist3(x,y,z)       (f3[1])(x,y,z)
#define Jcallsubr(x,y,z)    (f3[2])(x,y,z)
#define Jwlist3(x,y,z)      (f3[3])(x,y,z)
#define Jerrorcomp(x,y,z)   (f3[4])(x,y,z)

#define Jmakeconst(x)  (f4[0])(x)
#define Jmakepred(x)   (f4[1])(x)
#define Jmakevar(x)    (f4[2])(x)
#define Jmakestrflt(x) (f4[3])(x)
#define Jmakecomp(x)   (f4[4])(x)
#define Jmakesys(x)    (f4[5])(x)
#define Jmakeope(x)    (f4[6])(x)
#define Jmakeuser(x)   (f4[7])(x)
#define Jmakestrlong(x) (f4[8])(x)
#define Jmakebig(x)    (f4[9])(x)
#define Jmakestr(x)    (f4[10](x))
#define Jmakefun(x)   (f4[11](x))

