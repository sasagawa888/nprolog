jump_gen_head_list(L) :-
    write('({int res;'),
    write('Jpush_ustack(tree);'),
    write('res = Jlistp(tree);'),
    write('tree = Jcdr(tree);'),
    write('if(res=1) res = YES else res = NO;'),
    write('res})==YES && '),
    jump_gen_head_list1(L).

jump_gen_head_list1([]) :-
    write('({int res;'),
    write('res = Junify_nil(NIL,tree);'),
    write('tree = Jpop_ustack();'),
    write('res;})==YES ').

jump_gen_head_list1([L|Ls]) :-
    n_compiler_variable(L),
    write('({int res;'),
    write('res = Junify_var('),
    jump_gen_a_argument(L),
    write(',Jcar(tree));'),
    write('tree = Jcdr(tree);'),
    write('res;})==YES && '),
    jump_gen_head_list1(Ls).

jump_gen_head_list1([L|Ls]) :-
    atomic(L),
    write('({int res;'),
    write('res = Junify_const('),
    jump_gen_a_argument(L),
    write(','),
    write('Jcar(tree));'),
    write('tree = Jcdr(tree);'),
    write('res;})==YES && '),
    jump_gen_head_list1(Ls).

jump_gen_head_list1([L|Ls]) :-
    list(L),
    write('('),
    jump_gen_head_list(L),
    write(')'),
    jump_gen_head_list1(Ls,N,I1,Pos).

