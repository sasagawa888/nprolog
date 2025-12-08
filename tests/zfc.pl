% A set is represented as a list. 
% Its elements are sorted in ascending order, and no duplicates are allowed.


%Axiom of Extensionality
eqset(A,B) :-
    A=B.

%Axiom of Empty Set
emptyset([]).

%Axiom of Pairing
pairset(A,B,P) :-
    sort([A,B],P).

%Axiom of Union
unionset(A,U) :-
    union1(A,Flat),
    sort(Flat,U).

union1([], []).
union1([Set|Sets], Result) :-
    append(Set, Rest, Result),
    union1(Sets, Rest).

%Axiom of Power Set
powerset([], [[]]).
powerset([X|Xs], P) :-
    powerset(Xs, Ps),
    add_elem(X, Ps, Ps1),
    append(Ps, Ps1, P).

add_elem(_, [], []).
add_elem(X, [Set|Sets], [[X|Set]|Sets1]) :-
    add_elem(X, Sets, Sets1).

%Axiom of Infinity
%list of prolog is finify

%Axiom Schema of Separation
separation([],F,[]).
separation([A|As],F,[A|Bs]) :-
    P =.. [F,A],
    call(P),
    separation(As,F,Bs).
separation([A|As],F,Bs) :-
    P =.. [F,A],
    not(call(P)),
    separation(As,F,Bs).

%ex　separation([-1,0,1,2],positive,X).
positive(X) :- 
    X > 0 .

%Axiom of Replacement
% replacement([1,2,3],add10,X).
replacement([],F,[]).
replacement([A|As],F,[B|Bs]) :-
    P =.. [F,A,B],
    call(P),
    replacement(As,F,Bs).

%ex
add10(X,Y) :-
    Y is X + 10.

%Axiom of Regularity
%Prolog lists always satisfy regularity.

%Axiom of Choice
choice([A|As],0,A).
choice([A|As],N,B) :-
    N1 is N-1,
    choice(As,N1,B).