#include <setjmp.h>
#include <stdio.h>
#include "npl.h"


typedef int (*fn0)();
typedef int (*fn1)(int);
typedef int (*fn2)(int , int);
typedef int (*fn3)(int , int , int);
typedef int (*fn4)(char*);
typedef void (*tpred)(char*, int(*pred)(int , int));
typedef void (*tuser)(char*, int(*user)(int , int), int weight, int spec);

fn0 f0[NUM_FN0S];
fn1 f1[NUM_FN1S];
fn2 f2[NUM_FN2S];
fn3 f3[NUM_FN3S];
fn4 f4[NUM_FN4S];
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

#define Jlist3(x,y,z)       (f3[LIST3_IDX])(x,y,z)
#define Jcallsubr(x,y,z)    (f3[CALLSUBR_IDX])(x,y,z)
#define Jwlist3(x,y,z)      (f3[WLIST3_IDX])(x,y,z)
#define Jerrorcomp(x,y,z)   (f3[ERRORCOMP_IDX])(x,y,z)

#define Jmakeconst(x)  (f4[MAKECONST_IDX])(x)
#define Jmakepred(x)   (f4[MAKEPRED_IDX])(x)
#define Jmakevar(x)    (f4[MAKEVAR_IDX])(x)
#define Jmakestrflt(x) (f4[MAKESTRFLT_IDX])(x)
#define Jmakecomp(x)   (f4[MAKECOMP_IDX])(x)
#define Jmakesys(x)    (f4[MAKESYS_IDX])(x)
#define Jmakeope(x)    (f4[MAKEOPE_IDX])(x)
#define Jmakeuser(x)   (f4[MAKEUSER_IDX])(x)
#define Jmakestrlong(x) (f4[MAKESTRLONG_IDX])(x)
#define Jmakebig(x)    (f4[MAKEBIGX_IDX])(x)
#define Jmakestr(x)    (f4[MAKESTR_IDX](x))
#define Jmakefun(x)   (f4[MAKEFUNC_IDX](x))

