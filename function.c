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
#if _WIN32
#include <windows.h>
#include <direct.h>
#endif
#if __linux
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#endif
#if __OpenBSD__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#endif
#include "npl.h"

#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif __OpenBSD__
#define FLUSH fpurge(stdin);
#else
#define FLUSH __fpurge(stdin);
#endif

#if __linux
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
#endif
#if __OpenBSD__
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
#endif


#if _WIN32
//for dynamic link
typedef void (*tpred)(char*, int(*pred)(int , int));
typedef void (*p_f0)(int, tpred);
typedef void (*p_f1)(int, tpred);
typedef void (*p_f2)(int, tpred);
typedef void (*p_f3)(int, tpred);
typedef void (*p_f4)(int, tpred);
typedef void (*p_def)(tpred);
typedef void (*p_init)(void);
typedef void (*p_declare)(void);

void dynamic_link(int x){
    HMODULE hmod;

    hmod = LoadLibrary((LPCSTR)(GET_NAME(x)));
    //loadeddll = hmod;
    p_f0 init_f0 = (p_f0)GetProcAddress(hmod, (LPCSTR)"init0");
    p_f1 init_f1 = (p_f1)GetProcAddress(hmod, (LPCSTR)"init1");
    p_f2 init_f2 = (p_f2)GetProcAddress(hmod, (LPCSTR)"init2");
    p_f3 init_f3 = (p_f3)GetProcAddress(hmod, (LPCSTR)"init3");
    p_f4 init_f4 = (p_f4)GetProcAddress(hmod, (LPCSTR)"init4");
    p_def init_deftpred = (p_def)GetProcAddress(hmod, (LPCSTR)"init_deftpred");
    p_init init_tpredicate = (p_init)GetProcAddress(hmod, (LPCSTR)"init_tpredicate");
    p_declare init_declare = (p_declare)GetProcAddress(hmod, (LPCSTR)"init_declare");
    //p_cut1 init_cut = (p_cut1)GetProcAddress(hmod, (LPCSTR)"init_cut");
    //p_cut1 invoke_cut = (p_cut1)GetProcAddress(hmod, (LPCSTR)"invoke_cut");
#endif

    //argument-0 type
    init_f0(0,(tpred)checkgbc);
    init_f0(1,(tpred)gbc);
    init_f0(2,(tpred)freshcell);
    init_f0(3,(tpred)makevariant);
    init_f0(4,(tpred)get_tp);
    init_f0(5,(tpred)get_sp);
    init_f0(6,(tpred)print_trail_block);
    init_f0(11,(tpred)get_trail_end);
    init_f0(12,(tpred)debug);
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
    init_f1(8,(tpred)execute);
    init_f1(9,(tpred)unbind);
    init_f1(10,(tpred)push_trail_body);
    init_f1(11,(tpred)get_goal);
    init_f1(12,(tpred)set_tp);
    init_f1(13,(tpred)set_sp);
    init_f1(14,(tpred)set_length);
    init_f1(15,(tpred)deref);
    init_f1(16,(tpred)retract_goal);
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
    init_f1(32,(tpred)set_trail_end);
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
    init_f2(33,(tpred)set_goal);
    init_f2(34,(tpred)f_div);
    init_f2(35,(tpred)set_var);
    init_f2(36,(tpred)wcons);
    init_f2(37,(tpred)wlist2);
    init_f2(38,(tpred)wlistcons);
    init_f2(39,(tpred)proceed);

    //argument-3
    init_f3(0,(tpred)resolve_all);
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
    //cut_function[0] = init_cut;
    //cut_function[1] = invoke_cut;
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
    defoperator("?-",o_question,1200,FX,0);
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
    definfix("@",b_atmark,100,XFX);
    definfix(":",b_colon,50,XFX);
    definfix("->",b_ifthen,1050,XFY);

    defbuiltin("unify_with_occurs_check",b_unify_with_occurs_check);
    defbuiltin("op",b_op);
    defbuiltin("!",b_cut);
    defbuiltin("assert",b_assert);
    defbuiltin("asserta",b_asserta);
    defbuiltin("assertz",b_assert);
    defbuiltin("abolish",b_abolish);
    defbuiltin("read",b_read);
    defbuiltin("read_term",b_read_term);
    defbuiltin("read_item",b_read_item);
    defbuiltin("read_token",b_read_token);
    defbuiltin("write",b_write);
    defbuiltin("writeln",b_writeln);
    defbuiltin("write_term",b_write_term);
    defbuiltin("write_canonical",b_write_canonical);
    defbuiltin("writeq",b_writeq);
    defbuiltin("put",b_put);
    defbuiltin("get",b_get);
    defbuiltin("get0",b_get0);
    defbuiltin("get_char",b_get_char);
    defbuiltin("get_code",b_get_code);
    defbuiltin("get_byte",b_get_byte);
    defbuiltin("peek_byte",b_peek_byte);
    defbuiltin("put_char",b_put_char);
    defbuiltin("put_code",b_put_code);
    defbuiltin("put_byte",b_put_byte);
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
    defbuiltin("numbervars",b_numbervars);
    defbuiltin("predicate_property",b_predicate_property);
    defbuiltin("copy_term",b_copy_term);
    defbuiltin("debug",b_debug);
    defbuiltin("atom_length",b_atom_length);
    defbuiltin("findall",b_findall);
    defbuiltin("consult",b_consult);
    defbuiltin("reconsult",b_reconsult);
    defbuiltin("initialization",b_initialization);
    defbuiltin("include",b_include);
    defbuiltin("ensure_loaded",b_ensure_loaded);
    defbuiltin("use_module",b_use_module);
    defbuiltin("open",b_open);
    defbuiltin("close",b_close);
    defbuiltin("see",b_see);
    defbuiltin("seen",b_seen);
    defbuiltin("tell",b_tell);
    defbuiltin("told",b_told);
    defbuiltin("current_input",b_current_input);
    defbuiltin("current_output",b_current_output);
    defbuiltin("set_input",b_set_input);
    defbuiltin("set_output",b_set_output);
    defbuiltin("flush_output",b_flush_output);
    defbuiltin("at_end_of_stream",b_at_end_of_stream);
    defbuiltin("trace",b_trace);
    defbuiltin("notrace",b_notrace);
    defbuiltin("spy",b_spy);
    defbuiltin("nospy",b_nospy);
    defbuiltin("atom",b_atom);
    defbuiltin("string",b_string);
    defbuiltin("integer",b_integer);
    defbuiltin("real",b_real);
    defbuiltin("float",b_real);
    defbuiltin("number",b_number);
    defbuiltin("compound",b_compound);
    defbuiltin("ground",b_ground);
    defbuiltin("constant",b_constant);
    defbuiltin("var",b_var);
    defbuiltin("nonvar",b_nonvar);
    defbuiltin("atomic",b_atomic);
    defbuiltin("list",b_list);
    defbuiltin("gbc",b_gbc);
    defbuiltin("time",b_time);
    defbuiltin("timer",b_timer);
    defbuiltin("char_set",b_char_set);
    defbuiltin("char_code",b_char_code);
    defbuiltin("atom_chars",b_atom_chars);
    defbuiltin("atom_codes",b_atom_codes);
    defbuiltin("string_chars",b_string_chars);
    defbuiltin("string_codes",b_string_codes);
    defbuiltin("name",b_atom_codes);
    defbuiltin("number_chars",b_number_chars);
    defbuiltin("number_codes",b_number_codes);
    defbuiltin("catch",b_catch);
    defbuiltin("throw",b_throw);
    defbuiltin("reverse",b_reverse);
    defbuiltin("dynamic",b_dynamic);
    defbuiltin("multifile",b_multifile);
    defbuiltin("discontiguous",b_discontiguous);
    defbuiltin("char_conversion",b_char_conversion);
    defbuiltin("set_prolog_flag",b_set_prolog_flag);
    defbuiltin("module",b_module);
    defbuiltin("end_module",b_end_module);
    defbuiltin("export",b_export);
    defbuiltin("import",b_import);
    defbuiltin("reexport",b_import);
    defbuiltin("body",b_body);
    defbuiltin("end_body",b_end_body);
    defbuiltin("meta",b_meta);
    defbuiltin("calling_context",b_calling_context);
    defbuiltin("succ",b_succ);
    defbuiltin("term_variables",b_term_variables);
    defbuiltin("callable",b_callable);
    defbuiltin("%ask",b_ask);
    defbuiltin("%findall_help",b_findall_help);
    defbuiltin("%bagof_help",b_bagof_help);
    defbuiltin("system",b_system);
    defbuiltin("sort",b_sort);
    defbuiltin("keysort",b_keysort);
    defbuiltin("retractall",b_retractall);
    defbuiltin("compare",b_compare);
    defbuiltin("freeze",b_freeze);
    defbuiltin("make_directory",b_make_directory);
    defbuiltin("directory_exists",b_directory_exists);
    defbuiltin("current_directory",b_current_directory);
    defbuiltin("change_directory",b_change_directory);
    defbuiltin("expand_path",b_expand_path);
    defbuiltin("delete_file",b_delete_file);
    defbuiltin("file_exists",b_file_exists);
    defbuiltin("decompose_file_name",b_decompose_file_name);
    defbuiltin("environment_variable",b_environment_variable);
    defbuiltin("file_modification_time",b_file_modification_time);
    defbuiltin("date",b_date);
    defbuiltin("c_lang",b_c_lang);
    defbuiltin("c_define",b_c_define);
    defbuiltin("c_include",b_c_include);
    defbuiltin("c_option",b_c_option);
    defbuiltin("c_global",b_c_global);
    defbuiltin("o_include_cut",b_include_cut);
    defbuiltin("o_has_cut",b_has_cut);
    defbuiltin("o_has_c_lang",b_has_c_lang);
    defbuiltin("o_c_define",b_o_c_define);
    defbuiltin("o_c_include",b_o_c_include);
    defbuiltin("o_c_option",b_o_c_option);
    defbuiltin("o_c_global",b_o_c_global);
    defbuiltin("o_clause_with_arity",b_clause_with_arity);
    defbuiltin("o_variable_convert",b_variable_convert);
    defbuiltin("o_filename",b_filename);
    defbuiltin("o_arity_count",b_arity_count);
    defcompiled("o_reconsult_predicate",b_reconsult_predicate);
    defbuiltin("o_reconsult_predicate_list",b_reconsult_predicate_list);
    defbuiltin("o_defined_predicate",b_defined_predicate);
    defbuiltin("o_defined_userop",b_defined_userop);
    defbuiltin("o_property",b_property);
    defbuiltin("o_is",b_isp);
    defbuiltin("o_compiler_anoymous",b_compiler_anoymous);
    defbuiltin("o_compiler_variable",b_compiler_variable);
    defbuiltin("o_generate_variable",b_generate_variable);
    defbuiltin("o_generate_all_variable",b_generate_all_variable);
    defbuiltin("o_self_introduction",b_self_introduction);
    defbuiltin("o_dynamic_check",b_dynamic_check);
    defbuiltin("o_get_dynamic",b_get_dynamic);
    defbuiltin("o_get_execute",b_get_execute);
    defbuiltin("o_write_original_variable",b_write_original_variable);
    defbuiltin("o_atom_convert",b_atom_convert);
    defbuiltin("o_generate_before_cut",b_generate_before_cut);
    defbuiltin("o_generate_after_cut",b_generate_after_cut);
    defbuiltin("o_generate_before_c_lang",b_generate_before_c_lang);
    defbuiltin("o_generate_after_c_lang",b_generate_after_c_lang);
    defbuiltin("o_generated_module",b_generated_module);
    defbuiltin("o_argument_list",b_argument_list);
    defbuiltin("o_decompose",b_decompose);
    defbuiltin("o_findatom",b_findatom);
    defbuiltin("o_bignum",b_bignum);
    defbuiltin("o_longnum",b_longnum);
    defbuiltin("o_dumpcell",b_dumpcell);
    defcompiled("o_ifthen",b_comp_ifthen);
    defcompiled("o_ifthenelse",b_comp_ifthenelse);

    #if __linux
    defbuiltin("set_editor",b_set_editor);
    defbuiltin("edit",b_nano);
    defbuiltin("server_create",b_server_create);
    defbuiltin("server_accept",b_server_accept);
    defbuiltin("client_connect",b_client_connect);
    defbuiltin("socket_send",b_socket_send);
    defbuiltin("socket_recieve",b_socket_recieve);
    defbuiltin("socket_close",b_socket_close);
    #endif

    defcompiled("repeat",b_repeat);
    defcompiled("append",b_append);
    defcompiled("member",b_member);
    defcompiled("select",b_select);
    defcompiled("maplist",b_maplist);
    defcompiled("retract",b_retract);
    defcompiled("clause",b_clause);
    defcompiled("current_predicate",b_current_predicate);
    defcompiled("current_op",b_current_op);
    defcompiled("current_module",b_current_module);
    defcompiled("current_visible",b_current_visible);
    defcompiled("current_prolog_flag",b_current_prolog_flag);
    defcompiled("stream_property",b_stream_property);
    defcompiled("between",b_between);
    defcompiled("bagof",b_bagof);
    defcompiled("setof",b_setof);
    defcompiled("sub_atom",b_sub_atom);
    defcompiled("atom_concat",b_atom_concat);
    defcompiled("length",b_length);
    defcompiled("call",b_call);
    defcompiled("setup_call_cleanup",b_setup_call_cleanup);

    return;
}

int b_length(int nest, int n){
    int arg1,arg2,res,i,j,save1,save2;

    save2 = sp;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(integerp(eval(arg2)) && GET_INT(eval(arg2)) < 0)
            error(NOT_LESS_THAN_ZERO,"length ",arg2);
        if(!wide_variable_p(arg2) && !integerp(eval(arg2)))
            error(NOT_INT,"length ",arg2);
        if(wide_variable_p(arg1) && wide_variable_p(arg2) && eqp(arg1,arg2))
            error(RESOURCE_ERR,"length ",arg1);

        save1 = wp;
        if(listp(arg1) && length(arg1) == -1)
            return(NO);
        else if(listp(arg1) && integerp(arg2)){
            if(unify(arg2,makeint(length(arg1))))
                if(proceed(NIL,nest) == YES)
                    return(YES);

            wp = save1;
            unbind(save2);
            return(NO);
        }
        else if(listp(arg1) && wide_variable_p(arg2)){
            if(unify(arg2,makeint(length(arg1))) == YES)
                if(proceed(NIL,nest) == YES)
                    return(YES);

            wp = save1;
            unbind(save2);
            return(NO);
        }
        else if(wide_variable_p(arg1) && integerp(arg2)){
            i = GET_INT(arg2);
            res = NIL;
            while(i > 0){
                res = wlistcons(makeatom("_",ANOY),res);
                i--;
            }
            if(unify(arg1,res) == YES)
                if(proceed(NIL,nest) == YES)
                    return(YES);

            wp = save1;
            unbind(save2);
            return(NO);
        }
        else if(wide_variable_p(arg1) && wide_variable_p(arg2)){
            j = 0;
            while(1){
                i = j;
                res = NIL;
                while(i > 0){
                    res = wlistcons(makeatom("_",ANOY),res);
                    i--;
                }
                if(unify(arg1,res) == YES && unify(arg2,makeint(j)) == YES)
                    if(proceed(NIL,nest) == YES)
                        return(YES);

                wp = save1;
                unbind(save2);
                j++;
            }
        }
        else
            return(NO);
    }
    return(NO);
}


//compiled predicate
int b_repeat(int nest, int n){
    int save1,save2,save3;

    save2 = sp;
    save3 = tp;
    if(n == 0){
        loop:
        save1 = wp;
        save_trail(save3);
        if(proceed(NIL,nest) == YES){
            return(YES);
        }
    wp = save1;
    unbind(save2);
    tp = save3;
    retract_trail(save3);
    goto loop;
    }
    return(NO);
}

