
    
change_extension(File, NewExt, NewFile) :-
    atom_codes(File, Codes),
    change_extension1(Codes,BaseCodes),
    atom_codes(BaseAtom, BaseCodes),
    atom_concat(BaseAtom, '.', Temp),
    atom_concat(Temp, NewExt, NewFile).

change_extension1([],[]).
change_extension1([46|_],[]).
change_extension1([C|Cs],[C|Bs]) :-
        change_extension1(Cs,Bs).

    
    