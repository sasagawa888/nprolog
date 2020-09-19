#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <float.h>
#include <sys/stat.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#include "npl.h"

#define FLUSH __fpurge(stdin);

typedef void (*tpred)(char*, int(*pred)(int , int));

void dynamic_link(int x){
    char str[256] = {"./"};
    void* hmod;

    int (*init_f0)(int x, tpred y);
    int (*init_f1)(int x, tpred y);
    int (*init_f2)(int x, tpred y);
    int (*init_f3)(int x, tpred y);
    int (*init_f4)(int x, tpred y);
    void (*init_deftpred)(tpred x);
    void (*init_tpredicate)();
    void (*init_declare)();

    if(strstr(GET_NAME(x),"/"))
        strcpy(str,GET_NAME(x));
    else
        strcat(str,GET_NAME(x));

    hmod = dlopen(str, RTLD_LAZY);
    if(hmod == NULL)
        error(ILLEGAL_ARGS, "load", x);

    init_f0 = dlsym(hmod, "init0");
    init_f1 = dlsym(hmod, "init1");
    init_f2 = dlsym(hmod, "init2");
    init_f3 = dlsym(hmod, "init3");
    init_f4 = dlsym(hmod, "init4");
    init_deftpred = dlsym(hmod, "init_deftpred");
    init_tpredicate = dlsym(hmod, "init_tpredicate");
    init_declare = dlsym(hmod, "init_declare");

    //argument-0 type
    init_f0(0,(tpred)checkgbc);
    init_f0(1,(tpred)gbc);
    init_f0(2,(tpred)freshcell);
    init_f0(3,(tpred)makevariant);
    init_f0(13,(tpred)get_wp);

    //argument-1 type
    init_f1(0,(tpred)car);
    init_f1(1,(tpred)cdr);
    init_f1(2,(tpred)cadr);
    init_f1(3,(tpred)caddr);
    init_f1(4,(tpred)caar);
    init_f1(5,(tpred)cadar);
    init_f1(6,(tpred)print);
    init_f1(7,(tpred)makeint);
    init_f1(9,(tpred)unbind);
    init_f1(13,(tpred)set_sp);
    init_f1(15,(tpred)deref);
    init_f1(17,(tpred)get_int);
    init_f1(18,(tpred)f_sin);
    init_f1(19,(tpred)f_asin);
    init_f1(20,(tpred)f_cos);
    init_f1(21,(tpred)f_acos);
    init_f1(22,(tpred)f_tan);
    init_f1(23,(tpred)f_atan);
    init_f1(24,(tpred)f_exp);
    init_f1(25,(tpred)f_log);
    init_f1(26,(tpred)f_floor);
    init_f1(27,(tpred)f_ceiling);
    init_f1(28,(tpred)f_truncate);
    init_f1(29,(tpred)f_sign);
    init_f1(30,(tpred)f_round);
    init_f1(31,(tpred)list1);
    init_f1(33,(tpred)f_random);
    init_f1(34,(tpred)set_wp);
    init_f1(35,(tpred)wlist1);

    //argument-2 type
    init_f2(0,(tpred)cons);
    init_f2(1,(tpred)f_plus);
    init_f2(2,(tpred)f_minus);
    init_f2(3,(tpred)f_mult);
    init_f2(4,(tpred)f_divide);
    init_f2(5,(tpred)s_remainder);
    init_f2(6,(tpred)quotient);
    init_f2(7,(tpred)eqp);
    init_f2(8,(tpred)numeqp);
    init_f2(9,(tpred)smallerp);
    init_f2(10,(tpred)eqsmallerp);
    init_f2(11,(tpred)greaterp);
    init_f2(12,(tpred)eqgreaterp);
    init_f2(13,(tpred)unify);
    init_f2(14,(tpred)f_mod);
    init_f2(15,(tpred)gcd);
    init_f2(16,(tpred)lcm);
    init_f2(17,(tpred)f_expt);
    init_f2(18,(tpred)f_sqrt);
    init_f2(19,(tpred)f_leftshift);
    init_f2(20,(tpred)f_rightshift);
    init_f2(21,(tpred)f_logicaland);
    init_f2(22,(tpred)f_logicalor);
    init_f2(23,(tpred)f_exclusiveor);
    init_f2(24,(tpred)f_inclusiveand);
    init_f2(25,(tpred)listcons);
    init_f2(26,(tpred)list2);
    init_f2(27,(tpred)set_car);
    init_f2(28,(tpred)set_cdr);
    init_f2(29,(tpred)f_rem);
    init_f2(30,(tpred)f_complement);
    init_f2(31,(tpred)set_aux);
    init_f2(32,(tpred)not_numeqp);
    init_f2(34,(tpred)f_div);
    init_f2(35,(tpred)set_var);
    init_f2(36,(tpred)wcons);
    init_f2(37,(tpred)wlist2);
    init_f2(38,(tpred)wlistcons);

    //argument-3
    init_f3(0,(tpred)prove_all);
    init_f3(1,(tpred)list3);
    init_f3(2,(tpred)callsubr);
    init_f3(3,(tpred)wlist3);

    //argument-1 string type
    init_f4(0,(tpred)makeconst);
    init_f4(1,(tpred)makepred);
    init_f4(2,(tpred)makevar);
    init_f4(3,(tpred)makestrflt);
    init_f4(4,(tpred)makecomp);
    init_f4(5,(tpred)makesys);
    init_f4(6,(tpred)makeope);
    init_f4(7,(tpred)makeuser);
    init_f4(8,(tpred)makestrlong);
    init_f4(9,(tpred)makebigx);

    init_deftpred((tpred)defcompiled);
    init_tpredicate();
    init_declare();
    link_flag = 1;
    return;
}

