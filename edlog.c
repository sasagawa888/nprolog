#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <ctype.h>

#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED
#define NCURSES_OPAQUE 1
#ifdef __linux__
#include <ncurses.h>
#else
#include <curses.h>
#endif
#undef _XOPEN_SOURCE
#undef _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <term.h>
#include "compat/cdefs.h"
#include "edlog.h"




#ifndef CTRL
#define CTRL(X) ((X) & 0x1F)
#endif

#define NUM_STR_MAX 5
#define SHORT_STR_MAX 30

volatile sig_atomic_t ctrl_c = 0;
volatile sig_atomic_t ctrl_z = 0;

FILE *port;
char fname[256];		// file name 
bool cancel_flag;		// for CTRL+G 

// -----editor-----
int ed_scroll;
int ed_footer;
int ed_middle;
int ed_row;
int ed_col;			//position of buffer
int ed_col1;			//position of terminal when include unicode ed_col1 is different from ed_col
int ed_start;
int ed_end;
bool ed_ins = true;
int ed_tab = 0;
int ed_indent = 1;
char ed_data[ROW_SIZE][COL_SIZE];
char ed_copy[COPY_SIZE][COL_SIZE];
int ed_lparen_row = -1;
int ed_lparen_col;
int ed_rparen_row = -1;
int ed_rparen_col;
int ed_lbracket_row = -1;
int ed_lbracket_col;
int ed_rbracket_row = -1;
int ed_rbracket_col;
int ed_clip_start;
int ed_clip_end;
int ed_copy_end;
const char *ed_candidate[COMPLETION_CANDIDATES_MAX];
int ed_candidate_pt;
const enum Color ed_syntax_color = RED_ON_DFL;
const enum Color ed_builtin_color = CYAN_ON_DFL;
const enum Color ed_extended_color = MAGENTA_ON_DFL;
const enum Color ed_string_color = YELLOW_ON_DFL;
const enum Color ed_comment_color = BLUE_ON_DFL;
const enum Color ed_function_color = GREEN_ON_DFL;
int ed_incomment = -1;		// #|...|# comment
bool modify_flag;

/*  buffer data structure   text is "abc" at first row
 *  0,1,2,3,4,5...255 
 * [a,b,c,EOL,0,0,0,....,0]
*/

int main(int argc, char *argv[])
{
    int i, j;

    /* to enable CTRL('S') */
    if (system("stty -ixon") == -1) {
	printf("terminal error\n");
	return (0);
    }

    setlocale(LC_ALL, "");
    if (argc == 2)
	strcpy(fname, argv[1]);

    signal(SIGINT, signal_handler_c);
    signal(SIGSTOP, signal_handler_z);
    signal(SIGTSTP, signal_handler_z);
    for (i = 0; i < ROW_SIZE; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = 0;
	}
    }

    load_data(fname);
    init_ncurses();
    ed_scroll = LINES - 3;
    ed_footer = LINES;
    ed_middle = LINES / 2;
    ESCCLS();
    display_header();
    display_screen();
    ed_row = ed_col = ed_col1 = 0;
    edit_screen();
    CHECK(endwin);
    /* restore CTRL('S') */
    if (system("stty ixon") == -1) {
	printf("terminal error\n");
    }
}

int getch1(void)
{
    int c;

  retry:
    timeout(0);
    c = getch();
    timeout(-1);
    if (ctrl_c == 1) {
	ctrl_c = 0;
	return (CTRL('C'));
    } else if (ctrl_z == 1) {
	ctrl_z = 0;
	return (CTRL('Z'));
    }

    if (c == ERR) {
	goto retry;
    }
    return (c);
}

__dead void errw(const char *msg)
{
    endwin();
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void clear_status()
{
    int i;
    ESCREV();
    ESCMOVE(ed_footer, 1);
    for (i = 0; i < COLS - 9; i++)
	CHECK(addstr, " ");
    ESCMOVE(ed_footer, 1);
}

void restore_cursol()
{
    if (ed_col1 < COLS - LEFT_MARGIN)
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
    else
	ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		ed_col1 - (COLS - LEFT_MARGIN) + LEFT_MARGIN);
}

void init_ncurses()
{
    if (initscr() == NULL) {
	fputs("initscr\n", stderr);
	exit(EXIT_FAILURE);
    }
    if (has_colors()) {
	CHECK(start_color);
#ifdef NCURSES_VERSION
	CHECK(use_default_colors);
#endif
    }
    CHECK(scrollok, stdscr, TRUE);
    CHECK(idlok, stdscr, TRUE);
    CHECK(noecho);
    CHECK(keypad, stdscr, TRUE);
    CHECK(cbreak);
    CHECK(nonl);
    CHECK(intrflush, NULL, FALSE);
    curs_set(1);
#ifdef NCURSES_VERSION
    set_tabsize(8);
#endif

    if (has_colors()) {
	// Colors
	CHECK(init_pair, RED_ON_DFL, COLOR_RED, -1);
	CHECK(init_pair, YELLOW_ON_DFL, COLOR_YELLOW, -1);
	CHECK(init_pair, BLUE_ON_DFL, COLOR_BLUE, -1);
	CHECK(init_pair, MAGENTA_ON_DFL, COLOR_MAGENTA, -1);
	CHECK(init_pair, CYAN_ON_DFL, COLOR_CYAN, -1);
	CHECK(init_pair, DFL_ON_CYAN, -1, COLOR_CYAN);
	CHECK(init_pair, GREEN_ON_DFL, COLOR_GREEN, -1);
    }
}

void signal_handler_c(int signo __unused)
{
    ctrl_c = 1;
}

void signal_handler_z(int signo __unused)
{
    ctrl_z = 1;
}


// transform from UTF-8 to unicode
int utf8_to_ucs4(int row, int col)
{
    int x, x1, x2, x3, res;
    unsigned char uc;

    uc = (unsigned char) ed_data[row][col];
    if (uc <= 0x7f) {
	x = (int) uc;
	return (x);
    } else if (uc >= 0xc0 && uc <= 0xdf) {
	x = (int) (UTF2MSK1 & uc);
	x = x << 6;
	uc = (unsigned char) ed_data[row][col + 1];
	x1 = (int) (UTFOMSKO & uc);
	res = x | x1;
	return (res);
    } else if (uc >= 0xe0 && uc <= 0xef) {
	x = (int) (UTF3MSK1 & uc);
	x = x << 12;
	uc = (unsigned char) ed_data[row][col + 1];
	x1 = (int) (UTFOMSKO & uc);
	x1 = x1 << 6;
	uc = (unsigned char) ed_data[row][col + 2];
	x2 = (int) (UTFOMSKO & uc);
	res = x | x1 | x2;
	return (res);
    } else if (uc >= 0xf0 && uc <= 0xf7) {
	x = (int) (UTF4MSK1 & uc);
	x = x << 18;
	uc = (unsigned char) ed_data[row][col + 1];
	x1 = (int) (UTFOMSKO & uc);
	x1 = x1 << 12;
	uc = (unsigned char) ed_data[row][col + 2];
	x2 = (int) (UTFOMSKO & uc);
	x2 = x2 << 6;
	uc = (unsigned char) ed_data[row][col + 3];
	x3 = (int) (UTFOMSKO & uc);
	res = x | x1 | x2 | x3;
	return (res);
    } else
	return (-1);
}


bool is_word_char(char x)
{
    if (isalpha(x))
	return true;
    else if (isUni2(x))
	return true;
    else if (isUni3(x))
	return true;
    else if (isUni4(x))
	return true;

    return false;
}


// calculate buffer position to increase according to UTF8 unicode
int increase_buffer(int row, int col)
{
    int uc;

    uc = ed_data[row][col];
    if (isUni1(uc))
	return (1);
    else if (isUni2(uc))
	return (2);
    else if (isUni3(uc))
	return (3);
    else if (isUni4(uc))
	return (4);
    else
	return (-1);
}

// calculate terminal position to increase according to UTF8 unicode
int increase_terminal(int row, int col)
{
    int unicode;

    if (isUni3(ed_data[row][col])) {
	unicode = utf8_to_ucs4(row, col);
	// tai
	if (unicode >= 0x0e00 && unicode <= 0x0e7f)
	    return (1);
	// arabian
	else if (unicode >= 0x0600 && unicode <= 0x06ff)
	    return (1);
	// tamil
	else if (unicode >= 0xb80 && unicode <= 0xbff)
	    return (1);
	else
	    return (2);
    } else
	return (1);
}

// calculate buffer position to decrease according to UTF8 unicode
int decrease_buffer(int row, int col)
{

    if (isUni1(ed_data[row][col]))
	return (1);
    else if (isUni2(ed_data[row][col - 1]))
	return (2);
    else if (isUni3(ed_data[row][col - 2]))
	return (3);
    else if (isUni4(ed_data[row][col - 3]))
	return (4);
    else
	return (1);
}

// calculate terminal position to decrease according to UTF8 unicode
int decrease_terminal(int row, int col)
{
    int unicode;

    if (isUni3(ed_data[row][col - 2])) {
	unicode = utf8_to_ucs4(row, col - 2);
	//tai
	if (unicode >= 0x0e00 && unicode <= 0x0e7f)
	    return (1);
	// arabian
	else if (unicode >= 0x0600 && unicode <= 0x06ff)
	    return (1);
	// tamil
	else if (unicode >= 0xb80 && unicode <= 0xbff)
	    return (1);
	else
	    return (2);
    } else
	return (1);
}

// re calculate buffer position and terminal position at row
void recalculate_col(int row, int oldcol1)
{
    int new_col, new_col1;

    new_col = 0;
    new_col1 = 0;
    while (new_col < COL_SIZE) {
	if (new_col1 == oldcol1) {
	    break;
	} else if (ed_data[row][new_col] == EOL) {
	    break;
	} else if (ed_data[row][new_col] == 0) {
	    break;
	}
	new_col1 = new_col1 + increase_terminal(row, new_col);
	new_col = new_col + increase_buffer(row, new_col);
    }
    ed_col = new_col;
    ed_col1 = new_col1;
}


//---------------cursol control------------------------------

void right()
{
    int turn, new_col, new_col1;
    turn = COLS - LEFT_MARGIN;
    if (ed_col == find_eol(ed_row) || ed_col >= COL_SIZE)
	return;

    new_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
    new_col = ed_col + increase_buffer(ed_row, ed_col);

    if (ed_col1 < turn && new_col1 >= turn) {
	restore_paren();
	restore_bracket();
	ed_col = new_col;
	ed_col1 = new_col1;
	display_screen();
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
    } else {
	restore_paren();
	restore_bracket();
	ed_col = new_col;
	ed_col1 = new_col1;
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
    }
    restore_cursol();
}



void left()
{
    int turn, new_col, new_col1;
    turn = COLS - LEFT_MARGIN;
    if (ed_col1 == 0)
	return;

    new_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
    new_col = ed_col - decrease_buffer(ed_row, ed_col - 1);

    if (ed_col1 >= turn && new_col1 < turn) {
	ed_col = new_col;
	ed_col1 = new_col1;
	display_screen();
    } else {
	ed_col = new_col;
	ed_col1 = new_col1;
    }
    restore_paren();
    restore_bracket();
    emphasis_lparen();
    emphasis_rparen();
    emphasis_lbracket();
    emphasis_rbracket();
    restore_cursol();
}

