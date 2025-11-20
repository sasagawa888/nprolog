% Draw a C-curve (Koch C-curve)
% draw_c_curve(X0, Y0, X1, Y1, Depth, Color)

draw_c_curve(X0, Y0, X1, Y1, 0, Color) :-
    % Base case: draw straight line
    gr_line(X0, Y0, X1, Y1, Color).

draw_c_curve(X0, Y0, X1, Y1, Depth, Color) :-
    Depth > 0,
    DX is X1 - X0,
    DY is Y1 - Y0,

    % Compute midpoint rotated by +90 degrees
    MX is X0 + DX//2 - DY//2,
    MY is Y0 + DY//2 + DX//2,

    D1 is Depth - 1,

    % Recursive draw
    draw_c_curve(X0, Y0, MX, MY, D1, Color),
    draw_c_curve(MX, MY, X1, Y1, D1, Color).

draw :-
    gr_open,
    gr_cls(black),
    draw_c_curve(900, 300, 1300, 300, 12, blue),
    gr_close.


japan :-
    gr_open,
    gr_cls(black),
    draw_flag(900,300,400),
    gr_close.

draw_flag(X0,Y0,W) :-
    X1 is X0 + W,
    Y1 is Y0 + W*2//3,
    gr_rect(X0,Y0,X1,Y1,white,fill),
    H is Y1 - Y0,
    Cx is W // 2 + X0,
    Cy is H // 2 + Y0,
    R is H * 3 //10,
    gr_circle(Cx,Cy,R,red,fill).
