# N-Prolog
N-Prolog(NPL) is an interpreter and compiler to be subset of ARITY-Prolog.
it is based on O-Prolog. Project is now startup.

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

### startup.pl
Even if you do not specify an option, if there is a file startup.pl in the current directory, OPL loads it and start it.

## Goal
I hope that Prolog will become more popular. I hope many people enjoy Prolog. NPL aims at easy handling.

## Intaraction

```
?- is prompt.


Compiler
read compiler from library

?- use_module(library(compiler)).
yes

?- compile_file(filename.pl).

The Compiler generates filename.o object file.

?- ['filename.o'].
```

## example
```prolog
N-Prolog Ver 0.01
?- use_module(library(compiler)).
yes
?- compile_file('queens.pl').
pass1
pass2
compiling test16
compiling test
compiling queen
compiling queen_2
compiling qdelete
compiling tail nodiag
invoke GCC
yes
?- ['queens.o'].
yes
?- time(test).
Elapsed Time=0.023919 (second)
no
?- time(test16).
Elapsed Time=0.381781 (second)
no

Bignum
?- X is 2^1000.
X = 107150860718626732094842504906000181056140481170553360744375038837035105112493612249319837881569585812
7594672917553146825187145285692314043598457757469857480393456777482423098542107460506237114187795418215304
6474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376
yes

