

classify_num(N, X) :-
    ( N < 0 ->
        X = negative
    ; N =:= 0 ->
        X = zero
    ; N < 10 ->
        X = small
    ; N < 100 ->
        X = medium
    ;
        X = large
    ).


goal(member(a, [x,a,z])).
goal(append([1,2], [3,4], [1,2,3,4])).
goal(between(1,3,2)).
goal(classify_num(15, medium)).

run_goal(Name, Goal, ok) :-
    named_goal(Name, Goal),
    call(Goal).


named_goal(g1, member(a, [x,a,z])).
named_goal(g2, append([1,2], [3], [1,2,3])).
%named_goal(g3, classify_num(0, zero)).
%named_goal(g4, nested_if(1, -1, a_only)).

nested_if(A, B, X) :-
    ( A > 0 ->
        ( B > 0 ->
            X = both_positive
        ;
            X = a_only
        )
    ;
        ( B > 0 ->
            X = b_only
        ;
            X = none_positive
        )
    ).


test_meta(L) :-
    findall(Name, run_goal(Name, _, ok), L).