int b_member(int nest, int n){
    int arg1,arg2,x,y,l,save1,save2,body;

    save2 = sp;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);


        save1 = wp;
        x = makevariant();
        l = makevariant();
        if(unify(arg1,x) == YES && unify(arg2,wlistcons(x,l)) == YES){
            if(proceed(NIL,nest) == YES)
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
            if(proceed(body,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_append(int nest, int n){
    int arg1,arg2,arg3,x,ls,ys,zs,save1,save2,body;

    save2 = sp;
    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        save1 = wp;
        if(unify(arg1,NIL) == YES && unify(arg2,arg3) == YES){
            if(proceed(NIL,nest) == YES)
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
            if(proceed(body,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}


//select(X, [X | Xs], Xs).
//select(X, [Y | Ys], [Y | Zs]) :- select(X, Ys, Zs).
int b_select(int nest, int n){
    int arg1,arg2,arg3,save1,save2,body,x,xs,y,ys,zs;

    save2 = sp;
    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        save1 = wp;
        x = makevariant();
        xs = makevariant();
        if(unify(arg1,x) == YES &&
           unify(arg2,wlistcons(x,xs)) == YES &&
           unify(arg3,xs) == YES){
            if(proceed(NIL,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);

        save1 = wp;
        x = makevariant();
        y = makevariant();
        ys = makevariant();
        zs = makevariant();
        if(unify(arg1,x) == YES &&
           unify(arg2,wlistcons(y,ys)) == YES &&
           unify(arg3,wlistcons(y,zs)) == YES){
            body = wlist4(makeatom("select",COMP),x,ys,zs);
            if(proceed(body,nest) == YES)
                return(YES);

        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

/*
maplist(C, []).
maplist(C, [E1|E1s]) :-
   call(C, E1),
   maplist(C, E1s).

maplist(C, [], []).
maplist(C, [E1|E1s], [E2|E2s]) :-
   call(C, E1, E2),
   maplist(C, E1s, E2s).

*/

int b_maplist(int nest, int n){
    int arg1,arg2,arg3,arg4,varC,varE1,varE1s,
        varE2,varE2s,varE3,varE3s,body,save1,save2;

    save2 = sp;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        save1 = wp;
        varC = makevariant();
        if(unify(arg1,varC) == YES &&
           unify(arg2,NIL) == YES)
            if(proceed(NIL,nest) == YES)
                return(YES);

        wp = save1;
        unbind(save2);

        save1 = wp;
        varC = makevariant();
        varE1 = makevariant();
        varE1s = makevariant();
        if(unify(arg1,varC) == YES &&
            unify(arg2,wlistcons(varE1,varE1s)) == YES){
            body = wlist3(makeatom(",",OPE),wcons(makeatom("call",COMP),
                            wcons(varC,cons(varE1,NIL))),
                                wcons(makeatom("maplist",COMP),
                                    wcons(varC,wcons(varE1s,NIL))));

            if(proceed(body,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);

    }
    else if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        save1 = wp;
        varC = makevariant();
        if(unify(arg1,varC) == YES &&
           unify(arg2,NIL) == YES &&
           unify(arg3,NIL) == YES)
            if(proceed(NIL,nest) == YES)
                return(YES);

        wp = save1;
        unbind(save2);
        varC = makevariant();
        varE1 = makevariant();
        varE1s = makevariant();
        varE2 = makevariant();
        varE2s = makevariant();

        if(unify(arg1,varC) == YES &&
           unify(arg2,wlistcons(varE1,varE1s)) == YES &&
           unify(arg3,wlistcons(varE2,varE2s)) == YES){
            body = wlist3(makeatom(",",OPE),wlistcons(makeatom("call",COMP),
                            wcons(varC,wcons(varE1,wcons(varE2,NIL)))),
                                wcons(makeatom("maplist",COMP),
                                    wcons(varC,wcons(varE1s,
                                        wcons(varE2s,NIL)))));

            if(proceed(body,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
    }
    else if(n == 4){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        arg4 = deref(goal[5]);

        save1 = wp;
        varC = makevariant();
        if(unify(arg1,varC) == YES &&
           unify(arg2,NIL) == YES &&
           unify(arg3,NIL) == YES &&
           unify(arg4,NIL) == YES)
            if(proceed(NIL,nest) == YES)
             return(YES);

        wp = save1;
        unbind(save2);

        save1 = wp;
        varC = makevariant();
        varE1 = makevariant();
        varE1s = makevariant();
        varE2 = makevariant();
        varE2s = makevariant();
        varE3 = makevariant();
        varE3s = makevariant();
        if(unify(arg1,varC) == YES &&
           unify(arg2,wlistcons(varE1,varE1s)) == YES &&
           unify(arg3,wlistcons(varE2,varE2s)) == YES &&
           unify(arg4,wlistcons(varE3,varE3s)) == YES){
            body = wlist3(makeatom(",",OPE),wlistcons(makeatom("call",COMP),
                            wcons(varC,
                                wcons(varE1,
                                    wcons(varE2,
                                        wcons(varE3,NIL))))),
                                            wcons(makeatom("maplist",COMP),
                                                wcons(varC,
                                                    wcons(varE1s,
                                                        wcons(varE2s,
                                                            wcons(varE3s,NIL))))));

            if(proceed(body,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
    }
    return(NO);
}

int b_succ(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"succ ", list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"succ ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"succ ",arg2);
        if(!wide_variable_p(arg1) && !wide_integer_p(arg1))
            error(NOT_INT,"succ ",arg1);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"succ ",arg2);
        if(wide_integer_p(arg1) && negativep(arg1))
            error(NOT_LESS_THAN_ZERO,"succ ",arg1);
        if(wide_integer_p(arg2) && negativep(arg2))
            error(NOT_LESS_THAN_ZERO,"succ ",arg2);

        if(wide_variable_p(arg1))
            return(unify(arg1,minus(arg2,makeint(1))));
        else if(wide_variable_p(arg2))
            return(unify(arg2,plus(arg1,makeint(1))));
        else
            return(unify(arg2,plus(arg1,makeint(1))));

    }
    return(NO);
}

int b_term_variables(int nest, int n){
    int arg1,arg2,lis,res;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        if(!wide_variable_p(arg2) && !listp(arg2))
            error(NOT_LIST,"term_variables ",arg2);

        lis = listreverse(term_variables(arg1,NIL));
        res = unify(lis,arg2);

        return(res);
    }
    return(NO);
}


int term_variables(int x, int y){
    int temp;

    if(nullp(x))
    	return(y);
    else if(numberp(x))
    	return(y);
    else if(wide_variable_p(x) && !memq(x,y)){
    	temp = cons(x,y);
        SET_AUX(temp,LIST);
        return(temp);
    }
    else if(singlep(x))
    	return(y);
    else if(car(x) == AND)
    	return(term_variables(caddr(x),term_variables(cadr(x),y)));
    else if(car(x) == OR)
    	return(term_variables(caddr(x),term_variables(cadr(x),y)));
    else if(car(x) == DEFINE)
        return(term_variables(caddr(x),term_variables(cadr(x),y)));
    else
    	return(term_variables(caddr(x),term_variables(cadr(x),y)));
}

int b_callable(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(callablep(arg1))
            return(YES);
        else if(structurep(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);

}

int b_unify_with_occurs_check(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = goal[2];
        arg2 = goal[3];
        if(occursp(arg1,arg2))
            return(NO);
        return(unify(arg1,arg2));
    }
    return(NO);
}

int b_op(int nest, int n){
    int arg1,arg2,arg3,weight,type;

    if(n == 3){
        arg1 = deref(goal[2]); //priority
        arg2 = deref(goal[3]); //specifier
        arg3 = deref(goal[4]); //operator

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

int b_ask(int nest, int n){
    int x1,x2;
    char c;
    double end_time;

    if(n == 0){
        // if invoke from time/1 then print elapsed time
        if(time_flag){
            end_time = getETime();
            printf("Elapsed Time=%.6f (second)\n", end_time - time_flag);
            time_flag = 0;
        }
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
            numbervars_flag = 0;
            print(car(x2));
            printf(" = ");
            printanswer(deref(car(x2)));
            if(!nullp(cdr(x2)))
                printf("\n");
            x2 = cdr(x2);
        }

        fflush(stdout);
        FLUSH

        loop:
        c = getchar();
        if(c == '.'){
        	getchar();
            return(YES);
        }
        if(c == EOL){
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


int b_unify(int nest, int n){
    int arg1,arg2,res;

    if(n == 2){
        arg1 = goal[2];
        arg2 = goal[3];
        if(operationp(arg1) && car(arg1) == DOTOBJ)
            arg1 = operate(arg1);
        if(operationp(arg2) && car(arg2) == DOTOBJ)
            arg2 = operate(arg2);
        res = unify(arg1,arg2);
        return(res);
    }
    return(NO);
}

int b_notunify(int nest, int n){
    int arg1,arg2,res;

    if(n == 2){
        arg1 = goal[2];
        arg2 = goal[3];
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
int b_write(int nest, int n){
    int arg1,arg2,save;

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto write;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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
        numbervars_flag = 1;
        numbervars_top_pt = 0;
        print(arg2);
        fflush(GET_PORT(output_stream));
        quoted_flag = 1;
        numbervars_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_writeln(int nest, int n){
    int arg1,arg2,save;

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto write;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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
        numbervars_flag = 1;
        numbervars_top_pt = 0;
        print(arg2);
        fprintf(GET_PORT(output_stream),"\n");
        fflush(GET_PORT(output_stream));
        quoted_flag = 1;
        numbervars_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}


int b_write_term(int nest, int n){
    int arg1,arg2,arg3,save,var,variable_name_flag;

    if(n == 2){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        arg3 = deref(goal[3]);
        goto write_term;

    }
    else if(n == 3){
        arg1 = deref(goal[2]); //stream or alias
        arg2 = deref(goal[3]); //term
        arg3 = deref(goal[4]); //option

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"write_term ",arg1);
        if(!listp(arg3))
            error(NOT_LIST,"write_term ",arg3);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"write_term ",arg1);



        write_term:
        save = output_stream;
        var = NIL;
        variable_name_flag = 0;

        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        quoted_flag = 0;
        ignore_flag = 0;
        numbervars_flag = 0;
        while(!nullp(arg3)){
            if(quoted_option_p(car(arg3))){
                if(cadr(car(arg3)) == makeconst("true"))
                    quoted_flag = 1;
            }
            else if(ignore_optin_p(car(arg3))){
                if(cadr(car(arg3)) == makeconst("true"))
                    ignore_flag = 1;
            }
            else if(numbervars_option_p(car(arg3))){
                if(cadr(car(arg3)) == makeconst("true"))
                    numbervars_flag = 1;
            }
            else if(variable_name_p(car(arg3))){
                variable_name_flag = 1;
                var = cadr(car(arg3));
            }
            else if(wide_variable_p(car(arg3)))
                error(NOT_LIST,"write_term ",car(arg3));
            else
                error(NOT_WRITE_OPTION,"write_term ",car(arg3));

            arg3 = cdr(arg3);
        }

        if(!variable_name_flag)
            print(arg2);
        else{
            while(!nullp(var)){
                if(!eqp(car(car(var)),makeatom("=",SYS)))
                    error(NOT_WRITE_OPTION,"write_term ",car(var));
                unify(cadr(car(var)),caddr(car(var))); //e.g. 'A'=X
                variables = listremove(cadr(car(var)),variables);
                variables = listremove(caddr(car(var)),variables);
                var = cdr(var);
            }
            print(deref(arg2));
        }
        output_stream = save;
        quoted_flag = 1;
        ignore_flag = 0;
        numbervars_flag = 0;
        return(YES);
    }
    return(NO);
}

int quoted_option_p(int x){

    if(eqlp(car(x),makeconst("quoted")) &&
       eqlp(cadr(x),makeconst("true")) &&
       caddr(x) == NIL)
        return(1);
    else if(eqlp(car(x),makeconst("quoted")) &&
            eqlp(cadr(x),makeconst("false")) &&
            caddr(x) == NIL)
        return(1);
    else
        return(0);
}

int ignore_optin_p(int x){
    if(eqlp(car(x),makeconst("ignore_ops")) &&
       eqlp(cadr(x),makeconst("true")) &&
       caddr(x) == NIL)
        return(1);
    else if(eqlp(car(x),makeconst("ignore_ops")) &&
            eqlp(cadr(x),makeconst("false")) &&
            caddr(x) == NIL)
        return(1);
    else
        return(0);
}

int numbervars_option_p(int x){
    if(eqlp(car(x),makeconst("numbervars")) &&
       eqlp(cadr(x),makeconst("true")) &&
       caddr(x) == NIL)
        return(1);
    if(eqlp(car(x),makeconst("numbervars")) &&
       eqlp(cadr(x),makeconst("false")) &&
       caddr(x) == NIL)
        return(1);
    else
        return(0);
}

int b_write_canonical(int nest, int n){
    int arg1,arg2,save;

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto write_canonical;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
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

int b_writeq(int nest, int n){
    int arg1,arg2,save;

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto writeq;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
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
        numbervars_flag = 1;
        print(arg2);
        quoted_flag = 0;
        numbervars_flag = 0;
        output_stream = save;
        return(YES);
    }
    return(NO);
}


int b_nl(int nest, int n){
    int arg1,save;

    if(n == 0){
        fprintf(GET_PORT(output_stream),"\n");
        fflush(GET_PORT(output_stream));
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(goal[2]);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        fprintf(GET_PORT(output_stream),"\n");
        fflush(GET_PORT(output_stream));
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_put(int nest, int n){
    int arg1;
    if(n == 1){
        arg1 = deref(goal[2]);
        if(!integerp(arg1))
            error(NOT_INT,"put",arg1);
        fprintf(GET_PORT(output_stream), "%c", (char)GET_INT(arg1));
        return(YES);
    }
    return(NO);
}

int b_get0(int nest, int n){
#ifdef _WIN32
    int arg1,i,res;
    char c;
#elif __linux
    int c,arg1,i,res;
#elif __OpenBSD__
    int c,arg1,i,res;
#endif

    if(n == 1){
        arg1 = deref(goal[2]);
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

int b_get(int nest, int n){
#ifdef _WIN32
    int arg1,i,res;
    char c;
#elif __linux
    int c,arg1,i,res;
#elif __OpenBSD__
    int c,arg1,i,res;
#endif

    if(n == 1){
        arg1 = deref(goal[2]);

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


int b_get_char(int nest, int n){
#if _WIN32
    int arg1,arg2,res;
    char c,str[10];
#elif __linux
    int c,arg1,arg2,res;
    char str[10];
#elif __OpenBSD__
    int c,arg1,arg2,res;
    char str[10];
#endif

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto get_char;
    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        get_char:

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_char ",arg1);
        if(!wide_variable_p(arg2) && !characterp(arg2))
            error(NOT_CHAR,"get_char ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_char ",arg1);


        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);

        c = getc(GET_PORT(arg1));

        str[0] = c;
        str[1] = NUL;
        if(mode_flag == 0 && iskanji(c)){
            c = getc(GET_PORT(arg1));
            str[1] = c;
            str[2] = NUL;
        }
        else if(mode_flag == 1 && isUni2(c)){
            c = getc(GET_PORT(arg1));
            str[1] = c;
            str[2] = NUL;
        }
        else if(mode_flag == 1 && isUni3(c)){
            c = getc(GET_PORT(arg1));
            str[1] = c;
            c = getc(GET_PORT(arg1));
            str[2] = c;
            str[3] = NUL;
        }
        else if(mode_flag == 1 && isUni4(c)){
            c = getc(GET_PORT(arg1));
            str[1] = c;
            c = getc(GET_PORT(arg1));
            str[2] = c;
            c = getc(GET_PORT(arg1));
            str[3] = c;
            str[4] = NUL;
        }
        else if(mode_flag == 1 && isUni5(c)){
            c = getc(GET_PORT(arg1));
            str[1] = c;
            c = getc(GET_PORT(arg1));
            str[2] = c;
            c = getc(GET_PORT(arg1));
            str[3] = c;
            c = getc(GET_PORT(arg1));
            str[4] = c;
            str[5] = NUL;
        }
        else if(mode_flag == 1 && isUni6(c)){
            c = getc(GET_PORT(arg1));
            str[1] = c;
            c = getc(GET_PORT(arg1));
            str[2] = c;
            c = getc(GET_PORT(arg1));
            str[3] = c;
            c = getc(GET_PORT(arg1));
            str[4] = c;
            c = getc(GET_PORT(arg1));
            str[5] = c;
            str[6] = NUL;
        }
        res = NIL;
        if(c == EOF){
            if(GET_TR(arg1) == 0){
                SET_TR(arg1,1);
                res = unify(arg2,FEND);
            }
            else{
                if(GET_AUX(arg1) == makeconst("error"))
                    error(PAST_EOF_INPUT,"get_char ",arg1);
                else if(GET_AUX(arg1) == makeconst("eof_code")){
                    SET_TR(arg1,0);
                    res = unify(arg2,FEND);
                }
                else{
                    SET_TR(arg1,0);
                    res = unify(arg2,FEND);
                }
            }
        }
        else{
            res = unify(arg2,makeconst(str));
        }
        return(res);
    }
    return(NO);
}

int b_get_code(int nest, int n){
    int arg1,arg2,c,i,res;
    char str[10];

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto get_code;
    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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
        if(c == EOF){
            if(GET_TR(arg1) == 0){
                SET_TR(arg1,1);
                res = unify(arg2,makeint(-1));
            }
            else{
                if(GET_AUX(arg1) == makeconst("error"))
                    error(PAST_EOF_INPUT,"get_code ",arg1);
                else if(GET_AUX(arg1) == makeconst("eof_code")){
                    SET_TR(arg1,0);
                    res = unify(arg2,makeint(-1));
                }
                else{
                    SET_TR(arg1,1);
                    res = unify(arg2,makeint(-1));
                }
            }
        }
        else{
            res = unify(arg2,makeint(i));
        }
        return(res);
    }
    return(NO);
}

int b_get_byte(int nest, int n){
    int arg1,arg2,c,res;

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto get_byte;
    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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

        res = NIL;
        if(c == EOF){
            if(GET_TR(arg1) == 0){
                SET_TR(arg1,1);
                res = unify(arg2,FEND);
            }
            else{
                if(GET_AUX(arg1) == makeconst("error"))
                    error(PAST_EOF_INPUT,"get_byte ",arg1);
                else if(GET_AUX(arg1) == makeconst("eof_code"))
                    res = unify(arg2,FEND);

            }
        }
        else{
            res = unify(arg2,makeint(c));
        }
        return(res);
    }
    return(NO);
}

int b_peek_byte(int nest, int n){
    int arg1,arg2,c,res;

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto get_byte;
    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        get_byte:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"peek_byte ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"peek_byte ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"peek_byte ",arg1);

        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        c = fgetc(GET_PORT(arg1));
        ungetc(c,GET_PORT(arg1));

        res = NIL;
        if(c == EOF){
            if(GET_TR(arg1) == 0){
                SET_TR(arg1,1);
                res = unify(arg2,makeint(26)); //0x1A ctrl+Z ascii code
            }
            else{
                if(GET_AUX(arg1) == makeconst("error"))
                    error(PAST_EOF_INPUT,"peek_byte ",arg1);
                else if(GET_AUX(arg1) == makeconst("eof_code"))
                    res = unify(arg2,FEND);

            }
        }
        else{
            res = unify(arg2,makeint(c));
        }
        return(res);
    }
    return(NO);
}


int b_put_char(int nest, int n){
    int arg1,arg2,save;

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto put_char;
    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        put_char:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_char ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"get_char ",arg2);
        if(!wide_variable_p(arg2) && !characterp(arg2))
            error(NOT_CHAR,"get_char ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_char ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        print(arg2);
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_put_code(int nest, int n){
    int arg1,arg2,save;
    char str[10];

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto put_code;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        put_code:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_code ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"get_code ",arg2);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_CHAR,"get_code ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_code ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        str[0] = GET_INT(arg2);
        str[1] = NUL;
        print(makeconst(str));
        output_stream = save;
        return(YES);
    }
    return(NO);
}

int b_put_byte(int nest, int n){
    int arg1,arg2,save;

    if(n == 1){
        arg1 = output_stream;
        arg2 = deref(goal[2]);
        goto put_byte;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        put_byte:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"get_byte ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"get_byte ",arg2);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_CHAR,"get_byte ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"get_byte ",arg1);

        save = output_stream;
        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        fputc(GET_INT(arg2),GET_PORT(output_stream));
        output_stream = save;
        return(YES);
    }
    return(NO);
}


int b_tab(int nest, int n){
    int arg1,count;

    if(n == 1){
        arg1 = deref(goal[2]);
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

//unfinished
int b_read_term(int nest, int n){
    int arg1,arg2,arg3,original,copy,save,res,
        variable_name_flag,var,singleton_flag,var1;

    if(n == 2){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        arg3 = deref(goal[3]);
        goto read_term;

    }
    else if(n == 3){
        arg1 = deref(goal[2]); //stream
        arg2 = deref(goal[3]); //term
        arg3 = deref(goal[4]); //option
        read_term:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"read_term ",arg1);
        if(listp(arg3) && length(arg3) == -1)
            error(INSTANTATION_ERR,"read_term ",arg3);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"read_term ",arg1);
        if(!listp(arg3) && !nullp(arg3))
            error(NOT_LIST,"read_term ",arg3);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"read_term ", arg1);

        var = NIL;
        var1 = NIL;
        copy = NIL;
        while(!nullp(arg3)){
            if(variable_name_p(car(arg3))){
                variable_name_flag = 1;
                var = cadr(car(arg3));
            }
            else if(singletonp(car(arg3))){
                singleton_flag = 1;
                var1 = cadr(car(arg3));
            }
            else if(wide_variable_p(car(arg3)))
                error(INSTANTATION_ERR,"read_term ",car(arg3));
            else
                error(NOT_READ_OPTION,"read_term ",car(arg3));

            arg3 = cdr(arg3);
        }
        save = input_stream;
        if(aliasp(arg1))
            input_stream = GET_CAR(arg1);
        else
            input_stream = arg1;
        original = variable_to_call(parser(NIL,NIL,NIL,NIL,0,0));
        if(original == FEND){
            if(GET_AUX(input_stream) == makeconst("error") &&
               GET_TR(input_stream) == 1)
                error(EOF_ERROR,"read_term",NIL);
            SET_TR(input_stream,1); // for at_end_of_stream
            res = unify(arg2,original);
        }
        else if(variable_name_flag || singleton_flag){
            numbervars_base_pt = numbervars_top_pt;
            print(original);
            copy = copy_term(original);
            res = unify(arg2,copy);
            if(variable_name_flag)
                unify(var,variable_name_list());
            if(singleton_flag)
                unify(var1,singleton_list());
        }
        else
            res = unify(arg2,copy);


        input_stream = save;
        return(res);
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

// for read_term  e.g ['X'=_0001,'Y'=_0002]
// copy_term generate numbervars array.
// That array has relation data symbol,numbervar,count
int variable_name_list(void){
    int i,res,temp;

    res = NIL;
    for(i=numbervars_top_pt-1;i>=numbervars_base_pt;i--){
        temp = makecopy(numbervars[i][0]); //e.g. X -> 'X'
        res = listcons(list3(makeatom("=",SYS),temp,numbervars[i][1]),res);
    }
    return(res);
}


// for read_term singleton option e.g ['X'=_0001,'Y'=_0002]
// similer to variable_names but variable that appear only once
int singleton_list(void){
    int i,res,temp;

    res = NIL;
    for(i=numbervars_top_pt-1;i>=numbervars_base_pt;i--){
        if(numbervars[i][2] == 1){ //count == 1
            temp = makecopy(numbervars[i][0]); //e.g. X -> 'X'
            res = listcons(list3(makeatom("=",SYS),temp,numbervars[i][1]),res);
        }
    }
    return(res);
}

int b_read(int nest, int n){
    int arg1,arg2,save,temp,res;

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto read;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
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
            if(GET_AUX(input_stream) == makeconst("error") &&
               GET_TR(input_stream) == 1)
                error(EOF_ERROR,"read ",NIL);
            else
                temp = GET_AUX(input_stream);
            SET_TR(input_stream,1); //for at_end_of_stream;
        }
        res = unify(arg2,temp);
        input_stream = save;
        return(res);
    }
    return(NO);
}

int b_read_item(int nest, int n){
    int arg1,arg2,save,temp,res;

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto read;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        read:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"read_item ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"read_item ",arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"read_item ", arg1);
        save = input_stream;
        if(aliasp(arg1))
            input_stream = GET_CAR(arg1);
        else
            input_stream = arg1;

        temp = readitem();
        if(operatorp(temp))
            temp = makeconst(GET_NAME(temp)); //e.g.  (,) -> ','
        if(temp == FEND){
            if(GET_AUX(input_stream) == makeconst("error") &&
               GET_TR(input_stream) == 1)
                error(EOF_ERROR,"read_item",NIL);
            else
                temp = GET_AUX(input_stream);

            SET_TR(input_stream,1); //for at_end_of_stream;
        }
        res = unify(arg2,temp);
        input_stream = save;
        return(res);
    }
    return(NO);
}

int b_read_token(int nest, int n){
    int arg1,arg2,save,temp,res;
    char *e;

    if(n == 1){
        arg1 = input_stream;
        arg2 = deref(goal[2]);
        goto read;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        read:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"read_token ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"read_token ",arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"read_token ", arg1);
        save = input_stream;
        if(aliasp(arg1))
            input_stream = GET_CAR(arg1);
        else
            input_stream = arg1;

        gettoken();
        switch(stok.type){
            case PERIOD:    temp = makeconst("."); break;
            case COMMA:     temp = makeconst(","); break;
            case SEMICOLON: temp = makeconst(";"); break;
            case LPAREN:    temp = makeconst("("); break;
            case RPAREN:    temp = makeconst(")"); break;
            case LCURL:     temp = makeconst("{"); break;
            case RCURL:     temp = makeconst("}"); break;
            case LBRACKET:  temp = makeconst("["); break;
            case RBRACKET:  temp = makeconst("]"); break;
            case VERTICAL:  temp = makeconst("|"); break;
            case INTEGER:   temp = makeint(atoi(stok.buf)); break;
            case OCTNUM:    if(strtol(stok.buf,&e,8) < 1000000000)
                                temp = makeint(strtol(stok.buf,&e,8));
                            else
                                temp = makeoctbigx(stok.buf);
                            break;
            case BINNUM:    if(strtol(stok.buf,&e,2) < 1000000000)
                                temp = makeint(strtol(stok.buf,&e,2));
                            else
                                temp = makebinbigx(stok.buf);
                            break;
            case HEXNUM:    if(strtol(stok.buf,&e,16) < 1000000000)
                                temp = makeint(strtol(stok.buf,&e,16));
                            else
                                temp = makehexbigx(stok.buf);
                            break;
            case FLOATN:    temp = makeflt(atof(stok.buf)); break;
            case BIGNUM:    temp = makebigx(stok.buf); break;
            case CHARCODE:  temp = makeint(stok.buf[0]); break;
            case STRING:    temp = makestr(stok.buf); break;
            case FILEEND:   temp = FEND; break;
            default:        temp = makeconst(stok.buf); break;
        }

        if(temp == FEND){
            if(GET_AUX(input_stream) == makeconst("error") &&
               GET_TR(input_stream) == 1)
                error(EOF_ERROR,"read_token ",NIL);
            else
                temp = GET_AUX(input_stream);

            SET_TR(input_stream,1); //for at_end_of_stream;
        }
        res = unify(arg2,temp);
        input_stream = save;
        return(res);
    }
    return(NO);
}


int b_stream_property(int nest, int n){
    int arg1,arg2,prop,res,save1,save2,save3;
    fpos_t pos;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        if(!streamp(arg1) && !aliasp(arg1) && !wide_variable_p(arg1))
            error(NOT_STREAM,"stream_property ",arg1);


        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);

        if(wide_variable_p(arg2))
            goto var;

        res = NIL;
        if(car(arg2) == makeconst("file_name")){
            res = unify(cadr(arg2),GET_CDR(arg1));
        }
        else if(car(arg2) == makeconst("line_number")){
            res = unify(cadr(arg2),makeint(line));
        }
        else if(mode_option_p(arg2)){
            if(GET_OPT(arg1) == OPL_INPUT)
                res = unify(cadr(arg2),makeatom("read",SYS));
            else if(GET_OPT(arg1) ==OPL_OUTPUT)
                res = unify(cadr(arg2),makeatom("write",SYS));
        }
        else if(type_option_p(arg2)){
            if(GET_VAR(arg1) == OPL_TEXT)
                res = unify(cadr(arg2),makeconst("text"));
            else if(GET_VAR(arg1) == OPL_BINARY)
                res = unify(cadr(arg2),makeconst("binary"));
        }
        else if(alias_option_p(arg2)){
            if(wide_variable_p(arg1))
                res = unify(arg1,GET_CAR(cadr(arg2)));
            else
                res = unify(cadr(arg2),GET_CDR(arg1));
        }
        else if(position_option_p(arg2)){
            res = unify(cadr(arg2),makeint(fgetpos(GET_PORT(arg1), &pos)));
        }
        else if(reposition_option_p(arg2)){
            res = unify(cadr(arg2),GET_LENGTH(arg1));
        }
        else if(eof_action_option_p(arg2)){
            res = unify(cadr(arg2),GET_AUX(arg1));
        }

        if(res == YES){
            if(resolve_all(save3,sp,nest+1) == YES)
                return(YES);
            else
                goto exit;
        }
        var:
        prop = 0;
        while(prop < 8){
            switch(prop){
                case 0: unify(arg2,list2(makepred("file_name"),GET_CDR(arg1)));
                case 1: unify(arg2,list2(makepred("line_number"),makeint(line)));
                case 2: if(GET_OPT(arg1) == OPL_INPUT)
                            unify(arg2,list2(makepred("mode"),makeatom("read",SYS)));
                        else if(GET_OPT(arg1) ==OPL_OUTPUT)
                            unify(arg2,list2(makepred("mode"),makeatom("write",SYS)));
                case 3: if(GET_VAR(arg1) == OPL_TEXT)
                            unify(arg2,list2(makepred("type"),makeconst("text")));
                        else if(GET_VAR(arg1) == OPL_BINARY)
                            unify(arg2,list2(makepred("type"),makeconst("binary")));
                case 4: if(!nullp(GET_CDR(arg1)))
                            unify(arg2,list2(makepred("alias"),GET_CDR(arg1)));
                        else
                            unify(arg2,list2(makepred("alias"),OPLFALSE));
                case 5: unify(arg2,list2(makepred("position"),makeint(fgetpos(GET_PORT(arg1), &pos))));
                case 6: if(!nullp(GET_LENGTH(arg1)))
                            unify(arg2,list2(makepred("reposition"),OPLTRUE));
                        else
                            unify(arg2,list2(makepred("reposition"),OPLFALSE));
                case 7: if(!nullp(GET_AUX(arg1)))
                            unify(arg2,list2(makepred("eof_action"),OPLTRUE));
                        else
                            unify(arg2,list2(makepred("eof_action"),OPLFALSE));
            }
            if(resolve_all(save3,sp,nest+1) == YES)
                return(YES);

            tp = save1;
            unbind(save2);
            trail_end = save3;
            prop++;
        }
        exit:
        tp = save1;
        unbind(save2);
        trail_end = save3;
        return(NO);
    }
    return(NO);
}

int b_open(int nest, int n){
    int arg1,arg2,arg3,arg4,type,name,action,stream,repos;
    FILE *fp;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        arg4 = NIL;
        goto open;
    }
    if(n == 4){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        arg4 = deref(goal[5]);

        open:
        if(variablep(arg1) || anoymousp(arg1))
            error(INSTANTATION_ERR,"open ",arg1);
        if(!!structurep(arg1))
            error(NOT_SOURCE,"open ",arg1);
        if(variablep(arg2) || anoymousp(arg2))
            error(INSTANTATION_ERR,"open ",arg2);
        if(length(arg4) == -1) //improper_list
            error(NOT_LIST,"open ",arg4);
        if(!builtinp(arg2) && !!structurep(arg2))
            error(NOT_ATOM,"open ",arg2);
        if(!wide_variable_p(arg3))
            error(NOT_VAR,"open ",arg3);
        if(!listp(arg4) && !nullp(arg4))
            error(NOT_LIST,"open ",arg4);

        type = 1;
        name = NIL;
        action = makeconst("error");
        stream = NIL;
        repos = NO;
        while(!nullp(arg4)){
            if(type_option_p(car(arg4)) &&
               eqlp(cadr(car(arg4)),makeconst("text")))
                type = 1; // text
            else if(type_option_p(car(arg4)) &&
                    eqlp(cadr(car(arg4)),makeconst("binary")))
                type = 2; //binary
            else if(reposition_option_p(car(arg4)))
                repos = cadr(car(arg4));
            else if(alias_option_p(car(arg4))){
                name = cadr(car(arg4)); //alias(Name)
            }
            else if(eof_action_option_p(car(arg4)))
                action = cadr(car(arg4));
            else if(variablep(car(arg4)) || anoymousp(car(arg4)))
                error(INSTANTATION_ERR,"open ",car(arg4));
            else
                error(NOT_STREAM_OPTION,"open ",car(arg4));
            arg4 = cdr(arg4);
        }
        if(eqlp(arg2,makeconst("read")) && type == 1){
            fp = fopen(GET_NAME(arg1),"r");
            if(fp == NULL)
                error(EXISTENCE_ERR,"open ",arg1);
            stream = makestream(fp,OPL_INPUT,OPL_TEXT,action,arg1);
            SET_LENGTH(stream,repos);
            unify(arg3,stream);
        }
        else if(eqlp(arg2,makeconst("read")) && type == 2){
            fp = fopen(GET_NAME(arg1),"rb");
            if(fp == NULL)
                error(EXISTENCE_ERR,"open ",arg1);
            stream = makestream(fp,OPL_INPUT,OPL_TEXT,action,arg1);
            //SET_CDR(stream,name);
            SET_LENGTH(stream,repos);
            unify(arg3,stream);
        }
        else if(eqlp(arg2,makeconst("write")) && type == 1){
            stream = makestream(fopen(GET_NAME(arg1),"w"),OPL_OUTPUT,OPL_TEXT,action,arg1);
            SET_LENGTH(stream,repos);
            unify(arg3,stream);
        }
        else if(eqlp(arg2,makeconst("write")) && type == 2){
            stream = makestream(fopen(GET_NAME(arg1),"wb"),OPL_OUTPUT,OPL_TEXT,action,arg1);
            SET_LENGTH(stream,repos);
            unify(arg3,stream);
        }
        else if(eqlp(arg2,makeconst("append")) && type == 1){
            stream = makestream(fopen(GET_NAME(arg1),"a"),OPL_OUTPUT,OPL_TEXT,action,arg1);
            SET_LENGTH(stream,repos);
            unify(arg3,stream);
        }
        else if(eqlp(arg2,makeconst("append")) && type == 2){
            stream = makestream(fopen(GET_NAME(arg1),"ab"),OPL_OUTPUT,OPL_TEXT,action,arg1);
            SET_LENGTH(stream,repos);
            unify(arg3,stream);
        }
        else
            error(NOT_IO_MODE,"open ",car(arg2));

        //make alias
        if(name != NIL){
            SET_CAR(name,stream);
            SET_AUX(name,SIMP);
        }
        line = 0;
        column = 0;
        return(YES);
    }
    return(NO);
}

int mode_option_p(int x){
    if(eqlp(car(x),makeconst("mode")) &&
       singlep(cadr(x)) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}

int type_option_p(int x){
    if(eqlp(car(x),makeconst("type")) &&
       singlep(cadr(x)) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}


int alias_option_p(int x){
    if(eqlp(car(x),makeconst("alias")) &&
       singlep(cadr(x)) &&
       nullp(cddr(x))){
        if(GET_AUX(cadr(x)) == PRED ||
           GET_AUX(cadr(x)) == SYS ||
           GET_AUX(cadr(x)) == PRED)
            error(ILLEGAL_ARGS,"alias",cadr(x));
        return(1);
       }
    else
        return(0);
}

int position_option_p(int x){
    if(eqlp(car(x),makeconst("position")) &&
       singlep(cadr(x)) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}

int reposition_option_p(int x){
    if(eqlp(car(x),makeconst("reposition")) &&
       singlep(cadr(x)) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}


int eof_action_option_p(int x){
    if(eqlp(car(x),makeconst("eof_action")) &&
       singlep(cadr(x)) &&
       nullp(cddr(x))){
       if(GET_AUX(cadr(x)) == PRED ||
           GET_AUX(cadr(x)) == SYS ||
           GET_AUX(cadr(x)) == COMP)
            error(ILLEGAL_ARGS,"alias",cadr(x));
        return(1);
    }
    else
        return(0);
}

int b_close(int nest, int n){
    int arg1,arg2,type,res;

    if(n == 1){
        arg1 = deref(goal[2]);
        arg2 = NIL;
        goto close;

    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        close:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"close ",arg1);
        if(!listp(arg2) && !nullp(arg2))
            error(NOT_LIST,"close ",arg2);
        if(length(arg2) == -1) //partial list
            error(NOT_LIST,"close ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"close ",arg1);

        type = 0;
        while(!nullp(arg2)){
            if(forcefalsep(car(arg2)))
                type = 1; //force(false)
            else if(forcetruep(car(arg2)))
                type = 2; //force(true)
            else if(variablep(car(arg2)))
                error(INSTANTATION_ERR,"close",car(arg2));
            else
                error(NOT_CLOSE_OPTION,"close",car(arg2));

            arg2 = cdr(arg2);
        }
        if(arg1 == standard_input || arg1 == standard_output)
            return(YES);
        else if(type == 1 || type == 2){
            if(aliasp(arg1) && GET_CDR(arg1) == NORMAL){
                res = fclose(GET_PORT(GET_CAR(arg1)));
                SET_AUX(arg1,NIL);
                if(res == EOF && type ==1) //fail close
                    error(EXISTENCE_ERR,"close ",arg2);
            }
            else
                fclose(GET_PORT(arg1));
        }
        else
            fclose(GET_PORT(arg1));

        return(YES);
    }
    return(NO);
}

int forcefalsep(int x){
    if(eqlp(car(x),makeconst("force")) &&
       eqlp(cadr(x),makeconst("false")) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}

int forcetruep(int x){
    if(eqlp(car(x),makeconst("force")) &&
       eqlp(cadr(x),makeconst("true")) &&
       nullp(cddr(x)))
        return(1);
    else
        return(0);
}

int b_see(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
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

int b_seen(int nest, int n){
    if(n == 0){
        if(input_stream != standard_input){
            fclose(GET_PORT(input_stream));
            input_stream = standard_input;
        }
        return(YES);
    }
    return(NO);
}

int b_tell(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
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

int b_told(int nest, int n){
    if(n == 0){
        if(output_stream != standard_output){
            fclose(GET_PORT(output_stream));
            output_stream = standard_output;
        }
        return(YES);
    }
    return(NO);
}

int b_current_input(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(!wide_variable_p(arg1) && !streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"current_input ",arg1);
        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        return(unify(arg1,input_stream));
    }
    return(NO);
}

int b_current_output(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(!wide_variable_p(arg1) && !streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"current_output ",arg1);
        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        return(unify(arg1,output_stream));
    }
    return(NO);
}

int b_set_input(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"set_intput", arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"set_intput ", arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"set_input ", arg1);
        if(aliasp(arg1) && GET_OPT(car(arg1)) == OPL_OUTPUT)
            error(NOT_INPUT_STREAM,"set_input ", arg1);

        if(aliasp(arg1))
            input_stream = GET_CAR(arg1);
        else
            input_stream = arg1;
        return(YES);
    }
    return(NO);
}

int b_set_output(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"set_output", arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"set_output ", arg1);
        if(streamp(arg1) && GET_OPT(arg1) == OPL_INPUT)
            error(NOT_OUTPUT_STREAM,"set_output ", arg1);
        if(aliasp(arg1) && GET_OPT(car(arg1)) == OPL_INPUT)
            error(NOT_OUTPUT_STREAM,"set_output ", arg1);

        if(aliasp(arg1))
            output_stream = GET_CAR(arg1);
        else
            output_stream = arg1;
        return(YES);
    }
    return(NO);
}

int b_flush_output(int nest, int n){
    int arg1;

    if(n == 0){
        fflush(stdout);
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(goal[2]);
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

int b_at_end_of_stream(int nest, int n){
    int arg1;

    if(n == 0){
        arg1 = input_stream;
        goto at_end_of_stream;
    }
    else if(n == 1){
        arg1 = deref(goal[2]);

        at_end_of_stream:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"at_end_of_stream ",arg1);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"at_end_of_stream ",arg1);

        if(aliasp(arg1))
            arg1 = GET_CAR(arg1);
        if(GET_TR(arg1) == 1)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_set_stream_position(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"set_stream_position ",arg1);
        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"set_stream_position ",arg2);
        if(!streamp(arg1) && !aliasp(arg1))
            error(NOT_STREAM,"set_stream_position ",arg1);
        if(!integerp(arg2))
            error(NOT_INT,"set_stream_position",arg2);

        fseek(GET_PORT(arg1),GET_INT(arg2),SEEK_CUR);
        return(YES);
    }
    return(NO);
}


int b_consult(int nest, int n){
    int arg1,clause,save,atom,arity,temp;
    char str[STRSIZE];

    if(n == 1){
        arg1 = deref(goal[2]);
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
        contiguous_list = NIL;
        atom = NIL;
        arity = 0;
        SET_CDR(atom,NIL);
        while(1){
            clause = variable_to_call(parser(NIL,NIL,NIL,NIL,0,0));
            if(predicatep(clause)){
                if(atomp(clause))
                    arity = 0;
                else
                    arity = length(cdr(clause));

                if(module_name == NIL){
                    if(atomp(clause))
                        atom = clause;  // ex foo
                    else
                        atom = car(clause); // ex foo(x).
                }
                else{
                    if(atomp(clause))
                        atom = add_prefix(clause);
                    else
                        atom = add_prefix(car(clause)); // ex modulename_a(x)
                }

                if(!memq(makeint(length(cdr(clause))),GET_CDR(atom)))
                	SET_CDR(atom,cons(makeint(length(cdr(clause))),GET_CDR(atom)));
            }
            else if(clausep(clause)){
                if(!nullp(caddr(clause))){
                    if(atomp(cadr(clause)))
                        arity = 0;
                    else
                        arity = length(cdr(cadr(clause)));

                    if(module_name == NIL){
                        if(atomp(cadr(clause)))
                            atom = cadr(clause);
                        else
                            atom = car(cadr(clause));
                    }
                    else{
                        if(atomp(cadr(clause)))
                            atom = add_prefix(cadr(clause));
                        else
                            atom = add_prefix(car(cadr(clause)));
                    }
                }
            }
            if(!nullp(atom) && !memq(atom,reconsult_list)){
                reconsult_list = cons(atom,reconsult_list);
            }
            //contiguous check
            temp = list3(makeatom("/",OPE),atom,makeint(arity));
            if(!memberp(temp,contiguous_list))
                contiguous_list= cons(temp,contiguous_list);
            if(memberp(temp,cdr(contiguous_list)))
                error(DISCONTIGUOUS,"consult ",atom);

            if(clause == FEND)
                break;
            execute(clause);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;

        exit:
        while(!nullp(init_list)){
            arg1 = car(init_list);
            arg1 = list2(makeatom("?-",OPE),arg1);
            execute(arg1);
            init_list = cdr(init_list);
        }
        return(YES);
    }
    return(NO);
}


int b_reconsult(int nest, int n){
    int arg1,clause,save,atom,arity,temp;
    char str[STRSIZE];

    if(n == 1){
        arg1 = deref(goal[2]);
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
        contiguous_list = NIL;
        atom = NIL;
        arity = 0;
        SET_CDR(atom,NIL);
        define_list = NIL;
        include_list = NIL;
        option_list = NIL;
        global_list = NIL;
        execute_list = NIL;
        while(1){
            clause = variable_to_call(parser(NIL,NIL,NIL,NIL,0,0));
            if(clause == FEND)
                break;

            if(predicatep(clause)){
                if(atomp(clause))
                    arity = 0;
                else
                    arity = length(cdr(clause));

                if(module_name == NIL){
                    if(atomp(clause))
                        atom = clause;  // ex foo
                    else
                        atom = car(clause); // ex foo(x).
                }
                else{
                    if(atomp(clause))
                        if(export_check(clause))
                            atom = clause;
                        else
                            atom = add_prefix(clause);
                    else
                        if(export_check(clause))
                            atom = car(clause);
                        else
                            atom = add_prefix(car(clause)); // ex modulename_a(x)
                }
            }
            else if(clausep(clause)){
                if(!nullp(caddr(clause))){// ex a(x) :- b(x).
                    if(atomp(cadr(clause)))
                        arity = 0;
                    else
                        arity = length(cdr(cadr(clause)));

                    if(module_name == NIL){
                        if(atomp(cadr(clause))){
                            atom = makepred(GET_NAME(cadr(clause)));
                            clause = list3(car(clause),atom,caddr(clause));
                        }
                        else{
                            atom = car(cadr(clause));
                        }
                    }
                    else{
                        if(atomp(cadr(clause))){
                            if(export_check(cadr(clause)))
                                atom = cadr(clause);
                            else
                                atom = add_prefix(cadr(clause));
                        }
                        else{
                            if(export_check(cadr(clause)))
                                atom = car(cadr(clause));
                            else
                                atom = add_prefix(car(cadr(clause)));
                        }
                    }
                }
                else if(nullp(caddr(clause))){// ex :- b(X).
                    temp = cons(cadr(clause),execute_list);
                    SET_AUX(temp,LIST);
                	execute_list = temp;

                }
            }
            if(!nullp(atom) && !memq(atom,reconsult_list)){
                SET_CAR(atom,NIL);
                if(!infix_operator_p(atom))
                    SET_CDR(atom,NIL);
                temp = cons(atom,reconsult_list);
                SET_AUX(temp,LIST);
                reconsult_list = temp;
            }
            //memoize arity
            memoize_arity(clause,atom);

            //contiguous check
            temp = list3(makeatom("/",OPE),atom,makeint(arity));
            if(!memberp(temp,contiguous_list))
                contiguous_list= cons(temp,contiguous_list);
            if(memberp(temp,cdr(contiguous_list)))
                error(DISCONTIGUOUS,"consult ",atom);

            execute(clause);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;

        exit:
        while(!nullp(init_list)){
            arg1 = car(init_list);
            arg1 = list2(makeatom(":-",OPE),arg1);
            execute(arg1);
            init_list = cdr(init_list);
        }
        return(YES);
    }
    return(NO);
}

/*
 clause is predicate or clause
 atom is functor of clause. e.g. foo(X)->foo, foo(X) :- bar(X)->foo
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

int b_multifile(int nest, int n){
    int arg1;

    if(n == 2){
        arg1 = deref(goal[2]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"multifile ",arg1);
        if(!eqlp(car(arg1),makeatom("/",OPE)))
            error(PRED_INDICATOR,"multifile ",arg1);
        if(!atomp(cadr(arg1)))
            error(NOT_ATOM,"multifile ",cadr(arg1));
        if(!integerp(caddr(arg1)))
            error(NOT_INT,"multifile ",caddr(arg1));

        SET_OPT1(cadr(arg1),NO);
        arg1 = list3(car(arg1),makepred(GET_NAME(cadr(arg1))),caddr(arg1));
        if(!memberp(arg1,dynamic_list)){
            dynamic_list = listcons(arg1,dynamic_list);
        }
        return(YES);
    }
    return(NO);
}


int b_initialization(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        init_list = cons(arg1,init_list);
        return(YES);
    }
    return(NO);
}

int b_include(int nest, int n){
    int arg1,clause,save;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"include ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM, "include ", arg1);

        save = input_stream;
        input_stream = makestream(fopen(GET_NAME(arg1),"r"),OPL_INPUT,OPL_TEXT,NIL,arg1);

        if(GET_PORT(input_stream) == NULL)
            error(CANT_OPEN, "include", arg1);

        open_flag = 1;
        column = 0;
        while(1){
            clause = variable_to_call(parser(NIL,NIL,NIL,NIL,0,0));
            if(clause == FEND)
                break;
            execute(clause);
        }
        open_flag = 0;
        fclose(GET_PORT(input_stream));
        input_stream = save;
        return(YES);
    }
    return(NO);
}


int b_ensure_loaded(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(!memberp(arg1,load_list)){
        	load_list = cons(arg1,load_list);
        	b_consult(nest,n);
        }
        return(YES);
    }
    return(NO);
}

int b_use_module(int nest, int n){
	int arg1,filename;
    char str[ATOMSIZE];

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(!memberp(cadr(arg1),load_list)){
            memset(str,NUL,ATOMSIZE);
            strcpy(str,GET_NAME(car(arg1)));
            #if _WIN32
            strcat(str,"\\\\");
            #elif __linux
            strcat(str,"/");
            #elif __OpenBSD__
            strcat(str,"/");
            #endif
            strcat(str,GET_NAME(cadr(arg1)));
            strcat(str,".o");

            FILE* fp = fopen(str,"r");
            if(fp != NULL)
                fclose(fp);
            else{
                memset(str,NUL,ATOMSIZE);
                strcpy(str,GET_NAME(car(arg1)));
                #if _WIN32
                strcat(str,"\\\\");
                #elif __linux
                strcat(str,"/");
                #elif __OpenBSD__
                strcat(str,"/");
                #endif
                strcat(str,GET_NAME(cadr(arg1)));
                strcat(str,".pl");
            }
            filename = makeconst(str);
        	load_list = cons(cadr(arg1),load_list);
            goal[2] = filename;
        	b_consult(nest,n);
        }
        return(YES);
    }
    return(NO);
}



//arithmetic operation

int b_is(int nest, int n){
    int arg1,arg2,res;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"is ", arg2);

        arg2 = eval(arg2);
        res = unify(arg1,arg2);
        return(res);
    }
    return(NO);
}


int b_greater(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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

int b_smaller(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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

int b_eqsmaller(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
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

int b_eqgreater(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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

int b_numeq(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = eval(goal[2]);
        arg2 = eval(goal[3]);
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

int b_notnumeq(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = eval(goal[2]);
        arg2 = eval(goal[3]);
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

int b_equalp(int nest, int n){
    int arg1,arg2;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(anoymousp(arg1) && anoymousp(arg2))
            return(NO);
        else if(equalp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_notequalp(int nest, int n){
    int arg1,arg2;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(anoymousp(arg1) && anoymousp(arg2))
            return(YES);
        else if(!equalp(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}


//comparation of term
int b_compare(int nest, int n){
    int arg1,arg2,arg3;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
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


int b_atsmaller(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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


int b_ateqsmaller(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(ateqsmaller(arg1,arg2))
            return(YES);
        else
            return(NO);
    }
    error(UNDEF_PRED,"@=< ", makeint(n));
    return(NO);
}



int b_atgreater(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(!ateqsmaller(arg1,arg2))
            return(NO);
        else
            return(YES);
    }
    error(UNDEF_PRED,"@> ", makeint(n));
    return(NO);
}


int b_ateqgreater(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(atsmaller(arg1,arg2))
            return(NO);
        else
            return(YES);
    }
    error(UNDEF_PRED,"@>= ", makeint(n));
    return(NO);
}


//true fail
int b_fail(int nest, int n){
    if(n == 0){
        return(NO);
    }
    return(NO);
}

int b_call(int nest, int n){
    int arg1,save1,save2,temp;

    save2 = sp;
    if(n == 1){
        arg1 = deref(goal[2]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"call ",arg1);

        if(!callablep(arg1))
            error(NOT_CALLABLE,"call ",arg1);
        call:
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"call ",arg1);

        save1 = wp;
        if(arg1 == CUT){ //call(!) = true
            if(proceed(NIL,nest) == YES)
                return(YES);
        }
        else if(!has_cut_p(arg1)){
            if(proceed(arg1,nest) == YES)
                return(YES);

        }
        else{
            temp = before_cut(arg1);
            if(proceed(temp,NIL) == YES){
                temp = after_cut(arg1);
                if(proceed(temp,NIL) == YES){
                    if(proceed(NIL,nest) == YES)
                        return(YES);
                }
            }
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    else if(n > 1){
        temp = NIL;
        while(n > 1){
            temp = wcons(goal[n+1],temp);
            n--;
        }
        temp = deref(temp);
        arg1 = deref(goal[2]);
        if(structurep(arg1)){
            arg1 = append(arg1,temp);
        }
        else{
            arg1 = wcons(arg1,temp);
        }
        goto call;
    }
    return(NO);
}

int b_not(int nest, int n){
    int arg1,res,save1,save3;

    save1 = tp;
    save3 = trail_end;
    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"not ",arg1);
        if(!callablep(arg1))
            error(NOT_CALLABLE,"not ", arg1);

        res = NIL;
        if(arg1 == CUT)
            res = YES;
        else if(!has_cut_p(arg1)){
            save1 = tp;
            save3 = trail_end;
            set_length(arg1);
            save_trail(save1+10);  //save old trail 10
            push_trail_body1(arg1);
            res = resolve_all(save1,sp,nest+100); //to avoid duplicate nest
            tp = save1;
            retract_trail(save1+10); //retract old trail 10
            trail_end = save3;
        }
        else{
            if(proceed(before_cut(arg1),NIL) == YES)
                res = proceed(after_cut(arg1),NIL);
        }
        if(res == YES)
            return(NO);
        else
            return(YES);
    }
    return(NO);
}

int b_true(int nest, int n){
    if(n == 0){
        return(YES);
    }
    return(NO);
}


//database operation
int b_assert(int nest, int n){
    int arg1,atom;

    if(n == 1){
        arg1 = deref(goal[2]);
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
            if(atomp(arg1))
                atom = arg1;
            else
                atom = car(arg1);
            memoize_arity(arg1,atom);
            SET_VAR(arg1,unique(varslist(arg1)));
            set_length(arg1);
            add_data(car(arg1),arg1);
            return(YES);
        }
        else if(operationp(arg1)){
            if(!callablep(caddr(arg1)))
                error(NOT_CALLABLE,"assertz ",arg1);
            if(atomp(cadr(arg1)))
                atom = cadr(arg1);
            else
                atom = car(cadr(arg1));
            memoize_arity(arg1,atom);
            SET_VAR(arg1,unique(varslist(arg1)));
            set_length(arg1);
            operate(arg1);
            return(YES);
        }
        error(NOT_CALLABLE,"assertz",arg1);
    }
    return(NO);
}

int b_asserta(int nest, int n){
    int arg1,atom;
    if(n == 1){
        arg1 = deref(goal[2]);
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
            if(atomp(arg1))
                atom = arg1;
            else
                atom = car(arg1);
            memoize_arity(arg1,atom);
            SET_VAR(arg1,unique(varslist(arg1)));
            set_length(arg1);
            insert_data(car(arg1),arg1);
            return(YES);
        }
        else if(operationp(arg1)){
            if(!callablep(caddr(arg1)))
                error(NOT_CALLABLE,"asserta ",arg1);

            if(atomp(cadr(arg1)))
                atom = cadr(arg1);
            else
                atom = car(cadr(arg1));
            memoize_arity(arg1,atom);
            SET_VAR(arg1,unique(varslist(arg1)));
            set_length(arg1);
            assert_flag = 1;
            operate(arg1);
            assert_flag = 0;
            return(YES);
        }
        error(NOT_CALLABLE,"asserta",arg1);
    }
    return(NO);
}

int b_retract(int nest, int n){
    int arg1,clause,head,clauses,new_clauses,save1,save2;

    save2 = sp;
    clause = clauses = head = NIL;
    if(n == 1){
        arg1 = deref(goal[2]);
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

                if(proceed(NIL,nest) == YES)
                    return(YES);
                else
                    goto next;
            }
            new_clauses = cons(clause,new_clauses);
            next:
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        sp = save2;
        return(NO);
    }
    return(NO);
}


int b_retractall(int nest, int n){
    int arg1,clause,head,clauses,new_clauses,save1,save2;

    save1 = tp;
    save2 = sp;
    clause = clauses = head = NIL;
    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"retractall ",arg1);
        //if(operationp(arg1) && !predicatep(cadr(arg1)))
        //    error(NOT_CALLABLE,"retractall ",arg1);
        //if(!operationp(arg1) && !predicatep(arg1))
        //    error(NOT_CALLABLE,"retractall ",arg1);
        if(operationp(arg1) && builtinp(cadr(arg1)))
            error(BUILTIN_EXIST,"retractall ",arg1);
        if(!operationp(arg1) && builtinp(arg1))
            error(BUILTIN_EXIST,"retractall ",arg1);

        if(singlep(arg1)){
            arg1 = list1(arg1);
        }
        if(atom_predicate_p(arg1))
            clauses = GET_CAR(arg1);
        else if(predicatep(arg1))
            clauses = GET_CAR(car(arg1));

        new_clauses = NIL;
        while(!nullp(clauses)){
            clause = car(clauses);
            clauses = cdr(clauses);

            if(unify(arg1,clause) == YES)
                new_clauses = new_clauses;
            else
                new_clauses = cons(clause,new_clauses);

            tp = save1;
            unbind(save2);
        }
        if(atom_predicate_p(arg1)){
           SET_CAR(arg1,append(listreverse(new_clauses),clauses));
           if(GET_CAR(arg1) == NIL)
                SET_OPT1(arg1,NO);
        }
        else if(predicatep(arg1)){
            SET_CAR(car(arg1),append(listreverse(new_clauses),clauses));
            if(GET_CAR(car(arg1)) == NIL)
                SET_OPT1(car(arg1),NO);
        }
        else if(clausep(arg1) && atom_predicate_p(cadr(arg1))){
            SET_CAR(cadr(arg1),append(listreverse(new_clauses),clauses));
            if(GET_CAR(cadr(arg1)) == NIL)
                SET_OPT1(cadr(arg1),NO);
        }
        else if(clausep(arg1)){
            SET_CAR(car(cadr(arg1)),append(listreverse(new_clauses),clauses));
            if(GET_CAR(car(cadr(arg1))) == NIL)
                SET_OPT1(car(cadr(arg1)),NO);
        }
        tp = save1;
        sp = save2;
        return(YES);
    }
    return(NO);
}


int b_abolish(int nest, int n){
    int arg1,pred,clause,arity,clauses,new_clauses;

    clause = clauses = NIL;
    if(n == 1){
        arg1 = deref(goal[2]);

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

int b_clause(int nest, int n){
    int arg1,arg2,clause,clauses,save1,save2,copy;

    save2 = sp;
    if(n == 2){
        arg1 = deref(goal[2]); //head
        arg2 = deref(goal[3]); //body

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"clause ",arg1);
        if(!atom_predicate_p(arg1) && !predicatep(arg1))
            error(NOT_CALLABLE,"clause ",arg1);
        if(builtinp(arg1) || compiledp(arg1))
            error(BUILTIN_EXIST,"clause ",arg1);
        if(!wide_variable_p(arg2) && !callablep(arg2))
            error(NOT_CALLABLE,"clause ",arg2);

        if(atom_predicate_p(arg1))
            clauses = GET_CAR(arg1);
        else
            clauses = GET_CAR(car(arg1));

        save1 = wp;
        while(!nullp(clauses)){
            clause = car(clauses);
            clauses = cdr(clauses);
            copy = copy_term(clause);
            if(clausep(clause) && unify(arg1,cadr(copy)) == YES &&
                unify(arg2,caddr(copy)) == YES){
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            else if(predicatep(clause) && unify(arg1,copy) == YES &&
                unify(arg2,OPLTRUE) == YES){
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            wp = save1;
            unbind(save2);
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_current_predicate(int nest, int n){
    int arg1,save1,save2,predlist,pred,aritylist,arity;

    save2 = sp;
    if(n == 1){
        arg1 = deref(goal[2]);
        predlist = reverse(predicates);
        save1 = wp;
        while(!nullp(predlist)){
            pred = car(predlist);
            predlist = cdr(predlist);
            aritylist = GET_CDR(pred);
            while(!nullp(aritylist)){
                arity = car(aritylist);
                aritylist = cdr(aritylist);
                if(unify(arg1,list3(makeatom("/",OPE),pred,arity)) == YES)
                    if(proceed(NIL,nest) == YES)
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

int b_current_op(int nest, int n){
    int arg1,arg2,arg3,save1,save2,
        lis,weight,spec,op,w,s,o;

    save2 = sp;
    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        /*
        e.g. ',' ':-'  aux of operator is SIMP
        beclause of parsing. so change to OPE from SIMP
        */
        if(getatom(GET_NAME(arg3),OPE,hash(GET_NAME(arg3))))
            arg3 = makeatom(GET_NAME(arg3),OPE);

        lis = op_list;
        spec = NIL;
        save1 = wp;
        while(!nullp(lis)){
            weight = car(car(lis));
            spec = cadr(car(lis));
            op = caddr(car(lis));

            w= unify(arg1,weight);
            s = unify(arg2,spec);
            o = unify(arg3,op);
            if(w == YES && s == YES && o == YES)
                if(proceed(NIL,nest) == YES)
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

int b_current_module(int nest, int n){
    int arg1,i,save1,save2;

    save2 = sp;
    if(n == 1){
        arg1 = deref(goal[2]);

        i = 0;
        save1 = wp;
        while(i<module_pt){
            unify(arg1,module[i][0]);
            if(proceed(NIL,nest) == YES)
                return(YES);

            wp = save1;
            unbind(save2);
            i++;
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_current_visible(int nest, int n){
    int arg1,arg2,save1,save2,i,lis;

    save2 = sp;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        i=0;
        save1 = wp;
        while(i<module_pt){
            if(unify(arg2,module[i][0]) == YES){
                lis = module[i][1];
                while(!nullp(lis)){
                    if(unify(arg1,(car(lis))) == YES){
                        if(proceed(NIL,nest) == YES)
                            return(YES);
                    }
                    wp = save1;
                    unbind(save2);
                    lis = cdr(lis);
                }
            }
            wp = save1;
            unbind(save2);
            i++;
        }
    }
    return(NO);
}

int b_current_prolog_flag(int nest, int n){
    int arg1,arg2,save1,save2,lis;

    save2 = sp;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        lis = flag_list;
        save1 = wp;
        while(!nullp(lis)){
            if(unify(arg1,(car(car(lis)))) == YES){
                unify(arg2,(cdr(car(lis))));
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            wp = save1;
            unbind(save2);
            lis = cdr(lis);
        }
        tp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

//controle
int b_cut(int nest, int n){
    if(n == 0){
        return(YES);
    }
    return(NO);
}

int b_ifthen(int nest, int n){
    int arg1,arg2,save1,save2,save3;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        if(variablep(arg1))
            error(INSTANTATION_ERR,"-> ",arg1);
        if(variablep(arg2))
            error(INSTANTATION_ERR,"-> ",arg2);

        push_trail_body1(arg1);
        if(resolve_all(save1,sp,nest+3) == YES){
            tp = save1;
            if(!has_cut_p(arg2)){
                push_trail_body1(arg2);
                if(resolve_all(save1,sp,nest+4) == YES)
                    return(resolve_all(save3,sp,nest+1));
                else{
                    tp = save1;
                    sp = save2;
                    unbind(save2);
                    trail_end = save3;
                    return(NO);
                }
            }
            else{
                cut_flag = 1;
                push_trail_body1(before_cut(arg2));
                if(resolve_all(save3,sp,nest+3) ==YES){
                    push_trail_body1(after_cut(arg2));
                    return(resolve_all(save3,sp,nest+1));
                }
            }
          }
          else{
              tp = save1;
              sp = save2;
              unbind(save2);
              trail_end = save3;
              return(NO);
          }
    }
    return(NO);
}

int b_comp_ifthen(int nest, int n){
    int arg1,arg2,arg3,arg4,save1,save2;

    save1 = wp;
    save2 = sp;
    if(n == 4){
        arg1 = deref(goal[2]);  //if
        arg2 = deref(goal[3]);  //if cut or NIL
        arg3 = deref(goal[4]);  //then
        arg4 = deref(goal[5]);  //then cut or NIL

        if(nullp(arg2)){
            if(proceed(arg1,NIL) == YES){
                if(nullp(arg4)){
                    if(proceed(arg3,nest) == YES)
                        return(YES);
                }
                else{
                    if(proceed(arg3,NIL) == YES)
                        if(proceed(arg4,nest) == YES)
                            return(YES);
                }
            }
        }
        else{
            if(proceed(arg1,NIL) == YES){
                if(proceed(arg2,NIL) == YES){
                    if(nullp(arg4)){
                        if(proceed(arg3,nest) == YES)
                            return(YES);
                    }
                    else{
                        if(proceed(arg3,NIL) == YES){
                            if(proceed(arg4,nest) == YES)
                                return(YES);
                        }
                    }
                }
            }
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_comp_ifthenelse(int nest, int n){
    int arg1,arg2,arg3,arg4,arg5,arg6,save1,save2;

    save1 = wp;
    save2 = sp;
    if(n == 6){
        arg1 = deref(goal[2]);  //if
        arg2 = deref(goal[3]);  //if cut or NIL
        arg3 = deref(goal[4]);  //then
        arg4 = deref(goal[5]);  //then cut or NIL
        arg5 = deref(goal[6]);  //else
        arg6 = deref(goal[7]);  //else cut or NIL


        if(nullp(arg2)){
            if(proceed(arg1,NIL) == YES){
                if(nullp(arg4)){
                    if(proceed(arg3,nest) == YES)
                        return(YES);
                }
                else{
                    if(proceed(arg3,NIL) == YES)
                        if(proceed(arg4,nest) == YES)
                            return(YES);
                }
            }
            else{
                if(nullp(arg6)){
                    if(proceed(arg5,nest) == YES)
                        return(YES);
                }
                else{
                    if(proceed(arg5,NIL) == YES)
                        if(proceed(arg6,nest) == YES)
                            return(YES);
                }
            }
        }
        else{
            if(proceed(arg1,NIL) == YES){
                if(proceed(arg2,NIL) == YES){
                    if(nullp(arg4)){
                        if(proceed(arg3,nest) == YES)
                            return(YES);
                    }
                    else{
                        if(proceed(arg3,NIL) == YES){
                            if(proceed(arg4,nest) == YES)
                                return(YES);
                        }
                    }
                }
                else{
                    if(nullp(arg6)){
                        if(proceed(arg5,nest) == YES)
                            return(YES);
                    }
                    else{
                        if(proceed(arg5,NIL) == YES){
                            if(proceed(arg6,nest) == YES)
                                return(YES);
                        }
                    }
                }
            }
        }
        wp = save1;
        unbind(save2);
        return(NO);
    }
    return(NO);
}

int b_colon(int nest, int n){
    return(YES);
}

int b_atmark(int nest, int n){
    int arg1,arg2,res,save1,save2,save3;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        context = arg2;
        set_length(arg1);
        push_trail_body1(arg1);
        res = resolve_all(save1,sp,nest+1);
        context = NIL;
        tp = save1;
        if(res == NO)
            unbind(save2);
        trail_end = save3;
        return(res);
    }
    return(NO);
}

double getETime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec*1e-6;
}

int b_time(int nest, int n){
    int arg1,res;
    double end_time;

    if(n == 1){
        arg1 = goal[2];
        if(!structurep(arg1)){   // ex test -> (test)
            if(GET_AUX(arg1) == SIMP)
                arg1 = makeatom(GET_NAME(arg1),PRED);
            arg1 = cons(arg1,NIL);
        }
        push_trail_body1(arg1);
        time_flag = getETime(); //time_flag on and it store start time
        res = resolve_all(0,sp,0);
        if(res == NO){
            end_time = getETime();
            printf("Elapsed Time=%.6f (second)\n", end_time - time_flag);
            time_flag = 0;
        }
        return(res);
    }
    return(NO);
}

int b_timer(int nest, int n){
    int arg1,on,off;

    on = makeconst("on");
    off = makeconst("off");
    if(n == 1){
        arg1 = goal[2];

        if(arg1 == on)
            micro_second = getETime();
        else if(arg1 == off)
            micro_second = getETime() - micro_second;
        else if(variablep(arg1))
            unify(arg1,makeflt(micro_second));
        else
            error(ILLEGAL_ARGS,"timer",arg1);

        return(YES);
    }
    return(NO);
}

int b_char_set(int nest, int n){
    int arg1;

    if(n == 0){
        if(mode_flag == 0)
            printf("SJIS\n");
        else
            printf("Unicode\n");
        return(YES);
    }
    if(n == 1){
        arg1 = goal[2];
        if(eqp(arg1,makeconst("sjis"))){
            mode_flag = 0;
            return(YES);
        }
        else if(eqp(arg1,makeconst("unicode"))){
            mode_flag = 1;
            return(YES);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_char_conversion(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        return(unify(arg1,makeconst("on")));
    }
    return(NO);
}

int b_trace(int nest, int n){
    if(n == 0){
        trace_flag = FULL;
        return(YES);
    }
    return(NO);
}

int b_notrace(int nest, int n){
    if(n == 0){
        trace_flag = OFF;
        return(YES);
    }
    return(NO);
}

int b_spy(int nest, int n){
    int arg1;

    if(n == 0){
        print(spy_list);
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(goal[2]);
        SET_TR(cadr(arg1),1);
        if(!memberp(arg1,spy_list))
            spy_list = cons(arg1,spy_list);
        trace_flag = SPY;
        return(YES);
    }
    return(NO);
}

int b_nospy(int nest, int n){
    int arg1;

    if(n == 0){
        while(!nullp(spy_list)){
            SET_TR(cadr(car(spy_list)),0);
            spy_list = cdr(spy_list);
        }
        trace_flag = OFF;
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(goal[2]);
        SET_TR(cadr(arg1),0);
        spy_list = listremove(arg1,spy_list);
        if(nullp(spy_list))
            trace_flag = OFF;
        return(YES);
    }
    return(NO);
}

int b_halt(int nest, int n){
    int arg1;

    if(n == 0){
        printf("- good bye -\n");
        longjmp(buf,2);
    }
    else if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"halt ",arg1);
        if(!wide_integer_p(arg1))
            error(NOT_INT,"halt ",arg1);
        if(GET_INT(arg1) == 0){
            printf("- good bye -\n");
            longjmp(buf,2);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_abort(int nest, int n){

    if(n == 0){
        longjmp(buf,1);
    }
    return(NO);
}


//check data type
int b_atom(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(atomp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_integer(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(integerp(arg1) || longnump(arg1) || bignump(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_real(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(floatp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_number(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(numberp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}


int b_compound(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(compoundp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_ground(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(groundp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_var(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(variablep(arg1))
            return(YES);
        else if(anoymousp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_nonvar(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(variablep(arg1))
            return(NO);
        else if(anoymousp(arg1))
            return(NO);
        else
            return(YES);
    }
    return(NO);
}

int b_atomic(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(atomicp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_list(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(listp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_string(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(stringp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}


//characters
int b_char_code(int nest, int n){
    int arg1,arg2,code,res;
    char str[2];

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg1) && wide_variable_p(arg2))
            error(INSTANTATION_ERR,"char_code ",list2(arg1,arg2));
        if(!wide_variable_p(arg1) && !characterp(arg1))
            error(NOT_CHAR,"char_code ",arg1);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"char_code ",arg2);


        if(atomp(arg1) && !variablep(arg1)){
            strcpy(str,GET_NAME(arg1));
            if(str[0] == '\\'){
                if(str[1] == 'n')
                    return(unify(arg2,makeint(EOL)));
                else if(str[1] == 't')
                    return(unify(arg2,makeint(TAB)));
                else if(str[1] == 'f')
                    return(unify(arg2,makeint(FF)));
                else if(str[1] == 'r')
                    return(unify(arg2,makeint(CR)));
                else if(str[1] == 'v')
                    return(unify(arg2,makeint(VT)));
                else if(str[1] == 'a')
                    return(unify(arg2,makeint(BEL)));
                else if(str[1] == 'b')
                    return(unify(arg2,makeint(BS)));
                else
                    error(SYNTAX_ERR,"char_code ",NIL);
            }
            if(mode_flag == 0) //SJIS
                code = makeint(sjis_to_code(GET_NAME(arg1)));
            else //unicode
                code = makeint(utf8_to_ucs4(GET_NAME(arg1)));
            res = unify(arg2,code);
        return(res);
        }
        else if(integerp(arg2)){
            if(mode_flag == 0) //SJIS
                sjis_to_char(GET_INT(arg2),str);
            else //unicode
                ucs4_to_utf8(GET_INT(arg2),str);
            res = unify(arg1,makeconst(str));
            return(res);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_constant(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(constantp(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}


int b_atom_length(int nest, int n){
    int arg1,arg2,val;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"atom_length ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"atom_length ",arg1);
        if(integerp(eval(arg2)) && GET_INT(eval(arg2)) < 0)
            error(NOT_LESS_THAN_ZERO,"atom_length ",arg2);
        if(!wide_variable_p(arg2) && !integerp(arg2))
            error(NOT_INT,"atom_length ", arg2);

        val = makeint(atom_length(arg1));
        return(unify(arg2,val));
    }
    return(NO);
}


int b_atom_concat(int nest, int n){
    int arg1,arg2,arg3,atom,h,i,j,k,save1,save2;
    char str1[STRSIZE],str2[STRSIZE],str3[STRSIZE];

    save2 = sp;
    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        if(wide_variable_p(arg1) && wide_variable_p(arg3))
            error(INSTANTATION_ERR,"atom_concat ",list2(arg1,arg3));
        if(wide_variable_p(arg2) && wide_variable_p(arg3))
            error(INSTANTATION_ERR,"atom_concat ",list2(arg2,arg3));
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"atom_concat ",arg1);
        if(!wide_variable_p(arg2) && !atomp(arg2))
            error(NOT_ATOM,"atom_concat ",arg2);
        if(!wide_variable_p(arg3) && !atomp(arg3))
            error(NOT_ATOM,"atom_concat ",arg3);

        save1 = wp;
        if(!wide_variable_p(arg1) && !wide_variable_p(arg2)){
            strcpy(str1,GET_NAME(arg1));
            strcat(str1,GET_NAME(arg2));
            atom = makeconst(str1);

            if(unify(arg3,atom) == YES)
                if(proceed(NIL,nest) == YES)
                    return(YES);

            wp = save1;
            unbind(save2);
            return(NO);
        }
        else if(wide_variable_p(arg1) && !wide_variable_p(arg2) &&
                !wide_variable_p(arg3)){
            strcpy(str1,GET_NAME(arg3));
            //arg1
            memset(str2, '\0' ,STRSIZE);
            i = 0;
            k = strlen(GET_NAME(arg3)) - strlen(GET_NAME(arg2));
            while(i < k){
                str2[i] = str1[i];
                i++;
            }
            //arg2
            memset(str3, '\0' ,STRSIZE);
            i = 0;
            k = strlen(GET_NAME(arg2));
            j = strlen(GET_NAME(arg3)) - k;
            while(i < k){
                str3[i] = str1[j];
                i++;
                j++;
            }
            if(strcmp(str3,GET_NAME(arg2)) == 0){
                atom = makeconst(str2);
                unify(arg1,atom);
                if(proceed(NIL,nest) == YES)
                    return(YES);

            }
            wp = save1;
            unbind(save2);
            return(NO);
        }
        else if(!wide_variable_p(arg1) && wide_variable_p(arg2) &&
                !wide_variable_p(arg3)){
            strcpy(str1,GET_NAME(arg3));
            //arg2
            memset(str2, '\0' ,STRSIZE);
            i = 0;
            k = strlen(GET_NAME(arg3)) - strlen(GET_NAME(arg1));
            j = k - 1;
            while(i < k){
                str2[i] = str1[j];
                i++;
                j++;
            }
            //arg1
            memset(str3, '\0' ,STRSIZE);
            i = 0;
            k = strlen(GET_NAME(arg1));
            j = k - 1;
            while(i < k){
                str3[i] = str1[i];
                i++;
            }

            if(strcmp(str3,GET_NAME(arg1)) == 0){
                atom = makeconst(str2);
                unify(arg2,atom);
                if(proceed(NIL,nest) == YES)
                    return(YES);

            }
            wp = save1;
            unbind(save2);
            return(NO);
        }
        else if(wide_variable_p(arg1) && wide_variable_p(arg2) &&
                !wide_variable_p(arg3)){

            strcpy(str1,GET_NAME(arg3));
            h = strlen(GET_NAME(arg3));
            j = 0;
            while(j <= h){
                i = 0;
                k = j;
                memset(str2, '\0' ,STRSIZE);
                while(i < k){
                    str2[i] = str1[i];
                    i++;
                }
                i = 0;
                k = h - j;
                memset(str3, '\0' ,STRSIZE);
                while(i < k){
                    str3[i] = str1[i+j];
                    i++;
                }
                unify(arg1,makeconst(str2));
                unify(arg2,makeconst(str3));
                if(proceed(NIL,nest) == YES)
                    return(YES);

                wp = save1;
                unbind(save2);
                j++;
            }
        wp = save1;
        unbind(save2);
        return(NO);
        }
    }
    return(NO);
}

int b_sub_atom(int nest, int n){
    int arg1,arg2,arg3,arg4,arg5,h,i,j,k,b,l,a,atom,save1,save2;
    char str1[STRSIZE],str2[STRSIZE];

    save2 = sp;
    if(n == 5){
        arg1 = deref(goal[2]); //atom
        arg2 = deref(goal[3]); //before
        arg3 = deref(goal[4]); //length
        arg4 = deref(goal[5]); //after
        arg5 = deref(goal[6]); //sub_atom

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"sub_atom ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"sub_atom ",arg1);
        if(!wide_variable_p(arg5) && !atomp(arg5))
            error(NOT_ATOM,"sub_atom ",arg5);
        if(integerp(arg2) && GET_INT(arg2) < 0)
            error(NOT_LESS_THAN_ZERO,"sub_atom ",arg2);
        if(integerp(arg3) && GET_INT(arg3) < 0)
            error(NOT_LESS_THAN_ZERO,"sub_atom ",arg3);
        if(integerp(arg4) && GET_INT(arg4) < 0)
            error(NOT_LESS_THAN_ZERO,"sub_atom ",arg4);
        if(!wide_variable_p(arg2) && !wide_integer_p(arg2))
            error(NOT_INT,"sub_atom ",arg2);
        if(!wide_variable_p(arg3) && !wide_integer_p(arg3))
            error(NOT_INT,"sub_atom ",arg3);
        if(!wide_variable_p(arg4) && !wide_integer_p(arg4))
            error(NOT_INT,"sub_atom ",arg4);


        strcpy(str1,GET_NAME(arg1));
        save1 = wp;
        if(integerp(arg2) && integerp(arg3) && integerp(arg4)){
            b = GET_INT(arg2);
            l = GET_INT(arg3);
            a = GET_INT(arg4);
            if(atom_length(arg1) != (b+l+a))
                return(NO);
            i= 0;
            j = b;
            k = b + l - 1;
            memset(str2, '\0' ,STRSIZE);
            while(j <= k){
                str2[i] = str1[j];
                i++;
                j++;
            }
            atom = makeconst(str2);
            if(unify(arg5,atom) == YES){
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            else{
                wp = save1;
                unbind(save2);
                return(NO);
            }
        }
        else if(wide_variable_p(arg2) && integerp(arg3) && integerp(arg4)){
            l = GET_INT(arg3);
            a = GET_INT(arg4);
            b = atom_length(arg1) - l - a;
            i= 0;
            j = b;
            k = b + l - 1;
            memset(str2, '\0' ,STRSIZE);
            while(j <= k){
                str2[i] = str1[j];
                i++;
                j++;
            }
            atom = makeconst(str2);
            if(unify(arg2,makeint(b)) == YES &&
               unify(arg5,atom) == YES){
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            else{
                wp = save1;
                unbind(save2);
                return(NO);
            }
        }
        else if(integerp(arg2) && wide_variable_p(arg3) && integerp(arg4)){
            b = GET_INT(arg2);
            a = GET_INT(arg4);
            l = atom_length(arg1) - b - a;
            i= 0;
            j = b;
            k = b + l - 1;
            memset(str2, '\0' ,STRSIZE);
            while(j <= k){
                str2[i] = str1[j];
                i++;
                j++;
            }
            atom = makeconst(str2);
            if(unify(arg3,makeint(l)) == YES &&
               unify(arg5,atom) == YES){
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            else{
                wp = save1;
                unbind(save2);
                return(NO);
            }
        }
        else if(integerp(arg2) && integerp(arg3) && wide_variable_p(arg4)){
            b = GET_INT(arg2);
            l = GET_INT(arg3);
            a = atom_length(arg1) - b - l;
            i = 0;
            j = b;
            k = b + l - 1;
            memset(str2, '\0' ,STRSIZE);
            while(j <= k){
                str2[i] = str1[j];
                i++;
                j++;
            }
            atom = makeconst(str2);
            if(unify(arg4,makeint(a)) == YES &&
               unify(arg5,atom) == YES){
                if(proceed(NIL,nest) == YES)
                    return(YES);
            }
            else{
                wp = save1;
                unbind(save2);
                return(NO);
            }
        }
        else if(integerp(arg2) && wide_variable_p(arg3) && wide_variable_p(arg4)){
            h = atom_length(arg1);
            b = GET_INT(arg2);
            l = 0;
            a = h - b - l;
            while(b+l <= h){
                i = 0;
                j = b;
                k = b + l - 1;
                memset(str2, '\0' ,STRSIZE);
                while(j <= k){
                    str2[i] = str1[j];
                    i++;
                    j++;
                }
                atom = makeconst(str2);
                if(unify(arg3,makeint(l)) == YES &&
                   unify(arg4,makeint(a)) == YES){
                    if(unify(arg5,atom) == YES)
                        if(proceed(NIL,nest) == YES)
                            return(YES);
                }
                wp = save1;
                unbind(save2);
                l++;
                a--;
            }
        }
        else if(wide_variable_p(arg2) && integerp(arg3) && wide_variable_p(arg4)){
            h = atom_length(arg1);
            l = GET_INT(arg3);
            b = 0;
            a = h - b - l;
            while(b+l <= h){
                i = 0;
                j = b;
                k = b + l - 1;
                memset(str2, '\0' ,STRSIZE);
                while(j <= k){
                    str2[i] = str1[j];
                    i++;
                    j++;
                }
                atom = makeconst(str2);
                if(unify(arg2,makeint(b)) == YES &&
                   unify(arg4,makeint(a)) == YES &&
                   unify(arg5,atom) == YES){
                    if(unify(arg5,atom) == YES)
                        if(proceed(NIL,nest) == YES)
                            return(YES);
                }
                wp = save1;
                unbind(save2);
                b++;
                a--;
            }
        }
        else if(wide_variable_p(arg2) && wide_variable_p(arg3) && integerp(arg4)){
            a = GET_INT(arg4);
            b = 0;
            l = atom_length(arg1) - b - a;
            while(l >= 0){
                i = 0;
                j = b;
                k = b + l - 1;
                memset(str2, '\0' ,STRSIZE);
                while(j <= k){
                    str2[i] = str1[j];
                    i++;
                    j++;
                }
                atom = makeconst(str2);
                if(unify(arg2,makeint(b)) == YES &&
                   unify(arg3,makeint(l)) == YES){
                    if(unify(arg5,atom) == YES)
                        if(proceed(NIL,nest) == YES)
                            return(YES);
                }
                wp = save1;
                unbind(save2);
                l--;
                b++;
                a++;
            }
            return(NO);
        }
        else if(wide_variable_p(arg2) && wide_variable_p(arg3) && wide_variable_p(arg4)){
            h = atom_length(arg1);
            b = 0;
            l = 0;
            a = h - b - l;
            while(b+l <= h){
                while(b+l <= h){
                    i = 0;
                    j = b;
                    a = h - b - l;
                    k = b + l - 1;
                    memset(str2, '\0' ,STRSIZE);
                    while(j <= k){
                        str2[i] = str1[j];
                        i++;
                        j++;
                    }
                    atom = makeconst(str2);
                    if(unify(arg2,makeint(b)) == YES &&
                       unify(arg3,makeint(l)) == YES &&
                       unify(arg4,makeint(a)) == YES){
                        if(unify(arg5,atom) == YES)
                            if(proceed(NIL,nest) == YES)
                                return(YES);
                    }
                    wp = save1;
                    unbind(save2);
                    l++;
                }
                wp = save1;
                unbind(save2);
                l = 0;
                b++;
                a = h - b - l;
            }
        }
    }
    return(NO);
}

int b_atom_chars(int nest, int n){
    int arg1,arg2,ls,atom,pos,res;
    char str1[STRSIZE],str2[10];

    if(n == 2){
        arg1 = deref(goal[2]); //atom
        arg2 = deref(goal[3]); //list

        if(wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
            error(INSTANTATION_ERR,"atom_chars ",arg1);
        if(!wide_variable_p(arg1) && !atomp(arg1))
            error(NOT_ATOM,"atom_chars ",arg1);
        if(wide_variable_p(arg1) && !listp(arg2))
            error(NOT_LIST,"atom_chars ",arg2);
        if(wide_variable_p(arg1) && !atom_chars_list_p(arg2))
            error(NOT_CHAR,"atom_chars ",arg2);


        if(!wide_variable_p(arg1)){
            ls = NIL;
            strcpy(str1,GET_NAME(arg1));
            pos = 0;
            while(str1[pos] != NUL){
                if(mode_flag == 0 && iskanji(str1[pos])){ //SJIS
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
                ls = cons(makeconst(str2),ls);
            }
            ls = listreverse(ls);
            res = unify(arg2,ls);
            return(res);
            }
        else if(listp(arg2)){
            ls = arg2;
            str1[0] = NUL;
            while(!nullp(ls)){
                strcat(str1,GET_NAME(car(ls)));
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



int b_atom_codes(int nest, int n){
    int arg1,arg2,ls,atom,pos,code,res;
    char str1[STRSIZE],str2[10];

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
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

int b_string_chars(int nest, int n){
    int arg1,arg2,ls,atom,pos,res;
    char str1[STRSIZE],str2[10];

    if(n == 2){
        arg1 = deref(goal[2]); //string
        arg2 = deref(goal[3]); //list

        if(wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
            error(INSTANTATION_ERR,"string_chars ",arg1);
        if(!wide_variable_p(arg1) && !stringp(arg1))
            error(NOT_STR,"string_chars ",arg1);
        if(wide_variable_p(arg1) && !listp(arg2))
            error(NOT_LIST,"string_chars ",arg2);
        if(wide_variable_p(arg1) && !atom_chars_list_p(arg2))
            error(NOT_CHAR,"string_chars ",arg2);


        if(!wide_variable_p(arg1)){
            ls = NIL;
            strcpy(str1,GET_NAME(arg1));
            pos = 0;
            while(str1[pos] != NUL){
                if(mode_flag == 0 && iskanji(str1[pos])){ //SJIS
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
                ls = cons(makeconst(str2),ls);
            }
            ls = listreverse(ls);
            res = unify(arg2,ls);
            return(res);
            }
        else if(listp(arg2)){
            ls = arg2;
            str1[0] = NUL;
            while(!nullp(ls)){
                strcat(str1,GET_NAME(car(ls)));
                ls = cdr(ls);
            }
            atom = makestr(str1);
            res = unify(arg1,atom);
            return(res);
        }
        else
            return(NO);
    }
    return(NO);
}



int b_string_codes(int nest, int n){
    int arg1,arg2,ls,atom,pos,code,res;
    char str1[STRSIZE],str2[10];

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg1) && listp(arg2) && length(arg2) == -1)
            error(INSTANTATION_ERR,"string_codes ",arg1);
        if(!wide_variable_p(arg1) && !stringp(arg1))
            error(NOT_STR,"string_codes ",arg1);
        if(wide_variable_p(arg1) && !listp(arg2))
            error(NOT_LIST,"string_codes ",arg2);
        if(wide_variable_p(arg1) && !atom_codes_list_p(arg2))
            error(NOT_CHAR_CODE,"string_codes ",arg2);


        if(stringp(arg1) && !variablep(arg1)){
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
            atom = makestr(str1);
            res = unify(arg1,atom);
            return(res);
        }
        else
            return(NO);
    }
    return(NO);
}


int b_number_chars(int nest, int n){
    int arg1,arg2,res,pos,flag;
    char str1[STRSIZE],str2[2],c,*sym;
    double d;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(integerp(arg1)){
            sprintf(str1,"%d",GET_INT(arg1));
            pos = 0;
            c = str1[pos];
            res = NIL;
            while(c != NUL){
                str2[0] = c;
                str2[1] = NUL;
                res = cons(makeconst(str2),res);
                pos++;
                c = str1[pos];
            }
            res = listreverse(res);
            return(unify(arg2,res));
        }
        else if(floatp(arg1)){
            sprintf(str1,"%g",GET_FLT(arg1));
            pos = 0;
            c = str1[pos];
            res = NIL;
            while(c != NUL){
                if(c >= 48 && c <= 57){
                    str2[0] = c;
                    str2[1] = NUL;
                    res = cons(makeconst(str2),res);
                }
                else{
                    str2[0] = c;
                    str2[1] = NUL;
                    res = cons(makeconst(str2),res);
                }
                pos++;
                c = str1[pos];
            }
            res = listreverse(res);
            return(unify(arg2,res));
        }
        else if(listp(arg2)){
            pos = 0;
            while(!nullp(arg2)){
                sym = GET_NAME(car(arg2));
                c = *sym;
                str1[pos] = c;
                pos++;
                arg2 = cdr(arg2);
            }
            str1[pos] = NUL;
            pos = 0;
            flag = 0;
            c = str1[pos];
            while(c != NUL){
                if(!isdigit(c) && c != '-' && c != '+')
                    flag = 1;
                c = str1[pos];
                pos++;
            }
            if(flag){
                d = atof(str1);
                return(unify(arg1,makeflt(d)));
            }
            else{
                res = atoi(str1);
                return(unify(arg1,makeint(res)));
            }
        }
        return(NO);
    }
    return(NO);
}

int b_number_codes(int nest, int n){
    int arg1,arg2,res,pos,flag;
    char str1[STRSIZE],c,*sym;
    double d;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(integerp(arg1)){
            sprintf(str1,"%d",GET_INT(arg1));
            pos = 0;
            c = str1[pos];
            res = NIL;
            while(c != NUL){
                res = cons(makeint((int)c),res);
                pos++;
                c = str1[pos];
            }
            res = listreverse(res);
            return(unify(arg2,res));
        }
        else if(floatp(arg1)){
            sprintf(str1,"%g",GET_FLT(arg1));
            pos = 0;
            c = str1[pos];
            res = NIL;
            flag = 0;
            while(c != NUL){
                res = cons(makeint((int)c),res);
                pos++;
                c = str1[pos];
                if(c == '.')
                    flag = 1;
            }
            if(flag == 0){
                res = cons(makeint((int)'.'),res);
                res = cons(makeint((int)'0'),res);
            }
            res = listreverse(res);
            return(unify(arg2,res));
        }
        else if(listp(arg2)){
            pos = 0;
            while(!nullp(arg2)){
                if(integerp(car(arg2)))
                    c = (char)(GET_INT(car(arg2)));
                else{
                    sym = GET_NAME(car(arg2));
                    c = *sym;
                }
                str1[pos] = c;
                pos++;
                arg2 = cdr(arg2);
            }
            str1[pos] = NUL;
            pos = 0;
            flag = 0;
            c = str1[pos];
            while(c != NUL){
                if(!isdigit(c) && c != '-' && c != '+')
                    flag = 1;
                c = str1[pos];
                pos++;
            }
            if(flag){
                d = atof(str1);
                return(unify(arg1,makeflt(d)));
            }
            else{
                res = atoi(str1);
                return(unify(arg1,makeint(res)));
            }
        }
        return(NO);
    }
    return(NO);
}

/*
between(L, H, L) :- L =< H.
between(L, H, V) :- L < H, L1 is L + 1, between(L1, H, V).
*/

int b_between(int nest, int n){
    int arg1,arg2,arg3,varL1,varV,varH,varL,body,save1,save2;

    save2 = sp;
    if(n == 3){
        arg1 = deref(get_goal(2)); //lower
        arg2 = deref(get_goal(3)); //highwe
        arg3 = deref(get_goal(4)); //variable
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
        varH = makevariant();
        varL = makevariant();
        if(unify(arg1,varL) == YES &&
            unify(arg2,varH) == YES &&
            unify(arg3,varL) == YES){
                body = wlist3(makeatom("=<",SYS),deref(varL),deref(varH));
                if(proceed(body,nest) == YES)
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
            if(proceed(body,nest) == YES)
                return(YES);
        }
        wp = save1;
        unbind(save2);
    }
    return(NO);
}

//-----structure------
int b_functor(int nest, int n){
    int arg1,arg2,arg3,res,i;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

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

int b_arg(int nest, int n){
    int arg1,arg2,arg3,elt,i;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

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

int b_numbervars(int nest, int n){
    int arg1,arg2,arg3,vars,i,pred;

    if(n == 3){
        arg1 = deref(goal[2]); //term
        arg2 = deref(goal[3]); //start
        arg3 = deref(goal[4]); //end

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"numbervars ",arg1);
        if(!integerp(arg2))
            error(NOT_INT,"numbervars ",arg2);
        if(!wide_variable_p(arg3) && !integerp(arg3))
            error(NOT_INT,"numbervars ",arg3);

        vars = listreverse(unique(varslist(arg1)));
        i = GET_INT(arg2);
        while(!nullp(vars)){
            pred = makeatom("$VAR",SIMP);
            SET_AUX(pred,PRED);
            unify(car(vars),list2(pred,makeint(i)));
            vars = cdr(vars);
            i++;
        }
        if(unify(arg3,makeint(i)) == YES)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_predicate_property(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]); //term
        arg2 = deref(goal[3]); //prop

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"predicate_property ",arg1);

        if(atomp(arg1) && GET_AUX(arg1) == SYS)
            return(unify(arg2,makeconst("built_in")));
        else if(structurep(arg1) && GET_AUX(car(arg1)) == SYS)
            return(unify(arg2,makeconst("built_in")));
        else if(atomp(arg1) && GET_AUX(arg1) == PRED &&
                GET_CAR(arg1) != NIL)
            return(unify(arg2,makeatom("dynamic",SYS)));
        else if(structurep(arg1) && GET_AUX(car(arg1)) == PRED &&
                GET_CAR(car(arg1)) != NIL)
            return(unify(arg2,makeatom("dynamic",SYS)));
        else if(atomp(arg1) && GET_AUX(arg1) == COMP)
            return(unify(arg2,makeconst("static")));
        else if(structurep(arg1) && GET_AUX(car(arg1)) == COMP)
            return(unify(arg2,makeconst("static")));
        else
            return(NO);
    }
    return(NO);

}

//-----other----

int b_listing(int nest, int n){
    int arg1,clauses,pred,list,temp;

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
        arg1 = deref(goal[2]);
        if(atomp(arg1)){
            clauses = GET_CAR(arg1);
            listing_flag = 1;
            while(!nullp(clauses)){
                print(car(clauses));
                if(debug_flag){
                    if(GET_OPT(car(clauses)) == HASCUT)
                        printf("has cut");
                }
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
                      if(debug_flag){
                          if(GET_OPT(car(clauses)) == HASCUT)
                              printf("has cut");
                      }
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


int b_bagof(int nest, int n){
    int arg1,arg2,arg3,save1,save2,save3,save4,end,
    vars,notfree,free;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    save4 = variables;
    if(n == 3){
        arg1 = deref(goal[2]); //template
        arg2 = deref(goal[3]); //goal
        arg3 = deref(goal[4]); //instance

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"bagof ",arg2);
        if(!callablep(get_predicate(arg2)))
            error(NOT_CALLABLE,"bagof ",arg2);
        if(!wide_variable_p(arg3) && !listp(arg3))
            error(NOT_LIST,"bagof ",arg3);

        if(arg2 == makeconst("fail"))
            goto exit;
        vars = listreverse(unique(varslist(arg2)));
        notfree = cons(arg1,get_notfree_variable(arg2));
        free = get_free_variable(vars,notfree);
        if(nullp(free))
            goto findall;

        loop:
        bagof_list = NIL;
        push_trail_body_with_bagof_help(get_predicate(arg2),car(free),notfree);
        resolve_all(save1,sp,nest+1);
        unify(arg3,listreverse(bagof_list));
        unify(car(free),car(checking_var));
        checked_var = cons(checking_var,checked_var);
        checking_var = NIL;
        variables = save4;
        if(!nullp(bagof_list)){
            tp = save1;
            trail_end = save3;
            if(proceed(NIL,nest) == YES){
                return(YES);
            }
            else{
                tp = save1;
                trail_end = save3;
                unbind(save2);
                goto loop;
            }
        }
        else{
            exit:
            checked_var = NIL;
            checking_var = NIL;
            unbind(save2);
            return(NO);
        }

        findall:
        findall_pt++;
        findall_list[findall_pt] = NIL;
        end = tp;
        push_trail_body_with_findall_help(arg2,arg1);
        resolve_all(end,sp,nest);
        tp = save1;
        unbind(save2);
        trail_end = save3;
        unify(arg3,listreverse(findall_list[findall_pt]));
        findall_pt--;
        variables = save4;
            if(proceed(NIL,nest) == YES)
                return(YES);
    }
    return(NO);
}

int b_bagof_help(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = goal[2]; //derefvar
        arg2 = goal[3]; //freevar

        if(already_checked_p(arg2)){
            return(NO);
        }
        else if(now_checking_var_p(arg2)){
            bagof_list = cons(deref(arg1),bagof_list);
            return(NO);
        }
        else if(nullp(checking_var)){
            checking_var = deref(arg2);
            bagof_list = cons(deref(arg1),bagof_list);
            return(NO);
        }
        else
            return(NO);
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

//for bagof_help
int already_checked_p(int x){
    int lis;

    lis = checked_var;
    while(!nullp(lis)){
        if(unify(x,car(lis)) == YES)
            return(1);
        lis = cdr(lis);
    }
    return(0);
}

//for bagof_help
int now_checking_var_p(int x){
    if(unify(x,checking_var) == YES)
        return(1);
    else
        return(0);
}

//setof
int b_setof(int nest, int n){
    int arg1,arg2,arg3,save1,save2,save3,save4,end,
    vars,notfree,free;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    save4 = variables;
    if(n == 3){
        arg1 = deref(goal[2]); //template
        arg2 = deref(goal[3]); //goal
        arg3 = deref(goal[4]); //instance

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"setof ",arg2);
        if(!callablep(get_predicate(arg2)))
            error(NOT_CALLABLE,"setof ",arg2);
        if(!wide_variable_p(arg3) && !listp(arg3))
            error(NOT_LIST,"setof ",arg3);

        if(arg2 == makeconst("fail"))
            goto exit;
        vars = listreverse(unique(varslist(arg2)));
        notfree = cons(arg1,get_notfree_variable(arg2));
        free = get_free_variable(vars,notfree);
        if(nullp(free))
            goto findall;

        loop:
        bagof_list = NIL;
        push_trail_body_with_bagof_help(get_predicate(arg2),car(free),notfree);
        resolve_all(save1,sp,nest+1);
        unify(arg3,sort(unique(bagof_list)));
        unify(car(free),car(checking_var));
        checked_var = cons(checking_var,checked_var);
        checking_var = NIL;
        variables = save4;
        if(!nullp(bagof_list)){
            tp = save1;
            trail_end = save3;
            if(proceed(NIL,nest) == YES){
                return(YES);
            }
            else{
                tp = save1;
                trail_end = save3;
                unbind(save2);
                goto loop;
            }
        }
        else{
            exit:
            checked_var = NIL;
            checking_var = NIL;
            unbind(save2);
            return(NO);
        }

        findall:
        findall_pt++;
        findall_list[findall_pt] = NIL;
        end = tp;
        push_trail_body_with_findall_help(arg2,arg1);
        resolve_all(end,sp,nest);
        tp = save1;
        unbind(save2);
        trail_end = save3;
        unify(arg3,sort(unique(findall_list[findall_pt])));
        findall_pt--;
        variables = save4;
            if(proceed(NIL,nest) == YES)
                return(YES);
    }
    return(NO);
}


int b_findall(int nest, int n){
    int arg1,arg2,arg3,arg4,save1,save2,save3,save4,end;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    save4 = variables;
    if(n == 3){
        arg1 = deref(goal[2]); //template
        arg2 = deref(goal[3]); //goal
        arg3 = deref(goal[4]); //instance

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"findall ",arg2);
        if(!callablep(arg2))
            error(NOT_CALLABLE,"findall ",arg2);
        if(!wide_variable_p(arg3) && !listp(arg3))
            error(NOT_LIST,"findall ",arg3);

        findall_pt++;
        findall_list[findall_pt] = NIL;
        end = tp;
        push_trail_body_with_findall_help(arg2,arg1);
        resolve_all(end,sp,nest);
        tp = save1;
        unbind(save2);
        trail_end = save3;
        unify(arg3,listreverse(findall_list[findall_pt]));
        findall_pt--;
        variables = save4;
        return(YES);
    }
    if(n == 4){
        arg1 = deref(goal[2]); //template
        arg2 = deref(goal[3]); //goal
        arg3 = deref(goal[4]); //instance
        arg4 = deref(goal[5]); //tail

        if(wide_variable_p(arg2))
            error(INSTANTATION_ERR,"findall ",arg2);
        if(!callablep(arg2))
            error(NOT_CALLABLE,"findall ",arg2);
        if(!wide_variable_p(arg3) && !listp(arg3))
            error(NOT_LIST,"findall ",arg3);

        findall_pt++;
        findall_list[findall_pt] = NIL;
        end = tp;
        push_trail_body_with_findall_help(arg2,arg1);
        resolve_all(end,sp,nest);
        tp = save1;
        unbind(save2);
        trail_end = save3;
        unify(arg3,append(listreverse(findall_list[findall_pt]),arg4));
        findall_pt--;
        variables = save4;
        return(YES);
    }

    return(NO);
}

int b_findall_help(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = goal[2];

        findall_list[findall_pt] =
         listcons(copy_heap(deref(arg1)),findall_list[findall_pt]);
        return(NO);
    }
    return(NO);
}

//transform bwtween predicate and data
int b_univ(int nest, int n){
    int arg1,arg2,res;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

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

int b_copy_term(int nest, int n){
    int arg1,arg2,res;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        res = unify(arg2,copy_term(arg1));
        return(res);
    }
    return(NO);
}


//listreverse/2
int b_reverse(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(!variablep(arg1) && variablep(arg2))
            return(unify(listreverse(arg1),arg2));
        else if(variablep(arg1) && !variablep(arg2))
            return(unify(arg1,listreverse(arg2)));
        else
            return(NO);
    }
    return(NO);
}

int b_module(int nest, int n){
    int arg1,i;

    if(n == 1){
        arg1 = goal[2];
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"module ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"module ",arg1);

        module_name = arg1;
        export_list = NIL;
        meta_list = NIL;

        for(i=0;i<module_pt;i++)
            if(module[module_pt][0] == arg1){
                return(YES);
            }

        module[module_pt][0] = arg1;
        module_pt++;
        return(YES);
    }
    return(NO);
}

int b_end_module(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"end_module ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"end_module ",arg1);
        if(arg1 != module_name)
            error(SYNTAX_ERR,"end_module ",arg1);
        module_name = NIL;
        export_list = NIL;
        return(YES);
    }
    return(NO);
}

int b_export(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = goal[2];
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"export ",arg1);
        if(!listp(arg1))
            error(NOT_LIST,"export ",arg1);

        module[module_pt - 1][1] = arg1;
        return(YES);
    }
    return(NO);
}

int b_reexport(int nest, int n){
    int arg1,arg2,i;

    if(n == 1){
        arg1 = deref(goal[2]); //module
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"reexport ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"reexport ",arg1);

        for(i=0;i<MODULES;i++){
            if(module[i][0] == arg1){
                module[i][1] = export_list;
                return(YES);
            }
        }
        error(NOT_EXIST_MODULE,"reexport ",arg1);
    }
    else if(n == 2){
        arg1 = deref(goal[2]); //module
        arg2 = deref(goal[3]); //list

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"reexport ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"reexport ",arg1);
        if(!list(arg2))
            error(NOT_LIST,"reexport ",arg2);

        for(i=0;i<MODULES;i++){
            if(module[i][0] == arg1){
                module[i][1] = arg2;
                return(YES);
            }
        }
        error(NOT_EXIST_MODULE,"reexport ",arg1);
    }
    return(NO);
}

int b_meta(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(!listp(arg1))
            error(NOT_LIST,"meta ",arg1);

        meta_list = arg1;
        return(YES);
    }
    return(NO);
}

int b_calling_context(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        return(unify(arg1,context));
    }
    return(NO);
}

int b_import(int nest, int n){
    int arg1,arg2,i;

    if(n == 1){
        arg1 = goal[2]; //module
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"import ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"import ",arg1);

        module_name = arg1;
        for(i=0;i<MODULES;i++){
            if(module[i][0] == arg1){
                export_list = cons(module[i][1],export_list);
                return(YES);
            }
        }
        error(NOT_EXIST_MODULE,"import ",arg1);
    }
    else if(n == 2){
        arg1 = goal[2]; //module
        arg2 = goal[3]; //list
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"import ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"import ",arg1);
        if(!listp(arg2))
            error(NOT_LIST,"import ",arg2);

        module_name = arg1;
        export_list = cons(arg2,export_list);
        return(YES);
    }
    return(NO);
}


int b_body(int nest, int n){
    int arg1,i;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"body ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"body ",arg1);

        module_name = arg1;
        for(i=0;i<MODULES;i++){
            if(module[i][0] == arg1){
                export_list = module[i][1];
                return(YES);
            }
        }
        error(NOT_EXIST_MODULE,"body ",arg1);
    }
    return(NO);
}

int b_end_body(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"end_body ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"end_body ",arg1);
        if(!eqlp(arg1,module_name))
            error(SYNTAX_ERR,"end_body ",arg1);

        module_name = NIL;
        export_list = NIL;
        meta_list = NIL;
        return(YES);
    }
    return(NO);
}


//--------Flags------------
int b_dynamic(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"dynamic ",arg1);
        if(car(arg1) != makeatom("/",OPE))
            error(PRED_INDICATOR,"dynamic ",arg1);
        if(!atomp(cadr(arg1)))
            error(NOT_ATOM,"dynamic ",cadr(arg1));
        if(!integerp(caddr(arg1)))
            error(NOT_INT,"dynamic ",caddr(arg1));

        arg1 = list3(car(arg1),makepred(GET_NAME(cadr(arg1))),caddr(arg1));
        SET_OPT1(cadr(arg1),NO);
        if(!memberp(arg1,dynamic_list)){
            dynamic_list = listcons(arg1,dynamic_list);
        }
        return(YES);
    }
    return(NO);
}

int b_discontiguous(int nest, int n){
    int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"discontiguous ",arg1);
        if(car(arg1) != makeatom("/",OPE))
            error(PRED_INDICATOR,"discontiguous ",arg1);
        if(!atomp(cadr(arg1)))
            error(NOT_ATOM,"discontiguous ",cadr(arg1));
        if(!integerp(caddr(arg1)))
            error(NOT_INT,"discontiguous ",caddr(arg1));

        SET_OPT1(cadr(arg1),NO);

        if(!memberp(arg1,discontiguous_list))
        	discontiguous_list = cons(copy_heap(arg1),discontiguous_list);

        return(YES);
    }
    return(NO);
}

int b_debug(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = goal[2];
        if(arg1 == makeconst("on")){
            debug_flag = 1;
            sexp_flag = 1;
            gbc_flag = 1;
            flag_list = replace(cons(makeconst("debug"),
                                     makeconst("on")),flag_list);
            return(YES);
        }
        else if(arg1 == makeconst("off")){
            debug_flag = 0;
            sexp_flag = 0;
            gbc_flag = 0;
            flag_list = replace(cons(makeconst("debug"),
                                     makeconst("off")),flag_list);
            return(YES);
        }
        else
            return(NO);
    }
    return(NO);
}

int b_set_prolog_flag(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(eqlp(arg1,makesys("debug")) && eqlp(arg2,makeconst("on"))){
            sexp_flag = 1;
            flag_list = replace(cons(makesys("debug"),makeconst("on")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makesys("debug")) && eqlp(arg2,makeconst("off"))){
            sexp_flag = 0;
            flag_list = replace(cons(makesys("debug"),makeconst("off")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makeconst("unknown")) &&
                eqlp(arg2,makeconst("fail"))){
            undefined_flag = 0;
            flag_list = replace(cons(makeconst("unknown"),
                                     makeconst("fail")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makeconst("unknown")) &&
                eqlp(arg2,makeconst("error"))){
            undefined_flag = 1;
            flag_list = replace(cons(makeconst("unknown"),
                                     makeconst("error")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makeconst("unknown")) &&
                eqlp(arg2,makeconst("warning"))){
            undefined_flag = 2;
            flag_list = replace(cons(makeconst("unknown"),
                                     makeconst("warning")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makeconst("integer_rounding_function")) &&
                eqlp(arg2,makeconst("down"))){
            rounding_flag = 1;
            return(YES);
        }
        else if(eqlp(arg1,makeconst("integer_rounding_function")) &&
                eqlp(arg2,makeconst("toward_zero"))){
            rounding_flag = 0;
            return(YES);
        }
        else if(eqlp(arg1,makeconst("double_quotes")) &&
                eqlp(arg2,makeconst("codes"))){
            double_flag = 0;
            flag_list = replace(cons(makeconst("double_quotes"),
                                     makeconst("codes")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makeconst("double_quotes")) &&
                eqlp(arg2,makeconst("chars"))){
            double_flag = 1;
            flag_list = replace(cons(makeconst("double_quotes"),
                                     makeconst("chars")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makeconst("double_quotes")) &&
                eqlp(arg2,makeconst("string"))){
            double_flag = 2;
            flag_list = replace(cons(makeconst("double_quotes"),
                                     makeconst("string")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makesys("char_set")) &&
                eqlp(arg2,makeconst("sjis"))){
            mode_flag = 0;
            flag_list = replace(cons(makesys("char_set"),
                                     makeconst("sjis")),flag_list);
            return(YES);
        }
        else if(eqlp(arg1,makesys("char_set")) &&
                eqlp(arg2,makeconst("unicode"))){
            mode_flag = 1;
            flag_list = replace(cons(makesys("char_set"),
                                     makeconst("unicode")),flag_list);
            return(YES);
        }
        error(NOT_FLAG_SPEC,"set_prolog_flag ",list2(arg1,arg2));
        return(NO);
    }
    return(NO);
}

int b_setup_call_cleanup(int nest, int n){
    int arg1,arg2,arg3,save1,save2,temp;

    save2 = sp;
    if(n == 3){
        arg1 = deref(goal[2]); //setup
        arg2 = deref(goal[3]); //call
        arg3 = deref(goal[4]); //cleanup

        //for error invoke in call process
        //set arg3 to clearnup_dt.
        cleanup_dt = arg3;

        save1 = wp;
        //setup
        if(proceed(arg1,NIL) == NO){
            wp = save1;
            unbind(save2);
            return(NO);
        }

        //call
        if(arg2 == CUT){ //call(!) = true
            if(proceed(NIL,nest) == YES)
                goto cleanup;
        }
        else if(!has_cut_p(arg2)){
            if(proceed(arg2,nest) == YES)
                goto cleanup;
        }
        else{
            temp = before_cut(arg2);
            if(proceed(temp,NIL) == YES){
                temp = after_cut(arg2);
                if(proceed(temp,NIL) == YES){
                    if(proceed(NIL,nest) == YES)
                        goto cleanup;
                }
            }
        }
        wp = save1;
        unbind(save2);

        //cleanup
        cleanup:
        cleanup_dt = NIL;
        arg3 = deref(arg3);
        if(wide_variable_p(arg3))
            error(INSTANTATION_ERR,"set_call_cleanup ",arg3);

        proceed(arg3,nest);
        return(YES);
    }
    return(NO);
}

int b_freeze(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(!wide_variable_p(arg1))
            error(NOT_VAR,"freeze ",arg1);
        if(!callablep(arg2))
            error(NOT_CALLABLE,"freeze ",arg2);

        if(alpha_variable_p(arg1))
            variant[arg1-CELLSIZE][1] = arg2;
        else
            SET_ATTR(arg1,arg2);

        return(YES);
    }
    return(NO);
}

//operation
int o_define(int x, int y){
    int clause,save;

    if(!nullp(y)){
        if(builtinp(x) || compiledp(x))
            error(BUILTIN_EXIST,"assertz",x);
        if(atomp(x))
            SET_AUX(x,PRED);
        clause = list3(DEFINE,x,y);
        SET_AUX(clause,CLAUSE);
        if(module_name != NIL)
            clause = add_prefix(clause);
        SET_VAR(clause,reverse(unique(varslist(clause))));
        set_length(cadr(clause)); //head
        set_length(caddr(clause)); //body
        if(has_cut_p(y)){
            SET_OPT(clause,HASCUT);
        }
        if(has_ifthen_p(y)){
            SET_OPT1(clause,HASIFTHEN);
        }
        //when in module, head of clause is prifix added.
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
    	save = tp;
    	set_length(x);
    	push_trail_body1(x);
        return(resolve_all(save,sp,0));
    }
    return(NO);
}

int o_dcg(int x, int y){
    int clause,res;

    if(getatom("dcg_expand",COMP,hash("dcg_expand")))
        clause = list2(makecomp("dcg_expand"),
                   list3(makeatom("-->",OPE),x,y));
    else
        clause = list2(makepred("dcg_expand"),
                   list3(makeatom("-->",OPE),x,y));

    set_length(clause);
    tp = 0;
    push_trail_body1(clause);
    res = resolve_all(0,sp,0);
    return(res);
}

int o_question(int x, int y){
    int res,temp;

    //[file1,file2] -> consult(file1),consult(file2).
    if(listp(x))
        x = list_to_ope(x);

    if(atomp(x) && !builtinp(x) && !compiledp(x))
        x = makepred(GET_NAME(x));

    if(wide_variable_p(x))
        error(INSTANTATION_ERR,"?- ", x);

    if(!callablep(x))
        error(NOT_CALLABLE,"?- ", x);


    FLUSH
    if(!has_cut_p(x)){
        push_trail_body_with_ask(x);
        res = resolve_all(0,sp,1);
        if(res == CUT)
            res = NO;
        print(res);printf("\n");
        return(res);
    }
    /*
    e.g. ?- ((X=1;X=2),Y=6;Y=7,!,(X=3;X=4)).
    */
    else if(has_cut_p(x) && disjunctionp(after_cut(x))){
        temp = remove_cut(x);
        push_trail_body_with_ask(temp);
        res = resolve_all(0,sp,1);
        print(res);printf("\n");
        return(res);
    }
    else{
        push_trail_body1(before_cut(x));
        if(resolve_all(0,sp,1) == YES){
            push_trail_body_with_ask(after_cut(x));
            variables = listreverse(unique(varslist(x)));
            if(resolve_all(0,sp,1) == YES){
                res = YES;
                goto cut;
            }
            else{
                res = NO;
                goto cut;
            }
        }
        else{
            res = NO;
            goto cut;
        }
        cut:
        if(res == CUT)
            res = NO;
        print(res);printf("\n");
        return(res);
    }
}

int list_to_ope(int x){
    if(nullp(x))
        error(SYNTAX_ERR,"?-", x);
    else if(nullp(cdr(x)))
        return(cons(makeatom("reconsult",SYS),x));
    else{
        return(list3(makeatom(",",OPE),
                     list2(makeatom("reconsult",SYS),car(x)),
                     list_to_ope(cdr(x))));
    }
    return(NIL);
}

int b_gbc(int nest, int n){
    int arg1;

    if(n == 0){
        gbc();
        return(YES);
    }
    else if(n == 1){
        arg1 = deref(goal[2]);
        if(arg1 == YES)
            gbc_flag = 1;
        else if(arg1 == NO)
            gbc_flag = 0;

        return(YES);
    }
    return(NO);
}

int b_catch(int nest, int n){
    int arg1,arg2,arg3,clause,ret,res;

    //save1 = tp;
    if(n == 3){
        arg1 = deref(goal[2]); //goal
        arg2 = deref(goal[3]); //catcher
        arg3 = deref(goal[4]); //recovery

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"catch ",arg1);
        if(!callablep(arg1))
            error(NOT_CALLABLE,"catch ",arg1);

        catch_pt++;
        catch_dt[catch_pt][0] = arg2;
        catch_dt[catch_pt][1] = arg3;
        catch_dt[catch_pt][2] = tp;
        catch_dt[catch_pt][3] = sp;
        ret = setjmp(catch_buf[catch_pt]);
        if(ret == 0){
            clause = arg1;
            //end = tp;
            //set_length(clause);
            //push_trail_body1(clause);
            //res = resolve_all(end,sp,nest);
            res = proceed(arg1,nest);
            catch_pt--;
            //tp = save1;
            return(res);
        }
        else if(ret == 1){
            if(debug_flag){
                printf("recieve error ");
                print(deref(catch_dt[catch_pt][0]));
                printf("\n");
            }
            catch_pt--;
            ret = 0;
            if(anoymousp(arg3))
                return(YES);
            clause = deref(arg3);
            //end = tp;
            //set_length(clause);
            //push_trail_body(clause);
            //res = resolve_all(end,sp,nest);
            res = proceed(clause,nest);
            //tp = save1;
            return(res);
        }
    }
    return(NO);
}


int b_throw(int nest, int n){
    int arg1,i,tag;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"throw ",arg1);

        for(i=catch_pt;i>0;i--){
            tag = catch_dt[i][0];
            tp = catch_dt[i][2];
            sp = catch_dt[i][3];
            if(unify(arg1,tag) == YES){
                longjmp(catch_buf[i],1);
            }
        }
        error(UNCAUGHT_EXCEPTION,"throw",arg1);
    }
    return(NO);
}


int o_ignore(int nest, int n){
    return(YES);
}


//directory for Logtalk
int b_make_directory(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"make_directory ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"make_directory ", arg1);
        #if _WIN32
        mkdir(GET_NAME(arg1));
        #else
        mkdir(GET_NAME(arg1),0777);
        #endif
        return(YES);
    }
    return(NO);
}

int b_directory_exists(int nest, int n){
    int arg1;
    struct stat statBuf;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"directory exists ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"directory_exists ", arg1);

        if(stat(GET_NAME(arg1), &statBuf) == 0)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_current_directory(int nest , int n){
    int arg1;
    char str[ATOMSIZE];

    if(n == 1){
        arg1 = deref(goal[2]);
        //if(!wide_variable_p(arg1))
        //    error(NOT_VAR,"current_directory ",arg1);

        memset(str,NUL,ATOMSIZE);
        if(getcwd(str,ATOMSIZE) != NULL)
            unify(arg1,makeconst(str));
        else
            return(NO);

        return(YES);
    }
    return(NO);
}

int b_change_directory(int nest , int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
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

int b_expand_path(int nest, int n){
    int arg1,arg2,pos1,pos2;
    char str1[ATOMSIZE],str2[ATOMSIZE],str3[ATOMSIZE];
    char *str;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"expand_path ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"expand_path ",arg1);


        strcpy(str1,GET_NAME(arg1));
        if(str1[0] == '$'){
            pos1 = 0;
            pos2 = 1;
        }
        else{
            pos1 = 0;
            pos2 = 0;
        }
        while(str1[pos2] != NUL){
            str2[pos1] = str1[pos2];
            pos1++;
            pos2++;
            if(str1[pos2] == '/')
                break;
        }
        str2[pos1] = NUL;
        if(str1[0] == '$'){
            if((str = getenv(str2)) != NULL)
                strcpy(str3,str);
        }
        else
            strcpy(str3,str2);

        pos1 = 0;
        while(str1[pos2] != NUL){
            str2[pos1] = str1[pos2];
            pos1++;
            pos2++;
        }
        str2[pos1] = NUL;
        strcat(str3,str2);

        unify(arg2,makeconst(str3));
        return(YES);

    }
    return(NO);
}

int b_delete_file(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"delete_file ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"delete_file ", arg1);

        remove(GET_NAME(arg1));
        return(YES);
    }
    return(NO);
}

int b_file_exists(int nest, int n){
    int arg1,res;
    FILE *fp;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"file_exists ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"file_exists ", arg1);

        fp = fopen(GET_NAME(arg1), "r");
        if(fp == NULL)
            res = NO;
        else{
            fclose(fp);
            res = YES;
        }
        return(res);
    }
    return(NO);
}

int b_decompose_file_name(int nest, int n){
    int arg1,arg2,arg3,arg4,i,j,len,dirpos,extpos;

    char str[ATOMSIZE];
    char strdir[ATOMSIZE];  //directory
    char strname[ATOMSIZE]; //filename
    char strext[5];   //ext

    if(n == 4){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        arg4 = deref(goal[5]);
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"decompose_file_name ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"decompose_file_name ",arg1);


        memset(strdir,NUL,ATOMSIZE);
        memset(strname,NUL,ATOMSIZE);
        memset(strext,NUL,5);
        strcpy(str,GET_NAME(arg1));
        len = strlen(str);
        extpos = 0;
        dirpos = 0;
        j = 0;

        for(i=len;i>=0;i--){
            if(str[i] == '.'){
                extpos = i;
            }
            #if _WIN32
            else if(str[i] == '\\'){
                dirpos = i;
                break;
            }
            #else
            else if(str[i] == '/'){
                dirpos = i;
                break;
            }
            #endif
        }
        //directory
        if(dirpos != 0){
            i = 0;
            for(i=0;i<=dirpos;i++){
                strdir[j] = str[i];
                j++;
            }
        }
        //filename
        if(extpos != 0){ // horm/foo.pl
            j = 0;
            for(i=dirpos+1;i<extpos;i++){
                strname[j] = str[i];
                j++;
            }
        }
        else{  // homr/foo
            j = 0;
            for(i=dirpos+1;i<len;i++){
                strname[j] = str[i];
                j++;
            }
        }
        //ext
        if(extpos != 0){
            j = 0;
            for(i=extpos+1;i<len;i++){
                strext[j] = str[i];
                j++;
            }
        }
        unify(arg2,makeconst(strdir));
        unify(arg3,makeconst(strname));
        unify(arg4,makeconst(strext));
        return(YES);
    }
    return(NO);
}

int b_environment_variable(int nest, int n){
    int arg1,arg2;
    char *str;

    if(n == 2){
        arg1 = deref(goal[2]); //variable
        arg2 = deref(goal[3]); //value
        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"environment_variable ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"environment_variable ",arg1);
        //if(!wide_variable_p(arg2))
        //    error(NOT_VAR,"environment_variable ",arg2);

        if((str = getenv(GET_NAME(arg1))) != NULL)
            unify(arg2,makeconst(str));
        else
            return(NO);

        return(YES);
    }
    return(NO);
}

int b_file_modification_time(int nest, int n){
    int arg1,arg2,res;

    struct stat attr;
    struct tm *t_st;



    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(wide_variable_p(arg1))
            error(INSTANTATION_ERR,"file_modification_time ",arg1);
        if(!atomp(arg1))
            error(NOT_ATOM,"file_modification_time ",arg1);
        //if(!wide_variable_p(arg2))
        //    error(NOT_VAR,"file_modification_time ",arg2);

        if(stat(GET_NAME(arg1), &attr) != 0)
		    return(NO);

        t_st = localtime(&attr.st_mtime);

        res = NIL;
        res = cons(makeint(t_st->tm_sec),res);
        res = cons(makeint(t_st->tm_min),res);
        res = cons(makeint(t_st->tm_hour),res);
        res = cons(makeint(t_st->tm_mday),res);
        res = cons(makeint(t_st->tm_mon+1),res);
        res = cons(makeint(t_st->tm_year+1900),res);
        res = cons(makeconst("stamp"),res);
        SET_AUX(car(res),PRED);
        unify(arg2,res);
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
    int q,r;

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
    r = s_remainder(x,y);
    if(zerop(r))
        return(q);
    else
        if(positivep(x) && negativep(y)){
            if(rounding_flag == 0) //toward_zero
                return(q);
            else //down
                return(minus(q,makeint(1)));
        }
        else if(negativep(x) && positivep(y)){
            if(rounding_flag == 0) //toward_zero
                return(q);
            else //down
                return(minus(q,makeint(1)));
        }
        else
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
    if(negativep(q) && !eqp(x,mult(y,q))){
        if(rounding_flag == 1) // toward_zero
        q = minus(q,makeint(1));
    }
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

#if __linux
//extension
//-------Socket TCP/IP--------

int b_server_create(int nest, int n){
    int arg1,arg2,arg3,sock,res;
    struct sockaddr_in addr;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[2]);

        if(!singlep(arg1))
            error(NOT_ATOM, "server_create", arg1);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_create", NIL);
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(GET_NAME(arg1)));
        addr.sin_addr.s_addr = INADDR_ANY;
        res = bind(sock, (struct sockaddr *)&addr, sizeof(addr));

        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_create", NIL);
        }

        res = listen(sock, 5);
        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_create", NIL);
        }

        unify(arg2,makeint(sock));
        return(YES);
    }

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        if(!singlep(arg1))
            error(NOT_ATOM, "server_create", arg1);

        if(!singlep(arg2))
            error(NOT_ATOM, "server_create", arg2);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_create", NIL);
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(GET_NAME(arg2)));
        addr.sin_addr.s_addr = inet_addr(GET_NAME(arg1));
        res = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_create", NIL);
        }

        res = listen(sock, 5);
        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_create", NIL);
        }
        unify(arg3,makeint(sock));
        return(YES);

    }
    return(NO);
}



int b_server_accept(int nest, int n){
    int arg1,arg2,arg3,sock0,sock;
    struct sockaddr_in client;
    socklen_t len;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        if(!integerp(arg1))
            error(NOT_INT, "server_accept", arg1);

        sock0 = GET_INT(arg1);
        len = sizeof(client);
        sock = accept(sock0, (struct sockaddr *)&client, &len);

        if(sock < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "server_accept", NIL);
        }
        unify(arg2,makeconst(inet_ntoa(client.sin_addr)));
        unify(arg3,makeint(sock));
        return(YES);
   }
   return(NO);
}



int b_client_connect(int nest, int n){
    int arg1,arg2,arg3,sock,res;
    struct sockaddr_in server;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        if(!singlep(arg1))
            error(NOT_ATOM, "client_connect", arg1);

        if(!singlep(arg2))
            error(NOT_ATOM, "client_connect", arg2);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(GET_NAME(arg2)));
        server.sin_addr.s_addr = inet_addr(GET_NAME(arg1));
        res = connect(sock, (struct sockaddr *)&server, sizeof(server));

        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "clinet_connect", NIL);
        }
        unify(arg3,makeint(sock));
        return(YES);
    }
    return(NO);
}


int b_socket_send(int nest, int n){
    int arg1,arg2,sock,len,res;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(!integerp(arg1))
            error(NOT_INT, "socket_recieve", arg1);

        sock = GET_INT(arg1);
        len = strlen(GET_NAME(arg2));
        res = send(sock, GET_NAME(arg2), len, 0);

        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "socket_send", NIL);
        }
        return(YES);
    }
    return(NO);
}

int b_socket_recieve(int nest, int n){
    int arg1,arg2,sock,res;
    char str[STRSIZE];

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(!integerp(arg1))
            error(NOT_INT, "socket_recieve", arg1);

        sock = GET_INT(arg1);
        memset(str, 0, sizeof(str));
        res = recv(sock, str, sizeof(str),0);

        if(res < 0){
            printf( "%s\n", strerror(errno) );
            error(TCPIP, "socket_recieve", NIL);
        }
        unify(arg2,makeconst(str));
        return(YES);
    }
    return(NO);
}

int b_socket_close(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        close(GET_INT(arg1));
        return(YES);
    }
    return(NO);
}

int b_nano(int nest, int n){
    int arg1,res;
    char str1[STRSIZE];
    char str0[STRSIZE] = "nano ";

    if(n == 1){
        arg1 = deref(goal[2]);
        if(!singlep(arg1))
            error(NOT_ATOM,"nano",arg1);

        strcpy(str1,GET_NAME(arg1));
        strcat(str0,str1);
        res = system(str0);
        if(res == -1)
            error(SYSTEM_ERROR,"nano",arg1);
        goal[2] = arg1;
        b_reconsult(0,1);
        return(YES);
    }
    return(NO);
}


#endif


//JUMP Project
int b_include_cut(int nest, int n){
	int arg1,clauses,clause;

    if(n == 1){
    	arg1 = deref(goal[2]);
        clauses = GET_CAR(arg1);
        while(!nullp(clauses)){
        	clause = car(clauses);
            if(clausep(clause) && GET_OPT(clause) == HASCUT)
            	return(YES);
            clauses = cdr(clauses);
        }
        return(NO);
    }
    return(NO);
}

int b_has_cut(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(has_cut_p(arg1))
        	return(YES);
        else
        	return(NO);
    }
    return(NO);
}

int b_has_c_lang(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(has_c_lang_p(arg1))
        	return(YES);
        else
        	return(NO);
    }
    return(NO);
}


int b_o_c_define(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        return(unify(arg1,define_list));
    }
    return(NO);
}

int b_o_c_include(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        return(unify(arg1,include_list));
    }
    return(NO);
}

int b_o_c_option(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        if(nullp(option_list))
        	option_list = makeconst(" ");
        return(unify(arg1,option_list));
    }
    return(NO);
}

int b_o_c_global(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        return(unify(arg1,listreverse(global_list)));
    }
    return(NO);
}

int b_c_lang(int nest, int n){
	if(n == 1){
    	return(YES);
    }
    return(NO);
}

int b_c_define(int nest, int n){
	int arg1,arg2;

    if(n == 2){
    	arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        define_list = listcons(listcons(arg1,arg2),define_list);
        return(YES);
    }
    return(NO);
}

int b_c_include(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        include_list = listcons(arg1,include_list);
        return(YES);
    }
    return(NO);
}

int b_c_option(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        option_list = arg1;
        return(YES);
    }
    return(NO);
}

int b_c_global(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        global_list = listcons(arg1,global_list);
        return(YES);
    }
    return(NO);
}



int b_generate_all_variable(int nest, int n){
	int arg1,arg2;

    if(n == 2){
    	arg1 = deref(goal[2]);
        arg2 = goal[3];
        return(unify(arg2,generate_all_variable(GET_CAR(arg1))));
    }
    return(NO);
}

int b_generate_variable(int nest, int n){
	int arg1,arg2;

    if(n == 2){
    	arg1 = deref(goal[2]);
        arg2 = goal[3];
        return(unify(arg2,generate_variable(arg1)));
    }
    return(NO);
}

int generate_all_variable(int x){
    int y,res;

    res = NIL;
    while(!nullp(x)){
    	y = variable_convert1(car(x));
    	if(clausep(y))
    		res = generate_variable1(caddr(y),
                   generate_variable1(cadr(y),res));
    	else
    		res = generate_variable1(y,res);

        x = cdr(x);
    }
    return(res);
}

int generate_variable(int x){
	if(clausep(x))
    	return(generate_variable1(caddr(x),
                   generate_variable1(cadr(x),NIL)));
    else
    	return(generate_variable1(x,NIL));
}

int generate_variable1(int x, int y){
    int temp;

    if(nullp(x))
    	return(y);
    else if(numberp(x))
    	return(y);
    else if(compiler_variable_p(x) && !memq(x,y)){
    	temp = cons(x,y);
        SET_AUX(temp,LIST);
        return(temp);
    }
    else if(singlep(x))
    	return(y);
    else if(car(x) == AND)
    	return(generate_variable1(cadr(x),generate_variable1(caddr(x),y)));
    else if(car(x) == OR)
    	return(generate_variable1(cadr(x),generate_variable1(caddr(x),y)));
    else
    	return(generate_variable1(car(x),generate_variable1(cdr(x),y)));
}

int b_generate_before_cut(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = goal[3];

        if(has_cut_p(arg1))
            unify(arg2,before_cut(arg1));
        else
            unify(arg2,arg1);
        return(YES);

    }
    return(NO);
}

int b_generate_after_cut(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = goal[3];

        if(has_cut_p(arg1))
            unify(arg2,after_cut(arg1));
        else
            unify(arg2,NIL);
        return(YES);
    }
    return(NO);
}

int b_generate_before_c_lang(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = goal[3];

        unify(arg2,before_c_lang(arg1));
        return(YES);
    }
    return(NO);
}

