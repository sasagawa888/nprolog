# N-Prolog ユーザーズマニュアル

### □ ;
ゴールとゴールの区切りを表す。選言

### □ ,
ゴールとゴールの区切りを表す。連言

### □ E1 < E2
E1の値がE2の値より小さいかどうかを調べる。

### □ T1 = T2
T1とT2をユニフィケーションするように試みる。

### □　T1 \\= T2
T1がT2にユニフィケーションしたら失敗する。

### □　Struct =.. List
univと言われている。ストラクチャをリストにあるいはリストをストラクチャに変換する。

### □ E1 =< E2
E1の値がE2の値より小さいかまたは、等しいかを調べる。

### □ E1 > E2
E1の値がE2の値より大きいかどうかを調べる。

### □ E1 >= E2
E1の値がE2の値より大きいかまたは、等しいかを調べる。

### □ E1 =:= E2
E1とE2の値が等しいかどうかを調べる。

### □ E1 =\\= E2
E1とE2の値が等しくないかどうかを調べる。

### □ T1 == T2
項１と項２が同一かどうかを調べる。

### □ T1 \\== T2
T1とT2が同一でないかどうかを調べる。

### □ T1 @< T2
T1がT2の前にあるかどうかを調べる。

### □ T1 @＝< T2
T1がT2の前にあるかまたは等しいかどうかを調べる。

### □ T1 @> T2
T1がT2の後にあるかどうかを調べる。


### □ T1 @>= T2
T1がT2の後にあるかまたは等しいかどうかを調べる。

### □ [Filename]
consult述語を用いてファイルからデータベースに読み込む。
-Filenameを使ったときはresoncult述語が使われる。
ファイルを複数指定することもできる。[Filename1,filename2,...]

### □ [-'Filename']
`[-'Filename']` を使ったときは **reconsult** の動作になる。  
（同名述語がある場合は置き換える。）

複数指定もできる。`[-'file1.pl', -'file2.pl', ...]`

### □ abolish(name/Arity)
データべースから指定の名前をアリティーを持つすべての節を取り除く。

### □ abort
現在のプログラムを中止する。プログラムの終了後インタープリタに戻る。
プログラムがコンパイルされたものなら、abortはそのゴールを再スタートさせる。

### □ ansi_cuu(N)
カーソルをN行上げる。

### □ ansi_cud(N)
カーソルをN行下げる。

### □ ansi_cuf(N)
カーソルをN桁進める。

### □ ansi_cub(N)
カーソルをN桁戻す。

### □ ansi_cpr(Row,Col)
述語ansi_cprは、現在のカーソルの位置を知るために用いる。
引数Row、Colが代入されていない引数なら、現在のカーソル位置の座標を行と桁で
各引数にユニフィケーションする。
もし、代入されていれば、その数と現在位置の座標を比較する。

### □ ansi_scp
述語ansi_scpは、現在のカーソル位置とその位置の文字の属性をセーブする。

### □ ansi_rcp
述語ansi_rcpは、ansi_scpでセーブしたカーソル位置と属性をもとに戻す。

### □ ansi_ed
述語ansi_edはディスプレーとクリアする。

### □ ansi_el
述語ansi_elはカーソル位置から行末までを消す。

### □ ansi_sgr(G)
述語ansi_sgrは、グラフィック属性をセットする。Gは、整数でも整数のリストでもよい。
以下はあくまでも標準値で、機種によって異なる場合がある。

- 0 すべての属性をデフォルトに戻す。
- 1 強調
- 4 下線
- 5 ブリンク
- 7 リバース
- 8 シークレット
- 30 黒
- 31 赤
- 32 緑
- 33 黄色
- 34 青
- 35 マゼンダ
- 36 水色
- 37 白
- 40 背景色　黒
- 41 背景色　赤
- 42 背景色　緑
- 43 背景色　黄色
- 44 背景色　青
- 45 背景色　マゼンダ
- 46 背景色　水色
- 47 背景色　白



### □ arg(N,Term,X)
Xを項のN番目の値にユニフィケーションする。
（引数は１から増加方向に番号付けられている。）

### □ arg0(N,Term,X)
Xを項のN+1番目の引数の値にユニフィケーションする。
（引数は０から増加方向に番号付けられている。）

