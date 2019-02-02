%
:- module(json).
:- export([json_read/1,json_read/2,json_write/1,json_write/2,read_csv/2,csv_json/2,json_csv/2]).
:- end_module(json).

:- body(json).
:- set_prolog_flag(double_quotes,string).

json_read(X) :-
    read_item(Y),
    json_decode(Y,X).
json_read(S,X) :-
    read_item(S,Y),
    json_decode(Y,X).

json_decode(null,null).
json_decode(true,true).
json_decode(A:B,A1=B1) :-
    json_decode(A,A1),
    json_decode(B,B1).
json_decode({A:B},json([A1=B1])) :-
    json_decode(A,A1),
    json_decode(B,B1).
json_decode({(A:B),C},json([A1=B1|R])) :-
    json_decode(A,A1),
    json_decode(B,B1),
    json_decode_obj(C,R).
json_decode(X,X) :-
    list(X).
json_decode(X,X) :-
    number(X).
json_decode(X,Z) :-
    string(X),
    string_codes(X,Y),
    atom_codes(Z,Y).

json_decode_obj(A:B,[A1=B1]) :-
    json_decode(A,A1),
    json_decode(B,B1).
json_decode_obj((A,B),[A1|B1]) :-
    json_decode(A,A1),
    json_decode_obj(B,B1).


%----------------
json_write(X) :-
    json_encode(X,Y),
    write(Y).
json_write(S,X) :-
    json_encode(X,Y),
    write(S,Y).

json_encode(null,null).
json_encode(true,true).
json_encode(X,X) :-
    number(X).
json_encode(X,X) :-
    list(X).
json_encode(X,Y) :-
    atom(X),
    atom_chars(X,X1),
    string_chars(Y,X1).
json_encode(json(X),Y) :-
    functor(Y,'{}',1),
    json_encode_obj(X,Z),
    Y='{}'(Z).

json_encode_obj([A=B],A1:B1) :-
    json_encode(A,A1),
    json_encode(B,B1).
json_encode_obj([A=B|C],(A1:B1,C1)) :-
    json_encode(A,A1),
    json_encode(B,B1),
    json_encode_obj(C,C1).

%---------------csv -----------
%csv <=>JSON
csv_json([T|D],A) :-
    csv_json1(T,D,[],A).
csv_json1(T,[],P,A) :-
    reverse(P,A).
csv_json1(T,[D|Ds],P,A) :-
    T =.. [_|T1],
    D =.. [_|D1],
    csv_json2(T1,D1,[],L),
    P1 =.. [json|L],
    csv_json1(T,Ds,[P1|P],A).
csv_json2([],_,L,A) :-
    reverse(L,A).
csv_json2([T|Ts],[D|Ds],L,A) :-
    csv_json2(Ts,Ds,[T=D|L],A).

json_csv([J|Js],A) :-
    J =.. [_,T],
    json_csv1(T,Js,[],A).
json_csv1(T,[],P,[P1|A]) :-
    reverse(P,A),
    json_csv3(T,L),
    P1 =.. [csv|L].
json_csv1(T,[J|Js],P,A) :-
    J =.. [_,D],
    json_csv2(D,L),
    P1 =.. [csv|L],
    json_csv1(T,Js,[P1|P],A).
json_csv2([X=Y],[Y]).
json_csv2([X=Y|Ds],[Y|A]) :-
    json_csv2(Ds,A).
json_csv3([X=Y],[X]).
json_csv3([X=Y|Ds],[X|A]) :-
    json_csv3(Ds,A).



read_csv(S,X) :-
    read_csv1(S,end_of_line,[],[],X).

read_csv1(S,end_of_file,L,P,A) :-
    reverse(P,A).
read_csv1(S,',',L,P,A) :-
    read_item(S,X),
    read_csv1(S,X,[X|L],P,A).
read_csv1(S,end_of_line,L,P,A) :-
    read_item(S,X),
    (X=',' -> read_csv1(S,X,L,P,A) ; read_csv1(S,X,[X|L],P,A)).
read_csv1(S,B,L,P,A) :-
    read_item(S,X),
    (X=','->
       read_csv1(S,X,L,P,A);
       (X=end_of_file ->
          (reverse(L,L1),P1 =.. [csv|L1],read_csv1(S,X,[],[P1|P],A));
          (reverse(L,L1),P1 =.. [csv|L1],read_csv1(S,end_of_line,[X],[P1|P],A)))).



:- end_body(json).
