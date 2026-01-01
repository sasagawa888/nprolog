% Strong-connected-component

:- use_module(graph).

find(C) :-
    generate_graph([1,2,3,4,5,6,7],[ed(1,2),ed(2,3),ed(3,1),ed(3,4),ed(4,1),
                            ed(4,5),ed(5,6),ed(6,7),ed(7,5)],G),
    scc(G,C).

tops(X) :-
    generate_graph([1,2,3,4],[ed(1,2),ed(1,3),ed(1,4),ed(3,2),ed(4,2),ed(4,3)],G),
    topsort(G,X).


topsort(G,X) :-
    abolish(groupe/1),
    assert(groupe([])),
    arg(1,G,Vs),
    arg(2,G,Es),
    member(V,Vs),
    topsort1(V,Vs,Es,[]),
    fail.

topsort1(V,Vs,Es,P) :-
    member(ed(V,X),Es),
    topsort1(X,Vs,Es,[V|P]).
topsort1(V,Vs,Es,P) :-
    not(member(ed(V,X),Es)),
    assert(groupe([V|P])).

assemble(X) :-
    groupe(Y)

.