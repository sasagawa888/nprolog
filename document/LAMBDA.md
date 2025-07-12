# Lambda Library

A Prolog library for lambda calculus expression representation and reduction, including **α-conversion** and **β-reduction**.

---

## 📦 Usage

```prolog
?- use_module(lambda).

?- reduce([l(x,x), a], R).
R = a.

?- reduce([l(p, forall(x, implies(man(x), [p,x]))), l(x, loves(x,mary))], R).
R = forall(x, implies(man(x), loves(x, mary))).

## 🛠️ Specification
reduce(+Exp, -Result)

Reduces a lambda calculus expression Exp to its normal form by performing α-conversion to avoid variable capture, and then β-reduction as necessary.
Argument	Description
Exp	Input expression in lambda calculus representation
Result	Fully reduced result

Deterministic: always succeeds with a single normal form (if reachable).

## 📐 Data Representation

Lambda terms are represented in the following format:
Form	Meaning
l(Var, Body)	Lambda abstraction (λVar. Body)
[Func, Arg]	Function application ((Func Arg))
Examples
Lambda Term	Prolog Representation
λx.x	l(x, x)
(λx.x) a	[l(x, x), a]
λx.λy. x	l(x, l(y, x))
(λx.λy. x) a	[[l(x, l(y, x)), a]]
λp. ∀x (man(x) → p(x))	l(p, forall(x, implies(man(x), [p, x])))

## 🔁 Reduction Semantics

α-conversion renames bound variables to avoid capture during substitution.

    Example: l(x, l(x, x)) → l(x1, l(x, x))

β-reduction applies a function to its argument.

    Example: [l(x, x), a] → a

    Nested example: [[l(x, l(y, x)), a], b] → a

## 🧪 Examples

?- reduce([l(x, x), a], R).
R = a.

?- reduce([[l(x, l(y, x)), a], b], R).
R = a.

?- reduce([l(x, [x, z]), [l(y, y), a]], R).
R = [[l(y, y), a], z].

?- reduce([l(x, l(x, x)), a], R).
R = l(x1, x1).

## 📁 Implementation Notes

Only reduce/2 is exported. Internal predicates (alpha/4, beta/4, etc.) are hidden.

Expressions are first α-converted (renaming of bound variables) before β-reduction is performed.

Recursive reductions ensure full normalization.

## ✅ Tests

test(identity)    :- reduce([l(x, x), a], a).
test(constant)    :- reduce([l(x, y), a], y).
test(nested)      :- reduce([[l(x, l(y, x)), a], b], a).
test(app_in_arg)  :- reduce([l(x, [x, z]), [l(y, y), a]], [[l(y, y), a], z]).
test(shadowing)   :- reduce([l(x, l(x, x)), a], l(x1, x1)).

