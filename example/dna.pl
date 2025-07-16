%?-data(X),rna_amino(X,Y).
%X   = [a,u,g,c,g,c,a,a,u,g,u,g,u,a,a],
%Y   = [begin,arg,asn,val,end]
%yes

%?-rna_amino(X,[begin,arg,asn,val,end]).
%X   = [a,u,g,c,g,u,a,a,u,g,u,u,u,a,a]
%yes
 

%?-dna_rna([t,t,g,c,g,a,t],X).
%X   = [a,a,c,g,c,u,a]
%yes
 

%?- make_dna([arg,asn,val],X).
%X   = [[g,c],[c,g],[a,t],[t,a],[t,a],[a,t],[c,g],[a,t],[a,t]]
%yes


%Convert DNA code to amino acid name.
%test data
data([a,u,g,c,g,c,a,a,u,g,u,g,u,a,a]).

% global variable that indicates whether the conversion is in progress.
% Necessary for judging begin or met (methionine).
trans(off).

%Convert RNA sequence to amino acid name. Inverse conversion is also possible.
rna_amino([],[]) :-
    abolish(trans/1),
    assert(trans(off)).

rna_amino([A,B,C|Xs],[Z|Zs]) :-
    dnaword([A,B,C],Z),
    trans(on),
    rna_amino(Xs,Zs).

rna_amino([A,B,C|Xs],[Z|Zs]) :-
    dnaword([A,B,C],Z),
    abolish(trans/1),
    assert(trans(on)),
    rna_amino(Xs,Zs).

%RNA and its corresponding amino acid name
dnaword([u,u,u],phe).
dnaword([u,u,c],ala).
dnaword([u,u,a],leu).
dnaword([u,u,g],leu).
dnaword([c,u,u],leu).
dnaword([c,u,c],leu).
dnaword([c,u,a],leu).
dnaword([c,u,g],leu).
dnaword([a,u,u],ile).
dnaword([a,u,c],ile).
dnaword([a,u,a],ile).
dnaword([a,u,g],met) :- trans(on).
dnaword([a,u,g],begin).
dnaword([g,u,u],val).
dnaword([g,u,c],val).
dnaword([g,u,a],val).
dnaword([g,u,g],val).
dnaword([u,c,u],ser).
dnaword([u,c,c],ser).
dnaword([u,c,a],ser).
dnaword([u,c,g],ser).
dnaword([c,c,u],pro).
dnaword([c,c,c],pro).
dnaword([c,c,a],pro).
dnaword([c,c,g],pro).
dnaword([a,c,u],thr).
dnaword([a,c,c],thr).
dnaword([a,c,a],thr).
dnaword([a,c,g],thr).
dnaword([g,c,u],ala).
dnaword([g,c,c],ala).
dnaword([g,c,a],ala).
dnaword([g,c,g],ala).
dnaword([u,a,u],tyr).
dnaword([u,a,c],thr).
dnaword([u,a,a],end).
dnaword([u,a,g],end).
dnaword([c,a,u],his).
dnaword([c,a,c],his).
dnaword([c,a,a],gln).
dnaword([c,a,g],gln).
dnaword([a,a,u],asn).
dnaword([a,a,c],asn).
dnaword([a,a,a],lys).
dnaword([a,a,g],lys).
dnaword([g,a,u],asp).
dnaword([g,a,c],asp).
dnaword([g,a,a],glu).
dnaword([g,a,g],glu).
dnaword([u,g,u],cys).
dnaword([u,g,c],cys).
dnaword([u,g,a],end).
dnaword([u,g,g],trp).
dnaword([c,g,u],arg).
dnaword([c,g,c],arg).
dnaword([c,g,a],arg).
dnaword([c,g,g],arg).
dnaword([a,g,u],ser).
dnaword([a,g,c],ser).
dnaword([a,g,a],arg).
dnaword([a,g,g],arg).
dnaword([g,g,u],gly).
dnaword([g,g,c],gly).
dnaword([g,g,a],gly).
dnaword([g,g,g],gly).

%Convert DNA sequence (divided into one) to RNA sequence, reverse conversion possible
dna_rna([],[]).
dna_rna([X|Xs],[Z|Zs]) :-
    copy_rule(X,Z),
    dna_rna(Xs,Zs).

copy_rule(a,u).
copy_rule(t,a).
copy_rule(g,c).
copy_rule(c,g).

%A pair of DNA strings is generated from one DNA string.
make_dna_pair([],[]).
make_dna_pair([X|Xs],[Z|Zs]) :-
    pair_rule(X,Z),
    make_dna_pair(Xs,Zs).

pair_rule(a,t).
pair_rule(t,a).
pair_rule(g,c).
pair_rule(c,g).

%Attach two DNA strands into one double helix
conjugate_dna([],[],[]).
conjugate_dna([X|Xs],[Y|Ys],[[X,Y]|Zs]) :-
    conjugate_dna(Xs,Ys,Zs).

%Generate double helix DNA sequence from amino acid name.
make_dna(X,Z) :-
    rna_amino(Z1,X),
    dna_rna(X1,Z1),
    make_dna_pair(X1,X2),
    conjugate_dna(X1,X2,Z).
