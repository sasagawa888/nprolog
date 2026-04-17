

yes_or_no(X) :- 
    repeat, write('yes or no >'), read(X), (X == yes ; X == no),!.
