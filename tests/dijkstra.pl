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


:- dynamic(q/3).

% Q is　candidate set e.g. q(vertex,distance,path)
% R is unselected set e.g. [b,c,d...]
% V is setled vertex  e.g. a


initialize(G,S,R) :-
    abolish(q/3),
    asserta(q(S,0,none)),
    arg(1,G,Vs),
    difference(Vs,S,R).


dijkstra(G,X,Y) :-
    initialize(G,X,R),
    dijkstra1(G,X,Y).

dijkstra1(G,V,V).
dijkstra1(G,V,Y) :-
    selectq(V1,D,P),write(V1),
    unselected(G,R),write(R),nl,
    update(G,R,V1),
    dijkstra1(G,V1,Y).

% shotest vertex in set Q.
selectq(Vmin, Dmin, Pmin) :-
    setof(D-V-P, q(V,D,P), [Dmin-Vmin-Pmin|_]).

% unselected vertex R
unselected(G,R) :-
    arg(1,G,Vs),
    setof(V, q(V,_,_),Q),
    difference(Vs,Q,R).


% calculate distance unselected vertex
update(G,[],V,).
update(G,[R|Rs],V) :-
    arg(2,G,Es),
    member(ew(V,R,D),Es),
    q(V,D1,_),
    D2 is D+D1,
    asserta(q(R,D2,V)),
    update(G,Rs,V).
update(G,[R|Rs],V) :-
    arg(2,G,Es),
    not(member(ew(V,R,D),Es)),
    update(G,Rs,V).
