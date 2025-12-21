% Daijkstra

:- use_module(graph).
:- use_module(list).

sortest(Vs,Ds) :-
    route(G),
    dijkstra(G,a,h,A).


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


:- dynamic(q/3).

% Q is　candidate set e.g. q(vertex,distance,path)
% R is unselected set e.g. [b,c,d...]
% V is setled vertex  e.g. a


initialize(G,S,R) :-
    asserta(q(S,0,none)),
    arg(G,1,Vs),
    del(Vs,S,R).


dijkstra(G,X,Y,A) :-
    initialize(G,X,R),
    dijkstra1(G,R,X,Y).

dijkstra1(G,R,V,V).
dijkstra1(G,R,V,Y) :-
    update(G,R,V,Y,R1),
    shotestq(V1)
    dijkstra1(G,R1,V1).

update(G,R,V,Y) :-
    update1(G,Q,R,V,Q1,R1).


shotestq(Vmin, Dmin, Pmin) :-
    setof(D-V-P, q(V,D,P), [Dmin-Vmin-Pmin|_]).

% calculate distance unselected vertex
update1(G,[],V,Q,R1).
update1(G,[R|Rs],V) :-
    arg(2,G,Es),
    member(e(V,R,D),Es),
    member([D1,V,_],Q),
    D2 is D+D1,
    update1(G,[[D2,R,V]|Q],Rs,V).
update1(G,Q,[R|Rs],V) :-
    arg(2,G,Es),
    not(member(e(V,R,D),Es)),
    update1(G,Q,Rs,V).
