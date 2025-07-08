/*
* ex to understand quantum computing

*/


% simple version
polar(c(R,I),p(A,S)) :-
    A is sqrt(R^2+I^2),
    S is acos(R/A).

% product of complex vector
cprod(c(R1,I1),c(R2,I2),c(R3,I3)) :-
    R3 is R1*R2-I1*I2,
    I3 is R1*I2+R2*I1.

% add complex 
cadd(c(R1,I1), c(R2,I2), c(R3,I3)) :-
    R3 is R1 + R2,
    I3 is I1 + I2.

% dot product 
cdot([], [], c(0,0)).
cdot([A|As], [B|Bs], Z) :-
    cprod(A, B, P),
    cdot(As, Bs, Z1),
    cadd(P, Z1, Z).

% product of unitaly matrix and vector
mprod([],X,[]).
mprod([M|Ms],X,[Z|Zs]) :-
    cdot(M,X,Z),
    mprod(Ms,X,Zs).

% interference of V -> Z
interference(V,Z) :-
    interference1(V,Z1),
    polar(Z1,Z).

interference1([],c(0,0)).
interference1([V|Vs],Z) :-
    interference1(Vs,Z1),
    cadd(V,Z1,Z).

state([c(1,0), c(0,0), c(0,0), c(0,0)]).
hadamard([[c(0.5, 0), c(0.5, 0), c(0.5, 0), c(0.5, 0)],
          [c(0.5, 0), c(-0.5, 0), c(0.5, 0), c(-0.5, 0)],
          [c(0.5, 0), c(0.5, 0), c(-0.5, 0), c(-0.5, 0)],
          [c(0.5, 0), c(-0.5, 0), c(-0.5, 0), c(0.5, 0)]]).

hadamard1([[c(0.7071,0), c(0.0,0),   c(0.7071,0), c(0.0,0)],
          [c(0.0,0),   c(0.7071,0), c(0.0,0),    c(0.7071,0)],
          [c(0.7071,0), c(0.0,0),   c(-0.7071,0), c(0.0,0)],
          [c(0.0,0),   c(0.7071,0), c(0.0,0),    c(-0.7071,0)]]).

cnot([[c(1,0), c(0,0), c(0,0), c(0,0)],
      [c(0,0), c(1,0), c(0,0), c(0,0)],
      [c(0,0), c(0,0), c(0,0), c(1,0)],
      [c(0,0), c(0,0), c(1,0), c(0,0)]]).

amplitude([],[]).
amplitude([c(R,I)|Vs],[Y|Ys]) :-
    Y is r^2,
    amplitude(Vs,Ys).

probability(V,V1) :-
    amplitude(V,A),
    probability1(V,V1,A).

probarbility1([],[],A).
probarbirity1([V|Vs],[P|Ps],A) :-
    P is V / A,
    probarbility1(Vs,Ps,A).

test(I) :-
    state(S),
    hadamard1(H),
    mprod(H, S, R),
    interference(R,I).

test1(V) :-
    state(S),
    hadamard1(H),
    mprod(H, S, R),
    cnot(C),
    mprod(C,R,V).