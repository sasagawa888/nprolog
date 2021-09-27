happy(fido).
happy(harry).
happy(X) :- rich(X).
rich(harry).
/*
?- setof(Y, happy(Y), Set).
Y = _G180
Set = [fido, harry] ;
false.

?- bagof(Y, happy(Y), Bag).
Y = _G180
Bag = [fido, harry, harry] ;
false.

?- findall(Y, happy(Y), Bag).
Y = _G180
Bag = [fido, harry, harry] ;
false.

*/

foo(a, b, c).
foo(a, b, d).
foo(b, c, e).
foo(b, c, f).
foo(c, c, g).

/*
?- bagof(C, foo(A, B, C), Cs).
A = a, B = b, C = G308, Cs = [c, d] ;
A = b, B = c, C = G308, Cs = [e, f] ;length()
A = c, B = c, C = G308, Cs = [g].

?- bagof(C, A^foo(A, B, C), Cs).
A = G324, B = b, C = G326, Cs = [c, d] ;
A = G324, B = c, C = G326, Cs = [e, f, g].
*/