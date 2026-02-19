# Parser

A small parsing toolkit for N-Prolog.

This module provides:

read_codes/2: read a source file into a list of character codes.

tokenize/2: tokenize a list of character codes into a token list.

DCG rules (e.g. program//1) to parse tokens into an AST via phrase/2.

## Usage
```
?- use_module(parser).
yes
```

## Predicates
read_codes(+Stream, -Codes)

Reads all characters from Stream and returns them as a list of character codes.

Stream: a stream opened by open/3

Codes: list of integers (character codes)

tokenize(+Codes, -Tokens)

Converts a list of character codes into a token list.

## Current token forms:

word(Atom) — words/identifiers/keywords as atoms (e.g. word('DO'), word('X'))

num(Int) — decimal integer literals (e.g. num(1))

sym(Sym) — symbols/operators (e.g. sym(';'), sym('='), sym('+'))

# Notes:

Whitespace (spaces/newlines) is ignored.

Keywords like DO and END are currently returned as word('DO') etc.
(You may later split them into kw(do) and id(x) if desired.)

# Grammar (DCG)

The module defines DCG rules such as:

program//1 — parses a token list into an AST.

(Internally used with phrase/2.)

# Example

Input file (./tests/test.pl):

DO;
X = X+1;
END;

Run:

?- open(S,'./tests/test.pl',r),
   read_codes(S,C),
   tokenize(C,T),
   phrase(program(AST), T).

Output:

S = <stream24083>
C = [68,79,59,32,10,88,32,61,32,88,43,49,59,10,69,78,68,59,10,10,10]
T = [word('DO'),sym(';'),word('X'),sym(=),word('X'),sym('+'),num(1),sym(';'),word('END'),sym(';')]
AST = program([assign('X',plus(var('X'),num(1)))]) .
yes
AST shape (current)

For the example above, the AST uses these functors:

program(Stmts)

assign(Var, Expr)

plus(E1, E2)

var(Name)

num(N)

Example:

program([assign('X', plus(var('X'), num(1)))])
Notes / Next steps

# Typical next extensions:

Require ; to terminate statements (if not already enforced)

Add operator precedence (*, /, parentheses)

Introduce reserved-word tokens (e.g. kw(do), kw(end)) separate from identifiers

Add error reporting (position info: line/column)
