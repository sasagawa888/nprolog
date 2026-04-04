%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% compiler_stress.pl
% N-Prolog compiler stress test
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
?- test_formula(F).
?- test_if(A,B,C,D).
?- test_recompute(L).
?- test_share(R1,R2,R3).
?- test_mixed(L).
?- test_meta(L).
?- test_collect(F,S).
?- test_dcg1(Tree).
?- test_dcg2(N).
?- test_catch(R1,R2).
?- test_sum(S1,S2).
?- test_weird(L).
?- test_kind(K1,K2,K3).
?- test_transform(R).
*/


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 1. 項としての forall / exist / imply
%    述語呼び出しではなく「単なる項」として扱わせるテスト
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

formula(ex1,
  forall(x,
    imply(p(x),
      exist(y,
        and(q(x,y), r(y)))
))).

formula(ex2,
  exist(z,
    and(
      forall(x, imply(human(x), mortal(x))),
      human(z)
))).

formula(ex3,
  imply(
    and(p(a), q(b)),
    exist(y, and(r(y), s(a,y)))
)).

formula_head(functor_case(forall(x, p(x)))).
formula_head(functor_case(exist(y, q(y)))).
formula_head(functor_case(imply(p, q))).

pick_formula(Name, F) :-
    formula(Name, F).

pick_formula_head(X) :-
    formula_head(X).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2. -> ; の入れ子
%    if-then-else 周りのコード生成確認
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

classify_num(N, X) :-
    ( N < 0 ->
        X = negative
    ; N =:= 0 ->
        X = zero
    ; N < 10 ->
        X = small
    ; N < 100 ->
        X = medium
    ;
        X = large
    ).

