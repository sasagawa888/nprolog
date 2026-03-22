

foo(X,Y,Z) :- X -> Y ; Z.


%test(cut) :-
%    (true -> X = 1 ; X = 2),
%    X == 1.

%test(cut_failure) :-
%    (fail -> X = 1 ; X = 2),
%    X == 2.


%test(X) :-
%    true -> X = 1.


%test(cut_failure1) :-
%    (fail -> X = 1),
%    X = 1.