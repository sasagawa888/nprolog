% art of Prolog  Compiler
% © 1986, 1994 The MIT Press
% Leon Sterling and Ehud Shapiro

:- use_module(utils).
:- use_module(dcg).

test(A) :-
    open(S,'./tests/pascal.pl',r),
    read_codes(S,C),
    tokenize(C,T),
    compile(T,A).

compile(T,A) :-
    parse(T,A).

parse(S,A) :-
    phrase(pl_program(A),S).

pl_program(A) -->
    [program],identifier(X),[';'],statement(A).

statement((S,Ss)) -->
    [begin],statement(S),rest_statements(Ss).
statement(assign(X,V)) -->
    identifier(X),[':='],expression(V).
statement(if(T,S1,S2)) -->
    [if],test(T),[then],statement(S1),[else],statement(S2).
statement(while(T,S)) -->
    [while],test(T),[do],statement(S).
statement(read(X)) -->
    [read],identifier(X).
statement(write(X)) -->
    [write],expression(X).

rest_statements((S;Ss)) --> [';'],statement(S),rest_statements(Ss).
rest_statements(void) --> [end].

expression(X) --> pl_constant(X).
expression(expr(Op,X,Y)) -->
    pl_constant(X),arithmetic_op(Op),expression(Y).

arithmetic_op('+') --> ['+'].
arithmetic_op('-') --> ['-'].
arithmetic_op('*') --> ['*'].
arithmetic_op('//') --> ['//'].

pl_constant(name(X)) --> identifier(X).
pl_constant(number(X)) --> pl_integer(X).

identifier(X) --> [X],{atom(X)}.
pl_integer(X) --> [X],{integer(X)}.

test(compare(Op,X,Y)) -->
    expression(X),comparison_op(Op),expression(Y).

comparison_op('=') --> ['='].
comparison_op('/=') --> ['/='].
comparison_op('>') --> ['>'].
comparison_op('<') --> ['<'].
comparison_op('>=') --> ['>='].
comparison_op('<=') --> ['<='].
        
%---------------------------------------------