void up()
{
    int turn, oldcol1;
    turn = COLS - LEFT_MARGIN;

    if (ed_row == 0)
	return;
    else if (ed_clip_start != -1 && ed_row == ed_start) {
	if (ed_row == ed_clip_start)
	    ed_clip_start--;
	else
	    ed_clip_end--;
	ed_row--;
	ed_start--;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    } else if (ed_row == ed_start) {
	ed_row = ed_row - ed_middle;
	ed_start = ed_start - ed_middle;
	if (ed_row < 0)
	    ed_row = ed_start = 0;
	recalculate_col(ed_row, ed_col1);
	display_screen();
	restore_paren();
	restore_bracket();
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	ESCMOVE(2, ed_col1 + LEFT_MARGIN);
    } else if (ed_clip_start != -1) {
	if (ed_row == ed_clip_start)
	    ed_clip_start--;
	else
	    ed_clip_end--;
	ed_row--;
	recalculate_col(ed_row, ed_col1);
	display_screen();
	restore_paren();
	restore_bracket();
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	restore_cursol();
    } else {
	restore_paren();
	restore_bracket();
	ed_row--;
	oldcol1 = ed_col1;
	recalculate_col(ed_row, ed_col1);
	if ((ed_col1 >= turn && oldcol1 < turn) ||
	    (ed_col1 < turn && oldcol1 >= turn)) {
	    display_screen();
	}
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	restore_cursol();
    }
}

void down()
{
    int turn, oldcol1;
    turn = COLS - LEFT_MARGIN;

    if (ed_row == ed_end)
	return;
    else if (ed_clip_start != -1 && ed_row == ed_start + ed_scroll) {
	if (ed_row == ed_clip_end)
	    ed_clip_end++;
	else
	    ed_clip_start++;
	ed_row++;
	ed_start++;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    } else if (ed_row == ed_start + ed_scroll) {
	ed_row = ed_row + ed_middle;
	ed_start = ed_start + ed_middle;
	if (ed_row > ed_end)
	    ed_row = ed_start = ed_end - ed_scroll;
	display_screen();
	restore_paren();
	restore_bracket();
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	recalculate_col(ed_row, ed_col1);
	ESCMOVE(ed_footer - 1, ed_col1 + LEFT_MARGIN);
    } else if (ed_clip_start != -1) {
	if (ed_row == ed_clip_end)
	    ed_clip_end++;
	else
	    ed_clip_start++;
	ed_row++;
	recalculate_col(ed_row, ed_col1);
	display_screen();
	restore_paren();
	restore_bracket();
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	recalculate_col(ed_row, ed_col1);
	restore_cursol();
    } else {
	restore_paren();
	restore_bracket();
	ed_row++;
	oldcol1 = ed_col1;
	recalculate_col(ed_row, ed_col1);
	if ((ed_col1 >= turn && oldcol1 < turn) ||
	    (ed_col1 < turn && oldcol1 >= turn)) {
	    display_screen();
	}
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	restore_cursol();
    }
}

void return_key()
{
    int i;

    if (ed_row == ed_start + ed_scroll) {
	restore_paren();
	restore_bracket();
	insert_row();
	ed_start++;
	ed_row++;
	ed_end++;
	ed_col = ed_col1 = 0;
	display_screen();
	ESCMOVE(ed_footer, LEFT_MARGIN);
    } else if (ed_col >= COLS) {
	restore_paren();
	restore_bracket();
	insert_row();
	ed_start++;
	ed_row++;
	ed_end++;
	ed_col = ed_col1 = 0;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    } else {
	restore_paren();
	restore_bracket();
	insert_row();
	ed_row++;
	ed_end++;
	ed_col = ed_col1 = 0;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    }
    if (ed_indent) {
	ed_col = ed_col1 = 0;
	remove_headspace(ed_row);
	i = calc_tabs();
	softtabs(i);
	display_screen();
	restore_cursol();
    }
    modify_flag = true;
}


void tab_key()
{
    int i;

    if (ed_tab == 0) {
	ed_col = ed_col1 = 0;
	i = calc_tabs();
	remove_headspace(ed_row);
	softtabs(i);
    } else {
	softtabs(ed_tab);
    }
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void backspace_key(void)
{

    if (ed_row == 0 && ed_col == 0)
	return;
    else if (ed_col == 0) {
	restore_paren();
	restore_bracket();
	delete_row();
	if (ed_row < ed_start) {
	    ed_start = ed_row;
	}
	display_screen();
    } else {
	backspace();
	ESCCLSLA();
	restore_paren();
	restore_bracket();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
    }
    restore_cursol();
    modify_flag = true;
}

void del(void)
{

    if (ed_data[ed_row][ed_col] == EOL)
	return;
    delete_char();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void line_begin()
{
    int turn;
    turn = COLS - LEFT_MARGIN;

    if (ed_col1 < turn) {
	ed_col = ed_col1 = 0;
    } else {
	ed_col = ed_col1 = 0;
	ESCCLSLA();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
    }
    restore_cursol();
}

void line_end()
{
    int turn, i;
    turn = COLS - LEFT_MARGIN;

    for (i = 0; i < COL_SIZE; i++) {
	if (ed_data[ed_row][i] == NUL)
	    break;
    }

    if (ed_col1 < turn && i < turn) {
	ed_col = ed_col1 = i - 1;
    } else {
	ed_col = ed_col1 = i - 1;
	ESCCLSLA();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
    }
    restore_cursol();
}


void sexp_next()
{
    int old_row, old_col, old_col1;
    struct position pos;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;


    /* skip space comment */
    while (1) {
	if (ed_data[ed_row][ed_col] == ' ') {
	    ed_col1++;
	    ed_col++;
	} else if (ed_data[ed_row][ed_col] == ')') {
	    ed_col1++;
	    ed_col++;
	} else if (ed_data[ed_row][ed_col] == ';') {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    goto skip;
	} else {
	    break;
	}
    }

    if (ed_data[ed_row][ed_col] == '(') {	/* list */
	pos = find_rparen(1);
	if (pos.row != -1) {
	    ed_row = pos.row;
	    ed_col = ed_col1 = pos.col + 1;
	}
    } else {			/* atom */
	while (ed_data[ed_row][ed_col] != ' ' &&
	       ed_data[ed_row][ed_col] != '(' &&
	       ed_data[ed_row][ed_col] != ')' &&
	       ed_data[ed_row][ed_col] != EOL) {
	    ed_col++;
	    ed_col1++;
	}
    }

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void word_next()
{
    int old_row, old_col, old_col1;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;
    // skip word char 
    if (is_word_char(ed_data[ed_row][ed_col])) {
	while (is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
	    ed_col = ed_col + increase_buffer(ed_row, ed_col);
	}
    }
    // skip space 
    while (1) {
	if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    goto skip;
	} else if (!is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1++;
	    ed_col++;
	} else {
	    break;
	}
    }

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void list_next()
{
    int old_row, old_col, old_col1;
    struct position pos;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;
    /* skip space comment */
    while (1) {
	if (ed_data[ed_row][ed_col] == '(') {
	    break;
	} else if (ed_data[ed_row][ed_col] == ';') {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    goto skip;
	} else {
	    ed_col++;
	    ed_col1++;
	}
    }

    pos = find_rparen(1);
    if (pos.row != -1) {
	ed_row = pos.row;
	ed_col = ed_col1 = pos.col + 1;
    }

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}

void list_down()
{
    int old_row, old_col, old_col1;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;

    /* skip space comment */
    while (1) {
	if (ed_data[ed_row][ed_col] == '(') {
	    break;
	} else if (ed_data[ed_row][ed_col] == ')') {
	    ESCREV();
	    ESCMOVE(ed_footer, 1);
	    clear_status();
	    ESCMOVE(ed_footer, 1);
	    CHECK(addstr, "Can't find");
	    ESCRST();
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    return;
	} else if (ed_data[ed_row][ed_col] == ';') {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    goto skip;
	} else {
	    ed_col++;
	    ed_col1++;
	}
    }

    ed_col++;
    ed_col1++;

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void sexp_prev()
{
    struct position pos;

    /* skip atom */
    if (ed_data[ed_row][ed_col] != ' ' &&
	ed_data[ed_row][ed_col] != '(' && ed_data[ed_row][ed_col] != ')') {
	while (ed_data[ed_row][ed_col] != ' ' &&
	       ed_data[ed_row][ed_col] != '(' &&
	       ed_data[ed_row][ed_col] != ')' && ed_col != 0) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
    }

    if (ed_data[ed_row][ed_col] == '(' && ed_col == 0) {
	goto skip;
    }

    /* skip space */
    while (1) {
	if (ed_col > 0 && ed_data[ed_row][ed_col] == ' ') {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == EOL) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == '(') {
	    ed_col1--;
	    ed_col--;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (ed_data[ed_row][ed_col] == ' ' ||
		    ed_data[ed_row][ed_col] == '(' ||
		    ed_data[ed_row][ed_col] == EOL)) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	} else {
	    break;
	}
    }

    if (ed_data[ed_row][ed_col] == ')' &&
	ed_data[ed_row][ed_col - 1] == ')') {
	ed_col--;
    }

    if (ed_data[ed_row][ed_col] == ')') {
	pos = find_lparen(1);
	if (pos.row != -1) {
	    ed_row = pos.row;
	    ed_col = ed_col1 = pos.col;
	}
    } else {
	while (ed_data[ed_row][ed_col] != ' ' &&
	       ed_data[ed_row][ed_col] != '(' &&
	       ed_data[ed_row][ed_col] != ')' && ed_col != 0) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
	ed_col1++;
	ed_col++;
    }

  skip:
    if (ed_row < ed_start) {
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0)
	    ed_start = 0;
    }
    display_screen();
    restore_cursol();
}


void word_prev()
{
    if (ed_row == 0 && ed_col == 0) {
	clear_status();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	return;
    }
    // skip word char 
    if (is_word_char(ed_data[ed_row][ed_col])) {
	while (is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
    }
    // skip space 
    while (1) {
	if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (!is_word_char(ed_data[ed_row][ed_col]))) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_col > 0 && !is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	} else {
	    break;
	}
    }

    // skip word char 
    if (is_word_char(ed_data[ed_row][ed_col])) {
	while (is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
    }

    ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
    ed_col = ed_col + increase_buffer(ed_row, ed_col);

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void list_prev()
{
    struct position pos;

    /* skip space */
    while (1) {
	if (ed_data[ed_row][ed_col] == ')') {
	    break;
	} else if (ed_col > 0) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == EOL) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (ed_data[ed_row][ed_col] == ' ' ||
		    ed_data[ed_row][ed_col] == '(' ||
		    ed_data[ed_row][ed_col] == EOL)) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	}
    }

    pos = find_lparen(1);
    if (pos.row != -1) {
	ed_row = pos.row;
	ed_col = ed_col1 = pos.col;
    }

  skip:
    if (ed_row < ed_start) {
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0)
	    ed_start = 0;
    }
    display_screen();
    restore_cursol();
}

void list_up()
{
    int old_row, old_col, old_col1;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;
    if (ed_col > 0 && ed_data[ed_row][ed_col] == '(') {
	ed_col--;
	ed_col1--;
    }

    /* skip space */
    while (1) {
	if (ed_data[ed_row][ed_col] == '(') {
	    break;
	} else if (ed_data[ed_row][ed_col] == ')') {
	    ESCREV();
	    ESCMOVE(ed_footer, 1);
	    clear_status();
	    ESCMOVE(ed_footer, 1);
	    CHECK(addstr, "Can't find");
	    ESCRST();
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    return;
	} else if (ed_col > 0) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == EOL) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (ed_data[ed_row][ed_col] == ' ' ||
		    ed_data[ed_row][ed_col] == EOL)) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	}
    }


  skip:
    if (ed_row < ed_start) {
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0)
	    ed_start = 0;
    }
    display_screen();
    restore_cursol();
}

void redisplay_screen()
{
    ed_start = ed_row - ed_scroll / 2;
    if (ed_start < 0)
	ed_start = 0;

    display_screen();
    restore_cursol();
}

