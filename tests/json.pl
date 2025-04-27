
% JSON tests
:- use_module(json).

test(predicate) :-
    term_json(foo(1),J),
    J = {"predicate":"foo","argument":[1]}.
test(rpredicate) :-
    J = {"predicate":"foo","argument":[1]},
    term_json(T,J),
    T = foo(1).


test(clause) :- 
    term_json((foo(1):-bar(2)),J),
    J = {"head":{"predicate":"foo","argument":[1]},"body":{"predicate":"bar","argument":[2]}}.
test(rclause) :- 
    J = {"head":{"predicate":"foo","argument":[1]},"body":{"predicate":"bar","argument":[2]}},
    term_json(T,J),
    T = ((foo(1):-bar(2))).


test(true) :-
    term_json(T,"true"),
    T = '@true'.
test(rtrue) :-
    term_json('@true',J),
    J = "true".

test(null) :-
    term_json(T,"null"),
    T = '@null'.

test(rnull) :-
    term_json('@null',J),
    J = "null".
    

test(basic) :-
    term_json([id=1,id=2],J),
    J = [{"id":1},{"id":2}].

test(rbasic) :-
    J = [{"id":1},{"id":2}],
    term_json(T,J),
    T = [id=1,id=2].
