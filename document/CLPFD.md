# CLPFD
CLP(FD): Constraint Logic Programming over Finite Domains
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

# Memo
CLP(FD): Organization of Algorithms and Data Structures

## Data Structures

```
    fd_sets:  constraint-sets

    fd_domain[256] index of variable 
    fd_min[256]  A in A..Z  
    fd_max[256]  Z in A..Z
    fd_len[256]  Z-A
    fd_unique[256] all-different variable=1 else 0
    
```

## Constraint propagation
propagate_all sequentially takes constraint expressions from the given constraint set, from left to right, and passes them to propagate. The propagate function analyzes a single constraint expression. As a result of this analysis, it appropriately increments the global variable fd_domain.

If nil is given to propagate, it is interpreted as there being no constraints. It then processes the domains given by in, ins, and all_different one by one.

propagate_all receives multiple constraint expressions. It processes them sequentially, and when it finally reaches nil, the computation of the domains based on constraints is considered complete.

Since the domains are retained, when backtracking occurs, the search continues from the current state.


```
int fd_propagate(int sets)
{
    int res;

    if (sets == NIL)
	return (YES);
    else {
	res = fd_satisfiable(car(sets));
	if (res == YES || res == UNKNOWN)
	    return (fd_propagate(cdr(sets)));
	else if (res == NO)
	    return (NO);
    }
    return (NO);
}

int fd_solve()
{
    int res;

  loop:
    if (fd_var_idx == fd_var_max - 1)
	return (YES);

    res = fd_propagate(fd_sets);
    if (res == YES) {
	res = next_domain();
	if (res == NO)
	    return (NO);
	goto loop;
    } else if (res == NO) {
	res = prune_domain();
	if (res == NO)
	    return (NO);
	goto loop;
    } else if (res == UNKNOWN) {
	res = next_domain();
	if (res == NO)
	    return (NO);
	goto loop;
    }

    return (NO);
}



```

satisfiablep analyzes the expression expr and returns one of four possible values: yes, no, unknown, or futile.

- yes means that the expression is definitively true.

- no indicates failure, but there may still be a possibility of success in further exploration.

- unknown means the result cannot be determined at this point, but success is still possible.

- futile signifies that there is absolutely no possibility of success.

## Satisfiable
Analyze the expressions on the left-hand side and right-hand side, and convert them into lists whose elements are integers. The list will have either one or two elements.
If a variable is already instantiated or the expression is a constant, the list will have one element.
If the expression includes an uninstantiated variable, then compute two values: one using the lower bound of the variable's domain, and one using the upper bound. The result is a list with two elements.
Example:
```
X in 1..3  
Y in 2..3  
X + Y #= 3  
```
First stage:

X and Y are still uninstantiated.
Left-hand side: 1 + 2 = 3 (min), 3 + 3 = 6 (max) → [3,6]
Right-hand side: constant → [3]
Since 3 lies within the range [3,6], the constraint is deemed satisfiable.
Second stage:

Assume X is 1, Y remains uninstantiated.
1 + 2 = 3 (min), 1 + 3 = 4 (max) → [3,4]
Right-hand side is [3]
Since 3 lies within the range [3,4], the constraint is still satisfiable.
Third stage:

Assume X is 1 and Y is 2.
1 + 2 = 3 → [3], Right-hand side is also [3]
Since 3 equals 3, the constraint is satisfied.

If backtracking occurs, satisfiability is evaluated for other possible solutions in the same way.

## Mechanism for Determining Satisfiability

fd_analyze(expr) determines whether the given expression is satisfiable under the current domain.
It returns one of the following results: yes, no, or unknown. The function analyzes and evaluates both the left-hand side and right-hand side of the expression.

If a variable is already bound, its bound value is used.
If a variable is unbound, two evaluations are performed: one using its lower bound and one using its upper bound.
The result is stored in a list.
If all variables are bound, the result is a list of length 1.
If there are unbound variables, the result is a list of length 2.
In this case, the first element represents the lower bound and the second represents the upper bound.

satisfiablep(expr) analyzes this list to determine whether the expression is satisfiable.
If a definitive judgment cannot be made at that point, it returns unknown.

When propagate encounters an unknown result, it incrementally expands the domain and performs further satisfiability checks.

## Standard Form

Constraint expressions will be stored in a standard form.

Standard Form:

- Left-hand side: Expressions containing only variables

- Right-hand side: Expressions containing both variables and constants

Example 1:
X #= Y

Example 2:
X #= Y + 1

The use of negative signs will be avoided as much as possible. If negative signs are included, it complicates the satisfiability computation.

Example 3:
X + Y - Z #= 3 → X + Y #= Z + 3

If an expression with a negative sign is provided, an attempt will be made to convert it into an expression with only positive signs during the unification phase.
If conversion is not possible, the expression will remain as-is. In such cases, the satisfiability computation will be determined using the values of the instantiated variables.



## Internal Predicates
The handling of constraint operators like #= is defined as user-defined predicates within the library. These use internal predicates to store constraints as lists in fd_sets. The definitions are written in the clpfd.pl file inside the library.

```
X #= Y :-
    n_add_constraint(X #= Y).

```

The in and ins operators are used to register variables and add variable information, using the following internal predicates:

```
X in Y :-
    n_constraint_var(X, Y).

X ins Y :-
    n_constraint_vars(X, Y).
```

Constraint operators like #= are handled as infix operators using op/3.

```
:- op(600, xfy, '..').
:- op(600, xfy, #=).
:- op(600, xfy, #>).
:- op(600, xfy, #<).
:- op(600, xfy, #\=).
:- op(600, xfy, #<=).
:- op(600, xfy, #>=).
:- op(600, xfy, in).
:- op(600, xfy, ins).
```
