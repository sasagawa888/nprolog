%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% dynamic_stress.pl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
?- test_basic(L).
?- test_retract(L1, L2).
?- test_retractall(L1, L2).
?- test_dyn2(L).
?- test_wrapped(L1, L2).
?- test_call(L).
?- test_fail_then_assert(R1, R2).
?- test_counter(N1, N2, N3).
?- test_path(L1, L2).
?- test_hook(R1, R2, R3).
?- test_assert_order(L1, L2).
?- test_collect(L1, L2).
?- test_if_dyn(R1, R2).
*/


:- dynamic(dyn1/1).
:- dynamic(dyn2/2).
:- dynamic(counter/1).
:- dynamic(store/1).
:- dynamic(edge/2).
:- dynamic(hook/1).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 0. 初期化
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

reset_dyn :-
    retractall(dyn1(_)),
    retractall(dyn2(_,_)),
    retractall(counter(_)),
    retractall(store(_)),
    retractall(edge(_,_)),
    retractall(hook(_)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 1. いちばん基本
%    コンパイル済みコードから dynamic 述語が見えるか
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

add_dyn1(X) :-
    assertz(dyn1(X)).

get_dyn1(X) :-
    dyn1(X).

test_basic(L) :-
    reset_dyn,
    add_dyn1(a),
    add_dyn1(b),
    findall(X, get_dyn1(X), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2. retract の反映
%    いったん追加したものを消したら、コンパイル済み呼び出し側で
%    ちゃんと反映されるか
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

del_dyn1(X) :-
    retract(dyn1(X)).

test_retract(L1, L2) :-
    reset_dyn,
    add_dyn1(a),
    add_dyn1(b),
    findall(X, dyn1(X), L1),
    del_dyn1(a),
    findall(X, dyn1(X), L2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 3. retractall の反映
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test_retractall(L1, L2) :-
    reset_dyn,
    add_dyn1(x),
    add_dyn1(y),
    findall(X, dyn1(X), L1),
    retractall(dyn1(_)),
    findall(X, dyn1(X), L2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 4. 複数引数
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

add_dyn2(X,Y) :-
    assertz(dyn2(X,Y)).

pair_sum(X,Y,Z) :-
    dyn2(X,Y),
    Z is X + Y.

test_dyn2(L) :-
    reset_dyn,
    add_dyn2(1,2),
    add_dyn2(3,4),
    findall((X,Y,Z), pair_sum(X,Y,Z), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 5. dynamic を呼ぶ静的述語
%    これがコンパイルで固定化されるとまずい
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

wrapped_dyn1(X) :-
    dyn1(X).

test_wrapped(L1, L2) :-
    reset_dyn,
    assertz(dyn1(foo)),
    findall(X, wrapped_dyn1(X), L1),
    assertz(dyn1(bar)),
    findall(X, wrapped_dyn1(X), L2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 6. call/1 経由
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

call_dyn1(X) :-
    Goal = dyn1(X),
    call(Goal).

test_call(L) :-
    reset_dyn,
    assertz(dyn1(p)),
    assertz(dyn1(q)),
    findall(X, call_dyn1(X), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 7. 失敗後に assert して再試行
%    failure をコンパイル時に固定していないか
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

exists_zzz :-
    dyn1(zzz).

test_fail_then_assert(R1, R2) :-
    reset_dyn,
    ( exists_zzz -> R1 = yes ; R1 = no ),
    assertz(dyn1(zzz)),
    ( exists_zzz -> R2 = yes ; R2 = no ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 8. counter 風
%    読み出し→更新→読み出し
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

init_counter :-
    retractall(counter(_)),
    assertz(counter(0)).

inc_counter :-
    retract(counter(N)),
    N1 is N + 1,
    assertz(counter(N1)).

get_counter(N) :-
    counter(N).

test_counter(N1, N2, N3) :-
    reset_dyn,
    init_counter,
    get_counter(N1),
    inc_counter,
    get_counter(N2),
    inc_counter,
    get_counter(N3).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 9. バックトラックと dynamic
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test_backtrack(L) :-
    reset_dyn,
    assertz(dyn1(a)),
    assertz(dyn1(b)),
    assertz(dyn1(c)),
    findall(X, dyn1(X), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 10. バックトラック中に使う計算
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

dyn_calc(X,Y,Z) :-
    dyn2(X,Y),
    Z is X * 10 + Y.

test_dyn_calc(L) :-
    reset_dyn,
    assertz(dyn2(1,2)),
    assertz(dyn2(3,4)),
    assertz(dyn2(5,6)),
    findall(Z, dyn_calc(_,_,Z), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 11. 再帰の中で dynamic を使う
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

path(X,Y) :-
    edge(X,Y).
path(X,Y) :-
    edge(X,Z),
    path(Z,Y).

test_path(L1, L2) :-
    reset_dyn,
    assertz(edge(a,b)),
    assertz(edge(b,c)),
    findall(Y, path(a,Y), L1),
    assertz(edge(c,d)),
    findall(Y, path(a,Y), L2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 12. dynamic の有無で分岐
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

hooked(X) :-
    hook(X), !.
hooked(default).

test_hook(R1, R2, R3) :-
    reset_dyn,
    hooked(R1),
    assertz(hook(custom)),
    hooked(R2),
    retractall(hook(_)),
    hooked(R3).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 13. asserta / assertz の順序
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test_assert_order(L1, L2) :-
    reset_dyn,
    assertz(dyn1(z)),
    asserta(dyn1(a)),
    findall(X, dyn1(X), L1),
    asserta(dyn1(head)),
    findall(X, dyn1(X), L2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 14. 同じ dynamic を複数箇所から呼ぶ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

reader1(X) :- dyn1(X).
reader2(X) :- dyn1(X).
reader3(X) :- dyn1(X).

test_multi_reader(L1, L2, L3) :-
    reset_dyn,
    assertz(dyn1(alpha)),
    findall(X, reader1(X), L1),
    findall(X, reader2(X), L2),
    findall(X, reader3(X), L3).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 15. 動的データを経由して call/1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

run_hooked_goal(Result) :-
    store(Goal),
    call(Goal),
    Result = success.

test_stored_goal(R1, R2) :-
    reset_dyn,
    assertz(store(dyn1(a))),
    ( run_hooked_goal(R1) -> true ; R1 = fail ),
    assertz(dyn1(a)),
    ( run_hooked_goal(R2) -> true ; R2 = fail ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 16. retract しながら走査
%    実装によっては壊れやすい
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

consume_dyn1([], []).
consume_dyn1([X|Xs], Rest) :-
    retract(dyn1(X)),
    consume_dyn1(Xs, Rest).
consume_dyn1([], Rest) :-
    findall(Y, dyn1(Y), Rest).

test_consume(Taken, Rest) :-
    reset_dyn,
    assertz(dyn1(a)),
    assertz(dyn1(b)),
    assertz(dyn1(c)),
    consume_dyn1(Taken, Rest).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 17. dynamic 述語を if-then-else の条件に使う
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% compile error
/*
check_dyn1(X, yes) :-
    (dyn1(X) -> true ; fail ).
check_dyn1(X, no) :-
    \+ dyn1(X).
*/
test_if_dyn(R1, R2) :-
    reset_dyn,
    check_dyn1(a, R1),
    assertz(dyn1(a)),
    check_dyn1(a, R2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 18. dynamic + findall
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

collect_dyn1(L) :-
    findall(X, dyn1(X), L).

test_collect(L1, L2) :-
    reset_dyn,
    assertz(dyn1(10)),
    assertz(dyn1(20)),
    collect_dyn1(L1),
    assertz(dyn1(30)),
    collect_dyn1(L2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 19. dynamic を介した非決定呼び出し
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

choose_and_wrap(X, Y) :-
    dyn1(X),
    Y = value(X).

test_choose_wrap(L) :-
    reset_dyn,
    assertz(dyn1(red)),
    assertz(dyn1(blue)),
    findall(Y, choose_and_wrap(_, Y), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 20. 総合テスト
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test_all(A,B,C,D,E,F,G,H,I,J) :-
    test_basic(A),
    test_retract(B, C),
    test_counter(D, E, F),
    test_call(G),
    test_path(H, I),
    test_collect(J, _).