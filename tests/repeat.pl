
repeat0.
repeat0 :- repeat0.

test :-
    repeat,
    write(a),
    fail.
    