#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "npl.h"


typedef void (*tpred)(char *, int(*pred)(int, int));
typedef void (*tuser)(char *, int(*user)(int, int), int weight, int spec);

void dynamic_link(int x)
{
    char str[256] = { "./" };
    void *hmod;

    int (*init_f0)(int x, tpred y);
    int (*init_f1)(int x, tpred y);
    int (*init_f2)(int x, tpred y);
    int (*init_f3)(int x, tpred y);
    int (*init_f4)(int x, tpred y);
    void (*init_deftpred)(tpred x);
    void (*init_deftinfix)(tuser x);
    void (*init_tpredicate)();
    void (*init_declare)();

    if (strstr(GET_NAME(x), "/"))
	strcpy(str, GET_NAME(x));
    else
	strcat(str, GET_NAME(x));

    hmod = dlopen(str, RTLD_LAZY);
    if (hmod == NULL)
	error(ILLEGAL_ARGS, "load", x);

    init_f0 = dlsym(hmod, "init0");
    init_f1 = dlsym(hmod, "init1");
    init_f2 = dlsym(hmod, "init2");
    init_f3 = dlsym(hmod, "init3");
    init_f4 = dlsym(hmod, "init4");
    init_deftpred = dlsym(hmod, "init_deftpred");
    init_deftinfix = dlsym(hmod, "init_deftinfix");
    init_tpredicate = dlsym(hmod, "init_tpredicate");
    init_declare = dlsym(hmod, "init_declare");

    //argument-0 type
    init_f0(CHECKGBC_IDX, (tpred) checkgbc);
    init_f0(GBC_IDX, (tpred) gbc);
    init_f0(FRESHCELL_IDX, (tpred) freshcell);
    init_f0(MAKEVARIANT_IDX, (tpred) makevariant);
    init_f0(DEBUG_IDX, (tpred) debug);
    init_f0(INC_PROOF_IDX, (tpred) inc_proof);


    //argument-1 type
    init_f1(CAR_IDX, (tpred) car);
    init_f1(CDR_IDX, (tpred) cdr);
    init_f1(CADR_IDX, (tpred) cadr);
    init_f1(CADDR_IDX, (tpred) caddr);
    init_f1(CAAR_IDX, (tpred) caar);
    init_f1(CADAR_IDX, (tpred) cadar);
    init_f1(PRINT_IDX, (tpred) print);
    init_f1(MAKEINT_IDX, (tpred) makeint);
    init_f1(LENGTH_IDX, (tpred) length);
    init_f1(DEREF_IDX, (tpred) deref);
    init_f1(GET_INT_IDX, (tpred) get_int);
    init_f1(SIN_IDX, (tpred) f_sin);
    init_f1(ASIN_IDX, (tpred) f_asin);
    init_f1(COS_IDX, (tpred) f_cos);
    init_f1(ACOS_IDX, (tpred) f_acos);
    init_f1(TAN_IDX, (tpred) f_tan);
    init_f1(ATAN_IDX, (tpred) f_atan);
    init_f1(EXP_IDX, (tpred) f_exp);
    init_f1(LOG_IDX, (tpred) f_log);
    init_f1(LN_IDX, (tpred) f_ln);
    init_f1(LIST1_IDX, (tpred) list1);
    init_f1(RANDOM_IDX, (tpred) f_random);
    init_f1(RANDI_IDX, (tpred) f_randi);
    init_f1(SET_WP_IDX, (tpred) set_wp);
    init_f1(WLIST1_IDX, (tpred) wlist1);
    init_f1(OPERATE_IDX, (tpred) operate);
    init_f1(LISTP_IDX, (tpred) listp);
    init_f1(STRUCTUREP_IDX, (tpred) structurep);
    init_f1(VARIABLEP_IDX, (tpred) variablep);
    init_f1(GET_SP_IDX, (tpred) get_sp);
    init_f1(GET_WP_IDX, (tpred) get_wp);

    //argument-2 type
    init_f2(CONS_IDX, (tpred) cons);
    init_f2(PLUS_IDX, (tpred) f_plus);
    init_f2(MINUS_IDX, (tpred) f_minus);
    init_f2(MULT_IDX, (tpred) f_mult);
    init_f2(DIVIDE_IDX, (tpred) f_divide);
    init_f2(REMAINDER_IDX, (tpred) s_remainder);
    init_f2(QUOTIENT_IDX, (tpred) quotient);
    init_f2(EQP_IDX, (tpred) eqp);
    init_f2(EQUALP_IDX, (tpred) equalp);
    init_f2(NUMEQP_IDX, (tpred) numeqp);
    init_f2(SMALLERP_IDX, (tpred) smallerp);
    init_f2(EQSMALLERP_IDX, (tpred) eqsmallerp);
    init_f2(GREATERP_IDX, (tpred) greaterp);
    init_f2(EQGREATERP_IDX, (tpred) eqgreaterp);
    init_f2(UNIFY_IDX, (tpred) unify);
    init_f2(MOD_IDX, (tpred) f_mod);
    init_f2(EXPT_IDX, (tpred) f_expt);
    init_f2(SQRT_IDX, (tpred) f_sqrt);
    init_f2(LEFTSHIFT_IDX, (tpred) f_leftshift);
    init_f2(RIGHTSHIFT_IDX, (tpred) f_rightshift);
    init_f2(LOGICALAND_IDX, (tpred) f_logicaland);
    init_f2(LOGICALOR_IDX, (tpred) f_logicalor);
    init_f2(LISTCONS_IDX, (tpred) listcons);
    init_f2(LIST2_IDX, (tpred) list2);
    init_f2(SET_CAR_IDX, (tpred) set_car);
    init_f2(SET_CDR_IDX, (tpred) set_cdr);
    init_f2(COMPLEMENT_IDX, (tpred) f_complement);
    init_f2(SET_AUX_IDX, (tpred) set_aux);
    init_f2(NOT_NUMEQP_IDX, (tpred) not_numeqp);
    init_f2(DIV_IDX, (tpred) f_div);
    init_f2(SET_VAR_IDX, (tpred) set_var);
    init_f2(WCONS_IDX, (tpred) wcons);
    init_f2(WLIST2_IDX, (tpred) wlist2);
    init_f2(WLISTCONS_IDX, (tpred) wlistcons);
    init_f2(ADDTAIL_BODY_IDX, (tpred) addtail_body);
    init_f2(NTH_IDX, (tpred) nth);
    init_f2(UNIFY_CONST_IDX, (tpred) unify_const);
    init_f2(UNIFY_VAR_IDX, (tpred) unify_var);
    init_f2(UNIFY_NIL_IDX, (tpred) unify_nil);
    init_f2(ROUND_IDX, (tpred) f_round);
    init_f2(EXEC_ALL_IDX, (tpred) exec_all);
    init_f2(UNBIND_IDX, (tpred) unbind);
    init_f2(SET_SP_IDX, (tpred) set_sp);


    //argument-3
    init_f3(LIST3_IDX, (tpred) list3);
    init_f3(CALLSUBR_IDX, (tpred) callsubr);
    init_f3(WLIST3_IDX, (tpred) wlist3);
    init_f3(ERRORCOMP_IDX, (tpred) errorcomp);


    //argument-1 string type
    init_f4(MAKECONST_IDX, (tpred) makeconst);
    init_f4(MAKEPRED_IDX, (tpred) makepred);
    init_f4(MAKEVAR_IDX, (tpred) makevar);
    init_f4(MAKESTRFLT_IDX, (tpred) makestrflt);
    init_f4(MAKECOMP_IDX, (tpred) makecomp);
    init_f4(MAKESYS_IDX, (tpred) makesys);
    init_f4(MAKEOPE_IDX, (tpred) makeope);
    init_f4(MAKEUSER_IDX, (tpred) makeuser);
    init_f4(MAKESTRLONG_IDX, (tpred) makestrlong);
    init_f4(MAKEBIGX_IDX, (tpred) makebigx);
    init_f4(MAKESTR_IDX, (tpred) makestr);
    init_f4(MAKEFUNC_IDX, (tpred) makefunc);

    init_deftpred((tpred) defcompiled);
    init_deftinfix((tuser) definfixcomp);
    init_tpredicate();
    init_declare();
    link_flag = 1;
    return;
}
