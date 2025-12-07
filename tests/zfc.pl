:- use_module(math).

%Extensionality Axiom

%eqset([1,2,3],[1,2,3]).

%Pairing Axiom
pairset(A,B,P) :-
    sort([A,B],P).