% CLPFD test

:- use_module(clpfd).

foo(X,Y) :-
    X in 1..2,
    Y in 1..3,
    X #= Y,
    label([X,Y]).

/*
 domain    env
[]         [[1,2],[1,2,3]]

 X Y       [[1,2],[1,2]]
[[1,1] 
 [2,2]] 
*/

bar(X,Y,Z) :-
    X in 1..2,
    Y in 1..3,
    Z in 1..3,
    X #= Y,
    Z #= 3,
    label([X,Y,Z]).

/* idea memo
  domain          env
[]              [[1,2],[1,2,3],[1,2,3]]
|          
  x,y,z         [[1,2],[1,2],[1,2,3]]
[[1,1,*]
 [2,2,*]]
|               [[1,2],[1,2],[3]]]
[[1,1,3] 
 [2,2,3]]

*/

boo(X,Y,Z) :-
    X in 1..2,
    Y in 1..3,
    Z in 1..3,
    X #= Y,
    Z #< 3,
    label([X,Y,Z]).

/* idea memo
domain       env
  x,y,z     [[1,2],[1,2],[1,2,3]]
[[1,1,*]
 [2,2,*]]
  |   
[[1,1,*]    [[1,2],[1,2],[1,2]]
 [2,2,*]]

*/