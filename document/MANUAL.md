# N-Prolog User's manual
under construction.

### □ [Filename]
Read from a file into a database using a consult predicate.
-When using Filename, the resoncult predicate is used.
You can specify multiple files. [Filename1, filename2, ...] 

### □ abolish(name/Arity)
Removes all clauses with the specified name arity from the data berth. 

### □ abort
Stop the current program. Return to the interpreter after the program ends.
If the program is compiled, abort restarts its goal. 

### □ ansi_cuu(N)
Move the cursor up N lines. 

### □ ansi_cud(N)
Move the cursor down N lines. 

### □ ansi_cuf(N)
Move the cursor forward N digits. 

### □ ansi_sub(N)
Move the cursor back N digits. 

### □ ansi_cpr(Row,Col)
The predicate ansi_cpr is used to know the current cursor position.
If the arguments Row and Col are not assigned, the coordinates of the current cursor position are in rows and columns.
Unify each argument.
If it has been assigned, compare that number with the coordinates of the current position. 

### □ ansi_scp
The predicate ansi_scp saves the current cursor position and the character attributes at that position. 

### □ ansi_rcp
The predicate ansi_rcp restores the cursor position and attributes saved by ansi_scp. 

### □ ansi_ed

### □ ansi_el

### □ ansi_sgr(G)
The predicate ansi_sgr sets graphic attributes. G can be an integer or a list of integers.
The following are standard values only and may differ depending on the model. 

- 0 Reset all attributes to default.
- 1 emphasis
- 4 Underline
- 5 Blink
- 7 Reverse
- 8 secret
- 30 black
- 31 Red
- 32 green
- 33 yellow
- 34 blue
- 35 Magenta
- 36 Light blue
- 37 white
- 40 Background color black
- 41 Background color red
- 42 Background color green
- 43 Background color yellow
- 44 Background color blue
- 45 Background color Magenta
- 46 Background color light blue
- 47 Background color white 


### □ arg(N,Term,X)
Unify X to the Nth value of the term.
(Arguments are numbered from 1 in the increasing direction.) 

### □ arg0(N,Term,X)
Unify X to the value of the N + 1th argument of the term.
(Arguments are numbered from 0 in the increasing direction.) 

### □ assert(Clause)
Add a clause to the end of the predicate. 

### □ asserta(Clause)
Add a clause to the top of the predicate. 

### □ assertz(Clause)
Add a clause to the end of the predicate.

### □ atom(X)
Check if X is an atom. 

### □ atom_string(Atom,String)
Convert an atom to a string or convert a string to an atom. 

### □ atomic(X)
Check if X is an atom data type.

### □ break
Suspend program execution and display an interpreter prompt.
The program can be restarted by the following types: 

end_of_file

### □ call(P)
Call the interpreted goal P. 

### □ chdir(Path)
Change or revert to the current directory.

### □ clause(Head,Body)
Unify Head and Body to the head and body of the node, respectively.
Head must be assigned.
example 


```
?- assert((foo(X) :- write(X))).
yes
?- clause(foo(X),B).
X = v_1
B = (write(v_1));
no
?- 
```

### □ close(Handle)
Closes the file specified by Handle. 

### □ ctr_dec(Ctr,X)
Decreases the value of a counter and returns the previous value of that counter. 

### □ ctr_inc(Ctr,X)
Increases the value of a counter and returns the previous value of that counter. 

### □ ctr_is(Ctr,X)
Returns the current counter value. 

### □ ctr_set(Ctr,X)
Set the counter to the specified value. 

### □ current_op(Proc,Assoc,Op)
Returns the operator constants currently defined in the database while backtracking. 

### □ current_predicate(Predicate)
Returns the predicate currently defined in the database while backtracking.

### □ date(date(Year,Month,Day))
Set the year, month, and day. 

### □ date_day(date(Year,Month,Day),WeekDay)
Returns the day of the week on a given date as a number between 0 (Sunday) and 6 (Saturday). 

### □ dec(N,X)
Subtract 1 from the number N and give it to the value X. 

### □ delete(Filename)
Delete the specified file. 

### □ directory(Path,Name,Mode,Time,Date,Size)
List the directory files specified by Path.

example 

```
?- directory('./',A,B,C,D,E).
A = 'link.c'
B = file
C = time(13,20,47)
D = date(2020,10,4)
E = 4281 ;
A = 'compute.o'
B = file
C = time(7,54,38)
D = date(2020,10,18)
E = 37544 .
```

