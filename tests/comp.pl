
:- op(700,xfx,isc).

X isc c(R1,I1)+c(R2,I2) :- 
    R is R1+R2,
    I is I1+I2,
    X = c(R,I).

X isc c(R1,I1)-c(R2,I2) :- 
    R is R1-R2,
    I is I1-I2,
    X = c(R,I).

X isc c(R1,I1)*c(R2,I2) :- 
    R is R1*R2-I1*I2,
    I is R1*I2+I1*R2,
    X = c(R,I).

X isc c(R1,I1)/c(R2,I2) :- 
    D is R2^2+I2^2,
    R is (R1*R2-I1*I2)/D,
    I is (R1*I2+I1*R2)/D,
    X = c(R,I).

X isc conjugate(c(R,I)) :-
    X = c(R,-I).

X isc real_part(c(R,I)) :-
    X = R.

X isc imag_part(c(R,I)) :-
    X = I.

X isc abs(c(R,I)) :-
    X is sqrt(R^2+I^2).