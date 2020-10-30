/*
  dice puzzle

?- solve.
see https://qiita.com/sym_num/items/bc8bfb67fde98ce3787d
*/


data([[1,4,1,3,6,3,1,4,6,6,2,1,5,6,2,1,1,4],
      [5,4,2,4,5,5,5,5,5,3,2,3,5,4,2,3,5,5],
      [6,4,1,1,1,4,6,4,3,5,4,2,4,1,5,6,6,4],
      [2,4,2,3,5,5,1,2,6,2,6,5,1,2,6,3,2,2],
      [1,1,6,3,1,4,1,3,6,4,3,4,3,5,4,2,1,3],
      [5,3,2,5,1,2,5,5,1,2,1,2,6,1,3,6,6,5],
      [1,6,1,4,6,3,6,4,6,4,3,3,1,2,3,5,3,4],
      [2,2,6,5,1,2,2,5,5,5,6,5,1,2,6,2,1,2],
      [6,3,6,4,6,4,1,3,1,1,3,4,3,5,3,2,4,4],
      [5,5,5,4,2,3,5,4,2,3,1,2,6,6,1,6,1,5],
      [1,4,6,3,1,4,6,3,1,6,4,3,4,2,4,5,1,3],
      [5,2,1,5,6,2,2,4,5,3,6,5,1,2,6,5,1,2],
      [6,3,6,4,1,3,6,3,6,1,6,4,3,5,3,2,4,4],
      [2,5,2,4,2,5,1,2,5,4,2,3,6,6,3,1,4,6],
      [1,4,1,1,6,3,1,3,6,6,1,6,3,2,5,5,2,5],
      [1,5,6,3,5,3,5,4,2,3,5,4,3,1,4,6,4,1],
      [3,1,3,6,3,3,6,3,1,1,2,1,6,3,2,1,5,6],
      [6,5,1,2,6,5,1,5,1,2,6,5,5,3,2,4,5,3]]).

aref(R,C,X) :-
    data(M),
    row(R,M,V),
    col(C,V,X).

row(0,[V|Vs],V).
row(N,[V|Vs],X) :-
    N1 is N-1,
    row(N1,Vs,X).

col(0,[E|Es],E).
col(N,[E|Es],X) :-
    N1 is N-1,
    col(N1,Es,X).

diceU([F,B,U,D,L,R],[D,U,F,B,L,R]).
diceD([F,B,U,D,L,R],[U,D,B,F,L,R]).
diceL([F,B,U,D,L,R],[R,L,U,D,F,B]).
diceR([F,B,U,D,L,R],[L,R,U,D,B,F]).

%initial dice
dice([1,6,5,2,4,3]).

solve :- abolish(arrive/3),assert(arrive(-1,-1,-1)),dice(X),solve1(0,0,X,[]).

solve1(17,17,X,Root) :- write(Root).

%goto up
solve1(S,T,X,Root) :-
  S > 0,
  S1 is S - 1,
  not(arrive(S,T,down)),
  not(arrive(S1,T,up)),
  diceU(X,[F,B,U,D,L,R]),
  aref(S1,T,F),
  assertz(arrive(S1,T,up)),
  solve1(S1,T,[F,B,U,D,L,R],[[[S1,T],F]|Root]).

%goto right
solve1(S,T,X,Root) :-
  T < 17,
  T1 is T + 1,
  not(arrive(S,T,left)),
  not(arrive(S,T1,right)),
  diceR(X,[F,B,U,D,L,R]),
  aref(S,T1,F),
  assertz(arrive(S,T1,right)),
  solve1(S,T1,[F,B,U,D,L,R],[[[S,T1],F]|Root]).

%goto down
solve1(S,T,X,Root) :-
  S < 17,
  S1 is S + 1,
  not(arrive(S,T,up)),
  not(arrive(S1,T,down)),
  diceD(X,[F,B,U,D,L,R]),
  aref(S1,T,F),
  assertz(arrive(S1,T,down)),
  solve1(S1,T,[F,B,U,D,L,R],[[[S1,T],F]|Root]).

%goto left
solve1(S,T,X,Root) :-
  T > 0,
  T1 is T - 1,
  not(arrive(S,T,right)),
  not(arrive(S,T1,left)),
  diceL(X,[F,B,U,D,L,R]),
  aref(S,T1,F),
  assertz(arrive(S,T1,left)),
  solve1(S,T1,[F,B,U,D,L,R],[[[S,T1],F]|Root]).

