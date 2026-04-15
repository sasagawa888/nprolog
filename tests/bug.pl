


show(Test, X) :-
    write(Test), write(' : '), write(X), nl.

test8 :-
    ((fail ; fail ; X = ok)),
    show(test8, X).

% expected:
% test8 : ok

