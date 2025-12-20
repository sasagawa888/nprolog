% Graph library

%graph/2  list of vertex, list of edge
%graph([1, 2, 3, 4], [edge(1, 2), edge(1, 3), edge(1, 4), edge(2, 3), edge(2, 4), edge(3, 4)]).

:- module(graph,[generate_graph/3,vertex/2,edge/3,adjacent/3,connected/1,strongly_connected/1,
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
    member(edge(U,V,_),Es).

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
    findall(edge(U,V),
        ( member(U,Vs),
          member(V,Vs),
          U < V ),
        Es),
    generate_graph(Vs,Es,G).

numlist(N,N,[N]).
numlist(M,N,[M|Ns]) :-
    M1 is M+1,
    numlist(M1,N,Ns).