//-----------cut and paste-------------------------------
void cut_line()
{
    ed_clip_start = ed_clip_end = ed_row;
    copy_selection();
    delete_selection();
    ed_row = ed_clip_start;
    ed_clip_start = ed_clip_end = -1;
    restore_paren();
    restore_bracket();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void mark_unmark(void)
{
    if (ed_clip_start == -1) {
	ed_clip_start = ed_clip_end = ed_row;
	ESCMOVE(ed_footer, 1);
	ESCREV();
	CHECK(addstr, "marked");
	ESCRST();
	restore_cursol();
	return;
    } else {
	ed_clip_start = ed_clip_end = -1;
	display_screen();
	ESCMOVE(ed_footer, 1);
	ESCREV();
	CHECK(addstr, "unmark");
	ESCRST();
	restore_cursol();
	return;
    }
}

void cut_selection()
{
    copy_selection();
    delete_selection();
    restore_paren();
    restore_bracket();
    ed_start = ed_clip_start - ed_scroll / 2;
    if (ed_start < 0)
	ed_start = 0;
    ed_row = ed_clip_start - 1;
    if (ed_row < 0)
	ed_row = 0;
    ed_col = 0;
    ed_clip_start = ed_clip_end = -1;
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void uncut_selection()
{
    paste_selection();
    restore_paren();
    restore_bracket();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void save_selection()
{
    copy_selection();
    ed_row = ed_clip_start;
    ed_clip_start = ed_clip_end = -1;
    restore_paren();
    restore_bracket();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

//-----------------command----------------------------

char *replace_tilde(char *fname)
{
    if (fname[0] == '~') {
	static char fname1[256];
	char *home = getenv("HOME");
	if (home == NULL)
	    return "";
	else {
	    strcpy(fname1, home);
	    strcat(fname1, fname + 1);
	    return fname1;
	}
    } else {
	return fname;
    }
}

bool quit_with_save(void)
{
    int c;
    if (!modify_flag) {
	ESCCLS();
	ESCMOVE(1, 1);
	return true;
    } else {
	do {
	    ESCREV();
	    ESCMOVE(ed_footer, 1);
	    CHECK(addstr, "save modified buffer? Yes/No ");
	    CHECK(refresh);
	    c = getch();
	    if (c == ERR) {
		errw("getch");
	    }
	    ESCRST();
	    switch (c) {
	    case 'y':
		if (strcmp(fname, "") != 0) {
		    save_data(fname);
		} else {
		    save_file_as();
		}
		ESCCLS();
		ESCMOVE(1, 1);
		return true;
		break;
	    case 'n':
		ESCCLS();
		ESCMOVE(1, 1);
		return true;
		break;
	    case CTRL('G'):
		clear_status();
		ESCRST();
		restore_cursol();
		ctrl_c = 0;
		return false;
		break;
	    }
	}
	while (c != 'y' && c != 'n');
    }
    return false;
}

void save_file()
{
    if (strcmp(fname, "") == 0) {
	ESCMOVE(ed_footer, 1);
	clear_status();
	CHECK(addstr, "filename:  ");
	strcpy(fname, replace_tilde(getname()));
	if (cancel_flag) {
	    cancel_flag = 0;
	    clear_status();
	    ESCRST();
	    restore_cursol();
	    return;
	}
    }
    save_data(fname);
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    ESCMOVE(ed_footer, 1);
    CHECK(addstr, "saved ");
    CHECK(addstr, fname);
    ESCRST();
    restore_cursol();
    modify_flag = false;
}


void save_file_as()
{
    char str1[SHORT_STR_MAX];

    ESCMOVE(ed_footer, 1);
    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(str1, replace_tilde(getname()));
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    save_data(str1);
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    ESCMOVE(ed_footer, 1);
    CHECK(addstr, "saved ");
    CHECK(addstr, str1);
    ESCRST();
    restore_cursol();
    modify_flag = false;
}

void save_region()
{
    char str1[SHORT_STR_MAX];

    ESCMOVE(ed_footer, 1);
    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(str1, getname());
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    copy_selection();
    save_copy(str1);
    ed_copy_end = 0;
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    ESCMOVE(ed_footer, 1);
    CHECK(addstr, "saved ");
    CHECK(addstr, str1);
    ESCRST();
    restore_cursol();
}

void insert_file()
{
    char str1[SHORT_STR_MAX];
    int c, row, col;

    /* clear copy buffer */
    for (row = 0; row < COPY_SIZE; row++) {
	for (col = 0; col < COL_SIZE; col++) {
	    ed_copy[row][col] = 0;
	}
    }


    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(str1, getname());
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    ESCRST();
    port = fopen(str1, "r");
    if (port == NULL) {
	clear_status();
	CHECK(addstr, str1);
	CHECK(addstr, " doesn't exist");
	ESCRST();
	restore_cursol();
	return;
    }

    /* load file to copy buffer */
    row = col = 0;
    c = fgetc(port);
    while (c != EOF) {
	ed_copy[row][col] = c;
	if (c == EOL) {
	    row++;
	    col = 0;
	    if (row >= COPY_SIZE - 1) {
		CHECK(printw, "row %d over max-row", row);
	    }
	} else {
	    col++;
	    if (col >= COL_SIZE) {
		CHECK(printw, "column %d over max-column", col);
	    }
	}
	c = fgetc(port);
    }
    /* if get EOF without EOL 
     *  this is a pen[EOF] -> this is a pen[EOL]
     */
    if (col != 0) {
	ed_copy[ed_row][ed_col] = EOL;
	row++;
    }
    ed_copy_end = row;
    ed_copy[ed_copy_end][0] = EOL;
    fclose(port);

    /* paste copy buffer to main buffer */
    paste_selection();
    ed_copy_end = 0;
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void load_file()
{
    int i, j;

    for (i = 0; i < ROW_SIZE; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = 0;
	}
    }

    ESCMOVE(ed_footer, 1);
    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(fname, replace_tilde(getname()));
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    load_data(fname);
    ESCCLS();
    display_header();
    display_screen();
    ESCMOVE(ed_footer, 1);
    ESCREV();
    CHECK(addstr, "loaded ");
    CHECK(addstr, fname);
    ESCRST();
    ed_row = ed_col = ed_col1 = 0;
    restore_cursol();
    modify_flag = false;

}


//--------------searck word-------------------------------------

void search_next()
{
    char str1[SHORT_STR_MAX];
    struct position pos;

    clear_status();
    CHECK(addstr, "search:    ");
    strcpy(str1, getword1());
    ESCRST();
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    pos = find_word(str1);
    if (pos.row == -1) {
	ESCREV();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "can't find ");
	CHECK(addstr, str1);
	ESCRST();
	restore_cursol();
	return;
    }
    ed_row = pos.row;
    ed_col = ed_col1 = pos.col;
    ed_start = ed_row - ed_scroll / 2;
    if (ed_start < 0) {
	ed_start = 0;
    }
    display_screen();
    restore_cursol();
    ESCREV();
    CHECK(addstr, str1);
    ESCRST();
}

void search_prev()
{
    char str1[SHORT_STR_MAX];
    struct position pos;

    clear_status();
    CHECK(addstr, "search:    ");
    strcpy(str1, getword1());
    ESCRST();
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    pos = find_word_back(str1);
    if (pos.row == -1) {
	ESCREV();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "can't find ");
	CHECK(addstr, str1);
	ESCRST();
	restore_cursol();
	return;
    }
    ed_row = pos.row;
    ed_col = ed_col1 = pos.col;
    ed_start = ed_row - ed_scroll / 2;
    if (ed_start < 0) {
	ed_start = 0;
    }
    display_screen();
    restore_cursol();
    ESCREV();
    CHECK(addstr, str1);
    ESCRST();
}


void transfer_word()
{
    int c;
    char str1[SHORT_STR_MAX], str2[SHORT_STR_MAX];
    struct position pos;

    clear_status();
    CHECK(addstr, "search: ");
    strcpy(str1, getword1());
    clear_status();
    if (cancel_flag) {
	cancel_flag = false;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    CHECK(addstr, "replace: ");
    strcpy(str2, getword2());
    if (cancel_flag) {
	cancel_flag = false;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    ESCRST();
    pos = find_word(str1);
    while (pos.row != -1) {
	ed_row = pos.row;
	ed_col = ed_col1 = pos.col;
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0) {
	    ed_start = 0;
	}
	display_screen();
	restore_cursol();
	ESCREV();
	CHECK(addstr, str1);
	clear_status();
	do {
	    CHECK(addstr, "replace? y/n ");
	    ESCRST();
	    CHECK(refresh);
	    c = getch1();
	}
	while (c != 'y' && c != 'n' && c != CTRL('G'));
	if (c == 'y') {
	    ed_row = pos.row;
	    ed_col = ed_col1 = pos.col;
	    replace_word(str1, str2);
	    display_screen();
	    modify_flag = true;
	    ed_col++;
	} else if (c == CTRL('G')) {
	    clear_status();
	    ESCRST();
	    display_screen();
	    restore_cursol();
	    return;
	} else {
	    display_screen();
	    ed_col++;
	}
	pos = find_word(str1);
    }
    clear_status();
    CHECK(addstr, "can't find ");
    CHECK(addstr, str1);
    ESCRST();
    restore_cursol();
}


void completion()
{
    int i, c;
    find_candidate();		// completion
    if (ed_candidate_pt == 0)
	return;
    else if (ed_candidate_pt == 1) {
	replace_fragment(ed_candidate[0]);
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
    } else {
	const int CANDIDATE = 3;
	int k = 0;
	ESCMOVE(ed_footer, 1);
	bool more_candidates_selected;
	do {
	    more_candidates_selected = false;
	    ESCREV();
	    for (i = 0; i < CANDIDATE; i++) {
		if (i + k >= ed_candidate_pt)
		    break;
		CHECK(printw, "%d:%s ", i + 1, ed_candidate[i + k]);
	    }
	    if (ed_candidate_pt > k + CANDIDATE)
		CHECK(addstr, "4:more");
	    ESCRST();
	    bool bad_candidate_selected;
	    do {
		bad_candidate_selected = false;
		CHECK(refresh);
		c = getch();
		if (c == ERR) {
		    errw("getch");
		}
		if (c != CTRL('G')) {
		    i = c - '1';
		    more_candidates_selected =
			ed_candidate_pt > k + CANDIDATE && i == CANDIDATE;
		    if (more_candidates_selected) {
			k = k + CANDIDATE;
			ESCMVLEFT(1);
			ESCCLSL();
			break;
		    }
		    bad_candidate_selected =
			i + k > ed_candidate_pt || i < 0 || c == RET;
		} else {
		    ESCMOVE(ed_footer, 1);
		    ESCREV();
		    clear_status();
		    ESCRST();
		    return;
		}
	    }
	    while (bad_candidate_selected);
	}
	while (more_candidates_selected);
	if (c != ESC)
	    replace_fragment(ed_candidate[i + k]);
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
    }
    return;
}



void pageup()
{
    ed_start = ed_start - ed_scroll;
    if (ed_start < 0)
	ed_start = 0;
    ed_row = ed_start;
    display_screen();
    restore_cursol();
}

void home()
{
    ed_row = 0;
    ed_start = 0;
    recalculate_col(ed_row, ed_col);
    display_screen();
    ESCMOVE(2, ed_col1 + LEFT_MARGIN);
}

void end()
{
    ed_row = ed_end;
    if (ed_end > ed_scroll)
	ed_start = ed_row - ed_middle;
    recalculate_col(ed_row, ed_col);
    display_screen();
    restore_cursol();
}

void pagedn()
{
    if (ed_end < ed_start + ed_scroll)
	return;
    ed_start = ed_start + ed_scroll;
    if (ed_start > ed_end)
	ed_start = ed_end - ed_scroll;
    ed_row = ed_start;
    recalculate_col(ed_row, ed_col);
    display_screen();
    restore_cursol();
}


char *getname()
{
    int c;
    static int pos;
    static char buf[SHORT_STR_MAX];

    cancel_flag = false;
    ESCMOVE(ed_footer, 12);
    ESCREV();
    CHECK(addstr, "                    ");
    ESCMOVE(ed_footer, 12);
    CHECK(addstr, buf);
    ESCRST();

    while (1) {
	CHECK(refresh);
	c = getch();
	if (c == ERR) {
	    errw("getch");
	}
	switch (c) {
	case RET:
	    if (strcmp(buf, "") == 0)
		break;
	    else
		return (buf);
	case KEY_BACKSPACE:
	case DEL:
	    if (pos > 0)
		pos--;
	    buf[pos] = 0;
	    break;
	case CTRL('G'):
	    cancel_flag = true;
	    return (buf);
	default:
	    if (pos > SHORT_STR_MAX)
		break;
	    else if (c < 20)
		break;
	    buf[pos] = c;
	    pos++;
	    break;
	}
	ESCMOVE(ed_footer, 12);
	ESCREV();
	CHECK(addstr, "                    ");
	ESCMOVE(ed_footer, 12);
	CHECK(addstr, buf);
	ESCRST();
    }

}


char *getword1()
{
    int c;
    static int pos;
    static char buf[SHORT_STR_MAX];

    cancel_flag = false;
    ESCMOVE(ed_footer, 12);
    ESCREV();
    CHECK(addstr, "                    ");
    ESCMOVE(ed_footer, 12);
    CHECK(addstr, buf);
    ESCRST();

    while (1) {
	CHECK(refresh);
	c = getch();
	if (c == ERR) {
	    errw("getch");
	}
	switch (c) {
	case RET:
	    if (strcmp(buf, "") == 0)
		break;
	    else
		return (buf);
	case KEY_BACKSPACE:
	case DEL:
	    if (pos > 0)
		pos--;
	    buf[pos] = 0;
	    break;
	case CTRL('G'):
	    cancel_flag = true;
	    return (buf);
	default:
	    if (pos > SHORT_STR_MAX)
		break;
	    else if (c < 20)
		break;
	    buf[pos] = c;
	    pos++;
	    break;
	}
	ESCMOVE(ed_footer, 12);
	ESCREV();
	CHECK(addstr, "                    ");
	ESCMOVE(ed_footer, 12);
	CHECK(addstr, buf);
	ESCRST();
    }

}

char *getword2()
{
    int c;
    static int pos;
    static char buf[SHORT_STR_MAX];

    cancel_flag = false;
    ESCMOVE(ed_footer, 12);
    ESCREV();
    CHECK(addstr, "                    ");
    ESCMOVE(ed_footer, 12);
    CHECK(addstr, buf);
    ESCRST();

    while (1) {
	CHECK(refresh);
	c = getch();
	if (c == ERR) {
	    errw("getch");
	}
	switch (c) {
	case RET:
	    if (strcmp(buf, "") == 0)
		break;
	    else
		return (buf);
	case KEY_BACKSPACE:
	case DEL:
	    if (pos > 0)
		pos--;
	    buf[pos] = 0;
	    break;
	case CTRL('G'):
	    cancel_flag = true;
	    return (buf);
	default:
	    if (pos > SHORT_STR_MAX)
		break;
	    else if (c < 20)
		break;
	    buf[pos] = c;
	    pos++;
	    break;
	}
	ESCMOVE(ed_footer, 12);
	ESCREV();
	CHECK(addstr, "                    ");
	ESCMOVE(ed_footer, 12);
	CHECK(addstr, buf);
	ESCRST();
    }

}

void edit_screen(void)
{
    restore_cursol();
    bool quit = edit_loop();
    while (!quit) {
	quit = edit_loop();
    }
}

bool edit_loop(void)
{
    int c;

    static int skip = 0;
    static bool uni3 = false;

    CHECK(refresh);
    c = getch1();
    switch (c) {
    case CTRL('H'):
	help();
	break;
    case CTRL('F'):
	right();
	break;
    case CTRL('B'):
	left();
	break;
    case CTRL('P'):
	up();
	break;
    case CTRL('N'):
	down();
	break;
    case CTRL('D'):
	del();
	break;
    case CTRL('A'):
	line_begin();
	break;
    case CTRL('E'):
	line_end();
	break;
    case CTRL('K'):
	cut_line();
	break;
    case CTRL('W'):
	cut_selection();
	break;
    case CTRL('Y'):
	uncut_selection();
	break;
    case CTRL('X'):
	ESCMOVE(ed_footer, 1);
	ESCREV();
	clear_status();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "^X");
	ESCRST();
	while (1) {
	    c = getch1();
	    switch (c) {
	    case CTRL('C'):
		return (quit_with_save());
	    case CTRL('S'):
		save_file();
		return false;
	    case CTRL('F'):
	    case CTRL('V'):
		load_file();
		return false;
	    case CTRL('W'):
		save_file_as();
		return false;
	    case CTRL('I'):
		insert_file();
		return false;
	    case CTRL('P'):
		save_region();
		return false;
	    case CTRL('Z'):
		ESCCLS();
		ESCMOVE(1, 1);
		return true;
	    case CTRL('G'):
		ESCMOVE(ed_footer, 1);
		ESCREV();
		clear_status();
		ESCRST();
		return false;
	    }
	}
	break;
    case CTRL('V'):
	pagedn();
	break;
    case CTRL('S'):
	search_next();
	break;
    case CTRL('R'):
	search_prev();
	break;
    case CTRL('T'):
	transfer_word();
	break;
    case CTRL('L'):
	redisplay_screen();
	break;
    case ESC:
	ESCMOVE(ed_footer, 1);
	ESCREV();
	clear_status();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "M");
	ESCRST();
	CHECK(refresh);
	while (1) {
	    c = getch();
	    if (c == ERR) {
		errw("getch");
	    }
	    switch (c) {
	    case 'w':
		save_selection();
		return false;
	    case '<':
		home();
		return false;
	    case '>':
		end();
		return false;
	    case 'v':
		pageup();
		return false;
	    case '^':
		mark_unmark();
		return false;
	    case TAB:
		completion();
		return false;
	    case 'i':
		information();
		return false;
	    case 'f':
		word_next();
		return false;
	    case 'b':
		word_prev();
		return false;
	    case CTRL('F'):
		sexp_next();
		return false;
	    case CTRL('B'):
		sexp_prev();
		return false;
	    case CTRL('N'):
		list_next();
		return false;
	    case CTRL('P'):
		list_prev();
		return false;
	    case CTRL('D'):
		list_down();
		return false;
	    case CTRL('U'):
		list_up();
		return false;
	    case CTRL('G'):
		ESCMOVE(ed_footer, 1);
		ESCREV();
		clear_status();
		ESCRST();
		return false;
	    }
	}
	break;
    case KEY_UP:
	up();
	break;
    case KEY_DOWN:
	down();
	break;
    case KEY_LEFT:
	left();
	break;
    case KEY_RIGHT:
	right();
	break;
    case KEY_HOME:
	home();
	break;
    case KEY_END:
	end();
	break;
    case KEY_IC:
	ed_ins = !ed_ins;
	display_header();
	restore_cursol();
	break;
    case KEY_PPAGE:
	pageup();
	break;
    case KEY_NPAGE:
	pagedn();
	break;
    case KEY_DC:
	del();
	break;
    case KEY_BACKSPACE:
    case DEL:
	backspace_key();
	break;
    case RET:
    case CTRL('O'):
	return_key();
	break;
    case TAB:
	tab_key();
	break;
    default:
	if (ed_col >= COL_SIZE)
	    break;
	ESCCLSLA();
	restore_paren();
	restore_bracket();
	if (ed_ins)
	    insert_col();
	ed_data[ed_row][ed_col] = c;
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
	emphasis_lparen();
	emphasis_rparen();
	emphasis_lbracket();
	emphasis_rbracket();
	ed_col++;
	if (isUni1(c) && skip == 0) {
	    ed_col1++;
	    skip = 0;
	} else if (isUni2(c) && skip == 0) {
	    ed_col1++;
	    skip = 1;
	} else if (isUni4(c) && skip == 0) {
	    ed_col1++;
	    skip = 3;
	} else if (isUni3(c) && skip == 0) {
	    uni3 = true;
	    skip = 2;
	}

	if (skip > 0)
	    skip--;

	// groupe uni3 has 1 or 2 width char  e.g. tai char is width 1, japanese is 2
	if (uni3 == true && skip == 0) {
	    ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col - 2);
	    uni3 = false;
	}
	restore_cursol();
	modify_flag = true;
    }
    return false;
}

