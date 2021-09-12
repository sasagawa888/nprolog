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