void defoperator(char *name, int(*func)(int, int), int weight, int spec ,int opt){
    int atom,old_weight,old_spec,new_weight,new_spec,ex_spec;

    if(opt == 0)
        atom = makeatom(name,OPE);
    else if(opt == 1)
        atom = makeatom(name,SYS);
    else
        atom = makeatom(name,USER);

    old_spec = GET_OPT(atom);
    if(old_spec == FX ||
       old_spec == FY ||
       old_spec == XFX ||
       old_spec == YFX ||
       old_spec == XFY ||
       old_spec == XF ||
       old_spec == YF)
        old_weight = GET_CDR(atom);
    else if(spec == FX || spec == FY || spec == XF || spec == YF)
        old_weight = get_1st_weight(atom);
    else
        old_weight = get_2nd_weight(atom);

    if(old_spec == NIL){
        if(func != NIL)
            SET_SUBR(atom,func);

        SET_CDR(atom,weight);
        SET_OPT(atom,spec);
        weight = makeint(weight);
        spec = makespec(spec);
        op_list = listcons(list3(weight,spec,atom),op_list);
        return;
    }
    else{
        new_weight = 0;
        new_spec = NIL;
        if(old_spec == XFX){
            if(spec == FX){
                new_spec = FX_XFX;
                new_weight = weight * 10000 + old_weight;
            }
            else if(spec == FY){
                new_spec = FY_XFX;
                new_weight = weight * 10000 + old_weight;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == YFX){
            if(spec == FX){
                new_spec = FX_YFX;
                new_weight = weight * 10000 + old_weight;
            }
            else if(spec == FY){
                new_spec = FY_YFX;
                new_weight = weight * 10000 + old_weight;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == XFY){
            if(spec == FX){
                new_spec = FX_XFY;
                new_weight = weight * 10000 + old_weight;
            }
            else if(spec == FY){
                new_spec = FY_XFY;
                new_weight = weight * 10000 + old_weight;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == XF){
            if(spec  == FX){
                new_weight = weight * 10000 + old_weight;
                new_spec = FX_XF;
            }
            else if(spec == FY){
                new_weight = weight * 10000 + old_weight;
                new_spec = FY_XF;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == YF){
            if(spec  == FX){
                new_weight = weight * 10000 + old_weight;
                new_spec = FX_YF;
            }
            else if(spec == FY){
                new_weight = weight * 10000 + old_weight;
                new_spec = FY_YF;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == FX){
            if(spec == XFX){
                new_weight = old_weight * 10000 + weight;
                new_spec = FX_XFX;
            }
            else if(spec == YFX){
                new_weight = old_weight * 10000 + weight;
                new_spec = FX_YFX;
            }
            else if(spec == XFY){
                new_weight = old_weight * 10000 + weight;
                new_spec = FX_XFY;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == FY){
            if(spec == XFX){
                new_weight = old_weight * 10000 + weight;
                new_spec = FY_XFX;
            }
            else if(spec == YFX){
                new_weight = old_weight * 10000 + weight;
                new_spec = FY_YFX;
            }
            else if(spec == XFY){
                new_weight = old_weight * 10000 + weight;
                new_spec = FY_XFY;
            }
            else{
                new_spec = spec;
                new_weight = weight;
            }
        }
        else if(old_spec == FX_XFX){
            if(spec == FX){
                new_spec = FX_XFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_XFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FX_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FX_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FX_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FX_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FX_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FX_YFX){
            if(spec == FX){
                new_spec = FX_YFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_YFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FX_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FX_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FX_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FX_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FX_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FX_XFY){
            if(spec == FX){
                new_spec = FX_XFY;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_XFY;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FX_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FX_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FX_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FX_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FX_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FY_XFX){
            if(spec == FX){
                new_spec = FX_XFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_XFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FY_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FY_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FY_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FY_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FY_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FY_YFX){
            if(spec == FX){
                new_spec = FX_YFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_YFX;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FY_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FY_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FY_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FY_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FY_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FY_XFY){
            if(spec == FX){
                new_spec = FX_XFY;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_XFY;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FY_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FY_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FY_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FY_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FY_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FX_XF){
            if(spec == FX){
                new_spec = FX_XF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_XF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FX_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FX_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FX_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FX_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FX_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FX_YF){
            if(spec == FX){
                new_spec = FX_YF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_YF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FX_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FX_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FX_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FX_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FX_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FY_XF){
            if(spec == FX){
                new_spec = FX_XF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_XF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FY_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FY_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FY_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FY_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FX_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }
        else if(old_spec == FY_YF){
            if(spec == FX){
                new_spec = FX_YF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == FY){
                new_spec = FY_YF;
                new_weight = weight * 10000 + old_weight % 10000;
            }
            else if(spec == XFX){
                new_spec = FY_XFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YFX){
                new_spec = FY_YFX;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XFY){
                new_spec = FY_XFY;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == XF){
                new_spec = FY_XF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
            else if(spec == YF){
                new_spec = FY_YF;
                new_weight = (old_weight / 10000)*10000 + weight;
            }
        }

        if(func != NIL)
            SET_SUBR(atom,func);
        SET_CDR(atom,new_weight);
        SET_OPT(atom,new_spec);

        ex_spec = makeexspec(old_spec,spec);
        weight = makeint(weight);
        spec = makespec(spec);
        op_list = listremove3(NIL,ex_spec,atom,op_list);
        op_list = cons(list3(weight,spec,atom),op_list);
        return;
    }
}

void definfix(char *name, int(*func)(int, int), int weight, int spec){
    int atom;

    atom = makeatom(name,SYS);
    SET_SUBR(atom,func);
    SET_CDR(atom,weight);
    SET_OPT(atom,spec);
    weight = makeint(weight);
    spec = makespec(spec);
    op_list = cons(list3(weight,spec,atom),op_list);
    return;
}

void defbuiltin(char *name, int(*func)(int, int)){
    int atom;

    atom = makeatom(name,SYS);
    SET_SUBR(atom,func);
    return;
}

void defcompiled(char *name, int(*func)(int, int)){
    int atom;

    atom = makeatom(name,COMP);
    SET_SUBR(atom,func);
    return;
}

void definfixcomp(char *name, int(*func)(int, int), int weight, int spec){
    int atom;

    atom = makeatom(name,COMP);
    SET_SUBR(atom,func);
    SET_CDR(atom,weight);
    SET_OPT(atom,spec);
    weight = makeint(weight);
    spec = makespec(spec);
    op_list = cons(list3(weight,spec,atom),op_list);
    return;
}


void initoperator(void){
    defoperator(":-",o_define,1200,XFX,0);
    defoperator(":-",o_define,1200,FX,0);
    defoperator("-->",o_dcg,1200,XFX,0);
    defoperator("?-",o_ignore,1200,FX,0);
    defoperator(",",o_ignore,1000,XFY,0);
    defoperator(";",o_ignore,1100,XFY,0);
    defoperator(":",o_ignore,50,XFX,0);
    defoperator(".",o_cons,50,FX,0);
    defoperator("+",f_plus,500,YFX,0);
    defoperator("+",f_plus,200,FY,0);
    defoperator("-",f_minus,500,YFX,0);
    defoperator("-",f_minus,200,FY,0);
    defoperator("*",f_mult,400,YFX,0);
    defoperator("**",f_expt,200,XFY,0);
    defoperator("^",f_expt,200,XFY,0);
    defoperator("/",f_divide,400,YFX,0);
    defoperator("//",f_div,400,YFX,0);
    defoperator("mod",f_mod,400,YFX,0);
    defoperator("rem",f_rem,400,YFX,0);
    defoperator("<<",f_leftshift,400,YFX,0);
    defoperator(">>",f_rightshift,400,YFX,0);
    defoperator("/\\",f_logicaland,500,YFX,0);
    defoperator("\\/",f_logicalor,500,YFX,0);
    defoperator("\\",f_complement,200,FY,0);
    defoperator("xor",f_exclusiveor,500,YFX,0);
    defoperator("iand",f_inclusiveand,500,YFX,0);
    return;
}

void initbuiltin(void){
    definfix(">",b_greater,700,XFX);
    definfix("<",b_smaller,700,XFX);
    definfix("=<",b_eqsmaller,700,XFX);
    definfix(">=",b_eqgreater,700,XFX);
    definfix("=:=",b_numeq,700,XFX);
    definfix("=\\=",b_notnumeq,700,XFX);
    definfix("=/=",b_notnumeq,700,XFX);
    definfix("@<",b_atsmaller,700,XFX);
    definfix("@=<",b_ateqsmaller,700,XFX);
    definfix("@>",b_atgreater,700,XFX);
    definfix("@>=",b_ateqgreater,700,XFX);
    definfix("is",b_is,700,XFX);
    definfix("=",b_unify,700,XFX);
    definfix("==",b_equalp,700,XFX);
    definfix("\\==",b_notequalp,700,XFX);
    definfix("\\=",b_notunify,700,XFX);
    definfix("=..",b_univ,700,XFX);
    definfix("@",o_ignore,100,XFX);
    definfix(":",b_colon,50,XFX);
    definfix("->",b_ifthen,1050,XFY);
    definfix("\\+",b_not,900,FY);

    defbuiltin("op",b_op);
    defbuiltin("!",b_cut);
    defbuiltin("assert",b_assert);
    defbuiltin("asserta",b_asserta);
    defbuiltin("assertz",b_assert);
    defbuiltin("abolish",b_abolish);
    defbuiltin("compare",b_compare);
    defbuiltin("read",b_read);
    defbuiltin("write",b_write);
    defbuiltin("display",b_write_canonical);
    defbuiltin("writeq",b_writeq);
    defbuiltin("put",b_put);
    defbuiltin("get",b_get);
    defbuiltin("get0",b_get0);
    defbuiltin("get_code",b_get_code);
    defbuiltin("get_byte",b_get_byte);
    defbuiltin("nl",b_nl);
    defbuiltin("tab",b_tab);
    defbuiltin("fail",b_fail);
    defbuiltin("not",b_not);
    defbuiltin("true",b_true);
    defbuiltin("halt",b_halt);
    defbuiltin("abort",b_abort);
    defbuiltin("listing",b_listing);
    defbuiltin("functor",b_functor);
    defbuiltin("arg",b_arg);
    defbuiltin("arg0",b_arg0);
    defbuiltin("consult",b_consult);
    defbuiltin("reconsult",b_reconsult);
    defbuiltin("open",b_open);
    defbuiltin("close",b_close);
    defbuiltin("see",b_see);
    defbuiltin("seen",b_seen);
    defbuiltin("tell",b_tell);
    defbuiltin("told",b_told);
    defbuiltin("flush_output",b_flush_output);
    defbuiltin("trace",b_trace);
    defbuiltin("notrace",b_notrace);
    defbuiltin("spy",b_spy);
    defbuiltin("nospy",b_nospy);
    defbuiltin("leash",b_leash);
    defbuiltin("debug",b_debug);
    defbuiltin("atom",b_atom);
    defbuiltin("string",b_string);
    defbuiltin("integer",b_integer);
    defbuiltin("real",b_real);
    defbuiltin("float",b_real);
    defbuiltin("number",b_number);
    defbuiltin("compound",b_compound);
    defbuiltin("ground",b_ground);
    defbuiltin("system",b_system);
    defbuiltin("var",b_var);
    defbuiltin("nonvar",b_nonvar);
    defbuiltin("atomic",b_atomic);
    defbuiltin("list",b_list);
    defbuiltin("gc",b_gbc);
    defbuiltin("measure",b_measure);
    defbuiltin("%ask",b_ask);
    defbuiltin("shell",b_shell);
    defbuiltin("sort",b_sort);
    defbuiltin("keysort",b_keysort);
    defbuiltin("mkdir",b_make_directory);
    defbuiltin("chdir",b_change_directory);
    defbuiltin("inc",b_inc);
    defbuiltin("dec",b_dec);
    defbuiltin("length",b_length);
    defbuiltin("edit",b_nano);
    defbuiltin("reverse",b_reverse);
    defbuiltin("name",b_atom_codes);
    defbuiltin("delete",b_delete);
    defbuiltin("ansi_cuu",b_ansi_cuu);
    defbuiltin("ansi_cud",b_ansi_cud);
    defbuiltin("ansi_cuf",b_ansi_cuf);
    defbuiltin("ansi_cub",b_ansi_cub);
    defbuiltin("ifthen",b_ifthen);
    defbuiltin("ifthenelse",b_ifthenelse);
    defbuiltin("concat",b_concat);
    defbuiltin("string_length",b_string_length);
    defbuiltin("substring",b_substring);

    defcompiled("call",b_call);
    defcompiled("repeat",b_repeat);
    defcompiled("append",b_append);
    defcompiled("member",b_member);
    defcompiled("retract",b_retract);
    defcompiled("clause",b_clause);
    defcompiled("current_predicate",b_current_predicate);
    defcompiled("current_op",b_current_op);
    defcompiled("between",b_between);
    return;
}

int b_length(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(integerp(eval(arg2)) && GET_INT(eval(arg2)) < 0)
            error(NOT_LESS_THAN_ZERO,"length ",arg2);
        if(!wide_variable_p(arg2) && !integerp(eval(arg2)))
            error(NOT_INT,"length ",arg2);
        if(wide_variable_p(arg1) && wide_variable_p(arg2) && eqp(arg1,arg2))
            error(RESOURCE_ERR,"length ",arg1);

        if(unify(arg2,makeint(length(arg1))) == YES)
            return(YES);

        return(NO);
    }
    return(NO);
}


//compiled predicate
int b_repeat(int arglist, int rest){
    int n,save1;

    save1 = sp;
    n = length(arglist);
    if(n == 0){
        loop:
        if(prove_all(rest,sp,0) == YES){
            return(YES);
        }
    unbind(save1);
    goto loop;
    }
    return(NO);
}


int b_op(int arglist, int rest){
    int n,arg1,arg2,arg3,weight,type;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));   //priority
        arg2 = deref(cadr(arglist));  //specifier
        arg3 = deref(caddr(arglist)); //operator

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"op ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"op ",arg2);
        if(listp(arg3) && length(arg3) == -1)
            error(INSTANTATION_ERR,"op ",arg3);
        if(!integerp(arg1))
            error(NOT_INT,"op ",arg1);
        if(!atomp(arg2))
            error(NOT_ATOM,"op ",arg2);
        if(!atomp(arg3) && !listp(arg3))
            error(NOT_ATOM,"op ",arg3);
        weight = GET_INT(arg1);
        if(!(weight >= 0 && weight <= 1200))
            error(OPE_PRIORITY_ERR,"op ",arg1);
        if(arg3 == DOTOBJ)
            error(MODIFY_OPE_ERR,"op ",arg3);
        if(arg3 == AND)
            error(MODIFY_OPE_ERR,"op ",arg3);
        if(arg3 == makeatom("op",OPE))
            error(MODIFY_OPE_ERR,"op ",arg3);

        type = NIL;
        if(arg2 == makeconst("xfx")){
            type = XFX;

        }
        else if(arg2 == makeconst("yfx")){
            if(GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
                error(OPE_SPEC_ERR,"op",arg2);
            type = YFX;
        }
        else if(arg2 == makeconst("xfy")){
            if(GET_OPT(arg3) == XF || GET_OPT(arg3) == YF)
                error(OPE_SPEC_ERR,"op",arg2);
            type = XFY;
        }
        else if(arg2 == makeconst("fx"))
            type = FX;
        else if(arg2 == makeconst("fy"))
            type = FY;
        else if(arg2 == makeconst("xf")){
            if(GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
               GET_OPT(arg3) == XFY)
                error(OPE_SPEC_ERR,"op",arg2);
            type = XF;
        }
        else if(arg2 == makeconst("yf")){
            if(GET_OPT(arg3) == XFX || GET_OPT(arg3) == YFX ||
               GET_OPT(arg3) == XFY)
                error(OPE_SPEC_ERR,"op",arg2);
            type = YF;
        }
        else
            error(OPE_SPEC_ERR,"op",arg2);

        if(singlep(arg3)){
            if(operatorp(arg3))
                defoperator(GET_NAME(arg3),NIL,weight,type,0);
            else if(builtinp(arg3))
                defoperator(GET_NAME(arg3),NIL,weight,type,1);
            else
                defoperator(GET_NAME(arg3),NIL,weight,type,2);
        }
        else{
            while(!nullp(arg3)){
                if(wide_variable_p(car(arg3)))
                    error(INSTANTATION_ERR,"ope ",car(arg3));
                else if(!atomp(car(arg3)))
                    error(NOT_ATOM,"ope ",car(arg3));
                else if(operatorp(car(arg3)))
                    defoperator(GET_NAME(arg3),NIL,weight,type,0);
                else
                    defoperator(GET_NAME(car(arg3)),NIL,weight,type,1);

                arg3 = cdr(arg3);
            }
        }
        return(YES);
    }
    return(NO);
}


int o_cons(int x, int y){
    if(operationp(y))
        y = operate(y);
    return(cons(x,y));
}

int b_ask(int arglist, int rest){
    int n,x1,x2;
    char c;

    n = length(arglist);
    if(n == 0){
        x1 = variables;
        if(nullp(x1) || has_no_value_p(x1)){
            return(YES);
        }
        // ignore singleton e.g. X=X
        x2 = NIL;
        while(!nullp(x1)){
            if(variablep(car(x1)) && deref(car(x1)) != car(x1))
                x2 = cons(car(x1),x2);
            x1 = cdr(x1);
        }
        x2 = reverse(x2);
        while(!nullp(x2)){
            print(car(x2));
            printf(" = ");
            printanswer(deref(car(x2)));
            if(!nullp(cdr(x2)))
                printf("\n");
            x2 = cdr(x2);
        }

        fflush(stdout);
        fflush(stdin);

        loop:
        c = getchar();
        
        if(c == '.'){
        	getchar();
            return(YES);
        }
        else if(c == EOL){
            return(YES);
        }
        else if(c == ';'){
        	getchar();
            return(NO);
        }
        else
            goto loop;
    }
    return(NO);
}


int b_unify(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(operationp(arg1) && car(arg1) == DOTOBJ)
            arg1 = operate(arg1);
        if(operationp(arg2) && car(arg2) == DOTOBJ)
            arg2 = operate(arg2);
        res = unify(arg1,arg2);
        return(res);
    }
    return(NO);
}

int b_notunify(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(operationp(arg1))
            arg1 = operate(arg1);
        if(operationp(arg2))
            arg2 = operate(arg2);
        res = unify(arg1,arg2);
        if(res == NO)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}




//input and output
int b_write(int arglist, int rest){
    int n,arg1,arg2,save;

    n = length(arglist);
    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(car(arglist));
        goto write;

    }
    else if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        write:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"write ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"write ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 0;
        print(arg2);
        fflush(GET_PORT(output_stream));
        quoted_flag = 1;
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_write_canonical(int arglist, int rest){
    int n,arg1,arg2,save;

    n = length(arglist);
    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(car(arglist));
        goto write_canonical;

    }
    else if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        write_canonical:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"write_canonical ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"write_canonical ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 1;
        ignore_flag = 1;
        print(arg2);
        quoted_flag = 0;
        ignore_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_writeq(int arglist, int rest){
    int n,arg1,arg2,save;

    n = length(arglist);
    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(car(arglist));
        goto writeq;

    }
    else if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        writeq:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"writeq ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"writeq ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 1;
        print(arg2);
        quoted_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}


int b_nl(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        fprintf(GET_PORT(output_stream),"\n");
        fflush(GET_PORT(output_stream));
        return(YES);
    }
    
    return(NO);
}

int b_put(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(!integerp(arg1))
            error(NOT_INT,"put",arg1);
        fprintf(GET_PORT(output_stream), "%c", (char)GET_INT(arg1));
        return(YES);
    }
    return(NO);
}

int b_get0(int arglist, int rest){
    int n,c,arg1,i,res;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        c = getc(GET_PORT(input_stream));
        if(c == EOL){
            c = getc(GET_PORT(input_stream));
        }
        i = makeint((int)c);
        res = unify(arg1,i);
        return(res);
    }
    return(NO);
}

int b_get(int arglist, int rest){
    int n,c,arg1,i,res;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        loop:
        c = getc(GET_PORT(input_stream));
        if(c == EOL)
            c = getc(GET_PORT(input_stream));
        i = (int)c;
        if(c == EOL)
            goto exit;
        if(i < 32)
            goto loop;

        exit:
        res = unify(arg1,makeint(i));
        return(res);
    }
    return(NO);
}



int b_get_code(int arglist, int rest){
    int n,arg1,arg2,c,i,res;
    char str[10];

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(car(arglist));
        goto get_code;
    }
    else if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        get_code:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_code ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"get_code ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_code ",arg1);

        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        c = getc(GET_PORT(arg1));

        if(mode_flag == 0 && iskanji(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = NUL;
            i = sjis_to_code(str);
        }
        else if(mode_flag == 1 && isUni2(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni3(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni4(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = getc(GET_PORT(arg1));
            str[4] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni5(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = getc(GET_PORT(arg1));
            str[4] = getc(GET_PORT(arg1));
            str[5] = NUL;
            i = utf8_to_ucs4(str);
        }
        else if(mode_flag == 1 && isUni6(c)){
            str[0] = c;
            str[1] = getc(GET_PORT(arg1));
            str[2] = getc(GET_PORT(arg1));
            str[3] = getc(GET_PORT(arg1));
            str[4] = getc(GET_PORT(arg1));
            str[5] = getc(GET_PORT(arg1));
            str[6] = NUL;
            i = utf8_to_ucs4(str);
        }
        else{
            i = c;
        }

        res = NIL;
        
        res = unify(arg2,makeint(i));
        return(res);
    }
    return(NO);
}

int b_get_byte(int arglist, int rest){
    int n,arg1,arg2,c,res;

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(car(arglist));
        goto get_byte;
    }
    else if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        get_byte:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_byte ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"get_byte ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_byte ",arg1);

        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        c = fgetc(GET_PORT(arg1));

        res = unify(arg2,makeint(c));
        return(res);
    }
    return(NO);
}


int b_tab(int arglist, int rest){
    int n,arg1,count;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(integerp(eval(arg1)) && GET_INT(eval(arg1)) < 0)
            error(NOT_LESS_THAN_ZERO,"tab",arg1);
        if(!integerp(arg1))
            error(NOT_INT,"tab",arg1);

        count = GET_INT(arg1);
        while(count > 0){
            fprintf(GET_PORT(output_stream)," ");
            count--;
        }
        return(YES);
    }
    return(NO);
}


//option for read_term [variable_names(X)]
int variable_name_p(int x){

    if(eqlp(car(x),makeconst("variable_names")) &&
       (wide_variable_p(cadr(x)) || listp(cadr(x))) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}

//option for read_term [singletons(X)]
int singletonp(int x){

    if(eqlp(car(x),makeconst("singletons")) &&
       wide_variable_p(cadr(x)) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}



int b_read(int arglist, int rest){
    int n,arg1,arg2,save,temp,res;

    n = length(arglist);
    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(car(arglist));
        goto read;

    }
    else if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        read:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"read ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"read",arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"read ", arg1);
        save = input_stream;
        if(aliasp(arg1))
            input_stream = GET_CAR(arg1);
        else
            input_stream = arg1;

        temp = variable_to_call(readparse());
        if(temp == FEND){
            temp = GET_AUX(input_stream);
        }
        res = unify(arg2,temp);
        input_stream = save;
        return(res);
    }
    return(NO);
}




int b_open(int nest, int n){
    
    return(NO);
}



int b_close(int nest, int n){
    
    return(NO);
}


int b_see(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"see ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"see ",arg1);

        if(eqp(arg1,makeconst("user"))){
            input_stream = standard_input;
            return(YES);
        }
        else{
            input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

            if(GET_PORT(input_stream) == NULL)
                error(CANT_OPEN, "see", arg1);
            return(YES);
        }
    }
    return(NO);
}

int b_seen(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        if(input_stream != standard_input){
            fclose(GET_PORT(input_stream));
            input_stream = standard_input;
        }
        return(YES);
    }
    return(NO);
}

int b_tell(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"tell ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"tell ",arg1);

        if(eqp(arg1,makeconst("user"))){
            output_stream = standard_output;
            return(YES);
        }
        else{
            output_stream = makestream(fopen(GET_NAME(arg1),"w"),OPL_OUTPUT,OPL_TEXT,NIL,arg1);

            if(GET_PORT(input_stream) == NULL)
                error(CANT_OPEN, "tell", arg1);
            return(YES);
        }
    }
    return(NO);
}

int b_told(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        if(output_stream != standard_output){
            fclose(GET_PORT(output_stream));
            output_stream = standard_output;
        }
        return(YES);
    }
    return(NO);
}


int b_flush_output(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 0){
        fflush(stdout);
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"flush_output ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"flush_output ",arg1);
        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        if(GET_OPT(arg1) == OPL_INPUT)
            error(NOT_OUTPUT_STREAM,"flush_output ",arg1);

        fflush(GET_PORT(arg1));
        return(YES);
    }
    return(NO);
}