### □ assert(Clause)
節を述語の先頭に追加する。

### □ asserta(Clause)
節を述語の終わりに追加する。

### □ assertz(Clause)
節を述語の終わりに追加する。

### □ atom(X)
Xがアトムかどうかを調べる。

### □ atom_string(Atom,String)
アトムをストリングに変換またはストリングをアトムに変換する。

### □ atomic(X)
Xがアトムデータタイプかどうか調べる。

### □ break
プログラムの実行を一時中断し、インタプリタプロンプトを表示する。
次のタイプによってプログラムは再開できる。

end_of_file

### □ call(P)
インタープリトされたゴールPを呼び出す。

### □ chdir(Path)
現在のディレクトリを変えるかまたは戻す。

### □ clause(Head,Body)
HeadとBodyを節の頭部と本体にそれぞれユニフィケーションする。
Headは代入されなければならない。
例

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
Handleで指定したファイルをクローズする。

### □ ctr_dec(Ctr,X)
カウンタの値をへらし、そのカウンタの以前の値を戻す。

### □ ctr_inc(Ctr,X)
カウンタの値を増加させ、そのカウンタの以前の値を戻す。

### □ ctr_is(Ctr,X)
現在のカウンタ値を戻す。

### □ ctr_set(Ctr,X)
カウンタを指定の値にセットする。


### □ current_op(Proc,Assoc,Op)
バックトラックしつつデータベース中に現在定義されている演算子定数を戻す。

### □ current_predicate(Predicate)
バックトラックしつつデータベース中に現在定義されている述語を戻す。

### □ date(date(Year,Month,Day))
年、月、日を戻す。

### □ date_day(date(Year,Month,Day),WeekDay)
与えられた日付の曜日を０（日曜日）から６（土曜日）の間の数値で戻す。

### □ dec(N,X)
数Nから１を引いて、値Xに与える。

### □ delete(Filename)
指定のファイルを削除する。

### □ directory(Path,Name,Mode,Time,Date,Size)
Pathで指定したディレクトリファイルをリストする。

例

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
前置記法で項を標準出力装置に書き出す。

### □ dpu(Handlein,Handleout)
オープンされているファイルに第２のハンドルを割り当てる。

### □ edit(Filename)
Filenameで指定したファイルのエディトのため、インタープリタからエディタに切り換える。
エディタとしてedlogを呼び出す。Edlogを終了するとファイルの内容はインタプリタに読み込まれる。
環境変数EDITORに値が設定されている場合にはそのエディタを呼び出す。

例

```
EDITOR=emacs
```
### □ edit(Filename,Option)
Optionはatomのrまたはcです。rの場合にはreconsultでファイルを読み込みます。
cの場合にはconsultでファイルを読み込みます。

### □ eq(X,Y)
XとYが同じデータオブジェクトであり、かつ同じアドレスにストアされているかを調べる。

### □ expand_term(Term,Newterm)
DCG：限定節文法の項を等価なProlog項に変換する。

### □ erase(Ref)
指定の参照番号で格納されている項を取り除く。

### □ eraseall(Key)
指定のkeyで格納されている全ての項を取り除く。

### □ errcode(Code)
一番新しいエラーメッセージのコードを戻す。

### □ fileerrors(Old,New)
Linux　I/Oエラーメッセージの出力をするか否かを指定するか、あるいはこの指定の状態をチェックする。

### □ float(X)
Xが浮動小数点数かどうかを調べる。

### □ float_text(Float,Text,Format)
浮動小数をFormatの指定に応じてストリングに変換するか、又はストリングを浮動小数に変換する。
formatは次のうちのいずれかである。

- general 後に続く０はサプレスされる。
- fixed(N) Nは小数点の位置（０－１５）を与える。
- scientific(N) Nは指数表記法での小数点の桁数を与える。

### □ flush
タイプアヘッドバッファ内のすべての文字を取り除く

### □ functor(Struct,Name,Arity)
ストラクチャ名とアリティーを戻す。

### □ gc(Amount)
ガベージコレクションを起動する。
引数がfullのときはヒープ領域でもう必要としなくなったセルを回収する。

