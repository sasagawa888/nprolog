% Graph library

%graph/2  list of vertex, list of edge
%graph([1, 2, 3, 4], [e(1, 2), e(1, 3), e(1, 4), e(2, 3), e(2, 4), e(3, 4)]).

:- module(graph,[graph/2,e/2,ed/2,ew/3,edw/3,generate_graph/3,vertex/2,edge/3,adjacent/3,connected/1,strongly_connected/1,
                 complete/1,generate_kn/2,reverse_graph/2,dijkstra/4,scc/2,topsort/2]).

generate_graph(Vs,Es,G) :-
    G = graph(Vs,Es).

%vertex(graph(Vs,_), V).
vertex(G,V) :-
    arg(1,G,Vs),
    member(V,Vs).

%edge(graph(_,Es), U, V).
edge(G,U,V) :-
    arg(2,G,Es),
    type(G,undirected),
    member(e(U,V),Es).
edge(G,U,V) :-
    arg(2,G,Es),
    type(G,directed),
    member(ed(U,V),Es).
edge(G,U,V) :-
    arg(2,G,Es),
    type(G,undirected_weight),
    member(ew(U,V,_),Es).
edge(G,U,V) :-
    arg(2,G,Es),
    type(G,directed_weight),
    member(edw(U,V,_),Es).

type(G,undirected) :-
    arg(2,G,[e(_,_)|Es]).
type(G,undirected_weight) :-
    arg(2,G,[ew(_,_,_)|Es]).
type(G,directed) :-
    arg(2,G,[ed(_,_)|Es]).
type(G,directed_weight) :-
    arg(2,G,[edw(_,_,_)|Es]).


%adjacent(G, U, V).
adjacent(G,U,V) :-
    edge(G,U,V).
adjacent(G,U,V) :-
    edge(G,V,U).

%connected(G).
path(G,U,V,[U,V]) :-
    adjacent(G,U,V).

path(G,U,V,[U|P]) :-
    adjacent(G,U,W),
    U \= W,
    path(G,W,V,P).

connected(G) :-
    forall(
        (vertex(G,U), vertex(G,V)),
        path(G,U,V,_)
    ).

strongly_connected(G) :-
    forall(
        (vertex(G,U), vertex(G,V)),
        (path(G,U,V,_),path(G,V,U,_))
    ).

%subgraph(G, Vs, SubG).


% control
forall(P, Q) :-
    \+ (P, \+ Q).

%complete(G).  if G is graph true, else fail. 
complete(G) :-
    forall(
        (vertex(G,U), vertex(G,V), U \= V),
        adjacent(G,U,V)
    ).

%generate_kn(N,G).  generate complete N dimension graph.
generate_kn(N,G) :-
    numlist(1,N,Vs),
    findall(e(U,V),
        ( member(U,Vs),
          member(V,Vs),
          U < V ),
        Es),
    generate_graph(Vs,Es,G).

numlist(N,N,[N]).
numlist(M,N,[M|Ns]) :-
    M1 is M+1,
    numlist(M1,N,Ns).

reverse_graph(G,graph(Vs,Rs)) :-
    arg(1,G,Vs),
    arg(2,G,Es),
    reverse_graph1(Es,Rs).

reverse_graph1([],[]).
reverse_graph1([ed(V,X)|Es],[ed(X,V)|Rs]) :-
    reverse_graph1(Es,Rs).


%------dijkstra shortest-path -----------------

dijkstra(G,Start,Goal,Path) :-
    init(Start,Q),
    get_shortest(Q,Q,[V,_]),
    add_candidate(G,Q,Q1),
    %write(Q1),nl,
    dijkstra1(G,Q1,V,Goal,Q2),
    dijkstra2(Q2,Start,Goal,Path).

dijkstra1(G,Q,Goal,Goal,Q).
dijkstra1(G,Q,V,Goal,Q2) :-
    get_shortest(Q,Q,[V1,_]),
    add_candidate(G,Q,Q1),
    %write(Q1),nl,
    dijkstra1(G,Q1,V1,Goal,Q2).


dijkstra2([[Start,_,_]|_],Start,Goal,[]).
dijkstra2([[Goal,_,Prev]|Qs],Start,Goal,[Goal,Prev|Path]) :-
    dijkstra3(Qs,Prev,[Prev,_,P]),
    dijkstra2(Qs,Start,P,Path).
