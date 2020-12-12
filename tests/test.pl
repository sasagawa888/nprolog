
sum1(0,0) :- !.
sum1(J,S1) :- I is J-1,sum1(I,S),S1 is S + J.