void display_header(void)
{
    int i;
    ESCHOME();
    ESCREV();
    for (i = 0; i < COLS - 1; i++)
	CHECK(addch, ' ');
    ESCHOME();
    CHECK(printw, "Edlog %1.2f        File: %s   ", VERSION, fname);
    ESCMOVE(1, COLS - 9);
    if (ed_ins == true) {
	CHECK(addstr, "   insert");
    } else {
	CHECK(addstr, "overwrite");
    }
    ESCRST();
}

void display_screen()
{
    int line1, line2, i;

    ESCTOP();
    ESCCLS1();
    line1 = ed_start;
    line2 = ed_start + ed_scroll;
    if (line2 > ed_end)
	line2 = ed_end;

    while (line1 <= line2) {
	display_line(line1);
	line1++;
    }
    ESCMOVE(ed_footer, 1);
    ESCREV();
    for (i = 0; i < COLS - 9; i++)
	CHECK(addch, ' ');
    CHECK(addstr, "^H(help)");
    ESCRST();
}

void help(void)
{
    ESCMOVE(2, 1);
    ESCCLS1();
    CHECK(addstr, "--- Edlog help(1) ---\n"
	  "CTRL+F  move to right in character units     → key\n"
	  "CTRL+B  move to left in character units      ← key\n"
	  "CTRL+P  move to up in line                   ↑ key\n"
	  "CTRL+N  move to down in line                 ↓ key\n"
	  "CTRL+J  move to end of line\n"
	  "CTRL+A  move begin of line\n"
	  "CTRL+E  move to end of line\n"
	  "CTRL+D  delete one char                       Back Space key\n"
	  "CTRL+O  return                                Enter key\n"
	  "CTRL+V  display next page                     Page Down key\n"
	  "ESC V   display previous page                 Page Up key\n"
	  "ESC <   goto top page                         Home key\n"
	  "ESC >   goto end page                         End key\n"
	  "ESC f   Move forward in word units\n"
	  "ESC b   Move backward in word units\n"
	  "ESC CTRL+F  Move forward in S-expressdion units\n"
	  "ESC CTRL+B  Move Back in S-expression units\n"
	  "ESC CTRL+N  Move forward in list units\n"
	  "ESC CTRL+P  Move back in list units\n"
	  "ESC CTRL+U  Move up a level in the list structure\n"
	  "ESC STRL+D  Move down a level in the list structure\n"
	  "--- enter any key to go next page ---");
    CHECK(refresh);
    CHECK(getch);
    ESCMOVE(2, 1);
    ESCCLS1();
    CHECK(addstr, "--- Edlog help(2) ---\n"
	  "Insert      Switch insert-mode and overwrite-mode\n"
	  "TAB     insert spaces as lisp indent rule\n"
	  "CTRL+X  CTRL+C quit from editor with save\n"
	  "CTRL+X  CTRL+Z quit from editor without save\n"
	  "CTRL+X  CTRL+F load from file to editor\n"
	  "CTRL+X  CTRL+V load from file to editor\n"
	  "CTRL+X  CTRL+I insert buffer from file\n"
	  "CTRL+X  CTRL+S save file\n"
	  "CTRL+X  CTRL+W save file as\n"
	  "CTRL+X  CTRL+L save region to file as\n"
	  "CTRL+S  search a word forward\n"
	  "CTRL+R  search a word backward\n"
	  "CTRL+T  replace a word\n"
	  "ESC TAB complete builtin function name\n"
	  "ESC I   info of function\n"
	  "ESC ^   mark(or unmark) row for selection\n"
	  "CTRL+K  cut one line \n"
	  "CTRL+W  cut selection\n"
	  "ESC W   save selection\n"
	  "CTRL+Y  uncut selection\n"
	  "CTRL+G  cancel command\n" "--- enter any key to exit help ---");
    CHECK(refresh);
    CHECK(getch);
    display_screen();
    restore_cursol();
}

