% Rubic cube　2*2

% notation
%  Front   Back
%  [1,2]  [5,6]
%  [4,3]  [8,7]
%
% Orinet [ud,lr,fb] each element is 0,1,2,
% Face   F(front), U(upper), R(Right)
% Product  FUR = F(U(R))  (from right hand to left hand)

%cube state
initial_cube(cube([0,1,2,3,4,5,6,7],[[0,1,2],[0,1,2],[0,1,2],[0,1,2],[0,1,2],[0,1,2],[0,1,2],[0,1,2]])).


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

% F turn (clockwise looking at F face)
movef([P1,P2,P3,P4,P5,P6,P7,P8],
      [[O1ud,O1lr,O1fb],[O2ud,O2lr,O2fb],[O3ud,O3lr,O3fb],[O4ud,O4lr,O4fb],O5,O6,O7,O8],
      [P4,P1,P2,P3,P5,P6,P7,P8],
      [[O4lr,O4ud,O4fb],[O1lr,O1ud,O1fb],[O2lr,O2ud,O2fb],[O3lr,O3ud,O3fb],O5,O6,O7,O8]).

% U turn (clockwise looking at U face)
moveu([P1,P2,P3,P4,P5,P6,P7,P8],
      [[O1ud,O1lr,O1fb],[O2ud,O2lr,O2fb],O3,O4,[O5ud,O5lr,O5fb],[O6ud,O6lr,O6fb],O7,O8],
      [P5,P1,P3,P4,P6,P2,P7,P8],
      [[O5ud,O5fb,O5lr],[O1ud,O1fb,O1lr],O3,O4,[O6ud,O6fb,O6lr],[O2ud,O2fb,O2lr],O7,O8]).


% R turn (clockwise looking at R face)
mover([P1,P2,P3,P4,P5,P6,P7,P8],
      [O1,[O2ud,O2lr,O2fb],[O3ud,O3lr,O3fb],O4,O5,[O6ud,O6lr,O6fb],[O7ud,O7lr,O7fb],O8],
      [P1,P6,P2,P4,P5,P7,P3,P8],
      [O1,[O6fb,O6lr,O6ud],[O2fb,O2lr,O2ud],O4,O5,[O7fb,O7lr,O7ud],[O3fb,O3lr,O3ud],O8]).

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
