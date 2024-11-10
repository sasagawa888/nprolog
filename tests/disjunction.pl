% Testing the disjunction (choice) behavior in Prolog

% A rule with two choices
test(X) :-
    X = 1;   % First choice
    X = 2.   % Second choice

% Test case 1: Check that 1 and 2 can be obtained
test_case_1 :-
    test(X),
    write(X), nl,  % Write the value of X to the output
    fail.  % Force backtracking to try all choices

% A rule with three choices
test_3_choices(X) :-
    X = a;    % First choice
    X = b;    % Second choice
    X = c.    % Third choice

% Test case 2: Check that 'a', 'b', and 'c' are returned sequentially
test_case_2 :-
    test_3_choices(X),
    write(X), nl,  % Write the value of X to the output
    fail.  % Force backtracking to try all choices

% Conditional disjunction
test_conditional(X) :-
    X = 1, !; % First choice with cut (!), prevents backtracking
    X = 2.    % Second choice

% Test case 3: Check that only 1 is returned (no backtracking due to the cut)
test_case_3 :-
    test_conditional(X),
    write(X), nl.  % Write the value of X to the output