#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "npl.h"


typedef void (*tpred) (char *, int (*pred) (int, int));
typedef void (*tuser) (char *, int (*user) (int, int), int weight, int spec);

void
dynamic_link (int x)
{
  char str[256] = { "./" };
  void *hmod;

  int (*init_f0) (int x, tpred y);
  int (*init_f1) (int x, tpred y);
  int (*init_f2) (int x, tpred y);
  int (*init_f3) (int x, tpred y);
  int (*init_f4) (int x, tpred y);
  void (*init_deftpred) (tpred x);
  void (*init_deftinfix) (tuser x);
  void (*init_tpredicate) ();
  void (*init_declare) ();

  if (strstr (GET_NAME (x), "/"))
    strcpy (str, GET_NAME (x));
  else
    strcat (str, GET_NAME (x));

  hmod = dlopen (str, RTLD_LAZY);
  if (hmod == NULL)
    error (ILLEGAL_ARGS, "load", x);

  init_f0 = dlsym (hmod, "init0");
  init_f1 = dlsym (hmod, "init1");
  init_f2 = dlsym (hmod, "init2");
  init_f3 = dlsym (hmod, "init3");
  init_f4 = dlsym (hmod, "init4");
  init_deftpred = dlsym (hmod, "init_deftpred");
  init_deftinfix = dlsym (hmod, "init_deftinfix");
  init_tpredicate = dlsym (hmod, "init_tpredicate");
  init_declare = dlsym (hmod, "init_declare");

  //argument-0 type
  init_f0 (0, (tpred) checkgbc);
  init_f0 (1, (tpred) gbc);
  init_f0 (2, (tpred) freshcell);
  init_f0 (3, (tpred) makevariant);
  init_f0 (4, (tpred) get_sp);
  init_f0 (5, (tpred) get_wp);
  init_f0 (6, (tpred) debug);
  init_f0 (7, (tpred) inc_proof);
  init_f0 (8, (tpred) pop_ustack);
  init_f0 (9, (tpred) get_up);

  //argument-1 type
  init_f1 (0, (tpred) car);
  init_f1 (1, (tpred) cdr);
  init_f1 (2, (tpred) cadr);
  init_f1 (3, (tpred) caddr);
  init_f1 (4, (tpred) caar);
  init_f1 (5, (tpred) cadar);
  init_f1 (6, (tpred) print);
  init_f1 (7, (tpred) makeint);
  init_f1 (9, (tpred) unbind);
  init_f1 (12, (tpred) length);
  init_f1 (13, (tpred) set_sp);

  init_f1 (15, (tpred) deref);
  init_f1 (16, (tpred) push_ustack);
  init_f1 (17, (tpred) get_int);
  init_f1 (18, (tpred) f_sin);
  init_f1 (19, (tpred) f_asin);
  init_f1 (20, (tpred) f_cos);
  init_f1 (21, (tpred) f_acos);
  init_f1 (22, (tpred) f_tan);
  init_f1 (23, (tpred) f_atan);
  init_f1 (24, (tpred) f_exp);
  init_f1 (25, (tpred) f_log);
  init_f1 (26, (tpred) f_floor);
  init_f1 (27, (tpred) f_ceiling);
  init_f1 (28, (tpred) f_truncate);
  init_f1 (29, (tpred) f_sign);
  init_f1 (30, (tpred) f_round);
  init_f1 (31, (tpred) list1);
  init_f1 (33, (tpred) f_random);
  init_f1 (34, (tpred) set_wp);
  init_f1 (35, (tpred) wlist1);
  init_f1 (36, (tpred) operate);
  init_f1 (37, (tpred) listp);
  init_f1 (38, (tpred) structurep);
  init_f1 (39, (tpred) set_up);
  init_f1 (40, (tpred) variablep);

  //argument-2 type
  init_f2 (0, (tpred) cons);
  init_f2 (1, (tpred) f_plus);
  init_f2 (2, (tpred) f_minus);
  init_f2 (3, (tpred) f_mult);
  init_f2 (4, (tpred) f_divide);
  init_f2 (5, (tpred) s_remainder);
  init_f2 (6, (tpred) quotient);
  init_f2 (7, (tpred) eqp);
  init_f2 (8, (tpred) numeqp);
  init_f2 (9, (tpred) smallerp);
  init_f2 (10, (tpred) eqsmallerp);
  init_f2 (11, (tpred) greaterp);
  init_f2 (12, (tpred) eqgreaterp);
  init_f2 (13, (tpred) unify);
  init_f2 (14, (tpred) f_mod);
  init_f2 (15, (tpred) gcd);
  init_f2 (16, (tpred) lcm);
  init_f2 (17, (tpred) f_expt);
  init_f2 (18, (tpred) f_sqrt);
  init_f2 (19, (tpred) f_leftshift);
  init_f2 (20, (tpred) f_rightshift);
  init_f2 (21, (tpred) f_logicaland);
  init_f2 (22, (tpred) f_logicalor);
  init_f2 (23, (tpred) f_exclusiveor);
  init_f2 (24, (tpred) f_inclusiveand);
  init_f2 (25, (tpred) listcons);
  init_f2 (26, (tpred) list2);
  init_f2 (27, (tpred) set_car);
  init_f2 (28, (tpred) set_cdr);
  init_f2 (29, (tpred) f_rem);
  init_f2 (30, (tpred) f_complement);
  init_f2 (31, (tpred) set_aux);
  init_f2 (32, (tpred) not_numeqp);
  init_f2 (34, (tpred) f_div);
  init_f2 (35, (tpred) set_var);
  init_f2 (36, (tpred) wcons);
  init_f2 (37, (tpred) wlist2);
  init_f2 (38, (tpred) wlistcons);
  init_f2 (39, (tpred) addtail_body);
  init_f2 (40, (tpred) nth);
  init_f2 (41, (tpred) unify_const);
  init_f2 (42, (tpred) unify_var);
  init_f2 (43, (tpred) unify_nil);
  init_f2 (44, (tpred) prove_all);


  //argument-3
  init_f3 (1, (tpred) list3);
  init_f3 (2, (tpred) callsubr);
  init_f3 (3, (tpred) wlist3);
  init_f3 (4, (tpred) errorcomp);

  //argument-1 string type
  init_f4 (0, (tpred) makeconst);
  init_f4 (1, (tpred) makepred);
  init_f4 (2, (tpred) makevar);
  init_f4 (3, (tpred) makestrflt);
  init_f4 (4, (tpred) makecomp);
  init_f4 (5, (tpred) makesys);
  init_f4 (6, (tpred) makeope);
  init_f4 (7, (tpred) makeuser);
  init_f4 (8, (tpred) makestrlong);
  init_f4 (9, (tpred) makebigx);
  init_f4 (10, (tpred) makestr);
  init_f4 (11, (tpred) makefunc);

  init_deftpred ((tpred) defcompiled);
  init_deftinfix ((tuser) definfixcomp);
  init_tpredicate ();
  init_declare ();
  link_flag = 1;
  return;
}
