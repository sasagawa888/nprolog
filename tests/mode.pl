/*
mode inferencer  Idea memo

e.g.

% Partition list for quicksort
partition([X|L], Y, [X|L1], L2) :-
    X < Y, !, partition(L, Y, L1, L2).
partition([X|L], Y, L1, [X|L2]) :-
    !,partition(L, Y, L1, L2).
partition([], _ , [], []) :- !.

[X|L]と[X|L1]は同じ構造であり同じ変数Xを共有している。したがっていずれか一方が入力で他方が出力である。
[X|L]と[X|L2]は同じ構造であり同じ変数Xを共有している。したがっていずれか一方が入力で他方が出力である。
YはX<Yで使われている。したがって確定していなければいけないから第2引数は入力である。
これらのことから次の結論が得られる
mode(partition,[+,+,-,-]).
mode(partition,[-,+,+,+]).


% Quicksort
qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).
qsort([], R, R) :- !.

第1節の本体部でR1が現れておりこれは自由変数である。したがって第2引数は出力である。
第2節の頭部でRが2度現れている。したがって前者が入力であるのだから、後者が出力である。第2引数は入力、第3引数は出力である。
第1節の本体部でL1,L2が現れておりこれは自由変数である。したがってpartitionの第3、第4引数は出力である。
その場合にはすでに解析したようにLは入力である。したがって第1引数は入力である。

mode(qsort,[+,-,+]).


infer(Term,Env,Result) :- ... .
partition/4
Env is list  [var:+]
Result is list [+,+,-,-]

+ means input (instantated)
- means output (not instantated)

Env = [e(1,2),c(varY,+),c(varX,+),c(2,varY),c(1,varX)]
c/2　connect
e/2 exclusive

</2 >/2 =:=/2 /==/2 -> left and rigth must be +
right is left   -> right is -, left is +.


Prolog -> C 
input [X|L] -> x = car(a1);l=cdr(a1);
output [X|L] -> Jwcons(x,y,th);

multiple value retunr(JwlistN(A,B,...));

main:
int exec1(a1,a2){
}
int exec2(a3,a4){
}
if(Jvariablep(arg1) && Jvariablep(arg2)){
    res = exec1(deref(arg3,th),deref(arg4,th));
    Junify(arg1,Jnth(res,1));
    Junify(arg2,Jnth8res,2);
} else{
    res = exec2(deref(arg1,th),deref(arg2,th));
    Junify(arg3,Jnth(res,1));
    Junify(arg4,Jnth8res,2);
}
return(Jexec_all(...));
    

*/

/*
qsort1([], []).
qsort1([X|Xs], Ys) :-
    partition1(Xs, X, Ls, Gs),
    qsort1(Ls, SLs),
    qsort1(Gs, SGs),
    append(SLs, [X|SGs], Ys).

partition1([], _, [], []).
partition1([X|Xs], P, [X|Ls], Rs) :-
    X < P, !,
    partition1(Xs, P, Ls, Rs).
partition1([X|Xs], P, Ls, [X|Rs]) :-
    partition1(Xs, P, Ls, Rs).
*/

