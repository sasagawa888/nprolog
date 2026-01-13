# Cube library
library for 2*2 Rubik's Cube

# Usage

use_module(cube).

# Summary
Predicate	Purpose
init_cube/1	Create solved cube
gen_cube/3	Construct cube from raw data
move/3	Apply a single move
apply/3	Apply a sequence or power of moves
order/2	Compute order of a move or move sequence
try/1	Inspect changes caused by a move sequence
This structure makes the library suitable for group-theoretic exploration,
experimentation, and executable explanations of Rubik's Cube mathematics in
Prolog.

# Specifiction
Orinet [u,r,f,b,l,d] each element is 1,2,3,4,5,6 same as dices
Dice-number = Color
1=white,2=blue,3=red,4=orage,5=green,6=yellow 

- gen_cube/3
gen_cube(+Positions, +Orientations, -Cube)

Behavior
Constructs a cube term cube(P,O) directly from the given position list P
and orientation list O.
No validation is performed; this predicate is a simple constructor.

Examples
?- gen_cube(
     [1,2,3,4,5,6,7,8],
     [[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],
      [1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]],
     C).
C = cube([...], [...]).


- init_cube(C)
Behavior
Creates the solved (initial) state of the 2×2 Rubik’s Cube.
Piece positions are [1,2,3,4,5,6,7,8]
All pieces have the same default orientation [1,2,3,4,5,6]
This predicate is typically used as the starting point for all computations.

Examples
?- init_cube(C).
C = cube([1,2,3,4,5,6,7,8],
         [[1,2,3,4,5,6], ...]).


- move(+Move, +CubeBefore, -CubeAfter)

Behavior
Applies a single move to a cube state.
Supported moves:
Face turns
f, fi : Front (clockwise / inverse)
u, ui : Up (clockwise / inverse)
r, ri : Right (clockwise / inverse)
Whole-cube rotations
g, gi : rotate entire cube clockwise when looking at the U face
h, hi : rotate entire cube clockwise when looking at the R face
Inverse moves are implemented by reversing the forward transformation.

Examples
?- init_cube(C0),move(f,C0,C1).
C0 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])
C1 = cube_cube([4,1,2,3,5,6,7,8],[[5,1,3,4,6,2],[5,1,3,4,6,2],[5,1,3,4,6,2],[5,1,3,4,6,2],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]]) .
yes

?- init_cube(C0),move(fi,C0,C1).
C0 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])
C1 = cube_cube([2,3,4,1,5,6,7,8],[[2,6,3,4,1,5],[2,6,3,4,1,5],[2,6,3,4,1,5],[2,6,3,4,1,5],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]]) .
yes
?- 


- apply(+MoveExpr, +CubeBefore, -CubeAfter)
Behavior
Applies multiple moves to a cube state.
Two forms of MoveExpr are supported:
List of moves
Moves are applied from left to right.
[f,u,r]  ≡  R(U(F(C)))

Power notation M^N
applies move M exactly N times.

Examples
% List of moves
?- init_cube(C0),apply([f,u,r],C0,C1).
C0 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])
C1 = cube_cube([5,1,4,3,6,7,2,8],[[1,4,2,5,3,6],[1,4,2,5,3,6],[1,4,2,5,3,6],[5,1,3,4,6,2],[1,4,2,5,3,6],[3,2,6,1,5,4],[3,1,2,5,6,4],[1,2,3,4,5,6]]) .
yes

% Atom of moves
?- init_cube(C0),apply(f,C0,C1).
C0 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])
C1 = cube_cube([4,1,2,3,5,6,7,8],[[5,1,3,4,6,2],[5,1,3,4,6,2],[5,1,3,4,6,2],[5,1,3,4,6,2],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]]) .
yes

% Repeated move
?- init_cube(C0),apply(f^4,C0,C1).
C0 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])
C1 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]]) .
yes
?- init_cube(C0),apply([f,u,r]^3,C0,C1).
C0 = cube_cube([1,2,3,4,5,6,7,8],[[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6]])
C1 = cube_cube([7,6,4,3,2,1,5,8],[[3,5,1,6,2,4],[1,3,5,2,4,6],[3,5,1,6,2,4],[3,5,1,6,2,4],[2,3,1,6,4,5],[4,1,5,2,6,3],[4,1,5,2,6,3],[1,2,3,4,5,6]]) .
yes
?- 

- order(+MoveExpr, -N)

Behavior
Computes the order of a move or move sequence.
N is the smallest positive integer such that applying MoveExpr N times
returns the cube to the initial state.
Internally, the predicate repeatedly applies the move starting from the solved
cube until the original state is reached again.

Examples
?- order(f, N).
N = 4.

?- order([f,u,r], N).
N = 30 .

- try(+MoveExpr)

Behavior
A debugging and inspection utility.
Applies MoveExpr to the initial cube
Compares the result with the initial state
Prints only the pieces that changed
For each changed piece, it prints:
old position → new position
new orientation

Examples
?- try([f,u,r]).
position1->5 orient[1,4,2,5,3,6]
position2->1 orient[1,4,2,5,3,6]
position3->4 orient[1,4,2,5,3,6]
position4->3 orient[5,1,3,4,6,2]
position5->6 orient[1,4,2,5,3,6]
position6->7 orient[3,2,6,1,5,4]
position7->2 orient[3,1,2,5,6,4]
yes
?- 

