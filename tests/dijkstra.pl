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
                    ew(b,e,2),
                    ew(b,f,4),
                    ew(e,f,1),
                    ew(f,h,6),
                    ew(a,c,7),
                    ew(a,d,2),
                    ew(d,g,5),
                    ew(c,g,3),
                    ew(c,f,2),
                    ew(g,h,2)],G).


test1([[b,1,a],[c,7,a],[d,5,a],[a,0,none],[none,100,a]]).
test2([[e,3,b],[f,5,b],[b,1,a],[c,7,a],[d,2,a],[a,0,none],[none,100,a]]).


% selected set Q [[vertex,distance,path]...]

% find candidate vertex
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

add_candidate(G,Q,[[P,D2,V]|Q]) :-
    arg(2,G,Es),
    get_shortest(Q,Q,[V,D]),
    member(ew(V,P,D1),Es),
    D2 is D+D1.
add_candidate(G,Q,Q) :-
    arg(2,G,Es),
    get_shortest(Q,Q,[V,D]),
    not(member(ew(V,D,P),Es)).
    