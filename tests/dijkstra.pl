% Daijkstra

:- use_module(graph).
:- use_module(math).

shortest :-
    route(G),
    dijkstra(G,a,h),
    listing(q).


route(G) :-
    generate_graph([a,b,c,d,e,f,g,h],
                   [ew(a,b,1),
                    ew(b,c,2),
                    ew(b,f,4),
                    ew(e,f,1),
                    ew(f,h,6),
                    ew(a,c,7),
                    ew(a,d,2),
                    ew(d,g,5),
                    ew(c,g,3),
                    ew(c,f,2),
                    ew(g,b,2)],G).
