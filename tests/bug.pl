%p100
memberd(X,L) :- member(X,L),!.


%p143
:- op(700,xfx,isl).
Y isl [] + Y :-!.
Z isl [A|X] + Y :-
memberd(A,Y),!,Z isl X + Y.
[A|Z] isl [A|X] + Y :- Z isl X + Y.

%p144
[] isl [] * Y :-!.
[A|Z] isl [A|Z] * Y :-
memberd(A, X),!,Z isl X * Y.
Z isl [A|X] * Y :- Z isl X * Y.

%p147
[] isl [] - A :- !.
Z isl [A|LA] - X :- memberd(A,X),!,Z isl LA -X.
[A|Z] isl [A|LA] - X :- Z isl LA - X.

%p147
[] isl [] / A.
X isl [A|X] / A :- !.
[C|X] isl [C|CL] / A :- X isl LC / A.

%p148
Y isl subset([A|X]) :-
        memberd(A,Y),
        Y0 isl Y / A,
        Y0 isl subset(X).
Y isl subset([A|X]) :-
        Y isl subset(X).
[] isl subset([]).

%p153
power0(Power1,Set) :-
    bagof(X,(X isl subset(Set)),Power0),
    sort(Power0,Power),
    Power1 isl Power - [[],Set].

