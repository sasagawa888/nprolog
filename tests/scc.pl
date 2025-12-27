% Strong-connected-component

:- use_module(graph).

find(V,C) :-
    generate_graph([1,2,3],[ed(1,2),ed(2,3),ed(3,1),
                            ed(3,4),ed(4,5),ed(5,6),ed(6,4)],G),
    scc(G,V,C).

scc(G,V,C) :-
    arg(2,G,Es),
    scc1(G,V,Es,[],C).

scc1(G,V,[],P,P).
scc1(G,V,Es,P,P) :-
    member(V,P).
scc1(G,V,[ed(V,X)|Es],P,C) :-
    scc1(G,X,Es,[V|P],C).
scc1(G,V,[_|Es],P,C) :-
    scc1(G,V,Es,P,C).

