
sum1(0,0) :- !.
sum1(J,S1) :- I is J-1,sum1(I,S),S1 is S + J.

sum2(0,0).
sum2(J,S1) :- J>0,I is J-1,sum2(I,S),S1 is S + J.