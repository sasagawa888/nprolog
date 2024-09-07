% test cases
test_conditional :-
    (X = 1 -> Y = 2 ; Y = 3),
    Y == 2.


test_backtracking :-
    (X = 1 ; X = 2),
    X == 1.


test_unification :-
    X = 1,
    X = 1,
    X == 1.

test_unification_failure :-
    \+ (X = 1, X = 2).

test_cut :-
    (true -> X = 1 ; X = 2),
    X == 1.

test_cut_failure :-
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


test_fib :-
    fib(5, F),
    F == 5.

test_list :-
    [H|T] = [1, 2, 3],
    H == 1,
    T == [2, 3].

test_list_recursion :-
    length([1, 2, 3, 4], L),
    L == 4.

test_append :-
    append([1, 2], [3, 4], Result),
    Result == [1, 2, 3, 4].


test_member :-
    member(3, [1, 2, 3, 4]),
    \+ member(5, [1, 2, 3, 4]).

run_tests :-
    test_unification,
    test_unification_failure,
    test_list,
    test_list_recursion,
    test_fib,
    test_cut,
    test_cut_failure,
    test_conditional,
    test_backtracking,
    test_append,
    test_member,
    write('All tests passed.'), nl.


/* more tests */
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

% sort
test_sort :- 
    quick_sort([3,1,4,1,5,9,2,6,5], Sorted), Sorted = [1,1,2,3,4,5,5,6,9].



max1(X, Y, X) :- X >= Y, !.
max1(_, Y, Y).

test_max :-
    max1(3, 4, 4),
    max1(5, 2, 5),
    max1(7, 7, 7). 

% 集合操作のテスト
parent(john, mary).
parent(john, bob).
parent(susan, mary).
parent(susan, bob).

% bagof:
:- bagof(Child, parent(john, Child), Children), Children = [mary, bob].

% setof:
:- setof(Child, parent(_, Child), UniqueChildren), UniqueChildren = [bob, mary].

% findall:
:- findall(Child, parent(_, Child), AllChildren), AllChildren = [mary, bob, mary, bob].
