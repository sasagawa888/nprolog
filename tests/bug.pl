% parser test

gcd(A=A*1+B*0).
gcd(D=A*X+B*Y):-
  res_q(A=B*Q+R),
  (A1,B1)=(B, R),
  gcd(D=A1*X1+B1*Y1),
  T is X1-Y1*Q, (X,Y) = (Y1,T).