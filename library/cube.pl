% Rubic cube　2*2

% notation
%  Front   Back
%  [1,2]  [5,6]
%  [4,3]  [8,7]
%
% Orinet [u,r,f,b,l,d] each element is 1,2,3,4,5,6 same as dices
% Dice-number = Color
% 1=white,2=blue,3=red,4=orage,5=green,6=yellow  
% Move   F(front), U(upper), R(Right)  G(Right rotate cube) H(Upper rotate cobe)
% Product  [F,U,R] = R(U(F))  
% Prolog expression f,u,r,fi(F-inverse),ui(U-inverse),ri(R-inverse)
% e.g. [f,u,r] [f,u,fi,ri]

:- module(cube,[init_cube/1,gen_cube/3,move/3,order/2,apply/3,try/1]).

%cube state
init_cube(cube([1,2,3,4,5,6,7,8],
                  [[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],
                   [1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])).

gen_cube(P,O,cube(P,O)).

move(f,cube(P,O),cube(P1,O1)) :-
    movef(P,O,P1,O1).
move(fi,cube(P,O),cube(P1,O1)) :-
    movef(P1,O1,P,O).
move(u,cube(P,O),cube(P1,O1)) :-
    moveu(P,O,P1,O1).
move(ui,cube(P,O),cube(P1,O1)) :-
    moveu(P1,O1,P,O).
move(r,cube(P,O),cube(P1,O1)) :-
    mover(P,O,P1,O1).
move(ri,cube(P,O),cube(P1,O1)) :-
    mover(P1,O1,P,O).
move(g,cube(P,O),cube(P1,O1)) :-
    moveg(P,O,P1,O1).
move(gi,cube(P,O),cube(P1,O1)) :-
    moveg(P1,O1,P,O).
move(h,cube(P,O),cube(P1,O1)) :-
    moveh(P,O,P1,O1).
move(hi,cube(P,O),cube(P1,O1)) :-
    moveh(P1,O1,P,O).

apply(M^N, S, S1) :-
    power(N,M,S,S1).
apply([], S, S).
apply([M|Ms], S0, S2) :-
    move(M, S0, S1),
    apply(Ms, S1, S2).

% F turn (clockwise looking at F face)
movef([P1,P2,P3,P4,P5,P6,P7,P8],
      [[O1u,O1r,O1f,O1b,O1l,O1d],[O2u,O2r,O2f,O2b,O2l,O2d],[O3u,O3r,O3f,O3b,O3l,O3d],[O4u,O4r,O4f,O4b,O4l,O4d],O5,O6,O7,O8],
      [P4,P1,P2,P3,P5,P6,P7,P8],
      [[O4l,O4u,O4f,O4b,O4d,O4r],[O1l,O1u,O1f,O1b,O1d,O1r],[O2l,O2u,O2f,O2b,O2d,O2r],[O3l,O3u,O3f,O3b,O3d,O3r],O5,O6,O7,O8]).

% U turn (clockwise looking at U face)
moveu([P1,P2,P3,P4,P5,P6,P7,P8],
      [[O1u,O1r,O1f,O1b,O1l,O1d],[O2u,O2r,O2f,O2b,O2l,O2d],O3,O4,[O5u,O5r,O5f,O5b,O5l,O5d],[O6u,O6r,O6f,O6b,O6l,O6d],O7,O8],
      [P5,P1,P3,P4,P6,P2,P7,P8],
      [[O5u,O5b,O5r,O5l,O5f,O5d],[O1u,O1b,O1r,O1l,O1f,O1d],O3,O4,[O6u,O6b,O6r,O6l,O6f,O6d],[O2u,O2b,O2r,O2l,O2f,O2d],O7,O8]).


% R turn (clockwise looking at R face)
mover([P1,P2,P3,P4,P5,P6,P7,P8],
      [O1,[O2u,O2r,O2f,O2b,O2l,O2d],[O3u,O3r,O3f,O3b,O3l,O3d],O4,O5,[O6u,O6r,O6f,O6b,O6l,O6d],[O7u,O7r,O7f,O7b,O7l,O7d],O8],
      [P1,P6,P2,P4,P5,P7,P3,P8],
      [O1,[O6f,O6r,O6d,O6u,O6l,O6b],[O2f,O2r,O2d,O2u,O2l,O2b],O4,O5,[O7f,O7r,O7d,O7u,O7l,O7b],[O3f,O3r,O3d,O3u,O3l,O3b],O8]).



% G turn all cube (clockwise looking at U face)
moveg([P1,P2,P3,P4,P5,P6,P7,P8],
      [[O1u,O1r,O1f,O1b,O1l,O1d],[O2u,O2r,O2f,O2b,O2l,O2d],[O3u,O3r,O3f,O3b,O3l,O3d],[O4u,O4r,O4f,O4b,O4l,O4d],
       [O5u,O5r,O5f,O5b,O5l,O5d],[O6u,O6r,O6f,O6b,O6l,O6d],[O7u,O7r,O7f,O7b,O7l,O7d],[O8u,O8r,O8f,O8b,O8l,O8d]],
      [P5,P1,P7,P3,P6,P2,P8,P4],
      [[O5u,O5b,O5r,O5l,O5f,O5d],[O1u,O1b,O1r,O1l,O1f,O1d],[O7u,O7b,O7r,O7l,O7f,O7d],[O3u,O3b,O3r,O3l,O3f,O3d],
       [O6u,O6b,O6r,O6l,O6f,O6d],[O2u,O2b,O2r,O2l,O2f,O2d],[O8u,O8b,O8r,O8l,O8f,O8d],[O4u,O4b,O4r,O4l,O4f,O4d]]).


% H turn all cube (clockwise lokking at R face)
moveh([P1,P2,P3,P4,P5,P6,P7,P8],
      [[O1u,O1r,O1f,O1b,O1l,O1d],[O2u,O2r,O2f,O2b,O2l,O2d],[O3u,O3r,O3f,O3b,O3l,O3d],[O4u,O4r,O4f,O4b,O4l,O4d],
       [O5u,O5r,O5f,O5b,O5l,O5d],[O6u,O6r,O6f,O6b,O6l,O6d],[O7u,O7r,O7f,O7b,O7l,O7d],[O8u,O8r,O8f,O8b,O8l,O8d]],
      [P4,P6,P2,P8,P1,P7,P3,P5],
      [[O4f,O4r,O4d,O4u,O4l,O4b],[O6f,O6r,O6d,O6u,O6l,O6b],[O2f,O2r,O2d,O2u,O2l,O2b],[O8f,O8r,O8d,O8u,O8l,O8b],
       [O1f,O1r,O1d,O1u,O1l,O1b],[O7f,O7r,O7d,O7u,O7l,O7b],[O3f,O3r,O3d,O3u,O3l,O3b],[O5f,O5r,O5d,O5u,O5l,O5b]]).


% order of operation M(move). N is order
order(M,N) :-
    init_cube(C),
    order1(0,N,M,C,C).

order1(N,N,M,C,C) :-
    N > 0.
order1(N,N2,M,C,C1) :-
    apply(M,C1,C2),
    N1 is N+1,
    order1(N1,N2,M,C,C2).



% iteration N times of M(move). C1 is result state of cube
power(0,M,C,C).
power(N,M,C,C1) :-
    apply(M,C,C2),
    N1 is N-1,
    power(N1,M,C2,C1).

try(M) :-
    init_cube(cube(P,O)),
    apply(M,cube(P,O),cube(P1,O1)),
    check(P,O,P1,O1).

check([],[],[],[]).
check([OP|OPs],[OO|OOs],[OP|RPs],[OO|ROs]) :-
    check(OPs,OOs,RPs,ROs).
check([OP|OPs],[OO|OOs],[RP|RPs],[RO|ROs]) :-
    write(position),write(OP),write('->'),write(RP),write(' '),
    write(orient),write(RO),nl,
    check(OPs,OOs,RPs,ROs).