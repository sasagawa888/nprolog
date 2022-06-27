# N-Prolog

N-Prolog(NPL)はArity/Prolog32互換のインタプリタ、コンパイラです。 

N-PrologはISO-Prolog互換ではありません.
Arity/prolog32については右記をご参照ください。  http://petergabel.info/ArityProlog32/ArityProlog32PredList/

manual.txtにユーザーズマニュアルがあります。ご参照ください。
ライセンスは修正BSDに基づいています。無償でお使いいただけます。

## OS
下記のOSでの動作を確認しております。

- Ubuntu
- Linux MINT
- RaspberryPI Raspbian
- macOS

Windowsでお使いの場合にはWSLをお使いください。


## インストール
homeディレクトリにおいてGithubからクローンを作るか、あるいはzipファイルをダウンロードします。
linuexの端末において"sudo make install"とタイプします。

参考 https://www.youtube.com/watch?v=36vUd8ThMF0

## アンインストール
Linuxの端末において"sudo make uninstall"とタイプします。


# 起動
N-Prologを起動するには下記のように端末からタイプします。

```
npl

-c オプションはファイルを読み込んで起動します。

例
npl -c init.pl

-r オプションは編集可能REPLをOFFにして起動します。
指定しない場合にはREPLは編集可能となっています。
```

他のオプション

```
$ npl -h
List of options:
-c(--code) filename   -- NPL starts after reading the file.
-h(--help)            -- display help.
-r(--repl)            -- NPL does not use editable REPL.
-s(--script) filename -- NPL run file with script mode.
-v(--version)         -- dislplay version number.

```


## 目標
私はPrologがより多くの人に親しまれることを望んでいます。多くの人にPrologを楽しんでいただきたいと思います。
NPLは簡単な取扱を目指しています。


## 実行例
```prolog
N-Prolog Ver 1.50
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

# 編集可能なREPL
キーバインディングは下記の通りです。

- → move right
- ← move left 
- ↑ recall history older
- ↓ recall history newer
- return insert end of line
- back-space  backspace
- Esc Tab completion

# ユニコード
unicodeが使用可能です。

```

動物(人間).
人間(ジョー).

動物(X) :- 人間(X).

?- ['tests/animal.pl'].
yes
?- 動物(ジョー).
yes
?- 動物(X).
X = 人間 .
yes

```

# 組込み述語

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
dup/2
edit/1
eq/2
expand_term/2
fail/0
float/1
float_text/3
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
string_term/2
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

# 組み込み述語（拡張）

```
atom_concat/3
append/3
between/3
char_code/2
compile_file/1  (invoke compiler)
compound/1
ground/1
heapd/2     (dump heap area from 1st arg to 2nd arg)
member/2
measure/1   (measure elapsed time)
reverse/2 
bagof/3
setof/3
finall/3
```

# wiringPi 
ラズペリーPIにおいてはwiringPiのための組み込み述語が含まれます。

```
N-Prolog <==================================> C
wiringpi_spi_setup(ch speed) <===> wiringPiSPISetup (SPI_CH, SPI_SPEED)
wiringpi_setup_gpio  <===> wiringPiSetupGpio()
pin_mode(n, 'output) <====> pinMode(n, OUTPUT) or 'input -> INPUT 'pwm-output -> PWM_OUTPUT
digital_write(n, v) <===> digitalWrite(n, v)
digital_write_byte(v) <===> digitalWriteByte(value)
digital_read(pin) <===> digitalRead(pin)
delay(howlong) <===> void delay(unsigned int howLong)
delay_microseconds(howlong) <===> void delay_microseconds(unsigned int howLong)
pull_up_dn_control(pin, pud) <===> pullUpDnControl(pin,pud)
pwm_set_mode('pwm_mode_ms) <===> pwmSetMode(PWM_MODE_MS); or 'pwm_mode_bal -> PWM_MODE_BAL
pwm_set_clock(n) <===> pwmSetClock(n)
pwm_set_range(n) <===> pwmSetRange(n)
pwm_write(pin, value) <===> pwmWrite(pin , value)

timer_microseconds/1
usage:  timer_microseconds(on).   timer on
        timer_microseconds(off).  timer off
        timer_microsecons(X).     unify X elapsed time. float number ,unit seconds , valid digits microsecnods
        see tests/measure.pl
```


# 関数
```
pi             定数　円周率
X + Y          加算
X - Y　        減算
X * Y　        乗算
X / Y　        通常の除算　結果は浮動小数点数
X // Y　       整数の除算　結果は整数。
X ^ Y          べき乗
X ** Y         べき乗
X << Y         XをYだけ左へビットシフトする。（整数のみ）
X >> Y         XをYだけ右へビットシフトする。（整数のみ）
X mod Y        XをYで割った剰余（整数のみ）
X /\ Y         論理積
X \/ Y         論理和
\X  complement
X xor Y exclusive or
X iand Y inclusive and
abs(X)         Xの値の絶対値
sin(X)　       Xの正弦関数
asin(X)　      Xの逆正弦関数
cos(X) 　      Xの余弦関数
acos(X)　      Xの逆余弦関数
tan(X)　       Xの正接関数
atan(X)　      Xの逆正接関数
exp(X)　　     Xの指数関数
log(X)　　     Xの対数関数
floor(X)
ceiling(X)
truncate(X)
float(X)
float_integer_part(X)
float_fraction_part(X)
sign(X)
min(X,Y)
max(X,Y)
sqrt(X)
randi(n)      n以下0以上の整数乱数
randome　    １以下０以上の浮動小数点数乱数
```