/*                                     COL_SIZE
 * buffer [0].........................[255]
 * ed_col = position of buffer
 * LEFT_MARGIN area of line numver 7
 * COLS = size of terminal
 *
 * if terminal col size is 80.
 * 1----6|7--------80|
 * line   buffer[ 0]-[72]
 *        buffer[73]-[145]
 *        ommit 146~
 * turnaround point is 73 (80-7)
 * col is display point 0~, 73~ 
*/

/*
 * unicode for Edlis
 * Now many OS adapted UTF8. unicode in ed_data is utf8 
 * e.g.  Japanese あ  0xe3 0x81 0x82
 * curses require wchar_t wide-charactor. so transform from multibyte-utf8 to wide-charactor.
 * and use addwstr thus display unicode
*/
void display_unicode(int line, int col)
{
    char mb[10];
    wchar_t wch[10];
    if (isUni1(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = 0;
    } else if (isUni2(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = ed_data[line][col + 1];
	mb[2] = 0;
    } else if (isUni3(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = ed_data[line][col + 1];
	mb[2] = ed_data[line][col + 2];
	mb[3] = 0;
    } else if (isUni4(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = ed_data[line][col + 1];
	mb[2] = ed_data[line][col + 2];
	mb[3] = ed_data[line][col + 3];
	mb[4] = 0;
    }

    mbstowcs(wch, mb, 10);
    addwstr(wch);
}


int find_turn_buffer_position(int line)
{
    int col, col1, turn;

    turn = COLS - LEFT_MARGIN;
    col = col1 = 0;
    while (col1 < turn) {
	col1 = col1 + increase_terminal(line, col);
	col = col + increase_buffer(line, col);
    }
    return (col);
}

void display_line(int line)
{
    int col, col1, turn;
    char linestr[10];

    turn = COLS - LEFT_MARGIN;
    sprintf(linestr, "% 5d ", line);
    CHECK(addstr, linestr);


    if (ed_col1 < turn)
	col = col1 = 0;
    else {
	col = find_turn_buffer_position(line);	// need recalculation
	col1 = turn;
    }
    while (((ed_col1 < turn && col1 < turn)
	    || (ed_col1 >= turn && col < COL_SIZE))
	   && ed_data[line][col] != EOL && ed_data[line][col] != NUL) {
	if (line >= ed_clip_start && line <= ed_clip_end)
	    ESCREV();
	else
	    ESCRST();

	if (ed_incomment != -1 && line >= ed_incomment) {	// comment 
	    // 
	    // #|...|#
	    ESCBOLD();
	    set_color(ed_comment_color);
	    while (((ed_col1 < turn && col1 < turn)
		    || (ed_col1 >= turn && col < COL_SIZE))
		   && ed_data[line][col] != EOL
		   && ed_data[line][col] != NUL) {
		if (isUni1(ed_data[line][col])) {
		    CHECK(addch, ed_data[line][col]);
		} else {
		    display_unicode(line, col);
		}
		col1 = col1 + increase_terminal(line, col);
		col = col + increase_buffer(line, col);

		if (ed_data[line][col - 2] == '*' &&
		    ed_data[line][col - 1] == '/') {
		    ed_incomment = -1;
		    ESCRST();
		    ESCFORG();
		    break;
		}
	    }
	    ESCRST();
	    ESCFORG();
	} else if (ed_data[line][col] == ' ' ||
		   ed_data[line][col] == '(' ||
		   ed_data[line][col] == ')' ||
		   ed_data[line][col] == ',' ||
		   ed_data[line][col] == '.') {
	    CHECK(addch, ed_data[line][col]);
	    col++;
	    col1++;
	} else {
	    switch (check_token(line, col)) {
	    case HIGHLIGHT_SYNTAX:
		ESCBOLD();
		set_color(ed_syntax_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != ','
		       && ed_data[line][col] != '.'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_BUILTIN:
		ESCBOLD();
		set_color(ed_builtin_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != ','
		       && ed_data[line][col] != '.'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_FUNCTION:
		ESCBOLD();
		set_color(ed_function_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != ','
		       && ed_data[line][col] != '.'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_QUOTE:
		ESCBOLD();
		set_color(ed_string_color);
		CHECK(addch, ed_data[line][col]);
		col++;
		col1++;
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);


		    if (ed_data[line][col - 1] == '\'' &&
			ed_data[line][col - 2] != '\\')
			break;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_STRING:
		ESCBOLD();
		set_color(ed_string_color);
		CHECK(addch, ed_data[line][col]);
		col++;
		col1++;
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);


		    if (ed_data[line][col - 1] == '$' &&
			ed_data[line][col - 2] != '\\')
			break;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_COMMENT:
		ESCBOLD();
		set_color(ed_comment_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);

		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_EXTENDED:
		ESCBOLD();
		set_color(ed_extended_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != ','
		       && ed_data[line][col] != '.'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_MULTILINE_COMMENT:
		ESCBOLD();
		set_color(ed_comment_color);
		ed_incomment = line;
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != EOL
		       && ed_data[line][col] != NUL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		    if (ed_data[line][col - 2] == '*' &&
			ed_data[line][col - 1] == '/') {
			ed_incomment = -1;
			ESCRST();
			ESCFORG();
			break;
		    }
		}
		break;
	    default:
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != ','
		       && ed_data[line][col] != '.'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);

		}
	    }
	}
    }
    CHECK(addch, EOL);
    ESCRST();
}

void set_color(enum Color n)
{
    if (has_colors()) {
	CHECK(color_set, n, NULL);
    }
}

void backspace(void)
{
    int i, size;

    if (ed_data[ed_row][ed_col - 1] == ')') {
	ed_lparen_row = -1;
	ed_rparen_row = -1;
    }

    i = ed_col;
    size = decrease_buffer(ed_row, ed_col - 1);
    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
    while (i < COL_SIZE) {
	ed_data[ed_row][i - size] = ed_data[ed_row][i];
	i++;
    }
}

void delete_char(void)
{
    int i, size;

    if (ed_data[ed_row][ed_col] == ')') {
	ed_lparen_row = -1;
	ed_rparen_row = -1;
    }
    i = ed_col;
    size = increase_buffer(ed_row, ed_col);
    while (ed_data[ed_row][i + size] != 0) {
	ed_data[ed_row][i] = ed_data[ed_row][i + size];
	i++;
    }
    ed_data[ed_row][i] = 0;
}


void insert_col()
{
    int i;

    i = find_eol(ed_row);
    while (i >= ed_col) {
	ed_data[ed_row][i + 1] = ed_data[ed_row][i];
	i--;
    }
}

void insert_row()
{
    int i, j, k;

    for (i = ed_end; i >= ed_row; i--) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i + 1][j] = ed_data[i][j];
	}
    }
    k = 0;
    for (j = ed_col; j < COL_SIZE; j++) {
	ed_data[ed_row + 1][k] = ed_data[ed_row][j];
	k++;
    }
    ed_data[ed_row][ed_col] = EOL;
}

void delete_row()
{
    int i, j, k, l, l1;

    k = l = find_eol(ed_row - 1);
    l1 = find_eol1(ed_row - 1);
    for (j = 0; j < COL_SIZE; j++) {
	ed_data[ed_row - 1][k] = ed_data[ed_row][j];
	k++;
	if (ed_data[ed_row][j] == EOL)
	    break;
    }

    for (i = ed_row; i < ed_end; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = ed_data[i + 1][j];
	}
    }
    ed_row--;
    ed_end--;
    ed_col = l;
    ed_col1 = l1;
}

/*
 * find_eol find position of eol in buffer
*/
int find_eol(int row)
{
    int i;

    for (i = 0; i < COL_SIZE; i++) {
	if (ed_data[row][i] == EOL)
	    return (i);
    }
    return (-1);
}

/*
* find_eol1 find position of eol on display terminal
*/
int find_eol1(int row)
{
    int col, col1;		// col1 is position of display terminal
    col = col1 = 0;
    while (col < COL_SIZE) {
	if (ed_data[row][col] == EOL)
	    return (col1);
	else if (isUni1(ed_data[row][col])) {
	    col++;
	    col1++;
	} else {
	    if (isUni3(ed_data[row][col]))
		col1 = col1 + 2;
	    else
		col1++;

	    col = col + increase_buffer(row, col);
	}
    }

    return (-1);
}

struct position find_lparen(int bias)
{
    int nest, row, col, col1, limit;	//col is position of buffer, col1 is position of display
    struct position pos;

    row = ed_row;
    if (ed_col != 0) {
	col = ed_col - bias;
	col1 = ed_col1 - bias;
    } else {
	row--;
	if (row < 0) {
	    pos.col = 0;
	}
	col = find_eol(row);
	col1 = find_eol1(row);
    }

    nest = 0;
    limit = ed_row - ed_scroll;
    if (limit < 0)
	limit = 0;

