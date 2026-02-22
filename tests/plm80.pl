%PLM80


:- use_module(utils).
:- use_module(dcg).

test(A) :-
    open(S,'./tests/plm1.pl',r),
    read_codes(S,C),
    tokenize(C,T),write(T),nl,
    compile(T,A),
    close(S).

compile(T,A) :-
    parse(T,A).

parse(S,A) :-
    phrase(program(A),S).

program(A) --> pl_module(A).
program(A) --> statements(A).

pl_module(module(X,S)) -->
    identifier(X), [':'],
    ['DO'], [';'],
    statements(S),
    ['END'], identifier(X), [';'].


statements([])  --> [].
statements([S|Ss]) --> statement(S),statements(Ss).


statement(while(V,S)) -->
    ['DO'],['WHILE'],test(V),[';'],statements(S),['END'],[';'].
statement(case(V,S)) -->
    ['DO'],['CASE'],test(V),[';'],statements(S),['END'],[';'].
statement(if(V,S1,S2)) -->
    ['IF'],test(V),['THEN'],statement(S1),['ELSE'],statement(S2).    
statement(if(V,S)) -->
    ['IF'],test(V),['THEN'],statement(S).
statement(proc(N,P,S,T)) -->
    identifier(N),[':'],['PROCEDURE'],param(P),data_type(T),[';'],
    statements(S),['END'],identifier(N),[';'].
statement(assign(X,V)) -->
    identifier(X),['='],expression(V),[';'].
statement(return(S)) -->
    ['RETURN'],expression(S),[';'].
statement(return(void)) -->
    ['RETURN'],[';'].    
statement(declare(P,T)) -->
    ['DECLARE'],param(P),data_type(T),[';'].
statement(declare(V,T)) -->
    ['DECLARE'],identifier(V),data_type(T),[';'].
statement(label(N,S)) -->
    identifier(N),[':'],statement(S).
statement(goto(N)) -->
    ['GOTO'],identifier(N),[';'].
statement(halt) -->
    ['HALT'],[';'].
statement(block(S)) -->
    block(S).

block(S) -->
    ['DO'],[';'],statements(S),['END'],[';'].


param(S) -->
    ['('],params(S),[')'].

params([]) --> [].
params([S]) --> identifier(S).
params([S]) --> pl_constant(S).
params([S|Ss]) -->
    identifier(S),[','],params(Ss).
params([S|Ss]) -->
    pl_constant(S),[','],params(Ss).



expression(X) --> pl_constant(X).
expression(X) --> pl_function(X).
expression(E) --> add_expr(E).

add_expr(E) -->
    mul_expr(T),
    add_rest(T, E).

add_rest(Acc, E) -->
    add_op(Op),
    mul_expr(T),
    { Acc1 = expr(Op, Acc, T) },
    add_rest(Acc1, E).
add_rest(Acc, Acc) --> [].

mul_expr(E) -->
    primary(P),
    mul_rest(P, E).

mul_rest(Acc, E) -->
    mul_op(Op),
    primary(P),
    { Acc1 = expr(Op, Acc, P) },
    mul_rest(Acc1, E).
mul_rest(Acc, Acc) --> [].

add_op('+') --> ['+'].
add_op('-') --> ['-'].

mul_op('*') --> ['*'].
mul_op('//') --> ['//'].

primary(E) --> pl_constant(E).
primary(E) --> pl_function(E).
primary(E) --> ['('], expression(E), [')'].


arithmetic_op('+') --> ['+'].
arithmetic_op('-') --> ['-'].
arithmetic_op('*') --> ['*'].
arithmetic_op('//') --> ['//'].


pl_constant(name(X)) --> identifier(X).
pl_constant(number(X)) --> pl_integer(X).

pl_function(func(N,P)) --> identifier(N),param(P).

identifier(X) --> [X],{atom(X),not(reserved(X))}.
pl_integer(X) --> [X],{integer(X)}.

reserved('DO'). reserved('END'). reserved('WHILE'). reserved('CASE').
reserved('IF'). reserved('THEN'). reserved('ELSE').
reserved('PROCEDURE'). reserved('DECLARE'). reserved('RETURN').
reserved('GOTO'). reserved('HALT').
reserved('ADDRESS'). reserved('BYTE').
reserved('AND'). reserved('OR'). reserved('XOR').


