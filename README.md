# N-Prolog
N-Prolog(NPL) is an interpreter and compiler to be compatible with Arity/Prolog32.

N-Prolog is NOT ISO-Prolog.
About Arity/prolog32  see  http://petergabel.info/ArityProlog32/ArityProlog32PredList/

## Installation
On Linux  type "make" on terminal.

On Raspberry Pi type "make raspi" on terminal.

see https://www.youtube.com/watch?v=IJTj8VRxUHc&fbclid=IwAR1KLf1ytyTlGX26dEzYru83Wu679HvKi-v87MdtIS_cvRM9Qr4wZZW3wD4

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
N-Prolog Ver 1.12
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
?- ['tests/queens.pl'].
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
/+
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
ansi_sgr/1
ansi_cpr/2
ansi_scp/0
ansi_rcp/0
ansi_ed/0
ansi_el/0
arg/3
arg0/3
assert/1
asserta/1
assertz/1
atom/1
atomic/1
break/0
call/1
chdir/1
clause/2
close/1
compare/3
concat/3
consult/1
ctr_set/2
ctr_dec/2
ctr_inc/2
ctr_is/2
current_op/3
current_predicate/1
date/1
date_day/2
dec/2
delete/1
directory/6
display/1
edit/1
eq/2
expand_term/2
fail/0
float/1
flush/0 
gc/0
get/1
get/2
get0/1
get0/2
get0_noecho/1
halt/0
ifthen/2
ifthenelse/3
in/2
inc/2
instance/2
integer/1
is/2
keysort/2
length/2
listing/0
listing/1
mkdir/1
name/2
nl/0
nl/1
nonvar/1
nospy/1
notrace/0
number/1
not/1
out/1
open/3
read/1
read_line/2
reconsult/1
recorda/3
recordh/3
recordz/3
ref/1
reset_op/0
retrieveh/3
rmdir/1
see/1
seeing/1
seen/0
shell/1
sort/2
spy/1
string/1
string_length/2
syntaxerrors/2
system/1
tell/1
telling/1
told/0
time/1
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
atom_concat/3
append/3
between/3
compile_file/1  (invoke compiler)
compound/1
ground/1
member/2
measure/1   (measure elapsed time)
reverse/2
```

# wiringPi 
On paspberry PI, on terminal enter "make raspi".
As a result, N-Prolog includes builtin predicates of WiringPi. 


```
N-Prolog <==================================> C
wiringpi_spi_setup(ch speed) <===> wiringPiSPISetup (SPI_CH, SPI_SPEED)
wiringpi_setup_gpio  <===> wiringPiSetupGpio()
pin_mode(n, 'output) <====> pinMode(n, OUTPUT) or 'input -> INPUT 'pwm-output -> PWM_OUTPUT
digital_write(n, v) <===> digitalWrite(n, v)
digital_write_byte(v) <===> digitalWriteByte(value)
digital_read(pin) <===> digitalRead(pin)
delay(howlong) <===> void delay(unsigned int howLong)
pull_up_dn_control(pin, pud) <===> pullUpDnControl(pin,pud)
pwm_set_mode('pwm_mode_ms) <===> pwmSetMode(PWM_MODE_MS); or 'pwm_mode_bal -> PWM_MODE_BAL
pwm_set_clock(n) <===> pwmSetClock(n)
pwm_set_range(n) <===> pwmSetRange(n)
pwm_write(pin, value) <===> pwmWrite(pin , value)
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