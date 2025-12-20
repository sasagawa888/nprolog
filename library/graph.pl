% Graph library

%graph/2  list of vertex, list of edge
%graph([1, 2, 3, 4], [e(1, 2), e(1, 3), e(1, 4), e(2, 3), e(2, 4), e(3, 4)]).

:- module(graph,[graph/2,e/2,ed/2,ew/3,edw/3,generate_graph/3,vertex/2,edge/3,adjacent/3,connected/1,strongly_connected/1,
                 complete/1,generate_kn/2]).

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
    arg2(2,G,[e(_,_)|Es]).
type(G,undirected_weight) :-
    arg2(2,G,[ew(_,_,_)|Es]).
type(G,directed) :-
    arg2(2,G,[ed(_,_)|Es]).
type(G,directed_weight) :-
    arg2(2,G,[edw(_,_,_)|Es]).


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