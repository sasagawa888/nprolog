verify(X) :- 
	ifthenelse(
		call(X), 
		true, 
		(write('wrong '), write(X), nl)
	).

alltest :-
    test(Test),write(Test),nl,fail.
alltest.


test(atmark) :-
    verify(3 @> 2.1),
    verify([1,2,3] @>= [1,2,3]),
    verify([2,2,3] @> [1,2,3]),
    verify(prolog @>pro),
    verify(pro @< prolog).

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
    verify(atomic(1.0)),
    verify(atomic(人間)).

test(number) :-
    verify(number(1)),
    verify(number(1.0)),
    verify(number(1.0e1)),
    verify(number(0xffff)).

test(integer) :-
    verify(integer(0)),
    verify(integer(1)),
    verify(integer(10000000000)),
    verify(integer(-1)),
    verify(integer(-10000000001)),
    verify(integer(100000000000000000000000000000000000000000001)),
    verify(integer(0xface)),
    verify(integer(0o3476)),
    verify(integer(0b1010101)).

test(float) :-
    verify(float(1.0)),
    verify(float(0.000001)),
    verify(float(1.0e10)),
    verify(not(float(1))).
    
test(nonvar) :-
    X = a,
    verify(nonvar(X)),
    verify(not(nonvar(Y))).


test(var) :-
    verify(var(X)),
    verify(var(_)),
    verify(var(_abc)),
    Y = a,
    verify(not(var(Y))),
    _def = b,
    verify(not(var_def)).

test(radix) :-
    verify(0xff == 255), 
    verify(0o77 == 63),
    verify(0b1111 == 15).