拡張：引数にonを与えるとGC起動時にメッセージを表示する。引数にoffを与えると
メッセージを表示しなくなる。

### □ get(Char)
非印刷文字をスキップしながら、標準入力装置から次の文字を読み、
ASCII値をCharとユニフィケーションする。

### □ get0(Char)
非印刷文字をスキップしながら、標準入力装置から次の文字を読み、
ASCII値をCharとユニフィケーションする。get0は非印刷文字をスキップしない。

### □ get0_noecho(Char)
標準入力装置から次の文字を読み込み、ASCII値をCharにユニフィーケーションする。
get0_noechoは標準出力装置にその文字を表示しない。

### □ halt
インタープリタから抜け出す。

### □ instance(Ref,Term)
その参照番号の項を戻す。

### □ integer(X)
Ｘが整数かどうかを調べる。

### □int_text(Integer,String)
整数をストリングに変換するか、又はストリングを整数に変換する。

### □ X is E 
Eを評価し、その値をXにユニフィケーションする

### □ key(Key)
現在のデータベースの中のキーに対する名前とアリティーを戻す。

### □ key(Key,Ref)
キーに対する参照番号を戻す。

### □ keysort(L1,L2)
リストL1を標準の順序に並べる。リストの要素はKey_Valueの形式でなければならない。
ソートされたリストはL2に戻される。だぶっていても１つにされない。

### □ leash(Mode)
ポートを指定のModeに拘束する。

### □ length(List, N)
リストの長さがNであるかどうかを調べる。  
（必要に応じて、長さNのリストを生成することもできる。）

### □ listing
標準出力装置に現在のデータベースの述語をすべて書き出す。

### □ listing(Name/Arith)
### □ listing([Name/Arity,Name/Arity])
標準出力装置に現在のデータベースの中の指定の述語または述語のリストに対するすべての節を書き出す。

### □ list_text(List,AtomString)
文字リストをアトム（アトムが既に存在すれば）またはストリングに変換するか、アトムまたはストリングを
文字リストに変換する。

### □ mkdir(Path)
新しいディレクトリを作る。

### □ name(Atom,List)
リストをアトムに変換するか、アトムまたは整数をリストに変換する。

### □ nth_char(N,String,Char)
ストリングの先頭からN個離れた文字のASCII（unicode）を戻す。

### □ nth_ref(Key,N,Ref)
項のチェイニングの先頭からN番目の参照番号を戻す。

### □ open(Handle,Filename,Access)
既存のファイルをオープンする。

Accessは次のいずれか

```
r read (text)
w write (text)
rw read and write (text)
a append (text)
ra read and append (text)
rb read (binary)
wb write (binary)
```

### □ read(Term)
標準入力装置から項を読み込む。

### □ read(Handle,Term)
ファイルから項を読み込む。

### □ read_line(Handle,X)
Handleで指定したファイルから1行読む。

### □ read_string(MaxLength,X)
標準入力装置からストリングを読む。

### □ read_string(Handle,MaxLength,X)
指定ファイルからストリングを読む。

### □ record_after(Ref,Term,Newref)
Refの後に項を加えて、その項の新しい参照番号を返す。

### □ recorda(Key,Term,Ref)
述語の先頭に項を加えて、その項の新しい参照番号を戻す。

### □ recorded(Key,Term,Ref)
バックトラッキングしつつ、指定のキー下に格納されている項とその参照番号を戻す。

### □ recordz(Key,Term,Ref)
述語の終わりに項を追加し、その項に割り当てられた参照番号を戻す。

### □ recordh(Table_name,Sort_key,Term)
ハッシュテーブルに項を記録する。

### □ ref(X)
Xが参照番号かどうかを調べる。

### □ removeallh(Table_name)
ハッシュテーブルを削除する。

### □ replace(Ref,Term)
指定の参照番号の項をTermで与えた項で置き換える。

### □ removeh(Table_name,Sort_key,Term)
ハッシュテーブルから項を削除する。

### □ reset_op
演算子の定義をそのデフォールト値に戻す。

### □ retract(Clause)
データベースから節を除く。


### □ retrieveh(Table_name,Sort_key,Term)
ハッシュテーブルから項を戻す。


