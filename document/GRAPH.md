# Graph llbrary
Simple Graph library

# usage

use_module(graph).


# Specifications / API
1. generate_graph(Vs, Es, G)

Description:
Generates a graph G with vertices Vs and edges Es.

Parameters:

Vs : List of vertices, e.g., [a,b,c]

Es : List of edges, e.g., [e(a,b), e(b,c)]

G : Resulting graph term, e.g., graph([a,b,c],[e(a,b),e(b,c)])

Example:

?- generate_graph([a,b,c],[e(a,b),e(b,c)], G).
G = graph([a,b,c],[e(a,b), e(b,c)]).

- Es : List of undirected edges with weight, e.g., [ew(a,b,3), ew(b,c,4)]
ew(_,_,weight)
- Es : List of irected edges with weight, e.g., [edw(a,b,3), edw(b,c,4)]
edw(_,_,weight)
Es : List of directed edges, e.g., [ed(a,b), ed(b,c)]
ed(_,_)


2. vertex(G, V)

Description:
Checks whether V is a vertex in graph G.

Parameters:

G : Graph term

V : Vertex

Example:

?- generate_graph([a,b,c],[edge(a,b),edge(b,c)], G),
   vertex(G, b).
true.

3. edge(G, U, V)

Description:
Checks whether there is an edge from U to V in graph G.

Parameters:

G : Graph term, graph(_, Es)

U : Start vertex

V : End vertex

Example:

?- generate_graph([a,b,c],[edge(a,b),edge(b,c)], G),
   edge(G, a, b).
true.

4. adjacent(G, U, V)

Description:
Checks if vertices U and V are adjacent (connected directly by an edge) in graph G.

Example:

?- generate_graph([a,b,c],[edge(a,b),edge(b,c)], G),
   adjacent(G, a, b).
true.

?- adjacent(G, a, c).
false.

5. connected(G)

Description:
Checks whether the graph G is connected (there is a path between any two vertices).

Example:

?- generate_graph([a,b,c],[edge(a,b),edge(b,c)], G),
   connected(G).
true.

6. strongly_connected(G)

Description:
Checks whether G is strongly connected (for directed graphs, a path exists from every vertex to every other vertex).

Example:

?- generate_graph([a,b,c],[edge(a,b),edge(b,c),edge(c,a)], G),
   strongly_connected(G).
true.

7. complete(G)

Description:
Checks whether G is a complete graph (every vertex is connected to every other vertex).

Example:

?- generate_graph([a,b,c],[edge(a,b),edge(a,c),edge(b,c),edge(b,a),edge(c,a),edge(c,b)], G),
   complete(G).
true.

8. generate_kn(N, G)

Description:
Generates a complete graph G with N vertices.

Example:

?- generate_kn(3, G).
G = graph([1,2,3],[edge(1,2), edge(1,3), edge(2,1), edge(2,3), edge(3,1), edge(3,2)]).


💡 Note:

graph(Vs, Es) is the standard representation used in this library.

edge(U,V) denotes a directed edge from U to V.

For undirected graphs, treat edge(U,V) and edge(V,U) as equivalent.