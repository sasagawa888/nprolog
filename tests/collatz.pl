 % Collatz problem
 
collatz(1).
collatz(N) :-
    N > 1, N mod 2 =:= 0,
    N1 is N//2,
    write(N1), write(' '),
    collatz(N1).
collatz(N) :-
    N > 1, N mod 2 =:= 1,
    N1 is 3*N+1,
    write(N1), write(' '),
    collatz(N1).