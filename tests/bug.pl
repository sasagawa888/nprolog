
read_csv(File,L) :-
    read_codes(File,C),
    read_csv1(C,L).

read_csv1([])
    