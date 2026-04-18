

my_length([], A, A) :- !.
my_length([_ | Xs], A, N) :- A1 is A + 1, my_length(Xs, A1, N).

my_length(Xs, N) :- my_length(Xs, 0, N).