int b_generate_after_c_lang(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = goal[3];

        unify(arg2,after_c_lang(arg1));
        return(YES);
    }
    return(NO);
}



int b_generated_module(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        return(unify(arg2,GET_VAR(arg1)));
    }
    return(NO);
}

int b_compiler_anoymous(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);
        if(!!structurep(arg1))
            return(NO);
        else if(numberp(arg1))
        	return(NO);

        if(strcmp(GET_NAME(arg1),"var_") == 0)
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_compiler_variable(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);
        if(compiler_variable_p(arg1))
        	return(YES);
        else
        	return(NO);
    }
    return(NO);
}

int compiler_variable_p(int x){
	char str[256];

    if(numberp(x))
    	return(0);
    if(!!structurep(x))
    	return(0);
    strcpy(str,GET_NAME(x));
    str[3] = NUL;
    if(strcmp(str,"var") == 0)
    	return(1);
    else
    	return(0);
}


int b_defined_predicate(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(predicatep(arg1)){
            if(atomp(arg1) && GET_CAR(arg1) != NIL)
                return(YES);
            else if(structurep(arg1) && GET_CAR(car(arg1)) != NIL)
        	    return(YES);
            else
                return(NO);
        }
        else
        	return(NO);
    }
    return(NO);
}

int b_defined_userop(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(user_operation_p(arg1)){
            if(atomp(arg1) && GET_CAR(arg1) != NIL)
                return(YES);
            else if(structurep(arg1) && GET_CAR(car(arg1)) != NIL)
        	    return(YES);
            else
                return(NO);
        }
        else
        	return(NO);
    }
    return(NO);
}


