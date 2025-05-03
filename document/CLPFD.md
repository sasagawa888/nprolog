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
- X in A..Z

# Internal system predicate
- add_constraint(Expr)  Add the constraint expression to the set of constraints.
- constraint_set(X) Unify X with the list of constraint sets.
- constraint_var(Var,Range) Assign a range of integers to the variable and also add it to the list of constraint variables.

# memo
CLP(FD): Organization of Algorithms and Data Structures

## Data Structures

```
    constraint_set

    constraint_domain[256][10] 
    [var_N][0]=index
           [1]=start
           [2]=length
           [3]=end
           [4]= 1=unique 0=non

    constraint_select[256];
    constraint_select_idx; 0..256

    constraint_unique; list of unique variables
    e.g. [var_1,var_2...]
    
```
