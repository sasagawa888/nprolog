%PLM80


:- use_module(utils).
:- use_module(dcg).

test(A) :-
    open(S,'./tests/plm1.pl',r),
    read_codes(S,C),
    tokenize(C,T),write(T),nl,
    compile(T,A),
    close(S).

compile(T,A) :-
    parse(T,A).

parse(S,A) :-
    phrase(program(A),S).

program(A) --> pl_module(A).
program(A) --> statements(A).

pl_module(module(X,S)) -->
    identifier(X), [':'],
    ['DO'], [';'],
    statements(S),
    ['END'], identifier(X), [';'].


statements([])  --> [].
statements([S|Ss]) --> statement(S),statements(Ss).


statement(while(V,S)) -->
    ['DO'],['WHILE'],test(V),[';'],statements(S),['END'],[';'].
statement(case(V,S)) -->
    ['DO'],['CASE'],test(V),[';'],statements(S),['END'],[';'].
statement(if(V,S1,S2)) -->
    ['IF'],test(V),['THEN'],statement(S1),['ELSE'],statement(S2).    
statement(if(V,S)) -->
    ['IF'],test(V),['THEN'],statement(S).
statement(proc(N,P,S,T)) -->
    identifier(N),[':'],['PROCEDURE'],param(P),data_type(T),[';'],
    statements(S),['END'],identifier(N),[';'].
statement(assign(X,V)) -->
    identifier(X),['='],expression(V),[';'].
statement(return(S)) -->
    ['RETURN'],expression(S),[';'].
statement(return(void)) -->
    ['RETURN'],[';'].    
statement(declare(P,T)) -->
    ['DECLARE'],param(P),data_type(T),[';'].
statement(declare(V,T)) -->
    ['DECLARE'],identifier(V),data_type(T),[';'].
statement(label(N,S)) -->
    identifier(N),[':'],statement(S).
statement(goto(N)) -->
    ['GOTO'],identifier(N),[';'].
statement(halt) -->
    ['HALT'],[';'].
statement(block(S)) -->
    block(S).

block(S) -->
    ['DO'],[';'],statements(S),['END'],[';'].


param(S) -->
    ['('],params(S),[')'].

params([]) --> [].
params([S]) --> identifier(S).
params([S]) --> pl_constant(S).
params([S|Ss]) -->
    identifier(S),[','],params(Ss).
params([S|Ss]) -->
    pl_constant(S),[','],params(Ss).



expression(X) --> pl_constant(X).
expression(X) --> pl_function(X).
expression(E) --> add_expr(E).

add_expr(E) -->
    mul_expr(T),
    add_rest(T, E).

add_rest(Acc, E) -->
    add_op(Op),
    mul_expr(T),
    { Acc1 = expr(Op, Acc, T) },
    add_rest(Acc1, E).
add_rest(Acc, Acc) --> [].

mul_expr(E) -->
    primary(P),
    mul_rest(P, E).

mul_rest(Acc, E) -->
    mul_op(Op),
    primary(P),
    { Acc1 = expr(Op, Acc, P) },
    mul_rest(Acc1, E).
mul_rest(Acc, Acc) --> [].

add_op('+') --> ['+'].
add_op('-') --> ['-'].

mul_op('*') --> ['*'].
mul_op('//') --> ['//'].

primary(E) --> pl_constant(E).
primary(E) --> pl_function(E).
primary(E) --> ['('], expression(E), [')'].


arithmetic_op('+') --> ['+'].
arithmetic_op('-') --> ['-'].
arithmetic_op('*') --> ['*'].
arithmetic_op('//') --> ['//'].


pl_constant(name(X)) --> identifier(X).
pl_constant(number(X)) --> pl_integer(X).

pl_function(func(N,P)) --> identifier(N),param(P).

identifier(X) --> [X],{atom(X),not(reserved(X))}.
pl_integer(X) --> [X],{integer(X)}.

reserved('DO'). reserved('END'). reserved('WHILE'). reserved('CASE').
reserved('IF'). reserved('THEN'). reserved('ELSE').
reserved('PROCEDURE'). reserved('DECLARE'). reserved('RETURN').
reserved('GOTO'). reserved('HALT').
reserved('ADDRESS'). reserved('BYTE').
reserved('AND'). reserved('OR'). reserved('XOR').


test(comp(Op,X,Y)) -->
    expression(X),comparison_op(Op),expression(Y).


comparison_op('=') --> ['='].
comparison_op('<>') --> ['<>'].
comparison_op('>') --> ['>'].
comparison_op('<') --> ['<'].
comparison_op('>=') --> ['>='].
comparison_op('<=') --> ['<='].

logic_op(and) --> ['AND'].
logic_op(or) --> ['OR'].
logic_op(xor) --> ['XOR'].

data_type(addr) --> ['ADDRESS'].
data_type(byte) --> ['BYTE'].

