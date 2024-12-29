
%How can I determine it? This cannot be optimized.
listn(0,[]).
listn(N,[R|X]) :- R is randi(100),N1 is N-1,listn(N1,X). 

% N L B D are not depend on left-hand of is/2
nodiag([], _, _).
nodiag([N|L], B, D) :-
    D =\= N - B,
    D =\= B - N,
    D1 is D + 1,
    nodiag(L, B, D1).
   

%not self independence
foo(0,[]).
foo(N,[N|X]) :- N1 is N-1,foo(N1,X).

