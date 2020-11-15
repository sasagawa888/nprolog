%one-stroke


root(a,b,ab).
root(b,c,bc).
root(b,d,bd).
root(b,e,be).
root(c,e,ce).
root(c,d,cd).
root(d,e,de).
root(e,a,ae).

node([a,b,c,d,e]).
edge([ab,bc,bd,be,ce,cd,de,ae]).

run :- node(N),solve(N).

solve([]).
solve([N|Ns]) :-
   edge(E),solve1(N,E,[N]).
solve([N|Ns]) :-
  solve(Ns).

solve1(X,[],R) :- reverse(R,R1),write(R1),nl,fail.
solve1(X,E,R) :-
  root(X,Y,E1),
  delete1(E,E1,E2),
  solve1(Y,E2,[Y|R]).

solve1(X,E,R) :-
  root(Y,X,E1),
  delete1(E,E1,E2),
  solve1(Y,E2,[Y|R]).

delete1([X|Xs],X,Xs).
delete1([X|Xs],Y,[X|Z]) :-
  delete1(Xs,Y,Z).