### □ rename(Filename,Newname)
ファイル名を変更する。

### □ rmdir(Path)
ディレクトリを削除する。

### □ save
前回のセーブ後にデータベースに加えられた変更の全てをセーブする。
N-Prolog起動時にセーブしたファイルを読み込む。

### □ save(Name)
内部データベースを指定のNameのプログラム名でセーブする。

### □ shell(Command)
BASHコマンドを実行し、成功する。

### □sort(L1.L2)
リストL1を標準の順序に並び替え、重複を排除しL2にソート済みリストを戻す。

### □ spy(Name/Arity)
デバッグ用のスパイポイントとして述語を指定する。

### □ statistics(Atom,Val)
Prologシステムの使用状況の情報を戻す。

Atom -> Val
free -> ヒープ領域の空セルの数
wp   -> working-pointerの値
sp   -> stack-pointerの値
gc   -> GCが起動した回数
ac   -> variant-pointerの値

### □ stdin(FileHandle,Goal)
そのゴールの間、標準入力を変更する。

### □ stdout(FileHandle.Goal)
そのゴールの間、標準出力を変更する。

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
Xが未束縛変数かどうかを調べる。

### □ write(Term)
標準出力装置に書く。

### □ write(Handle,Term)
指定のファイルに項を書く。

### □ writeq(Term)
標準出力装置に書き、その項がProlog項として読み出しが可能なように、
アトムと関数子を引用符で囲む。

### □ writeq(Time,Term)
項を指定のファイルに書き、その項がProlog項として読み出しが可能なように、
アトムと関数子を引用符で囲む。


## 拡張述語
- compile_file(fn)
ファイルネームfnのPrologコードをコンパイルしてオブジェクトファイルを生成します。

- heapd(start,end)
整数startから整数endまでのheap領域のアドレスを表示します。

- measure(E)
述語Eの実行時間を計測して表示します。

- existerrors(Old,New)
述語不存在エラーメッセージの出力の可否の指定を行うか、あるいは現在のその設定をチェックする。

## ISO由来の組み込み述語

### □ \\+(Goal)
Goal を実行し，成功した場合は失敗し，失敗した場合は成功する（否定の失敗）。  
Goal 内で行われた変数束縛は外側には影響しない。


### □ atom_concat(A1,A2,A3)
アトム A1 と A2 を連結した結果を A3 にユニフィケーションする。  
※ N-Prolog では分解方向（例: atom_concat(X,b,ab)）はサポートしていない。


### □ append(L1,L2,L3)
リスト L1 と L2 を連結したリストを L3 にユニフィケーションする。


### □ member(E,List)
E が List の要素であれば成功する。


### □ between(Low,High,N)
整数 N が Low 以上 High 以下であれば成功する。  
N が変数の場合，Low から High まで順に生成する。


### □ select(E,L1,L2)
リスト L1 から要素 E を 1 つ取り除いた結果を L2 にユニフィケーションする。


### □ succ(N0,N1)
N1 が N0+1 であれば成功する。


### □ maplist(Goal,List)
List の各要素 X に対して call(Goal,X) を実行し，すべて成功すれば成功する。


### □ compound(Term)
Term が複合項（構造体）であれば成功する。


### □ ground(Term)
Term に変数が含まれていなければ成功する。


### □ once(Goal)
Goal の最初の解のみを求め，それ以降のバックトラックを行わない。


### □ atom_codes(Atom,Codes)
Atom と，その文字コードのリスト Codes を相互にユニフィケーションする。


### □ atom_chars(Atom,Chars)
Atom と，その文字のリスト Chars を相互にユニフィケーションする。


### □ char_code(Char,Code)
1 文字アトム Char とその文字コード Code を相互にユニフィケーションする。


### □ number_codes(Number,Codes)
数値 Number とその表記の文字コード列 Codes を相互にユニフィケーションする。


### □ number_chars(Number,Chars)
数値 Number とその表記の文字リスト Chars を相互にユニフィケーションする。


### □ predicate_property(Pred,Property)
述語 Pred の性質 Property を取得または列挙する。


### □ bagof(Template,Goal,Bag)
Goal の解から Template を集めたリストを Bag に返す。  
自由変数ごとに結果が分かれる。解が無い場合は失敗する。


