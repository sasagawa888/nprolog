#include <setjmp.h>
#include <stdio.h>
#include "npl.h"


typedef int (*fn0)();
typedef int (*fn1)(int);
typedef int (*fn2)(int , int);
typedef int (*fn3)(int , int , int);
typedef int (*fn4)(char*);
typedef int (*fn5)(int , int , int, int);
typedef void (*tpred)(char*, int(*pred)(int , int));
typedef void (*tuser)(char*, int(*user)(int , int), int weight, int spec);

static fn0 f0[NUM_FN0S];
static fn1 f1[NUM_FN1S];
static fn2 f2[NUM_FN2S];
static fn3 f3[NUM_FN3S];
static fn4 f4[NUM_FN4S];
static fn5 f5[NUM_FN5S];
tpred deftpred;
tuser deftinfix;
tpred deftsys;

static dp[10]; // disjunction pointer

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

void init5(int n, tpred x){
    f5[n] = (fn5)x;
}


//for define compiled builtin predicate
void init_deftpred(tpred x){
    deftpred = (tpred)x;
}

//for define infix compiled builtin predicate
void init_deftinfix(tuser x){
    deftinfix = (tuser)x;
}


static inline int Jcheckgbc(void)
{
    return f0[CHECKGBC_IDX]();
}

static inline int Jgbc(void)
{
    return f0[GBC_IDX]();
}

static inline int Jfreshcell(void)
{
    return f0[FRESHCELL_IDX]();
}

static inline int Jdebug(void) {
    return f0[DEBUG_IDX]();
}


static inline int Jcar(x){
    return f1[CAR_IDX](x);
}

static inline int Jcdr(int x) {
    return f1[CDR_IDX](x);
}

static inline int Jcadr(int x) {
    return f1[CADR_IDX](x);
}

static inline int Jcaddr(int x) {
    return f1[CADDR_IDX](x);
}

static inline int Jcaar(int x) {
    return f1[CAAR_IDX](x);
}

static inline int Jcadar(int x) {
    return f1[CADAR_IDX](x);
}

static inline int Jprint(int x) {
    return f1[PRINT_IDX](x);
}

static inline int Jmakeint(int x) {
    return f1[MAKEINT_IDX](x);
}


static inline int Jlength(int x) {
    return f1[LENGTH_IDX](x);
}


static inline int Jget_int(int x) {
    return f1[GET_INT_IDX](x);
}

static inline int Jlist1(int x) {
    return f1[LIST1_IDX](x);
}

static inline int Jrandom(int th) {
    return f1[RANDOM_IDX](th);
}

static inline int Jrandi(int x) {
    return f1[RANDI_IDX](x);
}


static inline int Jlistp(int x) {
    return f1[LISTP_IDX](x);
}

static inline int Jstructurep(int x) {
    return f1[STRUCTUREP_IDX](x);
}


static inline int Jvariablep(int x) {
    return f1[VARIABLEP_IDX](x);
}

static inline int Jget_sp(int x) {
    return f1[GET_SP_IDX](x);
}


static inline int Jget_wp(int x) {
    return f1[GET_WP_IDX](x);
}

static inline int Jinc_proof(int x) {
    return f1[INC_PROOF_IDX](x);
}


static inline int Jmakevariant(int x) {
    return f1[MAKEVARIANT_IDX](x);
}



static inline int Jcons(int x, int y) {
    return f2[CONS_IDX](x, y);
}


static inline int Jeqp(int x, int y) {
    return f2[EQP_IDX](x, y);
}

static inline int Jequalp(int x, int y) {
    return f2[EQUALP_IDX](x, y);
}


static inline int Jnumeqp(int x, int y) {
    return f2[NUMEQP_IDX](x, y);
}

static inline int Jsmallerp(int x, int y) {
    return f2[SMALLERP_IDX](x, y);
}

static inline int Jeqsmallerp(int x, int y) {
    return f2[EQSMALLERP_IDX](x, y);
}

static inline int Jgreaterp(int x, int y) {
    return f2[GREATERP_IDX](x, y);
}

static inline int Jeqgreaterp(int x, int y) {
    return f2[EQGREATERP_IDX](x, y);
}


static inline int Jlistcons(int x, int y) {
    return f2[LISTCONS_IDX](x, y);
}

static inline int Jlist2(int x, int y) {
    return f2[LIST2_IDX](x, y);
}

static inline int Jset_car(int x, int y) {
    return f2[SET_CAR_IDX](x, y);
}

static inline int Jset_cdr(int x, int y) {
    return f2[SET_CDR_IDX](x, y);
}


static inline int Jset_aux(int x, int y) {
    return f2[SET_AUX_IDX](x, y);
}

static inline int Jnot_numeqp(int x, int y) {
    return f2[NOT_NUMEQP_IDX](x, y);
}

static inline int Jdiv(int x, int y) {
    return f2[DIV_IDX](x, y);
}

static inline int Jset_var(int x, int y) {
    return f2[SET_VAR_IDX](x, y);
}


static inline int Jnth(int x, int y) {
    return f2[NTH_IDX](x, y);
}

static inline int Junbind(int x, int th) {
    return f2[UNBIND_IDX](x, th);
}

static inline int Jset_wp(int x, int th) {
    return f2[SET_WP_IDX](x,th);
}


static inline int Jderef(int x, int th) {
    return f2[DEREF_IDX](x,th);
}