int b_consult(int arglist, int rest){
    int n,arg1,clause,save;
    char str[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"consult ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM, "consult ",arg1);

        save = input_stream;
        input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

        if(GET_PORT(input_stream) == NULL)
            error(CANT_OPEN, "consult", arg1);

        //object file ex "foo.o"
        n = strlen(GET_NAME(arg1));
        strcpy(str,GET_NAME(arg1));
        if(str[n-1] == 'o' && str[n-2] == '.'){
            dynamic_link(arg1);
            input_stream = save;
            goto exit;
        }

        open_flag = 1;
        line = 1;
        column = 0;
        reconsult_list = NIL;
        while(1){
            skip:
            clause = parser(NIL,NIL,NIL,NIL,0,0);
            if(clause == FEND)
                break;

            //e.g. :- op(...)
            if(operationp(clause) && car(clause) == DEFINE && length(clause) == 2){
                operate(clause);
                goto skip;
            }
            // DCG syntax e.g. a-->b.
            if(dcgp(clause)){
                operate(clause);
                goto skip;
            }

            //assert
            b_assert(list1(clause),NIL);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;

        exit:
        return(YES);
    }
    return(NO);
}


int b_reconsult(int arglist, int rest){
    int n,arg1,clause,head,atom,save;
    char str[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"reconsult ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM, "reconsult ", arg1);

        save = input_stream;
        input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

        if(GET_PORT(input_stream) == NULL)
            error(CANT_OPEN, "reconsult", arg1);

        //object file ex "foo.o"
        n = strlen(GET_NAME(arg1));
        strcpy(str,GET_NAME(arg1));
        if(str[n-1] == 'o' && str[n-2] == '.'){
            dynamic_link(arg1);
            input_stream = save;
            goto exit;
        }

        open_flag = 1;
        line = 1;
        column = 0;
        reconsult_list = NIL;
        while(1){
            skip:
            clause = parser(NIL,NIL,NIL,NIL,0,0);
            if(clause == FEND)
                break;
            
            //e.g. :- op(...)
            if(operationp(clause) && car(clause) == DEFINE && length(clause) == 2){
                operate(clause);
                goto skip;
            }
            // DCG syntax e.g. a-->b.
            if(dcgp(clause)){
                operate(clause);
                goto skip;
            }

            //delete old definition
            if(predicatep(clause)){
                if(atomp(clause))
                    atom  = clause;
                else
                    atom = car(clause);
            }
            else{
                head = cadr(clause);
                if(atomp(head))
                    atom = head;
                else
                    atom = car(head);
            }
            if(!memberp(atom,reconsult_list)){
                reconsult_list = cons(atom,reconsult_list);
                SET_CAR(atom,NIL);
            }

            //assert
            b_assert(list1(clause),NIL);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;

        exit:
        return(YES);
    }
    return(NO);
}

/*
X)->foo, foo(X) :- bar(X)->foo
 set CDR part of atom the arity. e.g. cdr(atom) = #[2,3]
*/
void memoize_arity(int clause, int atom){
    if(predicatep(clause)){
        if(atomp(clause) && !memq(makeint(0),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(0),GET_ARITY(atom)));
        }
        else if(!atomp(clause) && !memq(makeint(length(cdr(clause))),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(length(cdr(clause))),GET_ARITY(atom)));
        }
    }
    else{
        if(atomp(cadr(clause)) &&
           !memq(makeint(0),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(0),GET_ARITY(atom)));
        }
        else if(!atomp(cadr(clause)) &&
                !memq(makeint(length(cdr(cadr(clause)))),GET_ARITY(atom))){
            SET_ARITY(atom,cons(makeint(length(cdr(cadr(clause)))),GET_ARITY(atom)));
        }
    }
}


//arithmetic operation

int b_is(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"is ", arg2);

        arg2 = eval(arg2);
        res = unify(arg1,arg2);
        return(res);
    }
    return(NO);
}


