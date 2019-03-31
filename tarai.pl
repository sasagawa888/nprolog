% test code
tarai_cut(X,Y,Z,Y) :- X=<Y,!.
tarai_cut(X,Y,Z,R) :-
	X1 is X-1,
	tarai_cut(X1,Y,Z,Rx),
	Y1 is Y-1,
	tarai_cut(Y1,Z,X,Ry),
	Z1 is Z-1,
	tarai_cut(Z1,X,Y,Rz),
	tarai_cut(Rx,Ry,Rz,R).
