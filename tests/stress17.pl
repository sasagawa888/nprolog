% ================================
% length/2 Stress Test Suite
% ================================
:-  use_module(utils).
% ---- utility ----

run(Test) :-
    write(Test), write(' : '),
    ( call(Test) -> writeln(ok)
    ; writeln(fail)
    ).

run_fail(Test) :-
    write(Test), write(' : '),
    ( call(Test) -> writeln('unexpected success')
    ; writeln(ok)
    ).

% ---- basic ----

test1 :- length([], 0).
test2 :- length([a,b,c], 3).
test3 :- length([1,2,3,4,5], N), N =:= 5.

% ---- generation ----

test4 :- length(L, 0), L = [].
test5 :- length(L, 3), L = [_,_,_].

% ---- partial binding ----

test6 :- length([a,b|T], 5), length(T, 3).
test7 :- length([_|T], N), N =:= 1, T = [].

% ---- nondet ----

test8 :-
    findall(L, length(L, 2), X),
    X = [[_,_]].

% ---- relational ----

test9 :- length(L, N), N = 2, L = [_,_].
test10 :- length(L, N), L = [a,b,c], N = 3.

% ---- failure ----

test11 :- length([a,b], 3).
test12 :- length([a,b,c], 2).

% ---- abnormal ----

test13 :- length(X, -1).     % implementation dependent
test14 :- length(foo, 3).    % implementation dependent

% ---- large ----
% make_list is used in list libraly

make_list1(0, []).
make_list1(N, [_|T]) :-
    N > 0,
    N1 is N - 1,
    make_list1(N1, T).

test15 :-
    make_list1(10000, L),
    length(L, N),
    N =:= 10000.

% ---- consistency ----

test16 :-
    length(L, N),
    length(L, M),
    N =:= M.

% ---- infinite stress ----

test17 :-
    length(L, N),
    length(L, N).

% ================================
% runner
% ================================

run_all :-
    writeln('--- basic ---'),
    run(test1),run(test2), run(test3),

    writeln('--- generation ---'),
    run(test4), run(test5),

    writeln('--- partial binding ---'),
    run(test6), run(test7),

    writeln('--- nondet ---'),
    run(test8),

    writeln('--- relational ---'),
    run(test9), run(test10),

    writeln('--- failure expected ---'),
    run_fail(test11), run_fail(test12),

    %writeln('--- abnormal (check behavior) ---'),
    %run(test13), run(test14),

    writeln('--- large ---'),
    run(test15),

    writeln('--- consistency ---'),
    run(test16),

    writeln('--- infinite stress (manual check) ---'),
    writeln('test17 should not loop badly or leak choicepoints').