### □ display(Term)
Write the term to standard output with prefix notation. 

### □ dpu(Handlein,Handleout)
Allocate a second fundle to the open file.

### □ edit(Filename)
Switch from the interpreter to the editor for editing the file specified by Filename.
Call nano as an editor. When you exit nano, the contents of the file will be read into the interpreter.
If the environment variable EDITOR has a value, call that editor.

example 

```
EDITOR=emacs
```

### □ eq(X,Y)
Check if X and Y are the same data object and are stored at the same address. 

### □ expand_term(Term,Newterm)
DCG: Converts a term in a limited clause grammar to an equivalent Prolog term. 

### □ float(X)
Check if X is a floating point number.

### □ float_text(Float,Text,Format)
Converts a floating point number to a string according to the Format specification, or converts a string to a floating point number.
format is the same format as the C language format. 

### □ flush
Remove all characters in the type-ahead buffer.

### □ functor(Struct,Name,Arity)
Returns the structure name and arity. 

### □ gc(Amount)
Launch garbage collection.
When the argument is full, the cells that are no longer needed in the heap area are collected. 

### □ get(Char)
Read the next character from a standard input device, skipping unprinted characters,
Unify the ASCII value with Char. 

### □ get0(Char)
Read the next character from a standard input device, skipping unprinted characters,
Unify the ASCII value with Char. get0 does not skip non-printing characters. 

### □ get0_noecho(Char)
Read the following characters from the standard input device and unify the ASCII value to Char.
get0_noecho does not display the character on the standard output device. 

### □ halt
Exits the interpreter. 

### □ instance(Ref,Term)
Returns the term for that reference number. 

### □ integer(X)
Check if X is an integer. 

### □int_text(Integer,String)
Convert an integer to a string, or convert a string to an integer. 

### □ X is E 
Evaluate E and unify its value to X.

### □ keysort(L1,L2)
Sort the list L1 in standard order. List elements must be in the form Key_Value.
The sorted list is returned to L2. Even if it is duplicated, it won't be united. 

### □ leash(Mode)
Constrain the port to the specified Mode. 

### □ length(L,N)
Change the length of the list back to N. 

### □ listing
Write all current database predicates to standard output. 

### □ listing(Name/Arith)
### □ listing([Name/Arity,Name/Arity])
Write all clauses to the specified predicate or list of predicates in the current database to standard output. 

### □ list_text(List,AtomString)
Convert a character list to an atom (if the atom already exists) or a string, or convert an atom or string
Convert to a character list. 

### □ mkdir(Path)
Create a new directory. 

### □ name(Atom,List)
Convert a list to an atom, or convert an atom or an integer to a list. 

### □ open(Handle,Filename,Access)
Open an existing file. 

Access is one of the following 

```
r read
w write
rw read and write
a append
ra read and append
```

### □ read(Term)
標準入力装置から項を読み込む。

### □ read(Handle,Term)
ファイルから項を読み込む。

### □ read_line(Handle,X)
Handleで指定したファイルから1行読む。

### □ recorda(Key,Term,Ref)
述語の戦闘に項を加えて、その項の新しい参照番号を戻す。

### □ recordz(Key,Term,Ref)
述語の終わりに項を追加し、その項に割り当てられた参照番号を戻す。

### □ recordh(Table_name,Sort_key,Term)
ハッシュテーブルに項を記録する。

### □ ref(X)
Xが参照番号かどうかを調べる。

### □ removeallh(Table_name)
ハッシュテーブルを削除する。

### □ removeh(Table_name,Sort_key,Term)
ハッシュテーブルから項を削除する。

### □ reset_op
演算子の定義をそのデフォールト値に戻す。

### □ retrieveh(Table_name,Sort_key,Term)
ハッシュテーブルから項を戻す。


### □ rename(Filename,Newname)
ファイル名を変更する。

### □ rmdir(Path)
ディレクトリを削除する。

### □ shell(Command)
BASHコマンドを実行し、成功する。

### □sort(L1.L2)
リストL1を標準の順序に並び替え、重複を排除しL2にソート済みリストを戻す。

### □ spy(Name/Arity)
デバッグ用のスパイポイントとして述語を指定する。

### □ stdin(FileHandle,Goal)
そのゴールの間、標準入力を変更する。

### □ stdout(FileHandle.Goal)
そのゴールの間、標準入力を変更する。

### □ stdinout(InFile,OutFile,goal)
そのゴールの間、標準入力と標準出力を変更する。

### □ string(X)
Xがストリングかどうかを調べる。

