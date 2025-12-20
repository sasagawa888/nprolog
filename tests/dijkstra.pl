% Daijkstra

:- use_module(graph).

route(G) :-
    generate_graph([a,b,c,d,e,f,g,h],
                   [edge(a,b,1),
                    edge(b,c,2),
                    edge(b,f,4),
                    edge(e,f,1),
                    edge(f,h,6),
                    edge(a,c,7),
                    edge(a,d,2),
                    edge(d,g,5),
                    edge(c,g,3),
                    edge(c,f,2),
                    edge(g,b,2)],G).
