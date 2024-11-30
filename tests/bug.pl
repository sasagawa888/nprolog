

%p179
arg_list(K,Y,M) :- PY =.. [prd|Y],arg(K,PY,M).

:- op(00,xfx,isq).

[J] isq X * [I] :-
arg_list(I,X,J),!.
[J|LJ] isq X * [I|L1] :-
arg_list(I,X,J),!,LJ isq X * LI.