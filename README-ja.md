**「このソフトウェアは平和と自由のための技術である。  
いかなる暴圧・抑圧・人権侵害・独裁の一助となることを望まない。」**


# N-Prolog

N-Prolog(NPL)はARITY/PROLOG(MS-DOS)上位互換のインタプリタ、コンパイラです。 

**N-PrologはISO-Prolog互換ではありません.** ARITY/PROLOG(MS-DOS)上位互換です。

MANUAL.mdにユーザーズマニュアルがあります。ご参照ください。
ライセンスは修正BSDに基づいています。無償でお使いいただけます。

![npl](npl.png)

## ISO-Prologとの関連
N-PrologはARITY/Prologの上位互換ではありますが、ISO-Prologの述語はおおむね実装してあります。また、起動時に-dオプションを追加することにより文字列はISOと同様にダブルクオート表記となります。勉強用、教材用としては十分にISO-Prologのコードを再現できます。詳細はSUPER.mdをご参照ください。


## OS
下記のOSでの動作を確認しております。

- Ubuntu
- Linux MINT
- RaspberryPI Raspbian


Windowsでお使いの場合にはWSLをお使いください。


## インストール
homeディレクトリにおいてGithubからクローンを作るか、あるいはzipファイルをダウンロードします。
linuexの端末において"sudo make install"とタイプします。

参考 https://www.youtube.com/watch?v=36vUd8ThMF0


N-Prologはncursesライブラリを必要とします。インストールしてください。

```
sudo apt update
sudo apt install libncurses-dev
```




## N-Prolog のファイルパス解決ルール

N-Prolog はファイルを読み込む際、以下のルールに従ってパスを自動的に解決します：

1. `./` や `../` で始まる **相対パス**はそのまま使われます。拡張子がなければ `.pl` が追加されます。
2. 環境変数 `NPROLOG_HOME` が定義されていれば、そのディレクトリ内を参照します。
3. `NPROLOG_HOME` が未定義で `HOME` が定義されていれば、`$HOME/nprolog/` を参照します。
4. それ以外の場合は、指定された名前をそのまま使います。拡張子がなければ `.pl` が追加されます。

いずれの場合でも、ファイル名にドット（`.`）が含まれていれば拡張子付きとみなし、`.pl` は追加されません。


## アンインストール
Linuxの端末において"sudo make uninstall"とタイプします。


# 起動
N-Prologを起動するには下記のように端末からタイプします。

```
npl


-c オプションはファイルを読み込んで起動します。

例
npl -l init.pl

-r オプションは編集可能REPLをOFFにして起動します。
指定しない場合にはREPLは編集可能となっています。
```

他のオプション

```
$ npl -h
-c filename -- NPL starts after reading the file.
-d          -- string is double quote.
-h          -- display help.
-m N        -- NPL runs with N(30>=N>=10) mega cells.
-n          -- NPL runs with network mode.
-r          -- NPL does not use editable REPL.
-s filename -- NPL runs file with script mode.
-v          -- dislplay version number.
```


## 目標
N-Prologは1980年代のDEC10-Prologを楽しむことを目標にしています。


## 実行例
```prolog
N-Prolog Ver 4.20
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

