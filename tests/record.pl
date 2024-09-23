%example of recordz

db_load(Fname,Key) :-
    open(H,Fname,r),
    get0(H,X),
    (x == 26,
    close(H);
    gets(H,X,L),
    name(M,L),
    atom_string(M,S),
    string_term(S,T),
    recordz(Key,T,_),
    fail).

gets(_,10,_) :-!,fail.
gets(_,13,[]) :-!.
gets(H,X,[X|L]) :-
    get0(H,Z),
    gets(H,Z,L).


test1 :-
    recordz(client,client(jones,life,00245),Refnum),
    recordh(alphabet,jones,Refnum),
    recordh(insurance,life,Refnum).

test2 :-
    retrieveh(alphabet,jones,Refnum),
    instance(Refnum,X),
    write(X).

test3 :-
    recordz(foo,foo(a,1),_),
    recordz(foo,foo(b,2),_),
    recorda(foo,foo(c,3),_),
    recorda(foo,foo(d,4),_),
    recordz(foo,foo(e,5),_).

test4 :-
    key(foo,Ref),
    nref(Ref,Ref1),
    nref(Ref1,Ref2),
    nref(Ref2,Ref3),
    nref(Ref3,Ref4),
    not nref(Ref4,Ref5),
    pref(Ref4,Ref3),
    pref(Ref3,Ref2),
    pref(Ref2,Ref1),
    pref(Ref1,Ref).
    
    