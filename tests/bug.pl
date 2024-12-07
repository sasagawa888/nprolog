%test
seq :- test1,test2,write(done).

test1 :- fail.
test1.

test2 :- fail.
test2.
