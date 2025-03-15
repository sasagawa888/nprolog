# Compiler

# Usage
To use the compiler in N-Prolog, you need to load the module. Compilation is performed using compile_file/1.

```
N-Prolog Ver 3.91
?- use_module(compiler).
yes
?- compile_file('./tests/fact.pl').
phase pass1
phase pass2
compiling fact
invoke GCC
yes
?- 

```

# Option

- compile_file(F,c)
If you provide c as the second argument, the converted C code will be retained. You can check what kind of code is being generated.

- compile_file(F,o)
If you provide o as the second argument, it simply compiles the C source code and generates the object code. This is useful when you need to manually modify the compiled code.

- compile_file(F,co)
If you provide co as the second argument, it compiles prolog code and generate c source and object code.


# C inline
N-Prolog allows embedding C code in the body section. When a string is passed to cinline/1, it is directly embedded into the compiled code as is.

e.g.

```
ack(M,N,X) :-
cinline($ int a(int m, int n){
              if(m==0) return(n+1);
              else if(n==0) return(a(m-1,1));
              else return(a(m-1,a(m,n-1)));
          }
          int m = Jget_int(Jderef(varM,th));
          int n = Jget_int(Jderef(varN,th));
          int res = a(m,n);
          Junify(varX,Jmakeint(res),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).

```

## C inline declare
To embed C code such as #include and #define, use cdeclate/1.
e.g. 

```
cdeclare($#define a 1$).
cdeclare($#define b 2$).
cdeclare($#include <stdio.h>$).
```

## C inline library option
To add compilation options, use clibrary/1.
e.g. 

```
clibrary($-ltcl -ltk$).
```

## C inline variable
In compiled Prolog, variable names have 'var' prefixed to them at compile time. When retrieving a value, deref is called first, and then the value is converted to a C value using an API corresponding to its type.

## C inline API
The publicly available APIs that can be used for embedding in this context are as follows.

- static inline int Jcheckgbc(void)
- static inline int Jgbc(void)
- static inline int Jfreshcell(void)
- static inline int Jdebug(void) 
- static inline int Jcar(x)
- static inline int Jcdr(int x) 
- static inline int Jcadr(int x) 
- static inline int Jcaddr(int x) 
- static inline int Jcaar(int x) 
- static inline int Jcadar(int x) 
- static inline int Jprint(int x) 
- static inline int Jmakeint(int x) 
- static inline int Jlength(int x) 
- static inline int Jget_int(int x) 
- static inline int Jlist1(int x) 
- static inline int Jrandom(int th) 
- static inline int Jrandi(int x) 
- static inline int Jlistp(int x) 
- static inline int Jstructurep(int x) 
- static inline int Jvariablep(int x) 
- static inline int Jget_sp(int x) 
- static inline int Jget_wp(int x) 
- static inline int Jget_ac(int x) 
- static inline int Jinc_proof(int x) 
- static inline int Jmakevariant(int x) 
- static inline int Jadd_dynamic(int x) 
- static inline int Jbigx_to_parmanent(int x) 
- static inline int Jcons(int x, int y) 
- static inline int Jeqp(int x, int y) 
- static inline int Jequalp(int x, int y) 
- static inline int Jnumeqp(int x, int y) 
- static inline int Jsmallerp(int x, int y) 
- static inline int Jeqsmallerp(int x, int y) 
- static inline int Jgreaterp(int x, int y) 
- static inline int Jeqgreaterp(int x, int y) 
- static inline int Jlistcons(int x, int y) 
- static inline int Jlist2(int x, int y) 
- static inline int Jset_car(int x, int y)
- static inline int Jset_cdr(int x, int y)
- static inline int Jset_aux(int x, int y) 
- static inline int Jnot_numeqp(int x, int y) 
- static inline int Jset_var(int x, int y) 
- static inline int Jnth(int x, int y) 
- static inline int Junbind(int x, int th) 
- static inline int Jset_wp(int x, int th) 
- static inline int Jset_ac(int x, int th) 
- static inline int Jderef(int x, int th) 
- static inline int Jwlist1(int x, int th) 
- static inline int Jsin(int x, int th) 
- static inline int Jasin(int x, int th) 
- static inline int Jcos(int x, int th) 
- static inline int Jacos(int x, int th) 
- static inline int Jtan(int x, int th) 
- static inline int Jatan(int x, int th) 
- static inline int Jexp(int x, int th) 
- static inline int Jlog(int x, int th) 
- static inline int Jln(int x, int th) 
- static inline int Junify_nil(int x, int th) 
- static inline int Jlist3(int x, int y, int z) 
- static inline int Jerrorcomp(int x, int y, int z) 
- static inline int Jwlistcons(int x, int y, int th) 
- static inline int Junify(int x, int y, int th) 
- static inline int Junify_pair(int x, int y, int th) 
- static inline int Junify_var(int x, int y, int th) 
- static inline int Junify_int(int x, int y, int th) 
- static inline int Junify_long(int x, int y, int th) 
- static inline int Junify_big(int x, int y, int th) 
- static inline int Junify_str(int x, int y, int th) 
- static inline int Junify_atom(int x, int y, int th) 
- static inline int Jexec_all(int x, int y, int th) 
- static inline int Jwcons(int x, int y, int th) 
- static inline int Jwlist2(int x, int y, int th) 
- static inline int Jaddtail_body(int x, int y, int th) 
- static inline int Jplus(int x, int y, int th) 
- static inline int Jminus(int x, int y, int th) 
- static inline int Jmult(int x, int y, int th) 
- static inline int Jdivide(int x, int y, int th) 
- static inline int Jremainder(int x, int y, int th) 
- static inline int Jquotient(int x, int y, int th) 
- static inline int Jmod(int x, int y, int th) 
- static inline int Jexpt(int x, int y, int th) 
- static inline int Jsqrt(int x, int y, int th) 
- static inline int Jleftshift(int x, int y, int th) 
- static inline int Jrightshift(int x, int y, int th) 
- static inline int Jlogicaland(int x, int y, int th) 
- static inline int Jlogicalor(int x, int y, int th) 
- static inline int Jcomplement(int x, int y, int th) 
- static inline int Jround(int x, int y, int th) 
- static inline int Jdiv(int x, int y, int th) 
- static inline int Jcall(int pred, int arglist, int th)
  call predicate without continuation.
- static inline int Jmakeconst(char* x) 
- static inline int Jmakepred(char* x) 
- static inline int Jmakevar(char* x) 
- static inline int Jmakestrflt(char* x) 
- static inline int Jmakecomp(char* x) 
- static inline int Jmakesys(char* x) 
- static inline int Jmakeope(char* x) 
- static inline int Jmakeuser(char* x) 
- static inline int Jmakestrlong(char* x) 
- static inline int Jmakebig(char* x)
- static inline int Jmakestr(char* x) 
- static inline int Jmakefun(char* x) 
- static inline int Jcallsubr(int x, int y, int z, int th) 
- static inline int Jwlist3(int x, int y, int z, int th) 

# Internal of compiler
Since version 3.92, I have been rewriting the compiler. The previous compiler could optimize only a very limited subset of tail-recursive predicates. I am generalizing this optimization to cover a broader range of cases and improve execution efficiency.

Specifically, the compiler classifies predicates into the following three categories through static analysis: predicates eligible for tail-recursion optimization, deterministic predicates, and all other predicates.

The predicate analyze/1 in the compiler is responsible for this classification. The analysis results are stored in pred_data/3 in the form pred_data(PredName, Arity, TailOrDetOrHalt). The code generation predicates refer to this data to generate the corresponding C code.