test(comp(Op,X,Y)) -->
    expression(X),comparison_op(Op),expression(Y).


comparison_op('=') --> ['='].
comparison_op('<>') --> ['<>'].
comparison_op('>') --> ['>'].
comparison_op('<') --> ['<'].
comparison_op('>=') --> ['>='].
comparison_op('<=') --> ['<='].

logic_op(and) --> ['AND'].
logic_op(or) --> ['OR'].
logic_op(xor) --> ['XOR'].

data_type(addr) --> ['ADDRESS'].
data_type(byte) --> ['BYTE'].

% =========================================================
% plm80_encode_nodcg.pl
% AST -> Z80 asm items (NO DCG used)
%
% Conventions:
% - expression result is always in HL (16-bit)
% - binary ops:
%     eval left -> HL, PUSH HL
%     eval right -> HL
%     POP DE
%     + : ADD HL,DE
%     * : CALL MUL16   (DE * HL -> HL)
% - call:
%     push args right-to-left, each as 16-bit in HL then PUSH HL
%     CALL Proc
%     caller cleans args: ADD SP, 2*arity
% - proc frame with IX:
%     PUSH IX ; LD IX,0 ; ADD IX,SP
%     arg1 at (IX+4)/(IX+5), arg2 at (IX+6)/(IX+7) ...
% =========================================================

% ---------- entry ----------
encode(AST, Asm) :-
    encode_program(AST, Asm, []).

% ---------- program ----------
encode_program(Stmts, Asm0, Asm) :-
    encode_toplevel(Stmts, Asm0, Asm).

encode_toplevel([], Asm, Asm).
encode_toplevel([S|Ss], Asm0, Asm) :-
    encode_top_stmt(S, Asm0, Asm1),
    encode_toplevel(Ss, Asm1, Asm).

encode_top_stmt(proc(Name, Params, Body, RetType), Asm0, Asm) :-
    proc_env(Name, Params, RetType, Env),
    emit_label(Name, Asm0, A1),
    emit(instr('PUSH',[ix]), A1, A2),
    emit(instr('LD',[ix,0]), A2, A3),
    emit(instr('ADD',[ix,sp]), A3, A4),
    encode_proc_body(Body, Env, A4, A5),
    emit(instr('POP',[ix]), A5, A6),
    emit(instr('RET',[]), A6, Asm).

encode_top_stmt(label(L, Stmt), Asm0, Asm) :-
    emit_label(L, Asm0, A1),
    encode_stmt(Stmt, top_env, A1, Asm).

encode_top_stmt(label(L), Asm0, Asm) :-
    emit_label(L, Asm0, Asm).

encode_top_stmt(halt, Asm0, Asm) :-
    emit_label('HALT_LABEL', Asm0, A1),
    emit(instr('HALT',[]), A1, A2),
    emit(instr('JP',['HALT_LABEL']), A2, Asm).

% ---------- proc body ----------
encode_proc_body([], _Env, Asm, Asm).
encode_proc_body([declare(_Vars,_Type)|Ss], Env, Asm0, Asm) :-
    % ignore declare in this minimal encoder
    encode_proc_body(Ss, Env, Asm0, Asm).
encode_proc_body([S|Ss], Env, Asm0, Asm) :-
    encode_stmt(S, Env, Asm0, Asm1),
    encode_proc_body(Ss, Env, Asm1, Asm).

% ---------- statements ----------
encode_stmt(assign(Var, Expr), Env, Asm0, Asm) :-
    encode_expr(Expr, Env, Asm0, Asm1),
    store_var16(Var, Env, Asm1, Asm).

encode_stmt(return(Expr), Env, Asm0, Asm) :-
    encode_expr(Expr, Env, Asm0, Asm).

encode_stmt(halt, _Env, Asm0, Asm) :-
    emit_label('HALT_LABEL', Asm0, A1),
    emit(instr('HALT',[]), A1, A2),
    emit(instr('JP',['HALT_LABEL']), A2, Asm).

% 予備：未対応stmtは無視（必要なら失敗させてもOK）
encode_stmt(_Other, _Env, Asm, Asm).

% ---------- expressions (result in HL) ----------
encode_expr(number(N), _Env, Asm0, Asm) :-
    emit(instr('LD',[hl,N]), Asm0, Asm).

