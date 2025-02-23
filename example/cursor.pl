% Cursor test code

% Clear the screen and get the current cursor position
test_ansi_cursor :-
    ansi_ed,        % Clear the screen
    ansi_scp,       % Save the current cursor position
    ansi_cuu(2),    % Move the cursor up by 2 lines
    ansi_cud(1),    % Move the cursor down by 1 line
    ansi_cuf(5),    % Move the cursor forward by 5 columns
    ansi_cub(3),    % Move the cursor back by 3 columns
    ansi_cpr(Row, Col),  % Get the current cursor position
    write('Current Cursor Position: '), 
    write(Row), write(','), write(Col), nl,
    ansi_rcp.       % Restore the saved cursor position

% Test for setting text attributes
test_ansi_sgr :-
    ansi_sgr(1),
    ansi_sgr(31),  % Set bold and red text
    write('This is bold and red text'), nl,
    ansi_sgr(0),   % Reset to default attributes
    write('This is normal text'), nl.

% Test for clearing the line
test_ansi_clear_line :-
    write('This line will be partially erased...'),
    ansi_cub(10),  % Move the cursor back by 10 columns
    ansi_el,       % Erase from the cursor to the end of the line
    write('End of test for line clear'), nl.

% Main predicate to run the tests
run_tests :-
    nl, write('Testing Cursor Movement...'), nl,
    test_ansi_cursor,
    nl, write('Testing SGR...'), nl,
    test_ansi_sgr,
    nl, write('Testing Line Clear...'), nl,
    test_ansi_clear_line.


% game
show_cursor_position :-
    ansi_cpr(Row, Col),
    write('current position:'),
    write([Row, Col]),
    nl.

game :-
    write('simple cursor game'),nl,
    write('input command（e.g.: ansi_cud(3), ansi_cuf(5), ansi_ed, halt）:'),nl,
    repeat,
    write('> '),
    read(Command),
    call(Command), 
    show_cursor_position,
    fail.
    