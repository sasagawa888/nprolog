%PLM80

program(program(Stmts)) -->
    block(Stmts).

block(Stmts) -->
    [word('DO')], [sym(';')],
    statements(Stmts),
    [word('END')], [sym(';')].

statements([S|Ss]) -->
    statement(S),
    statements(Ss).
statements([]) -->
    [].

% ---- 文 ----

statement(assign(Id, Expr)) -->
    [word(Id)],
    [sym('=')],
    expr(Expr),
    [sym(';')].

% ---- 式 ----

expr(Expr) -->
    term(T),
    expr_rest(T, Expr).

expr_rest(Acc, Expr) -->
    [sym('+')],
    term(T),
    { Acc1 = plus(Acc, T) },
    expr_rest(Acc1, Expr).
expr_rest(Acc, Acc) -->
    [].

term(var(Id)) -->
    [word(Id)].
term(num(N)) -->
    [num(N)].
