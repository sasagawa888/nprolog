% Benchmark prime number generation  using   the  sieve  of Eratosthenes
% algorithm with assert/retract. This benchmark tests assert/retract and
% JIT index generation and destruction.
%
% Auther: Jan Wielemaker
% Copyright: Public domain.

:- dynamic(prime/1).
:- dynamic(candidate/1).

retractall(Head) :-
    \+ \+ (
        clause(Head, Body),
        retract((Head :- Body)),
        fail
    ).
retractall(_).

top :- clean, primes(10000), !.

clean :-
    retractall(prime(_)),
    retractall(candidate(_)).

primes(N) :-
    \+ ( range(2, N, I), \+ assertz(candidate(I))),
    sieve(N).

sieve(Max) :-
    retract(candidate(First)),
    !,
    assertz(prime(First)),
    First < Max,
    sieve(First, 2, Max),
    sieve(Max).
sieve(_).

sieve(N, Mul, Max) :-
    I is N*Mul,
    I =< Max,
    !,
    (   retract(candidate(I))
    ->  true
    ;   true
    ),
    Mul2 is Mul+1,
    sieve(N, Mul2, Max).
sieve(_, _, _).

% is between/3, but only in mode +,+,-.  Simple Prolog definition
% for portability.
range(Low, High, Low) :-
    Low =< High.
range(Low, High, I) :-
    Low2 is Low+1,
    Low2 =< High,
    range(Low2, High, I).