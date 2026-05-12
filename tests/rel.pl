% sphere_point(Theta, Phi, X, Y, Z)
% 単位球上の点
sphere_point(Theta, Phi, X, Y, Z) :-
    X is sin(Theta) * cos(Phi),
    Y is sin(Theta) * sin(Phi),
    Z is cos(Theta).

% tangent_plane(X0,Y0,Z0, A,B,C,D)
% 点 (X0,Y0,Z0) における接平面
% A*x + B*y + C*z = D
%
% 単位球なら法線ベクトルはその点自身
tangent_plane(X0, Y0, Z0, X0, Y0, Z0, D) :-
    D is X0*X0 + Y0*Y0 + Z0*Z0.

% 使用例：
% ?- sphere_point(0.7853981633974483, 0.7853981633974483, X,Y,Z),
%    tangent_plane(X,Y,Z,A,B,C,D).

% finite tangent vectors by small difference

epsilon(1.0e-6).

sub3(X1,Y1,Z1, X0,Y0,Z0, DX,DY,DZ) :-
    DX is X1 - X0,
    DY is Y1 - Y0,
    DZ is Z1 - Z0.

tangent_vectors_numeric(Theta, Phi, Vt, Vp) :-
    epsilon(Eps),

    sphere_point(Theta, Phi, X0,Y0,Z0),

    Theta1 is Theta + Eps,
    sphere_point(Theta1, Phi, X1,Y1,Z1),
    sub3(X1,Y1,Z1, X0,Y0,Z0, DXt,DYt,DZt),
    Vt = v(DXt,DYt,DZt),

    Phi1 is Phi + Eps,
    sphere_point(Theta, Phi1, X2,Y2,Z2),
    sub3(X2,Y2,Z2, X0,Y0,Z0, DXp,DYp,DZp),
    Vp = v(DXp,DYp,DZp).