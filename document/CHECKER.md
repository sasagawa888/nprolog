# Checker
The checker is a library that performs static analysis of Prolog code to detect ARITY errors ,singleton variable issues and single clause issues.

# Usage

```
use_module(checker).

check_file(file_name).
```

# Example

```
foo(X,Y) :- write(1,2,X).
?- check_file('./tests/bug.pl').
detect arity write(1,2,varX) in foo(varX,varY)
detect singleton varY in foo(varX,varY)
no
?- 

fact(0,1).
facT(N,X) :-
        N1 is N-1,
        fact(N1,X1),
        X is N*X1.
?- check_file('./tests/fact.pl').
detect single clause facT(varN,varX):-varN1 is varN-1,(fact(varN1,varX1),varX is varN*varX1)
yes

```

# Why Checker
With short code like the example above, mistakes are easily detectable. However, when dealing with thousands of lines of Prolog code, it's easy to miss certain errors. In an interpreter, bugs that don’t cause runtime errors might go unnoticed. Many of these bugs stem from typographical mistakes, such as singleton variable issues. Sometimes, a mistake is made in the number of arguments in just one clause, and it's hard to notice. By detecting these errors, the goal is to prevent mistakes in large-scale code.

I have also included a feature to detect spelling mistakes in the head of clauses. This simply extracts clauses that occur only once. While some of these may be legitimate, there is also the possibility of spelling mistakes. It detects them as potential issues. In large codebases, these mistakes can be surprisingly difficult to find.