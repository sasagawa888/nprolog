

foo(X,Y,Z) :- X -> Y ; Z.


test(cut) :-
    (true -> X = 1 ; X = 2),
    X == 1.

%test(cut_failure) :-
%    (false -> X = 1 ; X = 2),
%    X == 2.