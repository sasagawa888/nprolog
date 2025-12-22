# List Library

This library provides basic list-processing predicates implemented in pure Prolog.
All predicates operate on standard Prolog lists and are mainly intended for
educational and experimental use.

## Usage

```prolog
?- use_module(list).

Predicates
last/2
last(+List, ?Last)


Returns the last element of List.

If List is empty, Last = []

If List has one element, that element is returned

Example

?- last([a,b,c], X).
X = c.

butlast/2
butlast(+List, ?Init)


Returns the list without its last element.

Example

?- butlast([a,b,c], X).
X = [a,b].

second/2
second(+List, ?Second)


Returns the second element of the list.

If the list has fewer than two elements, the result is []

Example

?- second([a,b,c], X).
X = b.

cons/3
cons(+Element, +List, ?Result)


Constructs a new list by adding Element to the front of List.

Example

?- cons(a, [b,c], X).
X = [a,b,c].

nth/3
nth(+N, +List, ?Element)


Returns the element at position N (1-based index).

Example

?- nth(2, [a,b,c], X).
X = b.

nth0/3
nth0(+N, +List, ?Element)


Returns the element at position N (0-based index).

Example

?- nth0(0, [a,b,c], X).
X = a.

iota/3
iota(+Start, +End, ?List)


Generates a list of consecutive integers from Start to End (inclusive).

Example

?- iota(1, 5, L).
L = [1,2,3,4,5].

take/3
take(+N, +List, ?Prefix)


Takes the first N elements from List.

Example

?- take(3, [a,b,c,d], X).
X = [a,b,c].

drop/3
drop(+N, +List, ?Rest)


Drops the first N elements from List and returns the remainder.

Example

?- drop(2, [a,b,c,d], X).
X = [c,d].

make_list/3
make_list(+N, +Element, ?List)


Creates a list of length N where every element is Element.

Example

?- make_list(3, x, L).
L = [x,x,x].

reverse/2
reverse(+List, ?Reversed)


Reverses a list.

Note: This implementation uses append/3 and has quadratic time complexity.

Example

?- reverse([a,b,c], X).
X = [c,b,a].

remove_at/3
remove_at(+Index, +List, ?Result)


Removes the element at position Index (0-based).

Example

?- remove_at(1, [a,b,c], X).
X = [a,c].

insert_at/4
insert_at(+Index, +Element, +List, ?Result)


Inserts Element at position Index (0-based).

Example

?- insert_at(1, x, [a,b,c], X).
X = [a,x,b,c].

qsort/2
qsort(+List, ?Sorted)


Sorts a list in ascending order using the QuickSort algorithm.

Uses =< and > for comparison

Not a stable sort

Example

?- qsort([3,1,4,1,5], X).
X = [1,1,3,4,5].

permutation/2
permutation(+List, ?Permutation)


Generates all permutations of List using backtracking.

Example

?- permutation([a,b,c], X).
X = [a,b,c] ;
X = [a,c,b] ;
...

flatten/2
flatten(+NestedList, ?FlatList)


Flattens a nested list structure into a single-level list.

Atomic values are treated as elements

Example

?- flatten([a,[b,[c,d]],e], X).
X = [a,b,c,d,e].

min_list/2
min_list(+List, ?Min)


Returns the minimum element of a numeric list.

Example

?- min_list([3,1,4], X).
X = 1.

max_list/2
max_list(+List, ?Max)


Returns the maximum element of a numeric list.

Example

?- max_list([3,1,4], X).
X = 4.

Notes

This library is designed for clarity and learning, not performance

Some predicates (reverse/2, permutation/2) are inefficient for large lists

Behavior may differ from standard Prolog libraries such as lists