    while (row >= limit) {
	if (ed_data[row][col] == '('
	    && !(col > 0 && ed_data[row][col - 1] == '\\') && nest == 0)
	    break;
	else if (ed_data[row][col] == ')'
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest++;
	else if (ed_data[row][col] == '('
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest--;
	else if (ed_data[row][col] == '$') {
	    col--;
	    col1--;
	    while (ed_data[row][col] != '$' && col > 0) {
		col1 = col1 - decrease_terminal(row, col);
		col = col - decrease_buffer(row, col);
	    }
	}


	if (col == 0) {
	    row--;
	    if (row > 0) {
		col = find_eol(row);
		col1 = find_eol1(row);
	    }

	} else {
	    col1 = col1 - decrease_terminal(row, col);
	    col = col - decrease_buffer(row, col);
	}
    }
    if (row >= limit) {
	pos.row = row;
	pos.col = col1;
    } else {
	pos.row = -1;
	pos.col = 0;
    }
    return (pos);
}

struct position find_rparen(int bias)
{
    int nest, row, col, col1, limit;	//col is position of buffer, col1 is position of display
    struct position pos;

    row = ed_row;
    col = ed_col + bias;
    col1 = ed_col1 + bias;
    nest = 0;
    limit = ed_row + ed_scroll;
    if (limit > ed_end)
	limit = ed_end;

    while (row < limit) {
	if (ed_data[row][col] == ')'
	    && !(col > 0 && ed_data[row][col - 1] == '\\') && nest == 0)
	    break;
	else if (ed_data[row][col] == '('
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest++;
	else if (ed_data[row][col] == ')'
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest--;
	else if (ed_data[row][col] == '$') {
	    col++;
	    col1++;
	    while (ed_data[row][col] != '$' && ed_data[row][col] != EOL
		   && ed_data[row][col] != 0) {
		col1 = col1 + increase_terminal(row, col);
		col = col + increase_buffer(row, col);
	    }
	}


	if (ed_data[row][col] == EOL) {
	    row++;
	    col = col1 = 0;
	} else {
	    col1 = col1 + increase_terminal(row, col);
	    col = col + increase_buffer(row, col);
	}
    }
    if (row < limit) {
	pos.row = row;
	pos.col = col1;
    } else {
	pos.row = -1;
	pos.col = 0;
    }
    return (pos);
}


struct position find_lbracket(int bias)
{
    int nest, row, col, col1, limit;	//col is position of buffer, col1 is position of display
    struct position pos;

    row = ed_row;
    if (ed_col != 0) {
	col = ed_col - bias;
	col1 = ed_col1 - bias;
    } else {
	row--;
	if (row < 0) {
	    pos.col = 0;
	}
	col = find_eol(row);
	col1 = find_eol1(row);
    }

    nest = 0;
    limit = ed_row - ed_scroll;
    if (limit < 0)
	limit = 0;

    while (row >= limit) {
	if (ed_data[row][col] == '['
	    && !(col > 0 && ed_data[row][col - 1] == '\\') && nest == 0)
	    break;
	else if (ed_data[row][col] == ']'
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest++;
	else if (ed_data[row][col] == '['
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest--;
	else if (ed_data[row][col] == '$') {
	    col--;
	    col1--;
	    while (ed_data[row][col] != '$' && col > 0) {
		col1 = col1 - decrease_terminal(row, col);
		col = col - decrease_buffer(row, col);
	    }
	}


	if (col == 0) {
	    row--;
	    if (row > 0) {
		col = find_eol(row);
		col1 = find_eol1(row);
	    }

	} else {
	    col1 = col1 - decrease_terminal(row, col);
	    col = col - decrease_buffer(row, col);
	}
    }
    if (row >= limit) {
	pos.row = row;
	pos.col = col1;
    } else {
	pos.row = -1;
	pos.col = 0;
    }
    return (pos);
}

struct position find_rbracket(int bias)
{
    int nest, row, col, col1, limit;	//col is position of buffer, col1 is position of display
    struct position pos;

    row = ed_row;
    col = ed_col + bias;
    col1 = ed_col1 + bias;
    nest = 0;
    limit = ed_row + ed_scroll;
    if (limit > ed_end)
	limit = ed_end;

    while (row < limit) {
	if (ed_data[row][col] == ']'
	    && !(col > 0 && ed_data[row][col - 1] == '\\') && nest == 0)
	    break;
	else if (ed_data[row][col] == '['
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest++;
	else if (ed_data[row][col] == ']'
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest--;
	else if (ed_data[row][col] == '$') {
	    col++;
	    col1++;
	    while (ed_data[row][col] != '$' && ed_data[row][col] != EOL
		   && ed_data[row][col] != 0) {
		col1 = col1 + increase_terminal(row, col);
		col = col + increase_buffer(row, col);
	    }
	}


	if (ed_data[row][col] == EOL) {
	    row++;
	    col = col1 = 0;
	} else {
	    col1 = col1 + increase_terminal(row, col);
	    col = col + increase_buffer(row, col);
	}
    }
    if (row < limit) {
	pos.row = row;
	pos.col = col1;
    } else {
	pos.row = -1;
	pos.col = 0;
    }
    return (pos);
}


void restore_paren()
{
    if (ed_lparen_row != -1 && ed_lparen_row >= ed_start
	&& ed_lparen_row <= ed_start + ed_scroll) {
	if (ed_lparen_col <= COLS - 1 - LEFT_MARGIN)
	    ESCMOVE(ed_lparen_row + TOP_MARGIN - ed_start,
		    ed_lparen_col + LEFT_MARGIN);
	else
	    ESCMOVE(ed_lparen_row + TOP_MARGIN - ed_start,
		    ed_lparen_col - COLS + LEFT_MARGIN);
	ESCBORG();
	CHECK(addch, '(');
	ed_lparen_row = -1;
    }
    if (ed_rparen_row != -1 && ed_rparen_row >= ed_start
	&& ed_rparen_row <= ed_start + ed_scroll) {
	if (ed_rparen_col <= COLS - 1 - LEFT_MARGIN)
	    ESCMOVE(ed_rparen_row + TOP_MARGIN - ed_start,
		    ed_rparen_col + LEFT_MARGIN);
	else
	    ESCMOVE(ed_rparen_row + TOP_MARGIN - ed_start,
		    ed_rparen_col - COLS + LEFT_MARGIN);
	ESCBORG();
	CHECK(addch, ')');
	ed_rparen_row = -1;
    }
}

void restore_bracket()
{
    if (ed_lbracket_row != -1 && ed_lbracket_row >= ed_start
	&& ed_lbracket_row <= ed_start + ed_scroll) {
	if (ed_lbracket_col <= COLS - 1 - LEFT_MARGIN)
	    ESCMOVE(ed_lbracket_row + TOP_MARGIN - ed_start,
		    ed_lbracket_col + LEFT_MARGIN);
	else
	    ESCMOVE(ed_lbracket_row + TOP_MARGIN - ed_start,
		    ed_lbracket_col - COLS + LEFT_MARGIN);
	ESCBORG();
	CHECK(addch, '[');
	ed_lbracket_row = -1;
    }
    if (ed_rbracket_row != -1 && ed_rbracket_row >= ed_start
	&& ed_rbracket_row <= ed_start + ed_scroll) {
	if (ed_rbracket_col <= COLS - 1 - LEFT_MARGIN)
	    ESCMOVE(ed_rbracket_row + TOP_MARGIN - ed_start,
		    ed_rbracket_col + LEFT_MARGIN);
	else
	    ESCMOVE(ed_rbracket_row + TOP_MARGIN - ed_start,
		    ed_rbracket_col - COLS + LEFT_MARGIN);
	ESCBORG();
	CHECK(addch, ']');
	ed_rbracket_row = -1;
    }
}


void emphasis_lparen()
{
    struct position pos;

    if (ed_data[ed_row][ed_col] != ')')
	return;

    pos = find_lparen(1);
    if (ed_col <= COLS - 1 - LEFT_MARGIN
	&& pos.col <= COLS - 1 - LEFT_MARGIN) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, ')');
	    ESCBORG();
	    if (pos.row >= ed_start) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, '(');
	    }
	    ed_lparen_row = pos.row;
	    ed_lparen_col = pos.col;
	    ed_rparen_row = ed_row;
	    ed_rparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    } else if (ed_col >= COLS && pos.col >= COLS) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		    ed_col1 - COLS + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, ')');
	    ESCBORG();
	    if (pos.row >= ed_start) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col - COLS + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, '(');
	    }
	    ed_lparen_row = pos.row;
	    ed_lparen_col = pos.col;
	    ed_rparen_row = ed_row;
	    ed_rparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    }
}

void emphasis_rparen()
{
    struct position pos;

    if (ed_data[ed_row][ed_col] != '(')
	return;

    pos = find_rparen(1);
    if (ed_col <= COLS - 1 - LEFT_MARGIN
	&& pos.col <= COLS - 1 - LEFT_MARGIN) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, '(');
	    ESCBORG();
	    if (pos.row <= ed_start + ed_scroll) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, ')');
	    }
	    ed_rparen_row = pos.row;
	    ed_rparen_col = pos.col;
	    ed_lparen_row = ed_row;
	    ed_lparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    } else if (ed_col >= COLS && pos.col >= COLS) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		    ed_col1 - COLS + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, '(');
	    ESCBORG();
	    if (pos.row <= ed_start + ed_scroll) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col - COLS + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, ')');
	    }
	    ed_rparen_row = pos.row;
	    ed_rparen_col = pos.col;
	    ed_lparen_row = ed_row;
	    ed_lparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    }
}


void emphasis_lbracket()
{
    struct position pos;

    if (ed_data[ed_row][ed_col] != ']')
	return;

    pos = find_lbracket(1);
    if (ed_col <= COLS - 1 - LEFT_MARGIN
	&& pos.col <= COLS - 1 - LEFT_MARGIN) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, ']');
	    ESCBORG();
	    if (pos.row >= ed_start) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, '[');
	    }
	    ed_lbracket_row = pos.row;
	    ed_lbracket_col = pos.col;
	    ed_rbracket_row = ed_row;
	    ed_rbracket_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    } else if (ed_col >= COLS && pos.col >= COLS) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		    ed_col1 - COLS + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, ']');
	    ESCBORG();
	    if (pos.row >= ed_start) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col - COLS + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, '[');
	    }
	    ed_lbracket_row = pos.row;
	    ed_lbracket_col = pos.col;
	    ed_rbracket_row = ed_row;
	    ed_rbracket_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    }
}

void emphasis_rbracket()
{
    struct position pos;

    if (ed_data[ed_row][ed_col] != '[')
	return;

    pos = find_rbracket(1);
    if (ed_col <= COLS - 1 - LEFT_MARGIN
	&& pos.col <= COLS - 1 - LEFT_MARGIN) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, '[');
	    ESCBORG();
	    if (pos.row <= ed_start + ed_scroll) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, ']');
	    }
	    ed_rbracket_row = pos.row;
	    ed_rbracket_col = pos.col;
	    ed_lbracket_row = ed_row;
	    ed_lbracket_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    } else if (ed_col >= COLS && pos.col >= COLS) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		    ed_col1 - COLS + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, '[');
	    ESCBORG();
	    if (pos.row <= ed_start + ed_scroll) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col - COLS + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, ']');
	    }
	    ed_rbracket_row = pos.row;
	    ed_rbracket_col = pos.col;
	    ed_lbracket_row = ed_row;
	    ed_lbracket_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    }
}


void softtabs(int n)
{
    while (n > 0) {
	insert_col();
	ed_data[ed_row][ed_col] = ' ';
	ed_col++;
	ed_col1++;
	n--;
    }
}


void save_data(char *fname)
{
    int row, col;

    FILE *port = fopen(fname, "w");
    for (row = 0; row <= ed_end; row++)
	for (col = 0; col < COL_SIZE; col++) {
	    fputc(ed_data[row][col], port);
	    if (ed_data[row][col] == EOL)
		break;
	}
    fclose(port);
}

void save_copy(char *fname)
{
    int row, col;

    FILE *port = fopen(fname, "w");
    for (row = 0; row < ed_copy_end; row++) {
	for (col = 0; col < COL_SIZE; col++) {
	    fputc(ed_copy[row][col], port);
	    if (ed_copy[row][col] == EOL)
		break;
	}
    }
    fputc(EOL, port);
    fclose(port);
}

void load_data(char *fname)
{
    port = fopen(fname, "r");
    ed_row = 0;
    ed_col = 0;
    ed_col1 = 0;
    ed_start = 0;
    ed_end = 0;
    ed_lparen_row = -1;
    ed_rparen_row = -1;
    ed_lbracket_row = -1;
    ed_rbracket_row = -1;
    ed_clip_start = -1;
    ed_clip_end = -1;
    ed_data[0][0] = EOL;
    if (port != NULL) {
	int c;

	c = fgetc(port);
	while (c != EOF) {
	    if (c == TAB) {
		c = SPACE;
	    }
	    ed_data[ed_row][ed_col] = c;
	    if (c == EOL) {
		ed_row++;
		ed_col = ed_col1 = 0;
		if (ed_row >= ROW_SIZE)
		    printf("row %d over max-row", ed_row);
	    } else {
		ed_col++;
		if (ed_col >= COL_SIZE)
		    printf("column %d over max-column", ed_col);
	    }
	    c = fgetc(port);
	}
	/* if get EOF without EOL 
	 *  this is a pen[EOF] -> this is a pen[EOL]
	 */
	if (ed_col != 0) {
	    ed_data[ed_row][ed_col] = EOL;
	    ed_row++;
	}
	ed_end = ed_row;
	ed_data[ed_end][0] = EOL;
	fclose(port);
    }
}


bool is_special(int row, int col)
{
    char str[TOKEN_MAX];
    int pos;

    pos = 0;
    while (ed_data[row][col] != ' ' &&
	   ed_data[row][col] != '(' && ed_data[row][col] >= ' ') {
	str[pos] = ed_data[row][col];
	col++;
	pos++;
    }
    str[pos] = NUL;
    if (pos == 0)
	return false;
    return in_special_table(str);
}

