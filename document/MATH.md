# N-Prolog Mathematics Library Reference
This module provides basic mathematical and set-theoretical tools for symbolic computation, including sets, functions, topology, and permutations.

---

## Module Declaration

```prolog
:- module(math, [...]).

Exported Predicates (Grouped by Category):
🔢 Set Operations
Predicate	Description
union(X,Y,Z)	Z is the union of sets X and Y
intersection(X,Y,Z)	Z is the intersection of X and Y
difference(X,Y,Z)	Z is the set difference X - Y
subset(X,Y)	X is a subset of Y
eqset(X,Y)	X and Y are equal sets
powerset(X,P)	P is the powerset of set X
permutation(X,Y)	Y is a permutation of list X
✅ Set Notation (Infix Syntax)
Operator	Meaning
Z isl X + Y	Z is the union of X and Y
Z isl X - Y	Z is the difference of X and Y
Z isl X * Y	Z is the intersection of X and Y
Z isl subset(X)	Z is a subset of X
🧭 Map Functions
Predicate	Description
map_val(F,X,Y)	Y is the image of X under map F
map_set(F,X,Ys)	Ys is the image set of X under map F
map_prod(F,G,H)	H is the product (composition) of F and G
map_inv(F,G)	G is the inverse of map F
list_map(List,Map)	Converts a list into a map from index to value
map_list(F,L)	Extracts the codomain of map F
Infix Notation for Maps
Operator	Meaning
Z ism val(F,X)	map_val(F,X,Z)
Z ism set(F,X)	map_set(F,X,Z)
Z ism X * Y	map_prod(X,Y,Z)
Z ism 1 // X	map_inv(X,Z)
🎯 Logic Control
Predicate	Description
forall(P,Q)	Succeeds if Q holds for all P
🔷 Topology
Predicate	Description
topology(O,Z)	Checks if O is a topology on set Z
topology_space(X,O)	True if O is a topology on base set X
🔁 Surjections and Injections
Predicate	Description
surjection(F, S, T)	F maps S onto T (surjective)
injection(F, S, _)	F maps S injectively (distinct elements have distinct images)
🔀 Permutations
Predicate	Description
perm_prod(X,Y,Z)	Z is the composition of X and Y
perm_inv(X,Z)	Z is the inverse of permutation X
perm_div(X,Y,Z)	Z is the result of dividing X by Y
perm_ident(N,X)	X is the identity permutation of size N
perm_inversion(P,N)	N is the number of inversions in P
perm_sign(P,Sign)	Sign is the sign of permutation P
perm_expt(X,N,Z)    Z is the exponentation of X and N 
perm_even(X,Z)      Z is even permutation of X.
perm_odd(X,Z)       Z is odd permutation of X.   
Infix Notation for Permutations
Operator	Meaning
Z isq X * Y	perm_prod(X,Y,Z)
Z isq 1 // X	perm_inv(X,Z)
Z isq X / Y	perm_div(X,Y,Z)
Z isq X ^ N perm_expt(X,N,Z)

groupe
Predicate	Description
groupe_prod(X,Y,Z)	Z is the composition of ID-X and ID-Y
groupe_create(p,N)  assert(p(X,N)) X is permutation
groupe_create(e,N)  assert(p(X,N)) X is even permutation
groupe_create(o,N)  assert(p(X,N)) X is odd permutation


Infix Notation for Groupe
Operator	Meaning
Z isg X * Y	groupe_prod(X,Y,Z)
Z isg (X * Y) * Z
Z isg X * (Y * Z)

📌 Notes

Sets are represented as sorted lists without duplicates.

Maps are represented as lists of value:key pairs (e.g., 1:a).

Permutations are lists of integers representing bijections.

Custom infix operators (isl, ism, isq) are defined for readable symbolic notation.