partition1(X,Y,L1,L2) :-
cinline($ //for qsort
          int exec1(int x, int y, int l1, int l2){
              Jinc_proof(th);
              if(x == NIL)
                  return(Jwlist2(l1,l2,th));
              else if(Jsmallerp(Jcar(x),y)){
                  Jinc_proof(th);
                  return(exec1(Jcdr(x),y,Jwlistcons(Jcar(x),l1,th),l2));
              }
              else return(exec1(Jcdr(x),y,l1,Jwlistcons(Jcar(x),l2,th)));
          }
          int x = Jderef(varX,th);
          int y = Jderef(varY,th);
          int res = exec1(Jcdr(x),y,NIL,NIL);
          Junify(varL1,Jcar(res),th);
          Junify(varL2,Jcar(Jcdr(res)),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).


qsort1(X,Y) :-
cinline($ //qsort
          int exec1(int a1){
            int x,l,l1,l2,r1,r2,r;
            Jinc_proof(th);
            l1 = Jmakevariant(th);
            l2 =  Jmakevariant(th);
            r = Jmakevariant(th);
              if(a1 != NIL){
                  x=Jcar(a1);l=Jcdr(a1);
                  Jcall(Jmakecomp("partition1"),Jwcons(a1,Jwlist3(x,l1,l2,th),th),th);
                  r1 =Jcar(exec1(Jderef(l1,th)));
                  r2 =Jcar(exec1(Jderef(l2,th)));
                  Jcall(Jmakesys("append"),Jwlist3(r1,Jwlistcons(x,r2,th),r,th),th);
                  Jinc_proof(th);
                  return(Jwlist1(Jderef(r,th),th));
              }
              else if(a1 == NIL){
                  return(Jwlist1(a1,th));
          }}
          int x = Jderef(varX,th);
          int res = Jcar(exec1(x));
          Junify(varY,res,th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).


qsort(X,Y,Z) :-
cinline($ //qsort
          int exec1(int a1, int r0){
            int x,l,l1,l2,r1,r2,r;
            Jinc_proof(th);
            l1 = Jmakevariant(th);
            l2 =  Jmakevariant(th);
            r = Jmakevariant(th);
              if(a1 != NIL){
                  x=Jcar(a1);l=Jcdr(a1);
                  Jcall(Jmakecomp("partition"),Jwcons(a1,Jwlist3(x,l1,l2,th),th),th);
                  r1 =Jcar(exec1(Jderef(l2,th),r0));
                  r2 =Jcar(exec1(Jderef(l1,th),Jwlistcons(x,r1,th)));
                  return(Jwlist1(r2,th));
              }
              else if(a1 == NIL){
                  return(Jwlist1(r0,th));
          }}
          int x = Jderef(varX,th);
          int z = Jderef(varZ,th);
          int res = Jcar(exec1(x,z));
          Junify(varY,res,th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).


partition(X,Y,L1,L2) :-
cinline($ //for qsort
          int exec1(int x, int y, int l1, int l2){
              Jinc_proof(th);
              if(x == NIL)
                  return(Jwlist2(l1,l2,th));
              else if(Jsmallerp(Jcar(x),y)){
                  Jinc_proof(th);
                  return(exec1(Jcdr(x),y,Jwlistcons(Jcar(x),l1,th),l2));
              }
              else return(exec1(Jcdr(x),y,l1,Jwlistcons(Jcar(x),l2,th)));
          }
          int x = Jderef(varX,th);
          int y = Jderef(varY,th);
          int res = exec1(Jcdr(x),y,NIL,NIL);
          Junify(varL1,Jcar(res),th);
          Junify(varL2,Jcar(Jcdr(res)),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).



% Reverse a list
nreverse([X|L0], L) :- nreverse(L0, L1), concatenate(L1, [X], L).
nreverse([], []) :- !.

% Concatenate two lists
concatenate([X|L1], L2, [X|L3]) :- !, concatenate(L1, L2, L3).
concatenate([], L, L) :- !.

% List of 30 elements for testing
list30([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 14, 15, 16, 17, 18, 19, 20, 
        21, 22, 25, 24, 25, 26, 27, 28, 29, 30]).

% List of 50 elements for another test
list50([27, 74, 17, 33, 94, 18, 46, 83, 65, 2, 32, 53, 28, 85, 99, 47, 28, 82, 6, 11,
        55, 29, 39, 81, 90, 37, 10, 0, 66, 51, 7, 21, 85, 27, 31, 63, 75, 4, 95, 99, 11, 28, 61,
        74, 18, 92, 40, 55, 59, 8]).

% Repeat a procedure
repeat_for(0) :- !, fail.
repeat_for(N).
repeat_for(N) :-
    M is N - 1,
    repeat_for(M).

% Run various tests
run(none, N) :- repeat_for(N), fail.


run(qsort, N) :-
    list50(X),
    repeat_for(N), 
    qsort(X, _, []), 
    fail.


run(qsort1, N) :-
    list50(X),
    repeat_for(N), 
    qsort1(X, _), 
    fail.


run(reverse, N) :-
    list30(X),
    repeat_for(N),
    nreverse(X, _),
    fail.

run(_,_).

% Testing and benchmarking
test(F, N) :-
    measure(run(F, N)).
    