### □ setof(Template,Goal,Set)
bagof/3 と同様だが，結果を重複除去しソートした集合として返す。  
解が無い場合は失敗する。


### □ findall(Template,Goal,List)
Goal のすべての解から Template を集めたリストを List に返す。  
解が無い場合は空リストを返す。


### □ write_canonical(Term)
Term を演算子を用いない正規形式で出力する。

### □ write_canonical(Stream,Term)
指定した Stream に正規形式で Term を出力する。


### □ atom_length(Atom,Length)
Atom の文字数を Length にユニフィケーションする。


### □ get_code(Code)
現在の入力から文字コードを 1 つ読み取る。

### □ get_code(Stream,Code)
指定した Stream から文字コードを 1 つ読み取る。


### □ get_char(Char)
現在の入力から 1 文字読み取る。

### □ get_char(Stream,Char)
指定した Stream から 1 文字読み取る。


### □ get_byte(Byte)
現在の入力から 1 バイト読み取る。

### □ get_byte(Stream,Byte)
指定した Stream から 1 バイト読み取る。


### □ put_char(Char)
現在の出力に 1 文字書き出す。

### □ put_char(Stream,Char)
指定した Stream に 1 文字書き出す。


### □ put_code(Code)
現在の出力に文字コード Code を書き出す。

### □ put_code(Stream,Code)
指定した Stream に文字コード Code を書き出す。


### □ put_byte(Byte)
現在の出力に 1 バイト書き出す。

### □ put_byte(Stream,Byte)
指定した Stream に 1 バイト書き出す。


### □ peek_code(Code)
現在の入力から文字コードを 1 つ読み取るが，入力位置は進めない。

### □ peek_code(Stream,Code)
指定した Stream から文字コードを読み取るが，入力位置は進めない。


### □ peek_char(Char)
現在の入力から 1 文字読み取るが，入力位置は進めない。

### □ peek_char(Stream,Char)
指定した Stream から 1 文字読み取るが，入力位置は進めない。


### □ peek_byte(Byte)
現在の入力から 1 バイト読み取るが，入力位置は進めない。

### □ peek_byte(Stream,Byte)
指定した Stream から 1 バイト読み取るが，入力位置は進めない。


### □ flush_output
現在の出力ストリームをフラッシュする。

### □ flush_output(Stream)
指定した Stream をフラッシュする。


### □ catch(Goal,Catcher,Recovery)
Goal 実行中に throw/1 により送出された例外が Catcher と一致した場合，Recovery を実行する。


### □ throw(Exception)
例外 Exception を送出する。


### □ unify_with_occurs_check(T1,T2)
循環構造を禁止したユニフィケーションを行う。


### □ current_input(Stream)
現在の入力ストリームを Stream に返す。


### □ current_output(Stream)
現在の出力ストリームを Stream に返す。


### □ set_input(Stream)
現在の入力ストリームを Stream に設定する。


### □ set_output(Stream)
現在の出力ストリームを Stream に設定する。


### □ use_module(File)
File をロードする。


### □ module(Module)
現在のモジュールを設定または宣言する。


### □ copy_term(T1,T2)
T1 のコピーを T2 にユニフィケーションする。変数は共有されない。


### □ at_end_of_stream(Stream)
Stream が終端に達していれば成功する。


### □ stream_property(Stream,Property)
Stream の性質 Property を取得または列挙する。


### □ dynamic(PredSpec)
PredSpec を動的述語として宣言する。  
※ N-Prolog では foo/1 と指定した場合，foo 述語全体が dynamic となる。


### □ initialization(Goal)
ファイルロード時に Goal を実行する。


### □ retractall(Head)
Head に一致するすべての節を削除する。


### □ subsumes_term(General,Specific)
General が Specific を包含する（より一般である）場合に成功する。

## 関数

