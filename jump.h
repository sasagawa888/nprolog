#include <setjmp.h>
#include <stdio.h>


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

typedef int (*fn0)();
typedef int (*fn1)(int);
typedef int (*fn2)(int , int);
typedef int (*fn3)(int , int , int);
typedef int (*fn4)(char*);
typedef void (*tpred)(char*, int(*pred)(int , int));


fn0 f0[50];
fn1 f1[50];
fn2 f2[50];
fn3 f3[50];
fn4 f4[50];
tpred deftpred;
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

//for define system builtin predicate
void init_deftsys(tpred x){
    deftsys = (tpred)x;
}

#define Jcheckgbc()  (f0[0])()
#define Jgbc()	     (f0[1])()
#define Jfreshcell() (f0[2])()
#define Jmakevariant() (f0[3])()
#define Jget_sp()    (f0[4])()
#define Jget_wp()    (f0[5])()
#define Jdebug()     (f0[6])()
#define Jinc_proof() (f0[7])()

#define Jcar(x)      (f1[0])(x)
#define Jcdr(x)      (f1[1])(x)
#define Jcadr(x)     (f1[2])(x)
#define Jcaddr(x)    (f1[3])(x)
#define Jcaar(x)     (f1[4])(x)
#define Jcadar(x)    (f1[5])(x)
#define Jprint(x)    (f1[6])(x)
#define Jmakeint(x)  (f1[7])(x)

#define Junbind(x)   (f1[9])(x)
#define Jlength(x)   (f1[12])(x)
#define Jset_sp(x)   (f1[13])(x)

#define Jderef(x)    (f1[15])(x)

#define Jget_int(x)  (f1[17])(x)
#define Jsin(x)      (f1[18])(x)
#define Jasin(x)     (f1[19])(x)
#define Jcos(x)      (f1[20])(x)
#define Jacos(x)     (f1[21])(x)
#define Jtan(x)      (f1[22])(x)
#define Jatan(x)     (f1[23])(x)
#define Jexp(x)      (f1[24])(x)
#define Jlog(x)      (f1[25])(x)
#define Jfloor(x)    (f1[26])(x)
#define Jceiling(x)  (f1[27])(x)
#define Jtruncate(x) (f1[28])(x)
#define Jsign(x)     (f1[29])(x)
#define Jround(x)    (f1[30])(x)
#define Jlist1(x)    (f1[31])(x)

#define Jrandom(x)   (f1[33])(x)
#define Jset_wp(x)   (f1[34])(x)
#define Jwlist1(x)   (f1[35])(x)
#define Jexecute(x)  (f1[36])(x)

#define Jcons(x,y)   (f2[0])(x,y)
#define Jplus(x,y)   (f2[1])(x,y)
#define Jminus(x,y)  (f2[2])(x,y)
#define Jmult(x,y)   (f2[3])(x,y)
#define Jdivide(x,y) (f2[4])(x,y)
#define Jremainder(x,y) (f2[5])(x,y)
#define Jquotient(x,y) (f2[6])(x,y)
#define Jeqp(x,y)    (f2[7])(x,y)
#define Jnumeqp(x,y) (f2[8])(x,y)
#define Jsmallerp(x,y) (f2[9])(x,y)
#define Jeqsmallerp(x,y) (f2[10])(x,y)
#define Jgreaterp(x,y) (f2[11])(x,y)
#define Jeqgreaterp(x,y) (f2[12])(x,y)
#define Junify(x,y)      (f2[13])(x,y)
#define Jmod(x,y)		 (f2[14])(x,y)
#define Jgcd(x,y)        (f2[15])(x,y)
#define Jlcm(x,y)        (f2[16])(x,y)
#define Jexpt(x,y)       (f2[17])(x,y)
#define Jsqrt(x,y)       (f2[18])(x,y)
#define Jleftshift(x,y)  (f2[19])(x,y)
#define Jrightshift(x,y) (f2[20])(x,y)
#define Jlogicaland(x,y) (f2[21])(x,y)
#define Jlogicalor(x,y)  (f2[22])(x,y)
#define Jexclusiveor(x,y) (f2[23])(x,y)
#define Jinclusiveand(x,y) (f2[24])(x,y)
#define Jlistcons(x,y)     (f2[25])(x,y)
#define Jlist2(x,y)        (f2[26])(x,y)
#define Jset_car(x,y)      (f2[27])(x,y)
#define Jset_cdr(x,y)      (f2[28])(x,y)
#define Jrem(x,y)          (f2[29])(x,y)
#define Jcomplement(x)     (f2[30])(x,y)
#define Jset_aux(x,y)      (f2[31])(x,y)
#define Jnot_numeqp(x,y)   (f2[32])(x,y)
#define Jset_goal(x,y)     (f2[33])(x,y)
#define Jdiv(x,y)          (f2[34])(x,y)
#define Jset_var(x,y)      (f2[35])(x,y)
#define Jwcons(x,y)        (f2[36])(x,y)
#define Jwlist2(x,y)       (f2[37])(x,y)
#define Jwlistcons(x,y)    (f2[38])(x,y)
#define Jaddtail_body(x,y)      (f2[39])(x,y)


#define Jprove_all(x,y,z) (f3[0])(x,y,z)
#define Jlist3(x,y,z)       (f3[1])(x,y,z)
#define Jcallsubr(x,y,z)    (f3[2])(x,y,z)
#define Jwlist3(x,y,z)      (f3[3])(x,y,z)

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

