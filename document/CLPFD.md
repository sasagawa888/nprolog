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
