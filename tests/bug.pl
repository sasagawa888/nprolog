
my_length([],0).
my_length([L|Ls],N) :-
  my_length(Ls,N1),
  N is N1 + 1.

rotate(L1, L2) :-
  append(Left, Right, L1),
  append(Right, Left, L2). 

rotate1(L1, N, L2) :-
  length(Right, N),
  append(Left, Right, L1),
  append(Right, Left, L2).

reverse_x( A,  B ) :- reverse_x( A, B, [] ).
reverse_x( [], B, C ):- B = C.
reverse_x( A,  B, C ):- A=[Ax|Ay], D=[Ax|C], reverse_x( Ay, B, D ).

foo(_) :- write(_).