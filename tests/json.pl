

dt1({"head":{"predicate":"foo","argument":["varX"]},
    "body":{{"predicate":"bar","argument":["varX"]},{"predicate":"boo","argument":["varX"]}}}).

dt2({"id":1}).

dt3({"id":[1,2,3]}).

test(predicate) :-
    term_json(foo(1),J),
    J = {"predicate":"foo","argument":[1]}.

test(clause) :- 
    term_json((foo(1):-bar(2)),J),
    J = {"head":{"predicate":"foo","argument":[1]},"body":{"predicate":"bar","argument":[2]}}.