dijkstra2([Q|Qs],Start,Goal,Path) :-
    dijkstra2(Qs,Start,Goal,Path).

dijkstra3([],Prev,[none,100,_]).
dijkstra3([[Prev,D,Path]|Qs],Prev,[Prev,D,Path]) :-
    dijkstra3(Qs,Prev,[Prev,D1,_]),
    D < D1,!.
dijkstra3([[Prev,D,Path]|Qs],Prev,[Prev,D1,P]) :-
    dijkstra3(Qs,Prev,[Prev,D1,P]),
    D >= D1,!.
dijkstra3([[Prev,D,Path]|Qs],Prev,[Prev,D,Path]).

dijkstra3([_|Qs],Prev,[Prev,D1,P]) :-
    dijkstra3(Qs,Prev,[Prev,D1,P]).


% initialize set Q
% max distance is 100.
init(Start,[[Start,0,none],[none,100,0]]).

% data structure
% selected set Q [[vertex,distance,path]...]
% find candidate vertex from Q set.
new([V,_,P],[]).
new([V,_,P],[[_,_,V]|Qs]) :- !,fail.
new([V,_,P],[_|Qs]) :- new([V,_,P],Qs).

get_shortest([[V,D,_]],_,[V,D]).
get_shortest([Q|Qs],A,[V,D]) :-
    new(Q,A),
    [V,D,_] = Q,
    get_shortest(Qs,A,[V1,D1]),
    D < D1,!.
get_shortest([Q|Qs],A,[V1,D1]) :-
    new(Q,A),
    [V,D,_] = Q,
    get_shortest(Qs,A,[V1,D1]),
    D >= D1,!.
get_shortest([Q|Qs],A,V) :-
    get_shortest(Qs,A,V).

% add candidate to Q
add_candidate(G,Q,Q1) :-
    arg(2,G,Es),
    get_shortest(Q,Q,[V,D]),
    add_candidate1(Q,Es,V,D,Q1).

add_candidate1(Q,[],V,D,Q).
add_candidate1(Q,[ew(V,P,D1)|Es],V,D,[[P,D2,V]|Qs]) :-
    D2 is D+D1,
    add_candidate1(Q,Es,V,D,Qs).
add_candidate1(Q,[_|Es],V,D,Qs) :-
    add_candidate1(Q,Es,V,D,Qs).


% Strong-connected-component

:- dynamic(component/1).

%diterministic member/2
member1(X,[X|_]).

same_set(X,Y) :-
    sort(X,X1),
    sort(Y,Y1),
    X1 = Y1.


subset([],[]).
subset([X|L],[X|S]) :-
subset(L,S).
subset(L, [_|S]) :-
subset(L,S).

scc(G,C) :-
    abolish(component/1),
    assert(component([])),
    arg(1,G,Vs),
    arg(2,G,Es),
    member1(V,Vs),
    scc1(V,Vs,Es,[]),
    fail.
scc(_,C) :-
    compile(C).

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
    regist1(X,P,C),
    sort([V|C],C1),
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


%------------ topological sort------------



topsort(G,X) :-
    abolish(groupe/1),
    assert(groupe([])),
    arg(1,G,Vs),
    arg(2,G,Es),
    member(V,Vs),
    topsort1(V,Vs,Es,[]),
    fail.
topsort(_,X) :-
    assemble(X).

topsort1(V,Vs,Es,P) :-
    member(ed(V,X),Es),
    topsort1(X,Vs,Es,[V|P]).
topsort1(V,Vs,Es,P) :-
    not(member(ed(V,X),Es)),
    assert(groupe([V|P])).

assemble(L2) :-
    bagof(X,(groupe(X),X \=[]),L),
    assemble1(L,L1),
    reverse(L1,L2).

assemble1([L],L).
assemble1([L|Ls],L) :-
    assemble1(Ls,L1),
    length(L,X),
    length(L1,Y),
    X >= Y.
assemble1([L|Ls],L1) :-
    assemble1(Ls,L1),
    length(L,X),
    length(L1,Y),
    X < Y.


reverse([],[]).
reverse([X|Xs],Y) :-
    reverse(Xs,Y1),
    append(Y1,[X],Y).