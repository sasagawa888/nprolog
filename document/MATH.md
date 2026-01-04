# N-Prolog Mathematics Library Reference
This module provides basic mathematical and set-theoretical tools for symbolic computation, including sets, functions, topology, and permutations.

math Module Reference
use_module(math).

🔢 Set Operations
union(X,Y,Z)

Description: Z is the union of sets X and Y
Example:

% example goes here

intersection(X,Y,Z)

Description: Z is the intersection of X and Y
Example:

% example goes here

difference(X,Y,Z)

Description: Z is the set difference X - Y
Example:

% example goes here

subset(X,Y)

Description: X is a subset of Y
Example:

% example goes here

eqset(X,Y)

Description: X and Y are equal sets
Example:

% example goes here

powerset(X,P)

Description: P is the powerset of set X
Example:

% example goes here

permutation(X,Y)

Description: Y is a permutation of list X
Example:

% example goes here

🔢 Infix Notation for Sets
Z isl X + Y

Description: Z is the union of X and Y
Example:

% example goes here

Z isl X - Y

Description: Z is the difference of X and Y
Example:

% example goes here

Z isl X * Y

Description: Z is the intersection of X and Y
Example:

% example goes here

Z isl subset(X)

Description: Z is a subset of X
Example:

% example goes here

🧭 Map Functions
map_val(F,X,Y)

Description: Y is the image of X under map F
Example:

% example goes here

map_set(F,X,Ys)

Description: Ys is the image set of X under map F
Example:

% example goes here

map_prod(F,G,H)

Description: H is the composition of maps F and G
Example:

% example goes here

map_inv(F,G)

Description: G is the inverse of map F
Example:

% example goes here

list_map(List,Map)

Description: Converts a list into a map from index to value
Example:

% example goes here

map_list(F,L)

Description: Extracts the codomain of map F
Example:

% example goes here

🧭 Infix Notation for Maps
Z ism val(F,X)

Description: map_val(F,X,Z)
Example:

% example goes here

Z ism set(F,X)

Description: map_set(F,X,Z)
Example:

% example goes here

Z ism X * Y

Description: map_prod(X,Y,Z)
Example:

% example goes here

Z ism 1 // X

Description: map_inv(X,Z)
Example:

% example goes here

🎯 Logic Control
forall(P,Q)

Description: Succeeds if Q holds for all P
Example:

% example goes here

🔷 Topology
topology(O,Z)

Description: Checks if O is a topology on set Z
Example:

% example goes here

topology_space(X,O)

Description: True if O is a topology on base set X
Example:

% example goes here

🔁 Surjections and Injections
surjection(F,S,T)

Description: F maps S onto T (surjective)
Example:

% example goes here

injection(F,S,_)

Description: F maps S injectively (distinct elements map to distinct images)
Example:

% example goes here

🔀 Permutations
perm_prod(X,Y,Z)

Description: Z is the composition of X and Y
Example:

% example goes here

perm_inv(X,Z)

Description: Z is the inverse of permutation X
Example:

% example goes here

perm_div(X,Y,Z)

Description: Z is the result of dividing X by Y
Example:

% example goes here

perm_ident(N,X)

Description: X is the identity permutation of size N
Example:

% example goes here

perm_inversion(P,N)

Description: N is the number of inversions in P
Example:

% example goes here

perm_sign(P,Sign)

Description: Sign is the sign of permutation P
Example:

% example goes here

perm_expt(X,N,Z)

Description: Z is the exponentiation X^N
Example:

% example goes here

perm_even(X,Z)

Description: Z is an even permutation of X
Example:

% example goes here

perm_odd(X,Z)

Description: Z is an odd permutation of X
Example:

% example goes here

🔀 Infix Notation for Permutations
Z isq X * Y

Description: perm_prod(X,Y,Z)
Example:

% example goes here

Z isq 1 // X

Description: perm_inv(X,Z)
Example:

% example goes here

Z isq X / Y

Description: perm_div(X,Y,Z)
Example:

% example goes here

Z isq X ^ N

Description: perm_expt(X,N,Z)
Example:

% example goes here

🏛 Groupe (Group)
groupe_prod(X,Y,Z)

Description: Z is the composition of ID-X and ID-Y
Example:

% example goes here

groupe_create(perm,N)

Description: Creates and asserts X as a permutation
Example:

% example goes here

groupe_create(even,N)

Description: Creates and asserts X as an even permutation
Example:

% example goes here

groupe_create(odd,N)

Description: Creates and asserts X as an odd permutation
Example:

% example goes here

🏛 Infix Notation for Groupe
Z isg X * Y

Description: groupe_prod(X,Y,Z)
Example:

% example goes here

Z isg (X * Y) * Z

Description: Associative composition
Example:

% example goes here

Z isg X * (Y * Z)

Description: Associative composition
Example:

% example goes here

📌 Notes

Sets are represented as sorted lists without duplicates.

Maps are represented as lists of value:key pairs (e.g., 1:a).

Permutations are lists of integers representing bijections.

Custom infix operators (isl, ism, isq, isg) are defined for readable symbolic notation.

Examples can be added in the Example section for clarity.
