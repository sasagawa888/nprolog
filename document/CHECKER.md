# Checker
The checker is a library that performs static analysis of Prolog code to detect ARITY errors and singleton variable issues.

# Usage

```
use_module(checker).

check_file(file_name).
```

# Example

```
foo(X,Y) :- Z is X+1.

N-Prolog Ver 4.00
?- use_module(checker).
yes
?- check_file('./tests/bug.pl').
detect singleton varY in foo(varX,varY)
detect singleton varZ in foo(varX,varY)
no
?- 

foo(X,Y) :- write(1,2,X).
?- check_file('./tests/bug.pl').
detect arity write(1,2,varX) in foo(varX,varY)
detect singleton varY in foo(varX,varY)
no
?- 
```

# Why Checker
With short code like the example above, mistakes are easily detectable. However, when dealing with thousands of lines of Prolog code, it's easy to miss certain errors. In an interpreter, bugs that don’t cause runtime errors might go unnoticed. Many of these bugs stem from typographical mistakes, such as singleton variable issues. Sometimes, a mistake is made in the number of arguments in just one clause, and it's hard to notice. By detecting these errors, the goal is to prevent mistakes in large-scale code.
