# CLPFD
CLP(FD): Constraint Logic Programming over Finite Domains

N-Prolog's CLPFD deliberately does not include heuristic optimizations. Experiencing how manually changing the order of variables or adding constraints affects the efficiency of the search space exploration is valuable and preferable for educational purposes.

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
- Xs ins A..Z
- all_different(Xs)

# Function
- + plus
- - minus
- * mult
- // divide
- ^ exponent
- ** exponent
- mod modulo

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

    fd_selected[256]  for all_different/1
    fd_sel_idx        index of selected stack
    
```
## Domain generation
The domain is generated on a C language array, where integer indices are stored.
The actual values are obtained by adding the index to the minimum value of the range.
This corresponds to variables.
By incrementing these indices, all integers within the range are generated without omission.
When the all_different/1 constraint requires the variables to be unique,
selected numbers are pushed onto a stack to avoid duplication.
When generating a new domain, these values are popped,
and new indices are generated and pushed onto the stack.

## Constraint propagation

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
    int res,res1;

  loop:
    
	// constraint propagate
    res = fd_propagate(fd_sets);
    if (res == YES) {
	// if all variables are bounded, then success
	if (fd_domain[0] != UNBOUND && fd_var_idx == fd_var_max - 1)
	return (YES);
	
	// if there are unbound variable, then next domain
	res1 = next_domain();
	// if domain is all selected, then end return complete
	if (res1 == COMPLETE)
		return (COMPLETE);
	goto loop;
    } else if (res == NO) {
	// if constraint set is not satistificate, then prune and go on
	res1 = prune_domain();
	// if domain is all selected, then end return complete
	if (res1 == COMPLETE)
	    return (COMPLETE);
	goto loop;
    } else if (res == UNKNOWN) {
	// if there is possibility, then go on solving 
	res1 = next_domain();
	// if domain is all selected, then end return complete
	if (res1 == COMPLETE)
	    return (COMPLETE);
	goto loop;
    }

    return (NO);
}

```

satisfiable analyzes the expression expr and returns one of four possible values: yes, no, unknown.

- yes means that the expression is definitively true.

- no indicates failure, but there may still be a possibility of success in further exploration.

- unknown means the result cannot be determined at this point, but success is still possible.


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

Idea Memo: Handling Free Variables
free variable is Var in -999999999..999999999
GET_VAR(x) == 2; distinguish normal var. normal var GET_VAR(x)==1.
At first free variable's GET_VAR is 0. when find free var,SET_VAR(x,2),and -999999999..999999999
satisficational find free variable, set fd_domain[idx] = value.
when propagate get NO , unbind free variables.

Idea Note
labeling/2: There may be situations where it is effective to have an option that prunes the search tree without exploring branches when the value is UNKNOWN. For example, in the queens problem, the determined variables are more important, and computing satisfiability for undetermined variables is meaningless.

# ✅ fd_narrowing Algorithm Overview

## 🎯 Goal
To iteratively **narrow the domain of finite-domain variables** by computing **min/max values of the overall expression**, thereby deducing constraints.

---

## 🧠 Core Idea
- Prioritize variables based on **coefficient magnitude** and **order of appearance**.
- Use **min/max evaluation** of expressions to determine feasible value ranges.
- If overlapping ranges between the left-hand side (LHS) and right-hand side (RHS) expressions shrink, restrict variable domains accordingly.

---

## 📝 Example: SEND + MORE = MONEY

### Setup

**Expressions:**
- LHS = `SEND + MORE`
- RHS = `MONEY`
- Each letter represents a digit with all values distinct (`all_different`).

**Variable order (based on descending coefficient → then appearance):**
- LHS variables: `[S, M, E, O, N, R, D]`
- RHS variables: `[M, O, N, E, Y]`

---

## 🔍 Step-by-Step Narrowing

### Step 1: All variables undefined
- Max(`SEND + MORE`) = `9999 + 9999 = 19998`
- Max(`MONEY`) = `99999`
- Min(`SEND + MORE`) = `0`
- Min(`MONEY`) = `0`

**Overlap:** `0 ~ 19998`  
➡ `MONEY` starts with `M × 10000`. To stay within overlap, `M` must be ≤ 1 ⇒ **`M = 1`**

---

### Step 2: `M = 1`
- Max(`MORE`) = `1999`
- Max(`SEND + MORE`) = `9999 + 1999 = 11998`
- Min(`MONEY`) = `10000`

**Overlap:** `10000 ~ 11998`  
➡ Assign smallest available digit to `O` ⇒ **`O = 0`**

---

### Step 3: `M = 1`, `O = 0`
- `MORE` = `1000`
- Max(`SEND`) = `9999`
- `SEND + MORE` = `9999 + 1000 = 10999`
➡ To match `MONEY = 10999`, `S` must be 9 ⇒ **`S = 9`**

---

### Step 4: `M = 1`, `O = 0`, `S = 9`
- `SEND + MORE = 10999`
- `MONEY = 10999`

➡ Both sides match ⇒ **Narrowing complete 🎉**

---

## 🧩 Key Characteristics

| Feature             | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| Heuristic-driven     | Prioritizes variables based on coefficient size and appearance order        |
| Semantic narrowing   | Uses expression-level min/max evaluation instead of only local constraints  |
| Decision mechanism   | Assumes a value → checks range consistency → narrows domain if necessary   |
| Contrast with AC-3   | Goes beyond binary constraints to analyze global structure of expressions   |
| Implementation ease  | Can be structured around symbolic expression evaluation and propagation     |