int b_property(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        if(builtinp(arg1))
            return(unify(arg2,makeconst("builtin")));
        else if(predicatep(arg1))
            return(unify(arg2,makeconst("predicate")));
        else if(compiledp(arg1))
            return(unify(arg2,makeconst("compiled")));
        else if(operationp(arg1))
            return(unify(arg2,makeconst("operation")));
        else if(operatorp(arg1))
            return(unify(arg2,makeconst("operation")));
        else if(user_operation_p(arg1))
            return(unify(arg2,makeconst("userop")));
        else
            return(NO);

    }
    return(NO);
}


int b_isp(int nest, int n){
	int arg1,arg2,temp,vars;

    if(n == 2){
    	arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        if(builtinp(arg1) && car(arg1) == makeatom("is",SYS)){
        	temp = caddr(arg1);
            if(compiler_variable_p(temp))
            	return(unify(arg2,list1(temp)));
            else{
            	vars = NIL;
            	while(!nullp(temp)){
            		if(compiler_variable_p(car(temp)))
                		vars = listcons(car(temp),vars);
                	temp = cdr(temp);
            	}
            	return(unify(arg2,vars));
            }
        }
        else
        	return(NO);

    }
    return(NO);
}

int b_reconsult_predicate(int nest, int n){
	int arg1,lis,save1,save2,save3,save4;

    save1 = tp;
    save2 = sp;
    save3 = trail_end;
    if(n == 1){
    	arg1 = deref(goal[2]);
        if(!wide_variable_p(arg1))
            error(NOT_VAR,"o_reconsult_predicate ",arg1);

        lis = reverse(reconsult_list);
        save4 = wp;
        while(!nullp(lis)){
            unify(arg1,car(lis));
            if(proceed(NIL,nest) == YES)
                return(YES);

            lis = cdr(lis);
            wp = save4;
            unbind(save2);
        }
        tp = save1;
        wp = save4;
        unbind(save2);
        trail_end = save3;
        return(NO);
    }
    return(NO);
}

