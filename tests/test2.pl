% 知識ベース
parent(alice, bob).
parent(bob, charlie).
parent(charlie, diana).

% ルール
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

% テスト
test_grandparent :-
    grandparent(alice, charlie),
    grandparent(bob, diana),
    \+ grandparent(alice, diana).

% 実行
:- test_grandparent.

% 知識ベース
ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).

% テスト
test_ancestor :-
    ancestor(alice, diana),
    \+ ancestor(bob, alice),
    ancestor(charlie, diana).

% 実行
:- test_ancestor.

% 知識ベース
likes(john, pizza).
likes(mary, pizza).
likes(john, sushi).

% ルール
likes_pizza(X) :- likes(X, pizza).

% テスト
test_likes_pizza :-
    likes_pizza(john),
    likes_pizza(mary),
    \+ likes_pizza(susan).

% 実行
:- test_likes_pizza.

% テスト
test_append :-
    append([1, 2], [3, 4], [1, 2, 3, 4]),
    \+ append([1], [2, 3], [1, 3]).

% 実行
:- test_append.

% 階層的な構造
factorial(0, 1).
factorial(N, F) :- N > 0, N1 is N - 1, factorial(N1, F1), F is N * F1.

% テスト
test_factorial :-
    factorial(5, 120),
    \+ factorial(4, 100),
    factorial(0, 1).

% 実行
:- test_factorial.

% 知識ベース
person(john, 30).
person(mary, 25).
person(alice, 35).

% ルール
older_than(X, Age) :- person(X, Age1), Age1 > Age.

% テスト
test_older_than :-
    older_than(alice, 30),
    \+ older_than(john, 35),
    older_than(mary, 20).

% 実行
:- test_older_than.

% 知識ベース
animal(dog).
animal(cat).
animal(bird).

% 条件付きルール
pet(X) :- animal(X), !.
pet(cat).

% より具体的なルール
pet(dog) :- !.
pet(bird) :- fail.

% テストケース
test_cut :-
    % pet/1 は cat と dog のいずれかを返すことを期待する
    (pet(dog) -> write('dog passed'); write('dog failed')), nl,
    (pet(cat) -> write('cat passed'); write('cat failed')), nl,
    (pet(bird) -> write('bird passed'); write('bird failed')), nl.

% 実行
:- test_cut.