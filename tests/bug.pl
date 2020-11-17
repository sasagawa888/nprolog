
pp(A,B,C) :- A^2 + B^2 =:= C^2,
            write(A), write(', '), write(B), write(', '), write(C), nl.
pp(A,B,C).

pa(A,B,C) :- A =:= B.
pa(A,B,C) :- pp(A,B,C), N is A + 1, pa(N,B,C).

pb(A,B,C) :- B =:= C.
pb(A,B,C) :- pa(A,B,C), N is B + 1, pb(1,N,C).

pc(A,B,C,Max) :- C > Max.
pc(A,B,C,Max) :- pb(1,1,C), N is C + 2, pc(1,1,N,Max).

run(Max) :- pc(1,1,1,Max).