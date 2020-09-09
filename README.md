# N-Prolog
N-Prolog(NPL) is an interpreter and compiler to be subset of ARITY-Prolog.
it is based on O-Prolog. Project is now startup.

N-Prolog is NOT ISO-Prolog.

## Installation
On Linux  type "make" on terminal.


# invoke
To invoke opl, enter command from terminal

```
./npl

-c option is for start up file.

./npl -c init.pl

-r option is for Not editable REPL mode.
Default, REPL is editable.
```

## Goal
I hope that Prolog will become more popular. I hope many people enjoy Prolog. NPL aims at easy handling.

## example
```prolog
N-Prolog Ver 0.01
?- length([1,2,3],X).
X = 3
yes


?- X is 2^1000.
X = 107150860718626732094842504906000181056140481170553360744375038837035105112493612249319837881569585812
7594672917553146825187145285692314043598457757469857480393456777482423098542107460506237114187795418215304
6474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376
yes

?- append(X,Y,[1,2,3]).
X = []
Y = [1,2,3];
X = [1]
Y = [2,3];
X = [1,2]
Y = [3];
X = [1,2,3]
Y = [];
no
?- 

?- halt.
- good bye -

```

# builtin predicate

```
=/2
\=/2
append/3
assert/1
asserta/1
assertz/1
fail/0
float/1
gc/0
halt/0
integer/1
is/2
length/2
member/2
nl/0
nonvar/1
number/1
not/1
true/0
var/1
write/1
writeq/1 writeq/2
```
