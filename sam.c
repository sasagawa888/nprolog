/*
SAM Sasagawa Abstract Machine
idea memo
fact(0,1).
fact(N,Y) :-
  N1 is N-1,
  fact(N1,Z),
  Y is N*Z.
SAS  ASEM
fact:
unify(A0,0),jrf(next),unify(A1,1),jrf(next),ret,
next:
unify(A0,N),retf,unify(A1,Y),retf,is(N1,-(N,1)),bias(2),pushB,ld(A0,N1),ld(A1,Z),call(fact),popB,is(Y,*(N,Z)).
byte code
unify,A0,0,jrf,4,unify,A1,1,jrf,2,ret,
unify,A0,N,retf,unify,A1,Y,retf,is,N1,-,N,1,bias,2,pushB,ld,A0,N1,ld,A1,Z,call,fact,popB,is,Y,*,N,Z.
list data
[1,2,3] -> cons(1,cons(2,3)) => cons,1,cons,2,3.
predicate
foo(a,b,c) -> foo,3,a,b,c.
atom -> heap
var -> variant area 
query ?- foo(X,Y,Z) -> ld,A0,X,ld,A1,Y,ld,A2,Z,call,foo.
*/

//register
int a1,a2,a3,a4,a5,a6,b;

//abstrct machine
void sam(){


}