int b_reconsult_predicate_list(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = goal[2];

        unify(arg1,listreverse(reconsult_list));
        return(YES);
    }
    return(NO);
}

int b_arity_count(int nest, int n){
	int arg1,arg2;

    if(n == 2){
    	arg1 = deref(goal[2]);
        arg2 = goal[3];

        return(unify(arg2,listreverse(GET_ARITY(arg1))));
    }
    return(NO);
}

int b_filename(int nest, int n){
	int arg1,arg2,pos,len;
    char str1[STRSIZE];

    if(n == 2){
    	arg1 = deref(goal[2]);
        arg2 = goal[3];
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

int b_system(int nest, int n){
    int arg1,res;
    char str1[STRSIZE];

    if(n == 1){
        arg1 = deref(goal[2]);
        if(!singlep(arg1))
            error(NOT_ATOM,"system",arg1);

        strcpy(str1,GET_NAME(arg1));
        res = system(str1);
        if(res == -1)
            error(SYSTEM_ERROR,"system",arg1);
        return(YES);
    }
    return(NO);
}


int b_clause_with_arity(int nest, int n){
    int arg1,arg2,arg3,l,clause,clauses,res;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        if(!singlep(arg1))
            error(NOT_ATOM, "o_clause_with_arity", arg1);
        if(!integerp(arg2))
            error(NOT_INT, "o_clause_with_arity", arg2);

        clauses = GET_CAR(arg1);
        l = GET_INT(arg2);
        res = NIL;

        while(!nullp(clauses)){
            clause = car(clauses);
            if(atomp(clause) && l == 0)
                res = cons(clause,res);
            else if(predicatep(clause) && length(clause) == l+1)
                res = cons(clause,res);
            else if(clausep(clause) && atomp(cadr(clause)) && l == 0)
                res = cons(clause,res);
            else if(clausep(clause) && length(cadr(clause)) == l+1)
                res = cons(clause,res);

            clauses = cdr(clauses);
        }
        res = listreverse(res);
        unify(res,arg3);
        return(YES);
    }
    return(NO);
}


int b_variable_convert(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = goal[3];

        return(unify(arg2,variable_convert1(arg1)));
    }
    return(NO);
}

