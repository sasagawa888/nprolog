# Module
N-Prolog has several modularized libraries.

- Compiler 
 use_module(compiler).
 Until version 3.89, the compiler was loaded at startup. However, as the compiler grew larger, it began to occupy the heap area. Therefore, starting from version 3.9, it has been changed to be called as a module only when needed.

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
 remove_at/3,insert_at/4,qsort/2
```
