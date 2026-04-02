
arc(a1, v1, v2).
arc(a2, v2, v3).
arc(a3, v3, v4).
arc(a4, v4, v1).
arc(a5, v3, v5).

walk(U, U).
walk(U, V) :- arc(_, U, U1), walk(U1, V).

foo(X,X).

%unify_var() is buggy