- pi             定数　円周率
- X + Y          加算
- X - Y　        減算
- X * Y　        乗算
- X / Y　        通常の除算　結果は浮動小数点数
- X // Y　       整数の除算　結果は整数。
- X ^ Y          べき乗
- X ** Y         べき乗
-  X << Y         XをYだけ左へビットシフトする。（整数のみ）
- X >> Y         XをYだけ右へビットシフトする。（整数のみ）
- X mod Y        XをYで割った剰余（整数のみ）
- X /\ Y         論理積
- X \/ Y         論理和
- \X  complement
- X xor Y        排他的論理和
- abs(X)         Xの値の絶対値
- sin(X)　       Xの正弦関数
- asin(X)　      Xの逆正弦関数
- cos(X) 　      Xの余弦関数
- acos(X)　      Xの逆余弦関数
- tan(X)　       Xの正接関数
- atan(X)　      Xの逆正接関数
- exp(X)　　     Xの指数関数
- ln(X)          Xの自然対数関数
- log(X)　　     Xの常用対数関数
- sqrt(X)        Xの平方根
- round(X,Y)     Xを小数点以下N桁に丸める。Nは０〜１５の整数」
- integer(X)     Xを整数に変換する。
- float(X)       Xを浮動小数点数に変換する。
- randi(n)       n以下0以上の整数乱数
- random 　      １以下０以上の浮動小数点数乱数


## デバッガコマンド
プログラムを起動することでデバッグを開始する。プログラムはスパイポイントに達する
まで実行される。そこに達すると、デバッガはプログラムを停止させ、呼び出し番号、
ポート、及び現在のプログラムの位置するゴールを表示する。
例えば、デバッガをオンにし、スパイポイントを,my_appendにセットして述語
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
DCGを使うためにはモジュールを呼び出してください。
use_module(dcg).

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
動詞句　verb phrase　vp
```

これをN-Prolog処理系で動かしてみましょう。
phraseという述語で文が正しいかどうかを確認することができます。


```
?- phrase(s,[a,dog,bites,a,postman]).
yes

```


このようにリストで与えられた文が与えられた文構造になっていることが確かめられました。間違った文を与えたらどうでしょう？


```
?- phrase(s,[bites,a,dog,a,postman]).
no

```

偽が返っています。文法規則に反しています。


面白いことに文法規則にかなった文を生成させることもできます。


```
?- phrase(s,X).
X = [a,dog,bites,a,dog];
X = [a,dog,bites,a,postman];
X = [a,postman,bites,a,dog];
X = [a,postman,bites,a,postman];
no
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


## 多重世界機構
:- use_module(mpworld).

中島秀之先生のProlog/KRに実装されていたものと同様な多重世界機構を拡張してあります。with/2述語を使います。
testsフォルダのmpw.plファイルに例題があります。参照　第7章　https://www.jstage.jst.go.jp/article/jjsai/2/3/2_367/_pdf

## Edlog エディタ
EdlogはN-Prolog専用のエディタです。

### 起動
edlog  あるいは　edlog filename と端末から入力してください。
詳細はctrl+hでヘルプを参照してください。



# 組込み述語

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
erase/1
eraseall/1
expand_term/2
fail/0
float/1
float_text/3
flush/0 
gc/1
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
document/SUPERSET.mdをご参照ください。


# 関数
```
pi             定数　円周率
X + Y          加算
X - Y　        減算
X * Y　        乗算
X / Y　        通常の除算　結果は浮動小数点数
X // Y　       整数の除算　結果は整数。
X ^ Y          べき乗
X << Y         XをYだけ左へビットシフトする。（整数のみ）
X >> Y         XをYだけ右へビットシフトする。（整数のみ）
X mod Y        XをYで割った剰余（整数のみ）
X /\ Y         論理積
X \/ Y         論理和
\X  complement ビットごとの補数（ビット反転）
abs(X)         Xの値の絶対値
sin(X)　       Xの正弦関数
asin(X)　      Xの逆正弦関数
cos(X) 　      Xの余弦関数
acos(X)　      Xの逆余弦関数
tan(X)　       Xの正接関数
atan(X)　      Xの逆正接関数
exp(X)　　     Xの指数関数
ln(X)          Xの自然対数関数
log(X)　　     Xの常用対数関数
sqrt(X)        Xの平方根関数
round(X,N)     Xを小数点以下N桁に丸める。Nは０〜１５の整数
randi(n)       n以下0以上の整数乱数
random　       １以下０以上の浮動小数点数乱数
```