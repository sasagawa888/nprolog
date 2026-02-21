# Token

A small parsing toolkit for N-Prolog.

This module provides:

read_codes/2: read a source file into a list of character codes.

tokenize/2: tokenize a list of character codes into a token list.

## Usage
```
?- use_module(token).
yes
```

## Predicates
read_codes(+Stream, -Codes)

tokenize(+Codes, -Tokens)

