
# O-Prolog
O-Prolog(OPL) is an interpreter and compiler to be compatible with Edinburgh Prolog and ISO-Prolog.
https://qiita.com/sym_num/items/e6e35d3e1bff41f0efe5

## Installation
On Linux  type "make" on terminal.

On Windows rename winmakefile -> makefile. and type "make" on terminal.
Require MINGW gcc

We confirmed the operation in the following environment.
- Ubuntu 16.04 GCC 5.4
- Raspbery Pi3 Raspbian GCC 6.3
- openSUSE leap 42.3 GCC 4.8.5
- Debian GNU/Linux GCC 6.3
- OpenBSD (Thanks Alexander)
- Windows10 MINGW GCC 5.3

# invoke
To invoke opl, enter command from terminal

```
opl (Windows)
./opl (Linux)

-c option is for start up file.

./opl -c init.pl

-r option is for Not editable REPL mode.
Default, REPL is editable.
```

### startup.pl
Even if you do not specify an option, if there is a file startup.pl in the current directory, OPL loads it and start it.

## Goal
I hope that Prolog will become more popular. I hope many people enjoy Prolog. OPL aims at easy handling.

## Intaraction

```
| (vertical bar) is prompt.

following code is assertion.

human(john).
error(X) :- human(X).

To question, require ?- operator.

?- error(john).

Compiler
read compiler from library

| ?- use_module(library(compiler)).
yes

?- compile_file(filename.pl).

The Compiler generates filename.o object file.

?- ['filename.o'].
```

## example
```prolog
O-Prolog Ver 1.70 (Chisato)
| ?- use_module(library(compiler)).
yes
| ?- compile_file('queens.pl').
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
| ?- ['queens.o'].
yes
| ?- time(test).
Elapsed Time=0.023919 (second)
no
| ?- time(test16).
Elapsed Time=0.381781 (second)
no

Bignum
| ?- X is 2^1000.
X = 107150860718626732094842504906000181056140481170553360744375038837035105112493612249319837881569585812
7594672917553146825187145285692314043598457757469857480393456777482423098542107460506237114187795418215304
6474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376
yes

Char set
Linux default is unicode.

Windows default is SJIS.

to change. set_prolog_flag(char_set,unicode).
```


## Builtin editor
OPL(Linux version) has builtin editor.
```
Invoke editor
?- edit(file-name). example edit('queens.pl')

?- edit([]). edit recent file again.

Command
CTR+O　save file.
CTRL+X　quit editor.
CTRL+K　delete selection.
CTRL+U　paste from clip board.
Editing
↑↓←→　move cursol
ESC A mark current row position. After this operation, cursol up or down reverse selected rows. ESC A again, unmark. Similer to nano editor
Enter key insert tab for Lisp automatic
Insert key switch insert/overwrite
Tab key insert tab for Lisp
BackSpace key delete backword char
Delete key　delete forwaord char
Home key display top page
ESC |(SSH)
End key　display end page
ESC /(SSH)
PageUp key PageUp
Ctrl+Y(SSH)
PageDown PageDown
Ctrl+V(SSH)

ESC TAB completion.

Setting
set_editor(indent,auto)　set auto indent mode.
set_editor(indent,manual) set manual indet mode. To indent tab key.
set_editor(tab,2)
set tab 2.
set_editor(tab,4) set tab 4.
set_editor(tab,8) set tab 8.

syntax highlighting.
n = 0-7
0=Black, 1=Red, 2 =Green, 4=Blue, 5=Maggenta, 6=Syan, 7=White.
set_editor(operator_color,n)
set_editor(builtin_color,n)
set_editor(extended_color,n)
set_editor(quote_color,n)
set_editor(comment_color,n)
```

## WiringPi
Version for Raspberry has wiringPi.

In order to use wiringPi, you need to invoke OPL with super user.

```
sudo ./opl

?- ['wiringpi.o'].

OPL <==================================> C

wiringpi_spi_setup(ch,speed)  <===>　　wiringPiSPISetup (SPI_CH, SPI_SPEED)
wiringpi_setup_gpio(X)  <===>  X=wiringPiSetupGpio()
pin-mode(N,output)  <====> pinMode(N, OUTPUT)  or input -> INPUT or pwm_output ->PWM-OUTPUT
digital_write(n,v)  <===> digitalWrite(n, v);
digital_write_byte(value)  <===>  digitalWriteByte(value)
digital_read(pin,X)  <===> X=digitalRead(pin)
delay(howlong) <===> void delay(unsigned int howLong)
pull_up_dn_control(pin, pud)  <===> pullUpDnControl(pin,pud)
pwm_set_mode(pwm_mode_ms)  <===> pwmSetMode(PWM_MODE_MS) or pwm_mode_bal -> PWM_MODE_BAL
pwm_set_clock(n) <===>  pwmSetClock(n);
pwm_set_range(n) <===>  pwmSetRange(n);
pwm_write(pin,value)  <===> pwmWrite(pin , value)
LED on/off
setup :-
    not(flag),wiringpi_setup_gpio(X),assert(flag),
    pin_mode(5,output).

test(0).
test(N) :-
    digital_write(5,1),
    delay(1000),
    digital_write(5,0),
    delay(1000),
    N1 is N - 1,
    test(N1).


%execute

?- setup.
?- test(10).


control servo moter
%hardware Micro servo Digital 9g SG90

setup :-
    not(flag),wiringpi_setup_gpio(X),assert(flag),
    pin_mode(18,pwm_output),
    pwm_set_mode(pwm_mode_ms),
    pwm_set_clock(400),
    pwm_set_range(1024).


test1(N) :-
    pwm_write(18,N).

%execute

?- setup.
?- test1(24).
?- test1(115).
```

## TCP/IP

```
server_create/2
　 server_create(N,S)
N = atom of port number
S = socket descriptor

example
server_create('5000',S).

server_create/3
server_create(IP,N,S)
IP = atom of IP address
N = atom of port number
S = socket discriptor

example
server_create('127.0.0.1','5000',S).

server_accept/3

server_accept(S,IP,C)
S = socket discriptor
C = socket discriptor for client


clinet_connect/3
client_connect(IP,N,S)
IP = atom of ip address
N = atom of port number
S = discriptor

socket_send/2
socket_send(S,X)
S = socket discriptor
X = atom as data


example
socket_send(S,hello).

socket_recieve/2
socket_send(S,Y)
S = socket discriptor
Y = atom as recieved data

socket_close/1
socket_close(S)
S = socket discriptor


example code

%test for TCP/IP

server :-
    server_create('127.0.0.1','5000',S),
    server_accept(S,Y,C),
    repeat,
    socket_recieve(C,D),
    write(D),
    socket_send(C,D),
    D == end,
    socket_close(S).


client :-
    client_connect('127.0.0.1','5000',S),
    repeat,
    read(X),
    socket_send(S,X),
    socket_recieve(S,Y),
    write(Y),
    Y == end,
    socket_close(S).
```
