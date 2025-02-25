% testing compile code for diterministic predicate

:- op(700,xfx,isl).

Y isl [] + Y :- !.
Z isl [A|X] + Y :- member(A,Y),!,Z isl X + Y.
[A|Z] isl [A|X] + Y :- Z isl X + Y.

