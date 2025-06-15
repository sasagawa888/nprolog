
% 1. 条件成功 → then節が実行される
test1 :- ifthenelse(true, write('then'), write('else')), nl.

% 2. 条件失敗 → else節が実行される
test2 :- ifthenelse(fail, write('then'), write('else')), nl.

% 3. then節で fail だがカットなし → else節が実行される 
test3 :- ifthenelse(true, (write('then'), fail), write('else')), nl.

% 4. then節で cut + fail → else節は実行されない（cutによる失敗）
test4 :- ifthenelse(true, (!, fail), write('else')), nl.

% 5. 条件が複数解を持つ → 最初の成功で then節が実行される
p(a).
p(b).
test5 :- ifthenelse(p(X), (write('then: '), write(X), nl), write('else')), nl.

% 6. 条件失敗 → else節が実行される
test6 :- ifthenelse(p(z), write('then'), write('else')), nl.

% 7. ネストした ifthenelse
test7 :- 
    ifthenelse(true,
        ifthenelse(fail, write('then-then'), write('then-else')),
        write('else')
    ), nl.

% カットありで then 節成功
test_cut1 :-
    ifthenelse(true, (write('then1'), !, write('after_cut1')), write('else1')), nl.

% カットありで then 節失敗（カットによる失敗）
test_cut2 :-
    ifthenelse(true, (!, fail), write('else2')), nl.

% カットありで else 節実行（条件失敗）
test_cut3 :-
    ifthenelse(fail, (!, write('then3')), write('else3')), nl.

% カットありで then 節成功だが fail でバックトラックしない
test_cut4 :-
    ifthenelse(true, (write('then4'), !, fail), write('else4')), nl.

% カットなしの then 節失敗で else 節実行（参考用）
test_cut5 :-
    ifthenelse(true, (write('then5'), fail), write('else5')), nl.


for_any(P,Q) :-
        P,
        ifthenelse(Q,fail,(!,fail)).
for_any(P,Q).



% 1. P が単純成功、Q が成功したら fail となり、再度 P から試す。
test_for_any_1 :-
    for_any(member(X, [1,2,3]), (X > 2)).

% 2. P が単純成功、Q が失敗するケース（X > 3 はリストにない）
test_for_any_2 :-
    for_any(member(X, [1,2,3]), (X > 3)).

% 3. P 失敗ケース
test_for_any_3 :-
    for_any(member(X, []), (X > 0)).

% 4. 複雑な条件 P と Q
test_for_any_4 :-
    for_any((member(X, [1,2,3]), X mod 2 =:= 1), (X =:= 1)).

% 5. Q が fail することでバックトラックを促す例
test_for_any_5 :-
    for_any(member(X, [1,2,3]), (X =:= 2)).