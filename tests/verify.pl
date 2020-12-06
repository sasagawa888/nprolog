verify(X) :- 
	ifthenelse(
		call(X), 
		true, 
		(write('wrong '), write(X), nl)
	).

alltest :-
    test(Test),
    fail.
alltest.

test(atmark) :-
    verify(3 @> 2.1),
    verify([1,2,3] @>= [1,2,3]),
    verify([2,2,3] @> [1,2,3]).

test(atom) :-
    verify(atom(a)),
    verify(not(atom(1))),
    verify(not(atom(1.1))),
    verify(atom('a*b')),
    verify(atom('123abc')),
    verify(atom(=$)),
    verify(atom(true)),
    verify(atom(動物)).

test(atomic) :-
    verify(atomic(1)),
    verify(atomic(abc)),
    verify(atomic(1.0)).

test(number) :-
    verify(number(1)),
    verify(number(1.0)),
    verify(number(1.0e1)).

test(integer) :-
    verify(integer(1)),
    verify(integer(10000000000)),
    verify(integer(-1)),
    verify(integer(-10000000001)),
    verify(integer(100000000000000000000000000000000000000000001)).

test(float) :-
    verify(float(1.0)),
    verify(float(0.000001)),
    verify(float(1.0e10)),
    verify(not(float(1))).

test(arithmetic) :-
    verify(2 is 1+1),
    verify(1.2 is 0.7+0.5),
    verify(8 is 2^3),
    verify(16 is 2**4),
    verify(-1.0 is cos(acos(-1))),
    verify(2==2),
    verify(1.23==1.23),
    verify(0.00000000000001==0.00000000000001),
    verify(2=:=2),
    verify(2\=3),
    verify(2=\=3),
    verify(2\=0.3),
    verify(2>1),
    verify(3.2>3),
    verify(2>=1),
    verify(1<2),
    verify(1<2.0),
    verify(1.0<999999999999999999999999),
    verify(1=<1).

test(string) :-
    verify(string($asdf$)),
    verify(string($123$)),
    verify(string($hello world!$)).

test(true_fail) :-
    verify(true),
    verify(not(fail)),
    verify((fail;true)).

test(unify) :-
    verify(c(Z) = c(c(z))),
    verify(Z == c(z)),

    verify(a(b,C) = a(B,c)),
    verify(C == c),
    verify(B == b),

    verify([E1,E2,E3] = [a,b,c]),
    verify(E1 == a),
    verify(E2 == b),
    verify(E3 == c),

    verify(not(a(a,b) = b(a,b))),

    verify(a(a,A1) = a(A1,a)),
    verify(A1 == a),

    verify(not(a(a,B1) = a(B1,b))).

test(list_difference) :-
    L = [a|T]-T, T = [], L = L1-[], 
    verify(L1 == [a]).

test(list_difference) :-
    L = T-T, L1 = [a,b|T], T = [c,d],
    verify(L1 == [a,b,c,d]).

test(univ) :-
    X =.. [sin,3],
    cos(2) =.. Y,
    verify(X == sin(3)),
    verify(Y == [cos,2]).

test(concat) :-
    concat(a123,asdf,X),
    X = a123asdf,

    concat($asdf$,$123$,Y),
    Y = $asdf123$.

test(current_predicate) :-
    verify(current_predicate(verify/1)).

test(dec) :-
    dec(10,X),
    X == 9.

test(inc) :-
    inc(9,X),
    X == 10.

test(float_text) :-
    float_text(1.23,X,$%1.2f$),
    verify(X = $1.23$),
    
    float_text(Y,$1.23$,$%1.2f$),
    verify(Y == 1.23).

test(length) :-
    verify(length([1,2,3],3)),
    verify(length([],0)).

test(member) :-
    verify(member(b,[a,b,c])),
    verify(member(1,[3,2,1])),
    verify(not(member(a,[3,2,1]))).

test(append) :-
    verify(append([a,b,c],[d,e,f],[a,b,c,d,e,f])).

test(reverse) :-
    reverse([a,b,c],X),
    verify(X=[c,b,a]).

test(list_text) :-
    list_text([97,115,100],X),
    verify(X = asd),
    list_text([97,115,115,101,114,116],Y),
    verify(Y=assert).

test(string_term) :-
    string_term($sin(3)$,X),
    verify(X = sin(3)).

:- alltest,write('All tests are done\n').