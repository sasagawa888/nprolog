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