### □ string_length(String,Length)
ストリングの長さを戻す。

### □ string_term(String,Term)
ストリングを項に変更する。

### □ substring(InString,N,Length,OutString)
ストリングからサブストリングを抽出する。
Nは開始位置　１から始まる自然数
Lengthは抽出する文字列の長さ

### □ syntaxerrors(Old,New)
文法エラーメッセージ出力の可否の指定を行うか、あるいは現在の設定をチェックする。
yesでエラーメッセージ出力し、noでエラーメッセージを出力しない。

### □ system(P)
Pが組込述語かどうかを調べる。

### □ tab(N)
スペース文字を指定の数だけ標準出力装置に書く。

### □ tab(Handle,N)
スペース文字を指定の数だけファイルに書く。

### □ tell(Filename)
出力のためにファイルをオープンし、それを現在の出力ファイルにする。

### □ telling(X) 
tellによりオープンされている出力ファイルの名前を戻す。


### □ time(time(Hours,Minutes,Seconds))
時、分、秒を返す。

```
時 [0-23]
分 [0-59]
秒 [0-61]
```

### □ trace
デバッガをオンにする。

### □ true
ゴールは常に成功する。

### □ var(X)
Xが代入された変数かどうかを調べる。

### □ write(Term)
標準出力装置に書く。

### □ write(Handle,Term)
指定のファイルに項を書く。

### □ writeeq(Term)
標準出力装置に書き、その項がProlog項として読み出しが可能なように、
アトムと関数子を引用符で囲む。

### □ writeeq(Time,Term)
項を指定のファイルに書き、その項がProlog項として読み出しが可能なように、
アトムと関数子を引用符で囲む。

## デバッガコマンド
プログラムを起動することでデバッグを開始する。プログラムはスパイポイントに達する
まで実行される。そこに達すると、デバッガはプログラムを停止させ、呼び出し晩坊、
ポート、及び現在のプログラムの位置するゴールを表示する。
例えば、デバッガをオンにし、スパイポイントを,my_appendnにセットして述語
my_appendのデバッグを開始する。

```
?- ['tests/test.pl'].
yes
?- trace.
yes
?- spy(my_append/3).
yes
?- my_append([1,2,3],[4,5],X).
** (0) CALL: my_append([1,2,3],[4,5],X)?> 
** (0) REDO: my_append([1,2,3],[4,5],X)?> 
** (1) CALL: my_append([2,3],[4,5],v_4)?> 
** (1) REDO: my_append([2,3],[4,5],v_4)?> 
** (2) CALL: my_append([3],[4,5],v_8)?> 
** (2) REDO: my_append([3],[4,5],v_8)?> 
** (3) CALL: my_append([],[4,5],v_12)?> 
X = [1,2,3,4,5] .
** (3) EXIT: my_append([],[4,5],v_12)?> 
** (2) EXIT: my_append([3],[4,5],v_8)?> 
** (1) EXIT: my_append([2,3],[4,5],v_4)?> 
** (0) EXIT: my_append([1,2,3],[4,5],X)?> 
yes
?- 
```

デバッグが終了したらnotraceを実行します。これをしないと実行が遅くなります。

```
?- notrace.
```

次の表示項目は、どのようにデバッガが現在のゴールに到達したかを示す記号である。

- **　ゴールがスパイポイントであることを示す。
- *>　ゴールがスパイポイントであり、かつスキップコマンドの結果このゴールに到達したことを示す。
- >   ゴールはスパイポイントではないが、スキップコマンドの結果このゴールに到達したことを示す。
- ->　xコマンドの結果デバッガが以前の選択点まで経路を逆に戻っていることを示す。


次の４つのポートがある。

-　CALLはゴールが呼ばれるポートである。インタプリタはゴールの呼び出し毎に番号を与える。
数字はデバッガが呼び込まれたとき０から始まり、デバッグが終了したときに０で終わる。

- EXITはゴールが成功したときプログラムが抜け出すポートである。

- REDOはプログラムがバックトラッキングでゴールに再び入るポートである。

- FAILはゴールが失敗のときプログラムが抜け出すポートである。


### a
プログラムを中断終了します。デバッガをオフにしてインタープリタのプロンプトを
表示します。

### b
デバッグ中のプログラムは終了しないでインタープリタのプロンプトを表示します。
end_of_fileと入力することにより、中断状態は解除され、デバッグを続けることが
できます。有効な中断の数だけ、インタープリタのプロンプトに？が余計に付きます。
例えば、中断が３回有効になっているときには、インタープリタのプロンプトは次の
ように表示されます。

