# Mode Inference Prototype

The `mode` library is planned to eventually be integrated into and absorbed by the compiler.

# Example Execution

```prolog
N-Prolog Ver 5.19 [30M cells]

?- use_module(mode).
yes

?- infer('./tests/bug').
inference1
inference2
yes

?- listing(mode).
mode(dummy,0,[]).
mode(partition,4,['+','+','-','-']).
mode(partition,4,['-','+','+','+']).
mode(foo,2,['-','+']).
mode(fact,2,['+','-']).
mode(bar,1,['+']).
mode(qsort,3,['+','-','+']).
yes
?-
```

The system analyzes the predicates defined in `bug.pl` and infers their input/output modes.

The analyzed source code is shown below.

```prolog
% mode test data

qsort([X|L], R, R0) :-
    partition(L, X, L1, L2),
    qsort(L2, R1, R0),
    qsort(L1, R, [X|R1]).

qsort([], R, R) :- !.


partition([X|L], Y, [X|L1], L2) :-
    X < Y,
    !,
    partition(L, Y, L1, L2).

partition([X|L], Y, L1, [X|L2]) :-
    !,
    partition(L, Y, L1, L2).

partition([], _, [], []) :- !.


% test case

foo(X,Y) :-
    true,
    X is Y.

fact(0,1).

fact(N,M) :-
    N1 is N - 1,
    fact(N1,M1),
    M is N * M1.

bar(X) :-
    write(X).

boo(1,2).
```

# Mode Notation

- `+` denotes an input argument.
- `-` denotes an output argument.

For example:

```prolog
mode(partition,4,['+','+','-','-']).
```

means:

```prolog
partition(+,+,-,-)
```

Predicates whose modes cannot be inferred are ignored.

In the example above, `boo/2` is excluded from analysis because it is treated as a simple database fact.

# Two-Pass Analysis

`qsort/3` depends on `partition/4`.

Without first analyzing `partition/4`, accurate mode inference for `qsort/3` is impossible.
For this reason, the system performs a two-pass analysis.

During the first pass, the mode of `qsort/3` remains unresolved.
After the mode information for `partition/4` becomes available, the second pass completes the inference for `qsort/3`.

# Inference Rules

Reasoning that is trivial for humans turned out to be surprisingly difficult to express in Prolog.

## Structural Correspondence

In `partition/4`, the terms:

```prolog
[X|L]
[X|L1]
```

have the same structure and share the variable `X`.

Therefore, the system assumes that one side represents input and the other side represents output.

From the condition:

```prolog
X < Y
```

both `X` and `Y` must already be instantiated.
Therefore, they are inferred to belong to input arguments.

The standard mode of `partition/4` is therefore:

```prolog
partition(+,+,-,-)
```

However, Prolog also allows reverse-direction execution.
For this reason, the system generates two modes:

```prolog
mode(partition,4,['+','+','-','-']).
mode(partition,4,['-','+','+','+']).
```

## Inference of `qsort/3`

In:

```prolog
partition(L, X, L1, L2)
```

`L1` and `L2` are free variables, so they are inferred to be outputs.

Using the previously inferred mode information for `partition/4`, the system infers that `L` and `X` are inputs.

In:

```prolog
qsort(L2, R1, R0)
```

`R1` is a free variable, so it is inferred to be an output.

Then, in:

```prolog
[X|R1]
```

`R1` is already known to be an output variable.
Therefore, the list structure itself is already determined, and the third argument of:

```prolog
qsort(L1, R, [X|R1])
```

is inferred to be an input.

Through this chain of reasoning, the system derives:

```prolog
qsort(+,-,+)
```

## Semantics of Built-in Predicates

### `is/2`

For `fact/2`, the inference relies on the semantics of `is/2`.

The left-hand side of `is/2` is treated as an output, while variables appearing on the right-hand side are treated as inputs.

Example:

```prolog
M is N * M1
```

- `M` is output
- `N` and `M1` are inputs

This leads to:

```prolog
fact(+,-)
```

### `write/1`

For:

```prolog
bar(X) :- write(X).
```

the argument of `write/1` must already be instantiated.

Therefore:

```prolog
bar(+)
```

is inferred.

# Internal Representation

Example internal State:

```prolog
State = [
    e(1,2),
    c(varY,+),
    c(varX,+),
    c(2,varY),
    c(1,varX)
]
```

## Internal Predicates

### `c/2` — Connection

Represents structural correspondence.

Example:

```prolog
c(1,[X|L])
```

means that argument 1 is structurally connected to `[X|L]`.

### `e/2` — Exclusive Relation

Represents mutually exclusive argument roles.

Example:

```prolog
e(2,3)
```

means that arguments 2 and 3 cannot both be inputs or both be outputs simultaneously.

### `s/2` — State

Represents inferred variable state.

Example:

```prolog
s(R,+)
```

means that variable `R` is inferred to be an input.

### `a/2` — Argument Mode

Represents the inferred mode of an argument.

Example:

```prolog
a(1,+)
```

means that argument 1 is inferred to be an input argument.