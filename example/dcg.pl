
s --> np,vp.
np --> det,n.
det -->[a].
n -->[dog].
n -->[postman].
vp --> v,np.
v -->[bites].

digit(D) --> [C],{0'0 =< C,C =< 0'9,D is C - 0'0}.

as --> [].
as --> [a], as.

lis([])     --> [].
lis([L|Ls]) --> [L], lis(Ls).
