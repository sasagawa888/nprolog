% Strong-connected-component

:- use_module(graph).
:- use_module(list).
:- use_module(math).

:- dynamic(component/1).

find(C) :-
    abolish(component/1),
    assert(component([])),
    generate_graph([1,2,3],[ed(1,2),ed(2,3),ed(3,1),ed(3,4),ed(4,1),
                            ed(4,5),ed(5,6),ed(6,7),ed(7,5)],G),
    scc(G,C).

scc(G,C) :-
    arg(1,G,Vs),
    arg(2,G,Es),
    member(V,Vs),
    scc1(V,Vs,Es,[]),
    fail.
scc(_,C) :-
    compile(C).

scc1(S,Vs,Es,P) :-
    same_set(Vs,P),!.

scc1(V,Vs,Es,P) :-
    member(ed(V,X),Es),
    member(X,P),
    regist(V,X,P).

scc1(V,Vs,Es,P) :-
    member(ed(V,X),Es),
    not(member(X,P)),
    scc1(X,Vs,Es,[V|P]).


regist(V,X,P) :-
    regist1(X,P,C),
    sort([V|C],C1),
    not(component(C1)),
    assert(component(C1)).


regist1(X,[X|_],[X]).
regist1(X,[P|Ps],[P|Ys]) :-
    regist1(X,Ps,Ys).


compile(C) :-
    setof(X,(component(X),X \= []),Y),
    compile1(Y,C).

compile1([C],[C]).
compile1([C|Cs],X) :-
    compile2(C,Cs), % include superset
    compile1(Cs,X).
compile1([C|Cs],[C|X]) :-
    compile1(Cs,X).
        
compile2(X,[]) :- fail.
compile2(X,[Y|Ys]) :-
    subset(X,Y).
compile2(X,[Y|Ys]) :-
    not(subset(X,Y)),
    compile2(X,Ys).