int b_greater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"> ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"> ",arg2);


        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,"> ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"> ",arg2);

        if(greaterp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_smaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"< ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"< ",arg2);


        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,"< ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"< ",arg2);
        if(smallerp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_eqsmaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"=< ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"=< ",arg2);

        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,"=< ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"=< ",arg2);
        if(eqsmallerp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_eqgreater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,">= ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,">= ",arg2);

        arg1 = eval(arg1);
        arg2 = eval(arg2);
        if(!numberp(arg1))
            error(NOT_NUM,">= ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,">= ",arg2);
        if(eqgreaterp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_numeq(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = eval(car(arglist));
        arg2 = eval(cadr(arglist));
        if(!numberp(arg1))
            error(NOT_NUM,"=:= ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"=:= ",arg2);

        if(numeqp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_notnumeq(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = eval(car(arglist));
        arg2 = eval(cadr(arglist));
        if(!numberp(arg1))
            error(NOT_NUM,"=:= ",arg1);
        if(!numberp(arg2))
            error(NOT_NUM,"=:= ",arg2);

        if(!numeqp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_equalp(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(anoymousp(arg1) && anoymousp(arg2))
            return(NO);
        else if(equalp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_notequalp(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(anoymousp(arg1) && anoymousp(arg2))
            return(YES);
        else if(!equalp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_compare(int arglist, int rest){
    int n,arg1,arg2,arg3;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"compare ",arg1);
        if(!wide_variable_p(arg1) &&
          !(eqp(arg1,makeatom("<",SYS)) ||
            eqp(arg1,makeatom("=",SYS)) ||
            eqp(arg1,makeatom(">",SYS))))
            error(NOT_ORDER,"compare ",arg1);

        if(equalp(arg2,arg3))
            return(unify(arg1,makeatom("=",SYS)));
        else if(atsmaller(arg2,arg3))
            return(unify(arg1,makeatom("<",SYS)));
        else if(atsmaller(arg3,arg2))
            return(unify(arg1,makeatom(">",SYS)));

    }
    return(NO);
}

int b_atsmaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(atsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@< ", makeint(n));
    return(NO);
}

int atsmaller(int x, int y){

    if(nullp(x))
        return(0);
    else if(variablep(x) || variablep(y))
        return(1);
    else if(atomp(x) && atomp(y)){
        if(strcmp(GET_NAME(x),GET_NAME(y)) < 0)
            return(1);
        else
            return(0);
    }
    else if(floatp(x) && floatp(y)){
        if(GET_FLT(x) < GET_FLT(y))
            return(1);
        else
            return(0);
    }
    else if(wide_integer_p(x) && wide_integer_p(y)){
        if(smallerp(x,y))
            return(1);
        else
            return(0);
    }
    else if(structurep(x) && structurep(y)){
        if(length(x) < length(y))
            return(1);
        else if(length(x) > length(y))
            return(0);
        else if(atsmaller(car(x),car(y)))
            return(1);
        else if(equalp(car(x),car(y)))
            return(atsmaller(cdr(x),cdr(y)));
        else
            return(0);
    }
    else if(floatp(x))
       return(1);
    else if(wide_integer_p(x) && atomp(y))
        return(1);
    else if(wide_integer_p(x) && structurep(y))
        return(1);
    else if(atomp(x) && structurep(y))
        return(1);
    else
        return(0);
}

int ateqsmaller(int x, int y){

    if(nullp(x))
        return(0);
    else if(variablep(x) || variablep(y))
        return(1);
    else if(atomp(x) && atomp(y)){
        if(strcmp(GET_NAME(x),GET_NAME(y)) <= 0)
            return(1);
        else
            return(0);
    }
    else if(floatp(x) && floatp(y)){
        if(GET_FLT(x) <= GET_FLT(y))
            return(1);
        else
            return(0);
    }
    else if(wide_integer_p(x) && wide_integer_p(y)){
        if(eqsmallerp(x,y))
            return(1);
        else
            return(0);
    }
    else if(structurep(x) && structurep(y)){
        if(length(x) < length(y))
            return(1);
        else if(length(x) > length(y))
            return(0);
        else if(ateqsmaller(car(x),car(y)))
            return(1);
        else if(equalp(car(x),car(y)))
            return(ateqsmaller(cdr(x),cdr(y)));
        else
            return(0);
    }
    else if(floatp(x))
       return(1);
    else if(wide_integer_p(x) && atomp(y))
        return(1);
    else if(wide_integer_p(x) && structurep(y))
        return(1);
    else if(atomp(x) && structurep(y))
        return(1);
    else
        return(0);
}


int b_ateqsmaller(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(ateqsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@=< ", makeint(n));
    return(NO);
}



int b_atgreater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(!ateqsmaller(arg1,arg2))
            return(NO);
        else
            return(YES);
    }
    error(UNDEF_PRED,"@> ", makeint(n));
    return(NO);
}


int b_ateqgreater(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(atsmaller(arg1,arg2))
            return(NO);
        else
            return(YES);
    }
    error(UNDEF_PRED,"@>= ", makeint(n));
    return(NO);
}


//true fail
int b_fail(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        return(NO);
    }
    return(NO);
}

int b_call(int arglist, int rest){
    int n,arg1,res;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"call ",arg1);

        if(!callablep(arg1))
            error(NOT_CALLABLE,"call ",arg1);
        
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"call ",arg1);

        res = prove_all(addtail_body(rest,arg1),sp,n);
        return(res);
    }
    
    return(NO);
}

int b_not(int arglist, int rest){
    int n,arg1,res;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"not ",arg1);
        if(!callablep(arg1))
            error(NOT_CALLABLE,"not ", arg1);

        res = prove(arg1,sp,rest,0);
        if(res == YES)
            return(NO);
        else
            return(YES);
    }
    return(NO);
}

int b_true(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        return(YES);
    }
    return(NO);
}


//database operation
int b_assert(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"assertz",arg1);
        if(singlep(arg1)){
            if(GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
                SET_AUX(arg1,PRED);
            arg1 = list1(arg1);
        }
        if(builtinp(arg1))
            error(BUILTIN_EXIST,"assertz",arg1);

        arg1 = variable_to_call(arg1); //P -> call(P)
        arg1 = copy_heap(arg1); //copy arg1 to heap area
        if(predicatep(arg1)){
            SET_VAR(arg1,unique(varslist(arg1)));
            add_data(car(arg1),arg1);
            checkgbc();
            return(YES);
        }
        else if(operationp(arg1)){
            if(!callablep(caddr(arg1)))
                error(NOT_CALLABLE,"assertz ",arg1);
            
            SET_VAR(arg1,unique(varslist(arg1)));
            operate(arg1);
            checkgbc();
            return(YES);
        }
        error(NOT_CALLABLE,"assertz",arg1);
    }
    return(NO);
}

int b_asserta(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"asserta",arg1);
        if(singlep(arg1)){
            if(GET_AUX(arg1) == SIMP || GET_AUX(arg1) == NIL)
                SET_AUX(arg1,PRED);
            arg1 = list1(arg1);
        }
        if(builtinp(arg1))
            error(BUILTIN_EXIST,"asserta",arg1);

        arg1 = variable_to_call(arg1); //P -> call(P)
        arg1 = copy_heap(arg1); //copy arg1 to heap area
        if(predicatep(arg1)){
            SET_VAR(arg1,unique(varslist(arg1)));
            insert_data(car(arg1),arg1);
            checkgbc();
            return(YES);
        }
        else if(operationp(arg1)){
            if(!callablep(caddr(arg1)))
                error(NOT_CALLABLE,"asserta ",arg1);

            SET_VAR(arg1,unique(varslist(arg1)));
            operate(arg1);
            assert_flag = 0;
            checkgbc();
            return(YES);
        }
        error(NOT_CALLABLE,"asserta",arg1);
    }
    return(NO);
}

int b_retract(int arglist, int rest){
    int n,arg1,clause,head,clauses,new_clauses,save1,save2;

    save2 = sp;
    clause = clauses = head = NIL;
    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"retract ",arg1);
        if(operationp(arg1) && !predicatep(cadr(arg1)))
            error(NOT_CALLABLE,"retract ",arg1);
        if(!operationp(arg1) && !predicatep(arg1))
            error(NOT_CALLABLE,"retract ",arg1);
        if(operationp(arg1) && builtinp(cadr(arg1)))
            error(BUILTIN_EXIST,"retract ",arg1);
        if(!operationp(arg1) && builtinp(arg1))
            error(BUILTIN_EXIST,"retract ",arg1);

        if(singlep(arg1)){
            arg1 = list1(arg1);
        }
        if(atom_predicate_p(arg1))
            clauses = GET_CAR(arg1);
        else if(predicatep(arg1))
            clauses = GET_CAR(car(arg1));
        else if(clausep(arg1) && atom_predicate_p(cadr(arg1)))
            clauses = GET_CAR(cadr(arg1));
        else if(clausep(arg1))
            clauses = GET_CAR(car(cadr(arg1)));

        new_clauses = NIL;
        save1 = wp;
        while(!nullp(clauses)){
            clause = car(clauses);
            clauses = cdr(clauses);

            if(unify(arg1,clause) == YES){
                if(atom_predicate_p(arg1))
                    SET_CAR(clause,append(listreverse(new_clauses),clauses));
                else if(predicatep(arg1))
                    SET_CAR(car(arg1),append(listreverse(new_clauses),clauses));
                else if(clausep(arg1) && atom_predicate_p(cadr(arg1)))
                    SET_CAR(cadr(arg1),append(listreverse(new_clauses),clauses));
                else if(clausep(arg1))
                    SET_CAR(car(cadr(arg1)),append(listreverse(new_clauses),clauses));

                //if(proceed(NIL,nest) == YES)
                //    return(YES);
                //else
                //    goto next;
            }
            new_clauses = cons(clause,new_clauses);
            
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        sp = save2;
        return(NO);
    }
    return(NO);
}


int b_abolish(int arglist, int rest){
    int n,arg1,pred,clause,arity,clauses,new_clauses;

    clause = clauses = NIL;
    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"abolish ",arg1);
        if(structurep(arg1) &&
           (wide_variable_p(cadr(arg1)) ||
            wide_variable_p(caddr(arg1))))
            error(INSTANTATION_ERR,"abolish ",arg1);
        if(car(arg1) != makeatom("/",OPE))
            error(PRED_INDICATOR,"abolish ",arg1);
        if(builtinp(cadr(arg1)))
            error(STATIC_PROCEDURE,"abolish ",arg1);
        if(!atomp(cadr(arg1)))
            error(NOT_ATOM,"abolish ",arg1);
        if(integerp(eval(caddr(arg1))) && GET_INT(eval(caddr(arg1))) < 0)
            error(NOT_LESS_THAN_ZERO,"abolish ",arg1);
        if(!integerp(caddr(arg1)))
            error(NOT_INT,"abolish ",arg1);

        pred = makepred(GET_NAME(cadr(arg1)));
        clauses = GET_CAR(pred);
        arity = GET_INT(caddr(arg1));

        new_clauses = NIL;
        while(!nullp(clauses)){
            clause = car(clauses);

            if(atom_predicate_p(clause) && arity == 0)
                goto abolish;
            else if(predicatep(clause) && length(clause)-1 == arity)
                goto abolish;
            else if(clausep(clause) && atom_predicate_p(cadr(clause)) &&
                    arity == 0)
                goto abolish;
            else if(clausep(clause) && length(cadr(clause))-1 == arity)
                goto abolish;

            new_clauses = cons(clause,new_clauses);

            abolish:
            clauses = cdr(clauses);
        }
        SET_CAR(pred,listreverse(new_clauses));
        if(nullp(new_clauses))
            listremove(cadr(arg1),predicates);
        return(YES);
    }
    return(NO);
}

