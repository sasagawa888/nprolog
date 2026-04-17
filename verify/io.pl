
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

test4 :-
    open(Stream, './tests/test.txt', r),
    peek_char(Stream, Char),
    close(Stream),
    write('First character in file: '), write(Char), nl.

test5 :-
    open(Stream, './tests/test.txt', r),
    peek_code(Stream, Code),
    close(Stream),
    write('First character code in file: '), write(Code), nl.
    
test6 :-
    open(Stream, './tests/test.txt', rb),
    get_byte(Stream, Code),
    close(Stream),
    write('First byte code in file: '), write(Code), nl.

test7 :-
    open(Stream, './tests/test.txt', rb),
    peek_byte(Stream, Code),
    close(Stream),
    write('First byte code in file: '), write(Code), nl.

test8 :- 
    copy_file('./tests/test.txt', './tests/test1.txt').

copy_file(InputFile, OutputFile) :-
    open(InStream, InputFile, r),
    open(OutStream, OutputFile, w),
    copy_stream_data(InStream, OutStream),
    close(InStream),
    close(OutStream).
    
copy_stream_data(InStream, OutStream) :-
    get_char(InStream, Char),
    (   Char \= end_of_file
    ->  put_char(OutStream, Char),
        copy_stream_data(InStream, OutStream)
    ;   true
    ).
            