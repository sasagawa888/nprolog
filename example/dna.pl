%DNAコードをアミノ酸の名称に変換。
%参考 「ＤＮＡの構造とはたらき」（べレ出版）

%テストデータ　
data([a,u,g,c,g,c,a,a,u,g,u,g,u,a,a]).


%変換中であるかどうかの大域変数。beginかmet（メチオニン）かの判定で必要。
:- dynamic(trans/1).
trans(off).

%RNA列をアミノ酸名に変換する。逆変換も可能。
rna_amino([],[]) :-
    abolish(trans/1),
    assert(trans(off)).

rna_amino([A,B,C|Xs],[Z|Zs]) :-
    dnaward([A,B,C],Z),
    trans(on),
    rna_amino(Xs,Zs).

rna_amino([A,B,C|Xs],[Z|Zs]) :-
    dnaward([A,B,C],Z),
    abolish(trans/1),
    assert(trans(on)),
    rna_amino(Xs,Zs).

%RNAとそれに対応するアミノ酸名
dnaward([u,u,u],phe).
dnaward([u,u,c],ala).
dnaward([u,u,a],leu).
dnaward([u,u,g],leu).
dnaward([c,u,u],leu).
dnaward([c,u,c],leu).
dnaward([c,u,a],leu).
dnaward([c,u,g],leu).
dnaward([a,u,u],ile).
dnaward([a,u,c],ile).
dnaward([a,u,a],ile).
dnaward([a,u,g],met) :- trans(on).
dnaward([a,u,g],begin).
dnaward([g,u,u],val).
dnaward([g,u,c],val).
dnaward([g,u,a],val).
dnaward([g,u,g],val).
dnaward([u,c,u],ser).
dnaward([u,c,c],ser).
dnaward([u,c,a],ser).
dnaward([u,c,g],ser).
dnaward([c,c,u],pro).
dnaward([c,c,c],pro).
dnaward([c,c,a],pro).
dnaward([c,c,g],pro).
dnaward([a,c,u],thr).
dnaward([a,c,c],thr).
dnaward([a,c,a],thr).
dnaward([a,c,g],thr).
dnaward([g,c,u],ala).
dnaward([g,c,c],ala).
dnaward([g,c,a],ala).
dnaward([g,c,g],ala).
dnaward([u,a,u],tyr).
dnaward([u,a,c],thr).
dnaward([u,a,a],end).
dnaward([u,a,g],end).
dnaward([c,a,u],his).
dnaward([c,a,c],his).
dnaward([c,a,a],gln).
dnaward([c,a,g],gln).
dnaward([a,a,u],asn).
dnaward([a,a,c],asn).
dnaward([a,a,a],lys).
dnaward([a,a,g],lys).
dnaward([g,a,u],asp).
dnaward([g,a,c],asp).
dnaward([g,a,a],glu).
dnaward([g,a,g],glu).
dnaward([u,g,u],cys).
dnaward([u,g,c],cys).
dnaward([u,g,a],end).
dnaward([u,g,g],trp).
dnaward([c,g,u],arg).
dnaward([c,g,c],arg).
dnaward([c,g,a],arg).
dnaward([c,g,g],arg).
dnaward([a,g,u],ser).
dnaward([a,g,c],ser).
dnaward([a,g,a],arg).
dnaward([a,g,g],arg).
dnaward([g,g,u],gly).
dnaward([g,g,c],gly).
dnaward([g,g,a],gly).
dnaward([g,g,g],gly).

%DNA列(１本に分けたもの）をRNA列へ変換、逆変換も可
dna_rna([],[]).
dna_rna([X|Xs],[Z|Zs]) :-
    copy_rule(X,Z),
    dna_rna(Xs,Zs).

copy_rule(a,u).
copy_rule(t,a).
copy_rule(g,c).
copy_rule(c,g).

%DNA列（１本）からペアのDNA列を生成する。
make_dna_pair([],[]).
make_dna_pair([X|Xs],[Z|Zs]) :-
    pair_rule(X,Z),
    make_dna_pair(Xs,Zs).

pair_rule(a,t).
pair_rule(t,a).
pair_rule(g,c).
pair_rule(c,g).

%DNA列（２本）をくっつけて１本の二重螺旋にする。
conjugate_dna([],[],[]).
conjugate_dna([X|Xs],[Y|Ys],[[X,Y]|Zs]) :-
    conjugate_dna(Xs,Ys,Zs).

%アミノ酸名から二重螺旋のDNA列を生成。
make_dna(X,Z) :-
    rna_amino(Z1,X),
    dna_rna(X1,Z1),
    make_dna_pair(X1,X2),
    conjugate_dna(X1,X2,Z).
