#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "npl.h"

//#define CHECK   1 //for parser debug check


int double_clause(int x)
{
    if (structurep(x) && car(x) == NECK && structurep(caddr(x)) && car(caddr(x)) == NECK)	// double :- 
	return (1);
    else
	return (0);
}

int readparse(int th)
{
    int res;

    paren_nest = 0;
    res = parser(NIL, NIL, NIL, NIL, 0, 0, th);
    if (paren_nest != 0) {
	exception(SYNTAX_ERR, makestr("extra paren"), NIL, th);
    }
    if (double_clause(res)) {
	exception(SYNTAX_ERR, makestr("require period"), res, th);
    }
    return (res);
}

/*
terminal 0= period is terminal, 1=
parsemode 0= comma is operator, 1= comma is separator
*/
int
parser(int operand, int operator, int weight, int spec, int terminal,
       int parsemode, int th)
{
    int temp, temp1, temp2, temp3, w1, w2;

    //for debug
#if CHECK
    printf("terminal %d, parsemode %d\n", terminal, parsemode);
    print(operand);
    print(operator);
    printf("\n");
#endif


    gettoken(th);
    if (stok.type == FILEEND) {	// end of file
	if (operand != NIL || operator != NIL)
	    exception(SYNTAX_ERR, makestr("expected period"), NIL, th);
	return (FEND);
    }
    if (terminal == 1
	&& (stok.type == PERIOD || (parsemode == 1 && stok.type == COMMA)
	    || stok.type == RBRACKET || stok.type == RPAREN || stok.type == RCURL || stok.type == VERTICAL)) {	//these are terminations
#if CHECK
	printf("terminate with terminalmode == 1\n");
#endif
	stok.flag = BACK;
	goto exit;
    }
    if (terminal == 0 && stok.type == PERIOD) {	//termination
#if CHECK
	printf("terminate with terminalmode == 0\n");
#endif
      exit:
	if (nullp(operator)) {
	    if (length(operand) != 1)
		exception(SYNTAX_ERR, makestr("expected operator"), NIL,
			  th);
	    else
		return (car(operand));
	} else {
	    if (length(operand) != 2)
		exception(SYNTAX_ERR, makestr("expected two operand"), NIL,
			  th);
	    else
		return (cons(car(operator), reverse(operand)));
	}
    }

    stok.flag = BACK;
    temp = readitem(th);

#if CHECK
    print(temp);
    printf("%d", GET_OPT(temp));
#endif

    if (terminal == 1 && infix_operator_p(temp) &&
	!mixturep(temp) && GET_CDR(temp) >= weight) {
#if CHECK
	printf("terminate with GET_CDR(%d)>=weight(%d)\n",
	       GET_CDR(temp), weight);
#endif
	unread = temp;
	goto exit;
    } else if (terminal == 1 && infix_operator_p(temp) &&
	       mixturep(temp) && get_2nd_weight(temp) >= weight &&
	       !(nullp(operand) && nullp(operator))) {
#if CHECK
	printf("terminate with get_2nd_weight(%d)>=weight(%d)\n",
	       get_2nd_weight(temp), weight);
#endif
	unread = temp;
	goto exit;
    }
    //operator as an atom
    if (parsemode == 1 && infix_operator_p(temp)) {
	gettoken(th);
	if ((parsemode == 1 && stok.type == COMMA) ||
	    stok.type == RBRACKET ||
	    stok.type == RPAREN || stok.type == RCURL
	    || stok.type == VERTICAL) {
#if CHECK
	    printf("terminate operator as an atom\n");
#endif
	    stok.flag = BACK;
	    return (temp);
	} else
	    stok.flag = BACK;

    }
    //prefix notation
    if (infix_operator_p(temp) &&
	length(operand) == length(operator) &&
	(stok.ch == '(' || stok.ch == NUL) && stok.ahead != ' ' &&
	GET_OPT(temp) != FX && GET_OPT(temp) != FY) {
	gettoken(th);
	if (stok.type == LPAREN) {
#if CHECK
	    printf("prefix notation\n");
#endif
	    temp1 = cons(temp, readparen(th));
	    temp2 =
		parser(cons(temp1, operand), operator, weight, spec,
		       terminal, parsemode, th);
	    prefix_flag = 1;
	    return (temp2);
	} else {
	    stok.flag = BACK;
	}
    }

    if (infix_operator_p(temp)
	&& (GET_OPT(temp) == FX || GET_OPT(temp) == FX_XFX
	    || GET_OPT(temp) == FX_XFY || GET_OPT(temp) == FX_YFX)
	&& length(operand) == length(operator)) {	//as FX
	if (GET_OPT(temp) == FX)
	    w1 = GET_CDR(temp);
	else
	    w1 = get_1st_weight(temp);

	if (mixturep(car(operator)))
	    w2 = get_2nd_weight(car(operator));
	else
	    w2 = GET_CDR(car(operator));

#if CHECK
	printf("fx %d %d\n", w1, w2);
#endif
	if (nullp(operator)) {
#if CHECK
	    printf("null operator\n");
#endif
	    if (w1 == 1200) {
		temp1 = parser(NIL, NIL, 1201, FX, 0, parsemode, th);
		return (list2(temp, temp1));
	    } else {
		temp1 = parser(NIL, NIL, w1, FX, 1, parsemode, th);
		return (parser
			(cons(list2(temp, temp1), operand), operator,
			 weight, spec, terminal, parsemode, th));
	    }
	} else if (w1 < w2) {
#if CHECK
	    printf("s1 < w2\n");
#endif
	    temp1 =
		list2(temp, parser(NIL, NIL, w1, FX, 1, parsemode, th));
	    return (parser
		    (cons(temp1, operand), operator, weight, spec,
		     terminal, parsemode, th));
	}
    } else if (infix_operator_p(temp)
	       && (GET_OPT(temp) == FY || GET_OPT(temp) == FY_XFX
		   || GET_OPT(temp) == FY_XFY || GET_OPT(temp) == FY_YFX)
	       && length(operand) == length(operator)) {	//as FY
	if (GET_OPT(temp) == FY)
	    w1 = GET_CDR(temp);
	else
	    w1 = get_1st_weight(temp);

#if CHECK
	printf("fy %dn", w1);
#endif
	temp1 = parser(NIL, NIL, w1 + 1, FY, 1, parsemode, th);
	if (temp == makeatom("-", OPE) && numberp(temp1))
	    temp2 = mult(temp1, makeint(-1), 0);
	else
	    temp2 = list2(temp, temp1);

	return (parser
		(cons(temp2, operand), operator, weight, spec, terminal,
		 parsemode, th));
    } else if (infix_operator_p(temp) &&
	       (GET_OPT(temp) == XFX ||
		GET_OPT(temp) == FX_XFX || GET_OPT(temp) == FY_XFX)) {
	if (GET_OPT(temp) == XFX)
	    w1 = GET_CDR(temp);
	else
	    w1 = get_2nd_weight(temp);

	if (mixturep(car(operator)))
	    w2 = get_2nd_weight(car(operator));
	else
	    w2 = GET_CDR(car(operator));

#if CHECK
	printf("xfx %d %d\n", w1, w2);
#endif

	if (nullp(operator)) {
#if CHECK
	    printf("null operator\n");
#endif
	    return (parser
		    (operand, cons(temp, operator), weight, spec, terminal,
		     parsemode, th));
	} else if (w1 == w2) {
#if CHECK
	    printf("w1 == w2\n");
#endif
	    temp1 =
		list3(temp, car(operand),
		      parser(NIL, NIL, w1, XFX, 1, parsemode, th));
	    return (parser
		    (cons(temp1, cdr(operand)), operator, weight, spec,
		     terminal, parsemode, th));
	} else if (w1 < w2) {
#if CHECK
	    printf("w1 < w2\n");
#endif
	    temp1 = parser(NIL, NIL, w1, XFX, 1, parsemode, th);
	    if (stok.type == RPAREN) {
		temp2 = list3(temp, car(operand), temp1);
		temp3 = list3(car(operator), cadr(operand), temp2);
		return (temp3);
	    } else {
		temp2 = list3(temp, car(operand), temp1);
		return (parser
			(cons(temp2, cdr(operand)), operator, weight, spec,
			 terminal, parsemode, th));
	    }
	} else {
#if CHECK
	    printf("w1 > w2\n");
#endif
	    temp1 = cons(car(operator), reverse(operand));
	    return (parser
		    (list1(temp1), cons(temp, cdr(operator)), weight, spec,
		     terminal, parsemode, th));
	}
    } else if (infix_operator_p(temp) &&
	       (GET_OPT(temp) == YFX ||
		GET_OPT(temp) == FX_YFX || GET_OPT(temp) == FY_YFX)) {
	if (GET_OPT(temp) == YFX)
	    w1 = GET_CDR(temp);
	else
	    w1 = get_2nd_weight(temp);

	if (mixturep(car(operator)))
	    w2 = get_2nd_weight(car(operator));
	else
	    w2 = GET_CDR(car(operator));

#if CHECK
	printf("yfx %d %d\n", w1, w2);
#endif
	if (nullp(operator)) {
#if CHECK
	    printf("null operator\n");
#endif
	    temp1 =
		parser(operand, cons(temp, operator), w1, YFX, 1,
		       parsemode, th);
	    return (parser
		    (list1(temp1), NIL, weight, spec, terminal,
		     parsemode, th));
	} else if (w1 == w2) {
#if CHECK
	    printf("s1 == w2\n");
#endif
	    temp1 = parser(NIL, NIL, w1, YFX, 1, parsemode, th);
	    temp2 =
		list3(temp, cons(car(operator), reverse(operand)), temp1);
	    return (parser
		    (list1(temp2), NIL, weight, spec, terminal,
		     parsemode, th));
	} else if (w1 < w2) {
#if CHECK
	    printf("s1 < w2\n");
#endif
	    temp1 = parser(NIL, NIL, w1, YFX, 1, parsemode, th);
	    temp2 = list3(temp, car(operand), temp1);
	    return (parser
		    (cons(temp2, cdr(operand)), operator, weight, spec,
		     terminal, parsemode, th));
	} else {
#if CHECK
	    printf("s1 > w2\n");
#endif
	    temp1 = cons(car(operator), reverse(operand));
	    return (parser
		    (list1(temp1), cons(temp, cdr(operator)), weight, spec,
		     terminal, parsemode, th));
	}
    } else if (infix_operator_p(temp) &&
	       (GET_OPT(temp) == XFY ||
		GET_OPT(temp) == FX_XFY || GET_OPT(temp) == FY_XFY)) {
	if (GET_OPT(temp) == XFY)
	    w1 = GET_CDR(temp);
	else
	    w1 = get_2nd_weight(temp);

	if (mixturep(car(operator)))
	    w2 = get_2nd_weight(car(operator));
	else
	    w2 = GET_CDR(car(operator));

#if CHECK
	printf("xfy %d %d\n", w1, w2);
#endif
	if (nullp(operator)) {
#if CHECK
	    printf("null operator\n");
#endif
	    return (parser
		    (operand, cons(temp, operator), weight, XFY, terminal,
		     parsemode, th));
	} else if (w1 == w2) {
#if CHECK
	    printf("w1 == w2\n");
#endif
	    temp1 =
		parser(list1(car(operand)), list1(temp), w1 + 1, XFY, 1,
		       parsemode, th);
	    temp2 = list3(car(operator), cadr(operand), temp1);
	    return (parser
		    (list1(temp2), NIL, weight, spec, terminal,
		     parsemode, th));
	} else if (w1 < w2) {
#if CHECK
	    printf("w1 < w2\n");
#endif
	    temp1 =
		parser(list1(car(operand)), list1(temp), w1 + 1, XFY, 1,
		       parsemode, th);
	    if (stok.type == RPAREN) {
		temp2 = list3(car(operator), cadr(operand), temp1);
		return (parser
			(list1(temp2), NIL, weight, spec, terminal,
			 parsemode, th));
	    } else {
		return (parser
			(cons(temp1, cdr(operand)), operator, weight, spec,
			 terminal, parsemode, th));
	    }
	} else {
#if CHECK
	    printf("w1 > w2\n");
#endif
	    temp1 = cons(car(operator), reverse(operand));
	    temp2 =
		parser(list1(temp1), list1(temp), w1 + 1, XFY, 1,
		       parsemode, th);
	    return (parser
		    (list1(temp2), cdr(operator), weight, spec, terminal,
		     parsemode, th));
	}
    } else if (infix_operator_p(temp) &&
	       (GET_OPT(temp) == XF ||
		GET_OPT(temp) == FX_XF || GET_OPT(temp) == FY_XF)) {

	if (GET_OPT(temp) == XF)
	    w1 = GET_CDR(temp);
	else
	    w1 = get_1st_weight(temp);

	if (mixturep(car(operator)))
	    w2 = get_2nd_weight(temp);
	else
	    w2 = GET_CDR(temp);

#if CHECK
	printf("xf %d %d\n", w1, w2);
#endif
	if (nullp(operator)) {
#if CHECK
	    printf("null operator\n");
#endif
	    temp1 = list2(temp, car(operand));
	    return (parser
		    (cons(temp1, NIL), operator, weight, spec, terminal,
		     parsemode, th));
	} else if (w1 < w2) {
#if CHECK
	    printf("w1 < w2\n");
#endif
	    temp1 = list2(temp, car(operand));
	    return (parser
		    (cons(temp1, cdr(operand)), operator, weight, spec,
		     terminal, parsemode, th));
	} else {
#if CHECK
	    printf("w1 > w2\n");
#endif
	    temp1 = cons(car(operator), reverse(operand));
	    temp2 = list2(temp, temp1);
	    return (parser
		    (cons(temp2, NIL), NIL, weight, spec, terminal,
		     parsemode, th));
	}
    } else if (infix_operator_p(temp) &&
	       (GET_OPT(temp) == YF ||
		GET_OPT(temp) == FX_YF || GET_OPT(temp) == FY_YF)) {

#if CHECK
	printf("yf\n");
#endif
	temp1 = list2(temp, car(operand));
	return (parser
		(cons(temp1, cdr(operand)), operator, weight, spec,
		 terminal, parsemode, th));
    } else {			//operand
	if (temp == RIGHTPAREN) {
	    stok.flag = BACK;
	    goto exit;
	} else if (temp == LEFTPAREN) {
	    paren_nest++;
	    //check (operator) ex (*)
	    gettoken(th);
	    if (stok.ahead == ')') {
		stok.flag = BACK;
		temp1 = readitem(th);
		gettoken(th);	//discard ')'
		paren_nest--;
		return (parser
			(cons(temp1, operand), operator, weight, spec,
			 terminal, parsemode, th));
	    }
	    stok.flag = BACK;
	    //comma is operator
	    temp1 = parser(NIL, NIL, 1201, NIL, 0, 0, th);
	    gettoken(th);	//discard RPAREN
	    paren_nest--;
	    return (parser
		    (cons(temp1, operand), operator, weight, spec,
		     terminal, parsemode, th));
	} else {
	    if (length(operand) >= 2)
		exception(SYNTAX_ERR, makestr("expected operator"), temp,
			  th);

	    return (parser
		    (cons(temp, operand), operator, weight, spec, terminal,
		     parsemode, th));
	}
    }

    return (NIL);
}