```
???-
```

### c
デバッガに次のポートまで１ステップずつ進む（creep)ように指示します。この方法で
実行をステップ毎に追うことができます。エンターキーはｃを入力することと同じです。

### d
現在のゴールを表示します。

### e
インタープリタを終了します。このコマンドでLinuxのプロンプトに戻ります。

### f
デバッガを直接FAILポートまで進ませます。すでにそのゴールが失敗であることが
わかっている場合に有効なコマンドです。

### h
ヘルプスクリーンを表示します。

### l（エル）
スパイポイントからスパイポイントへ飛ば（leap)します。
現在のスパイポイントのプログラム実行をステップ毎においことはしないで、
次のスパイポイントまでスキップすることができます。

### n
デバッガをオフにします。

### q
ゴールのEXITポートあるいはFAILポートにスキップします。
しかし、そのゴールの中にスパイポイントのセットがあればそのスパイポイントで実行は止まります。

### s
ゴールの中に他のスパイポイントがあっても、そのゴールのexitポートあるいは、FAILポートにスキップ
します。このコマンドはCALLポートまたはREDOポートからだけ使用できます。

### <esc>
エスケープキー　sを入力することと同じです。

### w
現在のゴールを書き出します。

### X
FAILポートあるいはREDOポートで使用できます。
CALLポートあるいはEXITポートに達するまで、デバッガに失敗を続けさせます。

### @
二次のゴールを呼び出し、ゴールが終了したとき、直ちにデバッガに戻ります。

### ;
EXITポートで使用され、デバッガに現在のゴールのREDOポートに進ませます。






## DCG：限定節文法
以下は中島秀之先生の「Prolog」（産業図書）にある例です。

A dog bites a postman.

この英文は構造をもっています。その構造は一定の文法規則に従っています。

```
文 -> 名詞句、動詞句
名詞句　->冠詞、名詞
冠詞　->a
名詞　->dog
名詞　->postman
動詞句　->動詞、名詞句
動詞　->bites
```

これを直接にPrologで記述することも可能ではあるのですが、もっと楽な方法があります。
それがDCGです。上記の規則をほぼそのままの形で記述することが可能です。

下記のコードをファイルに書き込み、Prologコードと同様にconsultで読み込ませます。

```
s --> np,vp.
np --> det,n.
det -->[a].
n -->[dog].
n -->[postman].
vp --> v,np.
v -->[bites].
```

なお、文法カテゴリーは省略形によっています。

```
文　sentence　s
名詞　noun　n
名詞句　noun　phrase　np
動詞　verb　v
限定詞　determiner　det
動詞句　verb　phrase
```

これをN-Prolog処理系で動かしてみましょう。
phraseという述語で文が正しいかどうかを確認することができます。


```
| ?- phrase(s,[a,dog,bites,a,postman]).
yes
| 
```


このようにリストで与えられた文が与えられた文構造になっていることが確かめられました。間違った文を与えたらどうでしょう？


```
| ?- phrase(s,[bites,a,dog,a,postman]).
no
|
```

偽が返っています。文法規則に反しています。


面白いことに文法規則にかなった文を生成させることもできます。


```
| ?- phrase(s,X).
X = [a,dog,bites,a,dog];
X = [a,dog,bites,a,postman];
X = [a,postman,bites,a,dog];
X = [a,postman,bites,a,postman];
no
| 
```

セミコロンを入力しバックトラックさせるといくつかの文がでてきました。
意味は変ですが文法規則には則っています。


## コンパイラ
まだ不完全ながらコンパイラも付属しています。起動時にコンパイラを読み込んでいます。

compile_file(filename)

このようにしてコンパイルするPrologコードの記述されたファイルをしてしてください。
C言語に変換し、さらにGCCでオブジェクトファイルにコンパイルします。

例えば9queensをコンパイルする場合には

compile_file('tests/queens.pl').
とします。これによりqueens.oというファイルが生成されます。

['tests/queens.o']. あるいは　consult('queens.o').　と入力すると読み込まれます。
あとは通常の述語と同様に使えます。

部分的に末尾再帰最適化の処理をしました。queensではSWI-Prologに近い実行速度がでます。


## Hello

My name is Kenichi Sasagawa.
I learned prolog at Arity/Prolog in the 1980s.
Now, I'm making a Prolog interpreter and compiler.
I want to make it compatible with the familiar Arity/Prolog.
Thank you.