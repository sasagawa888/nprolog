% test of tcl/tk

recur :- 
    tk_init,
    tk_canvas(c0,[width(600),height(600)]),
    gasket([300,0],[0,600],[600,600],6),
    tk_pack(c0),
    tk_mainloop.

midpoint([A0,A1],[B0,B1],[X0,X1]) :-
    X0 is (A0+B0)/2,
    X1 is (A1+B1)/2.

draw_triang([A0,A1],[B0,B1],[C0,C1]) :-
    tk_create(c0,line([A0,A1,B0,B1,C0,C1,A0,A1]),[fill(green)]).


gasket(A,B,C,0).
gasket(A,B,C,N) :-
    draw_triang(A,B,C),
    midpoint(A,B,A1),
    midpoint(B,C,B1),
    midpoint(C,A,C1),
    draw_triang(A1,B1,C1),
    tk_pack(c0),
    tk_update,
    N1 is N-1,
    gasket(A,A1,B1,N1),
    gasket(A1,B,C1,N1),
    gasket(C1,B1,C,N1).