int variable_convert1(int x){
    int y;
    variable_convert4(NIL); //initialize anoymous N
    y = variable_convert2(x);
    if(clausep(x)){
    	SET_AUX(y,CLAUSE);
        SET_OPT(y,GET_OPT(x));
    }
    return(y);
}

int variable_convert2(int x){
    int y,z;

    if(nullp(x))
        return(NIL);
    else if(anoymousp(x))
        return(variable_convert4(x));
    else if(variablep(x))
        return(variable_convert3(x));
    else if(!structurep(x))
        return(x);
    else{
        y = GET_AUX(x);
        z = cons(variable_convert2(car(x)),
                variable_convert2(cdr(x)));
        SET_AUX(z,y);
        return(z);
    }

}

//normal variable X -> varX
int variable_convert3(int x){
    int res;
    char str[STRSIZE];

    strcpy(str,"var");
    strcat(str,GET_NAME(x));
    res = makeconst(str);
    return(res);
}

//anoymous variable _ -> varN (N=1...)
int variable_convert4(int x){
    int res;
    static int n;
    char str1[STRSIZE],str2[STRSIZE];

    //initialize
    if(x == NIL){
        n = 1;
        return(0);
    }

    strcpy(str1,"var");
    sprintf(str2,"%d",n);
    strcat(str1,str2);
    res = makeconst(str1);
    n++;
    return(res);
}