int b_clause(int arglist, int rest){
    int n,arg1,arg2,save2;

    save2 = sp;
    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));  //head
        arg2 = deref(cadr(arglist)); //body

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"clause ",arg1);
        if(!atom_predicate_p(arg1) && !predicatep(arg1))
            error(NOT_CALLABLE,"clause ",arg1);
        if(builtinp(arg1) || compiledp(arg1))
            error(BUILTIN_EXIST,"clause ",arg1);
        if(!wide_variable_p(arg2) && !callablep(arg2))
            error(NOT_CALLABLE,"clause ",arg2);

    
        unbind(save2);
        return(NO);
    }
    return(NO);
}

//transform
int b_atom_codes(int arglist, int rest){
    int n,arg1,arg2,ls,atom,pos,code,res;
    char str1[STRSIZE],str2[10];

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        if(wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
            error(INSTANTATION_ERR,"atom_codes ",arg1);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"atom_codes ",arg1);
        if(wide_variable_p(arg1) && !listp(arg2))
            error(NOT_LIST,"atom_codes ",arg2);
        if(wide_variable_p(arg1) && !atom_codes_list_p(arg2))
            error(NOT_CHAR_CODE,"atom_codes ",arg2);


        if(singlep(arg1) && !variablep(arg1)){
            strcpy(str1,GET_NAME(arg1));
            ls = NIL;
            pos = 0;
            while(str1[pos] != NUL){
                if(str1[pos] == '\\'){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                }
                else if(mode_flag == 0 && iskanji(str1[pos])){ //SJIS
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = NUL;
                }
                else if(mode_flag == 1 && isUni2(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = NUL;
                }
                else if(mode_flag == 1 && isUni3(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = NUL;
                }
                else if(mode_flag == 1 && isUni4(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = NUL;
                }
                else if(mode_flag == 1 && isUni5(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = str1[pos++];
                    str2[5] = NUL;
                }
                else if(mode_flag == 1 && isUni6(str1[pos])){
                    str2[0] = str1[pos++];
                    str2[1] = str1[pos++];
                    str2[2] = str1[pos++];
                    str2[3] = str1[pos++];
                    str2[4] = str1[pos++];
                    str2[5] = str1[pos++];
                    str2[6] = NUL;
                }
                else{//ascii code
                    str2[0] = str1[pos++];
                    str2[1] = NUL;
                }
                if(str2[0] == '\\')
                    code = ctrl_to_number(str2[1]);
                else if(mode_flag == 0) //SJIS
                    code = makeint(sjis_to_code(str2));
                else //unicode
                    code = makeint(utf8_to_ucs4(str2));
                ls = cons(code,ls);
            }
            ls = listreverse(ls);
            res = unify(arg2,ls);
            return(res);
        }
        else if(structurep(arg2)){
            ls = arg2;
            str1[0] = NUL;
            while(!nullp(ls)){
                if(GET_INT(car(ls)) < ' ')
                    sprintf(str2,"\\x%x\\",GET_INT(car(ls)));
                else if(mode_flag == 0)
                    sjis_to_char(GET_INT(car(ls)),str2);
                else
                    ucs4_to_utf8(GET_INT(car(ls)),str2);
                strcat(str1,str2);
                ls = cdr(ls);
            }
            atom = makeconst(str1);
            res = unify(arg1,atom);
            return(res);
        }
        else
            return(NO);
    }
    return(NO);
}

//----------string transform-------------------

int b_concat(int arglist, int rest){
    int n,arg1,arg2,arg3,str;
    char str1[STRSIZE];

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));;
        arg3 = deref(caddr(arglist));
        
        if(!wide_variable_p(arg1) && !(atomp(arg1) || stringp(arg1)))
            error(NOT_STR,"concat ",arg1);
        if(!wide_variable_p(arg2) && !(atomp(arg2) || stringp(arg2)))
            error(NOT_STR,"concat ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"concat ", arg3);
    
        strcpy(str1,GET_NAME(arg1));
        strcat(str1,GET_NAME(arg2));
        str = makestr(str1);

        unify(arg3,str);
        return(YES);

    }
    return(NO);
}

int b_string_length(int arglist, int rest){
    int n,arg1,arg2,val;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"string_length ",arg1);
        if(!stringp(arg1))
            error(NOT_STR,"string_length ",arg1);
        if(integerp(eval(arg2)) && GET_INT(eval(arg2)) < 0)
            error(NOT_LESS_THAN_ZERO,"string_length ",arg2);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"string_length ", arg2);

        val = makeint(string_length(arg1));
        return(unify(arg2,val));
    }
    return(NO);
}

int b_substring(int arglist, int rest){
    int n,arg1,arg2,arg3,arg4,i,j,k,start,len,str;
    char str1[STRSIZE],str2[STRSIZE];

    n = length(arglist);
    if(n == 4){
        arg1 = deref(car(arglist));   //instring
        arg2 = deref(cadr(arglist));  //start
        arg3 = deref(caddr(arglist)); //length
        arg4 = deref(cadddr(arglist));//outstring

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"substring ",arg1);
        if(!stringp(arg1))
            error(NOT_STR,"substring ",arg1);
        if(!wide_variable_p(arg4) && !stringp(arg4))
            error(NOT_STR,"substring ",arg4);
        if(integerp(arg2) && GET_INT(arg2) < 0)
            error(NOT_LESS_THAN_ZERO,"substring ",arg2);
        if(integerp(arg3) && GET_INT(arg3) < 0)
            error(NOT_LESS_THAN_ZERO,"substring ",arg3);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"substring ",arg2);
        if(!wide_variable_p(arg3) && !wide_integer_p(arg3))
            error(NOT_INT,"substring ",arg3);
        


        strcpy(str1,GET_NAME(arg1));
        start = GET_INT(arg2);
        len   = GET_INT(arg3);
        if(string_length(arg1) < start+len-1)
            error(OUT_OF_RANGE,"substring ", list2(arg2,arg3));
        i= 0;
        j = start - 1;
        k = start + len - 1;
        memset(str2, '\0' ,STRSIZE);
         while(j < k){
            str2[i] = str1[j];
            i++;
            j++;
        }
        str = makestr(str2);
        return(unify(arg4,str));
    }
    return(NO);
}


//controle
int b_cut(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        return(YES);
    }
    return(NO);
}

int b_ifthen(int arglist, int rest){
    int n,arg1,arg2,save1;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        save1 = sp;
        if(variablep(arg1))
            error(INSTANTATION_ERR,"ifthen ",arg1);
        if(variablep(arg2))
            error(INSTANTATION_ERR,"ifthen ",arg2);

        if(prove_all(arg1,sp,0) == YES){
            return(prove_all(addtail_body(rest,arg2),sp,0));
        }
        else{
            unbind(save1);
            return(NO);
        }
            
        unbind(save1);
        return(NO);
    }
    return(NO);
}

int b_ifthenelse(int arglist, int rest){
    int n,arg1,arg2,arg3;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));
        
        if(variablep(arg1))
            error(INSTANTATION_ERR,"ifthenelse ",arg1);
        if(variablep(arg2))
            error(INSTANTATION_ERR,"ifthenelse ",arg2);
        if(variablep(arg3))
            error(INSTANTATION_ERR,"ifthenelse ",arg3);    

        if(prove_all(arg1,sp,0) == YES){
            if(prove_all(arg2,sp,0) == YES)
                return(prove_all(rest,sp,0));
        }
        else{
            if(prove_all(arg3,sp,0) == YES)
                return(prove_all(rest,sp,0));
        }
    }
    return(NO);
}



int b_colon(int nest, int n){
    return(YES);
}



double getETime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec*1e-6;
}

int b_measure(int arglist, int rest){
    int n,arg1,res;
    double start_time,end_time;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        start_time = getETime(); //time_flag on and it store start time
        res = prove_all(arg1,sp,0);
        end_time = getETime();
        printf("Elapsed Time=%.6f (second)\n", end_time - start_time);
        return(res);
    }
    return(NO);
}


int b_trace(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        debug_flag = ON;
        return(YES);
    }
    return(NO);
}

int b_notrace(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        debug_flag = OFF;
        return(YES);
    }
    return(NO);
}

int b_spy(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 0){
        print(spy_list);
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(car(arglist));
        arg1 = copy_heap(arg1);
    
        if(!memberp(arg1,spy_list))
            spy_list = cons(arg1,spy_list);
        return(YES);
    }
    return(NO);
}

int b_nospy(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 0){
        while(!nullp(spy_list)){
            spy_list = cdr(spy_list);
        }
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(car(arglist));
        arg1 = copy_heap(arg1);
        spy_list = listremove(arg1,spy_list);
        return(YES);
    }
    return(NO);
}

int b_leash(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = car(arglist);
        if(arg1 == makeatom("full",SIMP)){
            trace_flag = FULL;
            return(YES);
        }
        else if(arg1 == makeatom("tight",SIMP)){
            trace_flag = TIGHT;
            return(YES);
        }
        else if(arg1 == makeatom("half",SIMP)){
            trace_flag = HALF;
            return(YES);
        }
        else if(arg1 == makeatom("off",SIMP)){
            trace_flag = OFF;
            return(YES);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_debug(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        printf("debug_flag=%d\n", debug_flag);
        printf("trace_flag=%d\n", trace_flag);
        printf("spy_list=");
        print(spy_list);
        printf("\n");
        return(YES);
    }
    return(NO);
}

int b_halt(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        printf("- good bye -\n");
        longjmp(buf,2);
    }
    return(NO);
}

int b_abort(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        longjmp(buf,1);
    }
    return(NO);
}


