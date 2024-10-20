/* quantum-number iitaka p41*/

:- op(700,xfx,isq).


X isq q(R1,I1,J1,K1)+q(R2,I2,J2,K2) :-
    R is R1 + R2,
    I is I1 + I2,
    J is J1 + J2,
    K is K1 + K2,
    X = q(R,I,J,K).

X isq q(R1,I1,J1,K1)-q(R2,I2,J2,K2) :-
    R is R1 - R2,
    I is I1 - I2,
    J is J1 - J2,
    K is K1 - K2,
    X = q(R,I,J,K).

X isq q(R1,I1,J1,K1)*q(R2,I2,J2,K2) :-
    R is R1*R2 - I1*I2 - J1*J2 - K1*K2,
    I is R1*I2 + I1*R2 + J1*K2 - K1*J2,
    J is R1*J2 - I1*K2 + J1*R2 + K1*I2,
    K is R1*K2 + J1*K2 - K1*I2 + K1*R2,
    X= q(R,I,J,K).

X isq q(R1,I1,J1,K1)/q(R2,I2,J2,K2) :-
    I3 is -I1,
    J3 is -J1,
    K3 is -K1,
    q(R4,I4,J4,K4) isq q(R1,I1,J1,K1)/q(R2,I2,J2,K2), 
    D is (R1^2) + (I1^2) + (J1^2) + (K1^2),
    R is R4/D,
    I is I4/D,
    J is J4/D,
    K is K4/D,
    X = q(R,I,J,K).

X isq conjugate(q(R,I,J,K)) :-
    X = q(R,-I,-J,-K).