int b_self_introduction(int nest , int n){
	int arg1;

    if(n == 1){
    	arg1 = goal[2];
    	#if _WIN32
        	return(unify(arg1,makeconst("windows")));
        #elif __linux
        	return(unify(arg1,makeconst("linux")));
        #elif __OpenBSD__
        	return(unify(arg1,makeconst("openbsd")));
        #endif
    }
    return(NO);
}

int b_dynamic_check(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = deref(goal[2]);

        if(dynamic_check1(arg1))
            return(YES);
        else
        	return(NO);
    }
    return(NO);
}

int dynamic_check1(int x){
	int lis;

    lis = dynamic_list;
    while(!nullp(lis)){
    	if(eqlp(x,cadar(lis)))
        	return(1);
    	lis = cdr(lis);
    }
    return(0);
}

int b_get_dynamic(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = goal[2];
        return(unify(arg1,dynamic_list));
    }
    return(NO);
}

int b_get_execute(int nest, int n){
	int arg1;

    if(n == 1){
    	arg1 = goal[2];
        return(unify(arg1,execute_list));
    }
    return(NO);
}

int b_write_original_variable(int nest, int n){
	int arg1,pos;
    char str[STRSIZE];

    if(n == 1){
    	arg1 = deref(goal[2]);
        if(!compiler_variable_p(arg1))
        	return(NO);
        strcpy(str,GET_NAME(arg1));
        pos = 3;
        loop:
        	if(str[pos] == NUL)
            	return(YES);
            fprintf(GET_PORT(output_stream), "%c", str[pos]);
            pos++;
            goto loop;

    }
    return(NO);
}

