

find(P) :-
    generate_graph([a,b,c,d,e,f,g,h],
                   [ew(a,b,1),
                    ew(b,e,2),
                    ew(b,f,4),
                    ew(e,f,1),
                    ew(f,h,6),
                    ew(a,c,7),
                    ew(a,d,2),
                    ew(d,g,5),
                    ew(c,g,3),
                    ew(c,f,2),
                    ew(g,h,2)],G),
    dijkstra(G,a,h,P).
