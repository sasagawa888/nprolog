# CLPFD
under construction

# Usage

```
?- use_module(clpfd).
```

# Specification

- X #= Y
- X #\= Y
- X #> Y
- X #< Y
- X #>= Y
- X #<= Y


# memo
CLP(FD): Organization of Algorithms and Data Structures

## Data Structures

```
    Variable List
    Example: [var_1, var_2]
    Variables are associated with their respective domains:
    var_1 = [1, 2, 3]
    var_2 = [0, 1, 2]

    Domain List
    Example:
    var_1 : var_2 → [[1,1], [2,2]]
```

## Algorithms

    in Predicate
    Generates the domain for each variable and associates it with the corresponding variable atom.

```
    Equality Constraint #=
    The relation is instantiated and recorded in the domain list.
    At this time, if any variable is not yet determined, a * is inserted in its place.
    If the domain of a variable is not concretely defined, the result is NO.

    Examples:
    X = [1,2], Y = [1,2,3] → X #= Y → domain = [[1,1], [2,2]]

    X = [1,2], Y = [1,2,3], Z = [0,1,2] → X #= Y → domain = []
    Z #<3 → domain[[1,1,3],[2,2,3]]

    Inequality Constraint #\=
    Similar to equality, the relation is instantiated and added to the domain list.
    Insert * for undetermined variables.
    If variable domains are not defined concretely, return NO.

    Examples:
    X = [1,2], Y = [1,2,3] → X #\= Y → domain = [[1,2], [1,3], [2,1], [2,3]]
    
    X = [1,2], Y = [1,2,3], Z = [0,1,2] → X #\= Y → domain = []
    X #= 0 → domain = [[1,2,0], [1,3,0], [2,1,0], [2,3,0]]

    Comparison Constraints #<, #>, #=<, #>=
    These constraints narrow the domain of variables.
    If a variable is narrowed down to a single value, it is considered determined and recorded in the domain list.
    If the domain list already exists, incompatible entries are removed.
    If * is present, it is replaced with a concrete value.

    Example:
    X = [1,2,3] → X #< 2 → X = [1]
    If domains are not concretely defined, represent them abstractly:
    X #> 0 → X = [0, ∞]

    label Predicate
    If there is no * in the domain, the variable is determined and unified with the argument list.
    If * exists, exhaustive search is performed within the variable's range to determine values, then unified with the argument list.
```