test(sharp) :-
    verify(#x == 120),
    verify(#0 == 48),
    verify(#夢 == 22818).

test(arithmetic) :-
    verify(2 is 1+1),
    verify(-1 is 3-4),
    verify(6 is 2*3),
    verify(8 is 16/2),
    verify(2.3 is 1.1+1.2),
    verify(1.2 is 0.7+0.5),
    verify(2.3 is 3.4-1.1),
    verify(0.36 is 0.6*0.6),
    verify(8 is 2^3),
    verify(16 is 2^4),
    verify(-1.0 is cos(acos(-1))),
    verify(4 is 1 << 2),
    verify(8 is 1 << 3),
    verify(1 is 8 >> 3),
    verify(1 is 4 >> 2),
    verify(3 is abs(-3)),
    verify(3.3 is abs(-3.3)),
    verify(2.718281828459045 is exp(1)),
    verify(0 is log(1)),
    verify(1.0 is ln(exp(1))),
    verify(3.141592653589793 is pi),
    verify(2==2),
    verify(1.23==1.23),
    verify(0.00000000000001==0.00000000000001),
    verify(9999999999999999999999==9999999999999999999999),
    verify(-9999999999999999999999 == -9999999999999999999999),
    verify(2=:=2),
    verify(2\=3),
    verify(2=\=3),
    verify(2\=0.3),
    verify(2>1),
    verify(1+2>2),
    verify(1+2>1+0),
    verify(1+2>=2+1),
    verify(not(1>1)),
    verify(3.2>3),
    verify(2>=1),
    verify(1>=1),
    verify(1<2),
    verify(1<1+1),
    verify(not(1<1)),
    verify(1<2.0),
    verify(1.0<999999999999999999999999),
    verify(1=<1),
    verify(1=<1*1).

test(sort) :-
    sort([2,3,1],X),
    verify(X == [1,2,3]),
    keysort([25-a, e-100, n-5, 12-o, 50-t], Y),
    verify(Y == [12-o,25-a,50-t,e-100,n-5]).

test(string) :-
    verify(string($asdf$)),
    verify(string($123$)),
    verify(string($hello world!$)),
    verify($asdf$ = $asdf$),
    verify($asdf$ \= $qwer$).

test(true_fail_not) :-
    verify(true),
    verify(not(fail)),
    verify((fail;true)),
    verify(not(not(true))),
    verify(not(1==2)),
    verify(not(X == 2)),
    verify(not(X \= 2)).

test(system) :-
    verify(system(write/1)),
    verify(system(write/2)),
    verify(system(true/0)),
    verify(system(halt/0)),
    verify(system(is/2)),
    verify(system('=='/2)).

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

    verify(not(a(a,B1) = a(B1,b))),

    verify(X=X),
    verify((X=Y,Y=X)).

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
    verify(Y == [cos,2]),
    verify(a =.. [a]),
    verify(f(a, b, c) =.. [f, a, b, c]),
    verify(g(h(a), i(b, c)) =.. [g, h(a), i(b, c)]).

test(functor) :-
    verify(functor(book(pooh,miline,aa),book,3)),
    verify(functor(foo,foo,0)),
    verify(not(functor(foo(1,2),foo,3))),
    verify(functor([1,2,3],'.',2)).


test(arg) :-
    arg(1,book(poetry,milne,poetry),poetry),
    arg0(0,book(poetry,milne,poetry),poetry).

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
    float_text(1.23,X,_),
    verify(X = $1.23$),
    
    float_text(Y,$1.23$,_),
    verify(Y == 1.23).

test(length) :-
    verify(length([1,2,3],3)),
    verify(length([],0)),
    verify(length([],X)).

test(member) :-
    verify(member(b,[a,b,c])),
    verify(member(1,[3,2,1])),
    verify(member(a,[a|b])),
    verify(not(member(a,[3,2,1]))),
    verify(not(member(a,[]))).

test(append) :-
    verify(append([],[a,b,c],[a,b,c])),
    verify(append([a,b,c],[],[a,b,c])),
    verify(append([a,b,c],[d,e,f],[a,b,c,d,e,f])).

test(reverse) :-
    reverse([a,b,c],X),
    verify(X=[c,b,a]),
    verify(reverse([1,2,3],[3,2,1])),
    verify(reverse([],[])).

test(name) :-
    name(asdf,X),
    name(Y,X),
    verify(Y=asdf),

    name(笹川賢一,A),
    name(B,A),
    verify(B=笹川賢一).

test(list_text) :-
    list_text([97,115,100],X),
    verify(X = $asd$),
    list_text([97,115,115,101,114,116],Y),
    verify(Y = assert),
    list_text("abc",Z),
    verify(Z = abc).

test(int_text) :-
    int_text(6,X),
    verify(X = $6$),
    int_text(Y,$7$),
    verify(Y = 7),
    verify(int_text(5,$5$)).

test(string_term) :-
    string_term($sin(3)$,X),
    verify(X = sin(3)),
    string_term($1+2+3$,Y),
    verify(Y = 1+2+3).

test(atom_string) :-
    atom_string('orange',X),
    verify(X = $orange$),
    atom_string(Y,$apple$),
    verify(Y = apple).

test(dot) :-
    L = .(a,b),
    verify(L = [a|b]),
    M = .(a,[b,c]),
    verify(M = [a,b,c]).

test(between) :-
    verify(between(1,10,3)),
    verify(not(between(1,10,11))),
    between(1,1,B),
    verify(B = 1).

test(list) :-
    verify(list([])).

test(timer) :-
    C = 0,
    ctr_set(C, 5),
    ctr_is(C, X1),
    ctr_inc(C, X2),
    ctr_is(C, X3),
    ctr_dec(C, X4),
    ctr_is(C, X5),
    X5 = 5.

% set 
parent(john, mary).
parent(john, bob).
parent(susan, mary).
parent(susan, bob).

test(bagof) :- 
       bagof(Child, parent(john, Child), Children), Children = [mary, bob].

test(setof) :- 
       setof(Child, parent(_, Child), UniqueChildren), UniqueChildren = [bob, mary].

test(findall) :-
      findall(Child, parent(_, Child), AllChildren), AllChildren = [mary, bob, mary, bob].

max(X, Y, X) :- X >= Y, !.
max(_, Y, Y).

test(max) :-
    max(3, 4, 4),
    max(5, 2, 5),
    max(7, 7, 7). 

/* sort */
quick_sort([], []).
quick_sort([H|T], Sorted) :-
    partition(H, T, Left, Right),
    quick_sort(Left, SortedLeft),
    quick_sort(Right, SortedRight),
    append(SortedLeft, [H|SortedRight], Sorted).

partition(_, [], [], []).
partition(Pivot, [H|T], [H|Left], Right) :-
    H =< Pivot,
    partition(Pivot, T, Left, Right).
partition(Pivot, [H|T], Left, [H|Right]) :-
    H > Pivot,
    partition(Pivot, T, Left, Right).

test(sort) :- 
    quick_sort([3,1,4,1,5,9,2,6,5], Sorted), Sorted = [1,1,2,3,4,5,5,6,9].


test(conditional) :-
    (X = 1 -> Y = 2 ; Y = 3),
    Y == 2.


test(backtracking) :-
    (X = 1 ; X = 2),
    X == 1.


test(unification) :-
    X = 1,
    X = 1,
    X == 1.

test(unification_failure) :-
    \+ (X = 1, X = 2).

test(cut) :-
    (true -> X = 1 ; X = 2),
    X == 1.

test(cut_failure) :-
    (false -> X = 1 ; X = 2),
    X == 2.

fib(0, 0).
fib(1, 1).
fib(N, F) :-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fib(N1, F1),
    fib(N2, F2),
    F is F1 + F2.


test(fib) :-
    fib(5, F),
    F == 5.

test(list) :-
    [H|T] = [1, 2, 3],
    H == 1,
    T == [2, 3].

test(date) :-
    date(X),date_day(X,Y).


:- alltest,write('All tests are done'),nl.
