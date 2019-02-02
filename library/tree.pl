/*
Copyright c M.Hiroi All Rights Reserved.
http://www.geocities.jp/m_hiroi/prolog/index.html
*/
:- module(tree).
:- export([member_tree/2,count_leaf/2,istree/1,search_tree/2,
insert_tree/3,search_max/2,search_min/2,delete_max/2,delete_min/2,
delete_tree/3,traverse_tree/2,pre_traverse_tree/2,post_traverse_tree/2,
tree_of_list/2,list_of_tree/2,height_tree/2,count_node/2,sum_tree/2]).
:- end_module(tree).

:- body(tree).

/*
?- member_tree(5, [1, 2, [3, 4, [5, 6], 7], 8]).
true ;
false.

?- member_tree(X, [1, 2, [3, 4, [5, 6], 7], 8]).
X = 1 ;
X = 2 ;
X = 3 ;
X = 4 ;
X = 5 ;
X = 6 ;
X = 7 ;
X = 8 ;
false.
*/
member_tree(X, X) :- X \= [], atomic(X).
member_tree(X, [L | _]) :- member_tree(X, L).
member_tree(X, [_ | R]) :- member_tree(X, R).

/*
 ?- count_leaf([1, 2, [3, 4, [5, 6], 7], 8], X).
X = 8 ;
false.
*/
count_leaf([], 0).
count_leaf(X, 1) :- X \= [], atomic(X).
count_leaf([X | Xs], N) :-
    count_leaf(X, M1),
    count_leaf(Xs, M2),
    N is M1 + M2.



/*
?- istree(node(5, node(4, nil, nil), node(6, nil, nil))).
true ;
false.

?- istree(node(5, node(4, nil, nil), node(3, nil, nil))).
false.
*/
istree(nil, A, A).
istree(node(X, Left, Right), A, B) :-
    istree(Right, A, C),
    check(X, C),
    istree(Left, X, B).

istree(Node) :- istree(Node, nil, _).

/*
?- search_tree(5, node(5, node(4, nil, nil), node(6, nil, nil))).
true ;
false.

?- search_tree(1, node(5, node(4, nil, nil), node(6, nil, nil))).
false.
*/
search_tree(X, node(X, _, _)).
search_tree(X, node(Y, Left, _)) :- X < Y, search_tree(X, Left).
search_tree(X, node(Y, _, Right)) :- X > Y, search_tree(X, Right).

/*
?- insert_tree(1, node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = node(5, node(4, node(1, nil, nil), nil), node(6, nil, nil)) ;
false.

?- insert_tree(9, node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = node(5, node(4, nil, nil), node(6, nil, node(9, nil, nil))) ;
false.
*/
insert_tree(X, nil, node(X, nil, nil)).
insert_tree(X, node(X, Left, Right), node(X, Left, Right)).
insert_tree(X, node(Y, Left, Right), node(Y, New_node, Right)) :-
    X < Y, insert_tree(X, Left, New_node).
insert_tree(X, node(Y, Left, Right), node(Y, Left, New_node)) :-
    X > Y, insert_tree(X, Right, New_node).

/*
?- search_max(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 6 ;
false.
*/
search_max(node(X, _, nil), X).
search_max(node(_, _, Right), X) :- search_max(Right, X).


/*
?- search_min(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 4 ;
false
*/
search_min(node(X, nil, _), X).
search_min(node(_, Left, _), X) :- search_min(Left, X).

/*
?- delete_max(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 6 ;
false.
*/
delete_max(node(_, Left, nil), Left).
delete_max(node(X, Left, Right), node(X, Left, New_node)) :-
    delete_max(Right, New_node).

/*
?- delete_min(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 4 ;
false.
*/
delete_min(node(_, nil, Right), Right).
delete_min(node(X, Left, Right), node(X, New_node, Right)) :-
    delete_min(Left, New_node).

/*
?- delete_tree(5, node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = node(6, node(4, nil, nil), nil) ;
false.

?- delete_tree(4, node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = node(5, nil, node(6, nil, nil)) ;
false.

?- delete_tree(6, node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = node(5, node(4, nil, nil), nil).

?- delete_tree(0, node(5, node(4, nil, nil), node(6, nil, nil)), X).
false.
*/
delete_tree(X, node(X, Left, nil), Left) :- !.
delete_tree(X, node(X, nil, Right), Right) :- !.
delete_tree(X, node(X, Left, Right), node(Min_value, Left, New_node)) :-
    search_min(Right, Min_value),
    delete_min(Right, New_node).
delete_tree(X, node(Y, Left, Right), node(Y, New_node, Right)) :-
    X < Y, delete_tree(X, Left, New_node). 
delete_tree(X, node(Y, Left, Right), node(Y, Left, New_node)) :-
    X > Y, delete_tree(X, Right, New_node). 

/*
?- traverse_tree(X, node(5, node(4, nil, nil), node(6, nil, nil))).
X = 4 ;
X = 5 ;
X = 6 ;
false.
*/
traverse_tree(X, node(_, Left, _)) :- traverse_tree(X, Left).
traverse_tree(X, node(X, _, _)).  
traverse_tree(X, node(_, _, Right)) :- traverse_tree(X, Right).

/*
?- pre_traverse_tree(X, node(5, node(4, nil, nil), node(6, nil, nil))).
X = 5 ;
X = 4 ;
X = 6 ;
false.
*/
pre_traverse_tree(X, node(X, _, _)).  
pre_traverse_tree(X, node(_, Left, _)) :- pre_traverse_tree(X, Left).
pre_traverse_tree(X, node(_, _, Right)) :- pre_traverse_tree(X, Right).

/*
?- post_traverse_tree(X, node(5, node(4, nil, nil), node(6, nil, nil))).
X = 4 ;
X = 6 ;
X = 5.
*/
post_traverse_tree(X, node(_, Left, _)) :- post_traverse_tree(X, Left).
post_traverse_tree(X, node(_, _, Right)) :- post_traverse_tree(X, Right).
post_traverse_tree(X, node(X, _, _)). 

/*
?- tree_of_list([3,4,1,2,5], X).
X = node(3, node(1, nil, node(2, nil, nil)), node(4, nil, node(5, nil, nil))) ;
false.
*/
tree_of_list(Xs, Tree) :- tree_of_list(Xs, nil, Tree).
tree_of_list([], Tree, Tree).
tree_of_list([X|Xs], Node, Tree) :-
    insert_tree(X, Node, New_node), tree_of_list(Xs, New_node, Tree).


/*
?- list_of_tree(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = [4, 5, 6].
*/
list_of_tree(Tree, Xs) :- findall(X, traverse_tree(X, Tree), Xs).


/*
?- height_tree(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 2.
*/
height_tree(nil, 0).
height_tree(node(_, Left, Right), H) :-
    height_tree(Left, H1),
    height_tree(Right, H2),
    (H1 > H2 -> H is H1 + 1; H is H2 + 1).


/*
?- count_node(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 3.
*/
count_node(nil, 0).
count_node(node(_, Left, Right), N) :-
  count_node(Left, N1),
  count_node(Right, N2),
  N is N1 + N2 + 1.

/*
?- sum_tree(node(5, node(4, nil, nil), node(6, nil, nil)), X).
X = 15.
*/
sum_tree(nil, 0).
sum_tree(node(X, Left, Right), N) :-
    sum_tree(Left, N1),
    sum_tree(Right, N2),
    N is N1 + N2 + X.

:- end_body(tree).
