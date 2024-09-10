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
    recordz(client,client(hones,life,00245),Refnum),
    recordh(alphabet,jones,Rrfnum),
    recordh(insurance,life,Refnum).

test2 :-
    retrieveh(alphabet,jones,Refnum),
    instance(Refnum,X),
    write(X).
    
    