int findnext(int row, int col)
{
    if (ed_data[row][col] == '(')
	return (col);
    else {
	while (ed_data[row][col] != ' ' && ed_data[row][col] > ' ')
	    col++;

	while (ed_data[row][col] == ' ')
	    col++;
    }
    return (col);
}


void remove_headspace(int row __unused)
{
    int col, i, j, k;

    col = 0;
    while (ed_data[ed_row][col] == ' ')
	col++;
    k = find_eol(ed_row);
    if (k == -1)		// can't find
	k = 0;
    i = 0;
    for (j = col; j <= k; j++) {
	ed_data[ed_row][i] = ed_data[ed_row][j];
	i++;
    }
}

int calc_tabs()
{
    int col;

    if (ed_row == 0)
	return (0);

    col = 0;
    while (ed_data[ed_row - 1][col] == ' ') {
	col++;
    }
    return (col);

}

void copy_selection()
{
    int i, j, k;

    if (ed_clip_end - ed_clip_start > COPY_SIZE)
	return;

    j = 0;
    for (i = ed_clip_start; i <= ed_clip_end; i++) {
	for (k = 0; k < COLS; k++)
	    ed_copy[j][k] = ed_data[i][k];
	j++;
    }
    ed_copy_end = j;
}

void paste_selection()
{
    int i, j, k;

    if (ed_copy_end == 0)
	return;
    if (ed_end + ed_copy_end > ROW_SIZE) {
	clear_status();
	ESCMOVE(ed_footer, 1);
	ESCREV();
	CHECK(addstr, "Buffer over flow");
	ESCRST();
	restore_cursol();
	return;
    }

    for (i = ed_end; i >= ed_row; i--) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i + ed_copy_end][j] = ed_data[i][j];
	}
    }
    ed_end = ed_end + ed_copy_end;
    ed_data[ed_end][0] = EOL;

    k = ed_row;
    for (i = 0; i < ed_copy_end; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[k][j] = ed_copy[i][j];
	}
	k++;
    }

}

void delete_selection()
{
    int i, j, k;

    if (ed_clip_start == -1)
	return;
    k = ed_clip_end - ed_clip_start + 1;
    for (i = ed_clip_start; i <= ed_end; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = ed_data[i + k][j];
	}
    }
    ed_end = ed_end - k;
    ed_data[ed_end][0] = EOL;
}

enum HighlightToken check_token(int row, int col)
{
    char str[COL_SIZE];
    int pos;

    pos = 0;
    if (ed_data[row][col] == '\'')
	return HIGHLIGHT_QUOTE;
    else if (ed_data[row][col] == '$')
	return HIGHLIGHT_STRING;
    else if (ed_data[row][col] == '%')
	return HIGHLIGHT_COMMENT;
    while (ed_data[row][col] != ' ' &&
	   ed_data[row][col] != '(' &&
	   ed_data[row][col] != ')' &&
	   ed_data[row][col] != ',' &&
	   ed_data[row][col] != '.' &&
	   ed_data[row][col] != NUL && ed_data[row][col] != EOL) {
	str[pos] = ed_data[row][col];
	col++;
	pos++;
    }
    str[pos] = NUL;
    if (pos == 0)
	return HIGHLIGHT_NONE;
    else if (str[0] == '/' && str[1] == '*')
	return HIGHLIGHT_MULTILINE_COMMENT;	// /*...*/
    return maybe_match(str);
}

char *get_fragment()
{
    static char str[TOKEN_MAX];
    int col, pos;

    col = ed_col - 1;
    while (col >= 0 &&
	   ed_data[ed_row][col] != ' ' &&
	   ed_data[ed_row][col] != '(' &&
	   ed_data[ed_row][col] != ')' &&
	   ed_data[ed_row][col] != ',' && ed_data[ed_row][col] != ';') {
	col--;
    }
    col++;
    pos = 0;
    while (ed_data[ed_row][col] != ' ' &&
	   ed_data[ed_row][col] != '(' &&
	   ed_data[ed_row][col] != ',' &&
	   ed_data[ed_row][col] != '.' &&
	   ed_data[ed_row][col] != ';' && ed_data[ed_row][col] >= ' ') {
	str[pos] = ed_data[ed_row][col];
	col++;
	pos++;
    }
    str[pos] = NUL;
    return (str);
}

void find_candidate()
{
    char *str;

    str = get_fragment();
    ed_candidate_pt = 0;
    if (str[0] != NUL)
	gather_fuzzy_matches(str, ed_candidate, &ed_candidate_pt);
}

void replace_fragment(const char *newstr)
{
    char *oldstr;
    int m, n;

    oldstr = get_fragment();
    m = strlen(oldstr);
    n = strlen(newstr);
    while (m > 0) {
	backspace();
	m--;
    }
    while (n > 0) {
	insert_col();
	ed_data[ed_row][ed_col] = *newstr;
	ed_col++;
	ed_col1++;
	newstr++;
	n--;
    }
}

struct position find_word(const char *word)
{
    int i, j, k, len;
    struct position pos;
    const char *word1;

    i = ed_row;
    j = ed_col;
    word1 = word;
    len = strlen(word);
    while (i <= ed_end + 1) {
	while (j < COL_SIZE && ed_data[i][j] != NUL) {
	    k = j;
	    while (k < j + len && ed_data[i][k] == *word) {
		word++;
		k++;
	    }
	    if (k >= j + len) {
		pos.row = i;
		pos.col = j;
		return (pos);
	    }
	    j++;
	    word = word1;
	}
	i++;
	j = 0;
    }
    // can't find word
    pos.row = -1;
    pos.col = 0;
    return (pos);
}

struct position find_word_back(const char *word)
{
    int i, j, k, len;
    struct position pos;
    const char *word1;

    i = ed_row;
    j = ed_col;
    word1 = word;
    len = strlen(word);
    while (i >= 0) {
	while (j < COL_SIZE && ed_data[i][j] != NUL) {
	    k = j;
	    while (k < j + len && ed_data[i][k] == *word) {
		word++;
		k++;
	    }
	    if (k >= j + len) {
		pos.row = i;
		pos.col = j;
		return (pos);
	    }
	    j++;
	    word = word1;
	}
	i--;
	j = 0;
    }
    // can't find word
    pos.row = -1;
    pos.col = 0;
    return (pos);
}


void replace_word(const char *str1, const char *str2)
{
    int len1, len2, i, j;

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 == len2) {
	for (i = 0; i < len1; i++) {
	    ed_data[ed_row][ed_col] = *str2;
	    ed_col++;
	    str2++;
	}
    } else if (len1 > len2) {
	i = ed_col + len1;
	j = len1 - len2;
	while (ed_data[ed_row][i] != NUL) {
	    ed_data[ed_row][i - j] = ed_data[ed_row][i];
	    i++;
	}
	ed_data[ed_row][i] = NUL;

	for (i = 0; i < len2; i++) {
	    ed_data[ed_row][ed_col + i] = *str2;
	    str2++;
	}
    } else {			// len1 < len2
	i = find_eol(ed_row);
	j = len2 - len1;
	while (i >= ed_col + len1) {
	    ed_data[ed_row][i + j] = ed_data[ed_row][i];
	    i--;
	}
	ed_data[ed_row][i] = NUL;
	for (i = 0; i < len2; i++) {
	    ed_data[ed_row][ed_col + i] = *str2;
	    str2++;
	}
    }
}

//-------------------help information----------------------------------

void information(void)
{
    int i;

    i = find_function_data(get_fragment());
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    if (i != -1) {
	CHECK(addstr, functions_data[i + 1]);
	CHECK(addstr, "\n");
	ESCRST();
	CHECK(addstr, functions_data[i + 2]);
	CHECK(addstr, " --- enter any key to exit ---");
	CHECK(refresh);
	CHECK(getch);
	display_header();
	display_screen();
    } else {
	CHECK(addstr, "Can't fild");
	ESCRST();
    }
    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
}