nested_if(A, B, X) :-
    ( A > 0 ->
        ( B > 0 ->
            X = both_positive
        ;
            X = a_only
        )
    ;
        ( B > 0 ->
            X = b_only
        ;
            X = none_positive
        )
    ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 3. between/3 + is/2
%    バックトラック時に is/2 の再評価が正しいか
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

gen_pair_sum(Low, High, X, Y, Z) :-
    between(Low, High, X),
    between(Low, High, Y),
    Z is X + Y.

gen_weighted(Low, High, X, Y, Z) :-
    between(Low, High, X),
    A is X * 2,
    between(Low, High, Y),
    Z is A + Y.

recompute_test(N, X, Y) :-
    between(1, N, X),
    Y is X * X.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 4. 変数の受け渡しが微妙なケース
%    同一変数・構造展開・部分構造の共有
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

same_shape(node(A, leaf(B), A), node(X, leaf(Y), X), pair(A,B,X,Y)).

share_var_test(X, Y, Z) :-
    T = foo(X, Y, X),
    T = foo(a, Z, a).

nested_unify(Result) :-
    X = f(A, g(B, A), B),
    Result = X.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 5. 決定性と非決定性の混在
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

det_or_nondet(a, 1).
det_or_nondet(b, 2).
det_or_nondet(b, 3).
det_or_nondet(c, 4).

mixed_flow(Key, Value, Tag) :-
    det_or_nondet(Key, Value),
    ( Value mod 2 =:= 0 ->
        Tag = even
    ;
        Tag = odd
    ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 6. call/1 を使うメタ呼び出し
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goal(member(a, [x,a,z])).
goal(append([1,2], [3,4], [1,2,3,4])).
goal(between(1,3,2)).
goal(classify_num(15, medium)).

run_goal(Name, Goal, ok) :-
    named_goal(Name, Goal),
    call(Goal).

named_goal(g1, member(a, [x,a,z])).
named_goal(g2, append([1,2], [3], [1,2,3])).
named_goal(g3, classify_num(0, zero)).
named_goal(g4, nested_if(1, -1, a_only)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 7. findall / setof / bagof
%    非決定述語との組合せ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

edge(a,b).
edge(a,c).
edge(b,d).
edge(c,d).
edge(c,e).

path1(X,Y) :- edge(X,Y).
path1(X,Y) :- edge(X,Z), edge(Z,Y).

collect_paths_from(X, L) :-
    findall(Y, path1(X,Y), L).

collect_sorted_paths_from(X, L) :-
    setof(Y, path1(X,Y), L).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 8. DCG + {} のテスト
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
:- use_module(dcg).

sentence(s(NP,VP)) --> noun_phrase(NP, N), verb_phrase(VP, N).

noun_phrase(np(Det,Noun), N) -->
    det(Det),
    noun(Noun, N).

verb_phrase(vp(Verb), N) -->
    verb(Verb, N).

verb_phrase(vp(Verb, NP), N) -->
    trans_verb(Verb, N),
    noun_phrase(NP, _).

det(det(the)) --> [the].
det(det(a))   --> [a].

noun(noun(cat), singular) --> [cat].
noun(noun(dog), singular) --> [dog].
noun(noun(cats), plural)  --> [cats].
noun(noun(dogs), plural)  --> [dogs].

verb(verb(runs), singular) --> [runs].
verb(verb(run),  plural)   --> [run].

trans_verb(tv(chases), singular) --> [chases].
trans_verb(tv(chase),  plural)   --> [chase].

filtered_noun(N) -->
    [N],
    { N = cat ; N = dog ; N = cats ; N = dogs }.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 9. DCG 内でのちょっと変わった計算
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

digits_value(Value) -->
    digits(Ds),
    { number_from_digits(Ds, 0, Value) }.

digits([D|Ds]) --> digit(D), digits_rest(Ds).
digits_rest([D|Ds]) --> digit(D), !, digits_rest(Ds).
digits_rest([]) --> [].

digit(0) --> [0].
digit(1) --> [1].
digit(2) --> [2].
digit(3) --> [3].
digit(4) --> [4].
digit(5) --> [5].
digit(6) --> [6].
digit(7) --> [7].
digit(8) --> [8].
digit(9) --> [9].

number_from_digits([], Acc, Acc).
number_from_digits([D|Ds], Acc, Value) :-
    Acc1 is Acc * 10 + D,
    number_from_digits(Ds, Acc1, Value).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 10. catch / throw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

may_fail(0) :- throw(zero_division_like).
may_fail(N) :- N > 0.

safe_run(N, Result) :-
    catch(
        ( may_fail(N), Result = ok ),
        Error,
        Result = error(Error)
    ).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 11. 再帰 + 末尾再帰最適化候補
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

sum_list_tail(L, S) :-
    sum_list_tail(L, 0, S).

sum_list_tail([], Acc, Acc).
sum_list_tail([X|Xs], Acc, S) :-
    Acc1 is Acc + X,
    sum_list_tail(Xs, Acc1, S).

sum_list_non_tail([], 0).
sum_list_non_tail([X|Xs], S) :-
    sum_list_non_tail(Xs, S1),
    S is X + S1.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 12. append/member/between を混ぜた少し嫌なコード
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

weird_combo(X, Y, Z) :-
    append(A, B, [1,2,3,4]),
    member(X, A),
    member(Y, B),
    Z is X + Y.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 13. compound/ground の分岐
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

term_kind(T, ground_compound) :-
    compound(T),
    ground(T), !.
term_kind(T, nonground_compound) :-
    compound(T), !.
term_kind(T, atomic) :-
    atomic(T).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 14. 多段の構造変換
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

transform_term(Term, Result) :-
    Term = input(A, B, meta(forall(x, p(x)))),
    Result = output(B, A, meta(forall(x, p(x)))).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 15. 実行確認用
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

test_formula(F) :-
    pick_formula(ex1, F).

test_if(X1, X2, X3, X4) :-
    classify_num(-3, X1),
    classify_num(0, X2),
    classify_num(7, X3),
    classify_num(300, X4).

test_recompute(L) :-
    findall((X,Y), recompute_test(5, X, Y), L).

test_share(R1, R2, R3) :-
    same_shape(node(a, leaf(b), a), node(X, leaf(Y), X), R1),
    share_var_test(_, _, R2),
    nested_unify(R3).

test_mixed(L) :-
    findall((V,T), mixed_flow(b, V, T), L).

test_meta(L) :-
    findall(Name, run_goal(Name, _, ok), L).

test_collect(F, S) :-
    collect_paths_from(a, F),
    collect_sorted_paths_from(a, S).

test_dcg1(Tree) :-
    phrase(sentence(Tree), [the,dog,chases,a,cat]).

test_dcg2(N) :-
    phrase(digits_value(N), [1,2,3,4]).

test_catch(R1, R2) :-
    safe_run(3, R1),
    safe_run(0, R2).

test_sum(S1, S2) :-
    sum_list_tail([1,2,3,4,5], S1),
    sum_list_non_tail([1,2,3,4,5], S2).

test_weird(L) :-
    findall((X,Y,Z), weird_combo(X,Y,Z), L).

test_kind(K1, K2, K3) :-
    term_kind(foo(bar,baz), K1),
    term_kind(foo(X,baz), K2),
    term_kind(abc, K3).

test_transform(R) :-
    transform_term(input(1, 2, meta(forall(x,p(x)))), R).