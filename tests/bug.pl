myappend([],L,L) :- !.
myappend([A|L],B, [A|C]):-
	myappend(L,B,C).