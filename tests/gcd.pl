% parser test from iitaka book

gcd1(A=A*1+B*0).
gcd1(D=A*X+B*Y):-
  res_q(A=B*Q+R),
  (A1,B1)=(B, R),
  gcd1(D=A1*X1+B1*Y1),
  T is X1-Y1*Q, (X,Y) = (Y1,T).

res_q(A=B*Q+R) :-
    Q is A // B,
    R is A mod B.