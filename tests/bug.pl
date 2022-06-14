hanoi(1, From, To, _) :-
  write([From, to, To]), nl.
hanoi(N, From, To, Via) :-
  N1 is N - 1, hanoi(N1, From, Via, To),
  write([From, to, To]), nl,
  hanoi(N1, Via, To, From).

%?- hanoi( 16, a, b, c).