//check data type
int b_atom(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(atomp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_integer(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(integerp(arg1) || longnump(arg1) || bignump(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_real(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(floatp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_number(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(numberp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}


int b_compound(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(compoundp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_ground(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(groundp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_system(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(builtinp(arg1))
            return(YES);
        else
            return(NO);   
    }
    return(NO);
}

int b_var(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(variablep(arg1))
            return(YES);
        else if(anoymousp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_nonvar(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(variablep(arg1))
            return(NO);
        else if(anoymousp(arg1))
            return(NO);
        else
            return(YES);
    }
    return(NO);
}

int b_atomic(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(atomicp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_list(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(listp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_string(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));

        if(stringp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}



//-----structure------
int b_functor(int arglist, int rest){
    int n,arg1,arg2,arg3,res,i;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));

        // to avoid compier bug {}
        if(structurep(arg2) && car(arg2) == CURL && length(arg2) == 1)
            arg2 = CURL;

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"functor ", list2(arg1,arg2));
        if(wide_variable_p(arg1) && wide_variable_p(arg3))
            error(INSTANTATION_ERR,"functor ", list2(arg1,arg3));
        if(wide_variable_p(arg1) && !atomicp(arg2)){
            error(NOT_ATOMIC,"functor ", arg2);}
        if(wide_variable_p(arg1) && integerp(eval(arg3)) && GET_INT(eval(arg3)) < 0)
            error(NOT_LESS_THAN_ZERO,"functor ", arg3);
        if(wide_variable_p(arg1) && !integerp(arg3))
            error(NOT_INT, "functor ", arg3);
        if(wide_variable_p(arg1) && atomicp(arg2) &&
           !atomp(arg2) && integerp(arg3) && GET_INT(arg3) > 0)
            error(NOT_ATOM,"functor ", arg2);


        if(listp(arg1) &&
                 constantp(arg2) && integerp(arg3)){
            i = GET_INT(arg3);
            if(i == 0)
                return(unify(arg1,arg2));
            else{
                res = NIL;
                while(i > 0){
                    res = cons(makevariant(),res);
                    i--;
                }
                res = listreverse(res);
                SET_AUX(arg2,PRED);
                res = cons(arg2,res);
                if(arg2 == DOTOBJ && GET_INT(arg3)==2)
                    res = operate(res);
                return(unify(arg1,res));
            }
        }
        else if(listp(arg1) &&
                wide_variable_p(arg2) &&
                wide_variable_p(arg3)){
            unify(arg2,makeatom(".",SYS));
            unify(arg3,makeint(2));
            return(YES);
        }
        else if(structurep(arg1)){
            if(unify(car(arg1),arg2) == YES &&
               unify(makeint(length(cdr(arg1))),arg3) == YES)
                return(YES);
            else
                return(NO);
        }
        else if(variablep(arg1) && constantp(arg2) && integerp(arg3)){
            i = GET_INT(arg3);
            if(i == 0)
                return(unify(arg1,arg2));
            else{
                res = NIL;
                while(i > 0){
                    res = cons(makevariant(),res);
                    i--;
                }
                res = reverse(res);
                if(GET_AUX(arg2) == SIMP)
                    SET_AUX(arg2,PRED);
                res = cons(arg2,res);
                if(arg2 == DOTOBJ && GET_INT(arg3)==2)
                    res = operate(res);
                return(unify(arg1,res));
            }
        }
        else if(atomicp(arg1)){
            if(unify(arg1,arg2) == YES &&
               unify(makeint(0),arg3) == YES)
                return(YES);
            else
                return(NO);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_arg(int arglist, int rest){
    int n,arg1,arg2,arg3,elt,i;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"arg ", arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"arg ", arg2);
        if(!integerp(arg1))
            error(NOT_INT,"arg ", arg1);
        if(!compoundp(arg2))
            error(NOT_COMPOUND,"arg ", arg2);
        if(integerp(eval(arg1)) && GET_INT(eval(arg1)) < 0)
            error(NOT_LESS_THAN_ZERO,"arg ", arg1);

        if(integerp(arg1) && structurep(arg2)){
            i = GET_INT(arg1);
            if(i < 1 || i >= length(arg2))
                return(NO);
            elt = nth(cdr(arg2),i);
            return(unify(arg3,elt));
        }
    }
    return(NO);
}

int b_arg0(int arglist, int rest){
    int n,arg1,arg2,arg3,elt,i;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"arg ", arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"arg ", arg2);
        if(!integerp(arg1))
            error(NOT_INT,"arg ", arg1);
        if(!compoundp(arg2))
            error(NOT_COMPOUND,"arg ", arg2);
        if(integerp(eval(arg1)) && GET_INT(eval(arg1)) < 0)
            error(NOT_LESS_THAN_ZERO,"arg ", arg1);

        if(integerp(arg1) && structurep(arg2)){
            i = GET_INT(arg1)+1;
            if(i < 1 || i >= length(arg2))
                return(NO);
            elt = nth(cdr(arg2),i);
            return(unify(arg3,elt));
        }
    }
    return(NO);
}


//-----other----
int b_listing(int arglist, int rest){
    int n,arg1,clauses,pred,list,temp;

    n = length(arglist);
    if(n == 0){
        list = listreverse(predicates);
        listing_flag = 1;
        while(!nullp(list)){
            pred = car(list);
            list = cdr(list);
            clauses = GET_CAR(pred);
            while(!nullp(clauses)){
                print(car(clauses));
                printf(".\n");
                clauses = cdr(clauses);
            }
        }
        listing_flag = 0;
        return(YES);
    }
    if(n == 1){
        arg1 = deref(car(arglist));
        if(atomp(arg1)){
            clauses = GET_CAR(arg1);
            listing_flag = 1;
            while(!nullp(clauses)){
                print(car(clauses));
                printf(".\n");
                clauses = cdr(clauses);
            }
            listing_flag = 0;
            return(YES);
        }
        else if(eqlp(car(arg1),makeope("/")) &&
                atomp(cadr(arg1)) && integerp(caddr(arg1))){
            clauses = GET_CAR(cadr(arg1));
            listing_flag = 1;
            while(!nullp(clauses)){
                temp = car(clauses);
                if(predicatep(temp) && length(cdr(temp)) == GET_INT(caddr(arg1))){
                    print(temp);
                    printf(".\n");
                }
                else if(clausep(temp) && length(cdr(cadr(arg1))) == GET_INT(caddr(arg1))){
                    print(temp);
                    printf(".\n");
                }
                clauses = cdr(clauses);
            }
            listing_flag = 0;
            return(YES);
        }
    }
    return(NO);
}




// X^Y^Z^pred -> [X,Y,Z]
int get_notfree_variable(int x){
    int res;

    res = NIL;
    while(car(x) == makeatom("^",OPE)){
        res = cons(cadr(x),res);
        x = caddr(x);
    }
    return(listreverse(res));
}

// X^Y^Z^pred -> pred
int get_predicate(int x){
    if(predicatep(x))
        return(x);

    while(!predicatep(caddr(x)) && !nullp(x)){
        x = caddr(x);
    }
    return(caddr(x));
}

// x=[X,Y,Z,A,B] y=[X,Y,Z] -> [A,B]
int get_free_variable(int x, int y){
    int res;

    res = NIL;
    while(!nullp(x)){
        if(!memq(car(x),y))
            res = cons(car(x),res);
        x = cdr(x);
    }
    return(listreverse(res));
}



//transform bwtween predicate and data
int b_univ(int arglist, int rest){
    int n,arg1,arg2,res;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(variablep(arg1) && variablep(arg2))
            error(INSTANTATION_ERR,"=.. ",list2(arg1,arg2));
        if(listp(arg2) && compoundp(car(arg2)))
            error(NOT_ATOMIC,"=.. ", arg2);
        if(variablep(arg1) && nullp(arg2))
            error(NON_EMPTY_LIST,"=.. ", arg2);



        if(!wide_variable_p(arg1) && atomicp(arg1)){
            res = list1(arg1);
            SET_AUX(res,LIST);
            return(unify(res,arg2));
        }
        else if(predicatep(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(builtinp(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(compiledp(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(operationp(arg1)){
            res = structure_to_list(arg1);
            return(unify(res,arg2));
        }
        else if(variablep(arg1) && listp(arg2)){
            if(GET_AUX(car(arg2)) != SYS &&
               GET_AUX(car(arg2)) != COMP &&
               GET_AUX(car(arg2)) != OPE)
                SET_AUX(car(arg2),PRED);
            if(car(arg2) == DOTOBJ)
                arg2 = operate(arg2);
            SET_AUX(arg2,0);
            return(unify(arg1,arg2));
        }
        else if(listp(arg1)){
            arg1 = list3(DOTOBJ,car(arg1),cdr(arg1));
            SET_AUX(arg1,LIST);
            return(unify(arg1,arg2));
        }
        else if(alpha_variable_p(arg2)){//for bug of OPL compiler
            return(unify(arg1,arg2));
        }
        else{
            return(unify(arg1,arg2));
        }
    }
    return(NO);
}

int b_current_predicate(int arglist, int rest){
    int n,arg1,save1,save2,predlist,pred,aritylist,arity;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        predlist = reverse(predicates);
        save1 = wp;
        save2 = sp;
        while(!nullp(predlist)){
            pred = car(predlist);
            predlist = cdr(predlist);
            aritylist = GET_ARITY(pred);
            while(!nullp(aritylist)){
                arity = car(aritylist);
                aritylist = cdr(aritylist);   
                if(unify(arg1,list3(makeatom("/",OPE),pred,arity)) == YES)
                    if(prove(NIL,sp,rest,0) == YES)
                        return(YES);
                
                wp = save1;
                unbind(save2);
            }
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_current_op(int arglist, int rest){
    int n,arg1,arg2,arg3,save1,save2,
        lis,weight,spec,op,w,s,o;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));

        /*
        e.g. ',' ':-'  aux of operator is SIMP
        beclause of parsing. so change to OPE from SIMP
        */
        if(getatom(GET_NAME(arg3),OPE,hash(GET_NAME(arg3))))
            arg3 = makeatom(GET_NAME(arg3),OPE);

        lis = op_list;
        spec = NIL;
        save1 = wp;
        save2 = sp;
        while(!nullp(lis)){
            weight = car(car(lis));
            spec = cadr(car(lis));
            op = caddr(car(lis));

            w= unify(arg1,weight);
            s = unify(arg2,spec);
            o = unify(arg3,op);
            if(w == YES && s == YES && o == YES)
                if(prove(NIL,sp,rest,0) == YES)
                    return(YES);
            lis = cdr(lis);
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}


int o_define(int x, int y){
    int clause;

    if(!nullp(y)){
        if(builtinp(x) || compiledp(x))
            error(BUILTIN_EXIST,"assertz",x);
        if(atomp(x))
            SET_AUX(x,PRED);
        clause = list3(DEFINE,x,y);
        SET_AUX(clause,CLAUSE);
        SET_VAR(clause,reverse(unique(varslist(clause))));
    
        if(assert_flag){
            if(atomp(x))
                insert_data(cadr(clause),clause);
            else
        	    insert_data(car(cadr(clause)),clause);
        }
        else{
            if(atomp(x))
        	     add_data(cadr(clause),clause);
            else
                add_data(car(cadr(clause)),clause);
        }

        return(YES);
    }
    // :- predicate.
    else{
        return(prove_all(x,sp,0));
    }
    return(NO);
}

int o_dcg(int x, int y){
    int clause,res;

    clause = list2(makepred("dcg_expand"),
                list3(makeatom("-->",OPE),x,y));

    res = prove_all(clause,sp,0);
    return(res);
}



int b_gbc(int arglist, int rest){
    int n;

    n = length(arglist);
    if(n == 0){
        gbc();
        return(YES);
    }
    
    return(NO);
}



int o_ignore(int nest, int n){
    return(YES);
}


//-----------file system-------------------
int b_make_directory(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"make_directory ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"make_directory ", arg1);
        mkdir(GET_NAME(arg1),0777);
        return(YES);
    }
    return(NO);
}


int b_change_directory(int arglist , int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"change_directory ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"change_directory ", arg1);

        if(chdir(GET_NAME(arg1)) != -1)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_delete(int arglist, int rest){
    int n,arg1;

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"delete ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"delete ", arg1);

        remove(GET_NAME(arg1));
        return(YES);
    }
    return(NO);
}


//function
int eval(int x){
    int function,arg1,arg2;
    int result[3];

    if(nullp(x))
        return(NIL);
    else if(integerp(x))
        return(x);
    else if(floatp(x))
        return(x);
    else if(longnump(x))
        return(x);
    else if(bignump(x))
        return(x);
    else if(variablep(x))
        return(deref(x));
    else if(!structurep(x)){
        if(eqp(x,makeconst("pi")))
            return(makeflt(3.14159265358979323846));
        else
            error(EVALUATION_ERR,"eval ",x);
    }
    else if(eqp(car(x),makeatom("abs",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_abs(arg1));
    }
    else if(eqp(car(x),makeatom("sin",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_sin(arg1));
    }
    else if(eqp(car(x),makeatom("asin",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_asin(arg1));
    }
    else if(eqp(car(x),makeatom("cos",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_cos(arg1));
    }
    else if(eqp(car(x),makeatom("acos",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_acos(arg1));
    }
    else if(eqp(car(x),makeatom("tan",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_tan(arg1));
    }
    else if(eqp(car(x),makeatom("atan",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_atan(arg1));
    }
    else if(eqp(car(x),makeatom("exp",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_exp(arg1));
    }
    else if(eqp(car(x),makeatom("log",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_log(arg1));
    }
    else if(eqp(car(x),makeatom("floor",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_floor(arg1));
    }
    else if(eqp(car(x),makeatom("ceiling",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_ceiling(arg1));
    }
    else if(eqp(car(x),makeatom("truncate",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_truncate(arg1));
    }
    else if(eqlp(car(x),makeatom("float",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_float(arg1));
    }
    else if(eqp(car(x),makeatom("float_integer_part",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_float_integer_part(arg1));
    }
    else if(eqp(car(x),makeatom("float_fraction_part",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_float_fraction_part(arg1));
    }
    else if(eqp(car(x),makeatom("sign",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_sign(arg1));
    }
    else if(eqp(car(x),makeatom("sqrt",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_sqrt(arg1));
    }
    else if(eqp(car(x),makeatom("round",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_round(arg1));
    }
    else if(eqp(car(x),makeatom("gcd",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        arg2 = result[2];
        return(gcd(arg1,arg2));
    }
    else if(eqp(car(x),makeatom("lcm",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        arg2 = result[2];
        return(lcm(arg1,arg2));
    }
    else if(eqp(car(x),makeatom("min",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        arg2 = result[2];
        return(f_min(arg1,arg2));
    }
    else if(eqp(car(x),makeatom("max",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        arg2 = result[2];
        return(f_max(arg1,arg2));
    }
    else if(eqp(car(x),makeatom("random",PRED))){
        evalterm(x,result);
        arg1 = result[1];
        return(f_random(arg1));
    }
    else if(structurep(x) && operatorp(car(x))){
        evalterm(x,result);
        function = result[0];
        arg1 = result[1];
        arg2 = result[2];
        return((GET_SUBR(function))(arg1, arg2));
    }
    error(EVALUATION_ERR,"eval ",x);
    return(NIL);
}

void evalterm(int x, int result[3]){

    result[0] = car(x);
    result[1] = eval(deref(cadr(x)));
    result[2] = eval(deref(caddr(x)));
    return;
}


int f_plus(int x, int y){
    if(nullp(y))
        y = makeint(0);
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"+ ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"+ ",y);
    if(!numberp(x))
        error(NOT_NUM,"+ ",x);
    if(!numberp(y))
        error(NOT_NUM,"+ ",y);
    return(plus(x,y));
}

int f_minus(int x, int y){
    if(nullp(y)){
        y = x;
        x = makeint(0);
    }
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"- ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"- ",y);
    if(!numberp(x))
        error(NOT_NUM,"- ",x);
    if(!numberp(y))
        error(NOT_NUM,"- ",y);
    if(!nullp(y))
        return(minus(x,y));
    else
        return(mult(x,makeint(-1)));
}

int f_mult(int x, int y){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"* ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"* ",y);
    if(!numberp(x))
        error(NOT_NUM,"* ",x);
    if(!numberp(y))
        error(NOT_NUM,"* ",y);
    return(mult(x,y));
}

int f_divide(int x, int y){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"/ ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"/ ",y);
    if(!numberp(x))
        error(NOT_NUM,"/ ",x);
    if(!numberp(y))
        error(NOT_NUM,"/ ",y);
    if(zerop(y))
    	error(DIV_ZERO,"/",NIL);
    return(exact_to_inexact(divide(x,y)));
}

int f_div(int x, int y){
    int q;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"/ ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"/ ",y);
    if(!numberp(x))
        error(NOT_NUM,"/ ",x);
    if(!numberp(y))
        error(NOT_NUM,"/ ",y);
    if(zerop(y))
    	error(DIV_ZERO,"/",NIL);

    q = quotient(x,y);
    return(q);
}

int f_mod(int x, int y){
    int res;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"mod ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"mod ",y);
    if(!numberp(x))
        error(NOT_NUM,"mod ",x);
    if(!numberp(y))
        error(NOT_NUM,"mod ",y);
    if(!wide_integer_p(x))
        error(NOT_INT,"mod ",x);
    if(!wide_integer_p(y))
        error(NOT_INT,"mod ",y);

    if((positivep(x) && positivep(y)) ||
       (negativep(x) && negativep(y)))
        res = s_remainder(x,y);
    else if((positivep(x) && negativep(y)))
        res = plus(y,s_remainder(x,y));
    else if(negativep(x) && positivep(y))
        res = mult(makeint(-1),plus(y,s_remainder(x,y)));
    else
        res = s_remainder(x,y);
    return(res);
}

int f_rem(int x, int y){
    int q,r;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"rem ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"rem ",y);
    if(!numberp(x))
        error(NOT_NUM,"rem ",x);
    if(!numberp(y))
        error(NOT_NUM,"rem ",y);
    if(!wide_integer_p(x))
        error(NOT_INT,"rem ",x);
    if(!wide_integer_p(y))
        error(NOT_INT,"rem ",y);

    q = quotient(x,y);
    r = minus(x,mult(y,q));
    return(r);
}

int f_expt(int x, int y){
    double dx,dy,dz;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"** ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"** ",y);
    if(negativep(x) && !wide_integer_p(y))
        error(EVALUATION_ERR,"** ",y);
    if(!numberp(x))
        error(NOT_NUM,"** ",x);
    if(!numberp(y))
        error(NOT_NUM,"** ",y);
    if(floatp(x) && GET_FLT(x) >= DBL_MAX)
        error(EVALUATION_ERR,"** ",x);
    if(floatp(x) && (GET_FLT(x) <= DBL_MIN && GET_FLT(x) != 0))
        error(EVALUATION_ERR,"** ",x);
    if(bignump(x) && (longnump(y) || bignump(y)))
        error(EXPONENT_ERR,"** ",y);

    if((integerp(x) || longnump(x) || bignump(x)) && integerp(y) && GET_INT(y) == 0)
        return(makeint(1));

    if((integerp(x) || longnump(x) || bignump(x)) && (integerp(y) && GET_INT(y) > 0))
        return(expt(x,GET_INT(y)));

    if((integerp(x) || floatp(x)) &&
       (integerp(y) || floatp(y))){

        x = exact_to_inexact(x);
        y = exact_to_inexact(y);
        dx = GET_FLT(x);
        dy = GET_FLT(y);
        dz = pow(dx,dy);
        return(makeflt(dz));
    }
    if(integerp(x) && (integerp(y) || longnump(y) || bignump(y))){
        if(GET_INT(x) == 1)
            return(x);
        else if(GET_INT(x) == 0)
            return(x);
        else if(GET_INT(x) == -1){
            if(zerop(s_remainder(y,makeint(2))))
                return(makeint(1));
            else
                return(x);
        }
    }
    if(floatp(x) && (longnump(y) || bignump(y))){
        if(GET_FLT(x) == 1.0)
            return(x);
        else if(GET_FLT(x) == 0.0)
            return(x);
        else if(GET_FLT(x) == -1.0){
            if(zerop(s_remainder(y,makeint(2))))
                return(makeflt(1.0));
            else
                return(x);
        }
    }
    if(longnump(x) && integerp(y)){
        if(GET_INT(y) == 1){
            dx = GET_FLT(exact_to_inexact(x));
            dy = dx;
            return(makeflt(dy));
        }
        else if(GET_INT(y) == 2){
            dx = GET_FLT(exact_to_inexact(x));
            dy = dx*dx;
            return(makeflt(dy));
        }
        else if(GET_INT(y) == -1){
            dx = GET_FLT(exact_to_inexact(x));
            dy = 1.0 / dx;
            return(makeflt(dy));
        }
        else if(GET_INT(y) == -2){
            dx = GET_FLT(exact_to_inexact(x));
            dy = 1.0 / (dx*dx);
            return(makeflt(dy));
        }
    }
    if(longnump(x) && floatp(y)){
        if(GET_FLT(y) == 0.0){
            return(makeflt(1.0));
        }
        else if(GET_FLT(y) == 1.0){
            dx = GET_FLT(exact_to_inexact(x));
            dy = dx;
            return(makeflt(dy));
        }
        else if(GET_FLT(y) == 2.0){
            dx = GET_FLT(exact_to_inexact(x));
            dy = dx*dx;
            return(makeflt(dy));
        }
        else if(GET_FLT(y) == -1.0){
            dx = GET_FLT(exact_to_inexact(x));
            dy = 1.0 / dx;
            return(makeflt(dy));
        }
        else if(GET_FLT(y) == -2.0){
            dx = GET_FLT(exact_to_inexact(x));
            dy = 1.0 / (dx*dx);
            return(makeflt(dy));
        }
    }
    return(UNDEF);
}

//x is cell address, y is integer of C
int expt(int x, int y){
    int res,p;

    res = makeint(1);
    p = x;
    while(y > 0){
        if((y % 2) ==0){
            p = mult(p,p);
            y = y / 2;
        }
        else{
            res = mult(res,p);
            y = y -1;
        }
    }
    return(res);
}

int f_sqrt(int x){
    double dx;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"sqrt ",x);
    if(!numberp(x))
        error(NOT_NUM,"sqrt ",x);


    dx = sqrt(GET_FLT(exact_to_inexact(x)));
    if(ceil(dx) == floor(dx) && dx < BIGNUM_BASE)
        return(makeint((int)dx));
    else
        return(makeflt(dx));
}

int f_round(int x){
    double dx,df,dc;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"round ",x);
    if(!numberp(x))
        error(NOT_NUM, "round ", x);

    if(floatp(x)){
        dx = GET_FLT(x);
        df = floor(dx);
        dc = ceil(dx);
        if(dx == (df+dc)/2)
            if(fmod(df,2.0) == 0.0)
                dx = df;
            else
                dx = dc;
        else
            dx = round(dx);

        return(makeflt(dx));
    }
    else
        return(x);
}

int f_leftshift(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"<< ", x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"<< ", y);
    if(!integerp(x))
        error(NOT_INT,"<<", x);
    if(!integerp(y))
        error(NOT_INT,"<<", y);

    x = GET_INT(x);
    y = GET_INT(y);
    return(makeint(x<<y));
}

int f_rightshift(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,">> ", x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,">> ", y);
    if(!integerp(x))
        error(NOT_INT,">> ", x);
    if(!integerp(y))
        error(NOT_INT,">> ", y);

    x = GET_INT(x);
    y = GET_INT(y);
    return(makeint(x>>y));
}

int f_logicaland(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"/\\ ", x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"/\\ ", y);
    if(!integerp(x))
        error(NOT_INT,"/\\ ", x);
    if(!integerp(y))
        error(NOT_INT,"/\\ ", y);

    x = GET_INT(x);
    y = GET_INT(y);
    return(makeint(x & y));
}

int f_logicalor(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"\\/ ", x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"\\/ ", y);
    if(!integerp(x))
        error(NOT_INT,"\\/ ", x);
    if(!integerp(y))
        error(NOT_INT,"\\/ ", y);

    x = GET_INT(x);
    y = GET_INT(y);
    return(makeint(x | y));
}

int f_complement(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"\\ ", x);
    if(!integerp(x))
        error(NOT_INT,"\\ ", x);

    x = GET_INT(x);
    return(makeint(~x));
}

int f_exclusiveor(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"xor ", x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"xor ", y);
    if(!integerp(x))
        error(NOT_INT,"xor ", x);
    if(!integerp(y))
        error(NOT_INT,"xor ", y);


    x = GET_INT(x);
    y = GET_INT(y);
    return(makeint(x ^ y));
}

int f_inclusiveand(int x, int y){

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"iand ", x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"iand ", y);
    if(!integerp(x))
        error(NOT_INT,"iand ", x);
    if(!integerp(y))
        error(NOT_INT,"iand ", y);


    x = GET_INT(x);
    y = GET_INT(y);
    return(makeint(~(x ^ y)));
}

int f_abs(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"abs ",x);
    if(!numberp(x))
        error(NOT_NUM,"abs ",x);

    return(absolute(x));
}

int f_sin(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"sin ",x);
    if(!numberp(x))
        error(NOT_NUM,"sin ",x);

    return(makeflt(sin(GET_FLT(exact_to_inexact(x)))));
}

int f_asin(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"asin ",x);
    if(!numberp(x))
        error(NOT_NUM,"asin ",x);

	  return(makeflt(asin(GET_FLT(exact_to_inexact(x)))));
}

int f_cos(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"cos ",x);
    if(!numberp(x))
        error(NOT_NUM,"cos ",x);

	  return(makeflt(cos(GET_FLT(exact_to_inexact(x)))));
}

int f_acos(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"acos ",x);
    if(!numberp(x))
        error(NOT_NUM,"acos ",x);

	  return(makeflt(acos(GET_FLT(exact_to_inexact(x)))));
}

int f_tan(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"tan ",x);
    if(!numberp(x))
        error(NOT_NUM,"tan ",x);

	  return(makeflt(tan(GET_FLT(exact_to_inexact(x)))));
}

int f_atan(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"atan ",x);
    if(!numberp(x))
        error(NOT_NUM,"atan ",x);

	  return(makeflt(atan(GET_FLT(exact_to_inexact(x)))));
}

int f_exp(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"exp ",x);
    if(!numberp(x))
        error(NOT_NUM,"exp ",x);

	  return(makeflt(exp(GET_FLT(exact_to_inexact(x)))));
}

int f_log(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"log ",x);
    if(!numberp(x))
        error(NOT_NUM,"log ",x);
    if(zerop(x) || negativep(x))
        error(EVALUATION_ERR,"log ", x);

	  return(makeflt(log(GET_FLT(exact_to_inexact(x)))));
}

int f_floor(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"floor ",x);
    if(!numberp(x))
        error(NOT_NUM,"floor ",x);

	  return(makeint((int)floor(GET_FLT(exact_to_inexact(x)))));
}

int f_ceiling(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"ceiling ",x);
    if(!numberp(x))
        error(NOT_NUM,"ceiling ",x);

	  return(makeint((int)ceil(GET_FLT(exact_to_inexact(x)))));
}

int f_truncate(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"truncate ",x);
    if(!numberp(x))
        error(NOT_NUM,"truncate ",x);

	  return(makeint((int)trunc(GET_FLT(exact_to_inexact(x)))));
}

int f_float(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"float ",x);
    if(!numberp(x))
        error(NOT_NUM,"float ",x);

	  return(makeflt(GET_FLT(exact_to_inexact(x))));
}

int f_float_integer_part(int x){
    double f;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"float_integer_part ",x);
    if(!numberp(x))
        error(NOT_NUM,"float_integer_part ",x);

    f = GET_FLT(exact_to_inexact(x));
    f = trunc(f);
	  return(makeflt(f));
}

int f_float_fraction_part(int x){
    double f;

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"float_fraction_part ",x);
    if(!numberp(x))
        error(NOT_NUM,"float_fraction_part ",x);

    f = GET_FLT(exact_to_inexact(x));
    f = f - (int)f;
	  return(makeflt(f));
}


int f_sign(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"sign ",x);
    if(!numberp(x))
        error(NOT_NUM,"sign ",x);

    if(positivep(x))
    	return(makeint(1));
    else if(zerop(x))
    	return(makeint(0));
    else if(negativep(x))
    	return(makeint(-1));
    else
    	return(NIL);
}

int f_min(int x, int y){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"min ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"min ",y);
    if(!numberp(x))
        error(NOT_NUM,"min ",x);
    if(!numberp(y))
        error(NOT_NUM,"min ",y);

    if(smallerp(x,y)){
        if(!floatp(x) && floatp(y))
            return(exact_to_inexact(x));
        else
            return(x);
    }
    else{
        if(!floatp(y) && floatp(x))
            return(exact_to_inexact(y));
        else
            return(y);
    }
}

int f_max(int x, int y){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"max ",x);
    if(wide_variable_p(y))
        error(INSTANTATION_ERR,"max ",y);
    if(!numberp(x))
        error(NOT_NUM,"max ",x);
    if(!numberp(y))
        error(NOT_NUM,"max ",y);

    if(greaterp(x,y)){
        if(!floatp(x) && floatp(y))
            return(exact_to_inexact(x));
        else
            return(x);
    }
    else{
        if(!floatp(y) && floatp(x))
            return(exact_to_inexact(y));
        else
            return(y);
    }
}


int f_random(int x){
    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"random ",x);
    if(!integerp(x))
        error(NOT_INT,"random", x);

    x = GET_INT(x);
    return(makeint(rand() & x));
}



int b_nano(int arglist, int rest){
    int n,arg1,res;
    char str1[STRSIZE];
    char str0[STRSIZE] = "nano ";

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(!singlep(arg1))
            error(NOT_ATOM,"nano",arg1);

        strcpy(str1,GET_NAME(arg1));
        strcat(str0,str1);
        res = system(str0);
        if(res == -1)
            error(SYSTEM_ERROR,"nano",arg1);
        b_reconsult(list1(arg1),NIL);
        return(YES);
    }
    return(NO);
}









int b_filename(int arglist, int rest){
	int n,arg1,arg2,pos,len;
    char str1[STRSIZE];

    n = length(arglist);
    if(n == 2){
    	arg1 = deref(car(arglist));
        arg2 = cadr(arglist);
    	strcpy(str1,GET_NAME(arg1));
        len = strlen(GET_NAME(arg1));
        for(pos=0;pos<len;pos++)
        	if(str1[pos] == '.'){
            	str1[pos] = NUL;
                return(unify(arg2,makeconst(str1)));
            }
        return(unify(arg1,arg2));
    }
    return(NO);
}

int b_shell(int arglist, int rest){
    int n,arg1,res;
    char str1[STRSIZE];

    n = length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(!singlep(arg1))
            error(NOT_ATOM,"shell",arg1);

        strcpy(str1,GET_NAME(arg1));
        res = system(str1);
        if(res == -1)
            error(SYSTEM_ERROR,"shell",arg1);
        return(YES);
    }
    return(NO);
}



int b_sort(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        return(unify(arg2,sort(arg1)));
    }
    return(NO);
}

int b_keysort(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        return(unify(arg2,keysort(arg1)));
    }
    return(NO);
}

int b_member(int arglist, int rest){
    int n,arg1,arg2,x,y,l,save1,save2,body;

    save2 = sp;
    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));


        save1 = wp;
        x = makevariant();
        l = makevariant();
        if(unify(arg1,x) == YES && unify(arg2,wlistcons(x,l)) == YES){
            if(prove(NIL,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);

        save1 = wp;
        x = makevariant();
        y = makevariant();
        l = makevariant();
        if(unify(arg1,x) == YES &&
           unify(arg2,wlistcons(y,l)) == YES){
            body = wlist3(makeatom("member",COMP),x,l);
            if(prove(body,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

//---------extention--------

int b_append(int arglist, int rest){
    int n,arg1,arg2,arg3,x,ls,ys,zs,save1,save2,body;

    save2 = sp;
    body = NIL;
    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));
        arg3 = deref(caddr(arglist));

        save1 = wp;
        if(unify(arg1,NIL) == YES && unify(arg2,arg3) == YES){
            if(prove(NIL,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);

        save1 = wp;
        x = makevariant();
        ls = makevariant();
        ys = makevariant();
        zs = makevariant();
        if(unify(arg1,wlistcons(x,ls)) == YES &&
           unify(arg2,ys) == YES &&
           unify(arg3,wlistcons(x,zs)) == YES){
            body = wlist4(makeatom("append",COMP),ls,ys,zs);
            if(prove(body,sp,rest,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

//listreverse/2
int b_reverse(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(!variablep(arg1) && variablep(arg2))
            return(unify(listreverse(arg1),arg2));
        else if(variablep(arg1) && !variablep(arg2))
            return(unify(arg1,listreverse(arg2)));
        else
            return(NO);
    }
    return(NO);
}

/*
between(L, H, L) :- L =< H.
between(L, H, V) :- L < H, L1 is L + 1, between(L1, H, V).
*/

int b_between(int arglist, int rest){
    int n,arg1,arg2,arg3,varL1,varV,varH,varL,body,save1,save2;

    n = length(arglist);
    if(n == 3){
        arg1 = deref(car(arglist));   //low
        arg2 = deref(cadr(arglist));  //high
        arg3 = deref(caddr(arglist)); //variable
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"between ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"between ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"between ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"between ",arg2);
        if(!wide_variable_p(arg3) && !wide_integer_p(arg3))
            error(NOT_INT,"between ",arg3);

        save1 = wp;
        save2 = sp;
        varH = makevariant();
        varL = makevariant();
        if(unify(arg1,varL) == YES &&
            unify(arg2,varH) == YES &&
            unify(arg3,varL) == YES){
                body = wlist3(makeatom("=<",SYS),deref(varL),deref(varH));
                if(prove(body,sp,rest,0) == YES)
                    return(YES);
        }
        wp = save1;
        unbind(save2);

        save1 = wp;
        varL1 = makevariant();
        varL = makevariant();
        varH = makevariant();
        varV = makevariant();
        if(unify(arg1,varL) == YES &&
            unify(arg2,varH) == YES &&
            unify(arg3,varV) == YES){
            body = wlist3(makeatom(",",OPE),wlist3(makeatom("<",SYS),deref(varL),deref(varH)),wlist3(makeatom(",",OPE),wlist3(makeatom("is",SYS),varL1,wcons(makeatom("+",OPE),wcons(varL,wcons(makeint(1),NIL)))),wcons(makeatom("between",COMP),wcons(varL1,wcons(varH,wcons(varV,NIL))))));
            if(prove_all(addtail_body(rest,body),sp,0) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
    }
    return(NO);
}


//------------------------------------------------

int b_inc(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"inc ", list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"inc ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"inc ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"inc ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"inc ",arg2);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"inc ",arg1);
        if(wide_integer_p(arg2) && negativep(arg2))
            error(NOT_LESS_THAN_ZERO,"inc ",arg2);

        if(wide_variable_p(arg1))
            return(unify(arg1,minus(arg2,makeint(1))));
        else if(wide_variable_p(arg2))
            return(unify(arg2,plus(arg1,makeint(1))));
        else
            return(unify(arg2,plus(arg1,makeint(1))));

    }
    return(NO);
}

int b_dec(int arglist, int rest){
    int n,arg1,arg2;

    n = length(arglist);
    if(n == 2){
        arg1 = deref(car(arglist));
        arg2 = deref(cadr(arglist));

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"dec ", list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"dec ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"dec ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"dec ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"dec ",arg2);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"dec ",arg1);
        if(wide_integer_p(arg2) && negativep(arg2))
            error(NOT_LESS_THAN_ZERO,"dec ",arg2);

        if(wide_variable_p(arg1))
            return(unify(arg1,plus(arg2,makeint(1))));
        else if(wide_variable_p(arg2))
            return(unify(arg2,minus(arg1,makeint(1))));
        else
            return(unify(arg2,minus(arg1,makeint(1))));

    }
    return(NO);
}

int b_ansi_cuu(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cuu ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"ansi_cuu ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cuu ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVU;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_cud(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cud ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_cud ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cud ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVD;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_cuf(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cuf ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_cuf ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cuf ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVR;
            m--;
        }
        return(YES);
    }
    return(NO);
}

int b_ansi_cub(int arglist, int rest){
    int n,arg1,m;

    n=length(arglist);
    if(n == 1){
        arg1 = deref(car(arglist));
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"ansi_cub ", arg1);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"and_cub ",arg1);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"ansi_cub ",arg1);
        m = get_int(arg1);
        while(m > 0){
            ESCMVL;
            m--;
        }
        return(YES);
    }
    return(NO);
}