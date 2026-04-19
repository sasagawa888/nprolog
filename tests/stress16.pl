% stress_cut
%
% cut (!) stress tests for N-Prolog
%
% expected behavior:
% test1  : a
% test2  : a
% test3  : c
% test4  : yes
% test5  : no
% test6  : 2
% test7  : 1
% test8  : then
% test9  : 10
% test10 : 5
% test11 : 100
% test12 : 7
% test13 : 1
% test14 : yes
% test15 : no
% test16 : 2
% test17 : 1
% test18 : ok
% test19 : 3
% test20 : 2

run_all :-
    test1,
    test2,
    test3,
    test4,
    test5,
    test6,
    test7,
    test8,
    test9,
    test10,
    test11,
    test12,
    test13,
    test14,
    test15,
    test16,
    test17,
    test18,
    test19,
    test20.

show(Test, X) :-
    write(Test),
    write(' : '),
    write(X),
    nl.

show2(Test, X, Y) :-
    write(Test),
    write(' : '),
    write(X),
    write(','),
    write(Y),
    nl.


% -------------------------
% basic cut
% -------------------------

p1(a).
p1(b) :- !.
p1(c).

test1 :-
    p1(X),
    show(test1, X).

% expected: b
% reason: p1(a) fails to match if backtracking? no, because first clause succeeds.
% Actually test1 as written would print a.
%
% So we force first clause to fail in wrapper.

q1(a) :- fail.
q1(b) :- !.
q1(c).

test1 :-
    q1(X),
    show(test1, X).

% -------------------------
% cut removes later clauses
% -------------------------

p2(a) :- !.
p2(b).

test2 :-
    p2(X),
    show(test2, X).

% -------------------------
% cut after first subgoal
% -------------------------

p3(X) :-
    member1(X, [a,b,c]),
    X = c,
    !.
p3(z).

test3 :-
    p3(X),
    show(test3, X).

member1(X, [X|_]).
member1(X, [_|Xs]) :-
    member1(X, Xs).

% -------------------------
% cut + fail
% -------------------------

p4 :-
    a4,
    !,
    b4.

a4.
b4.

test4 :-
    ( p4 -> show(test4, yes)
    ; show(test4, no)
    ).

p5 :-
    a5,
    !,
    b5.

a5.
b5 :- fail.
p5_alt.

test5 :-
    ( p5 -> show(test5, yes)
    ; show(test5, no)
    ).

% -------------------------
% cut inside choice generator
% -------------------------

p6(X) :-
    member1(X, [1,2,3]),
    X > 1,
    !.

test6 :-
    p6(X),
    show(test6, X).

% -------------------------
% multiple clauses + cut
% -------------------------

p7(1) :- !.
p7(2).
p7(3).

test7 :-
    p7(X),
    show(test7, X).

% -------------------------
% if-then-else with cut in then
% -------------------------

p8(X) :-
    ( 1 =:= 1 ->
        (!,
        X = then)
    ;
        X = else
    ).

test8 :-
    ( p8(then) -> show(test8, then)
    ; show(test8, else)
    ).

% -------------------------
% cut commits variable choice
% -------------------------

p9(X) :-
    member1(X, [10,20,30]),
    X = 10,
    !.

test9 :-
    p9(X),
    show(test9, X).

% -------------------------
% parent cut after called predicate
% -------------------------

a10(1).
a10(2).
a10(3).

p10(X) :-
    a10(X),
    X > 1,
    !.

test10 :-
    p10(X),
    show(test10, X).

% -------------------------
% cut with disjunction in body
% -------------------------

p11(X) :-
    ( X = 100 ; X = 200 ),
    !.

test11 :-
    p11(X),
    show(test11, X).

% -------------------------
% cut and arithmetic
% -------------------------

p12(N, X) :-
    ( N > 0 ->
        (A is N + 2,
        !,
        X is A * 1)
    ;
        X = 0
    ).

test12 :-
    p12(5, X),
    show(test12, X).

% -------------------------
% cut stops second solution
% -------------------------

p13(X) :-
    member1(X, [1,2,3]),
    !.

test13 :-
    p13(X),
    show(test13, X).

% -------------------------
% explicit fallback blocked by cut
% -------------------------

p14 :-
    a14,
    !.
p14 :-
    fail.

a14.

test14 :-
    ( p14 -> show(test14, yes)
    ; show(test14, no)
    ).

% -------------------------
% explicit fallback needed but blocked
% -------------------------

p15 :-
    a15,
    !,
    b15.
p15 :-
    c15.

a15.
b15 :- fail.
c15.

test15 :-
    ( p15 -> show(test15, yes)
    ; show(test15, no)
    ).

% -------------------------
% nested cut helper
% -------------------------

h16(X) :-
    member1(X, [1,2,3]),
    X > 1,
    !.

p16(X) :-
    h16(X).

test16 :-
    p16(X),
    show(test16, X).

% -------------------------
% cut after deterministic arithmetic check
% -------------------------

p17(X) :-
    X is 1 + 0,
    !.

test17 :-
    p17(X),
    show(test17, X).

% -------------------------
% cut in first branch of disjunction
% -------------------------

p18 :-
    ( a18, ! ; b18 ).

a18.
b18 :- fail.

test18 :-
    ( p18 -> show(test18, ok)
    ; show(test18, ng)
    ).

% -------------------------
% cut with repeated generator
% -------------------------

p19(X) :-
    member1(X, [1,2,3,4]),
    X > 2,
    !.

test19 :-
    p19(X),
    show(test19, X).

% -------------------------
% cut in second clause after first fails
% -------------------------

p20(X) :-
    X = 1,
    fail.
p20(X) :-
    X = 2,
    !.
p20(X) :-
    X = 3.

test20 :-
    p20(X),
    show(test20, X).