//convert atom for C language function name
int b_atom_convert(int nest, int n){
    int arg1,arg2,pos1,pos2;
    char str1[ATOMSIZE],str2[ATOMSIZE];

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        strcpy(str1,GET_NAME(arg1));
        pos1 = 0;
        pos2 = 0;
        while(str1[pos1] != NUL){
            if(str1[pos1] == ':'){
                str2[pos2] = '_';
                pos2++;
            }
            else if(str1[pos1] == '&'){
                str2[pos2] = 'a';
                pos2++;
                str2[pos2] = 'n';
                pos2++;
                str2[pos2] = 'd';
                pos2++;
            }
            else if(str1[pos1] == '?'){
                str2[pos2] = 'm';
                pos2++;
                str2[pos2] = 'a';
                pos2++;
                str2[pos2] = 'g';
                pos2++;
            }
            else if(str1[pos1] == '+'){
                str2[pos2] = 'p';
                pos2++;
                str2[pos2] = 'l';
                pos2++;
                str2[pos2] = 's';
                pos2++;
            }
            else if(str1[pos1] == '-'){
                str2[pos2] = 'm';
                pos2++;
                str2[pos2] = 'n';
                pos2++;
                str2[pos2] = 's';
                pos2++;
            }
            else if(str1[pos1] == '*'){
                str2[pos2] = 'a';
                pos2++;
                str2[pos2] = 's';
                pos2++;
                str2[pos2] = 't';
                pos2++;
            }
            else if(str1[pos1] == '/'){
                str2[pos2] = 'd';
                pos2++;
                str2[pos2] = 'i';
                pos2++;
                str2[pos2] = 'v';
                pos2++;
            }
            else if(str1[pos1] == '>'){
                str2[pos2] = 'r';
                pos2++;
                str2[pos2] = 'i';
                pos2++;
                str2[pos2] = 'g';
                pos2++;
            }
            else if(str1[pos1] == '<'){
                str2[pos2] = 'l';
                pos2++;
                str2[pos2] = 'e';
                pos2++;
                str2[pos2] = 'f';
                pos2++;
            }
            else{
                str2[pos2] = str1[pos1];
                pos2++;
            }
            pos1++;
        }
        str2[pos2] = NUL;
        unify(arg2,makeconst(str2));
        return(YES);
    }
    return(NO);
}

int b_argument_list(int nest, int n){
    int arg1,arg2,res;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        arg1 = listreverse(cdr(arg1));
        res = NIL;
        while(!nullp(arg1)){
           res = listcons(car(arg1),res);
           arg1 = cdr(arg1);
        }
        return(unify(arg2,res));
    }
    return(NO);
}

int b_decompose(int nest, int n){
    int arg1,arg2,arg3;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        unify(arg2,car(arg1));
        unify(arg3,cdr(arg1));
        return(YES);
    }
    return(NO);
}

int b_findatom(int nest, int n){
    int arg1,arg2,arg3,res;

    if(n == 3){
        arg1 = deref(goal[2]); //atom
        arg2 = deref(goal[3]); //property
        arg3 = deref(goal[4]); //address

        res = NIL;
        if(eqlp(arg2,makeconst("constant")))
            res = findatom(arg1,SIMP);
        else if(eqlp(arg2,makeconst("predicate")))
            res = findatom(arg1,PRED);
        else if(eqlp(arg2,makeconst("builtin")))
            res = findatom(arg1,SYS);
        else if(eqlp(arg2,makeconst("compiled")))
            res = findatom(arg1,COMP);
        else if(eqlp(arg2,makeconst("operator")))
            res = findatom(arg1,OPE);
        else if(eqlp(arg2,makeconst("userop")))
            res = findatom(arg1,USER);
        else
            error(ILLEGAL_ARGS,"findatom ", arg2);

        return(unify(arg3,makeint(res)));
    }
    return(NO);
}

int b_bignum(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(bignump(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_longnum(int nest, int n){
    int arg1;

    if(n == 1){
        arg1 = deref(goal[2]);

        if(longnump(arg1))
            return(YES);
        else
            return(NO);
    }
    return(NO);
}

int b_dumpcell(int nest, int n){
    int arg1,arg2;

    if(n == 1){
        arg1 = deref(goal[2]);

        cellprint(GET_INT(arg1));
        return(YES);
    }
    else if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        heapdump(GET_INT(arg1),GET_INT(arg2));
        return(YES);
    }
    return(NO);
}


int b_sort(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        return(unify(arg2,sort(arg1)));
    }
    return(NO);
}

int b_keysort(int nest, int n){
    int arg1,arg2;

    if(n == 2){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);

        return(unify(arg2,keysort(arg1)));
    }
    return(NO);
}

int b_date(int nest, int n){
    int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
    struct tm* jst;
    time_t t;

    if(n == 3){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);

        t = time( NULL );
        jst = localtime( &t );
        unify(arg1,makeint(jst->tm_year));
        unify(arg2,makeint(jst->tm_mon));
        unify(arg3,makeint(jst->tm_mday));

        return(YES);
    }
    else if(n == 9){
        arg1 = deref(goal[2]);
        arg2 = deref(goal[3]);
        arg3 = deref(goal[4]);
        arg4 = deref(goal[5]);
        arg5 = deref(goal[6]);
        arg6 = deref(goal[7]);
        arg7 = deref(goal[8]);
        arg8 = deref(goal[9]);
        arg9 = deref(goal[10]);

        t = time( NULL );
        jst = localtime( &t );
        unify(arg1,makeint(jst->tm_year));
        unify(arg2,makeint(jst->tm_mon));
        unify(arg3,makeint(jst->tm_mday));
        unify(arg4,makeint(jst->tm_wday));
        unify(arg5,makeint(jst->tm_hour));
        unify(arg6,makeint(jst->tm_min));
        unify(arg7,makeint(jst->tm_sec));
        unify(arg8,makeint(jst->tm_yday));
        unify(arg9,makeint(jst->tm_isdst));

        return(YES);
    }
    return(NO);
}
