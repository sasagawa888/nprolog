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
            if (解が１つ)　constraint_set を１つ取り除く
            else if(解がない) break;
            else constraint_search(expr);
        } else if( expr == (X #< Y)){
            if (解が１つ)　constraint_set を１つ取り除く
            else if(解がない) break;
            else constraint_search(expr);
        } else if( expr == (X #> Y)){
            if (解が１つ)　constraint_set を１つ取り除く
            else if(解がない) break;
            else constraint_search(expr);
        } else if ( expt == X in A..Z){
            constraint_var = cons(X,constraint_var);
            constraint_env = cons(makerange(A..Z),constraint_env);
        }


        constraint_set = cdr(constraint_set);
    }
    return (NO);
}

void constraint_search(expr)
{
    int candidate,var,env,domain;

    var = constraint_var;
    env = constraint_env;
    domain = NIL;
    while(最初の変数要素 != NIL){
        try:
        assign(expr,var,env); // exprに値を代入する
        if(establish(expr)){
            成立したなら2番めの変数要素を１つ減らす　domainに要素を記録
            goto try;
        }
        else {
            不成立なら1番めの変数要素を１つ減らす
            2番め以後の変数要素を復元する。
            goto try;
        }

    }
    見つけたdomainを既存のものに連結する
    constraint_domain = cons(domain,constraint_domain);
}
```