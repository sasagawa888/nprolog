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



</2 >/2 =:=/2 /==/2 -> left and rigth must be +
right is left   -> right is -, left is +.
*/


partition(X,Y,L1,L2) :-
cinline($ //for qsort
          int exec1(int x, int y, int l1, int l2){
              if(x == NIL)
                  return(Jlist2(l1,l2));
              else if(Jsmallerp(Jcar(x),y))
                  return(exec1(Jcdr(x),y,Jlistcons(Jcar(x),l1),l2));
              else return(exec1(Jcdr(x),y,l1,Jlistcons(Jcar(x),l2)));
          }
          int x = Jderef(varX,th);
          int y = Jderef(varY,th);
          int res = exec1(x,y,NIL,NIL);
          Junify(varL1,Jcar(res),th);
          Junify(varL2,Jcar(Jcdr(res)),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).


% Quicksort
qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).
qsort([], R, R) :- !.

/*
qsort(X,Y) :-
cinline($ //qsort
          int exec1(int x, int y){
              if(x == NIL)
                  return(y);
              else{
                  int l1,l2;
                  Jcall(Jmakecomp("partition"),Jlist3(x,l1,l2));
                  return(exec1(l1,y);
          }
          int x = Jderef(varX,th);
          int y = Jderef(varY,th);
          int res = exec1(x,y,NIL,NIL);
          Junify(varL1,Jcar(res),th);
          Junify(varL2,Jcar(Jcdr(res)),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).
*/