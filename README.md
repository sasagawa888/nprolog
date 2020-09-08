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

## Intaraction

```
?- is prompt.


```

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

?- halt().
- good bye -

```
