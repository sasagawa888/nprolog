% ?- enigma([h,e,l,l,o],[a,a,a],X).
% ?- enigma([s,i,r,h,d],[a,a,a],X).


enigma([],_,[]).
enigma([L|Ls],[R1,R2,R3],[M|Ms]) :-
    connecta(L,R3,L1),
    ic(L1,L2),
    connecta(L2,R2,L3),
    iic(L3,L4),
    connecta(L4,R1,L5),
    iiic(L5,L6),
    plug(L6,L7),
    iiic(L8,L7),
    connectb(L8,R1,L9),
    iic(L10,L9),
    connectb(L10,R2,L11),
    ic(L12,L11),
    connectb(L12,R3,M),
    count([R1,R2,R3],R),
    enigma(Ls,R,Ms).

%adjust char when forward
connecta(X,Y,Z) :-
    char_code(X,Cx),
    char_code(Y,Cy),
    Cz is mod((Cx-97) + (Cy-97),26)+97,
    char_code(Z,Cz).

%adjust char when backward
connectb(X,Y,Z) :-
    char_code(X,Cx),
    char_code(Y,Cy),
    Cz is mod((Cx-97+26) - (Cy-97),26)+97,
    char_code(Z,Cz).

%count up roter
count([X,Y,z],[X,Y1,a]) :-
    Y \== z,
    next(Y,Y1).

count([X,z,z],[X1,a,a]) :-
    next(X,X1).

count([X,Y,Z],[X,Y,Z1]) :-
    Z \== z,
    next(Z,Z1).

next(X,Y) :-
    char_code(X,C),
    C1 is C+1,
    char_code(Y,C1).

%rotor1
%ABCDEFGHIJKLMNOPQRSTUVWXYZ
%DMTWSILRUYQNKFEJCAZBPGXOHV
ic(a,d).
ic(b,m).
ic(c,t).
ic(d,w).
ic(e,s).
ic(f,i).
ic(g,l).
ic(h,r).
ic(i,u).
ic(j,y).
ic(k,q).
ic(l,n).
ic(m,k).
ic(n,f).
ic(o,e).
ic(p,j).
ic(q,c).
ic(r,a).
ic(s,z).
ic(t,b).
ic(u,p).
ic(v,g).
ic(w,x).
ic(x,o).
ic(y,h).
ic(z,v).


%rotor2
%ABCDEFGHIJKLMNOPQRSTUVWXYZ
%HQZGPJTMOBLNCIFDYAWVEUSRKX
iic(a,h).
iic(b,q).
iic(c,z).
iic(d,g).
iic(e,p).
iic(f,j).
iic(g,t).
iic(h,m).
iic(i,o).
iic(j,b).
iic(k,l).
iic(l,n).
iic(m,c).
iic(n,i).
iic(o,f).
iic(p,d).
iic(q,y).
iic(r,a).
iic(s,w).
iic(t,v).
iic(u,e).
iic(v,u).
iic(w,s).
iic(x,r).
iic(y,k).
iic(z,x).

%rotor3
%ABCDEFGHIJKLMNOPQRSTUVWXYZ
%UQNTLSZFMREHDPXKIBVYGJCWOA
iiic(a,u).
iiic(b,q).
iiic(c,n).
iiic(d,t).
iiic(e,l).
iiic(f,s).
iiic(g,z).
iiic(h,f).
iiic(i,m).
iiic(j,r).
iiic(k,e).
iiic(l,h).
iiic(m,d).
iiic(n,p).
iiic(o,x).
iiic(p,k).
iiic(q,i).
iiic(r,b).
iiic(s,v).
iiic(t,y).
iiic(u,g).
iiic(v,j).
iiic(w,c).
iiic(x,w).
iiic(y,o).
iiic(z,a).

%plug
%ABCDEFGHIJKLMNOPQRSTUVWXYZ
%DPLAXGFMRSOCHZKBYIJVWTUEQN
plug(a,d).
plug(b,p).
plug(c,l).
plug(d,a).
plug(e,x).
plug(f,g).
plug(g,f).
plug(h,m).
plug(i,r).
plug(j,s).
plug(k,o).
plug(l,c).
plug(m,h).
plug(n,z).
plug(o,k).
plug(p,b).
plug(q,y).
plug(r,i).
plug(s,j).
plug(t,v).
plug(u,w).
plug(v,t).
plug(w,u).
plug(x,e).
plug(y,q).
plug(z,n).
