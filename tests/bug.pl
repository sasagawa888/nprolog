
:- use_module(list).

read_csv(File,L) :-
    read_codes(File,C),
    read_csv1(C,[],[],[],L).

%read_csv1(C,Item,Col,Row,Result)
read_csv1([],Item,Col,Row,Result) :-
    reverse(Item,Item1),
    atom_codes(A,Item1),
    reverse([A|Col],Col1),
    reverse([Col1|Row],Result).
read_csv1([44|Cs],Item,Col,Row,Result) :-
    reverse(Item,Item1),
    atom_codes(A,Item1),
    read_csv1(Cs,[],[A|Col],Row,Result).
read_csv1([13,10|Cs],Item,Col,Row,Result) :-
    reverse(Item,Item1),
    atom_codes(A,Item1),
    reverse([A|Col],Col1),
    read_csv1(Cs,[],[],[Col1|Row],Result).
read_csv1([10|Cs],Item,Col,Row,Result) :-
    reverse(Item,Item1),
    atom_codes(A,Item1),
    reverse([A|Col],Col1),
    read_csv1(Cs,[],[],[Col1|Row],Result).
read_csv1([C|Cs],Item,Col,Row,Result) :-
    read_csv1(Cs,[C|Item],Col,Row,Result).

test(X) :-
    atom_codes('abc,def\r\nghi,jkl', C),
    read_csv1(C,[],[],[],X).