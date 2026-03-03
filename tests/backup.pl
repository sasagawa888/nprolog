
% PL/M compiler


plm80(File) :-
    open(S,File,r),
    read_codes(S,C),
    tokenize(C,T),
    compile(T,Ast),
    close(S),
    encode(Ast,Asm),
    change_ext(File,asm,Out),
    open(S,Out,w),
    %format(S,$INCLUDE ~A\n$,['plmbase.asm']),
    output_asm(user_output,Asm),
    close(S).

% output_asm(+StreamOrAlias, +Lines)
output_asm(_S, []).
output_asm(S, [X|Xs]) :-
    output_asm_line(S, X),
    output_asm(S, Xs).

output_asm_line(S, label(L)) :-
    format(S, $~A:$, [L]),
    nl(S).

output_asm_line(S, instr(Op, Args0)) :-
    normalize_args(Args0, Args),
    format(S, $    ~A$, [Op]),
    ( Args = [] ->
        true
    ;
        put_char(S, ' '),
        output_operands(S, Args)
    ),
    nl(S).

normalize_args(Args, Args) :- list(Args), !.
normalize_args(A, [A]).

output_operands(S, [A|As]) :-
    output_operand(S, A),
    output_operands_rest(S, As).

output_operands_rest(_S, []).
output_operands_rest(S, [X|Xs]) :-
    put_char(S, ','),
    output_operand(S, X),
    output_operands_rest(S, Xs).

output_operand(S, X) :-
    ( integer(X) ->
        format(S, $~D$, [X])
    ; X = mem(Reg, Disp) ->
        format(S, $(~A$, [Reg]),
        output_disp(S, Disp),
        put_char(S, ')')
    ; X = mem(Reg) ->
        format(S, $(~A)$, [Reg])
    ; X = mem_label(L) ->
        format(S, $(~A)$, [L])
    ; atom(X) ->
        format(S, $~A$, [X])
    ; string(X) ->
        % N-Prolog の文字列型があるならこれでOK
        format(S, $~S$, [X])
    ;
        % 最後の保険：そのまま出す（仕様に合わせて調整可）
        write(S, X)
    ).

output_disp(_S, 0) :- !.
output_disp(S, N) :-
    N > 0, !,
    format(S, $+~D$, [N]).
output_disp(S, N) :-
    N < 0,
    N1 is -N,
    format(S, $-~D$, [N1]).
