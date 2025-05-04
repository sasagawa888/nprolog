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
    fd_sets:  constraint-sets

    fd_domain[256] index of variable 
    fd_min[256]  A in A..Z  
    fd_max[256]  Z in A..Z
    fd_len[256]  Z-A
    fd_unique[256] all-different variable=1 else 0
    
```

## Constraint propagation

```

int propagate_all(int sets)
{
    int res;
    if (sets == NIL)
             return(YES);

	if (propagate(car(sets)) == YES){
	        return(propagate_all(cdr(sets)));
    }
	else{
        res = prune_domain();
        if(res == NO)
            return(NO);

        propagate_all(fd_sets);
    }

    return (NO);
}

int propagate(int expr)
{
    int res;

    res = next_domain();
    if(res == NO)
        return(NO);
    loop:
    bind_variable(expr);
    if (satisfiablep(expr) == YES) {
        if(fd_var_idx == fd_var_max -1)
            return(YES);
    
	return (propagate(new_expr(expr)));
    } else {
	res = prune_domain();
    if(res == NO){
        unbind_variable(expr);
        goto loop;
    }
    
    bind_variable(expr);
	if (satisfiablep(expr) == YES)
	    return (propagate(new_expr(expr)));
    }
    return (NO);
}


```

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