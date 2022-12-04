
%example1
:- with(a,assertz(p(a))).
:- with(b,assertz(p(b))).
:- with(c,assertz(p(c1))).
:- with(c,assertz(p(c2))).

%example2
:- with(w1,assertz(bird(canary))).
:- with(w1,assertz(bird(penguin))).
:- with(w2,assertz((fly(X) :- bird(X)))).
:- with(w3,deny(fly(penguin))).