jump_gen_head_list(L,N,Pos) :-
    write('(Jlistp('),
    jump_gen_head2(N,Pos),
    write(') && '),
    jump_gen_head_list1(L,N,1,Pos),
    write(')').

jump_gen_head_list1([],N,I,Pos) :-
    write('Junify_nil(NIL,'),
    jump_gen_head2(N,Pos),
    write(') == YES').

jump_gen_head_list1([L|Ls],N,I,Pos) :-
    n_compiler_variable(L),
    write('Junify_var('),
    jump_gen_a_argument(L),
    write(','),
    jump_gen_head2(N,[I|Pos]),
    write(') == YES && '),
    I1 is I+1,
    jump_gen_head_list1(Ls,N,I1,Pos).

jump_gen_head_list1([L|Ls],N,I,Pos) :-
    atomic(L),
    write('Junify_const('),
    jump_gen_a_argument(L),
    write(','),
    jump_gen_head2(N,[I|Pos]),
    write(') == YES && '),
    I1 is I+1,
    jump_gen_head_list1(Ls,N,I1,Pos).

jump_gen_head_list1([L|Ls],N,I,Pos) :-
    list(L),
    jump_gen_head_list(L,N,1,[I|Pos]),
    I1 is I+1,
    jump_gen_head_list1(Ls,N,I1,Pos).


% write L=[2,1] -> Jnth(Jnth(argN,1),2)
jump_gen_head2(N,[]) :-
    write('arg'),
    write(N).
jump_gen_head2(N,[L|Ls]) :-
    write('Jnth('),
    jump_gen_head2(N,Ls),
    write(','),
    write(L),
    write(')').
© 2021 GitHub, Inc.