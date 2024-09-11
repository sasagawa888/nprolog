% parser test from iitaka book
% ?- gcd(D=12+X+23*Y).


gcd(A=A*1+0*0).
gcd(D=A*X+B*Y):-
  res_q(A=B*Q+R),
  (A1,B1)=(B, R),
  gcd(D=A1*X1+B1*Y1),
  T is X1-Y1*Q, (X,Y) = (Y1,T).

res_q(A=B*Q+R) :-
    Q is A // B,
    R is A mod B.

