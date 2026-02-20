:- use_module(dcg).

t1 :- phrase(([a],[b]), [a,b]).
t2 :- phrase(([a];[b]), [b]).
t3 :- phrase(([a],!,[b];[a],[c]), [a,b]).
t4 :- phrase(([word(W)],{W='X'}), [word('X')]).