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
int propagate_all(int constraint, int vars, int domain)
{

    if (nullp(constraint))
	return (YES);
    else 
	return (propargate(cadr(constraint), caddr(constraint), vars, domain));

    return (NO);
}

int propergate(int constraint, int rest, int vars, int domain)
{

    if (nullp(constraint)) {
	return (propergate_all(rest, vars, domain));
    } else if (#= constraint) {
    
    } else if (#< constraint) {

    } ...
	
    return (NO);
}
```