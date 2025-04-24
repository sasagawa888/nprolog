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

```
// Idea sketch
int constraint_set;
int constraint_var;
int constraint_env;
int constraint_domain;

int constraint_propagate()
{
    int expr;

    constraint_set = reverse(constraint_set);
    constraint_var = NIL;
    constraint_env = NIL;
    constraint_domain = NIL;

    while(constraint_set != NIL){
        expr = car(constraint_set);
        if( expr == (X #= Y)){
            // If there is only one solution, remove it from constraint_set
            if (only one solution) constraint_set is reduced by one
            // If no solution exists, break
            else if(no solution) break;
            // Otherwise, narrow the solution range and try all possibilities
            else narrow the solution range and try all possibilities constraint_search(expr, env);
        } else if( expr == (X #< Y)){
            // If there is only one solution, remove it from constraint_set
            if (only one solution) constraint_set is reduced by one
            // If no solution exists, break
            else if(no solution) break;
            // Otherwise, narrow the solution range and try all possibilities
            else narrow the solution range and try all possibilities constraint_search(expr, env);
        } else if( expr == (X #> Y)){
            // If there is only one solution, remove it from constraint_set
            if (only one solution) constraint_set is reduced by one
            // If no solution exists, break
            else if(no solution) break;
            // Otherwise, narrow the solution range and try all possibilities
            else narrow the solution range and try all possibilities constraint_search(expr, env);
        } else if ( expr == X in A..Z){
            // Register the variable and its initial value range
            constraint_var = cons(X, constraint_var);
            constraint_env = cons(makerange(A..Z), constraint_env);
        }

        constraint_set = cdr(constraint_set);
    }
    return (NO);
}

void constraint_search(expr, env)
{
    int candidate, var, env, domain;

    var = constraint_var;
    env = constraint_env;
    domain = NIL;
    while(candidates remain){
         // Like Lisp's dolist
        if (expr is satisfied) remember it in domain
    }
    // Append the found domain to the existing one
    constraint_domain = cons(domain, constraint_domain);
}
```

