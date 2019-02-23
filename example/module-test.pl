:- module(my_list_stuff).
:- export([last/2,my_reverse/2]).

:- begin_module(my_list_stuff).

last([E],E).
last([_|E],Last) :- last(E,Last).

my_reverse(List1,List2) :- reverse_aux(List1,[],List2).

reverse_aux([H|T],Stack,Result) :-
    reverse_aux(T,[H|Stack],Result).
revarse_aux([],Result,Result).

:- end_module.
