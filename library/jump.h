#include <setjmp.h>
#include <stdio.h>

#define CELLSIZE 10000000
#define FREESIZE      300
#define STACKSIZE   300000
#define CTRLSTKSIZE  1000
#define VARIANTSIZE 1000000
#define VARIANTMAX  11000000
#define ATOMSIZE 256
#define BUFSIZE 256
#define STRSIZE 256
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
#define OPLTRUE 32
#define OPLFALSE    34
#define CURL    36
#define IFTHEN  38
#define NUMVAR  40
#define UNDERBAR    42
#define DOTOBJ  44
#define HASHTBSIZE 107
#define BIGNUM_BASE 1000000000
#define SMALL_INT_MAX       1000000000
#define SMALL_INT_MIN       -1000000000
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
// following are data for SJIS transform
#define SJIS1       65280      //#b1111111100000000
#define SJIS2       255        //#b0000000011111111



//operator 
#define XFX 1
#define XFY 2
#define YFX 3
#define FX  4
#define FY  5
#define XF  6
#define YF  7 

//clause option
#define HASCUT  100 //the clause has cut operator
#define CUTING  101 //the clause that has cut is now on executing.

//atom type
#define SIMP   1 //constant
#define VAR     2 //variable
#define ANOY    3 //anoimouse
#define FUN     4 //function operator
#define OPE     5 //operator
#define PRED    6 //user defined predicate
#define SYS     7 //system predicate
#define CLAUSE  8 //clause
#define COMP    9 //compiled predicate
#define LIST    10 //list created by univ ( SET_VAR(x,LIST) )


//-------read--------
#define EOL     '\n'
#define TAB     '\t'
#define SPACE   ' '
#define ESCAPE  033
#define NUL     '\0'


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
jmp_buf cut_buf[1000];
int cut_pt;
int cut_dt[1000][3];

void init0(int n, int x){
    f0[n] = (fn0)x;
}

void init1(int n, int x){
    f1[n] = (fn1)x;
}

void init2(int n, int x){
    f2[n] = (fn2)x;
}

void init3(int n, int x){
    f3[n] = (fn3)x;
}

void init4(int n, int x){
    f4[n] = (fn4)x;
}

//for define compiled builtin predicate
void init_deftpred(int x){
    deftpred = (tpred)x;
}


#define Jcheckgbc()  (f0[0])()
#define Jgbc()	     (f0[1])()
#define Jfreshcell() (f0[2])()
#define Jmakevariant() (f0[3])()
#define Jget_tp()    (f0[4])()
#define Jget_sp()    (f0[5])()
#define Jprint_trail_block() (f0[6])()
#define Jdec_cut()   (f0[7])()
#define Jpop_cut()   (f0[8])()
#define Jpush_cut()  (f0[9])()
#define Jget_cut_jmp() (f0[10])()
#define Jget_trail_end() (f0[11])()
#define Jdebug()     (f0[12])()
#define Jget_wp()    (f0[13])()

#define Jcar(x)      (f1[0])(x)
#define Jcdr(x)      (f1[1])(x)
#define Jcadr(x)     (f1[2])(x)
#define Jcaddr(x)    (f1[3])(x)
#define Jcaar(x)     (f1[4])(x)
#define Jcadar(x)    (f1[5])(x)
#define Jprint(x)    (f1[6])(x)
#define Jmakeint(x)  (f1[7])(x)
#define Jexecute(x)  (f1[8])(x)
#define Junbind(x)   (f1[9])(x)
#define Jpush_trail_body(x) (f1[10])(x)
#define Jget_goal(x) (f1[11])(x)
#define Jset_tp(x)   (f1[12])(x)
#define Jset_sp(x)   (f1[13])(x)
#define Jset_length(x) (f1[14])(x)
#define Jderef(x)    (f1[15])(x)
#define Jretract_goal(x) (f1[16])(x)
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
#define Jset_trail_end(x) (f1[32])(x)
#define Jrandom(x)   (f1[33])(x)
#define Jset_wp(x)   (f1[34])(x)
#define Jwlist1(x)   (f1[35])(x)
#define Jdisplay(x)  (f1[36])(x)

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
#define Jproceed(x,y)      (f2[39])(x,y)

#define Jresolve_all(x,y,z) (f3[0])(x,y,z)
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

//for cut operator
void init_cut(void){
	cut_pt = 0;
}

void invoke_cut(void){
    longjmp(cut_buf[1],1);
}

