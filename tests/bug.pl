
funcall([/,X,Y],Z,E) :-
    eval(X,X1,E),
    eval(Y,Y1,E),
    Z is X1/Y1.


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
