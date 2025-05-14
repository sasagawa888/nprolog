# Multiple World Mechanism

# Usage

```
?- use_module(mpworld).
```

The multiple world mechanism similar to that implemented in Dr. Hideyuki Nakajima's Prolog/KR is extended. Use the with/2 predicate.
There is an example in the mpw.pl file in the tests folder.
See Chapter 7 https://stacks.stanford.edu/file/druid:bv252vf8932/bv252vf8932.pdf

# Example

```
:- use_module(mpworld).

% World multiplex mechanism
%example1
:- with(a,assertz(p(a))).
:- with(b,assertz(p(b))).
:- with(c,assertz(p(c1))).
:- with(c,assertz(p(c2))).

%example2
% with(w1,with(w2,with(w3,fly(canary)))). -> yes
% with(w1,with(w2,with(w3,fly(penguin)))). -> no
:- with(w1,assertz(bird(canary))).
:- with(w1,assertz(bird(penguin))).
:- with(w2,assertz((fly(X) :- bird(X)))).
:- with(w3,deny(fly(penguin))).

```
