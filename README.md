# N-Prolog
N-Prolog(NPL) is an interpreter to be subset of ARITY-Prolog.
it is based on O-Prolog. Project is now startup.

N-Prolog is NOT ISO-Prolog.

## Installation
On Linux  type "make" on terminal.


# invoke
To invoke opl, enter command from terminal

```
./npl

-c option is for start up file.

e.g.
./npl -c init.pl

-r option is for Not editable REPL mode.
Default, REPL is editable.
```

## Goal
I hope that Prolog will become more popular. I hope many people enjoy Prolog. NPL aims at easy handling.

## example
```prolog
N-Prolog Ver 0.02
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
?- ['queens.pl'].
yes
?- test.
....
[9,7,2,4,1,8,5,3,6]
[9,7,3,8,2,5,1,6,4]
[9,7,4,2,8,6,1,3,5]
no
?- 



?- halt.
- good bye -

```

# builtin predicate

```
<
=/
\=
= ..
=<
> 
>=
=:=
=\=
==
\==
@<
@=<
@>
@>=
abolish/1
abort/0
ansi_cuu/1
ansi_cud/1
ansi_cuf/1
ansi_cub/1
arg/3
arg0/3
assert/1
asserta/1
assertz/1
atom/1
atomic/1
call/1
chdir/1
compare/3
concat/3
consult/1
current_op/3
current_predicate/1
dec/2
delete/1
display/1
edit/1
fail/0
float/1
flush/0 
gc/0
halt/0
ifthen/2
ifthenelse/3
inc/2
integer/1
is/2
keysort/2
length/2
listing/0
listing/1
mkdir/1
name/2
nl/0
nonvar/1
nospy/1
notrace/0
number/1
not/1
read/1
reconsult/1
shell/1
sort/2
spy/1
string/1
string_length/2
system/1
trace/0
true/0
var/1
write/1
write/2
writeq/1
writeq/2
```

# builtin (extension)
```
append/3
between/3
member/2
measure/1   measure elapsed time
reverse/2
```

# function
```
+
-
*
/
^  expt
** expt
<< leftshift
>> rightshift
/\ logical and
\/ logical or
\  complement
xor exclusive or
iand inclusive and
abs 
sin
asin
cos 
acos
tan
atan
exp
log
floor
ceiling
truncate
float
float_integer_part
float_fraction_part
sign
min
max
random
```