//-------readitem()--------

int readc(void)
{
    int c;

    if (bridge_flag == 1)
	return (read_string_term(1));
    else if (input_stream == standard_input && repl_flag)
	c = read_line(0);
    else
	c = getc(GET_PORT(input_stream));

    if (c == EOL) {
	line++;
	column = 0;
    } else
	column++;

    return (c);
}

void unreadc(char c)
{
    if (bridge_flag == 1) {
	read_string_term(-1);
	return;
    }

    if (c == EOL)
	line--;
    else
	column--;
    if (input_stream == standard_input && repl_flag)
	c = read_line(-1);
    else
	ungetc(c, GET_PORT(input_stream));
}

#define SETBUF(c) {                        \
	if(pos >= BUFSIZE-1)                     \
	exception(RESOURCE_ERR, makestr("gettoken"), NIL,0); \
	stok.buf[pos++] = c;                   \
}

#define SETBUFEND(c) {                        \
	if(pos >= BUFSIZE-1)                     \
	exception(RESOURCE_ERR, makestr("gettoken"), NIL,0); \
	stok.buf[pos] = c;                   \
}



void gettoken(int th)
{
    int c, c1, pos, i;

    stok.space = NOTSKIP;
    if (stok.flag == BACK) {
	stok.flag = GO;
	return;
    }

    if (stok.ch == ')') {
	stok.type = RPAREN;
	stok.ch = NUL;
	stok.ahead = NUL;
	return;
    }

    if (stok.ch == '(') {
	stok.type = LPAREN;
	stok.ch = NUL;
	stok.ahead = NUL;
	return;
    }

    if (stok.ch == '[') {
	stok.type = LBRACKET;
	stok.ch = NUL;
	stok.ahead = NUL;
	return;
    }

    if (stok.ch == ']') {
	stok.type = RBRACKET;
	stok.ch = NUL;
	stok.ahead = NUL;
	return;
    }

    if (stok.ch == '|') {
	stok.type = VERTICAL;
	stok.ch = NUL;
	stok.ahead = NUL;
	return;
    }


    if (stok.ch == '.') {
	c = readc();
	if (c <= ' ') {
	    stok.type = PERIOD;
	    unreadc(c);
	    stok.ch = NUL;
	    stok.ahead = NUL;
	    return;
	} else if (c == '.') {
	    stok.buf[0] = '.';
	    stok.buf[1] = '.';
	    stok.buf[2] = NUL;
	    stok.type = ATOMOBJ;
	    stok.ch = NUL;
	    stok.ahead = NUL;
	    return;
	} else {
	    unreadc(c);
	}
    }


    if (stok.ch != NUL) {
	c = stok.ch;
	stok.ch = NUL;
	stok.ahead = NUL;
    } else {
	c = readc();
    }

    //ignore ctrl+c pause or resume signal from parent
    if (c == 0x11 || c == 0x12 || c == 0x13) {
	c = readc();
    }

  skip:
    while (c == SPACE || c == EOL || c == TAB || c == RET) {
	c = readc();
	stok.space = SKIP;
    }
    //skip comment line
    //when EOF is at line end, return FILEEND object
    if (c == '%') {
	while (!(c == EOL)) {
	    c = readc();
	    if (c == EOF) {
		stok.type = FILEEND;
		return;
	    }
	}
	stok.ch = NUL;
	goto skip;
    }
    //comment /*    */
    if (c == '/') {
	c = readc();
	if (c == '*') {
	  reskip:
	    c = readc();
	    while (c != '*') {
		c = readc();
	    }
	    c = readc();
	    if (c != '/')
		goto reskip;
	    else {
		c = readc();
		goto skip;
	    }
	} else {
	    unreadc(c);
	    c = '/';
	}
    }
    //when end of file, return FILEEND object
    if (c == EOF) {
	stok.type = FILEEND;
	return;
    }

    switch (c) {
    case '(':
	stok.type = LPAREN;
	return;
    case ')':
	stok.type = RPAREN;
	return;
    case '[':
	stok.type = LBRACKET;
	return;
    case ']':
	stok.type = RBRACKET;
	return;
    case '|':
	stok.type = VERTICAL;
	return;
    case '{':
	c1 = readc();
	if (c1 == '}') {
	    stok.buf[0] = '{';
	    stok.buf[1] = '}';
	    stok.buf[2] = NUL;
	    stok.type = ATOMOBJ;
	    return;
	}
	unreadc(c1);
	stok.type = LCURL;
	return;
    case '}':
	stok.type = RCURL;
	return;
    case ',':
	stok.type = COMMA;
	return;
    case ';':
	stok.type = SEMICOLON;
	return;
    case '.':
	c = readc();
	if (c <= ' ') {
	    stok.type = PERIOD;
	    unreadc(c);
	    return;
	} else {
	    stok.type = DOT;
	    unreadc(c);
	    return;
	}
    }
    //variant
    if (c == 'v') {
	c = readc();
	if (c == '_') {
	    pos = 0;
	    c = readc();
	    while (isdigit(c)) {
		SETBUF(c) c = readc();
	    }
	    SETBUFEND(NUL) stok.type = VARIANT;
	    stok.ch = c;
	    stok.ahead = c;
	    return;
	}
	unreadc(c);
	c = 'v';
    }
    //constant-atom in Unicode
    if (islower(c) || unicodep(c)) {
	pos = 0;
	while ((isalpha(c) || isdigit(c) || c == '_' ||
		unicodep(c)) && !isatomch(c)) {

	    SETBUF(c) if (isUni2(c)) {
		c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni3(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni4(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni5(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni6(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else
		c = readc();
	}
	SETBUFEND(NUL) stok.ch = c;
	stok.ahead = c;
	for (i = 0; i < OPERATOR_NUMBER; i++) {
	    if (strcmp(operator[i], stok.buf) == 0) {
		stok.type = OPERATOR;
		return;
	    }
	}
	for (i = 0; i < FUNCTION_NUMBER; i++) {
	    if (strcmp(function[i], stok.buf) == 0) {
		stok.type = FUNCTION;
		return;
	    }
	}
	for (i = 0; i < BUILTIN_NUMBER; i++) {
	    if (strcmp(builtin[i], stok.buf) == 0) {
		stok.type = BUILTIN;
		return;
	    }
	}
	for (i = 0; i < COMPILED_NUMBER; i++) {
	    if (strcmp(compiled[i], stok.buf) == 0) {
		stok.type = BUILTIN;
		return;
	    }
	}
	stok.type = ATOMOBJ;
	return;
    }
    //variable
    if (isupper(c)) {
	pos = 0;
	SETBUF(c) c = readc();
	while (isalpha(c) || isdigit(c) || c == '_') {
	    SETBUF(c) c = readc();
	}
	SETBUFEND(NUL) stok.type = VARIABLE;
	stok.ch = c;
	stok.ahead = c;
	return;
    }
    //cut operator
    if (c == '!') {
	pos = 0;
	SETBUF(c) SETBUFEND(NUL) stok.type = BUILTIN;
	stok.ch = NUL;
	stok.ahead = NUL;
	return;
    }
    //variable in Unicode 
    if (c == '_') {
	pos = 0;
	SETBUF(c) c = readc();
	while (isalpha(c) || isdigit(c) || c == '_' || unicodep(c)) {
	    SETBUF(c) if (isUni2(c)) {
		c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni3(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni4(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni5(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else if (isUni6(c)) {
		c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
		SETBUF(c) c = readc();
	    } else
		c = readc();
	}
	SETBUFEND(NUL) if (pos == 1) {
	    stok.type = ANOYMOUS;
	    stok.ch = c;
	    stok.ahead = c;
	    return;
	} else {
	    stok.type = VARIABLE;
	    stok.ch = c;
	    stok.ahead = c;
	    return;
	}
    }
    //special atom
    if (c == '\'') {
	pos = 0;
      redo:
	c = readc();
	while (c != '\'') {
	    if (c == EOL)
		exception(SYNTAX_ERR,
			  makestr("unexpected EOL in quoted atom"), NIL,
			  th);

	    if (c == EOF)
		exception(SYNTAX_ERR,
			  makestr("unexpected EOF in quoted atom"), NIL,
			  th);

	    if (c == '\\') {
		c = readc();
		if (c == EOL) {
		    //skip eol
		    goto redo;
		} else if (c == '\"' || c == '\\' || c == '\'' || c == '`')
		    stok.buf[pos++] = '\\';
		else if (c == 'a' || c == 'b' || c == 'f' ||
			 c == 'n' || c == 'r' || c == 't' || c == 'v') {
		    stok.buf[pos++] = '\\';
		} else {
		    exception(SYNTAX_ERR,
			      makestr("illegal token in quoted atom"), NIL,
			      th);
		}
	    }

	    SETBUF(c) c = readc();
	}
	c = readc();
	if (c == '\'') {	// case ex 'let''s' -> let's
	    SETBUF(c) goto redo;
	} else
	    unreadc(c);

	SETBUFEND(NUL) stok.ch = NUL;
	stok.ahead = c;
	for (i = 0; i < FUNCTION_NUMBER; i++) {
	    if (strcmp(function[i], stok.buf) == 0) {
		stok.type = FUNCTION;
		return;
	    }
	}
	for (i = 0; i < BUILTIN_NUMBER; i++) {
	    if (strcmp(builtin[i], stok.buf) == 0) {
		stok.type = BUILTIN;
		return;
	    }
	}

	for (i = 0; i < COMPILED_NUMBER; i++) {
	    if (strcmp(compiled[i], stok.buf) == 0) {
		stok.type = COMPILED;
		return;
	    }
	}
	stok.type = ATOMOBJ;
	return;
    }
    //string
    //ARITY/PROLOG mode
    if (c == '$' && !string_flag) {
	pos = 0;
	c = readc();
	while (c != '$') {
	    if (c == '\\') {
		SETBUF(c)
		    c = readc();
		SETBUF(c);
	    } else if (c == EOF)
		exception(SYNTAX_ERR, makestr("not exist right $ in file"),
			  NIL, th);
	    else {
		SETBUF(c)
	    }
	    c = readc();
	}
	SETBUFEND(NUL) stok.type = STRING;
	stok.ch = NUL;
	stok.ahead = c;
	return;
    }
    //ISO-Prolog mode
    if (c == '"' && string_flag) {
	pos = 0;
	c = readc();
	while (c != '"') {
	    if (c == '\\') {
		SETBUF(c);
		c = readc();
		SETBUF(c);
	    } else if (c == EOF)
		exception(SYNTAX_ERR,
			  makestr("not exist right \" in file"), NIL, th);
	    else {
		SETBUF(c)
	    }
	    c = readc();
	}
	SETBUFEND(NUL) stok.type = STRING;
	stok.ch = NUL;
	stok.ahead = c;
	return;
    }

    if (c == '`')
	exception(SYNTAX_ERR, makestr("illegal token back quote"), NIL,
		  th);


    //number octal ex 0o12345
    //number binaly ex 0b10110101
    //number hexadecimal ex 0x89ABC
    if (c == '0') {
	c = readc();
	if (c == 'o') {
	    pos = 0;
	    c = readc();
	    while (isoctch(c)) {
		SETBUF(c) c = readc();
	    }
	    SETBUFEND(NUL) stok.type = OCTNUM;
	    stok.ch = c;
	    return;
	} else if (c == 'b') {
	    pos = 0;
	    c = readc();
	    while (isbinch(c)) {
		SETBUF(c) c = readc();
	    }
	    SETBUFEND(NUL) stok.type = BINNUM;
	    stok.ch = c;
	    return;
	} else if (c == 'x') {
	    pos = 0;
	    c = readc();
	    while (ishexch(c)) {
		SETBUF(c) c = readc();
	    }
	    SETBUFEND(NUL) stok.type = HEXNUM;
	    stok.ch = c;
	    return;
	} else if (c == '\'') {
	    c = readc();
	    if (c != '\\') {
		stok.buf[0] = c;
		stok.type = CHARCODE;
		return;
	    } else {		/* ex 0'\141\ or 0'\x97\ */
		c = readc();
		if (c == 'n') {
		    stok.buf[0] = EOL;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 't') {
		    stok.buf[0] = TAB;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 'f') {
		    stok.buf[0] = FF;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 'r') {
		    stok.buf[0] = CR;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 'v') {
		    stok.buf[0] = VT;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 'a') {
		    stok.buf[0] = BEL;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 'b') {
		    stok.buf[0] = BS;
		    stok.type = CHARCODE;
		    return;
		} else if (c == 'x') {
		    i = 0;
		    c = readc();
		    while (c != '\\') {
			if (!ishexch(c))
			    exception(SYNTAX_ERR,
				      makestr("illegal hex char"), NIL,
				      th);
			stok.buf[i] = c;
			c = readc();
			if (c == EOL)
			    exception(SYNTAX_ERR,
				      makestr("unexpected EOL"), NIL, th);
			i++;
		    }
		    stok.buf[i] = NUL;
		    stok.type = HEXNUM;
		    return;
		} else if (isdigit(c)) {
		    i = 0;
		    while (c != '\\') {
			if (!isoctch(c))
			    exception(SYNTAX_ERR,
				      makestr("illegal oct char"), NIL,
				      th);
			stok.buf[i] = c;
			c = readc();
			if (c == EOL)
			    exception(SYNTAX_ERR,
				      makestr
				      ("unexpected EOL in oct char"), NIL,
				      th);
			i++;
		    }
		    stok.buf[i] = NUL;
		    stok.type = OCTNUM;
		    return;
		} else
		    exception(SYNTAX_ERR, makestr("illegal number token"),
			      NIL, th);
	    }
	} else {
	    unreadc(c);
	    c = '0';
	    unreadc(c);
	}
    }
    //number
    if (isdigit(c)) {
	pos = 0;
	SETBUF(c) c = readc();
	while (isdigit(c)) {
	    SETBUF(c) c = readc();
	}
	if (c == '.') {
	    c = readc();
	    if (c == '.') {
		unreadc(c);
		c = '.';
		goto integer1;
	    } else {
		unreadc(c);
		c = '.';
		goto float1;
	    }
	}
	if (c == 'E' || c == 'e')
	    exception(SYNTAX_ERR, makestr("float number expected dot"),
		      NIL, th);

      integer1:
	SETBUFEND(NUL)
	    if (strlen(stok.buf) <= 9)
	    stok.type = INTEGER;
	else if (strlen(stok.buf) <= 19)
	    stok.type = LONGNUM;
	else
	    stok.type = BIGNUM;
	stok.ch = c;
	return;

      float1:
	SETBUF(c) c = readc();
	if (!isdigit(c)) {	//2. -> 2(integer) + .DOT
	    pos--;
	    SETBUFEND(NUL)
		if (strlen(stok.buf) <= 9)
		stok.type = INTEGER;
	    else if (strlen(stok.buf) <= 19)
		stok.type = LONGNUM;
	    else
		stok.type = BIGNUM;
	    unreadc(c);
	    stok.ch = '.';
	    stok.ahead = '.';
	    return;
	}

	while (isdigit(c)) {
	    SETBUF(c) c = readc();
	}
	if (c == 'E' || c == 'e')
	    goto float2;

	SETBUFEND(NUL) stok.type = FLOATN;
	stok.ch = c;
	stok.ahead = c;
	return;

      float2:
	SETBUF(c) c = readc();
	if (c != '+' && c != '-' && !isdigit(c)) {
	    SETBUF(c)
		SETBUFEND(NUL)
		exception(SYNTAX_ERR, makestr("illegal float token"),
			  NIL, th);
	}
	SETBUF(c) c = readc();
	while (isdigit(c)) {
	    SETBUF(c) c = readc();
	}
	SETBUFEND(NUL) stok.type = FLOATN;
	stok.ch = c;
	stok.ahead = c;
	return;
    }
    //operator
    if (isatomch(c)) {
	pos = 0;
	while (isatomch(c)) {
	    SETBUF(c) c = readc();
	}
	SETBUFEND(NUL) stok.ch = c;
	stok.ahead = c;

	for (i = 0; i < OPERATOR_NUMBER; i++) {
	    if (strcmp(operator[i], stok.buf) == 0) {
		stok.type = OPERATOR;
		return;
	    }
	}
	for (i = 0; i < FUNCTION_NUMBER; i++) {
	    if (strcmp(function[i], stok.buf) == 0) {
		stok.type = FUNCTION;
		return;
	    }
	}
	for (i = 0; i < BUILTIN_NUMBER; i++) {
	    if (strcmp(builtin[i], stok.buf) == 0) {
		stok.type = BUILTIN;
		return;
	    }
	}
	for (i = 0; i < COMPILED_NUMBER; i++) {
	    if (strcmp(compiled[i], stok.buf) == 0) {
		stok.type = COMPILED;
		return;
	    }
	}

	stok.type = ATOMOBJ;
	return;

    }
	printf("%d ", stok.buf[0]);
    exception(SYNTAX_ERR, makestr("illegal token"), makestr(stok.buf), th);
}


int isoctch(char c)
{
    switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
	return (1);
    default:
	return (0);

    }
}

int isbinch(char c)
{
    switch (c) {
    case '0':
    case '1':
	return (1);
    default:
	return (0);
    }
}

int ishexch(char c)
{
    switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
	return (1);
    default:
	return (0);
    }
}

int isatomch(char c)
{
    switch (c) {
    case '#':
	//case '$':
    case '&':
    case '*':
    case '+':
    case '-':
    case '/':
    case ':':
    case '.':
    case '<':
    case '=':
    case '>':
    case '?':
    case '@':
    case '^':
    case '~':
    case '\\':
	return (1);
    default:
	return (0);
    }
}

int readitem(int th)
{
    int res;
    res = readitem1(th);
    // '.'(1,'.'(2,[])) -> [1,2]
    if (operationp(res) && car(res) == DOTOBJ)
	res = operate(res, 0);

    return (res);
}

int readitem1(int th)
{
    int temp, temp1;
    char *e, str[ATOMSIZE];

    if (unread != NIL) {
	temp = unread;
	unread = NIL;
	return (temp);
    }

    gettoken(th);
#if CHECK
    printf("call gettoken from readitem and catch %s\n", stok.buf);
#endif
    switch (stok.type) {
    case COMMA:
	return (AND);
    case SEMICOLON:
	return (OR);
    case LPAREN:
	return (LEFTPAREN);
    case RPAREN:
	return (RIGHTPAREN);
    case LCURL:
	return (list2(NCURL, readcurl(th)));
    case OPERATOR:
	return (makeatom(stok.buf, OPE));
    case DOT:
	gettoken(th);
	if (stok.type == LPAREN) {
	    temp = readparen(th);
	    return (cons(DOTOBJ, temp));
	} else {
	    stok.flag = BACK;
	    return (DOTOBJ);
	}
    case BUILTIN:
	temp = makeatom(stok.buf, SYS);
	if (temp == makesys("="))
	    return (temp);
	gettoken(th);
	if (stok.type == LPAREN) {
	    if (stok.space == SKIP) {
		stok.flag = BACK;
		return (temp);
	    }

	    temp1 = readparen(th);
	    return (cons(temp, temp1));
	} else if (strcmp(stok.buf, "/") == 0) {
	    temp1 = readitem(th);
	    return (list3(SLASH, temp, temp1));
	} else {
	    stok.flag = BACK;
	    return (temp);
	}
    case COMPILED:
	temp = makeatom(stok.buf, COMP);
	gettoken(th);
	if (stok.type == LPAREN) {
	    if (stok.space == SKIP)
		exception(SYNTAX_ERR,
			  makestr("illegal compiled predicate"), temp, th);

	    temp1 = readparen(th);
	    return (cons(temp, temp1));
	} else {
	    stok.flag = BACK;
	    return (temp);
	}
    case FUNCTION:
	temp = makeatom(stok.buf, FUNC);
	gettoken(th);
	if (stok.type == LPAREN) {
	    if (stok.space == SKIP)
		exception(SYNTAX_ERR, makestr("illegal function"), temp,
			  th);

	    temp1 = readparen(th);
	    return (cons(temp, temp1));
	} else {
	    stok.flag = BACK;
	    return (temp);
	}
    case VERTICAL:
	return (makeatom("|", SIMP));
    case INTEGER:
	return (makeint(atoi(stok.buf)));
    case OCTNUM:
	if (strtol(stok.buf, &e, 8) < 1000000000)
	    return (makeint(strtol(stok.buf, &e, 8)));
	else
	    return (makeoctbigx(stok.buf));
    case BINNUM:
	if (strtol(stok.buf, &e, 2) < 1000000000)
	    return (makeint(strtol(stok.buf, &e, 2)));
	else
	    return (makebinbigx(stok.buf));
    case HEXNUM:
	if (strtol(stok.buf, &e, 16) < 1000000000)
	    return (makeint(strtol(stok.buf, &e, 16)));
	else
	    return (makehexbigx(stok.buf));
    case FLOATN:
	return (makeflt(atof(stok.buf)));
    case LONGNUM:
	return (makelong(atol(stok.buf)));
    case BIGNUM:
	if (open_flag)
	    return (bigx_to_parmanent(makebigx(stok.buf)));
	else
	    return (makebigx(stok.buf));
    case CHARCODE:
	return (makeint(stok.buf[0]));
    case ATOMOBJ:
	strcpy(str, stok.buf);
	if (stok.ch == EOL || stok.ch == CR)
	    goto elseexit1;

	gettoken(th);
	if (stok.type == LPAREN) {
	    if (getatom(str, SYS, hash(str)))
		temp = makeatom(str, SYS);
	    else if (getatom(str, COMP, hash(str)))
		temp = makeatom(str, COMP);
	    else if (getatom(str, OPE, hash(str)))
		temp = makeatom(str, OPE);
	    else if (getatom(str, USER, hash(str)))
		goto elseexit;
	    else
		temp = makeatom(str, PRED);

	    if (stok.space == SKIP)
		exception(SYNTAX_ERR, makestr("illegal predicate"), temp,
			  th);

	    temp1 = readparen(th);
	    prefix_flag = 1;
	    return (cons(temp, temp1));
	} else if (strcmp(stok.buf, "/") == 0) {
	    if (getatom(str, SYS, hash(str)))
		temp = makeatom(str, SYS);
	    else if (getatom(str, COMP, hash(str)))
		temp = makeatom(str, COMP);
	    else if (getatom(str, OPE, hash(str)))
		temp = makeatom(str, OPE);
	    else if (getatom(str, USER, hash(str)))
		temp = makeatom(str, USER);
	    else
		temp = makeatom(str, PRED);

	    temp1 = readitem(th);
	    return (list3(SLASH, temp, temp1));
	} else {
	  elseexit:
	    stok.flag = BACK;
	  elseexit1:
	    if (getatom(str, COMP, hash(str)))
		temp = makeatom(str, COMP);
	    else if (getatom(str, PRED, hash(str)))
		temp = makeatom(str, PRED);
	    else if (getatom(str, SYS, hash(str)))
		temp = cons(makeatom(str, SYS), NIL);
	    else if (getatom(str, USER, hash(str)))
		temp = makeatom(str, USER);
	    else
		temp = makeatom(str, SIMP);
	    return (temp);
	}
    case VARIABLE:
	temp = makeatom(stok.buf, VAR);
	if (!break_flag) {
	    SET_CAR(temp, UNBIND);	//value
	    SET_CDR(temp, UNBIND);	//alpha variable
	} else if (break_flag && !memberp(temp, variables[0])) {
	    /* In the execution of break/0, 
	     * the unification of the variables up to that point must be maintained. 
	     * However, the values of the new variables generated in break/0 should not be retained.
	     */
	    SET_CAR(temp, UNBIND);	//value
	    SET_CDR(temp, UNBIND);	//alpha variable
	}
	SET_VAR(temp, NIL);
	return (temp);
    case ANOYMOUS:
	return (makeatom(stok.buf, ANOY));
    case VARIANT:
	temp = atoi(stok.buf);
	temp = temp + CELLSIZE;
	return (temp);
    case STRING:
	return (makestr(stok.buf));
    case LBRACKET:
	temp = readlist(th);
	if (!nullp(temp))
	    SET_AUX(temp, LIST);
	return (temp);
	/*
	   case DBLQUOTE:
	   temp = readdouble(th);
	   if (!nullp(temp))
	   SET_AUX(temp, LIST);
	   return (temp);
	 */
    case FILEEND:
	return (FEND);
    default:
	break;
    }
    exception(SYSTEM_ERR, makestr(stok.buf), NIL, th);
    return (0);
}


int readparen(int th)
{
    int car, cdr;

    gettoken(th);
    if (stok.type == RPAREN)
	return (NIL);
    else if (stok.type == LPAREN) {	//assert((foo(X) :- boo(X))).
	gettoken(th);		//atom as operand ex (*)
	if (stok.ahead == ')') {
	    paren_nest++;
	    stok.flag = BACK;
	    car = readitem(th);
	    goto next;
	}
	stok.flag = BACK;
	paren_nest++;
	car = parser(NIL, NIL, 1201, NIL, 0, 0, th);
      next:
	gettoken(th);		//discard ')'
	paren_nest--;
	gettoken(th);		//read-ahead

	if (stok.type == PERIOD) {
	    exception(SYNTAX_ERR, makestr("not enough right paren"), NIL,
		      th);
	} else if (stok.type == COMMA || stok.type == RPAREN) {
	    stok.flag = BACK;
	} else {		// for example (*)=(*)
	    stok.flag = BACK;
	    //comma as separater
	    car = parser(list1(car), NIL, 1201, NIL, 1, 1, th);
	}
    } else {
	stok.flag = BACK;
	//comma as separater
	prefix_flag = 0;
	car = parser(NIL, NIL, 1201, NIL, 1, 1, th);
	if ((operationp(car) || user_operation_p(car)) &&
	    heavy999p(GET_CAR(car)) && prefix_flag != 1)
	    exception(SYNTAX_ERR, makestr("expected ( )"), car, th);

    }

  repeat:
    gettoken(th);
    if (stok.type == PERIOD) {
	exception(SYNTAX_ERR, makestr("not enough right paren"), NIL, th);
    } else if (stok.type == COMMA) {
	cdr = readparen(th);
	return (cons(car, cdr));
    } else if (stok.type == RPAREN) {
	return (cons(car, NIL));
    } else if (stok.type != RCURL && stok.type != VERTICAL &&
	       stok.type != RBRACKET) {
	stok.flag = BACK;
	car = parser(list1(car), NIL, 1201, NIL, 1, 1, th);
	goto repeat;
    } else {
	exception(SYNTAX_ERR, makestr("illegal paren"), NIL, th);
    }
    return (NIL);
}



int readlist(int th)
{
    int car, cdr, temp;

    gettoken(th);
    if (stok.type == RBRACKET)
	return (NIL);
    else if (stok.type == LBRACKET) {
	car = readlist(th);
    } else if (stok.type == LPAREN) {
	gettoken(th);		//operator as operand ex (*)
	if (stok.ahead == ')') {
	    stok.flag = BACK;
	    car = readitem(th);
	    goto next;
	}
	stok.flag = BACK;
	//comma as operator
	paren_nest++;
	car = parser(NIL, NIL, 1201, NIL, 0, 0, th);
      next:
	gettoken(th);		//discard ')'
	paren_nest--;
	gettoken(th);		//read-ahead
	if (stok.type == COMMA || stok.type == RBRACKET ||
	    stok.type == VERTICAL) {
	    stok.flag = BACK;
	} else {		// for example (*)=(*)
	    stok.flag = BACK;
	    //comma as separater
	    car = parser(list1(car), NIL, 1201, NIL, 1, 1, th);
	}
    } else {
	stok.flag = BACK;
	//comma as separater
	prefix_flag = 0;
	car = parser(NIL, NIL, 1201, NIL, 1, 1, th);

	if ((operationp(car) || user_operation_p(car)) &&
	    heavy999p(GET_CAR(car)) && prefix_flag != 1)
	    exception(SYNTAX_ERR, makestr("expected ( )"), car, th);

    }
  repeat:
    gettoken(th);
    if (stok.type == VERTICAL) {
	//comma as separater
	cdr = NIL;
	cdr = parser(NIL, NIL, 1201, NIL, 1, 1, th);
	gettoken(th);		//discard Rbracket
	if (stok.type != RBRACKET)
	    exception(SYNTAX_ERR, makestr("illegal partial list"), 21, th);
	temp = cons(car, cdr);
	SET_AUX(temp, LIST);
	return (temp);
    } else if (stok.type == COMMA) {
	cdr = readlist(th);
	temp = cons(car, cdr);
	SET_AUX(temp, LIST);
	return (temp);
    } else if (stok.type == RBRACKET) {
	temp = cons(car, NIL);
	SET_AUX(temp, LIST);
	return (temp);
    } else if (stok.type != RCURL && stok.type != RPAREN
	       && stok.type != RBRACKET) {
	stok.flag = BACK;
	car = parser(list1(car), NIL, 1201, NIL, 1, 1, th);
	goto repeat;
    } else {
	exception(SYNTAX_ERR, makestr("illegal list"), NIL, th);
    }
    return (NIL);
}

int readdouble(int th)
{
    int temp;

    temp = readc();
    if (temp == '"')
	return (NIL);
    else if (temp == EOF)
	exception(SYNTAX_ERR, makestr("expected double quote"), NIL, th);
    else
	return (listcons(makeint(temp), readdouble(th)));

    return (NIL);
}

int readcurl(int th)
{
    int car;

    gettoken(th);
    if (stok.type == RCURL)
	return (NIL);

    if (stok.type == LCURL) {
	car = list2(NCURL, readcurl(th));
    } else {
	stok.flag = BACK;
	//comma as separater
	car = parser(NIL, NIL, 1201, NIL, 1, 1, th);
    }
    gettoken(th);
    if (stok.type == COMMA) {
	if (nullp(car))
	    exception(SYNTAX_ERR, makestr("illeagal curl {}"), NIL, th);
	else
	    return (list3(AND, car, readcurl(th)));
    } else if (stok.type == RCURL) {
	return (car);
    } else
	exception(SYNTAX_ERR, makestr("illegal curl {}"), NIL, th);
    return (NIL);
}

//--------------debug tool----------
void monitor(int x)
{
    static int y;
    int z;

    z = GET_AUX(x);
    if (y != z) {
	printf("monitor %d -> %d\n", y, z);
	y = z;
    }
}

void report_atom(int x)
{
    printf("aux= %d\n", GET_AUX(x));
    printf("opt= %d\n", GET_OPT(x));
    printf("cdr= %d\n", GET_CDR(x));
}

void report_token(void)
{
    printf("stok.type=%d\n", stok.type);
    printf("stok.ch=%c\n", stok.ch);
    printf("stok.ahead=%c\n", stok.ahead);
    printf("stok.buf=%s\n", stok.buf);
}
