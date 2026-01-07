% Rubic cube

% notation
%  Front   Back
%  [1,2]  [5,6]
%  [3,4]  [7,8]
%
% Orinet 0,1,2 (mod 3)
% orientation = twist of a corner relative to U/D axis
% 0 means the U/D color is on U or D face
% initial is [0,0,0,0,0,0,0,0]

movef([P1,P2,P3,P4,P5,P6,P7,P8],[O1,O2,O3,O4,O5,O6,O7,O8],
      [P4,P1,P2,P3,P5,P6,P7,P8],[N1,N2,N3,N4,O5,O6,O7,O8]) :-
        N1 is (O1+1) mod 3,
        N2 is (O2+1) mod 3,
        N3 is (O3+1) mod 3,
        N4 is (O4+1) mod 3.


