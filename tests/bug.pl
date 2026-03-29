

:- use_module(dcg).


add_rest(Acc, E) -->
    add_op(Op),
    mul_expr(T),
    { Acc1 = expr(Op, Acc, T) },
    add_rest(Acc1, E).
add_rest(Acc, Acc) --> [].