encode_expr(name(X), Env, Asm0, Asm) :-
    load_var16(X, Env, Asm0, Asm).

encode_expr(func(Name, Args), Env, Asm0, Asm) :-
    push_args_r2l(Args, Env, Asm0, A1),
    emit(instr('CALL',[Name]), A1, A2),
    list_length(Args, Arity),
    Bytes is Arity*2,
    ( Bytes =:= 0 ->
        Asm = A2
    ;   emit(instr('ADD',[sp,Bytes]), A2, Asm)
    ).

encode_expr(expr('+',A,B), Env, Asm0, Asm) :-
    encode_expr(A, Env, Asm0, A1),
    emit(instr('PUSH',[hl]), A1, A2),
    encode_expr(B, Env, A2, A3),
    emit(instr('POP',[de]), A3, A4),
    emit(instr('ADD',[hl,de]), A4, Asm).

encode_expr(expr('*',A,B), Env, Asm0, Asm) :-
    encode_expr(A, Env, Asm0, A1),
    emit(instr('PUSH',[hl]), A1, A2),
    encode_expr(B, Env, A2, A3),
    emit(instr('POP',[de]), A3, A4),
    emit(instr('CALL',['MUL16']), A4, Asm).

% 未対応exprは0に
encode_expr(_Other, _Env, Asm0, Asm) :-
    emit(instr('LD',[hl,0]), Asm0, Asm).

% ---------- pushing args right-to-left ----------
push_args_r2l(Args, Env, Asm0, Asm) :-
    rev(Args, Rev),
    push_args_l2r(Rev, Env, Asm0, Asm).

push_args_l2r([], _Env, Asm, Asm).
push_args_l2r([A|As], Env, Asm0, Asm) :-
    encode_expr(A, Env, Asm0, A1),
    emit(instr('PUSH',[hl]), A1, A2),
    push_args_l2r(As, Env, A2, Asm).

% ---------- load/store vars (16-bit) ----------
% Params: (IX+off) ; Globals: (Label)
load_var16(Var, Env, Asm0, Asm) :-
    ( param_offset(Env, Var, Off) ->
        emit(instr('LD',[l, mem(ix,Off)]), Asm0, A1),
        Off1 is Off + 1,
        emit(instr('LD',[h, mem(ix,Off1)]), A1, Asm)
    ;   emit(instr('LD',[hl, mem_label(Var)]), Asm0, Asm)
    ).

store_var16(Var, Env, Asm0, Asm) :-
    ( param_offset(Env, Var, Off) ->
        emit(instr('LD',[mem(ix,Off), l]), Asm0, A1),
        Off1 is Off + 1,
        emit(instr('LD',[mem(ix,Off1), h]), A1, Asm)
    ;   emit(instr('LD',[mem_label(Var), hl]), Asm0, Asm)
    ).


% ---------- env / offsets ----------
proc_env(Name, Params, RetType, env(Name, POffs, RetType)) :-
    param_offsets(Params, 4, POffs).

param_offsets([], _Off, []).
param_offsets([P|Ps], Off0, [P-Off0|Rest]) :-
    Off1 is Off0 + 2,
    param_offsets(Ps, Off1, Rest).

param_offset(env(_Name,POffs,_Ret), Var, Off) :-
    member(Var-Off, POffs).
param_offset(top_env, _Var, _Off) :- fail.

% ---------- utilities ----------
emit(Item, [Item|Rest], Rest).

emit_label(L, Asm0, Asm) :-
    emit(label(L), Asm0, Asm).

%member(X, [X|_]).
%member(X, [_|Xs]) :- member(X, Xs).

list_length([], 0).
list_length([_|Xs], N) :- list_length(Xs, N1), N is N1 + 1.

rev(L, R) :- rev1(L, [], R).
rev1([], A, A).
rev1([X|Xs], A, R) :- rev1(Xs, [X|A], R).

% ---------- (optional) simple printer ----------
% テキスト化が不要なら使わなくてOK。
print_asm([]).
print_asm([label(L)|Xs]) :-
    write(L), write(':'), nl,
    print_asm(Xs).
print_asm([instr(Op,Args)|Xs]) :-
    write('    '), write(Op),
    ( Args = [] -> true ; write(' '), write(Args) ),
    nl,
    print_asm(Xs).