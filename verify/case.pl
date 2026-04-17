p.
q.
r :- fail.

a :- write('a'), nl.
b :- write('b'), nl.
c :- write('c'), nl.

t1 :- case([true->a | b]).
% expected: a

t2 :- case([fail->a | b]).
% expected: b

t3 :- case([true->fail | b]).
% expected: fail

t4 :- case([fail->fail | b]).
% expected: b

t5 :- case([true->true | fail]).
% expected: success

t6 :- case([fail->true | true]).
% expected: success

t7 :- case([fail->a, true->b | c]).
% expected: b

t8 :- case([fail->a, fail->b | c]).
% expected: c

t9 :- case([true->a, true->b | c]).
% expected: a

t10 :- case([true->fail, true->b | c]).
% expected: fail
