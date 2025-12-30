% Strong-connected-component

:- use_module(graph).
:- use_module(list).

:- dynamic(component/1).

find(C) :-
    abolish(component/1),
    assert(compnent([])),
    generate_graph([1,2,3],[ed(1,2),ed(2,3),ed(3,1),ed(3,4),ed(4,1),
                            ed(4,5),ed(5,6),ed(6,7),ed(7,5)],G),
    scc(G,C).

scc(G,C) :-
    arg(1,G,Vs),
    arg(2,G,Es),
    member(V,Vs),
    scc1(V,Vs,Es,[]),
    component(C).

scc1(S,Vs,Es,P) :-
    same_set(Vs,P).

scc1(V,Vs,Es,P) :-
    member(ed(V,X),Es),
    member(X,P),
    regist(V,X,P).

scc1(V,Vs,Es,P) :-
    member(ed(V,X),Es),
    not(member(X,P)),
    scc1(X,Vs,Es,[V|P]).

regist(V,X,P) :-
    regist1(V,X,P,C),
    component(C),
    retract(component(C)),
    assert(component([V|C])).

regist(V,X,P) :-
    regist1(X,P,C),
    not(component(C)),
    assert(component([V|C])).

regist1(X,[X|_],[]).
regist1(X,[P|Ps],[P|Ys]) :-
    regist1(X,Ps,Ys).

compile(C) :-
    setof(X,component(X),C).