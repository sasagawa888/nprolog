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
    