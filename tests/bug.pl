% testing checker

cdeclare($#define a 1$).

%clibrary($-ltcl -ltk$).

foo(X) :- write(1,2,X).

foo(Y,1) :- \+(Y).
