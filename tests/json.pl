% JSON

:- op(500,xfy,':').

:- set_prolog_flag(string,iso).

reset_json :- set_prolog_flag(string,arity).

term_to_json(X,J) :-
    string(X).

term_to_json(X,J) :-
    atom(X),
    string_term(J,X).

term_to_json(X,X) :-
    number(X).


term_to_json(X,J) :-
    list(X),
    term_to_json_list(X,J).


term_to_json_list([],[]).
term_to_json_list([L|Ls],[J|Js]) :-
    term_to_json(L,J),
    term_to_json_list(Ls,Js).


    
