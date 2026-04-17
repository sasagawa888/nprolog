

my_between(L, H, L) :- L =< H.
my_between(L, H, V) :- L < H, L1 is L + 1, my_between(L1, H, V).