static inline int Jwlist1(int x, int th) {
    return f2[WLIST1_IDX](x,th);
}


static inline int Jsin(int x, int th) {
    return f2[SIN_IDX](x,th);
}

static inline int Jasin(int x, int th) {
    return f2[ASIN_IDX](x,th);
}

static inline int Jcos(int x, int th) {
    return f2[COS_IDX](x,th);
}

static inline int Jacos(int x, int th) {
    return f2[ACOS_IDX](x,th);
}

static inline int Jtan(int x, int th) {
    return f2[TAN_IDX](x,th);
}

static inline int Jatan(int x, int th) {
    return f2[ATAN_IDX](x,th);
}

static inline int Jexp(int x, int th) {
    return f2[EXP_IDX](x,th);
}

static inline int Jlog(int x, int th) {
    return f2[LOG_IDX](x,th);
}

static inline int Jln(int x, int th) {
    return f2[LN_IDX](x,th);
}


static inline int Jlist3(int x, int y, int z) {
    return f3[LIST3_IDX](x, y, z);
}

static inline int Jerrorcomp(int x, int y, int z) {
    return f3[ERRORCOMP_IDX](x, y, z);
}

static inline int Jwlistcons(int x, int y, int th) {
    return f3[WLISTCONS_IDX](x, y, th);
}

static inline int Junify(int x, int y, int th) {
    return f3[UNIFY_IDX](x, y, th);
}

static inline int Junify_var(int x, int y, int th) {
    return f3[UNIFY_VAR_IDX](x, y, th);
}

static inline int Junify_const(int x, int y, int th) {
    return f3[UNIFY_CONST_IDX](x, y, th);
}


static inline int Junify_nil(int x, int y, int th) {
    return f3[UNIFY_NIL_IDX](x, y, th);
}


static inline int Jexec_all(int x, int y, int th) {
    return f3[EXEC_ALL_IDX](x, y, th);
}

static inline int Jwcons(int x, int y, int th) {
    return f3[WCONS_IDX](x, y, th);
}

static inline int Jwlist2(int x, int y, int th) {
    return f3[WLIST2_IDX](x, y,th);
}


static inline int Jaddtail_body(int x, int y, int th) {
    return f3[ADDTAIL_BODY_IDX](x, y, th);
}

static inline int Jplus(int x, int y, int th) {
    return f3[PLUS_IDX](x, y, th);
}

static inline int Jminus(int x, int y, int th) {
    return f3[MINUS_IDX](x, y, th);
}

static inline int Jmult(int x, int y, int th) {
    return f3[MULT_IDX](x, y, th);
}

static inline int Jdivide(int x, int y, int th) {
    return f3[DIVIDE_IDX](x, y, th);
}

static inline int Jremainder(int x, int y, int th) {
    return f3[REMAINDER_IDX](x, y, th);
}

static inline int Jquotient(int x, int y, int th) {
    return f3[QUOTIENT_IDX](x, y, th);
}


static inline int Jmod(int x, int y, int th) {
    return f3[MOD_IDX](x, y, th);
}

static inline int Jexpt(int x, int y, int th) {
    return f3[EXPT_IDX](x, y, th);
}

static inline int Jsqrt(int x, int y, int th) {
    return f3[SQRT_IDX](x, y, th);
}

static inline int Jleftshift(int x, int y, int th) {
    return f3[LEFTSHIFT_IDX](x, y, th);
}

static inline int Jrightshift(int x, int y, int th) {
    return f3[RIGHTSHIFT_IDX](x, y, th);
}

static inline int Jlogicaland(int x, int y, int th) {
    return f3[LOGICALAND_IDX](x, y, th);
}

static inline int Jlogicalor(int x, int y, int th) {
    return f3[LOGICALOR_IDX](x, y, th);
}

static inline int Jcomplement(int x, int y, int th) {
    return f3[COMPLEMENT_IDX](x, y, th);
}

static inline int Jround(int x, int y, int th) {
    return f3[ROUND_IDX](x, y, th);
}


static inline int Jmakeconst(char* x) {
    return f4[MAKECONST_IDX](x);
}

static inline int Jmakepred(char* x) {
    return f4[MAKEPRED_IDX](x);
}

static inline int Jmakevar(char* x) {
    return f4[MAKEVAR_IDX](x);
}

static inline int Jmakestrflt(char* x) {
    return f4[MAKESTRFLT_IDX](x);
}

static inline int Jmakecomp(char* x) {
    return f4[MAKECOMP_IDX](x);
}

static inline int Jmakesys(char* x) {
    return f4[MAKESYS_IDX](x);
}

static inline int Jmakeope(char* x) {
    return f4[MAKEOPE_IDX](x);
}

static inline int Jmakeuser(char* x) {
    return f4[MAKEUSER_IDX](x);
}

static inline int Jmakestrlong(char* x) {
    return f4[MAKESTRLONG_IDX](x);
}

static inline int Jmakebig(char* x) {
    return f4[MAKEBIGX_IDX](x);
}

static inline int Jmakestr(char* x) {
    return f4[MAKESTR_IDX](x);
}

static inline int Jmakefun(char* x) {
    return f4[MAKEFUNC_IDX](x);
}


static inline int Jcallsubr(int x, int y, int z, int th) {
    return f5[CALLSUBR_IDX](x, y, z, th);
}

static inline int Jwlist3(int x, int y, int z, int th) {
    return f5[WLIST3_IDX](x, y, z, th);
}
