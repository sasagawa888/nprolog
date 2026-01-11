% Rubic cube　2*2

% notation
%  Front   Back
%  [1,2]  [5,6]
%  [4,3]  [8,7]
%
% Orinet [u,r,f,b,l,d] each element is 1,2,3,4,5,6 same as dices
% Dice-number = Color
% 1=white,2=blue,3=red,4=orage,5=green,6=yellow  
% Face   F(front), U(upper), R(Right)
% Product  FUR = F(U(R))  (from right hand to left hand)

%cube state
initial_cube(cube([1,2,3,4,5,6,7,8],
                  [[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],
                   [1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])).


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


% order of operation M(move). N is order
order(M,N) :-
    initial_cube(C),
    order1(0,N,M,C,C).

order1(N,N,M,C,C) :-
    N > 0.
order1(N,N2,M,C,cube(P,O)) :-
    Pred =.. [M,P,O,P1,O1],
    call(Pred),
    N1 is N+1,
    order1(N1,N2,M,C,cube(P1,O1)).

% iteration N times of M(move). C1 is result state of cube
iterate(N,M,C1) :-
    initial_cube(C),
    iterate1(N,M,C,C1).
iterate1(0,M,C,C).
iterate1(N,M,cube(P,O),C) :-
    Pred =.. [M,P,O,P1,O1],
    call(Pred),
    N1 is N-1,
    iterate1(N1,M,cube(P1,O1),C).

% F-U-R
movefur(P,O,P3,O3) :-
    mover(P,O,P1,O1),
    moveu(P1,O1,P2,O2),
    movef(P2,O2,P3,O3).

% R-U-F
moveruf(P,O,P3,O3) :-
    movef(P,O,P1,O1),
    moveu(P1,O1,P2,O2),
    mover(P2,O2,P3,O3).

% F-R-U
movefru(P,O,P3,O3) :-
    moveu(P,O,P1,O1),
    mover(P1,O1,P2,O2),
    movef(P2,O2,P3,O3).

% commutator F R
commfr(P,O,P4,O4) :-
    movef(P1,O1,P,O),    %F-1
    mover(P2,O2,P1,O1),  %R-1
    movef(P2,O2,P3,O3),  %F
    mover(P3,O3,P4,O4).  %R


% commutator U R
commur(P,O,P4,O4) :-
    moveu(P1,O1,P,O),    %U-1
    mover(P2,O2,P1,O1),  %R-1
    moveu(P2,O2,P3,O3),  %U
    mover(P3,O3,P4,O4).  %R

% commutator F U
commfu(P,O,P4,O4) :-
    movef(P1,O1,P,O),    %F-1
    moveu(P2,O2,P1,O1),  %U-1
    movef(P2,O2,P3,O3),  %F
    moveu(P3,O3,P4,O4).  %U



try1(M1) :-
    initial_cube(cube(P,O)),
    Pred1 =.. [M1,P,O,P1,O1],
    call(Pred1),
    check(P,O,P1,O1).

try2(M1,M2) :-
    initial_cube(cube(P,O)),
    Pred1 =.. [M1,P,O,P1,O1],
    call(Pred1),
    Pred2 =.. [M2,P1,O1,P2,O2],
    call(Pred2),
    check(P,O,P2,O2).

check([],[],[],[]).
check([OP|OPs],[OO|OOs],[OP|RPs],[OO|ROs]) :-
    check(OPs,OOs,RPs,ROs).
check([OP|OPs],[OO|OOs],[RP|RPs],[RO|ROs]) :-
    write(position),write(OP),write('->'),write(RP),write(' '),
    write(orient),write(RO),nl,
    check(OPs,OOs,RPs,ROs).