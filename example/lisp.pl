%Lisp in Prolog
fun(1,2,3). %dummy to avoid existence error

repl :-
    repeat,
    write('> '),
    read(X),
    eval(X,Y,[]),
    write(Y),nl,
    (X=[quit]->true;fail).

eval(X,X,E) :-
    integer(X).
eval(X,X,E) :-
    float(X).
eval(X,Y,E) :-
    atom(X),
    assoc(X,E,Y).
eval(X,Y,E) :-
    atom(X),
    global(X,Y).
eval([quit],t,E).
eval([defun,F,A,B],t,E) :-
    assert(fun(F,A,B)).
eval([setq,X,Y],t,E) :-
    eval(Y,Z,E),
    assert(global(X,Z)).
eval(X,Y,E) :-
    funcall(X,Y,E).

funcall([F|A1],Z,E) :-
    fun(F,A,B),
    argument(A,A1,Y),
    append(Y,E,E1),
    eval(B,Z,E1).
funcall([+,X,Y],Z,E) :-
    eval(X,X1,E),
    eval(Y,Y1,E),
    Z is X1+Y1.
funcall([-,X,Y],Z,E) :-
    eval(X,X1,E),
    eval(Y,Y1,E),
    Z is X1-Y1.
funcall([*,X,Y],Z,E) :-
    eval(X,X1,E),
    eval(Y,Y1,E),
    Z is X1*Y1.
funcall([/,X,Y],Z,E) :-
    eval(X,X1,E),
    eval(Y,Y1,E),
    Z is X1/Y1.

assoc(X,[],Z) :- fail.
assoc(X,[[X|Y]|Ys],Y).
assoc(X,[_|Ys],Z) :-
    assoc(X,Ys,Z).



argument([X],[Y],[X|Y]).
argument([X|Xs],[Y|Ys],[[X|Y],Z]) :-
    argument(Xs,Ys,Z).


global(t,t).
global(nil,nil).