static const char *functions_data[] = {
    "abolish",
    "abolish(name/Arity)",
    "Removes all clauses with the specified name arity from the data berth.",
    "abort",
    "abort",
    "Stop the current program. Return to the interpreter after the program ends. If the program is compiled, abort restarts its goal.",
    "ansi_cuu",
    "ansi_cuu(N)",
    "Move the cursor up N lines.",
    "ansi_cud",
    "ansi_cud(N)",
    "Move the cursor down N lines.",
    "ansi_cuf",
    "ansi_cuf(N)",
    "Move the cursor forward N digits.",
    "ansi_sub",
    "ansi_sub(N)",
    "Move the cursor back N digits.",
    "ansi_cpr",
    "ansi_cpr(Row,Col)",
    "The predicate ansi_cpr is used to know the current cursor position. If the arguments Row and Col are not assigned, the coordinates of the current cursor position are in rows and columns. Unify each argument. If it has been assigned, compare that number with the coordinates of the current position.",
    "ansi_scp",
    "ansi_scp",
    "The predicate ansi_scp saves the current cursor position and the character attributes at that position.",
    "ansi_rcp",
    "ansi_rcp",
    "The predicate ansi_rcp restores the cursor position and attributes saved by ansi_scp.",
    "ansi_ed",
    "ansi_ed",
    "The predicate ansi_ed erase display.",
    "ansi_el",
    "ansi_el",
    "The predicate ansi_el erase from the cursor to end of line.",
    "ansi_sgr",
    "ansi_sgr(G)",
    "The predicate ansi_sgr sets graphic attributes. G can be an integer or a list of integers. see user manual.",
    "arg",
    "arg(N,Term,X)",
    "Unify X to the Nth value of the term. (Arguments are numbered from 1 in the increasing direction.)",
    "arg0",
    "arg0(N,Term,X)",
    "Unify X to the value of the N + 1th argument of the term. (Arguments are numbered from 0 in the increasing direction.)",
    "assert",
    "assert(Clause)",
    "Add a clause to the end of the predicate.",
    "asserta",
    "asserta(Clause)",
    "Add a clause to the top of the predicate.",
    "assertz",
    "assertz(Clause)",
    "Add a clause to the end of the predicate.",
    "atom",
    "atom(X)",
    "Check if X is an atom.",
    "atom_string",
    "atom_string(Atom,String)",
    "Convert an atom to a string or convert a string to an atom.",
    "atomic",
    "atomic(X)",
    "Check if X is an atom data type.",
    "break",
    "break",
    "Suspend program execution and display an interpreter prompt. The program can be restarted by the following types: end_of_file",
    "call",
    "call(P)",
    "Call the interpreted goal P.",
    "chdir",
    "chdir(Path)",
    "Change or revert to the current directory.",
    "clause",
    "clause(Head,Body)",
    "Unify Head and Body to the head and body of the node, respectively. Head must be assigned. example",
    "close",
    "close(Handle)",
    "Closes the file specified by Handle.",
    "ctr_dec",
    "ctr_dec(Ctr,X)",
    "Decreases the value of a counter and returns the previous value of that counter.",
    "ctr_inc",
    "ctr_inc(Ctr,X)",
    "Increases the value of a counter and returns the previous value of that counter.",
    "ctr_is",
    "ctr_is(Ctr,X)",
    "Returns the current counter value.",
    "ctr_set",
    "ctr_set(Ctr,X)",
    "Set the counter to the specified value.",
    "current_op",
    "current_op(Proc,Assoc,Op)",
    "Returns the operator constants currently defined in the database while backtracking.",
    "current_predicate",
    "current_predicate(Predicate)",
    "Returns the predicate currently defined in the database while backtracking.",
    "date",
    "date(date(Year,Month,Day))",
    "Set the year, month, and day.",
    "date_day",
    "date_day(date(Year,Month,Day),WeekDay)",
    "Returns the day of the week on a given date as a number between 0 (Sunday) and 6 (Saturday).",
    "dec",
    "dec(N,X)",
    "Subtract 1 from the number N and give it to the value X.",
    "delete",
    "delete(Filename)",
    "Delete the specified file.",
    "directory",
    "directory(Path,Name,Mode,Time,Date,Size)",
    "List the directory files specified by Path. see user manual",
    "display",
    "display(Term)",
    "Write the term to standard output with prefix notation.",
    "dup",
    "dpu(Handlein,Handleout)",
    "Allocate a second fundle to the open file.",
    "edit",
    "edit(Filename)",
    "Switch from the interpreter to the editor for editing the file specified by Filename. Call nano as an editor. When you exit nano, the contents of the file will be read into the interpreter. If the environment variable EDITOR has a value, call that editor.",
    "eq",
    "eq(X,Y)",
    "Check if X and Y are the same data object and are stored at the same address.",
    "erase",
    "erase(Ref)",
    "Removes the entry stored under the specified reference number.",
    "eraseall",
    "eraseall(Key)",
    "Removes all entries stored under the specified key.",
    "expand_term",
    "expand_term(Term,Newterm)",
    "DCG: Converts a term in a limited clause grammar to an equivalent Prolog term.",
    "fail",
    "fail",
    "Goals are always false.",
    "float",
    "float(X)",
    "Check if X is a floating point number.",
    "float_text",
    "float_text(Float,Text,Format)",
    "Converts a floating point number to a string according to the Format specification, or converts a string to a floating point number. see user manual.",
    "flush",
    "flush",
    "Remove all characters in the type-ahead buffer.",
    "functor",
    "functor(Struct,Name,Arity)",
    "Returns the structure name and arity.",
    "gc",
    "gc(Amount)",
    "Launch garbage collection. When the argument is full, the cells that are no longer needed in the heap area are collected.",
    "get",
    "get(Char)",
    "Read the next character from a standard input device, skipping unprinted characters, Unify the ASCII value with Char.",
    "get0",
    "get0(Char)",
    "Read the next character from a standard input device, skipping unprinted characters, Unify the ASCII value with Char. get0 does not skip non-printing characters.",
    "get0_noecho",
    "get0_noecho(Char)",
    "Read the following characters from the standard input device and unify the ASCII value to Char. get0_noecho does not display the character on the standard output device.",
    "halt",
    "halt",
    "Exits the interpreter.",
    "ifthen",
    "ifthen(P, Q)",
    "Execute goal Q if goal P succeeds.",
    "ifthenelse",
    "ifthenelse(P, Q, R)",
    "Execute goal Q if goal P succeeds; if P fails, execute R.",
    "in",
    "in(Port, Byte)",
    "Read one byte from the specified port.",
    "inc",
    "inc(N, X)",
    "Add 1 to number N and assign the result to X.",
    "instance",
    "instance(Ref,Term)",
    "Returns the term for that reference number.",
    "integer",
    "integer(X)",
    "Check if X is an integer.",
    "int_text",
    "int_text(Integer,String)",
    "Convert an integer to a string, or convert a string to an integer.",
    "is",
    "X is E",
    "Evaluate E and unify its value to X.",
    "keysort",
    "keysort(L1,L2)",
    "Sort the list L1 in standard order. List elements must be in the form Key_Value. The sorted list is returned to L2. Even if it is duplicated, it won't be united.",
    "leash",
    "leash(Mode)",
    "Constrain the port to the specified Mode.",
    "length",
    "length(L,N)",
    "Change the length of the list back to N.",
    "listing",
    "listing/listing(Name/Arith)/listing([Name/Arity,Name/Arity])",
    "Write all clauses to the specified predicate or list of predicates in the current database to standard output.",
    "list_text",
    "list_text(List,AtomString)",
    "Convert a character list to an atom (if the atom already exists) or a string, or convert an atom or string Convert to a character list.",
    "mkdir",
    "mkdir(Path)",
    "Create a new directory.",
    "name",
    "name(Atom,List)",
    "Convert a list to an atom, or convert an atom or an integer to a list.",
    "nl",
    "nl/nl(Handle)",
    "write newline to stdout. write newline to file.",
    "nth_char",
    "nth_char(N, String, Char)",
    "Return the ASCII (or Unicode) value of the character that is N positions from the start of the string.",
    "open",
    "open(Handle,Filename,Access)",
    "Open an existing file. Access is one of the following r read w write rw read and write a append ra read and append",
    "read",
    "read(Term)/read(Handle,Term)",
    "Read terms from standard input devices. Read terms from a file.",
    "read_line",
    "read_line(X)/read_line(Handle,X)",
    "Read one line from standard input. Read one line from the file specified by Handle.",
    "read_string",
    "read_string(MaxLength, X)/read_string(Handle, MaxLength, X)",
    "Reads a string from the standard input device. Reads a string from the specified file.",
    "recorda",
    "recorda(Key,Term,Ref)",
    "Predicates a term and returns a new reference number for that term.",
    "recorded",
    "recorded(Key, Term, Ref)",
    "Returns the term stored under the specified key and its reference number while backtracking.",
    "recordz",
    "recordz(Key,Term,Ref)",
    "Adds a term at the end of the predicate and returns the reference number assigned to that term.",
    "recordh",
    "recordh(Table_name,Sort_key,Term)",
    "Record the term in the hash table.",
    "ref",
    "ref(X)",
    "Check if X is a reference number.",
    "removeallh",
    "removeallh(Table_name)",
    "Delete the hash table.",
    "removeh",
    "removeh(Table_name,Sort_key,Term)",
    "Remove a term from the hash table.",
    "reset_op",
    "reset_op",
    "Reset the operator definition to its default value.",
    "retract",
    "retract (Clause)",
    "Remove a clause from the database.",
    "retrieveh",
    "retrieveh(Table_name,Sort_key,Term)",
    "Returns a term from the hash table.",
    "rename",
    "rename(Filename,Newname)",
    "Rename the file.",
    "rmdir",
    "rmdir(Path)",
    "Delete the directory.",
    "save",
    "save/save(Name)",
    "Save all changes made to the database since the last save. Save the internal database with the specified program name, Name.",
    "shell",
    "shell(Command)",
    "Execute the BASH command and succeed.",
    "sort",
    "sort(L1.L2)",
    "Sort list L1 into standard order, eliminate duplication and return sorted list to L2.",
    "spy",
    "spy(Name/Arity)",
    "Set a predicate as a debug spy point.",
    "stdin",
    "stdin(FileHandle,Goal)",
    "Change standard input during that goal.",
    "stdout",
    "stdout(FileHandle.Goal)",
    "Change standard input during that goal.",
    "stdinout",
    "stdinout(InFile,OutFile,goal)",
    "During that goal, change standard input and standard output.",
    "string",
    "string(X)",
    "Check if X is a string.",
    "string_length",
    "string_length(String,Length)",
    "Returns the length of the string.",
    "string_term",
    "string_term(String,Term)",
    "Change the string to a term.",
    "substring",
    "substring(InString,N,Length,OutString)",
    "Extract substrings from strings. N is a natural number starting from the starting position 1. Length is the length of the character string to be extracted",
    "syntaxerrors",
    "syntaxerrors(Old,New)",
    "Specify whether to output the syntax error message or check the current setting. An error message is output with yes, and no error message is output with no.",
    "system",
    "system(P)",
    "Check if P is an embedded predicate.",
    "tab",
    "tab(N)/tab(Handle,N)",
    "Write the specified number of space characters to the standard output device.Write the specified number of space characters in the file.",
    "tell",
    "tell(Filename)",
    "Open a file for output and make it the current output file.",
    "telling",
    "telling(X)",
    "Returns the name of the output file opened by tell.",
    "time",
    "time(Hours,Minutes,Seconds)",
    "Returns hour, minute, and second. hour [0-23] minute [0-59] second [0-61]",
    "trace",
    "trace",
    "Turn on the debugger.",
    "true",
    "true",
    "Goals are always successful.",
    "var",
    "var(X)",
    "Check if X is the assigned variable.",
    "write",
    "write(Term)/write(Handle,Term)",
    "Write to standard output device.Write the term in the specified file.",
    "writeq",
    "writeq(Term)/writeeq(Time,Term)",
    "Write to standard output device so that the term can be read as a Prolog term Enclose the atom and function in quotation marks.Write the term to the specified file so that the term can be read as a Prolog term Enclose the atom and function in quotation marks.",
    ";",
    ";",
    "Represents the separation between goals. Disjunction (OR).",
    ">",
    "E1 < E2",
    "Checks if the value of `E1` is less than the value of `E2`.",
    "=",
    "T1 = T2",
    "Attempts to unify `T1` and `T2`.",
    "\\=",
    "T1 \\= T2",
    "Fails if `T1` unifies with `T2`.",
    "=..",
    "Struct =.. List",
    "Known as \"univ\". Converts a structure to a list or a list to a structure.",
    "=<",
    "E1 =< E2",
    "Checks if the value of `E1` is less than or equal to the value of `E2`.",
    ">",
    "E1 > E2",
    "Checks if the value of `E1` is greater than the value of `E2`.",
    ">=",
    "E1 >= E2",
    "Checks if the value of `E1` is greater than or equal to the value of `E2`.",
    "=:=",
    "E1 =:= E2",
    "Checks if the value of `E1` is equal to the value of `E2`.",
    "=\\=",
    "E1 =\\= E2",
    "Checks if the value of `E1` is not equal to the value of `E2`.",
    "==",
    "T1 == T2",
    "Checks if `T1` and `T2` are identical (equivalent).",
    "\\==",
    "T1 \\== T2",
    "Checks if `T1` and `T2` are not identical (not equivalent).",
    "@<",
    "T1 @< T2",
    "Checks if `T1` precedes `T2`.",
    "@=<",
    "T1 @=< T2",
    "Checks if `T1` precedes `T2` or is equal to it.",
    "@>",
    "T1 @> T2",
    "Checks if `T1` succeeds `T2`.",
    "@>=",
    "T1 @>= T2",
    "Checks if `T1` succeeds `T2` or is equal to it.",
    "atom_concat",
    "atom_concat(E1, E2, X)",
    "Unifies X with the atom that results from concatenating atoms E1 and E2.",
    "append",
    "append(L1, L2, X)",
    "Unifies X with the list that results from concatenating lists L1 and L2.",
    "between",
    "between(start, end, Value)",
    "Unifies Value with integers from start to end",
    "char_code",
    "char_code(E, X)",
    "Unifies X with the internal code of character E.",
    "compile_file",
    "compile_file(fn)",
    "Compiles the Prolog code from the file fn and generates an object file.",
    "compound",
    "compound(E)",
    "Checks whether E is a compound term.",
    "ground",
    "ground(E)",
    "Checks whether E contains no uninstantiated variables.",
    "heapd",
    "heapd(start, end)",
    "Displays the heap region addresses from start to end.",
    "member",
    "member(E, L)",
    "Checks whether atom E is a member of the list L.",
    "measure",
    "measure(E)",
    "Measures and displays the execution time of the predicate E.",
    "predicate_property",
    "predicate_property(E, X)",
    "Unifies X with the properties of the predicate E.",
    "reverse",
    "reverse(L, X)",
    "Unifies X with the list that results from reversing the list L.",
    "bagof",
    "bagof(X, Pred, Bag)",
    "Collects all X that unify with the predicate Pred into the list Bag.",
    "setof",
    "setof(X, Pred, Bag)",
    "Collects all X that unify with the predicate Pred into the list Bag, with duplicates removed.",
    "findall",
    "findall(X, Pred, Bag)",
    "Collects all X that unify with the predicate Pred into the list Bag.",

};

#define NELEM(X) (sizeof(X) / sizeof((X)[0]))

int find_function_data(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(functions_data); i = i + 3) {
	if (strcmp(functions_data[i], str) == 0) {
	    return i;
	}
    }
    return -1;
}
