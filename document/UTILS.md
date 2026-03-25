# Utils

A small parsing toolkit for N-Prolog.

This module provides:

read_codes/2: read a source file into a list of character codes.

tokenize/2: tokenize a list of character codes into a token list.

## Usage
```
?- use_module(utils).
yes
```

## Predicates
- read_codes(+Stream, -Codes)

- read_csv(+Stream, -List)

- tokenize(+Codes, -Tokens)

- format(Stream(String),Format,List)

- writeln(X) write(Stream,X)


## format(Str,Format,List).
If the first argument is a variable, the formatted string will be unified with the variable. The second argument is the format, which is a string. Values can be inserted into the string, and the values to be inserted are provided as a list in the third argument.

The variables for insertion are as follows:
- ~O  All of atomic.
- ~A atom
- ~S string
- ~D integer
- ~F float
- ~X hex integer
- ~Bn binary integer with n digits
- ~n newline
- ~t tab
- ~~ ~

## format(Stream,format,List).
If the first argument is a stream or alias, the edited string will be output to that stream. The specifications of the second and third arguments remain the same.

e.g.

```
?- format(user_output,$asdf$,[]).
asdfyes
?- format(X,$hello ~S !$,[$world$]).
X = $hello world !$ .
yes
?- format(X,$hello ~A !$,[world]).
X = $hello world !$ .
yes
?- 
?- format(X,$number ~D $,[1]).
X = $number 1 $ .
yes
?- format(X,$number ~F $,[1.1]).
X = $number 1.1 $ .
yes
?- format(X,$number ~O ~O $,[1.1,atom]).
X = $number 1.1 atom $ .
yes
```
