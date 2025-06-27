# Module
N-Prolog has several modularized libraries.

- Compiler 
 use_module(compiler).
 Until version 3.89, the compiler was loaded at startup. However, as the compiler grew larger, it began to occupy the heap area. Therefore, starting from version 3.9, it has been changed to be called as a module only when needed.

 - Checker
 use_module(checker).
 The checker is a library that performs static analysis of Prolog code to detect ARITY errors ,singleton variable issues and single clause issues.
 see CHECKER.md


- DCG
 use_module(dcg).
 Starting from version 3.9, DCG must be loaded from a module when used.

- Multiple world system
 use_module(mpworld).
 Starting from version 3.9, mpworld must be loaded from a module when used.
 see https://www.ipsj.or.jp/10jigyo/taikai/67kai/67program/html/event/ts10.pdf

- List
 use_module(list).
 It includes basic predicates for list processing. Please refer to the following.

```
 last/2,butlast/2,second/2,cons/3,nth/3,nth0/3,iota/3,take/3,drop/3,make_list/3,reverse/2,
 remove_at/3,insert_at/4,qsort/2,permutation/2,flatten/2
```

- tcltk
see TCLTK.md

# module/2
module/2 is a predicate used to create a module. The first argument is the module name, and the second argument is a list of predicate names with arities to be exported to the outside. Modules are defined on a per-file basis. Specifically, predicates not included in the list given as the second argument are prefixed with the module name followed by an underscore. This mechanism hides internal predicates and prevents name collisions.

In directives such as :-op/3 or :-dynamic, atoms are executed as-is. When referring to hidden predicates, you need to explicitly add the module name prefix to their names.

## example
```
:- module(test,[foo/1]).
:- dynamic(test_bar/1).

foo(X) :- bar(X).

bar(X) :- write(X).
```