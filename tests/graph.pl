% Graph library

%graph/2  list of vertex, list of edge
%graph([1, 2, 3, 4], [edge(1, 2), edge(1, 3), edge(1, 4), edge(2, 3), edge(2, 4), edge(3, 4)]).


%vertex(graph(Vs,_), V).

%edge(graph(_,Es), U, V).

%adjacent(G, U, V).

%connected(G).

%subgraph(G, Vs, SubG).


% control
forall(P, Q) :-
    \+ (P, \+ Q).

%complete(G).  if G is graph true, else fail. 
%generate_kn(N,G).  generate complete N dimension graph.
