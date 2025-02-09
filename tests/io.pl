
test1 :-
    write('Enter a character: '),
    flush_output,
    get_char(Char),
    nl,
    write('You entered: '), write(Char), nl.

test2 :-
    open(Stream, './tests/test.txt', r),
    get_char(Stream, Char),
    close(Stream),
    write('First character in file: '), write(Char), nl.

test3 :-
    open(Stream, './tests/test.txt', r),
    get_code(Stream, Code),
    close(Stream),
    write('First character code in file: '), write(Code), nl.